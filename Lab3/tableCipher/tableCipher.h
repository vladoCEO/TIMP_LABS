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
    std::string key;   // Ключ = строка (её длина задает число столбцов)

    std::string  getValidKey(const std::string& s);
    std::string  getValidOpenText(const std::string& s);
    std::string  getValidCipherText(const std::string& s);

public:
    tableCipher() = delete;
    explicit tableCipher(const std::string& skey);

    std::string encrypt(const std::string& open_text);
    std::string decrypt(const std::string& cipher_text);
};
