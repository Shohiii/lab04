#include "Account.h"
#include <stdexcept>

Account::Account(int id, int balance) : id(id), balance(balance), is_locked(false) {}

int Account::GetBalance() const { return balance; }

void Account::ChangeBalance(int diff) {
    if (!is_locked) throw std::runtime_error("Account is not locked");
    balance += diff;
}

void Account::Lock() { is_locked = true; }

void Account::Unlock() { is_locked = false; }
