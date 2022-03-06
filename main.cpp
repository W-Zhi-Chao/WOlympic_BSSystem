#include "head/core.h"
#include "head/calculator.h"
#include "head/SQL.h"
#include "head/User.h"
#include "head/Commodity.h"
#include "head/Order.h"
#include <unistd.h>
#include <time.h>
using namespace std;
Commodity com=Commodity();
Order ord=Order();
SQL sql=SQL();
User use=User();
char pwd[256];
char date[16];
char TIME[16];
void get_directory(){
    getcwd(pwd,sizeof(pwd));
    char *tem = strrchr(pwd,'/');
    //cout<<tem<<endl;
    strcpy(tem, "/attachment/");
}
void update_time(){
    time_t t=time(0);
    strftime(date,sizeof(date),"%Y-%m-%d",localtime(&t));
    strftime(TIME,sizeof(TIME),"%H:%M:%S",localtime(&t));
}
inline void INIT(){
    get_directory();
    update_time();
    com.Init();
    ord.Init();
    use.Init();
    sql.Init();
}
inline void EXIT(){
    com.Exit();
    ord.Exit();
    use.Exit();
    sql.Exit();
}
int main() {
    INIT();
    string cmd = "UPDATE commodity SET 商品状态=销售中 WHERE 商品ID=M001";
    sql.read(cmd,0);
    cmd = "SELECT * FROM commodity";
    sql.read(cmd,0);
    EXIT();

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
