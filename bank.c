#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void create_account();
void deposit_money();
void withdraw_money();
void check_balance();

typedef struct
{
    char name[50];
    int acc_no;
    float balance;

} account;
const char *account_file = "account.dat";

void create_account()
{
    account acc;
    FILE *file = fopen(account_file, "ab+");
    if (file == NULL)
    {
        printf("\nunable to open file!!");
        return;
    }
    char c;
    do
    {
        c = getchar();
    } while (c != '\n' && c != EOF);

    printf("\nEnter your name :");
    fgets(acc.name, sizeof(acc.name), stdin);
    int ind = strcspn(acc.name, "\n");
    acc.name[ind] = '\0';
    printf("\nenter your account number :");
    scanf("%d", &acc.acc_no);
    acc.balance = 0;

    fwrite(&acc, sizeof(acc), 1, file);
    fclose(file);
    printf("\n Account created succesfully!");
}
void deposit_money()
{
    FILE *file = fopen(account_file, "rb+");
    if (file == NULL)
    {
        printf("\nunable to open the account !");
        return;
    }
    int acc_no;
    float money;
    account acc_read;
    printf("\nenter your account number :");
    scanf("%d", &acc_no);
    printf("\nEnter the amount to deposit :");
    scanf("%f", &money);
    while (fread(&acc_read, sizeof(acc_read), 1, file))
    {
        if (acc_read.acc_no == acc_no)
        {
            acc_read.balance += money;
            fseek(file, -sizeof(acc_read), SEEK_CUR);
            fwrite(&acc_read, sizeof(acc_read), 1, file);
            fclose(file);
            printf("successfully deposited Rs. %.2f new balance is Rs.%.2f", money, acc_read.balance);
            return;
        }
    }

    fclose(file);
    printf("account number %d not found in records", acc_no);
}
void withdraw_money()
{
    FILE *file = fopen(account_file, "rb+");
    if (file == NULL)
    {
        printf("unable to open the acoount  file !!!\n");
        return;
    }
    int acc_no;
    float money;
    account acc_read;
    printf("\nenter your acoount number: ");
    scanf("%d", &acc_no);
    printf("\nenter the money you want to withdraw : ");
    scanf("%f", &money);
    while (fread(&acc_read, sizeof(acc_read), 1, file))
    {
        if (acc_read.acc_no==acc_no)
        {
            if (acc_read.balance >= money)
            {
                acc_read.balance -= money;
                fseek(file, -sizeof(acc_read), SEEK_CUR);
                fwrite(&acc_read, sizeof(acc_read), 1, file);
                printf("\nsuccessfully withdraw Rs.%.2f remauning balance is Rs.%.2f", money, acc_read.balance);
            }
            else
            {
                printf("\ninsufficient balance!");
            }
            fclose(file);
            return;
        }
    }
    fclose(file);
    printf("\nmoney could not be withdraw as the account no %d was not found in records ", acc_no);
}
void check_balance()
{
    FILE *file = fopen(account_file, "rb");
    if (file == NULL)
    {
        printf("\nunable to open file!!");
        return;
    }
    int acc_no;
    account acc_read;
    printf("\nenter your account number :");
    scanf("%d", &acc_no);
    while (fread(&acc_read, sizeof(acc_read), 1, file))
    {
        if (acc_read.acc_no == acc_no)
        {
            printf("\nyour current account balance is RS.%.2f", acc_read.balance);
            fclose(file);
            return;
        }
    }
    fclose(file);
    printf("\nAccount NO: %d was not found.\n", acc_no);
}

int main()
{
    while (1)
    {
        int choice;
        printf("\n\n*** Bank management system ***");
        printf("\n1.Create account");
        printf("\n2.Deposit Money");
        printf("\n3.Withdraw money");
        printf("\n4.Check balance");
        printf("\n5.Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            create_account();
            break;
        case 2:
            deposit_money();
            break;
        case 3:
            withdraw_money();
            break;
        case 4:
            check_balance();
            break;
        case 5:
            printf("\nClosing the bank\nthaks for visting us\n");
            return 0;
            break;

        default:
            printf("Invalid choice!");
            break;
        }
    }
}
//account 123
//456
//0609
// monthaly balance 789
