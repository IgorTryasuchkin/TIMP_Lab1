#include <iostream>
#include <locale>
#include <limits>
#include <stdexcept>
#include "modeBetaCipher.h"

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

// проверка: строка должна содержать только заглавные русские буквы
bool isValid(const wstring& s) {
    for (auto c : s) {
        if (c < L'А' || c > L'Я') // можно добавить L'Ё' при необходимости
            return false;
    }
    return true;
}

int main() {
    setupLocale();

    unsigned key;
    wstring text;
    unsigned op;

    wcout << L"Шифр маршрутной перестановки\n";
    wcout << L"Введите ключ (количество столбцов, >=2): ";
    if (!(wcin >> key) || key < 2) {
        wcerr << L"Ошибка: ключ должен быть >= 2\n";
        return 1;
    }
    wcout << L"Ключ принят\n";

    modeBetaCipher cipher(key);

    do {
        wcout << L"\nВыберите операцию (0 - выход, 1 - шифрование, 2 - дешифрование): ";
        if (!(wcin >> op)) break;   // конец ввода или не число
        if (op > 2) {
            wcout << L"Ошибка: недопустимая операция\n";
        } else if (op > 0) {
            // Очистка буфера после ввода числа
            wcin.ignore(numeric_limits<streamsize>::max(), L'\n');
            wcout << L"Введите текст (ЗАГЛАВНЫМИ русскими буквами без пробелов): ";
            getline(wcin, text); // читаем всю строку целиком
            if (isValid(text)) {
                if (op == 1) {
                    wcout << L"Зашифрованный текст: " << cipher.encrypt(text) << endl;
                } else {
                    wcout << L"Расшифрованный текст: " << cipher.decrypt(text) << endl;
                }
            } else {
                wcout << L"Операция прервана: некорректный текст\n";
            }
        }
    } while (op != 0);

    return 0;
}
