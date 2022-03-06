#ifndef WOLYMPIC_BSSYSTEM_COMMODITY_H
#define WOLYMPIC_BSSYSTEM_COMMODITY_H
#define COM_NUM 8
#include<map>
extern char pwd[256];
const int com_table[COM_NUM]={5,20,10,10,100,10,12,10};
const int com_print_table[COM_NUM]={8,15,12,7,100,10,14,10};
typedef struct{
    char ID[5];   // ID
    char Name[20]; // 名称
    char price[10]; // 价格
    char number[100]; // 数量
    char description[10]; // 描述
    char sellerID[10]; // 卖家ID
    char addedDate[12]; // 上架时间
    char state[10]; // 商品状态
} s_commodity;
class Commodity {
public:
    s_commodity *commodity;
    char target[256];
    string head;
    int num;
    map<string,int> com_map;
    Commodity() {
        commodity = new s_commodity[100];
        head="商品ID,名称,价格,数量,描述,卖家ID,上架时间,商品状态";
        num=0;
        com_map["ID"]=0;
        com_map["名称"]=com_map["ID"]+com_table[0];
        com_map["价格"]=com_map["名称"]+com_table[1];
        com_map["数量"]=com_map["价格"]+com_table[2];
        com_map["描述"]=com_map["数量"]+com_table[3];
        com_map["卖家ID"]=com_map["描述"]+com_table[4];
        com_map["上架时间"]=com_map["卖家ID"]+com_table[5];
        com_map["商品状态"]=com_map["上架时间"]+com_table[6];
        //order = new Order;
    }
    ~Commodity(){
        delete []commodity;
    }
    inline void Init(){
        strcpy(target,pwd);
        strcat(target,"commodity.txt");
        Read();
    }
    inline void Exit(){
        Write();
    }
    void Read();
    void Write();
    void Insert(string &value,int identity);
    void Select(string &value, string &attribute, int identity);
    void Delete(string &value, string &attribute, int identity);
    void Update(string &value, string &attribute, string &set);
};
#endif
