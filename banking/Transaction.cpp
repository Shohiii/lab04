#include "Transaction.h"
bool Transaction::Make(Account& from, Account& to, int sum) {
    if (sum <= 0) return false;
    if (from.GetBalance() < sum) return false;
    from.Lock();
    to.Lock();
    from.ChangeBalance(-sum);
    to.ChangeBalance(sum);
    from.Unlock();
    to.Unlock();
    return true;
}
