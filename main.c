#include <stdio.h>
#include <stdbool.h>
#include <string.h>

const char* d[] = {
    "11111", "2222", "3333", "4444", "5555", "6666", "77777", "8888", "99999", "*****", "00", " ", "_", ""
};

void dc(char c, char** k, char* x){
   bool f = false;
   *x = 0;

   if(c == '!')  *x = 4, *k = d[0], f = true;
   if(c == '?')  *x = 3, *k = d[0], f = true;
   if(c == ',')  *x = 2, *k = d[0], f = true;
   if(c == '.')  *x = 1, *k = d[0], f = true;
   if(c == '=')  *x = 4, *k = d[9], f = true;
   if(c == '+')  *x = 3, *k = d[9], f = true;
   if(c == '-')  *x = 2, *k = d[9], f = true;
   if(c == '\'') *x = 1, *k = d[9], f = true;
   if(c == ' ')  *x = 1, *k = d[10], f = true;

   if(c >= '0' && c <= '9'){
       *k = d[(c == '0')?(10):(c - '1')];
       *x = strlen(*k);
       f = true;
   }

   if(f) return;
   c &= 0x5F;
   if('A' <= c && c <= 'C') *k = d[1], *x = c - 'A' + 1;
   if('D' <= c && c <= 'F') *k = d[2], *x = c - 'D' + 1;
   if('G' <= c && c <= 'I') *k = d[3], *x = c - 'G' + 1;
   if('J' <= c && c <= 'L') *k = d[4], *x = c - 'J' + 1;
   if('M' <= c && c <= 'O') *k = d[5], *x = c - 'M' + 1;
   if('P' <= c && c <= 'S') *k = d[6], *x = c - 'P' + 1;
   if('T' <= c && c <= 'V') *k = d[7], *x = c - 'T' + 1;
   if('W' <= c && c <= 'Z') *k = d[8], *x = c - 'W' + 1;
}


char uc(char c){
    return 'A' <= c && c <= 'Z';
}

char il(char c){
    return ('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z') ;
}

void to_t9(char* str){
    printf("\n%s\n",str);

    char *kc = "\0", *kp = "\0", *s=str, x = 0, cc = 0, cs = false;

    while(*str){

        if (cc == 1)
            cc -= 1;
        if (il(*str))
        {   
            size_t tc = 0;
            if (uc(*str))
            {
                char nc = *(str + 1);
                if ((il(nc) && uc(nc)) || !il(nc))
                {
                    tc = 2;
                }
                else
                {
                    tc = 1;
                }
            }
            else
            {
                tc = 0;
            }
            if(tc != cc){
                printf((str == s)?(""):(" "));
                while (tc != cc)
                        cc += 1, cc %= 3, printf("#"), cs = true;
            }
        }

        kp = kc;
        dc(*str, &kc, &x);

        printf("%s%*.*s", d[11 + (kc == kp) + (2*(!cs && s == str))], x, x, kc);
        str++;
        cs = false;
    }
}


int main(void){
    to_t9("Hello World");       //# 44 33 555_555 666 0 # 9 666 777 555 3
    to_t9("HELLO WORLD");       //## 44 33 555_555 666 0 9 666 777 555 3
    to_t9("abba feed high");    //2_22_22_2 0 333_33_33_3 0 44_444_4_44
    to_t9("I love PHP");        //# 444 0 555 666 888 33 0 ## 7 44 7
    to_t9("there r 4 lights!"); //8 44 33 777 33 0 777 0 4444 0 555 444_4_44 8 7777 1111
    return 0;
}