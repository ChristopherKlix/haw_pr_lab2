// ---------
// includes & defines
// ---------
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <errno.h>

#define SMALLEST_PRIME 2


// ---------
// prototypes
// ---------
#include "main.h"


// ---------
// execution
// ---------
int main(int argc, char const *argv[])
{
    // request number from user
    unsigned int n;

    // (U)ser (I)nterface elements
    // 
    // %u is used to format as an `unsigned int`
    // 
    // note that we provide the ADDRESS of `n`
    // and NOT `n` itself.
    do
    {
        system("clear");
        ui_headline("Welcome to PRIMES!");

        printf("Please, enter a positive number\nless than 1000: ");
        scanf("%u", &n);
    }
    while (!check_for_valid_input(&n));


    // ----------------
    // TASK 1
    // even or odd
    // 
    // compute & print results
    // ----------------
    print_even_or_not(n);


    // ----------------
    // TASK 2
    // prime or not
    //  
    // compute & print results
    // ----------------
    print_prime_or_not(n);


    // ----------------
    // TASK 3
    // all prime in `n`
    //  
    // compute & print results
    // check all numbers up to `n` for prime
    // ----------------
    print_all_primes(n);


    // ----------------
    // TASK 4
    // prime factors of `n`
    //  
    // compute & print results
    // 
    print_prime_factors(n);


    // ----------------
    // TASK 5
    // GCD of `n` and `m`
    //  
    // compute & print results
    // 
    // function can be called in separate file

    return 0;
}


int check_for_valid_input(unsigned int *_n)
{
    if ((int) *_n >= 1000)
    {
        printf("\nInvalid input: number must be less than 1000\n\n");
    }
    else if ((int) *_n < 0)
    {
        printf("\nInvalid input: number must be a positive number\n\n");
    }
    else
    {
        return 1;
    }

    fprintf(stderr, "    Try again in 3 second.");
    msleep(1000);
    fprintf(stderr, "\033[2K\r");
    fprintf(stderr, "    Try again in 2 second..");
    msleep(1000);
    fprintf(stderr, "\033[2K\r");
    fprintf(stderr, "    Try again in 1 second...");
    msleep(1000);

    return 0;
}


// This function computes and prints wether `n` is even or not
// 
// Since this code only prints the result
// to screen, it does NOT have a return value.
// 
// To signal this to the programmer, it returns `void`
// 
// ! IMPORTANT
// 
// This function has SIDE-EFFECTS
// It does print to the screen without `main()` knowing of it
// 
// This should be avoided!
// 
void print_even_or_not(int _n)
{
    ui_subheadline("EVEN OR ODD?");

    if (is_even(_n))
    {
        printf("The number %u is even.\n", _n);
    }
    else
    {
        printf("The number %u is odd.\n", _n);
    }

    return;
}


// This function computes and prints wether `n` is a prime
// 
// Since this code only prints the result
// to screen, it does NOT have a return value.
// 
// To signal this to the programmer, it returns `void`
// 
// ! IMPORTANT
// 
// This function has SIDE-EFFECTS
// It does print to the screen without `main()` knowing of it
// 
// This should be avoided!
// 
void print_prime_or_not(int _n)
{
    ui_subheadline("PRIME OR NOT?");

    if (is_prime(_n))
    {
        printf("The number %u is a prime.\n", _n);
    }
    else
    {
        printf("The number %u is not a prime.\n", _n);
    }

    return;
}


// This function computes and prints all primes from 0 to `n`
// 
// Since this code only prints the result
// to screen, it does NOT have a return value.
// 
// To signal this to the programmer, it returns `void`
// 
// ! IMPORTANT
// 
// This function has SIDE-EFFECTS
// It does print to the screen without `main()` knowing of it
// 
// This should be avoided!
// 
void print_all_primes(int _n)
{
    ui_subheadline("COUNTING PRIMES");

    int _printed_primes = 0;

    for (int i = 0; i < _n; i+=2)
    {
        if (i == 0) i++;

        if (is_prime(i))
        {
            printf("%5i", i);
            _printed_primes++;

            if ((_printed_primes % 6) == 0)
            {
                printf("\n");
            }
        }
    }

    if (!_printed_primes)
    {
        printf("This number has no primes.");
    }

    printf("\n");

    return;
}

// This function computes and prints all prime factors of `n`
// 
// Since this code only prints the result
// to screen, it does NOT have a return value.
// 
// To signal this to the programmer, it returns `void`
// 
// ! IMPORTANT
// 
// This function has SIDE-EFFECTS
// It does print to the screen without `main()` knowing of it
// 
// This should be avoided!
// 
void print_prime_factors(int _n)
{
    ui_subheadline("COMPUTING PRIME FACTORS");
    int _printed_factors = 0;

    int _f = SMALLEST_PRIME;

    do
    {
        if ((_n % _f) == 0)
        {
            _n /= _f;
            printf("%5i", _f);
            _printed_factors++;

            if ((_printed_factors % 6) == 0)
            {
                printf("\n");
            }
        }
        else
        {
            do
            {
                _f++;
            } while (!is_prime(_f));
        }
    } while (_n > 1);
    
    if (!_printed_factors)
    {
        printf("This number has no prime factors.");
    }

    printf("\n");
    ui_line();

    return;
}


// This function simply checks for even/odd
// 
// The return value is either:
//      1   :=  True (even)
//      0   :=  False (odd)
// 
// This solution does not care about sign (+ / -)
// 
// But it does integer overflow for numbers larger than 4 bytes
// 
// This function only simplifies code-readibility
// 
int is_even(int _n)
{
    return ((_n % 2) == 0);
}


// This function checks if the provided number n
// is a prime or not
// 
// The return value is either:
//      1   :=  True
//      0   :=  False
// 
// This solution does not care about sign (+ / -)
// 
// But it does integer overflow for numbers larger than 4 bytes
// 
// It also is not the most efficient implementation
// 
// ! IMPORTANT
// see the advanced version for a more elegant solution
// 
int is_prime(int _n)
{
    // Covering edge case of 1 & 2
    // 
    // Since 1 is only divisble by 1 and... 1
    // the code would count this as a prime
    // 
    // But 1 is a special case that does NOT count as a prime
    // 
    // Since 2 is divisble by 2, it would be considered
    // not a prime
    // 
    // But 2 is a special case that counts as a prime
    // 
    // ! IMPORTANT
    // see the advanced version for a more elegant solution
    // 
    if (_n == 1) return 0;
    else if (_n == 2) return 1;


    // if it has a factor than it's not a prime
    // 
    // this for-loop iterates over all possible dividers (factors)
    // 
    // if it can find a factor, it returns False (0)
    for (int i = SMALLEST_PRIME+1; i < sqrt(_n); i+=2)
    {
        if ((_n % i) == 0)
        {
            return 0;
        }
    }

    // At this point, there is not factor in n
    // therefore it has to be a prime
    // 
    // the function returns True (1)
    return 1;
}


void ui_line(void)
{
    printf("--------------------------------\n");
}

void ui_headline(char *txt)
{
    printf("--------------------------------\n");
    printf("        %s\n", txt);
    printf("--------------------------------\n");
}

void ui_subheadline(char *txt)
{
    printf("\n        %s\n", txt);
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