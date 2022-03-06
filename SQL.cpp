#include "head/SQL.h"
#include "head/Commodity.h"
extern Commodity com;
extern Order ord;
void SQL::read(string &cmd,int identity) {
    vector<string> res = split(cmd," ");
    if(res.at(0)=="INSERT"){
        assert(res.size()==4&&"INSERT命令格式错误");
        res.at(4).erase(res.at(4).begin());
        res.at(4).erase(res.at(4).end()-1);
        INSERT(res.at(2),res.at(4),identity);
    } else if(res.at(0)=="DELETE"){
        assert(res.size()==5&&"DELETE命令格式错误");
        string tem = res.at(4);
        string::size_type pos=tem.find("=");
        string tem1 = tem.substr(0,pos);
        string tem2 = tem.substr(pos+1);
        cout<<tem1<<" "<<tem2<<endl;
        DELETE(res.at(2),tem2,tem1,identity);
    } else if(res.at(0)=="UPDATE"){
        assert(res.size()==6&&"UPDATE命令格式错误");
        string tem = res.at(5);
        string::size_type pos=tem.find("=");
        string tem1 = tem.substr(0,pos);
        string tem2 = tem.substr(pos+1);
        cout<<tem1<<" "<<tem2<<endl;
        UPDATE(res.at(1),tem2,tem1,res.at(3),identity);
    } else if(res.at(0)=="SELECT"){
        assert((res.size()==4||res.size()==8)&&"SELECT命令格式错误");
        if(res.size()>4){
            SELECT(res.at(3), res.at(7), res.at(5), identity);
        } else{
            string empty = "";
            SELECT(res.at(3),empty, empty,identity);
        }
    } else assert(0&&"他奶奶的,这你都能错\n");
}
void SQL::INSERT(string &name, string &value, int identity) {
    if(name=="commodity"){
        com.Insert(value,identity);
    } else if(name=="order"){

    } else if(name=="user"){

    }
}
void SQL::SELECT(string &name, string &value,string &attribute, int identity){
    if(name=="commodity"){
        com.Select(value,attribute,identity);
    } else if(name=="order"){

    } else if(name=="user"){

    }
}
void SQL::DELETE(string &name, string &value, string &attribute, int identity) {
    if(name=="commodity"){
        com.Delete(value,attribute,identity);
    } else if(name=="order"){

    } else if(name=="user"){

    }
}
void SQL::UPDATE(string &name, string &value, string &attribute, string &set, int identity) {
    if(name=="commodity"){
        com.Update(value,attribute,set,identity);
    } else if(name=="order"){

    } else if(name=="user"){

    }
}