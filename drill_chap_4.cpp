#include "D:/Codigos_Estudo/c++/Cpp_Intro_Studies/std_lib_facilities.h" 

int main() 
{
    double val1;
    double val2;

    cout << "Enter 2 numbers: \n";

    while (cin >> val1 >> val2 ) {
        if (val1 < val2) {
            cout << "The smaller value is: " << val1 <<'\n';
            cout << "The larger value is: " << val2 << '\n';
        }
        else if (val1 > val2) {
            cout << "The smaller value is: " << val2 <<'\n';
            cout << "The larger value is: " << val1 << '\n';
        }
        else {
            cout << "val1 == val2\n";
        }
        if (abs(val1 - val2) <= 1.0/100)
            cout << "The numbers are almost equal!\n";
    }
    return 0;
}