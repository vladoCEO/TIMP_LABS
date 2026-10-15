#include "tableCipher.h"
#include <cwctype>   

// Заполнитель для неполных строк таблицы
static const wchar_t PAD = L'Я';

// ===== Конструктор =====
tableCipher::tableCipher(const std::wstring& skey)
{
    key = getValidKey(skey);
}

// Ключ — строка только из цифр, преобразуется в целое.
// Проверки: не пустой; только цифры; значение >= 2.
int tableCipher::getValidKey(const std::wstring& skey)
{
    if (skey.empty())
        throw cipher_error("Empty key");

    for (auto c : skey) {
        if (!iswdigit(c))
            throw cipher_error("Invalid key");
    }

    int k = std::stoi(skey);
    if (k < 2)
        throw cipher_error("Key too small");
    return k;
}

// Удаляет всё, кроме букв (без исключения).
// Строчные буквы переводит в прописные.
// Если после очистки строка пуста → исключение.
std::wstring tableCipher::getValidOpenText(const std::wstring& s)
{
    std::wstring tmp;
    for (auto c : s) {
        if (iswalpha(c)) {
            if (iswlower(c))
                tmp.push_back(static_cast<wchar_t>(towupper(c)));
            else
                tmp.push_back(c);
        }
    }
    if (tmp.empty())
        throw cipher_error("Empty open text");
    return tmp;
}

// Пустая строка → исключение.
// Любой символ не в верхнем регистре → исключение.
std::wstring tableCipher::getValidCipherText(const std::wstring& s)
{
    if (s.empty())
        throw cipher_error("Empty cipher text");
    for (auto c : s) {
        if (!iswupper(c))
            throw cipher_error("Invalid cipher text");
    }
    return s;
}

// ===== Зашифрование =====
std::wstring tableCipher::encrypt(const std::wstring& open_text)
{
    std::wstring text = getValidOpenText(open_text);

    int n    = static_cast<int>(text.size());
    int rows = (n + key - 1) / key;

    std::wstring table(rows * key, PAD);
    for (int i = 0; i < n; ++i)
        table[i] = text[i];

    std::wstring result;
    result.reserve(rows * key);
    for (int col = key - 1; col >= 0; --col)
        for (int row = 0; row < rows; ++row)
            result.push_back(table[row * key + col]);

    return result;
}

// ===== Расшифрование =====
std::wstring tableCipher::decrypt(const std::wstring& cipher_text)
{
    std::wstring text = getValidCipherText(cipher_text);

    int n = static_cast<int>(text.size());
    if (n % key != 0)
        throw cipher_error("Invalid cipher text length");
    int rows = n / key;

    std::wstring table(n, PAD);
    int idx = 0;
    for (int col = key - 1; col >= 0; --col)
        for (int row = 0; row < rows; ++row)
            table[row * key + col] = text[idx++];

    std::wstring result;
    result.reserve(n);
    for (int i = 0; i < n; ++i)
        result.push_back(table[i]);

    return result;
}