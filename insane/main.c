#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <errno.h>
#include <math.h>
#include <string.h>

// prototyes
void *check_sign(void *args_pointer);
void *check_prime(void *args_pointer);
void *compute_primes(void *args_pointer);
void *_compriupward(void *args);
void *_compridownward(void *args);
void *compute_primefactors(void *args);
int is_prime(unsigned int n);
void *ui_computing(void *args);
// util methods
int msleep(long msec);
int get_int(char *txt);
char *boolean(unsigned int b);

// Main computation engine
void *idle(void *p);

// UI prototypes
void ui_line(void);

// #define COMPUTATION_BOUND 100000000 // 1 billion
#define COMPUTATION_BOUND (unsigned int) 4294967295 // 4.29 billion (largest unsigned int)
#define DEBUG 0
#define MULTITHREADING 1
#define MAX_THREADS 200
#define SQUAREROOT 1
long _counter = 0;
long _primecounter = 0;
int _sleep_t = 0;

// unsigned int _primes[COMPUTATION_BOUND];

// Custom struct to hold args
// to parse into threads as void-pointer
typedef struct
{
    unsigned int n;
    unsigned int is_even;
    unsigned int is_prime;
    unsigned int *primes;
    unsigned int *primefactors;
}
thread_args;

typedef struct
{
    int thread_number;
    thread_args *n_args;
    long bound;
}
ARGS_TO_THREADS;

typedef struct
{
    int is_computing;
    thread_args *n_args;
}
UI_ARGS;



int main(int argc, char const *argv[])
{
    system("clear");

    printf("-----------------------------------\n");
    printf("              PRIMES     \n");
    printf("-----------------------------------\n");

    // Initialize arguments that will be
    // overwritten by threads
    thread_args n_args = {
        .n = 0,
        .is_even = 0,
        .is_prime = 0,
        .primefactors = malloc(100UL * sizeof(unsigned int))
    };

    if (argc >= 2)
    {
        sscanf(argv[1],"%u",&n_args.n);
    }
    else
    {
        char _s[256];
        char _cb[256];
        strcpy(_s, "Please enter a positive number less than ");
        sprintf(_cb, "%u", COMPUTATION_BOUND);
        strcat(_s, _cb);
        strcat(_s, ": ");
        n_args.n = (unsigned int) get_int(_s);
    }

    if (argc >= 3)
    {
        if (strcmp(argv[2], "-a") == 0)
        {
            _sleep_t = 50;
        }
    }

    // Reduce memory by limiting prime
    // array to input n, not COMPUTATION BOUND
    n_args.primes  = malloc(n_args.n * sizeof(unsigned int));

    // Create threads
    pthread_t thread_sign;
    pthread_t thread_prime;
    pthread_t thread_compute_primes;
    pthread_t thread_compute_primefactors;
    pthread_t thread_ui_computing;

    UI_ARGS ui_args = {
        .is_computing = 1,
        .n_args = &n_args
    };

    // Start threads
    if (!DEBUG) pthread_create(&thread_ui_computing, NULL, ui_computing, (void*) &ui_args);
    pthread_create(&thread_sign, NULL, check_sign, (void*) &n_args);
    pthread_create(&thread_prime, NULL, check_prime, (void*) &n_args);
    pthread_create(&thread_compute_primes, NULL, compute_primes, (void*) &n_args);
    pthread_create(&thread_compute_primefactors, NULL, compute_primefactors, (void*) &n_args);

    // Wait for finished execution of threads
    pthread_join(thread_sign, NULL);
    pthread_join(thread_prime, NULL);
    pthread_join(thread_compute_primes, NULL);
    pthread_join(thread_compute_primefactors, NULL);

    ui_args.is_computing = 0;
    pthread_join(thread_ui_computing, NULL);


    ui_line();
    printf("   Primes in %u: %ld (%.2f%%)\n", n_args.n, _primecounter, (double) _primecounter / n_args.n * 100);
    ui_line();

    long print_bound = n_args.n;
    if (n_args.n > 10)
    {
        print_bound = 7;
    }

    for (long i = 0; i < n_args.n; i++)
    {
        if (i >= COMPUTATION_BOUND)
        {
            printf("Computation bound reached: %u\n", COMPUTATION_BOUND);
            break;
        }
        if (n_args.n > 10 && i == 4)
        {
            printf("\n   ...\n\n");
            if (n_args.n > 10000) i = n_args.n - 100;
            else i = n_args.n - n_args.n * 0.1;
            continue;
        }

        if (n_args.primes[i] != 0)
        {
            printf("    %u\n", n_args.primes[i]);
            msleep(_sleep_t);
        }
    }
    ui_line();
    printf("   Prime factors in %u\n", n_args.n);
    ui_line();

    for (int i = 0; n_args.primefactors[i] != 0; i++)
    {
        if (!i)
        {
            printf("    1");
            continue;
        }

        if (i >= COMPUTATION_BOUND)
        {
            printf("Computation bound reached: %u\n", COMPUTATION_BOUND);
            break;
        }
        if (n_args.primefactors[i] != 0)
        {
            printf(" x ");
            printf("%u", n_args.primefactors[i]);
            msleep(_sleep_t);
        }

        // if ((i+1) == n_args.n) printf("\n");
    }
    
    printf("\n");

    ui_line();
    msleep(_sleep_t);
    printf("Value: %u\n", n_args.n);
    msleep(_sleep_t);
    printf("Even:  %s\n", boolean(n_args.is_even));
    msleep(_sleep_t);
    printf("Prime: %s\n", boolean(n_args.is_prime));
    msleep(_sleep_t);
    ui_line();

    free(n_args.primes);
    free(n_args.primefactors);

    return 0;
}


void *ui_computing(void *args)
{
    UI_ARGS *ui_args = (UI_ARGS *) args;
    long _n = ui_args->n_args->n;
    char symbols[4] = {'/', '-', '\\', '|'};
    int i = 0;

    fprintf(stderr, "┌─────────────────────────────────┐\n");
    fprintf(stderr, "│  Computing %c  %-10ld    0%%  │\n", symbols[i++ % 4], 0l);
    fprintf(stderr, "└─────────────────────────────────┘");
    fprintf(stderr, "\33[1A\33[1000C");
    msleep(50);


    while (ui_args->is_computing)
    {
        fprintf(stderr, "\33[2K\r");
        fprintf(stderr, "│  Computing %c  %-10ld  %3d%%  │", symbols[i++ % 4], _counter, (int) (((double) _counter / _n) * 100));
        msleep(50);
    }

    fprintf(stderr, "\33[2K\r");
    fprintf(stderr, "│  Computing \U00002705 %-10ld  100%%  │", _n);
    printf("\n\n");

    return NULL;
}


void *check_sign(void *args_pointer)
{
    thread_args *n_args = (thread_args *) args_pointer;

    (*n_args).is_even = (((*n_args).n % 2) == 0);

    if (DEBUG) printf("# check_sign completed\n");
    return NULL;
}


void *check_prime(void *args_pointer)
{
    // Casting void-pointer to usable struct pointer
    thread_args *n_args = (thread_args *) args_pointer;

    // Check for cardinality
    (*n_args).is_prime = is_prime((*n_args).n);

    if (DEBUG) printf("# check_prime completed\n");
    return NULL;
}


void *compute_primes(void *args_pointer)
{
    // Casting void-pointer to usable struct pointer
    thread_args *n_args = (thread_args *) args_pointer;

    // Create threads for parallel processing
    pthread_t threadup;
    pthread_t threaddown;

    const long N = n_args->n;
    const long _MAX_THREADS = MULTITHREADING ? MAX_THREADS : 1;
    const long T = (N < _MAX_THREADS) ? N : _MAX_THREADS;
    const long CHUNKSC = N / T;


    if (DEBUG) printf("# Thread count: %ld;\n", T);
    if (DEBUG) printf("# Per thread n: %ld;\n", CHUNKSC);

    pthread_t threads[T];
    ARGS_TO_THREADS args_to_threads[T];

    for (long i = 0; i < T; i++)
    {
        args_to_threads[i].thread_number = i;
        args_to_threads[i].n_args = n_args;
        args_to_threads[i].bound = (i)*CHUNKSC;

        pthread_create(&threads[i], NULL, idle, (void*) &(args_to_threads[i]));
    }

    if (DEBUG) printf("# All threads started...\n");

    for (int i = 0; i < T; i++)
    {
        pthread_join(threads[i], NULL);
    }

    if (DEBUG) printf("# All threads completed...\n");

    // Start execution of threads
    // pthread_create(&threadup, NULL, _compriupward, (void*) n_args);
    // pthread_create(&threaddown, NULL, _compridownward, (void*) n_args);

    // Wait for threads to complete
    // pthread_join(threadup, NULL);
    // pthread_join(threaddown, NULL);

    return NULL;
}

void *idle(void *args)
{
    ARGS_TO_THREADS *thread_args = (ARGS_TO_THREADS *) args;

    if (DEBUG) printf("# Thread %d started...\n", thread_args->thread_number);
    if (DEBUG) printf("#    Thread %d bound: %ld;\n", thread_args->thread_number, thread_args->bound);

    long bound = thread_args->bound;
    
    for (long i = bound; i < thread_args->n_args->n && i < COMPUTATION_BOUND; i++)
    {
        _counter++;

        if (thread_args->n_args->primes[i] != 0)
        {
            if (DEBUG) printf("# Thread %d found boundary: %ld\n", thread_args->thread_number, i);
            return NULL;
        }

        if (is_prime((unsigned int) i))
        {
            _primecounter++;
            thread_args->n_args->primes[i] = i;
        }
    }

    return NULL;
}

void *_compriupward(void *args)
{
    thread_args *n_args = (thread_args *) args;
    int n = (*n_args).n;

    for (int i = 0; i < n && i < COMPUTATION_BOUND; i++)
    {
        if ((*n_args).primes[i] != 0)
        {
            printf("_compriupward: Found boundary: %u\n", i);
            return NULL;
        }

        if (is_prime((unsigned int) i))
        {
            (*n_args).primes[i] = i;
        }
    }

    return NULL;
}

void *_compridownward(void *args)
{
    thread_args *n_args = (thread_args *) args;
    int n = (*n_args).n;

    for (int i = n-1; i > 0; i--)
    {
        if ((*n_args).primes[i] != 0)
        {
            printf("_compridownward: Found boundary: %u\n", i);
            return NULL;
        }

        if (is_prime((unsigned int) i))
        {
            (*n_args).primes[i] = i;
        }
    }

    return NULL;
}


void *compute_primefactors(void *args)
{
    thread_args *n_args = (thread_args *) args;
    int _n = (*n_args).n; // working var

    int _f = 2;
    int _i = 0;

    do
    {
        if ((_n % _f) == 0)
        {
            _n /= _f;
            (*n_args).primefactors[_i] = _f;
            _i++;
        }
        else
        {
            do
            {
                _f++;
            } while (!is_prime(_f));
        }
    } while (_n > 1);

    return NULL;
}


int is_prime(unsigned int n)
{
    if (n == 2)
    {
        return 1;
    }

    if ((n % 2) == 0)
    {
        return 0;
    }

    for (int i = 3; i < (SQUAREROOT ? sqrt(n) : n); i+=2)
    {
        if ((n % i) == 0)
        {
            return 0;
        }
    }

    return 1;
}


// 
// Utility functions
// 
// 
int get_int(char *txt)
{
    int n;
    printf("%s", txt);
    scanf("%u", &n);
    while ((getchar()) != '\n') { }
    return n;
}


char *boolean(unsigned int b)
{
    if (b == 0)
    {
        return "False";
    }
    else
    {
        return "True";
    }
}

int msleep(long msec)
{
    struct timespec ts;
    int res;

    if (msec < 0)
    {
        errno = EINVAL;
        return -1;
    }

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    do {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);

    return res;
}

// UI methods
void ui_line(void)
{
    const char *UI_LINE = "───────────────────────────────────";

    printf("%s\n", UI_LINE);
    return;
}
