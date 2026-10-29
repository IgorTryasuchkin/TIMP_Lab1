#pragma once
#include <string>
#include <vector>

class modeBetaCipher {
private:
    unsigned cols; // количество столбцов таблицы (ключ)
public:
    modeBetaCipher(unsigned key);                    // конструктор
    std::wstring encrypt(const std::wstring& text);  // шифрование
    std::wstring decrypt(const std::wstring& text);  // расшифровка
};
