#include "head/core.h"
#include "head/calculator.h"
#include <stack>
#define ISNUMBER(x) (x<='9'&&x>='0')

TOKEN calculator::readin(const char *&str, char *&dst){
    while(*str){
        if(*str==' '){
            str++;
            continue;
        }
        TOKEN ret;
        if(isoperator(*str)){
            if(*str=='(') ret = TK_L;
            else if(*str==')') ret = TK_R;
            else ret = TK_OPERATOR;
            *dst++=*str++;
            return ret;
        } else if(ISNUMBER(*str)){
            if(*str=='0'&&ISNUMBER(*(str+1))) return TK_ERR;
            while(ISNUMBER(*str))
                *dst++=*str++;
            if(*str=='.') {
                *dst++=*str++;
                while(ISNUMBER(*str)) *dst++=*str++;
            }
            return TK_NUM;
        } else return TK_ERR;
    }
    return TK_ERR;
}

double calculator::atod(char *&str){
    // convert str to double
    // str should be formal
    double res1=0,res2=1;
    while(*str!='.'&&*str){
        if(*str==' ') break;
        res1 = res1 * 10 + *str - '0';
        str++;
    }
    if(*str=='.') str++;
    while(*str!=' '&&*str) {
        res2 /= 10;
        res1 += res2*(*str-'0');
        str++;
    }
    return res1;
}
bool calculator::work(const char* expression){
    // return false if something is wrong
    // else return true
    bool ret = false;
    preprocess(expression);
    switch(this->flag){
        case ERR1:
            cout<<"缺少操作数"<<endl;
            break;
        case ERR_OPERAND:
            cout<<"你的输入中有不合法的字符"<<endl;
            break;
        case ERR_LACKOP:
            cout<<"缺少操作符"<<endl;
            break;
        case ERR_BRACKET:
            cout<<"你的输入中括号不匹配"<<endl;
            break;
        case SUC:
            calculate(transform(input));
            if(flag==ZERO_DIV) cout<<"有除0错误"<<endl;
            else {cout<<"计算完成"<<endl; ret=true;}
            break;
    }
    memset(input,'\0',1000);
    return ret;
}
void calculator::preprocess(const char *expression) {
    // put preprocessed expression in input and return error code
    // definition of error code is in core.h
    char *cpy = this->input;
    int bracket = 0;
    if(*expression=='+'||*expression=='-')
        *cpy++='0';
    TOKEN last = readin(expression,cpy);
    if(last!=TK_L&&last!=TK_NUM){
        if(*(expression-1)=='+'||*(expression-1)=='-') {
            this->flag = ERR1;
            return;
        }
    }
    if(last==TK_L) bracket+=1;
    while(*expression){
        TOKEN now = readin(expression,cpy);
        if(now==TK_ERR){
            this->flag = ERR_OPERAND;
            return;
        }
        if(now==TK_OPERATOR){
            if((*(expression-1)=='-'||*(expression-1)=='+')&&last==TK_L) {
                *(cpy - 1) = '0';
                *cpy++ = *(expression - 1);
            } else if(last!=TK_R&&last!=TK_NUM){
                this->flag = ERR1;
                return;
            }
        } else if(now==TK_NUM){
            if(last!=TK_OPERATOR &&last!=TK_L){
                this->flag = ERR_LACKOP;
                return;
            }
        } else if(now==TK_L){
            bracket+=1;
            if(last!=TK_OPERATOR&&last!=TK_L){
                this->flag = ERR_LACKOP;
                return;
            }
        } else if(now==TK_R){
            bracket-=1;
            if(bracket<0){
                this->flag = ERR_BRACKET;
                return;
            }
            if(last!=TK_NUM&&last!=TK_R){
                this->flag = ERR1;
                return;
            }
        }
        last = now;
    }
    if(bracket>0){
        this->flag = ERR_BRACKET;
        return;
    }
    this->flag=SUC; //SUCCESS
    return;
}

bool calculator::isoperator(char a){
    if(a=='+'||a=='-'||a=='*'||a=='/'||a=='('||a==')')
        return true;
    return false;
}

char* calculator::transform(const char *expression) {
    // expression: 1000 bytes at most
    stack<char> op;
    char *res = new char[1000];
    char *cpy = res;
    for(int i=0; expression[i]!='\0'; i++){
        if(isoperator(expression[i])){
            if(op.empty()||expression[i]=='(') op.push(expression[i]);
            else if(expression[i]==')'){
                while(op.top()!='('){
                    *cpy++ = op.top();
                    op.pop();
                }
                op.pop(); //pop (
            } else{
                if(larger_operator(expression[i],op.top())){
                    op.push(expression[i]);
                } else{
                    *cpy++ = op.top();
                    op.pop();
                    i--;         // come back to the same i
                    continue;
                }
            }
        } else if(expression[i]!=' '){
            *cpy++ = expression[i];
            if(expression[i+1]=='\0'|| isoperator(expression[i+1]) || expression[i+1]==' ') *cpy++=' ';
        }
    }
    while(!op.empty()){
        *cpy++ = op.top();
        op.pop();
    }
    //cout<<res<<endl;
    return res;
}

void calculator::calculate(char *postfix) {
    // caculate a postfix expression
    stack<double> st;
    char *cpy = postfix;
    while(*cpy!='\0'){
        while (*cpy == ' ') cpy++;
        if(isoperator(*cpy)) {
            double x1 = st.top();
            st.pop();
            double x2 = st.top();
            st.pop();
            switch (*cpy) {
                case '+':
                    st.push(x1 + x2); break;
                case '-':
                    st.push(x2 - x1); break;
                case '*':
                    st.push(x2 * x1); break;
                case '/':
                    if(x1==0){
                        this->flag=ZERO_DIV;
                        return;
                    }
                    st.push(x2 / x1); break;
            }
        } else{
            st.push(atod(cpy));
        }
        cpy++;
    }
    delete []postfix;
    this->output = st.top();
}