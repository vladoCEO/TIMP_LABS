#include "tableCipher.h"
#include <cctype> // Для isalpha, toupper, isupper

// Заполнитель для неполной последней строки таблицы
static const char PAD = 'X';

tableCipher::tableCipher(const std::string& skey)
{
    key = getValidKey(skey);
}

// Валидация ключа: не пустой, только буквы, длина >= 2.
std::string tableCipher::getValidKey(const std::string& s)
{
    if (s.empty()){
        throw cipher_error("Empty key");
    }
    if (s.size() < 2){
        throw cipher_error("Key too small"); // Длина ключа = число столбцов
    }
        std::string tmp(s);
    for (auto& c : tmp) {
        if (!isalpha(static_cast<unsigned char>(c)))
            throw cipher_error("Invalid key");
        c = static_cast<char>(toupper(static_cast<unsigned char>(c)));
    }
    return tmp;
}

// Удаляет не-буквы, строчные -> прописные, пусто -> исключение.
std::string tableCipher::getValidOpenText(const std::string& s)
{
    std::string tmp;
    for (char c : s) {
        if (isalpha(static_cast<unsigned char>(c))) {
            tmp.push_back(static_cast<char>(toupper(static_cast<unsigned char>(c))));
        }
    }
    if (tmp.empty())
        throw cipher_error("Empty open text");
    return tmp;
}

// Пусто или есть не-прописной символ -> исключение.
std::string tableCipher::getValidCipherText(const std::string& s)
{
    if (s.empty())
        throw cipher_error("Empty cipher text");
    for (char c : s) {
        if (!isupper(static_cast<unsigned char>(c)))
            throw cipher_error("Invalid cipher text");
    }
    return s;
}

// Запись по строкам слева направо, чтение по столбцам справа налево
std::string tableCipher::encrypt(const std::string& open_text)
{
    std::string text = getValidOpenText(open_text);
    int cols = static_cast<int>(key.size()); // Количество столбцов = длина ключа

    int n    = static_cast<int>(text.size());
    int rows = (n + cols - 1) / cols;

    std::string table(rows * cols, PAD);
    for (int i = 0; i < n; ++i)
        table[i] = text[i];

    std::string result;
    result.reserve(rows * cols);
    // Маршрут считывания: сверху вниз, справа налево
    for (int col = cols - 1; col >= 0; --col)
        for (int row = 0; row < rows; ++row)
            result.push_back(table[row * cols + col]);
    return result;
}

std::string tableCipher::decrypt(const std::string& cipher_text)
{
    std::string text = getValidCipherText(cipher_text);
    int cols = static_cast<int>(key.size());

    int n = static_cast<int>(text.size());
    if (n % cols != 0)
        throw cipher_error("Invalid cipher text length");
    int rows = n / cols;

    std::string table(n, PAD);
    int idx = 0;
    for (int col = cols - 1; col >= 0; --col)
        for (int row = 0; row < rows; ++row)
            table[row * cols + col] = text[idx++];
    return table;
}
