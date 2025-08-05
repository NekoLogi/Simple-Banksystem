#ifndef BANK_H
#define BANK_H

#include <stdio.h>
#include <stdlib.h>

typedef enum transaction_type
{
    WITHDRAW,
    DEPOSIT,
    TRANSFER_FROM,
    TRANSFER_TO
} transaction_type;

/// @brief Represents information of a transaction.
typedef struct Transaction
{
    long id;
    long double amount;
} Transaction;

/// @brief Represents information of a transaction history.
/// @warning Variable next should be ignored, modifying it manually could cause undefine behaviour.
typedef struct History
{
    Transaction *transaction;
    transaction_type type;
    long double balance;

    struct History *next; // Required for utlist
} History;

/// @brief Represents a bank account.
/// @warning Variable next should be ignored, modifying it manually could cause undefine behaviour.
typedef struct Bank
{
    long id;
    char *firstName;
    char *lastName;
    char *country;
    char *city;
    char *street;
    long double balance;
    struct History *history;

    struct Bank *next; // Required for utlist
} Bank;

/// @brief Represents a list of bank accounts.
/// @warning Do not free this variable manually, use remove_account to properly delete and free accounts.
extern Bank *accounts;

/// @brief Transfers an amount from the sender to the receiver account.
/// @param sender Pointer to a Transaction struct containing sender info.
/// @param receiver_id ID of the receiving account.
/// @return 0 if transaction is successful, 1 if it fails.
int transfer(Transaction *sender, long receiver_id);

/// @brief Converts balance amount to real currency.
/// @param user A Pointer to a struct containing transaction data.
/// @return 0 if transaction is successful, 1 if it fails.
int withdraw(Transaction *user);

/// @brief Converts real currency to digital currency and adds into balance of the user.
/// @param user A Pointer to a struct containing transaction data.
/// @return 0 if transaction is successful, 1 if it fails.
int deposit(Transaction *user);

/// @brief Adds a bank account into the struct pointer named accounts.
/// @param account Pointer to a Bank struct containing bank account info.
/// @return 0 if creation is successful, 1 if it fails.
int add_account(Bank *account);

/// @brief Removes a bank account from the struct pointer named accounts.
/// @param id ID of the bank account.
/// @return 0 if deletion is successful, 1 if it fails.
/// @warning This function will free the memory of the removed account.
int remove_account(long id);

/// @brief Searches for a bank account.
/// @param id ID of the bank account.
/// @return Pointer to a Bank struct containing bank account info, Null if the account doesn't exist.
Bank *get_account(long id);

/// @brief Print out the whole transaction history from a bank account.
/// @param id ID of the bank account.
/// @return 0 if print is successful, 1 if it fails.
int get_history(long id);

#endif