#ifndef Decryption_H
#define Decryption_H
#include "Encryption.h"

string DecrypECB(string cipher)
{
    ECB_Mode<AES>::Decryption d;
    d.SetKey(key, AES::DEFAULT_KEYLENGTH);
    string recovered;
    StringSource(cipher, true,
        new StreamTransformationFilter(d, new StringSink(recovered)));

    return recovered;
}
string DecrypCBC(string cipher)
{
    CBC_Mode<AES>::Decryption d;
    d.SetKeyWithIV(key, AES::DEFAULT_KEYLENGTH, iv);
    string recovered;
    StringSource(cipher, true,
        new StreamTransformationFilter(d, new StringSink(recovered)));

    return recovered;
}
string DecrypOFB(string cipher)
{
    OFB_Mode<AES>::Decryption d;
    d.SetKeyWithIV(key, AES::DEFAULT_KEYLENGTH, iv);
    string recovered;
    StringSource(cipher, true,
        new StreamTransformationFilter(d, new StringSink(recovered)));

    return recovered;
}


string DecrypCFB(string cipher)
{
    CFB_Mode<AES>::Decryption d;
    d.SetKeyWithIV(key, AES::DEFAULT_KEYLENGTH, iv);
    string recovered;
    StringSource(cipher, true,
        new StreamTransformationFilter(d, new StringSink(recovered)));

    return recovered;
}

string DecrypCTR(string cipher)
{
    CTR_Mode<AES>::Decryption d;
    d.SetKeyWithIV(key, AES::DEFAULT_KEYLENGTH, iv);
    string recovered;
    StringSource(cipher, true,
        new StreamTransformationFilter(d, new StringSink(recovered)));

    return recovered;
}

string DecrypXTS(string cipher)
{
    string recovered;
    // StringSource(cipher, true, new HexDecoder(new StringSink(recovered)));
    CryptoPP::byte newIV[AES::BLOCKSIZE];
    for (int i = 0; i < AES::BLOCKSIZE; i++)
    {
        newIV[i] = iv[i];
    }
    XTS_Mode<AES>::Decryption d;
    d.SetKeyWithIV(key, sizeof(key), newIV);
    StringSource s(cipher, true,
                   new StreamTransformationFilter(d,
                                                  new StringSink(recovered)));
    return recovered;
}
string DecrypCCM(string cipher) {
  string recovered;
  CryptoPP::byte newIV[AES::BLOCKSIZE];
  for (int i = 0; i < AES::BLOCKSIZE; i++) {
    newIV[i] = iv[i];
  }

  CCM<AES, 8>::Decryption d;
  d.SetKeyWithIV(key, sizeof(key), newIV);
  d.SpecifyDataLengths(0, cipher.size() - 8, 0);

  AuthenticatedDecryptionFilter df(d,
                                   new StringSink(recovered));
  StringSource s(cipher, true,
                 new Redirector(df));
  return recovered;
}
string DecrypGCM(string cipher)
{
    string recovered;
    GCM<AES>::Decryption d;
    d.SetKeyWithIV(key, sizeof(key), iv, sizeof(iv));
    StringSource s(cipher, true,
                   new AuthenticatedDecryptionFilter(d,
                                                     new StringSink(recovered)));
    return recovered;
}
#endif