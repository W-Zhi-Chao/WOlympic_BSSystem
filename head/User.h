#ifndef WOLYMPIC_BSSYSTEM_USER_H
#define WOLYMPIC_BSSYSTEM_USER_H
#define USE_NUM 7
#include<map>
#include"core.h"
extern char pwd[256];
const int use_table[USE_NUM]={5,10,20,20,20,10,10};
const int use_print_table[USE_NUM]={8,12,20,20,20,12,12};
typedef struct{
    char userID[5];   // 用户ID
    char userName[10]; // 用户名
    char passwd[20]; // 密码
    char telephone[20]; // 联系方式
    char location[20]; // 地址
    char money[10]; // 钱包余额
    char state[10]; // 用户状态
} s_user;
class User {
public:
    s_user *user;
    char target[256];
    string head;
    map<string,int> use_map;
    int num;
    User() {
        user = new s_user[100];
        head="用户ID,用户名,密码,联系方式,地址,钱包余额,用户状态";
        num=0;
        use_map["用户ID"]=0;
        use_map["用户名"]=use_map["用户ID"]+use_table[0];
        use_map["密码"]=use_map["用户名"]+use_table[1];
        use_map["联系方式"]=use_map["密码"]+use_table[2];
        use_map["地址"]=use_map["联系方式"]+use_table[3];
        use_map["钱包余额"]=use_map["地址"]+use_table[4];
        use_map["用户状态"]=use_map["钱包余额"]+use_table[5];
        //order = new Order;
    }
    ~User(){
        delete []user;
    }
    void Init(){
        strcpy(target,pwd);
        strcat(target,"user.txt");
        Read();
    }
    inline void Exit(){
        Write();
    }
    void Read();
    void Write();
    void Printhead(int identity);
    void Insert(string &value,int identity);
    bool Select(string &value, string &attribute, int identity);
    void Delete(string &value, string &attribute, int identity);
    void Update(string &value, string &attribute, string &set, int identity);
    int Find(const char* name);
};
#endif
