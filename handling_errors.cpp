#include "std_lib_facilities.h" 

void error(string s1, string s2)
{
    throw runtime_error(s1+s2);
}

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