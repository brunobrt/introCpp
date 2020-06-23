#include "D:/Codigos_Estudo/c++/Cpp_Intro_Studies/std_lib_facilities.h"

int main()
{
    cout << "Please enter your first name and age\n";
    string first_name = "???";
    int age = 0;
    cin >> first_name >> age; //Read a string followed by an integer
    cout << "Hello, " << first_name << "(age " << age << ")\n";
}