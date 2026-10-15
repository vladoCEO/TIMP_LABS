#pragma once
#include <vector>
#include <string>
#include <map>
#include <stdexcept>

class cipher_error : public std::invalid_argument {
public:
    explicit cipher_error(const std::string& what_arg)
        : std::invalid_argument(what_arg) {}
    explicit cipher_error(const char* what_arg)
        : std::invalid_argument(what_arg) {}
};

class modAlphaCipher
{
private:
    // Русский алфавит в верхнем регистре (33 буквы)
    std::wstring numAlpha = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
    std::map<wchar_t, int> alphaNum;   // ассоциативный массив "номер по символу"
    std::vector<int> key;              // ключ в числовом виде

    std::vector<int> convert(const std::wstring& s);      // строка → вектор
    std::wstring     convert(const std::vector<int>& v);  // вектор → строка

    std::wstring getValidKey(const std::wstring& s);         // валидация ключа
    std::wstring getValidOpenText(const std::wstring& s);    // валидация открытого текста
    std::wstring getValidCipherText(const std::wstring& s);  // валидация шифротекста

public:
    modAlphaCipher() = delete;
    explicit modAlphaCipher(const std::wstring& skey);

    std::wstring encrypt(const std::wstring& open_text);
    std::wstring decrypt(const std::wstring& cipher_text);
};