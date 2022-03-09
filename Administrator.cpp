#include "head/core.h"
#include "head/Administrator.h"
#include "head/SQL.h"
extern SQL *sql;
void Administrator::Init() {
    strcpy(target,pwd);
    strcat(target,"administrator.txt");
    ifstream fs;
    fs.open(target);
    char *tem = new char[64];
    fs.getline(tem,64);
    fs.getline(tem,64);
    fs.close();
    char *cpy= strchr(tem,',');
    *cpy++='\0';
    strcpy(ID,tem);
    strcpy(passwd,cpy);
    delete []tem;
}
void Administrator::Signin(const char *name, const char *passwd){
    if(strcmp(name,this->ID)==0&&strcmp(passwd,this->passwd)==0) {
        cout << endl<<"-----登录成功-----";
        cout<<endl;
        admin_main();
    }
    else {
        cout << endl<<"----密码错误或用户名不存在，返回主菜单----";
        cout<<endl;
        return;
    }
}
void Administrator::admin_main() {
    char *option=new char[32];
    char *tem=new char[20];
    while(true){
        SPLITLINE(75);
        cout << "1.查看所有商品 2.搜索商品 3.下架商品 4.查看所有订单 5.查看所有用户 6.封禁用户 7.注销" << endl;
        SPLITLINE(75);
        cout<<endl<<"请输入操作: ";
        string cmd;
        cin.getline(option,32);
        if(strcmp(option,"1")==0){
            cmd="SELECT * FROM commodity";
            sql->read(cmd,0);
            cout<<endl;
        } else if(strcmp(option,"2")==0){
            cout<<"请输入商品名称: ";
            cin.getline(tem,20);
            cmd="SELECT * FROM commodity WHERE 名称 CONTAINS ";
            cmd.append(tem);
            sql->read(cmd,0);
            cout<<endl;
        } else if(strcmp(option,"3")==0){
            cout<<"请输入商品ID: ";
            cin.getline(tem,20);
            cmd="DELETE FROM commodity WHERE 商品ID=";
            cmd.append(tem);
            string cmd1 = "SELECT * FROM commodity WHERE 商品ID CONTAINS ";
            cmd1.append(tem);
            cout<<"确认要下架该商品吗？"<<endl;
            sql->read(cmd1,0);
            if(sql->suc) {
                char t[2];
                cout<<"请选择(y/n): ";
                cin.getline(t,2);
                if(strcmp(t,"y")==0) {
                    sql->read(cmd, 0);
                }else if(strcmp(t,"n")==0){}
                else{cout<<"只能输入y/n! 返回主界面"<<endl;}
            }
            cout<<endl;
        } else if(strcmp(option,"4")==0){
            string cmd="SELECT * FROM order";
            sql->read(cmd,0);
            cout<<endl;
        } else if(strcmp(option,"5")==0){
            string cmd="SELECT * FROM user";
            sql->read(cmd,0);
            cout<<endl;
        } else if(strcmp(option,"6")==0){
            cout<<"请输入要删除的用户ID: ";
            cin.getline(tem,20);
            cmd="DELETE FROM user WHERE 用户ID=";
            cmd.append(tem);
            string cmd1 = "SELECT * FROM user WHERE 用户ID CONTAINS ";
            cmd1.append(tem);
            cout<<"确认要删除该用户吗？"<<endl;
            sql->read(cmd1,0);
            if(sql->suc) {
                char t[2];
                cout<<"请选择(y/n): ";
                cin.getline(t,2);
                if(strcmp(t,"y")==0) {
                    sql->read(cmd, 0);
                    cmd = "UPDATE commodity SET 商品状态=已下架 WHERE 卖家ID=";
                    cmd.append(tem);
                    sql->read(cmd,0);
                }else if(strcmp(t,"n")==0){}
                else{cout<<"只能输入y/n，别给老子加空格! 返回主界面"<<endl;}
            }
            cout<<endl;
        } else if(strcmp(option,"7")==0){
            break;
        } else{
            cout<<"命令错误请重新输入\n";
        }
    }
    delete []tem;
    delete []option;
}