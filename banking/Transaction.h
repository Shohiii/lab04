#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "Account.h"

class Transaction {
public:
    bool Make(Account& from, Account& to, int sum);
};

#endif
