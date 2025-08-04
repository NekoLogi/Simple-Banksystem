#include <stdio.h>

/// @brief A struct that defines transaction data for processing.
typedef struct
{
    long id;
    long double amount;
    Transaction *account;
} Transaction;

/// @brief A struct that defines Account data.
typedef struct
{
    long id;
    const char *firstName;
    const char *lastName;
    const char *country;
    const char *city;
    const char *street;
    long double balance;
} Bank;

typedef struct
{
    Bank *account;
    Account *prev;
    Account *next;
} Account;

/// @brief transfer amount of currency to another account/user.
/// @param sender a struct that defines transaction data.
/// @param receiver_id id of receiving account.
/// @return 0 if transaction successful | 1 if transaction failed.
int transfer(Transaction *sender, long receiver_id)
{
}

/// @brief convert balance amount to real currency.
/// @param user a struct that defines transaction data.
/// @return 0 if transaction successful | 1 if transaction failed.
int withdraw(Transaction *user)
{
}

/// @brief convert real currency amount to digital and adds into balance.
/// @param user a struct that defines transaction data.
/// @return 0 if transaction successful | 1 if transaction failed.
int deposit(Transaction *user)
{
}