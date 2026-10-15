#pragma once
#include <string>
#include <stdexcept>


class cipher_error : public std::invalid_argument {
public:
    explicit cipher_error(const std::string& what_arg)
        : std::invalid_argument(what_arg) {}
    explicit cipher_error(const char* what_arg)
        : std::invalid_argument(what_arg) {}
};

class tableCipher
{
private:
    int key;   // ключ = количество столбцов таблицы

    int          getValidKey(const std::wstring& skey);
    std::wstring getValidOpenText(const std::wstring& s);
    std::wstring getValidCipherText(const std::wstring& s);

public:
    tableCipher() = delete;
    explicit tableCipher(const std::wstring& skey);

    std::wstring encrypt(const std::wstring& open_text);
    std::wstring decrypt(const std::wstring& cipher_text);
};