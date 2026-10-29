#include <UnitTest++/UnitTest++.h>
#include "modAlphaCipher.h"
#include <clocale> // Для setlocale

SUITE(KeyTest)
{
    TEST(ValidKey) { CHECK(modAlphaCipher(L"БВГ").encrypt(L"ААААА") == L"БВГБВ"); }
    TEST(LongKey) { CHECK(modAlphaCipher(L"БВГДЕ").encrypt(L"ААААА") == L"БВГДЕ"); }
    TEST(LowCaseKey) { CHECK(modAlphaCipher(L"бвг").encrypt(L"ААААА") == L"БВГБВ"); }
    TEST(DigitsInKey) { CHECK_THROW(modAlphaCipher cp(L"Б1"), cipher_error); }
    TEST(PunctuationInKey) { CHECK_THROW(modAlphaCipher cp(L"Б,В"), cipher_error); }
    TEST(WhitespaceInKey) { CHECK_THROW(modAlphaCipher cp(L"Б В"), cipher_error); }
    TEST(EmptyKey) { CHECK_THROW(modAlphaCipher cp(L""), cipher_error); }
    TEST(WeakKey) { CHECK_THROW(modAlphaCipher cp(L"ААА"), cipher_error); }
}

struct KeyB_fixture {
    modAlphaCipher * p;
    KeyB_fixture() { p = new modAlphaCipher(L"Б"); }
    ~KeyB_fixture() { delete p; }
};

SUITE(EncryptTest)
{
    TEST_FIXTURE(KeyB_fixture, UpCaseString) { 
        CHECK(p->encrypt(L"ПРИВЕТ") == L"РСЙГЁУ"); 
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) { 
        CHECK(p->encrypt(L"привет") == L"РСЙГЁУ"); 
    }
    TEST_FIXTURE(KeyB_fixture, StringWithWhitspaceAndPunct) { 
        CHECK(p->encrypt(L"ПРИ ВЕТ!!!") == L"РСЙГЁУ"); 
    }
    TEST_FIXTURE(KeyB_fixture, StringWithNumbers) { 
        CHECK(p->encrypt(L"С НОВЫМ 2026 ГОДОМ") == L"ТОПГЬНДПЕПН"); 
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) { 
        CHECK_THROW(p->encrypt(L""), cipher_error); 
    }
    TEST_FIXTURE(KeyB_fixture, NoAlphaString) { 
        CHECK_THROW(p->encrypt(L"1234+8765=9999"), cipher_error); 
    }
    TEST(MaxShiftKey) { 
        CHECK(modAlphaCipher(L"Я").encrypt(L"ПРИВЕТ") == L"ОПЗБДС"); 
    }
}

SUITE(DecryptText)
{
    TEST_FIXTURE(KeyB_fixture, UpCaseString) { 
        CHECK(p->decrypt(L"РСЙГЁУ") == L"ПРИВЕТ"); 
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) { 
        CHECK_THROW(p->decrypt(L"рсйгёу"), cipher_error); 
    }
    TEST_FIXTURE(KeyB_fixture, WhitespaceString) { 
        CHECK_THROW(p->decrypt(L"РС ЙГЁ У"), cipher_error); 
    }
    TEST_FIXTURE(KeyB_fixture, DigitsString) { 
        CHECK_THROW(p->decrypt(L"РСЙ1ГЁУ"), cipher_error); 
    }
    TEST_FIXTURE(KeyB_fixture, PunctString) { 
        CHECK_THROW(p->decrypt(L"РС,ЙГЁУ"), cipher_error); 
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) { 
        CHECK_THROW(p->decrypt(L""), cipher_error); 
    }
    TEST(MaxShiftKey) { 
        CHECK(modAlphaCipher(L"Я").decrypt(L"ОПЗБДС") == L"ПРИВЕТ"); 
    }
}

int main()
{
    // Устанавливаем локаль для корректной работы iswalpha и towupper с кириллицей
    setlocale(LC_ALL, ""); 
    return UnitTest::RunAllTests();
}
