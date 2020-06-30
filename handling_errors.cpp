#include "D:/Codigos_Estudo/c++/Cpp_Intro_Studies/std_lib_facilities.h" 

int main()
try {
    // our program
    return 0;  // 0 indicates sucess
}
catch (exception& e) {
    cerr << "error: " << e.what() << '\n';
    keep_window_open();
    return 1;  // 1 indicates failure
}
catch (...) {
    cerr << "Oops: unknown exception!\n";
    keep_window_open();
    return 2;  // 2 indicates failure
}