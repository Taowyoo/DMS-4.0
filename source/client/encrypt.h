#ifndef ENCRYPT_H
#define ENCRYPT_H

namespace encryption {

class encrypt
{
private:
    char  plainText[32];
    int key;
public:
    encrypt(){}
    encrypt(const char mingwen2[32]);

    char* cipherText();
};

}


#endif // ENCRYPT_H
