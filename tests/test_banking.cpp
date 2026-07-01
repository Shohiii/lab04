#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../banking/Account.h"
#include "../banking/Transaction.h"

class MockAccount : public Account {
public:
    MockAccount(int id, int balance) : Account(id, balance) {}
    MOCK_CONST_METHOD0(GetBalance, int());
    MOCK_METHOD1(ChangeBalance, void(int diff));
    MOCK_METHOD0(Lock, void());
    MOCK_METHOD0(Unlock, void());
};

TEST(AccountTest, BasicOperations) {
    Account acc(1, 100);
    EXPECT_EQ(acc.GetBalance(), 100);
    EXPECT_THROW(acc.ChangeBalance(50), std::runtime_error);
    acc.Lock();
    acc.ChangeBalance(50);
    EXPECT_EQ(acc.GetBalance(), 150);
    acc.Unlock();
}
TEST(TransactionTest, InvalidSum) {
    Account from(1, 100);
    Account to(2, 100);
    Transaction tr;
    EXPECT_FALSE(tr.Make(from, to, 0));
    EXPECT_FALSE(tr.Make(from, to, -50));
}

TEST(TransactionTest, InsufficientFunds) {
    Account from(1, 50);
    Account to(2, 100);
    Transaction tr;
    EXPECT_FALSE(tr.Make(from, to, 100));
}

TEST(TransactionTest, SuccessfulTransferWithMock) {
    MockAccount from(1, 500);
    MockAccount to(2, 500);
    Transaction tr;
    EXPECT_CALL(from, GetBalance()).WillRepeatedly(::testing::Return(500));
    EXPECT_CALL(from, Lock()).Times(1);
    EXPECT_CALL(to, Lock()).Times(1);
    EXPECT_CALL(from, ChangeBalance(-100)).Times(1);
    EXPECT_CALL(to, ChangeBalance(100)).Times(1);
    EXPECT_CALL(from, Unlock()).Times(1);
    EXPECT_CALL(to, Unlock()).Times(1);
    EXPECT_TRUE(tr.Make(from, to, 100));
}
