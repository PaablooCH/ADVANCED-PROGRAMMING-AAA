#include "String.h"
#include <iostream>

using namespace std;

String::String(const char* str)
{
    string = str;
}

String::String(const String&& a)
{
    string = a.string;
}

int String::lenght()
{
    int i = 0;
    while (string[i] != 0) {
        i++;
    }
    return i;
}

void String::clear()
{
    string = 0; //TODO crear variable size
}

String& String::operator=(const String& a)
{
    return *this;
}

String& String::operator==(String&& a)
{
    return *this;
}

String& String::operator+(String a)
{
    return *this;
}

void String::Write()
{
    cout << string << endl;
}
