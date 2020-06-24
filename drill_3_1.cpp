#include "D:/Codigos_Estudo/c++/Cpp_Intro_Studies/std_lib_facilities.h"

int main()
{
    cout << "Enter the name of the person you want to write to, followed by a friend's name, also, enter 'm' for male and 'f' for female:\n";
    string first_name;
    string friend_name;
    char friend_sex = 0;
    cin >> first_name >> friend_name >> friend_sex;
    if (friend_sex == 'm')
        cout << "if you see " << friend_name << " please ask him to call me";
    else if (friend_sex == 'f')
        cout << "if you see " << friend_name << " please ask her to call me";
    else 
        cout << "Dear " << first_name << ",\nHow are you?\nI'm fine and you?\nMe too! have you seen " << friend_name << " lately?\n";
}