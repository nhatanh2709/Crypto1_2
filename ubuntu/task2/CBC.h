#ifndef CBC_H
#define CBC_H
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include "AES.h"
using namespace std;
std::vector<uint8_t> string_to_int(string s)
{
    vector<uint8_t> ans;
    for (auto value : s)
        ans.push_back(static_cast<uint8_t>(value));
    return ans;
}
std::string int_to_hex(const std::vector<uint8_t> &data)
{
    std::stringstream ss;
    for (const auto &byte : data)
    {
        ss << std::hex << std::setw(2) << std::setfill('0') << (byte & 0xff);
    }
    return ss.str();
}
std::string string_from_hex(const std::string &s)
{
    std::string bytes;
    for (unsigned int i = 0; i < s.length(); i += 2)
    {
        std::string byteString = s.substr(i, 2);
        char byte = (char)strtol(byteString.c_str(), NULL, 16);
        bytes.push_back(byte);
    } 
    if (bytes.size() % 16)
    {
        int sz = bytes.size() % 16;
        int res = 16 - sz;
        for (int i = 0; i < res; ++i)
        {
            bytes.push_back(static_cast<char>(res));
        }
    }

    return bytes;
}
wstring string_to_wstring(const string &str)
{
    wstring_convert<codecvt_utf8<wchar_t>> towstring;
    return towstring.from_bytes(str);
}

string wstring_to_string(const wstring &str)
{
    wstring_convert<codecvt_utf8<wchar_t>> tostring;
    return tostring.to_bytes(str);
}
class CBC
{
public:
     std::string Padding(const std::string &data)
    {
        std::string ans;
        for (auto c : data)
            ans.push_back(c);
        int pad_len = 16 - (ans.size() % 16);
        for (int i = 0; i <= pad_len - 1; i++)
            ans.push_back(static_cast<char>(pad_len));
        return ans;
    }
    std::string Unpadding(std::string data)
    {
        int sz = data.back();
        data.erase(data.end() - sz, data.end());
        return data;
    }

    std::string cbc_encrypt(std::string plaintext, std::string key, std::string iv)
    {
        AES aes;
        std::string padded_data = Padding(plaintext);
        std::vector<std::vector<uint8_t>> encrypted_blocks;

        std::vector<uint8_t> previous_block = string_to_int(iv);
        for (std::string::size_type i = 0; i < padded_data.size(); i += 16)
        {
            std::string block = padded_data.substr(i, 16);
            for (int j = 0; j < 16; ++j)
            {
                block[j] ^= previous_block[j];
            }
            std::vector<uint8_t> encrypted_block = aes.encrypt(std::vector<uint8_t>(block.begin(), block.end()), key);
            encrypted_blocks.push_back(encrypted_block);
            previous_block = encrypted_block;
        }

        std::vector<uint8_t> result = string_to_int(iv);
        for (auto &block : encrypted_blocks)
        {
            result.insert(result.end(), block.begin(), block.end());
        }
        return int_to_hex(result);
    }
    std::string cbc_decrypt(std::string ciphertext_hex, std::string key, std::string iv)
    {
        AES aes;
        std::string ciphertext = string_from_hex(ciphertext_hex);
        if (ciphertext.size() % 16 != 0)
        {
            throw std::invalid_argument("Ciphertext length must be a multiple of 16 bytes for CBC mode.");
        }
        iv = std::string(ciphertext.begin(), ciphertext.begin() + 16);
        ciphertext.erase(ciphertext.begin(), ciphertext.begin() + 16);

        std::string decrypted_blocks;
        std::vector<unsigned char> previous_block(iv.begin(), iv.end());

        for (size_t i = 0; i < ciphertext.size(); i += 16)
        {
            std::vector<unsigned char> block(ciphertext.begin() + i, ciphertext.begin() + i + 16);
            std::vector<unsigned char> decrypted_block = aes.decrypt(block, key);
            for (size_t j = 0; j < 16; ++j)
            {
                decrypted_block[j] ^= previous_block[j];
            }

            decrypted_blocks += std::string(decrypted_block.begin(), decrypted_block.end());
            previous_block = block;
        }

        std::string decrypted_data = Unpadding(decrypted_blocks);
        return decrypted_data;
    }
};

#endif