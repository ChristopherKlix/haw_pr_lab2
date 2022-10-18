// ---------
// includes & defines
// ---------
#include <stdio.h>

#define SMALLEST_PRIME 2


// ---------
// prototypes
// ---------
int is_prime(int);
int is_even(int);
void print_prime_factors(int);


// ---------
// execution
// ---------
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

    // ----------------
    // TASK 1
    // even or odd
    // 
    // compute & print results
    // ----------------
    if (is_even(n))
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
    if (is_prime(n))
    {
        printf("The number %u is a prime.\n", n);
    }
    else
    {
        printf("The number %u is not a prime.\n", n);
    }


    // ----------------
    // TASK 3
    // all prime in `n`
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
    // see advanced version
    // ----------------
    for (int i = 0; i < n; i++)
    {
        if (is_prime(i))
        {
            printf("%i is a prime\n", i);
        }
    }


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
    // see advanced version for GCD computation
    // ...

    return 0;
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
    printf("Computing prime factors\n"); // AVOID printing out of main()

    int _f = SMALLEST_PRIME;

    do
    {
        if ((_n % _f) == 0)
        {
            _n /= _f;
            printf("%i ", _f); // AVOID printing out of main()
        }
        else
        {
            do
            {
                _f++;
            } while (!is_prime(_f));
        }
    } while (_n > 1);
    
    printf("\n"); // AVOID printing out of main()

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
int is_even(int n)
{
    return ((n % 2) == 0);
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
int is_prime(int n)
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
    if (n == 1)
    {
        return 0;
    }

    if (n == 2)
    {
        return 1;
    }

    // if it has a factor than it's not a prime
    // 
    // this for-loop iterates over all possible dividers (factors)
    // 
    // if it can find a factor, it returns False (0)
    for (int i = SMALLEST_PRIME; i < n; i++)
    {
        if ((n % i) == 0)
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
