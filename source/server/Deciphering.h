#ifndef DECIPHERING_H
#define DECIPHERING_H
#include <iostream>
#include <string.h>
#include <math.h>

using namespace std;

class Deciphering
{
        char miwen[32];
        int Key;

public: Deciphering(char miwen2[32])
        {
                strcpy(miwen,miwen2);
                Key = 3;
        }
        char* decipher()
        {
            char * Str = new char[32];
            strcpy(Str,miwen);
          //Str=miwen;
                int l = strlen(Str);
                //char mingwen[32];
                Key=Key%26;
                for(int i = 0; i < l; i++)
                {
                        if(Str[i] >= 65 && Str[i] <=90)
                        {
                                Str[i] = Str[i]-Key;
                                if(Str[i]<65)
                              {
                               Str[i]=91-(65-Str[i])%26;
                              }
                        if(Str[i]>90)
                           {
                             Str[i]=(Str[i]-90)%26+64;
                           }
                         }
            if(Str[i] >= 97 && Str[i] <=122)
                 {
                    Str[i] = Str[i]-Key;
                      if(Str[i]<97)

                     {
                       Str[i]=123-(97-Str[i])%26;
                     }
                      if(Str[i]>122)
                     {
                       Str[i]=(Str[i]-122)%26+96;
                     }
                 }
              if(Str[i] >= 48 && Str[i] <=57)
                        {
                                Str[i] = Str[i]-Key;
                                if(Str[i]<48)
                              {
                               Str[i]=58-(48-Str[i])%10;
                              }
                        if(Str[i]>57)
                           {
                             Str[i]=(Str[i]-57)%10+47;
                           }
                         }
                }
                return Str;
        }
};
#endif // DECIPHERING_H
