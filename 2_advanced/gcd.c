// ---------
// includes & defines
// ---------
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <errno.h>

#define SMALLEST_PRIME 2
#define DEBUG 0


// ---------
// prototypes
// ---------
#include "main.h"


// ---------
// execution
// ---------
int main(int argc, char const *argv[])
{
    // request numbers from user
    unsigned int a;
    unsigned int b;

    // (U)ser (I)nterface elements
    // 
    // %u is used to format as an `unsigned int`
    // 
    // note that we provide the ADDRESS of `n`
    // and NOT `n` itself.
    do
    {
        system("clear");
        ui_headline("Welcome to GCD!");

        printf("Please, enter two positive number\nless than 1000:\n");
        printf("First number:  ");
        scanf("%u", &a);
    }
    while (!check_for_valid_input(&a));

    do
    {
        system("clear");
        ui_headline("Welcome to GCD!");
        printf("Please, enter two positive\nnumbers less than 1000:\n");
        printf("First number:  %u\n", a);
        printf("Second number: ");
        scanf("%u", &b);
    }
    while (!check_for_valid_input(&b));

    ui_line();
    printf("    Calculating GCD(%u,%u)...\n", a, b);
    ui_line();

    if (DEBUG) printf("a: %u\n", a);
    if (DEBUG) printf("b: %u\n", b);

    // Sorting a & b

    // x always is the larger number
    long _x = (a > b) ? a : b;
    // y always is the smaller number
    long _y = (a < b) ? a : b;
    // The remainder of x % y
    long _r;
    long gcd;

    do
    {
        _r = _x % _y;
        _x = _y;
        _y = _r;
    }
    while (_r != 0);

    gcd = _x;

    printf("The GCD(%u,%u) is %li\n", a, b, gcd);
    ui_line();

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