#include "modeBetaCipher.h"
#include <vector>
#include <stdexcept>

using namespace std;

modeBetaCipher::modeBetaCipher(unsigned key) {
    if (key < 2) {
        throw invalid_argument("Ключ должен быть >= 2");
    }
    cols = key;
}

// Шифрование
wstring modeBetaCipher::encrypt(const wstring& text) {
    unsigned n = text.size();
    unsigned rows = (n + cols - 1) / cols;
    vector<vector<wchar_t>> table(rows, vector<wchar_t>(cols, L'_'));

    // Заполнение таблицы по строкам слева направо
    unsigned k = 0;
    for (unsigned r = 0; r < rows; r++) {
        for (unsigned c = 0; c < cols; c++) {
            if (k < n) table[r][c] = text[k++];
        }
    }

    // Чтение таблицы сверху вниз, справа налево
    wstring result;
    for (int c = cols - 1; c >= 0; c--) {
        for (unsigned r = 0; r < rows; r++) {
            if (table[r][c] != L'_') result.push_back(table[r][c]);
        }
    }
    return result;
}

// Дешифрование
wstring modeBetaCipher::decrypt(const wstring& text) {
    unsigned n = text.size();
    unsigned rows = (n + cols - 1) / cols;
    unsigned fullCols = n % cols; // сколько ячеек занято в последней строке

    vector<unsigned> colHeights(cols, rows);
    if (fullCols != 0) {
        for (unsigned c = 0; c < cols - fullCols; c++) {
            colHeights[cols - 1 - c]--; // правые столбцы короче на одну ячейку
        }
    }

    vector<vector<wchar_t>> table(rows, vector<wchar_t>(cols, L'_'));

    // Заполнение таблицы по маршруту сверху вниз, справа налево
    unsigned k = 0;
    for (int c = cols - 1; c >= 0; c--) {
        for (unsigned r = 0; r < colHeights[c]; r++) {
            table[r][c] = text[k++];
        }
    }

    // Чтение таблицы по строкам слева направо
    wstring result;
    for (unsigned r = 0; r < rows; r++) {
        for (unsigned c = 0; c < cols; c++) {
            if (table[r][c] != L'_') result.push_back(table[r][c]);
        }
    }
    return result;
}
