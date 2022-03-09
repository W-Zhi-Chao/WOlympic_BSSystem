#include "head/core.h"
#include "head/main.h"
using namespace std;
Commodity *com;
Order *ord;
SQL *sql;
User *use;
Administrator *adm;
calculator *cal;
People *peo;
Buyer *buy;
Seller *sel;
char pwd[256];
char date[16];
char TIME[16];
void get_directory(){
    getcwd(pwd,sizeof(pwd));
    char *tem = strrchr(pwd,'/');
    strcpy(tem, "/attachment/");
}
void update_time(){
    time_t t=time(0);
    strftime(date,sizeof(date),"%Y-%m-%d",localtime(&t));
    strftime(TIME,sizeof(TIME),"%H:%M:%S",localtime(&t));
}
void INIT(){
    com = new Commodity;
    ord = new Order;
    use = new User;
    sql = new SQL;
    adm = new Administrator;
    cal = new calculator;
    peo = new People;
    buy = new Buyer;
    sel = new Seller;
    get_directory();
    update_time();
    com->Init();
    ord->Init();
    use->Init();
    sql->Init();
    adm->Init();
}
int main() {
    INIT();
    while(true) {
        SPLITLINE(40);
        cout << "1.管理员登录 2.用户注册 3.用户登录 4.退出程序" << endl;
        SPLITLINE(40);
        cout << endl << "请输入操作: ";
        char option[32];
        cin.getline(option,32);
        if(strcmp(option,"1")==0){
            cout<<"请输入管理员姓名: ";
            char ID[20],passwd[20];
            cin.getline(ID,20);
            cout<<"请输入密码: ";
            cin.getline(passwd,20);
            adm->Signin(ID,passwd);
        } else if(strcmp(option,"2")==0){
            peo->Signup();
        } else if(strcmp(option,"3")==0){
            cout<<"请输入用户ID: ";
            char ID[10],passwd[20];
            cin.getline(ID,10);
            cout<<"请输入密码: ";
            cin.getline(passwd,20);
            peo->Signin(ID,passwd);
        } else if(strcmp(option,"4")==0){
            break;
        } else{
            cout<<"命令错误请重新输入"<<endl;
        }
    }
//    string cmd = "DELETE FROM commodity WHERE 商品ID=M001";
//    sql->read(cmd,0);
//    cmd = "SELECT * FROM commodity";
//    sql->read(cmd,0);
//    auto *A=new calculator;
//    while(true) {
//        cout << "请输入你的表达式，注意不要超过100个字符:" << endl;
//        char tem[1000];
//        cin.getline(tem, 1000);
//        bool ret = A->work(tem);
//        //cout<<A.input<<endl;
//        if (ret) {
//            cout << A->output << endl;
//        }
//    }

    return 0;
}
