#include "head/core.h"
#include "head/People.h"
#include "head/SQL.h"
#include "head/User.h"
#include "head/Order.h"
#include "head/Commodity.h"
#include "head/calculator.h"
#include <map>
extern SQL *sql;
extern User *use;
extern Commodity *com;
extern Order *ord;
extern calculator *cal;
extern Buyer *buy;
extern Seller *sel;
extern People *peo;
void People::Signin(char *id, char *passwd) {
    user_id = use->Find(id);
    if(user_id==-1){
        cout << endl<<"----用户名不存在，返回主菜单----";
        cout<<endl;
    } else if(strcmp(use->user[user_id].passwd,passwd)==0){
        cout << endl<<"-----登录成功-----";
        cout<<endl;
        sprintf(u,"U%03d",user_id+1);
        strcpy(buy->u,u);
        strcpy(sel->u,u);
        buy->user_id=user_id;
        sel->user_id=user_id;
        peoplemain();
    } else{
        cout << endl<<"----密码错误，返回主菜单----";
        cout<<endl;
    }
}
void People::Signup() {
    string name,location,phone,passwd,cmd;
    cout<<"请输入要注册的用户名，不超过10个字符: ";
    cin>>name;
    cout<<"请输入您的密码，不超过20个字符: ";
    cin>>passwd;
    cout<<"请输入您的联系方式，不超过20个字符: ";
    cin>>phone;
    cout<<"请输入您的地址，不超过20个字符: ";
    cin>>location;
    char tem[256];
    sprintf(tem,"INSERT INTO user VALUES (U%03d,%s,%s,%s,%s,0.0,正常)",use->num+1,tem,name.c_str(),passwd.c_str(),phone.c_str(),location.c_str());
    cmd=tem;
    sql->read(cmd,0);
    cout<<"Hello, "<<name<<"! 请记住你的用户ID: "<<tem<<endl;
}
void People::peoplemain() {
    char *option=new char[32];
    char *tem=new char[20];
    while(true){
        SPLITLINE(40);
        cout << "1.我是买家 2.我是卖家 3.个人信息管理 4.注销登录" << endl;
        SPLITLINE(40);
        cout<<endl<<"请输入操作: ";
        string cmd;
        cin.getline(option,32);
        if(strcmp(option,"1")==0){
            buy->buyermain();
        } else if(strcmp(option,"2")==0){
            sel->sellermain();
        } else if(strcmp(option,"3")==0){
             manageinfo();
        } else if(strcmp(option,"4")==0){
            break;
        } else cout<<"输入错误，请重新输入"<<endl;
    }
    delete []tem;
    delete []option;
}
void People::manageinfo() {
    char *option=new char[32];
    char *tem=new char[20];
    while(true){
        SPLITLINE(40);
        cout << "1.查看信息 2.修改信息 3.充值 4.返回用户主界面" << endl;
        SPLITLINE(40);
        cout<<endl<<"请输入操作: ";
        string cmd;
        cin.getline(option,32);
        if(strcmp(option,"1")==0){
            Showinfo();
        } else if(strcmp(option,"2")==0){
            Editinfo();
        } else if(strcmp(option,"3")==0){
            AddCredit();
        } else if(strcmp(option,"4")==0){
            break;
        } else cout<<"输入错误，请重新输入"<<endl;
    }
    delete []tem;
    delete []option;
}
void People::Showinfo() {
    SPLITLINE(25);
    cout<<"用户名: "<<use->user[user_id].userID<<endl;
    cout<<"联系方式: "<<use->user[user_id].telephone<<endl;
    cout<<"地址: "<<use->user[user_id].location<<endl;
    string exp="";
    // 售出记录查询
    for(int i=0; i<ord->num; i++) {
        if (strcmp(ord->order[i].sellerID, u) == 0) {
            exp.append(ord->order[i].number);
            exp.append("*");
            exp.append(ord->order[i].price);
            exp.append("+");
        }
    }
    // 购买记录查询
    exp.pop_back();
    exp.push_back('-');
    for(int i=0; i<ord->num; i++) {
        if (strcmp(ord->order[i].buyerID, u) == 0) {
            exp.append(ord->order[i].number);
            exp.append("*");
            exp.append(ord->order[i].price);
            exp.append("-");
        }
    }
    exp.pop_back();
    // 化简表达式
    map<string,string> st;
    for(int i=0;i<exp.size();i++){
        if(exp.at(i)=='*'){
            int j,k;
            for(j=i-1;j>=0;j--)
                if(exp.at(j)=='+'||exp.at(j)=='-') break;
            string subs,subs2;
            subs = exp.substr(j+1,i-j-1);
            for(k=i+1;k<exp.size();k++)
                if(exp.at(k)=='+'||exp.at(k)=='-') break;
            subs2 = exp.substr(i+1,k-i-1);
            if(st.find(subs)==st.end()) {
                st[subs]="";
            }
            if(j!=-1) {
                st[subs].push_back(exp.at(j));
            }
            st[subs].append(subs2);
            //st[subs].append(subs);
        }
    }
    exp="";
    ifstream fs;
    char tem[128];
    // 充值记录查询
    fs.open("/Users/wzc/Desktop/Study/Code/C++/WOlympic_BSSystem/attachment/credit.txt");
    fs.getline(tem,128);
    while(!fs.eof()) {
        fs.getline(tem, 128);
        string t=tem;
        string::size_type pos1 = t.find(",",0);
        string::size_type pos2 = t.find(",",6);
        if(t.substr(0,pos1)==u){
            exp.append(t.substr(pos1+1,pos2-pos1-1));
            exp.append("+");
        }
    }
    fs.close();
    for(auto i=st.begin();i!=st.end();i++){
        exp.append(i->first);
        exp.append("*(");
        exp.append(i->second);
        exp.append(")+");
    }
    exp.pop_back();
    if(cal->work(exp.c_str())) {
        printf("钱包余额: %.1f\n",cal->output);
    }
    SPLITLINE(25);
}
void People::Editinfo() {
    // people can share 用户名 but 用户ID is unique
    cout<<"请选择修改的属性(1.用户名 2.联系方式 3.地址 4.密码): ";
    char tem[20];
    string cmd;
    cin.getline(tem,2);
    if(strcmp(tem,"1")==0){
        cout<<"请输入新的用户名，不超过10字符: ";
        cin.getline(tem,20);
        cmd  = "UPDATE user SET 用户名=";
        cmd.append(tem);
        cmd.append(" WHERE 用户ID=");
        cmd.append(u);
        sql->read(cmd,1);
    } else if(strcmp(tem,"2")==0){
        cout<<"请输入新的联系方式，不超过20字符: ";
        cin.getline(tem,20);
        cmd  = "UPDATE user SET 联系方式=";
        cmd.append(tem);
        cmd.append(" WHERE 用户ID=");
        cmd.append(u);
        sql->read(cmd,1);
    } else if(strcmp(tem,"3")==0){
        cout<<"请输入新的地址，不超过20字符: ";
        cin.getline(tem,20);
        cmd  = "UPDATE user SET 地址=";
        cmd.append(tem);
        cmd.append(" WHERE 用户ID=");
        cmd.append(u);
        sql->read(cmd,1);
    } else if(strcmp(tem,"4")==0){
        cout<<"请输入新的密码，不超过20字符: ";
        cin.getline(tem,20);
        cmd  = "UPDATE user SET 密码=";
        cmd.append(tem);
        cmd.append(" WHERE 用户ID=");
        cmd.append(u);
        sql->read(cmd,1);
    } else cout<<"输入错误，请重新输入"<<endl;
}
void People::AddCredit() {
    ofstream fs;
    fs.open("/Users/wzc/Desktop/Study/Code/C++/WOlympic_BSSystem/attachment/credit.txt",ios::app);
    cout<<"请输入充值金额，龙叔温馨提示，系统里的你再强也是虚假的: ";
    char tem[16];
    cin.getline(tem,16);
    float x=strtof(use->user[user_id].money,NULL);
    float y=strtof(tem,NULL);
    sprintf(tem,"%.1f",y);
    fs<<u<<','<<tem<<','<<date<<endl;
    sprintf(tem,"%.1f",x+y);
    string cmd="UPDATE user SET 钱包余额=";
    cmd.append(tem);
    cmd.append(" WHERE 用户ID=");
    cmd.append(u);
    sql->read(cmd,0);
    cout<<"充值成功!"<<endl;
    fs.close();
}

void Buyer::buyermain(){
    char *option=new char[32];
    char *tem=new char[20];
    while(true){
        SPLITLINE(75);
        cout<<"1.查看商品列表 2.购买商品 3.搜索商品 4.查看历史订单 5.查看商品详细信息 6.返回用户主界面"<<endl;
        SPLITLINE(75);
        cout<<endl<<"请输入操作: ";
        string cmd;
        cin.getline(option,32);
        if(strcmp(option,"1")==0){
            ListCom();
        } else if(strcmp(option,"2")==0){
            BuyCom();
        } else if(strcmp(option,"3")==0){
            SearchCom();
        } else if(strcmp(option,"4")==0){
            HistoryOrder();
        } else if(strcmp(option,"5")==0){
            ShowDetailCom();
        } else if(strcmp(option,"6")==0){
            break;
        } else cout<<"输入错误，请重新输入"<<endl;
    }
    delete []tem;
    delete []option;
}
void Buyer::ListCom(){
    string cmd="SELECT * FROM commodity";
    sql->read(cmd,1);
    cout<<endl;
}
void Buyer::BuyCom(){
    char ID[5],number[10];
    cout<<"请输入商品ID: ";
    cin.getline(ID,5);
    cout<<"请输入购买数量: ";
    cin.getline(number,10);
    int com_id = com->Find(ID);
    if(com_id==-1) cout<<"没有您想要的商品!"<<endl;
    else if(com_id==-2) cout<<"你不能购买你自己的商品!"<<endl;
    else{
        int n1=strtol(com->commodity[com_id].number,NULL,10);
        int n2=strtol(number,NULL,10);
        double price=strtod(com->commodity[com_id].price,NULL);
        if(n2<=0) cout<<"请输入正确的商品数量! "<<endl;
        else if(n1<n2) cout<<"上架商品数量不够! "<<endl;
        else{
            double remain=strtod(use->user[user_id].money,NULL);
            if(remain<price*n1) {
                cout<<"您的余额不够! "<<endl;
                cout<<"请选择(1.返回到买家主界面 2.充值): ";
                char tem[8];
                cin.getline(tem,8);
                if(strcmp("1",tem)==0) return;
                else peo->AddCredit();
            }
            else{
                // update commodity.txt order.txt
                string cmd="UPDATE commodity SET 数量=";
                char tem[10];
                sprintf(tem,"%d",n1-n2);
                cmd.append(tem);
                cmd.append(" WHERE 商品ID=");
                cmd.append(ID);
                sql->read(cmd,0);
                cmd="UPDATE user SET 钱包余额=";
                sprintf(tem,"%.1f",remain-price*n2);
                cmd.append(tem);
                cmd.append(" WHERE 用户ID=");
                cmd.append(u);
                sql->read(cmd,0);
                // insert order.txt
                cmd="INSERT INTO order VALUES (";
                sprintf(tem,"T%03d",ord->num+1);
                cmd.append(tem);
                cmd.push_back(',');
                cmd.append(ID);
                cmd.push_back(',');
                cmd.append(com->commodity[com_id].price);
                cmd.push_back(',');
                cmd.append(number);
                cmd.push_back(',');
                cmd.append(date);
                cmd.push_back(',');
                cmd.append(com->commodity[com_id].sellerID);
                cmd.push_back(',');
                cmd.append(u);
                cmd.push_back(')');
                sql->read(cmd,0);
                SPLITSTAR(30);
                cout<<"交易提醒!"<<endl;
                cout<<"交易时间: "<<date<<endl;
                printf("交易单价: %.1f\n",price);
                printf("交易数量: %d\n",n2);
                printf("交易状态: 交易成功!\n");
                printf("您的余额: %.1f\n",remain-price*n2);
                SPLITSTAR(30);
                cout<<endl;
            }
        }
    }
}
void Buyer::SearchCom() {
    string cmd="SELECT * FROM commodity WHERE 名称 CONTAINS ";
    char name[20];
    cout<<"请输入商品名称: ";
    cin.getline(name,20);
    cmd.append(name);
    sql->read(cmd,1);
    cout<<endl;
}
void Buyer::ShowDetailCom() {
    string cmd="SELECT * FROM commodity WHERE 商品ID CONTAINS ";
    char ID[5];
    cout<<"请输入商品ID: ";
    cin.getline(ID,5);
    cmd.append(ID);
    sql->read(cmd,3);
    cout<<endl;
}
void Buyer::HistoryOrder() {
    string cmd="SELECT * FROM order WHERE 买家ID CONTAINS ";
    cmd.append(u);
    sql->read(cmd,1);
    cout<<endl;
}

void Seller::sellermain() {
    char *option=new char[32];
    char *tem=new char[20];
    while(true){
        SPLITLINE(75);
        cout<<"1.查看商品列表 2.购买商品 3.搜索商品 4.查看历史订单 5.查看商品详细信息 6.返回用户主界面"<<endl;
        SPLITLINE(75);
        cout<<endl<<"请输入操作: ";
        string cmd;
        cin.getline(option,32);
        if(strcmp(option,"1")==0){
            Release();
        } else if(strcmp(option,"2")==0){
            Show_R();
        } else if(strcmp(option,"3")==0){
            EditCom();
        } else if(strcmp(option,"4")==0){
            RemoveCom();
        } else if(strcmp(option,"5")==0){
            HistoryOrder();
        } else if(strcmp(option,"6")==0){
            break;
        } else cout<<"输入错误，请重新输入"<<endl;
    }
    delete []tem;
    delete []option;
}
void Seller::Release() {
    string cmd;
    char c[512];
    string name, price, number, decription;
    cout << "请输入商品名称，不超过20字符: " << endl;
    cin >> name;
    if (name.size() >= 20) {
        cout << "输入长度过长" << endl;
        return;
    }
    cout << "请输入商品价格，不超过8字符，精确到小数点后一位: " << endl;
    cin >> price;
    if (price.size() >= 10) {
        cout << "输入长度过长" << endl;
        return;
    }
    cout << "请输入商品数量，不超过8字符: " << endl;
    cin >> number;
    if (number.size() >= 10) {
        cout << "输入长度过长" << endl;
        return;
    }
    cout << "请输入商品数量，不超过70字符: " << endl;
    cin >> decription;
    if (number.size() >= 70) {
        cout << "输入长度过长" << endl;
        return;
    }
    sprintf(c, "INSERT INTO commodity VALUES (M%03d,%s,%s,%s,%s,%s,%s,销售中)", com->num + 1, name.c_str(), price.c_str(),
            number.c_str(), decription.c_str(), u, date);
    cmd = c;
    cout << "请确认输入无误! " << endl;
    SPLITSTAR(30);
    cout << "商品名称: " << name << endl;
    cout << "商品数量: " << number << endl;
    cout << "商品价格: " << price << endl;
    cout << "商品描述: " << decription << endl;
    cout << endl;
    cout << "你确认要发布该商品吗?(y/n):";
    cin >> c;
    SPLITSTAR(30);
    while (strcmp(c, "y") != 0 || strcmp(c, "n") != 0) {
        cout << "你的输入有误，请重新输入(y/n)";
        cin >> c;
    }
    if (strcmp(c, "y") == 0) {
        sql->read(cmd, 0);
        cout<<"商品发布成功!"<<endl;
    }
}
void Seller::Show_R() {
    string cmd;
    char c[256];
    sprintf(c,"SELECT * FROM commodity WHERE 卖家ID CONTAINS %s",u);
    cmd=c;
    sql->read(cmd,2);
    cout<<endl;
}
void Seller::EditCom() {
    string ID,opt,change,cmd;
    char c[512];
    cout<<"请输入被修改商品的ID: ";
    cin>>ID;
    int com_id = com->Find_Seller(ID.c_str());
    if(com_id==-1)  {cout<<"商品不存在!"<<endl;return;}
    cout<<"请输入要修改商品的属性(1.价格 2.描述 3.数量): ";
    cin>>opt;
    if(opt=="1"){
        cout<<"请输入新的价格，不超过8字符，精确到小数点后一位:";
        cin>>change;
        cout<<"请确认商品修改信息无误!"<<endl;
        SPLITSTAR(30);
        cout<<"商品ID: "<<ID<<endl;
        cout<<"商品名称: "<<com->commodity[com_id].Name<<endl;
        cout<<"商品价格: "<<change<<endl;
        cout<<"商品数量: "<<com->commodity[com_id].number<<endl;
        cout<<"商品描述: "<<com->commodity[com_id].description<<endl;
        SPLITSTAR(30);
        cout<<"确认修改?(y/n)";
        cin>>opt;
        while(opt!="y"&&opt!="n") cin>>opt;
        if(opt=="y"){
            sprintf(c,"UPDATE commodity SET 价格=%s WHERE 商品ID=%s",change.c_str(),ID.c_str());
        }
    } else if(opt=="2"){
        cout<<"请输入新的描述，不超过70字符:";
        cin>>change;
        cout<<"请确认商品修改信息无误!"<<endl;
        SPLITSTAR(30);
        cout<<"商品ID: "<<ID<<endl;
        cout<<"商品名称: "<<com->commodity[com_id].Name<<endl;
        cout<<"商品价格: "<<com->commodity[com_id].price<<endl;
        cout<<"商品数量: "<<com->commodity[com_id].number<<endl;
        cout<<"商品描述: "<<change<<endl;
        SPLITSTAR(30);
        cout<<"确认修改?(y/n)";
        cin>>opt;
        while(opt!="y"&&opt!="n") cin>>opt;
        if(opt=="y"){
            sprintf(c,"UPDATE commodity SET 描述=%s WHERE 商品ID=%s",change.c_str(),ID.c_str());
        }
    } else if(opt=="3"){
        cout<<"请输入新的数量，不超过8字符:";
        cin>>change;
        cout<<"请确认商品修改信息无误!"<<endl;
        SPLITSTAR(30);
        cout<<"商品ID: "<<ID<<endl;
        cout<<"商品名称: "<<com->commodity[com_id].Name<<endl;
        cout<<"商品价格: "<<com->commodity[com_id].price<<endl;
        cout<<"商品数量: "<<change<<endl;
        cout<<"商品描述: "<<com->commodity[com_id].description<<endl;
        SPLITSTAR(30);
        cout<<"确认修改?(y/n)";
        cin>>opt;
        while(opt!="y"&&opt!="n") cin>>opt;
        if(opt=="y"){
            sprintf(c,"UPDATE commodity SET 数量=%s WHERE 商品ID=%s",change.c_str(),ID.c_str());
        }
    } else cout<<"输入错误"<<endl;
    cmd=c;
    sql->read(cmd,0);
}
void Seller::RemoveCom() {
    cout<<"请输入要下架的商品ID: ";
    string ID;
    cin>>ID;
    int com_id = com->Find_Seller(ID.c_str());
    if(strcmp(com->commodity[com_id].sellerID,u)!=0) cout<<"只能下架你自己的商品"<<endl;
    else{
        cout<<"确认要删除该商品吗?"<<endl;
        SPLITSTAR(80);
        com->Printhead(0);
        for(int i=0;i<COM_NUM;i++){
            char *ptr = (char *)&com->commodity[com_id];
            if(i==4){ptr+=com_table[i];continue;}
            printf("%s", ptr);
            int j = com_print_table[i] - len(ptr);
            for (; j > 0; j--) printf(" ");
            ptr += com_table[i];
        }
        SPLITSTAR(80);
        cout<<"请选择(y/n)";
        string opt;
        cin>>opt;
        while(opt!="y"&&opt!="n") cin>>opt;
        string cmd="DELETE FROM commodity WHERE 商品ID=";
        cmd.append(ID);
        sql->read(cmd,0);
        cout<<endl;
    }
}
void Seller::HistoryOrder() {
    string cmd = "SELECT * FROM order WHERE 卖家ID CONTAINS ";
    cmd.append(u);
    sql->read(cmd,2);
    cout<<endl;
}