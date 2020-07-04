#include "std_lib_facilities.h" 

int main()
{
    cout << "Please enter expression (we can handle +, -, *, and /): ";
    int lval = 0;
    int rval;
    cin >> lval;
    if (!cin) error("no second operand");
    for (char op; cin >> op;) {
        if (op != 'x') cin >> rval;
        if (!cin) error("no second operand");
        switch (op)
        {
        case '+':
            lval += rval;
            break;
        case '-':
            lval -= rval;
            break;
        case '*':
            lval *= rval;
            break;
        case '/':
            lval /= rval;
            break;
        default:
            cout << "Result: " << lval << '\n';
            break;
        }
    }
    error("bad expression");
}