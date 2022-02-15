#include <stdio.h>

int main(void) {
    unsigned long long card = 4003600000000014;

    unsigned char lhun_toggle = 0;
    unsigned int lhun_num = 0;
    for(unsigned long long i = 1; i <= card; i *= 10, lhun_toggle = !lhun_toggle) {
        unsigned int digit = 0;
        digit = (card / i) % 10;
        if (!lhun_toggle) {
            lhun_num += digit;
        }
        else {
            digit *= 2;
            lhun_num += digit % 10;
            lhun_num += digit / 10;
        }
    }
    printf("lhun num = %i\n", lhun_num);
}
