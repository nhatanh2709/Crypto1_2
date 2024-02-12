#include "AES.h"
#include "CBC.h"

int main()
{
    
    CBC aescbc;

    while (1)
    {
        int choosen;
        cout << "Enter your choose\n"
              << "1. Encrypt\n"
              << "2. Decrypt\n";

        cin >> choosen;
        cin.ignore();
        switch (choosen)
        {
            case 1:
            {
                string plain, key, iv;
                cout << "Plaintext: ";
                getline(cin, plain);
                cout << "Key: ";
                getline(cin, key);
                if (key.size() != 16)
                {
                    cout << "Invalid:";
                    exit(0);
                }
                cout << "IV: ";
                getline(cin, iv);
                if (iv.length() != 16)
                {
                    cout << "Invalid";
                    exit(0);
                }
                std::string ciphertext = aescbc.cbc_encrypt(plain, key , iv);
                cout << "Cipher: " << ciphertext << endl;
                break;
 
            }
            case 2:
            {
                string key, iv, cipher;
                cout << "Key: ";
                getline(cin, key);
                if (key.size() != 16)
                {
                    cout << "Invalid:";
                    exit(0);
                }
                cout << "IV: ";
                getline(cin, iv);
                if (iv.length() != 16)
                {
                    cout << "Invalid";
                    exit(0);
                }
                cout << "Ennter your cipher: ";
                getline(cin, cipher);
                std::string plain = aescbc.cbc_decrypt(cipher, key , iv);
                cout << "Plaintext: " << plain << endl;
                exit(0);
            }
            default:
                cout << "Invalid input\n";
                exit(0);
        }
    }
    return 0;
}