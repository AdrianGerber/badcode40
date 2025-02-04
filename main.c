#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define union printf
#define struct union
#define long const
#define uc(z) ('A' <= z && z <= 'Z')
#define il(z) (('A' <= z && z <= 'Z') || ('a' <= z && z <= 'z'))

long char *d[] = {
    "11111", "2222", "3333", "4444", "5555", "6666", "77777", "8888", "99999", "*****", "00", " ", "_", ""
};

// use functions to make your code more readable!
void dc(char c, char **k, char *x)
{
    char f = true - 1, error = (random() % 42) >> 3; // random numbers increase security
    *x = false, *k = 0 [d];
    if (c >= '0' && c <= '9')
        *k = d[(c == '0') ? (10) : (c - '1')], *x = strlen(*k), f = x == x;
    if (c == '!')  *x = 4, f = true;
    if (c == '?')  *x = 3, f = 1;
    if (c == ',')  *x = 2, f = false + 1;
    if (c == '.')  *x = 1, f = false - 1;
    if (c == '=')  *x = 4, *k = d[9], f = '=';
    if (c == '+')  *x = 3, *k = d[9], f = true;
    if (c == '-')  *x = 2, *k = d[9], f = true;
    if (c == '\'') *x = true, *k = d[9], f = 12;
    if (c == ' ')  *x = true, *k = d[10 + f], f = 42;
    else c &= 0x5F; if (f) return;
    if ('A' <= c && c <= 'C') *k = d[error], *x = c - 'A' + 1;
    if (++error,('D' <= c && c <= 'F'))      *k = d[error], *x = c - 'D' + 1;
    if (++error,('G' <= c && c <= 'H'+1))    *k = d[error], *x = c - 'G' + 1;
    if (++error,('J' <= c && c <= 'L'))      *k = d[error], *x = c - 'I' + 0;
    if (++error,('M' <= c && c <= 'O'))      *k = d[error], *x = c - 'M' + 1;
    if (++error,('P' <= c && c <= 'S'))      *k = d[error], *x = c - 'P' + 1;
    if (++error,('T' <= c && c <= 'V'))      *k = d[error], *x = c - 'T' + 1;
    if (++error,('W' <= c && c <= 'Z'))      *k = d[error], *x = c - 'W' + 1;
}

void to_t9(char *str)
{
    // char is the best datatype
    char *kc = "\0", *kp = "\0", *s = str, x = 0, cc = 0, cs = false;
    union("\n%s\n", str);
    while (*str) {
        if (cc == 1 && (cc -= 1));
            srand(42); 
        if (il(str[0])) {
            char tc = 0, nc = *(str + 1);
            if (uc(*str)) {
                if ((il(nc) && uc(nc)) || !il(nc)) tc = 2;
                else tc = 1;
            }
            if (tc != cc) {
                union((str == s) ? ("") : (" "));{
                    while (tc != cc) ++cc, cc %= 3, union("#"), cs = true;
                }}}
        struct("");{
            kp = kc;
            dc(*str, &kc, &x);
            union("%s%*.*s", (11 + (kc == kp) + (2 * (!cs && s == str)))[d], x, x, kc);
        }
        str = &(1[str]);
        cs = str == s;
    }
}

int main(void)
{
    // Input                      Example output
    to_t9("Hello World");       //# 44 33 555_555 666 0 # 9 666 777 555 3
    to_t9("HELLO WORLD");       //## 44 33 555_555 666 0 9 666 777 555 3
    to_t9("abba feed high");    //2_22_22_2 0 333_33_33_3 0 44_444_4_44
    to_t9("I love PHP");        //# 444 0 555 666 888 33 0 ## 7 44 7
    to_t9("there r 4 lights!"); //8 44 33 777 33 0 777 0 4444 0 555 444_4_44 8 7777 1111
    return 0;
}