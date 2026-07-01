#ifndef ACCOUNT_H
#define ACCOUNT_H
class Account {
    int id;
    int balance;
    bool is_locked;
public:
    Account(int id, int balance);
    virtual ~Account() = default;
    virtual int GetBalance() const;
    virtual void ChangeBalance(int diff);
    virtual void Lock();
    virtual void Unlock();
};
#endif
