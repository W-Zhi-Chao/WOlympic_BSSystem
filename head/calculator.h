
#ifndef WOLYMPIC_BSSYSTEM_CALCULATOR_H
#define WOLYMPIC_BSSYSTEM_CALCULATOR_H

typedef enum {SUC, ERR_OPERAND, ERR_BRACKET, ERR_LACKOP, ERR1,ZERO_DIV} Cal_Error_Code;
typedef enum {TK_NUM,TK_L,TK_R,TK_OPERATOR,TK_ERR} TOKEN; /* all tk_type */

class calculator{
public:
    char* input=NULL;   // cannot be modified, store preprocessed expression
    double output; // output is saved in this variable
    Cal_Error_Code flag;
    calculator(){
        input=new char[1000];
        output=0;
        flag=SUC;
    }
    bool work(const char* expression);
    ~calculator(){
        if(input)
            delete []input;
    }
private:
    TOKEN readin(const char*&,char *&);     // move pointer and return the matched token_type
    void preprocess(const char* expression); //set flag
    char *transform(const char*); // transform infix to postfix
    double atod(char*&);
    bool larger_operator(char op1,char op2){   // op1>op2 true
        if(op1=='+'||op1=='-') {
            if (op2 == '(') return true;
            else return false;
        } else if(op1=='*'||op1=='/') {
            if (op2 == '(' || op2 == '+' || op2 == '-') return true;
            else return false;
        } else if(op1=='(') return false;
        return false;
    }
    bool isoperator(char);
    void calculate(char*); // accept a postfix expression operands separated with ' '
};
#endif
