#pragma once
#include <string>
#include <vector>
#include <map>

class modAlphaCipher {
private:
    std::wstring numAlpha = L"АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
    std::map<wchar_t, int> alphaNum;
    std::vector<int> key;
    std::vector<int> convert(const std::wstring& s);
    std::wstring convert(const std::vector<int>& v);
public:
    modAlphaCipher(const std::wstring& skey);
    std::wstring encrypt(const std::wstring& open_text);
    std::wstring decrypt(const std::wstring& cipher_text);
};
