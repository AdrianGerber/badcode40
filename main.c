#include <stdio.h>
#include <stdbool.h>
#include <string.h>


const char* decoder[] = {
    "11111", "2222", "3333", "4444", "5555", "6666", "77777", "8888", "99999", "*****", "00", " ", "_", ""
};

void decodeChar(char c, char** key, size_t* count){
   bool k = false;
   *count = 0;

   if(c == '!')  *count = 4, *key = decoder[0], k = true;
   if(c == '?')  *count = 3, *key = decoder[0], k = true;
   if(c == ',')  *count = 2, *key = decoder[0], k = true;
   if(c == '.')  *count = 1, *key = decoder[0], k = true;
   if(c == '=')  *count = 4, *key = decoder[9], k = true;
   if(c == '+')  *count = 3, *key = decoder[9], k = true;
   if(c == '-')  *count = 2, *key = decoder[9], k = true;
   if(c == '\'') *count = 1, *key = decoder[9], k = true;
   if(c == ' ')  *count = 1, *key = decoder[10], k = true;

   if(c >= '0' && c <= '9'){
       *key = decoder[(c == '0')?(10):(c - '1')];
       *count = strlen(*key);
       k = true;
   }


   if(k) return;
   c &= 0x5F; // to uppercase
   if('A' <= c && c <= 'C') *key = decoder[1], *count = c - 'A' + 1;
   if('D' <= c && c <= 'F') *key = decoder[2], *count = c - 'D' + 1;
   if('G' <= c && c <= 'I') *key = decoder[3], *count = c - 'G' + 1;
   if('J' <= c && c <= 'L') *key = decoder[4], *count = c - 'J' + 1;
   if('M' <= c && c <= 'O') *key = decoder[5], *count = c - 'M' + 1;
   if('P' <= c && c <= 'S') *key = decoder[6], *count = c - 'P' + 1;
   if('T' <= c && c <= 'V') *key = decoder[7], *count = c - 'T' + 1;
   if('W' <= c && c <= 'Z') *key = decoder[8], *count = c - 'W' + 1;
}


bool uppercase(char c){
    return 'A' <= c && c <= 'Z';
}

bool isLetter(char c){
    return ('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z') ;
}

void to_t9(char* str){
    printf("\n%s\n",str);

    char *currentKey = "\0", *previousKey = "\0";
    size_t count = 0;
    size_t currentCase = 0;
    char* originalStrPtr = str;
    bool changedCase = 0;
    while(*str){

        // adjust case
        if (currentCase == 1)
            currentCase -= 1;
        if (isLetter(*str))
        {   
            size_t targetCase = 0;
            if (uppercase(*str))
            {
                char nextChar = *(str + 1);
                if ((isLetter(nextChar) && uppercase(nextChar)) || !isLetter(nextChar))
                {
                    targetCase = 2;
                }
                else
                {
                    targetCase = 1;
                }
            }
            else
            {
                targetCase = 0;
            }
            if(targetCase != currentCase){
                printf((str == originalStrPtr)?(""):(" "));
                while (targetCase != currentCase)
                        currentCase += 1, currentCase %= 3, printf("#"), changedCase = true;
            }
        }


        // print character
        previousKey = currentKey;
        decodeChar(*str, &currentKey, &count);

        printf("%s%*.*s", decoder[11 + (currentKey == previousKey) + (2*(!changedCase && originalStrPtr == str))], count, count, currentKey);
        str++;
        changedCase = false;
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