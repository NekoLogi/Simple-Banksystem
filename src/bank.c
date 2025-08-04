#include "bank.h"
#include "utlist.h"
#include "utils.h"

Bank *accounts = NULL;
long current_id = 1;

int transfer(Transaction *sender, long receiver_id)
{
    if (sender == NULL)
    {
        return 1;
    }
    if (sender->id == 0)
    {
        return 1;
    }
    if (receiver_id == 0)
    {
        return 1;
    }

    // Sender
    Bank *bank_sender = get_account(sender->id);
    if (bank_sender == NULL)
    {
        return 1;
    }
    if (bank_sender->balance < sender->amount)
    {
        return 1;
    }

    // Receiver
    Bank *bank_receiver = get_account(receiver_id);
    if (bank_receiver == NULL)
    {
        return 1;
    }

    bank_receiver->balance += sender->amount;
    bank_sender->balance -= sender->amount;
    return 0;
}

int withdraw(Transaction *user)
{
    if (user == NULL)
    {
        return 1;
    }
    if (user->id == 0)
    {
        return 1;
    }

    Bank *bank_user = get_account(user->id);
    if (bank_user == NULL)
    {
        return 1;
    }

    bank_user->balance -= user->amount;
    return 0;
}

int deposit(Transaction *user)
{
    if (user == NULL)
    {
        return 1;
    }
    if (user->id == 0)
    {
        return 1;
    }

    Bank *bank_user = get_account(user->id);
    if (bank_user == NULL)
    {
        return 1;
    }

    bank_user->balance += user->amount;
    return 0;
}

int add_account(Bank *account)
{
    if (account == NULL)
    {
        return 1;
    }

    Bank *new_account = malloc(sizeof(Bank));
    new_account->id = current_id;
    current_id++;
    new_account->firstName = my_strdup(account->firstName);
    new_account->lastName = my_strdup(account->lastName);
    new_account->country = my_strdup(account->country);
    new_account->city = my_strdup(account->city);
    new_account->street = my_strdup(account->street);
    new_account->balance = account->balance;
    new_account->history = NULL;
    new_account->next = NULL;

    LL_APPEND(accounts, account);
    return 0;
}

int remove_account(long id)
{
    if (id == 0)
    {
        return 1;
    }

    Bank *account = get_account(id);
    if (account == NULL)
    {
        return 1;
    }

    LL_DELETE(accounts, account);
    free(account);
    account = NULL;
    return 0;
}

Bank *get_account(long id)
{
    if (id == 0)
    {
        return NULL;
    }

    Bank *el;
    LL_FOREACH(accounts, el)
    {
        if (el == NULL)
        {
            continue;
        }

        if (el->id == id)
        {
            return el;
        }
    }
    return NULL;
}

int add_history(Transaction *user, transaction_type type)
{
    if (user == NULL)
    {
        return 1;
    }
    if (user->id == 0)
    {
        return 1;
    }

    Bank *bank_user = get_account(user->id);
    if (bank_user == NULL)
    {
        return 1;
    }

    History *new_history = malloc(sizeof(History));
    new_history->transaction->id = user->id;
    new_history->transaction->amount = user->amount;
    new_history->type = type;
    new_history->balance = bank_user->balance;

    LL_APPEND(bank_user->history, new_history);

    return 0;
}

int get_history(long id)
{
    if (id == 0)
    {
        return 1;
    }

    Bank *bank_user = get_account(id);
    if (bank_user == NULL)
    {
        return 1;
    }

    History *el;
    LL_FOREACH(bank_user->history, el)
    {
        if (el == NULL)
        {
            continue;
        }

        switch ((int)el->type)
        {
        case WITHDRAW:
            printf("---\n");
            printf("Action: Withdraw\n");
            printf("Balance: \t%Lf\n", el->balance);
            printf("Amount: \t-%Lf\n", el->transaction->amount);
            break;

        case DEPOSIT:
            printf("---\n");
            printf("Action: Deposit\n");
            printf("Balance: \t%Lf\n", el->balance);
            printf("Amount: \t+%Lf\n", el->transaction->amount);
            break;

        case TRANSFER_FROM:
            printf("---\n");
            printf("Action: transfer\n");
            printf("From:\n");
            printf("\tID: %ld\n", el->transaction->id);
            Bank *bank_receiver = get_account(el->transaction->id);
            if (bank_user == NULL)
            {
                printf("\tFull Name: %s %s\n", bank_receiver->firstName, bank_receiver->lastName);
            }
            else
            {
                printf("\tFull Name: NOT FOUND\n");
            }
            printf("To:\n");
            printf("\tID: %ld\n", bank_user->id);
            printf("\tFull Name: %s %s\n", bank_user->firstName, bank_user->lastName);
            printf("\tBalance: \t%Lf\n", el->balance);
            printf("\tAmount: \t+%Lf\n", el->transaction->amount);
            break;

        case TRANSFER_TO:
            printf("---\n");
            printf("Action: transfer\n");
            printf("From:\n");
            printf("\tID: %ld\n", bank_user->id);
            printf("\tFull Name: %s %s\n", bank_user->firstName, bank_user->lastName);
            printf("To:\n");
            printf("\tID: %ld\n", el->transaction->id);
            Bank *bank_receiver2 = get_account(el->transaction->id);
            if (bank_user == NULL)
            {
                printf("\tFull Name: %s %s\n", bank_receiver2->firstName, bank_receiver2->lastName);
            }
            else
            {
                printf("\tFull Name: NOT FOUND\n");
            }
            printf("\tBalance: \t%Lf\n", el->balance);
            printf("\tAmount: \t-%Lf\n", el->transaction->amount);
        }
    }
    return 0;
}
