#include "std_lib_facilities.h" 

int area(int length, int width) { 
    return length * width; 
}

int main()
{
    /* ======== Errors ======== */
    //int s1 = area(7;           // error: expected ')' before ';' token
    //int s2 = area(7)           //  too few arguments to function 'int area(int, int)'
    //Int s3 = area(7);          // error: 'Int' was not declared in this scope
    //int s4 = area('7);         // error: missing terminating ' character
    
    /* ======== Non-errors ======== */
    // int x4 = area(10,–7);     // OK: but what is a rectangle with a width of minus 7?
    // int x5 = area(10.7,9.3);  // OK: but calls area(10,9)
    // char x6 = area(100,9999);  // OK: but truncates the result

}