#include <iostream>
#include <locale>
#include <stdexcept>
#include "modeAlphaCipher.h"

using namespace std;

// Настройка локали: сначала русская, затем запасные варианты
// (если ru_RU.UTF-8 не сгенерирована в системе, locale() бросает исключение)
static void setupLocale() {
    const char* names[] = {"ru_RU.UTF-8", "C.UTF-8", ""};
    for (auto name : names) {
        try {
            locale::global(locale(name));
            break;
        } catch (const runtime_error&) {
        }
    }
    wcout.imbue(locale());
    wcin.imbue(locale());
}

// проверка, чтобы строка состояла только из русских прописных букв
bool isValid(const wstring& s) {
    for (auto c : s) {
        if (c < L'А' || c > L'Я')
            return false;
    }
    return true;
}

int main(int argc, char **argv) {
    setupLocale();

    wstring key;
    wstring text;
    unsigned op;

    wcout << L"Шифр готов. Введите ключ: ";
    wcin >> key;
    if (key.empty() || !isValid(key)) {
        wcerr << L"Ошибка: ключ недопустим\n";
        return 1;
    }
    wcout << L"Ключ принят\n";

    modAlphaCipher cipher(key);

    do {
        wcout << L"\nВыберите действие (0 - выход, 1 - зашифровать, 2 - расшифровать): ";
        if (!(wcin >> op)) break;   // конец ввода или не число
        if (op > 2) {
            wcout << L"Ошибка: недопустимая операция\n";
        } else if (op > 0) {
            wcout << L"Введите текст: ";
            wcin >> text;
            if (isValid(text)) {
                if (op == 1) {
                    wcout << L"Зашифрованный текст: " << cipher.encrypt(text) << endl;
                } else {
                    wcout << L"Расшифрованный текст: " << cipher.decrypt(text) << endl;
                }
            } else {
                wcout << L"Операция прервана: введённый текст содержит недопустимые символы\n";
            }
        }
    } while (op != 0);

    return 0;
}
