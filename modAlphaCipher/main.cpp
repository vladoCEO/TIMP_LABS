#include <iostream>
#include <locale>
#include <string>
#include "modAlphaCipher.h"
using namespace std;

void check(const wstring& Text, const wstring& key, const bool destructCipherText = false)
{
    try {
        wstring cipherText;
        wstring decryptedText;
        modAlphaCipher cipher(key);

        cipherText = cipher.encrypt(Text);
        if (destructCipherText)                                   // «портим» шифротекст
            cipherText.front() = towlower(cipherText.front());
        decryptedText = cipher.decrypt(cipherText);

        wcout << L"key=" << key << endl;
        wcout << Text << endl;
        wcout << cipherText << endl;
        wcout << decryptedText << endl;

        if (Text == decryptedText)
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
    check(L"МОРДОБРЕЙВОЛОС", L"БРИТВА");
    check(L"КОЖУРАБАНАНА",    L"ФРУКТ");
    check(L"ШКОЛЬНЫЙАВТОБУС", L"КАЛЫМАГА");

    // --- Валидация ключа ---
    check(L"МОРДОБРЕЙВОЛОС", L"бритва");       // строчные → автоматически к прописным, Ok
    check(L"МОРДОБРЕЙВОЛОС", L"");             // пустой ключ → исключение
    check(L"МОРДОБРЕЙВОЛОС", L"БРИТВА123");    // цифры в ключе → исключение

    // --- Валидация открытого текста ---
    check(L"Мордобрей волос!!!", L"БРИТВА");   // пробелы и знаки удалятся, регистр приведётся
    check(L"123", L"БРИТВА");                  // после очистки пусто → исключение

    // --- Валидация шифротекста ---
    check(L"МОРДОБРЕЙВОЛОС", L"БРИТВА", true); // «испорченный» шифротекст → исключение

    return 0;
}