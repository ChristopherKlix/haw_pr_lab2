from math import sqrt
from os import system

SMALLEST_PRIME = 2

def main():
    
    UI.welcome()

    n = int(input('    Enter a number: '))

    UI.computing()

    primes = compute_primes_in(n)
    factors = compute_factors_in(n)

    print(primes)
    print(factors)

    print(f'        {n} is {("even" if is_even(n) else "odd")}')
    print(f'        {n} is {("" if is_prime(n) else "not ")}a prime')
    UI.line()


def compute_primes_in(_n):
    primes = set()
    for i in range(3, _n, 2):
        if (is_prime(i)): primes.add(i)
    return primes


def compute_factors_in(_n):
    factors = list()
    _f = SMALLEST_PRIME

    while _n > 1:
        if not (_n % _f):
            _n /= _f
            factors.append(_f)
        else:
            _f = get_next_prime(_f)


    return factors


def get_next_prime(_n):
    _n += 1
    while (not is_prime(_n)): _n += 1
    return _n


def is_even(n):
    return not (n % 2)


def is_prime(n):
    if is_even(n): return False

    for i in range(3, int(sqrt(n)), 2):
        if not (n % i): return False

    return True


class UI:
    def h1(s):
        print(f'        {s}')

    def h2(s):
        print(f'        {s}')

    def welcome():
        system('clear')

        UI.line()
        UI.h1('PRIMES')
        UI.line()

    def computing():
        UI.line()
        UI.h2('Calculating...')
        UI.line()

    def line():
        print('-' * 32)


if __name__ == '__main__':
    main()
