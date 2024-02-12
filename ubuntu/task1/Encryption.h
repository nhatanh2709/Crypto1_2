#ifndef Encryption_H
#define Encryption_H
#include "library.h"
CryptoPP::byte key[AES::MAX_KEYLENGTH];
CryptoPP::byte iv[AES::MAX_KEYLENGTH];
wstring string_to_wstring(const string& str) {
    wstring_convert<codecvt_utf8<wchar_t>> towstring;
    return towstring.from_bytes(str);
}

string wstring_to_string(const wstring& str) {
    wstring_convert<codecvt_utf8<wchar_t>> tostring;
    return tostring.to_bytes(str);
}


string EncryECB(string plain)
{
    string cipher,encoded;
    ECB_Mode<AES>::Encryption e;
    e.SetKey(key, AES::DEFAULT_KEYLENGTH);
    StringSource(plain, true, new StreamTransformationFilter(e, new StringSink(cipher)));
    return cipher;;
}

string EncryCBC(string plain)
{
    string cipher,encoded;
    CBC_Mode<AES>::Encryption e;
    e.SetKeyWithIV(key, AES::DEFAULT_KEYLENGTH, iv);
    StringSource (plain, true,new StreamTransformationFilter(e,new StringSink(cipher))) ;
    return cipher;
}

string EncryOFB(string plain)
{
    string cipher,encoded;
    OFB_Mode<AES>::Encryption e;
    e.SetKeyWithIV(key, AES::DEFAULT_KEYLENGTH, iv);
    StringSource (plain, true,new StreamTransformationFilter(e,new StringSink(cipher))) ;
    return cipher;
}

string EncryCFB(string plain)
{
    string cipher,encoded;
    CFB_Mode<AES>::Encryption e;
    e.SetKeyWithIV(key, AES::DEFAULT_KEYLENGTH, iv);
    StringSource (plain, true,new StreamTransformationFilter(e,new StringSink(cipher))) ;
    return cipher;
}
string EncryCTR(string plain)
{
    string cipher,encoded;
    CTR_Mode<AES>::Encryption e;
    e.SetKeyWithIV(key, AES::DEFAULT_KEYLENGTH, iv);
    StringSource (plain, true,new StreamTransformationFilter(e,new StringSink(cipher))) ;
    return cipher;
}

string EncryXTS(string plain)
{
    CryptoPP::byte newIV[AES::BLOCKSIZE];
    string cipher, encoded;
    for (int i = 0; i < AES::BLOCKSIZE; i++)
    {
        newIV[i] = iv[i];
    }
    XTS_Mode<AES>::Encryption e;
    e.SetKeyWithIV(key, sizeof(key), newIV);
    StringSource s(plain, true,
                   new StreamTransformationFilter(e,
                                                  new StringSink(cipher)));

    return cipher;
}
string EncryCCM(string plain) {
  CryptoPP::byte newIV[AES::BLOCKSIZE];
  string cipher, encoded;
  for (int i = 0; i < AES::BLOCKSIZE; i++) {
    newIV[i] = iv[i];
  }

  CCM<AES, 8>::Encryption e;
  e.SetKeyWithIV(key, size(key), newIV);
  e.SpecifyDataLengths(0, plain.size(), 0);

  StringSource s(plain, true,
                 new AuthenticatedEncryptionFilter(e,
                                                  new StringSink(cipher)));

  return cipher;
}

string EncryGCM(string plain)
{
    string cipher;
    GCM< AES >::Encryption e;
		e.SetKeyWithIV(key, sizeof(key), iv, sizeof(iv));
		StringSource s(plain, true, 
			new AuthenticatedEncryptionFilter(e,
				new StringSink(cipher)
			)    
		); 
	return cipher;
}
#endif