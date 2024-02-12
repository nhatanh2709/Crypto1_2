#include "AES.h"
#include "CBC.h"
#ifdef _WIN32
#include <io.h>
#include <fcntl.h>
#else
#endif
/* Convert string <--> utf8*/
#include <locale>
using std::wstring_convert;
#include <codecvt>
using std::codecvt_utf8;
#ifdef _WIN32
#include <io.h>
#include <fcntl.h>
#endif

int main()
{
    #ifdef __linux__
    setlocale(LC_ALL, "");
    #elif _WIN32
    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stdout), _O_U16TEXT);
    #endif
    CBC aescbc;

    while (1)
    {
        int aescipher;
        wcout << "Enter your choose\n"
              << "1. Encrypt\n"
              << "2. Decrypt\n";

        wcin >> aescipher;
        wcin.ignore();
        switch (aescipher)
        {
            case 1:
            {
                wstring plain, key, iv;
                wcout << "Plaintext: ";
                wcin.ignore();
                getline(wcin, plain);
                wcout << "Key: ";
                wcin.ignore();
                getline(wcin, key);
                if (key.size() != 16)
                {
                    wcout << "Invalid:";
                    exit(0);
                }
                wcout << "IV: ";
                wcin.ignore();
                getline(wcin, iv);
                if (iv.length() != 16)
                {
                    wcout << "Invalid";
                    exit(0);
                }
                std::string ciphertext = aescbc.cbc_encrypt(wstring_to_string(plain), wstring_to_string(key) , wstring_to_string(iv));
                wcout << "Cipher: " << string_to_wstring(ciphertext) << endl;
                break;
 
            }
            case 2:
            {
                wstring key, iv, cipher;
                wcout << "Ennter your cipher: ";
                wcin.ignore();
                getline(wcin, cipher);                
                wcout << "Key: ";
                wcin.ignore();
                getline(wcin, key);
                if (key.size() != 16)
                {
                    wcout << "Invalid:";
                    exit(0);
                }
                wcout << "IV: ";
                wcin.ignore();
                getline(wcin, iv);
                if (iv.length() != 16)
                {
                    wcout << "Invalid";
                    exit(0);
                }
                
                std::string plain = aescbc.cbc_decrypt(wstring_to_string(cipher), wstring_to_string(key), wstring_to_string(iv));
                wcout << "Plaintext: " << string_to_wstring(plain) << endl;
                exit(0);
            }
            default:
                wcout << "Invalid input\n";
                exit(0);
        }
    }
    return 0;
}