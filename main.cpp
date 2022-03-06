#include "head/core.h"
#include "head/calculator.h"
#include "head/SQL.h"
#include "head/Commodity.h"
#include "head/Order.h"
#include <unistd.h>
#include <time.h>
using namespace std;
Commodity com=Commodity();
Order ord=Order();
char pwd[256];
char date[16];
char TIME[16];
void get_directory(){
    getcwd(pwd,sizeof(pwd));
    char *tem = strrchr(pwd,'/');
    strcpy(tem,"/attachment/");
}
void update_time(){
    time_t t=time(0);
    strftime(date,sizeof(date),"%Y-%m-%d",localtime(&t));
    strftime(TIME,sizeof(TIME),"%H:%M:%S",localtime(&t));
}
int main() {
    get_directory();
    update_time();
    com.Init();
    SQL a;
    string cmd = "UPDATE commodity SET 商品状态=销售中 WHERE 商品ID=M001";
    a.read(cmd,0);
    cmd = "SELECT * FROM commodity";
    a.read(cmd,0);
    com.Exit();
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
