// ---------
// includes
// ---------
#include <stdio.h>


// ---------
// prototypes
// ---------
// empty


// ---------
// execution
// ---------
// 
// ! IMPORTANT
// 
// This is a very SIMPLIFIED version
// 
// note that you SHOULD NOT consider
// this code 'correct'.
// Yeah, it works...
// But it's not a good solution
// 
// see intermediate version
int main(void)
{
    // request number from user
    unsigned int n;

    // (U)ser (I)nterface elements
    printf("Hey, enter a positive number less than 1000 ");

    // %u is used to format as an `unsigned int`
    // 
    // note that we provide the ADDRESS of `n`
    // and NOT `n` itself.
    scanf("%u", &n);
    printf("\n");   // just for formatting


    // ----------------
    // TASK 1
    // even or odd
    // 
    // compute & print results
    // ----------------
    if ((n % 2) == 0)
    {
        printf("The number %u is even.\n", n);
    }
    else
    {
        printf("The number %u is odd.\n", n);
    }


    // ----------------
    // TASK 2
    // prime or not
    //  
    // compute & print results
    // ----------------
    int n_is_a_prime = 1;   // setting a default of true

    for (int i = 2; i < n; i++)
    {
        if ((n % i) == 0)
        {
            n_is_a_prime = 0;
        }
    }

    if (n_is_a_prime)
    {
        printf("The number %u is a prime.\n", n);
    }
    else
    {
        printf("The number %u is not a prime.\n", n);
    }


    // ----------------
    // TASK 3
    // all primes in `n`
    //  
    // compute & print results
    // check all numbers up to `n` for prime
    // 
    // ! IMPORTANT
    // 
    // This is NOT the most efficient nor elegant solution
    // Computing a prime takes n-iterations
    // This results in an efficiency of O(n)
    // 
    // see intermediate version
    // 
    // also... just... don't... write code like this xD
    // ----------------
    printf("\nAll prime numbers in %u:\n", n);
    for (int i = 2; i < n; i++)
    {
        int prime = 1;

        for (int j = 2; j < i; j++)
        {
            if ((i % j) == 0)
            {
                prime = 0;
            }
        }

        if (prime)
        {
            printf("The number %i is a prime.\n", i);
        }
    }


    // ----------------
    // TASK 4
    // prime factors of `n`
    //  
    // compute & print results
    // 
    // This task is by definition an intermediate task
    // 
    // see intermediate version
    // ...


    // ----------------
    // TASK 5
    // GCD of `n` and `m`
    //  
    // compute & print results
    // 
    // see advanced version for GCD computation
    // ...


    return 0;
}
