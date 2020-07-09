#include <stdio.h>
#include <stdbool.h>


const char* decoder = "1111" "\0" "222" "\0" "333" "\0" "444" "\0" "555" "\0" "666" "\0" "7777" "\0" "888" "\0" "9999" "\0" "****" "\0" "0";
const char* separator[2] = {" ", "_"};


void decodeChar(char c, char* key, size_t* offset){
    *key = '-';
    if(c == '!')  *offset = 0, *key = '1';
    if(c == '?')  *offset = 1, *key = '1';
    if(c == ',')  *offset = 2, *key = '1';
    if(c == '.')  *offset = 3, *key = '1';
    if(c == '=')  *offset = 39, *key = '*';
    if(c == '+')  *offset = 40, *key = '*';
    if(c == '-')  *offset = 41, *key = '*';
    if(c == '\'') *offset = 42, *key = '*';
    if(c == ' ')  *offset = 44, *key = '0';





    if(*key != '-') return;




    c &= 0x5F; // to uppercase
    if('A' <= c && c <= 'C') *offset = 5  + ('C'-'A') - (c - 'A'), *key = '2';
    if('D' <= c && c <= 'F') *offset = 9  + ('F'-'D') - (c - 'D'), *key = '3';
    if('G' <= c && c <= 'I') *offset = 13 + ('I'-'G') - (c - 'G'), *key = '4';
    if('J' <= c && c <= 'L') *offset = 17 + ('L'-'J') - (c - 'J'), *key = '5';
    if('M' <= c && c <= 'O') *offset = 21 + ('O'-'M') - (c - 'M'), *key = '6';
    if('P' <= c && c <= 'S') *offset = 25 + ('S'-'P') - (c - 'P'), *key = '7';
    if('T' <= c && c <= 'V') *offset = 30 + ('V'-'T') - (c - 'T'), *key = '8';
    if('W' <= c && c <= 'Z') *offset = 34 + ('Z'-'W') - (c - 'W'), *key = '9';



}


bool uppercase(char c){
    return 'A' <= c && c <= 'Z';
}

bool isLetter(char c){
    return ('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z') ;
}

void to_t9(char* str){
    printf("\n%s\n",str);

    char currentKey = '\0', previousKey = '\0';
    size_t offset = 0;
    size_t currentCase = 0;
    char* originalStrPtr = str;
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
                        currentCase += 1, currentCase %= 3, printf("#");
            }
        }


        // print character
        previousKey = currentKey;
        decodeChar(*str, &currentKey, &offset);
        printf("%s%s", separator[currentKey == previousKey], decoder + offset);
        str++;
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