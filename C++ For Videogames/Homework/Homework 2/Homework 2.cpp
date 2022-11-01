#include <iostream>
#include "String.h"

using namespace std;

int main()
{
    String a("hello");
    String b(std::move(a));
    a.Write();
    b.Write();
    String c = a + b;
    c.Write();
    if (c == "hellohello") {
        cout << "Son iguales" << endl;
    }
    else {
        cout << "No son iguales" << endl;
    }
    cout << a.Lenght() << endl;
    a.clear();
    cout << a.Lenght() << endl;
    a = b;
    a.Write();
    cout << a.Lenght() << endl;

}