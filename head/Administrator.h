#ifndef WOLYMPIC_BSSYSTEM_ADMINISTRATOR_H
#define WOLYMPIC_BSSYSTEM_ADMINISTRATOR_H
class Administrator{
public:
    char ID[20];
    char passwd[20];
    char target[256];
    void Init();
    void admin_main();
    void Signin(const char *name, const char *passwd);
};
#endif
