#ifndef WOLYMPIC_BSSYSTEM_ORDER_H
#define WOLYMPIC_BSSYSTEM_ORDER_H
#include<map>
#include"core.h"
#define ORD_NUM 7
extern char pwd[256];
const int ord_table[ORD_NUM]={5,5,10,10,12,5,5};
const int ord_print_table[ORD_NUM]={8,8,12,8,14,8,8};
typedef struct{
    char orderID[5];   // 订单ID
    char comID[5]; // 商品ID
    char price[10]; // 单价
    char number[10]; // 数量
    char sellDate[12]; // 交易时间
    char sellerID[5]; // 卖家ID
    char buyerID[5]; // 买家ID
} s_order;
class Order {
public:
    s_order *order;
    char target[256];
    string head;
    int num;
    map<string,int> ord_map;
    Order() {
        order = new s_order[100];
        head="订单ID,商品ID,交易单价,数量,交易时间,卖家ID,买家ID";
        num=0;
        ord_map["订单ID"]=0;
        ord_map["商品ID"]=ord_map["订单ID"]+ord_table[0];
        ord_map["交易单价"]=ord_map["商品ID"]+ord_table[1];
        ord_map["数量"]=ord_map["交易单价"]+ord_table[2];
        ord_map["交易时间"]=ord_map["数量"]+ord_table[3];
        ord_map["卖家ID"]=ord_map["交易时间"]+ord_table[4];
        ord_map["买家ID"]=ord_map["卖家ID"]+ord_table[5];
        //order = new Order;
    }
    ~Order(){
        delete []order;
    }
    inline void Init(){
        strcpy(target,pwd);
        strcat(target,"order.txt");
        Read();
    }
    inline void Exit(){
        Write();
    }
    void Read();
    void Write();
    void Printhead();
    void Insert(string &value,int identity);
    void Select(string &value, string &attribute, int identity);
    void Delete(string &value, string &attribute, int identity);
    void Update(string &value, string &attribute, string &set, int identity);
};
#endif

