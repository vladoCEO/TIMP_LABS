#include "modAlphaCipher.h"
#include <cwctype>

modAlphaCipher::modAlphaCipher(const std::wstring& skey)
{
    for (unsigned i = 0; i < numAlpha.size(); ++i)
        alphaNum[numAlpha[i]] = i;

    key = convert(getValidKey(skey));

    // Проверка на вырожденный ключ
    size_t n = 0;
    for (auto e : key)
        if (e == 0)
            n++;
    if (2 * n > key.size())
        throw cipher_error("Weak key");
}

std::wstring modAlphaCipher::encrypt(const std::wstring& open_text)
{
    std::vector<int> work = convert(getValidOpenText(open_text));
    for (unsigned i = 0; i < work.size(); i++)
        work[i] = (work[i] + key[i % key.size()]) % alphaNum.size();
    return convert(work);
}

std::wstring modAlphaCipher::decrypt(const std::wstring& cipher_text)
{
    std::vector<int> work = convert(getValidCipherText(cipher_text));
    for (unsigned i = 0; i < work.size(); i++)
        work[i] = (work[i] + alphaNum.size() - key[i % key.size()]) % alphaNum.size();
    return convert(work);
}

std::vector<int> modAlphaCipher::convert(const std::wstring& s)
{
    std::vector<int> result;
    for (auto c : s)
        result.push_back(alphaNum[c]);
    return result;
}

std::wstring modAlphaCipher::convert(const std::vector<int>& v)
{
    std::wstring result;
    for (auto i : v)
        result.push_back(numAlpha[i]);
    return result;
}

// Пустой ключ, не-буква или буква не из нашего алфавита -> исключение
std::wstring modAlphaCipher::getValidKey(const std::wstring& s)
{
    if (s.empty())
        throw cipher_error("Empty key");
        
    std::wstring tmp(s);
    for (auto& c : tmp) {
        if (!iswalpha(c))
            throw cipher_error("Invalid key (not a letter)");
            
        c = towupper(c); // Делаем прописной
        
        // Проверяем, что буква есть в нашем алфавите (отсекаем латиницу)
        if (alphaNum.find(c) == alphaNum.end())
            throw cipher_error("Invalid key (not russian letter)");
    }
    return tmp;
}

// Не-буквы удаляются, строчные -> прописные
std::wstring modAlphaCipher::getValidOpenText(const std::wstring& s)
{
    std::wstring tmp;
    for (auto c : s) {
        if (iswalpha(c)) {
            wchar_t u = towupper(c);
            // Добавляем только если буква есть в нашем русском алфавите
            if (alphaNum.find(u) != alphaNum.end())
                tmp.push_back(u);
        }
    }
    if (tmp.empty())
        throw cipher_error("Empty open text");
    return tmp;
}

// Любой символ не из алфавита (включая строчные) -> исключение
std::wstring modAlphaCipher::getValidCipherText(const std::wstring& s)
{
    if (s.empty())
        throw cipher_error("Empty cipher text");
    for (auto c : s) {
        // Проверяем, что символ есть в алфавите (это автоматически отсекает строчные и знаки)
        if (alphaNum.find(c) == alphaNum.end())
            throw cipher_error("Invalid cipher text");
    }
    return s;
}