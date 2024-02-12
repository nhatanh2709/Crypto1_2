#include "Encryption.h"
#include "Decrytion.h"
#include "library.h"
string GetString(string fileName)
{
    string output;
    ifstream file;
    file.open(fileName);
    output.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return output;
}
void print_key_iv()
{
    string encodedKey, encodedIV;
    StringSource(key, sizeof(key), true, new HexEncoder(new StringSink(encodedKey)));
    StringSource(iv, sizeof(iv), true, new HexEncoder(new StringSink(encodedIV)));
    cout << "Generated Key: " << encodedKey << endl;
    cout << "Generated IV: " << encodedIV << endl;
    return ;
}
void KeyIVScreen(int mode) 
{
    cout << "Enter key:";
    string keyName;
    cin >> keyName;
    cin.ignore();
    StringSource(keyName,true,new HexDecoder(new ArraySink(key,sizeof(key))));
    if (mode == 1)
        return;
    cout << "Enter IV:";
    string IVName;
    cin >> IVName;
    StringSource(IVName,true,new HexDecoder(new ArraySink(iv,sizeof(iv))));
}
void KeyIVGen(int mode)
{
    AutoSeededRandomPool prng;
    prng.GenerateBlock(key, sizeof(key));
    prng.GenerateBlock(iv, sizeof(iv));    
    print_key_iv();         
}
void KeyIVFile(int mode)
{
    string fileKey,fileIv;
    cout << "Enter key file name:";
    cin >> fileKey;
    std::ifstream keyFile(fileKey, std::ios::binary);
    keyFile.read(reinterpret_cast<char*>(key), sizeof(key));
    keyFile.close();
    if ( mode == 1) return ;
    cout << "Enter Iv file name:";
    cin >> fileIv;
    std::ifstream ivFile(fileIv, std::ios::binary);
    ivFile.read(reinterpret_cast<char*>(iv), sizeof(iv));
    ivFile.close();
}
void InputPlainText(string &text)
{
    int choosen;
    cout << "Choose one option"
          << "\n"
          << "1.From KeyBoard\n"
          << "2.From File\n"
          << "Please enter a number (1-2):";
    cin >> choosen;
    cin.ignore();
    switch (choosen)
    {
        case 1:
        {
            cout << "Enter Plaintext\n:";
            cin.ignore();
            getline(cin, text);
            break;
        }
        case 2:
        {
            string filename;
            cout << "Enter FileName: ";
            cin >> filename;
            text = GetString(filename);
        }
    default:
        break;
    }
}
void InputCipherText(string &text)
{
    int choosen;
    cout << "Choose one option"
          << "\n"
          << "1.From KeyBoard\n"
          << "2.From File\n"
          << "Please enter a number (1-2):";
    cin >> choosen;
    cin.ignore();
    switch (choosen)
    {
        case 1:
        {
            cout << "Enter Ciphertext\n:";
            cin.ignore();
            getline(cin, text);
            break;
        }
        case 2:
        {
            string filename;
            cout << "Enter FileName: ";
            cin >> filename;
            text = GetString(filename);
        }
    default:
        break;
    }
}
void Output(int &data)
{
    int Choosen;
    cout<< "How do you want to display output:\n"
        << "1.Display in screen\n"
        << "2.Write on file\n"
        << "Enter the option: ";
    cin >> Choosen;
    data = Choosen;
    return ;

}
void OutputFile(string text)
{
    string FileName;
    cout << "Enter FileName:";
    cin.ignore();
    cin >> FileName;
    StringSource(text,true,new FileSink(FileName.data()));
}
void OutputCipher(string cipher,int Show)
{
    switch(Show)
    {
        case 1:
        {
            cout<<"Ciphertext:" << cipher << endl;
            return ;
        }
        case 2:
        {
            OutputFile(cipher);
            return;
        }
    }
}
void OutputPlain(string cipher,int Show)
{
    switch(Show)
    {
        case 1:
        {
            cout<<"Plaintext:" << cipher << endl;
            return ;
        }
        case 2:
        {
            OutputFile(cipher);
            return;
        }
    }
}
int main()
{
#ifdef _WIN32
SetConsoleOutputCP(CP_UTF8);
SetConsoleCP(CP_UTF8);
#endif
   
    while (true)
    {
        int mode;
        cout << "Choose your mode:\n"
              << "1.ECB" << "\n"
              << "2.CBC" << "\n"
              << "3.OFB" << "\n"
              << "4.CFB" << "\n"
              << "5.CTR" << "\n"
              << "6.XTS" << "\n"
              << "7.CCM" << "\n"
              << "8.GCM" << "\n";
        cin >> mode;
        int choosen;
        cout << "Choose one option: " << "\n"
              << "1. Gen Key and Iv ;" << "\n"
              << "2. Encrypt;" << "\n"
              << "3. Decrypt;" << "\n"
              << "Enter the option:" << "\n";
        cin >> choosen;
        switch (choosen)
        {
            case 1:
            {
                int Type;
                cout << "How do you want to gen key:\n"
                    << "1.Random" << "\n"
                    << "2.Input from screen" << "\n"
                    << "3.Input from file" << "\n"
                    << "Enter the option:";
                cin >> Type;
                switch(Type)
                {
                    case 1:
                    {
                        KeyIVGen(mode);
                        break;
                    }
                    case 2:
                    {
                        KeyIVScreen(mode);
                        break;
                    }
                    case 3:
                    {
                        KeyIVFile(mode);
                        break;
                    }
                    default:
                        cout<<"het cuu";
                        break;
                }
                break;
            }
            case 2:
            {
                string cipher;
                string plaintext;
                int Show;
                InputPlainText(plaintext);
                Output(Show);
                switch(mode)
                {
                    case 1:
                    {
                        auto BeginTime = std::chrono::high_resolution_clock::now();
                        for (int i = 1; i <=1000; i++) cipher=EncryECB(plaintext); 
                        auto EndTime = std::chrono::high_resolution_clock::now();
                        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(EndTime - BeginTime).count();
                        double averageTime = static_cast<double>(duration) / 1000.0;
                        cout << "Time: " << averageTime << " ms" << std::endl;
                        string encoded;
                        StringSource(cipher, true, new HexEncoder(new StringSink(encoded)));
                        OutputCipher(encoded, Show);
                        break;
                    }
                    case 2:
                    {
                    
                        auto BeginTime = std::chrono::high_resolution_clock::now();
                        for (int i = 1; i <=1000; i++)cipher=EncryCBC(plaintext);
                        auto EndTime = std::chrono::high_resolution_clock::now();
                        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(EndTime - BeginTime).count();
                        double averageTime = static_cast<double>(duration) / 1000.0;
                        cout << "Time: " << averageTime << " ms" << std::endl;
                        string encoded;
                        StringSource(cipher, true, new HexEncoder(new StringSink(encoded)));
                        OutputCipher(encoded, Show);
                        break;
                    }
                    case 3:
                    {
                        auto BeginTime = std::chrono::high_resolution_clock::now();
                        for (int i = 1; i <=1000; i++) cipher=EncryOFB(plaintext); 
                        auto EndTime = std::chrono::high_resolution_clock::now();
                        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(EndTime - BeginTime).count();
                        double averageTime = static_cast<double>(duration) / 1000.0;
                        cout << "Time: " << averageTime << " ms" << std::endl;
                        string encoded;
                        StringSource(cipher, true, new HexEncoder(new StringSink(encoded)));
                        OutputCipher(encoded, Show);
                        break;
                    }
                    case 4:
                    {
                        auto BeginTime = std::chrono::high_resolution_clock::now();
                        for (int i = 1; i <=1000; i++) cipher=EncryCFB(plaintext); 
                        auto EndTime = std::chrono::high_resolution_clock::now();
                        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(EndTime - BeginTime).count();
                        double averageTime = static_cast<double>(duration) / 1000.0;
                        cout << "Time: " << averageTime << " ms" << std::endl;
                        string encoded;
                        StringSource(cipher, true, new HexEncoder(new StringSink(encoded)));
                        OutputCipher(encoded, Show);
                        break;
                    }
                    case 5:
                    {
                        auto BeginTime = std::chrono::high_resolution_clock::now();
                        for (int i = 1; i <=1000; i++) cipher=EncryCTR(plaintext); 
                        auto EndTime = std::chrono::high_resolution_clock::now();
                        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(EndTime - BeginTime).count();
                        double averageTime = static_cast<double>(duration) / 1000.0;
                        cout << "Time: " << averageTime << " ms" << std::endl;
                        string encoded;
                        StringSource(cipher, true, new HexEncoder(new StringSink(encoded)));
                        OutputCipher(encoded, Show);
                        break;
                    }
                    case 6:
                    {
                        auto BeginTime = std::chrono::high_resolution_clock::now();
                        for (int i = 1; i <=1000; i++) cipher=EncryXTS(plaintext); 
                        auto EndTime = std::chrono::high_resolution_clock::now();
                        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(EndTime - BeginTime).count();
                        double averageTime = static_cast<double>(duration) / 1000.0;
                        cout << "Time: " << averageTime << " ms" << std::endl;
                        string encoded;
                        StringSource(cipher, true, new HexEncoder(new StringSink(encoded)));
                        OutputCipher(encoded, Show);
                        break;
                    }
                    case 7:
                    {
                        auto BeginTime = std::chrono::high_resolution_clock::now();
                        for (int i = 1; i <=1000; i++) cipher=EncryCCM(plaintext); 
                        auto EndTime = std::chrono::high_resolution_clock::now();
                        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(EndTime - BeginTime).count();
                        double averageTime = static_cast<double>(duration) / 1000.0;
                        cout << "Time: " << averageTime << " ms" << std::endl;
                        string encoded;
                        StringSource(cipher, true, new HexEncoder(new StringSink(encoded)));
                        OutputCipher(encoded, Show);
                        break;
                    }
                    case 8:
                    {
                        auto BeginTime = std::chrono::high_resolution_clock::now();
                        for (int i = 1; i <=1000; i++) cipher=EncryGCM(plaintext); 
                        auto EndTime = std::chrono::high_resolution_clock::now();
                        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(EndTime - BeginTime).count();
                        double averageTime = static_cast<double>(duration) / 1000.0;
                        cout << "Time: " << averageTime << " ms" << std::endl;
                        string encoded;
                        StringSource(cipher, true, new HexEncoder(new StringSink(encoded)));
                        OutputCipher(encoded, Show);
                        break;   
                    }
                }
                break;
            
            }
            case 3:
            {
                string cipher;
                string plain;
                int Show;
                InputCipherText(cipher);
                Output(Show);
                switch(mode)
                {
                    case 1:
                    {
                        string decoded;
                        StringSource(cipher, true, new HexDecoder(new StringSink(decoded)));
                        auto BeginTime = std::chrono::high_resolution_clock::now();
                        for (int i = 1; i <=1000; i++) plain=DecrypECB(decoded); 
                        auto EndTime = std::chrono::high_resolution_clock::now();
                        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(EndTime - BeginTime).count();
                        double averageTime = static_cast<double>(duration) / 1000.0;
                        cout << "Time: " << averageTime << " ms" << std::endl;
                        OutputPlain(plain,Show);
                        break;
                    }
                    case 2:
                    {
                        string decoded;
                        StringSource(cipher, true, new HexDecoder(new StringSink(decoded)));
                        auto BeginTime = std::chrono::high_resolution_clock::now();
                        for (int i = 1; i <=1000; i++) plain=DecrypCBC(decoded); 
                        auto EndTime = std::chrono::high_resolution_clock::now();
                        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(EndTime - BeginTime).count();
                        double averageTime = static_cast<double>(duration) / 1000.0;
                        cout << "Time: " << averageTime << " ms" << std::endl;
                        OutputPlain(plain,Show);
                        break;
                    }
                    case 3:
                    {
                        string decoded;
                        StringSource(cipher, true, new HexDecoder(new StringSink(decoded)));
                        auto BeginTime = std::chrono::high_resolution_clock::now();
                        for (int i = 1; i <=1000; i++) plain=DecrypOFB(decoded); 
                        auto EndTime = std::chrono::high_resolution_clock::now();
                        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(EndTime - BeginTime).count();
                        double averageTime = static_cast<double>(duration) / 1000.0;
                        cout << "Time: " << averageTime << " ms" << std::endl;
                        OutputPlain(plain,Show);
                        break;
                    }
                    case 4:
                    {
                        string decoded;
                        StringSource(cipher, true, new HexDecoder(new StringSink(decoded)));
                        auto BeginTime = std::chrono::high_resolution_clock::now();
                        for (int i = 1; i <=1000; i++) plain=DecrypCFB(decoded); 
                        auto EndTime = std::chrono::high_resolution_clock::now();
                        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(EndTime - BeginTime).count();
                        double averageTime = static_cast<double>(duration) / 1000.0;
                        cout << "Time: " << averageTime << " ms" << std::endl;
                        OutputPlain(plain,Show);
                        break;
                    }
                    case 5:
                    {
                        string decoded;
                        StringSource(cipher, true, new HexDecoder(new StringSink(decoded)));
                        auto BeginTime = std::chrono::high_resolution_clock::now();
                        for (int i = 1; i <=1000; i++) plain=DecrypCTR(decoded); 
                        auto EndTime = std::chrono::high_resolution_clock::now();
                        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(EndTime - BeginTime).count();
                        double averageTime = static_cast<double>(duration) / 1000.0;
                        cout << "Time: " << averageTime << " ms" << std::endl;
                        OutputPlain(plain,Show);
                        break;
                    }
                    case 6:
                    {
                        string decoded;
                        StringSource(cipher, true, new HexDecoder(new StringSink(decoded)));
                        auto BeginTime = std::chrono::high_resolution_clock::now();
                        for (int i = 1; i <=1000; i++) plain=DecrypXTS(decoded); 
                        auto EndTime = std::chrono::high_resolution_clock::now();
                        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(EndTime - BeginTime).count();
                        double averageTime = static_cast<double>(duration) / 1000.0;
                        cout << "Time: " << averageTime << " ms" << std::endl;
                        OutputPlain(plain,Show);
                        break;
                    }
                    case 7:
                    {
                        string decoded;
                        StringSource(cipher, true, new HexDecoder(new StringSink(decoded)));
                        auto BeginTime = std::chrono::high_resolution_clock::now();
                        for (int i = 1; i <=1000; i++) plain=DecrypCCM(decoded); 
                        auto EndTime = std::chrono::high_resolution_clock::now();
                        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(EndTime - BeginTime).count();
                        double averageTime = static_cast<double>(duration) / 1000.0;
                        cout << "Time: " << averageTime << " ms" << std::endl;
                        OutputPlain(plain,Show);
                        break;
                    }
                    case 8:
                    {
                        string decoded;
                        StringSource(cipher, true, new HexDecoder(new StringSink(decoded)));
                        auto BeginTime = std::chrono::high_resolution_clock::now();
                        for (int i = 1; i <=1000; i++) plain=DecrypGCM(decoded); 
                        auto EndTime = std::chrono::high_resolution_clock::now();
                        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(EndTime - BeginTime).count();
                        double averageTime = static_cast<double>(duration) / 1000.0;
                        cout << "Time: " << averageTime << " ms" << std::endl;
                        OutputPlain(plain,Show);
                        break;   
                    }
                    default:
                        break;
                }
                break;
            }
            default :
                break;
        }
    }
}