#include "encrypt.h"
using namespace encryption;
#include <cstring>

encrypt::encrypt(const char mingwen2[])
{
    strcpy( plainText,mingwen2);
    key=3;

}

char* encrypt::cipherText()
{
    char *str = new char[32];
    strcpy(str, plainText);

    int m = strlen(str);
    key = key % 26;
    for(int i = 0; i < m; i++)
    {
        if(str[i] >= 65 && str[i] <=90)
        {
            str[i] = str[i]+key;
            if(str[i]<65)
            {
                str[i]=91-(65-str[i])%26;
            }
            if(str[i]>90)
            {
                str[i]=(str[i]-90)%26+64;
            }
        }

        if(str[i] >= 97 && str[i] <=122)
        {
            str[i] = str[i]+key;
            if(str[i]<97)
            {
                str[i]=123-(97-str[i])%26;
            }
            if(str[i]>122)
            {
                str[i]=(str[i]-122)%26+96;
            }
        }

        if(str[i] >= 48 && str[i] <=57)
        {
            str[i] = str[i]+key;
            if(str[i]<48)
            {
                str[i]=58-(48-str[i])%10;
            }
            if(str[i]>57)
            {
                str[i]=(str[i]-57)%10+47;
            }
        }
    }
    return str;
}
