#include "String.h"
#include <iostream>

using namespace std;

String::String(const char* str)
{
    string = str;
    int i = 0;
    while (string[i] != 0) {
        i++;
    }
    lenght = i;
}

String::String(const String&& a)
{
    string = a.string;
    lenght = a.lenght;
}

void String::clear()
{
    //TODO preguntar porque no se puede hacer delete string
    string = 0;
    lenght = 0;
}

String& String::operator=(const String& a)
{
    delete string;
    char* tmp_string = new char[a.lenght + 1];
    std::copy(a.string, a.string + a.lenght, tmp_string);
    tmp_string[a.lenght] = 0;
    string = tmp_string;
    lenght = a.lenght;
    return *this;
}

bool String::operator==(const char* a)
{
    int a_lenght = 0;
    while (a[a_lenght] != 0) {
        a_lenght++;
    }
    if (lenght != a_lenght) return false;
    for (int i = 0; i < lenght; i++) {
        if (string[i] != a[i])
            return false;
    }
    return true;
}

String String::operator+(const String& a)
{
    String aux("");
    aux.lenght = lenght + a.lenght;
    char* tmp_string = new char[a.lenght + lenght + 1];
    for (int i = 0; i < lenght; i++) {
        tmp_string[i] = string[i];
    }
    for (int i = 0; i < a.lenght; i++) {
        tmp_string[i + lenght] = string[i];
    }
    tmp_string[a.lenght + lenght] = 0;
    aux.string = tmp_string;
    return aux;
}

void String::Write()
{
    cout << string << endl;
}
