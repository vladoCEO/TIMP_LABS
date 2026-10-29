#include <iostream>
#include <locale>
#include <string>
#include "tableCipher.h"
using namespace std;

void check(const wstring& Text, const wstring& key, const bool destructCipherText = false)
{
    try {
        wstring cipherText;
        wstring decryptedText;
        tableCipher cipher(key);

        cipherText = cipher.encrypt(Text);
        if (destructCipherText)
            cipherText.front() = towlower(cipherText.front());
        decryptedText = cipher.decrypt(cipherText);

        wcout << L"key=" << key << endl;
        wcout << L"Text    : " << Text << endl;
        wcout << L"Cipher  : " << cipherText << endl;
        wcout << L"Decrypt : " << decryptedText << endl;

        if (decryptedText.compare(0, Text.size(), Text) == 0)
            wcout << L"Ok\n";
        else
            wcout << L"Err\n";
    }
    catch (const cipher_error& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

int main(int argc, char** argv)
{
    setlocale(LC_ALL, "ru_RU.UTF-8");

    // --- Корректная работа ---
    check(L"ПРИВЕТКАКДЕЛА", L"4");
    check(L"ПРИВЕТКАКДЕЛА", L"3");
    check(L"ПРИВЕТКАКДЕЛА", L"7");

    // --- Валидация ключа ---
    check(L"ПРИВЕТКАКДЕЛА", L"");       // Empty key
    check(L"ПРИВЕТКАКДЕЛА", L"1");      // Key small
    check(L"ПРИВЕТКАКДЕЛА", L"abc");    // Invalid key

    // --- Валидация открытого текста ---
    check(L"Привет, как дела!!!", L"4");
    check(L"12345", L"4");              // Empty open text

    // --- Валидация шифротекста ---
    check(L"ПРИВЕТКАКДЕЛА", L"4", true); // Invalid cipher text

    return 0;
}