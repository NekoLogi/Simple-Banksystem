#include <stdio.h>
#include "bank.h"
#include <string.h>
#include <ctype.h>

char *next_token;
int maxStringSize = 255;

/// @brief Receives the input of the console.
/// @param prompt If a prompt should be printed before reading the input, set to NULL if no prompt should be printed.
/// @return The user-input of the console.
char *get_input(const char *prompt)
{
    if (prompt != NULL)
    {
        printf("%s: ", prompt);
        fflush(stdout);
    }

    char *input = NULL;
    fgets(input, maxStringSize, stdin);
    if (input == NULL)
    {
        return NULL;
    }

    return input;
}

/// @brief Creates a transaction struct with the previous user-input.
/// @return A pointer to a transaction struct.
Transaction *generate_transaction()
{
    char *token = strtok_s(NULL, " ", &next_token);
    if (token == NULL)
    {
        return NULL;
    }

    // Get User ID
    long user_id = 0;
    sscanf_s(token, "%ld", &user_id);
    if (user_id == 0)
    {
        return NULL;
    }

    token = strtok_s(NULL, " ", &next_token);
    if (token == NULL)
    {
        return NULL;
    }

    // Get transfer amount
    long double amount = 0;
    sscanf_s(token, "%Lf", &amount);
    if (amount == 0)
    {
        return NULL;
    }

    Transaction *action = malloc(sizeof(Transaction));
    action->id = user_id;
    action->amount = amount;

    return action;
}

/// @return 0 if transaction is successful, 1 if it fails.
int handle_withdraw()
{
    Transaction *action = generate_transaction();
    if (action == NULL)
    {
        return 1;
    }
    withdraw(action);
    free(action);
    return 0;
}

/// @return 0 if transaction is successful, 1 if it fails.
int handle_deposit()
{
    Transaction *action = generate_transaction();
    if (action == NULL)
    {
        return 1;
    }
    deposit(action);
    free(action);
    return 0;
}

/// @brief Handles the transfer functionality.
/// @return 0 if transaction is successful, 1 if it fails.
int handle_transfer()
{
    Transaction *action = generate_transaction();
    if (action == NULL)
    {
        return 1;
    }

    char *token = strtok_s(NULL, " ", &next_token);
    if (token == NULL)
    {
        return 1;
    }

    // Get User ID
    long user_id = 0;
    sscanf_s(token, "%ld", &user_id);
    if (user_id == 0)
    {
        return 1;
    }

    transfer(action, user_id);
    free(action);
    return 0;
}

/// @brief Creates a bank struct with new user-input.
/// @return A pointer to a bank struct.
Bank *generate_account()
{
    char *token = strtok_s(NULL, " ", &next_token);
    if (token == NULL)
    {
        return NULL;
    }

    // Get full name
    char *fullName = get_input("Enter full name (first and last)");
    if (fullName == NULL)
    {
        return NULL;
    }

    for (int i = 0; fullName[i]; i++)
    {
        fullName[i] = (char)tolower((unsigned char)fullName[i]);
    }

    token = strtok_s(fullName, " ", &next_token);
    if (token == NULL)
    {
        return NULL;
    }

    token[0] = (char)toupper((char)token[0]);
    char *firstName = NULL;
    strcpy_s(firstName, maxStringSize, token);

    token = strtok_s(NULL, " ", &next_token);
    if (token == NULL)
    {
        return NULL;
    }

    char *lastName = NULL;
    strcpy_s(lastName, maxStringSize, token);

    // Get country
    char *country = get_input("Enter country");
    if (country == NULL)
    {
        return NULL;
    }

    // Get city
    char *city = get_input("Enter city");
    if (city == NULL)
    {
        return NULL;
    }

    // Get street
    char *street = get_input("Enter street");
    if (street == NULL)
    {
        return NULL;
    }

    Bank *account = malloc(sizeof(Bank));
    account->id = 0;
    strcpy_s(account->firstName, maxStringSize, firstName);
    strcpy_s(account->lastName, maxStringSize, lastName);
    strcpy_s(account->country, maxStringSize, country);
    strcpy_s(account->city, maxStringSize, city);
    strcpy_s(account->street, maxStringSize, street);
    account->balance = 0;
    account->history = NULL;

    return account;
}

/// @return 0 if transaction is successful, 1 if it fails.
int handle_new_account()
{
    Bank *account = generate_account();
    if (account == NULL)
    {
        return 1;
    }

    int result = add_account(account);
    free(account);
    return result;
}

/// @return 0 if transaction is successful, 1 if it fails.
int handle_remove_account()
{
    char *token = strtok_s(NULL, " ", &next_token);
    if (token == NULL)
    {
        return 1;
    }

    // Get User ID
    long user_id = 0;
    sscanf_s(token, "%ld", &user_id);
    if (user_id == 0)
    {
        return 1;
    }

    int result = remove_account(user_id);
    return result;
}

/// @return 0 if printing is successful, 1 if it fails.
int handle_get_history()
{
    char *token = strtok_s(NULL, " ", &next_token);
    if (token == NULL)
    {
        return 1;
    }

    // Get User ID
    long user_id = 0;
    sscanf_s(token, "%ld", &user_id);
    if (user_id == 0)
    {
        return 1;
    }

    int result = get_history(user_id);
    return result;
}

/// @param input Requires a string with the user-input.
/// @return 0 if successful, 1 if it fails.
int handle_input(char *input)
{
    if (input == NULL)
    {
        return -1;
    }

    for (int i = 0; input[i]; i++)
    {
        input[i] = (char)tolower((unsigned char)input[i]);
    }

    char *token = strtok_s(input, " ", &next_token);
    while (token != NULL)
    {
        if (strcmp(token, "withdraw") == 0 || strcmp(token, "wd") == 0)
        {
            int result = handle_withdraw();
            if (result == 0)
            {
                return 0;
            }
        }
        else if (strcmp(token, "deposit") == 0 || strcmp(token, "dp") == 0)
        {
            int result = handle_deposit();
            if (result == 0)
            {
                return 0;
            }
        }
        else if (strcmp(token, "transfer") == 0 || strcmp(token, "tf") == 0)
        {
            int result = handle_transfer();
            if (result == 0)
            {
                return 0;
            }
        }
        else if (strcmp(token, "create") == 0 || strcmp(token, "cr") == 0)
        {
            int result = handle_new_account();
            if (result == 0)
            {
                return 0;
            }
        }
        else if (strcmp(token, "remove") == 0 || strcmp(token, "rm") == 0)
        {
            int result = handle_remove_account();
            if (result == 0)
            {
                return 0;
            }
        }
        else if (strcmp(token, "history") == 0 || strcmp(token, "hs") == 0)
        {
            int result = handle_get_history();
            if (result == 0)
            {
                return 0;
            }
        }
        else if (strcmp(token, "help") == 0)
        {
            printf("Available options:\n");
            printf("\t- withdraw or wd\n");
            printf("\t\tExample: withdraw <User ID>\n");
            printf("\t- deposit or dp\n");
            printf("\t\tExample: deposit <User ID>\n");
            printf("\t- transfer or tf\n");
            printf("\t\tExample: transfer <User ID> <Receiver ID> <Amount>\n");
            printf("\t- create or cr\n");
            printf("\t\tExample: create <User ID>\n");
            printf("\t- remove or rm\n");
            printf("\t\tExample: remove <User ID>\n");
            printf("\t- history or hs\n");
            printf("\t\tExample: history <User ID>\n");
            printf("\n\n");
        }
        else if (strcmp(token, "exit") == 0)
        {
            exit(0);
        }

        token = strtok_s(NULL, " ", &next_token);
    }
    return 1;
}

int main()
{
    while (1)
    {
        char *input = get_input("Enter action");
        handle_input(input);
    }
    return 0;
}