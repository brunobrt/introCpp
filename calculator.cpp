/*
    Simple Calculator: This program implements a basic expression calculator.
    Input from cin; output to cout.
    The grammar for input is:

    Calculation:
        Expression
        Print
        Quit
        Calculation Statement

    Statement:
        Declaration
        Expression

    Declaration:
        "let" Name "=" Expression
    Print:
        ;
    Quit:
        q
    
    Expression:
        Term
        Expression + Term
        Expression - Term
    Term:
        Primary
        Term * Primary
        Term / Primary
        Term % Primary
    Primary:
        Number
        ( Expression )
        - Primary
        + Primary
    Number:
        floating-point-literal

    Input comes from cin thorugh the Token_stream called ts.
*/

#include "std_lib_facilities.h" 

// Constants
const char number = '8';      // t.kind == number means that t is a number Token
const char quit = 'q';        // t.kind == quit means that t is a quit Token
const char print = ';';       // t.kind == print means that t is a print Token
const string prompt = "> ";   // used to prompt a new expression
const string result = "= ";   // used to indicate that what follows is a result
const char name = 'a';        // name token
const char let = 'L';         // declaration token
const string declkey = "let"; // declaration keyword

// Classes
class Token {
    public: 
    char kind;
    double value;
    string name;
    Token(char ch) :kind{ch} {}                         // initialize kind with ch
    Token(char ch, double val) :kind{ch}, value{val} {} // initialize kind and value
    Token(char ch, string n) :kind{ch}, name{n} {}      // initialize kind and name
};

class Token_stream {
    public:
        Token_stream() :full(0), buffer(0) {}
        Token get();            // get a Token
        void putback(Token t);  // put  a Token back
        void ignore(char c);    // discard characters up to and including a c
    private:
        bool full {false};      // is there a Token in the buffer?
        Token buffer;           // here is where we keep a Token put back using putback()
};

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
    case quit:
    case print:
    case '(': 
    case ')': 
    case '+':
    case '-': 
    case '*': 
    case '/':
    case '=':
        return Token{ch};     // let eac character represent itself
    case '.':                 // a floating-point-literal can start with a dot
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':    // numeric literal
    {
        cin.putback(ch);        // put digit back into the input stream
        double val;
        cin >> val;             // read a floating-point number
        return Token{number, val}; 
    }
    default :
        if (isalpha(ch)){
            cin.putback(ch);
            string s;
            s += ch;
            while(cin.get(ch) && (isalpha(ch) || isdigit(ch))) s += ch;
            cin.putback(ch);
            if (s == declkey) return Token(let);  // declaration keyword
            return Token{name, s};
        }
        error("Bad token");
    }
}

void Token_stream::putback(Token t)
{
    if (full) error("putback() into a full buffer");
    buffer = t;   // copy t to buffer
    full = true;  // buffer is now full
}

void Token_stream::ignore(char c)
    // c represents the kind of Token
{
    // first look in buffer:
    if (full && c == buffer.kind) {
        full = false;
        return;
    }
    full = false;

    // now search input
    char ch = 0;
    while (cin>>ch)
    if (ch == c) return;
}

class Variable {
    public: 
        string name;
        double value;
};
// Initializations
Token_stream ts;      // provides get() and putback()
double expression();  // declaration so that primary() can call expression()
// Variables
vector <Variable> var_table;
// Functions

double primary()      // deal with number and parentheses
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
    case number:     // we use '8' tu represent a number
        return t.value;
    case '-':
        return - primary();
    case '+':
        return primary();
    default:
        error("primary expected");
    }
}

double term()         // deal with * and /
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
        case '%':
        {
            double d = primary();
            if (d == 0) error("%: divide by zero");
            left = fmod(left, d);
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

void clean_up_mess()
{
    ts.ignore(print);
}

double get_value(string s)    // return the value of the Variable named s
{
    for (const Variable& v: var_table)
        if(v.name == s) return v.value;
    error("get: undefined variable ", s);
}

void set_value(string s, double d)  // set the Variable named s to d
{
    for (Variable& v: var_table)
    if (v.name == s) {
        v.value = d;
        return;
    }
    error("set: undefined variable ", s);
}

bool is_declared(string var)
    // is var in var_table?
{
    for (const Variable& v : var_table)
        if(v.name == var) return true;
    return false;
}

double define_name(string var, double val)
    // add {var, val} to var_table
{
    if(is_declared(var)) error(var, "declared twice");
    var_table.push_back(Variable{var, val});
    return val;
}

double declaration()
    // assume we have seen "let"
    // handle: name = expression
    // declare a variable called "name" with initial value "expression"
{
    Token t = ts.get();
    if(t.kind != name) error("name expected in declaration");
    string var_name = t.name;

    Token t2 = ts.get();
    if(t2.kind != '=') error("= missing in declaration of ", var_name);
    
    double d = expression();
    define_name(var_name, d);
    return d;
}

double statement()
{
    Token t = ts.get();
    switch (t.kind)
    {
    case let:
        return declaration();
        break;
    
    default:
        ts.putback(t);
        return expression();
    }
}

void calculate()      // expression evaluation loop
{
    while (cin)
    try
    {
        cout << prompt;
        Token t = ts.get();
        while (t.kind == print) t = ts.get();  // first discard all "prints"
        if (t.kind == quit) return;
        ts.putback(t);
        cout << result << statement() << '\n';
    }
    catch (exception& e){
        cerr << e.what() << '\n';
        clean_up_mess();
    }
}

int main()
try{
    // predine names:
    define_name("pi", 3.1415926535);
    define_name("e", 2.718218284);
    calculate();
    return 0;
}
catch (runtime_error& e) {
    cerr << e.what() << '\n';
    return 1;
}
catch (exception& e) {
    cerr << e.what() << '\n';
    return 2;
}
catch (...) {
    cerr << "exception\n";
    return 3;
}