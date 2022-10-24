#include <iostream>
#include "String.h"

using namespace std;

int main()
{
    String a("hello");
    String b(std::move(a));
    a.Write();
    b.Write();
    cout << a.lenght() << endl;
    a.clear();
    cout << a.lenght() << endl;
    cout << "Hello World!\n";
}