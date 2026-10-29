#include <UnitTest++/UnitTest++.h>
#include "tableCipher.h"


SUITE(KeyTest)
{
    // 1.1 Верный ключ (в методичке проверяли через encrypt)
    TEST(ValidKey) {
        CHECK_EQUAL("ITREPV", tableCipher("KEY").encrypt("PRIVET"));
    }
    
    // 1.2 Ключ длиннее (проверяем, что шифрование работает с длинным ключом)
	TEST(LongKey) {
    CHECK_EQUAL("XXXXTEVIRP", tableCipher("ABCDEFGHIJ").encrypt("PRIVET"));
}
    // 1.3 Вырожденный ключ (длина 1)
    TEST(KeyIsOne) {
        CHECK_THROW(tableCipher cp("A"), cipher_error);
    }
    
    // 1.4 Пустой ключ
    TEST(EmptyKey) {
        CHECK_THROW(tableCipher cp(""), cipher_error);
    }
    
    // 1.5 В ключе цифры
    TEST(DigitsInKey) {
        CHECK_THROW(tableCipher cp("K1Y"), cipher_error);
    }
    
    // 1.6 В ключе знаки препинания
    TEST(PunctInKey) {
        CHECK_THROW(tableCipher cp("K,Y"), cipher_error);
    }
}


struct Key3_fixture {
    tableCipher * p;
    Key3_fixture() {
        p = new tableCipher("KEY");
    }
    ~Key3_fixture() {
        delete p;
    }
};


SUITE(EncryptTest)
{
    TEST_FIXTURE(Key3_fixture, UpCaseString) {
        CHECK_EQUAL("ITREPV", p->encrypt("PRIVET"));
    }
    
    TEST_FIXTURE(Key3_fixture, LowCaseString) {
        CHECK_EQUAL("ITREPV", p->encrypt("privet"));
    }
    
    TEST_FIXTURE(Key3_fixture, StringWithWhitspaceAndPunct) {
        CHECK_EQUAL("ITREPV", p->encrypt("PRI VET!!!"));
    }
    
	TEST_FIXTURE(Key3_fixture, StringWithNumbers) {
        CHECK_EQUAL("PNYRAYWAHPEE", p->encrypt("HAPPY NEW 2019 YEAR"));
    }
    
    TEST_FIXTURE(Key3_fixture, EmptyString) {
        CHECK_THROW(p->encrypt(""), cipher_error);
    }
    
    TEST_FIXTURE(Key3_fixture, NoAlphaString) {
        CHECK_THROW(p->encrypt("1234+8765=9999"), cipher_error);
    }
}


SUITE(DecryptText)
{
    TEST_FIXTURE(Key3_fixture, UpCaseString) {
        CHECK_EQUAL("PRIVET", p->decrypt("ITREPV"));
    }
    
    TEST_FIXTURE(Key3_fixture, LowCaseString) {
        CHECK_THROW(p->decrypt("itrePV"), cipher_error);
    }
    
    TEST_FIXTURE(Key3_fixture, WhitespaceString) {
        CHECK_THROW(p->decrypt("IT REPV"), cipher_error);
    }
    
    TEST_FIXTURE(Key3_fixture, DigitsString) {
        CHECK_THROW(p->decrypt("ITR3PV"), cipher_error);
    }
    
    TEST_FIXTURE(Key3_fixture, PunctString) {
        CHECK_THROW(p->decrypt("ITR,PV"), cipher_error);
    }
    
    TEST_FIXTURE(Key3_fixture, EmptyString) {
        CHECK_THROW(p->decrypt(""), cipher_error);
    }
}


int main(int argc, char **argv)
{
    return UnitTest::RunAllTests();
}