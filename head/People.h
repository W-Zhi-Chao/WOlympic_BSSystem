#ifndef WOLYMPIC_BSSYSTEM_PEOPLE_H
#define WOLYMPIC_BSSYSTEM_PEOPLE_H
// Buyer and Seller should be inherentted from People
class People{
public:
    int user_id;
    char u[5];
    void Signin(char *id,char *passwd);
    void Signup();
    void Showinfo();
    void Editinfo();
    void AddCredit();
    void peoplemain();
    void manageinfo();
};
class Buyer{
public:
    int user_id;
    char u[5];
    void buyermain();
    void ListCom();
    void BuyCom();
    void SearchCom();
    void HistoryOrder();
    void ShowDetailCom();
};
class Seller{
public:
    int user_id;
    char u[5];
    void sellermain();
    void Release();
    void Show_R();
    void EditCom();
    void RemoveCom();
    void HistoryOrder();
};
#endif
