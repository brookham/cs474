#include <stdio.h>

unsigned int digits_sum(unsigned int v)
{
    unsigned int total = 0;

    while (v) {
        total += v % 10;
        v /= 10;
    }

    return total;
}

/*
 * Given an account number with no check digit, compute and return the
 * check digit.
 */
unsigned int luhn_compute_check_digit(unsigned long long v)
{
    int digits[32];
    int n = 0;
    unsigned long long t = v;

    /* Extract digits from right to left */
    while (t > 0 && n < (int)(sizeof(digits)/sizeof(digits[0]) - 1)) {
        digits[n++] = t % 10;
        t /= 10;
    }

    /* shift digits right to insert placeholder for check digit at index 0 */
    for (int i = n; i > 0; i--)
        digits[i] = digits[i - 1];
    digits[0] = 0;
    n++;

    int total = 0;
    for (int i = 0; i < n; i++) {
        int d = digits[i];
        /* Double every second digit from the right (i == 1,3,5,...)*/
        if (i % 2 == 1) {
            d = d * 2;
            if (d > 9)
                d -= 9;
        }
        total += d;
    }

    int chk_digit = (10 - (total % 10)) % 10;
    return chk_digit;
}

int luhn_is_valid(unsigned long long v)
{
    unsigned int check_digit, computed_check_digit;

    check_digit = v % 10;
    computed_check_digit = luhn_compute_check_digit(v / 10);

    return check_digit == computed_check_digit;
}

#define TEST_COUNT 8

int main(void)
{
    unsigned long long account_numbers[TEST_COUNT] = {
        4539908860705595,  // valid
        4916056182581170,  // valid
        5137532317317391,  // valid
        5456126701113392,  // valid
        4539918860705595,  // invalid
        4916056187581170,  // invalid
        5137532317318391,  // invalid
        5456126701113395   // invalid
    };

    for (int i = 0; i < TEST_COUNT; i++)
        printf("Card number %llu: %s\n", account_numbers[i],
            luhn_is_valid(account_numbers[i]) ? "valid" : "invalid");
}