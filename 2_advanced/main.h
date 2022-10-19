#ifndef MAIN_H_   /* Include guard */
#define MAIN_H_


int check_for_valid_input(unsigned int *);
int is_prime(int);
int is_even(int);
void print_even_or_not(int);
void print_prime_or_not(int);
void print_all_primes(int);
void print_prime_factors(int);

void ui_line(void);
void ui_headline(char *);
void ui_subheadline(char *);

int msleep(long);

#endif