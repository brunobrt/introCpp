#include "std_lib_facilities.h" 

class Token {
    public: char kind;
    double value;
};

class Token_stream {
    public:
        Token_stream();         // make a Token_stream that reads from cin
        Token get();            // get a Token
        void putback(Token t);  // put  a Token back
    private:
        bool full {false};      // is there a Token in the buffer?
        Token buffer;           // here is where we keep a Token put back using putback()
};

void Token_stream::putback(Token t)
{
    if (full) error("putback() into a full buffer");
    buffer = t;   // copy t to buffer
    full = true;  // buffer is now full
}

Token Token_stream::get()
{
    if (full) {             // do we already have a Token ready?
        full = false;       // remove Token from buffer
        return buffer;
    }
    char ch;
    cin >> ch;              // note that >> skips whitespace
    switch (ch)
    {
    case ';': // for "print"
    case 'q': // for "quit"
    case '(': case ')': case '+': case '-': case '*': case '/':
        return Token{ch};
    case '.':
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9': 
    {
        cin.putback(ch);        // put digit back into the input stream
        double val;
        cin >> val;             // read a floating-point number
        return Token{'8', val}; // let '8' represent "a number"
    }
    default :
        error("Bad token");
    }
}

Token_stream ts;     // provides get() and putback()
double expression(); // declaration so that primary() can call expression()

double primary()     // deal with number and parentheses
{
    Token t = ts.get();
    switch (t.kind)
    {
    case '(':
        {
            double d = expression();
            t = ts.get();
            if (t.kind != ')') error("')' expected");
            return d;
        }
        break;
    case '8':     // we use '8' tu represent a number
        return t.value;
    default:
        error("primary expected");
    }
}

double term()        // deal with * and /
{
    double left = primary();
    Token t = ts.get();
    while(true) {
        switch (t.kind)
        {
        case '*':
            left *= primary();
            t = ts.get();
            break;
        case '/':
        {
            double d = primary();
            if (d == 0) error("divide by zero");
            left /= d;
            t = ts.get();
            break;
        }
        default:
            ts.putback(t);
            return left;
        }
    }
}

double expression()   // deal with + and -
{
    double left = term();     // read and evaluate Term
    Token t = ts.get();      // get the next Token from the Token stream
    while(true) {
        switch (t.kind)
        {
        case '+':
            left += term();   // evaluate Term and add
            t = ts.get();
            break;
        case '-':
            left -+ term();   // evaluate Term and subtract
            t = ts.get();
            break;
        default:
            ts.putback(t);    // put t back into the Token stream.
            return left;      // finally: no more + or -; return the answer
        }
    }
}


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