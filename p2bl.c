// ATM Simulation Program by B.Tech CSE Student 

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TXN 20
#define INT_CHARGE 2000

// Function declarations
void checkBalance(int balance);
int deposit(int balance, char txn[][50], int *tcount);
int withdraw(int balance, char txn[][50], int *tcount);
int withdrawWithOTP(int balance, char txn[][50], int *tcount, char regMobile[]);
int transferMoney(int balance, char txn[][50], int *tcount);
int getHiddenPin();
void changePin(int *pin);
void showTransactions(char txn[][50], int tcount);

// NEW (File Handling)
void savePin(int pin);
int loadPin();

int main() {
    int pin = loadPin();   // Load saved PIN
    int enteredPin;
    int balance = 5000000;
    int choice;
    int attempts = 3;

    char registeredMobile[11] = "12";
    char transactions[MAX_TXN][50];
    int tcount = 0;

    // PIN verification
    while (attempts > 0) {
        printf("Enter your 4-digit ATM PIN: ");
        enteredPin = getHiddenPin();

        if (enteredPin == pin)
            break;
        else {
            attempts--;
            printf("\nWrong PIN! Attempts left: %d\n", attempts);
        }
    }

    if (attempts == 0) {
        printf("Card blocked! Too many wrong attempts.\n");
        return 0;
    }

    // ATM Menu
    do {
        printf("\n\n===== ATM MENU =====");
        printf("\n \n1. Check Balance");
        printf("\n \n2. Deposit Money");
        printf("\n \n3. Withdraw Money");
        printf("\n \n4. Withdraw with Mobile OTP");
        printf("\n \n5. Transaction History");
        printf("\n \n6. Transfer Money");
        printf("\n \n7. Change PIN");
        printf("\n \n8. Exit");
        printf("\n \n Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                checkBalance(balance);
                break;
            case 2:
                balance = deposit(balance, transactions, &tcount);
                break;
            case 3:
                balance = withdraw(balance, transactions, &tcount);
                break;
            case 4:
                balance = withdrawWithOTP(balance, transactions, &tcount, registeredMobile);
                break;
            case 5:
                showTransactions(transactions, tcount);
                break;
            case 6:
                balance = transferMoney(balance, transactions, &tcount);
                break;
            case 7:
                changePin(&pin);
                break;
            case 8:
                printf("Thank you for using ATM!\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 8);

    return 0;
}

// Hidden PIN input
int getHiddenPin() {
    int pin = 0;
    char ch;
    int count = 0;

    while (1) {
        ch = getch();

        if (ch == 13) {
            if (count == 4)
                break;
            else {
                printf("\nPIN must be exactly 4 digits!\nRe-enter PIN: ");
                pin = 0;
                count = 0;
            }
        }

        if (ch >= '0' && ch <= '9' && count < 4) {
            pin = pin * 10 + (ch - '0');
            count++;
            printf(" * ");
        }
    }
    return pin;
}

// Check balance
void checkBalance(int balance) {
    printf("Your current balance is: %d\n", balance);
}

// Deposit
int deposit(int balance, char txn[][50], int *tcount) {
    int amount;
    printf("Enter amount to deposit: ");
    scanf("%d", &amount);

    if (amount > 0) {
        balance += amount;
        if (*tcount < MAX_TXN) {
            sprintf(txn[*tcount], "Deposited %d", amount);
            (*tcount)++;
        }
        printf("Deposit successful.\n");
    } else {
        printf("Invalid amount!\n");
    }
    return balance;
}

// Withdraw
int withdraw(int balance, char txn[][50], int *tcount) {
    int amount, type, total;

    printf("\n1. Domestic Withdrawal");
    printf("\n2. International Withdrawal");
    printf("\nChoose type: ");
    scanf("%d", &type);

    printf("Enter amount: ");
    scanf("%d", &amount);

    if (amount <= 0) {
        printf("Invalid amount!\n");
        return balance;
    }

    if (type == 1)
        total = amount;
    else if (type == 2)
        total = amount + INT_CHARGE;
    else {
        printf("Invalid option!\n");
        return balance;
    }

    if (total <= balance) {
        balance -= total;
        if (*tcount < MAX_TXN) {
            sprintf(txn[*tcount], "Withdraw %d", amount);
            (*tcount)++;
        }
        printf("Please collect your cash.\n");
    } else {
        printf("Insufficient balance!\n");
    }
    return balance;
}

// OTP Withdrawal
int withdrawWithOTP(int balance, char txn[][50], int *tcount, char regMobile[]) {
    char enteredMobile[11];
    int amount, otp, enteredOtp;
    int attempts = 3;

    printf("Enter registered mobile number: ");
    scanf("%s", enteredMobile);

    if (strcmp(enteredMobile, regMobile) != 0) {
        printf("Mobile number not registered!\n");
        return balance;
    }

    printf("Enter amount to withdraw: ");
    scanf("%d", &amount);

    if (amount <= 0 || amount > balance) {
        printf("Invalid amount or insufficient balance!\n");
        return balance;
    }

    srand(time(NULL));
    otp = rand() % 9000 + 1000;

    printf("OTP sent to mobile %s\n", regMobile);
    printf("(Simulation OTP: %d)\n", otp);

    while (attempts > 0) {
        printf("Enter OTP: ");
        scanf("%d", &enteredOtp);

        if (enteredOtp == otp) {
            balance -= amount;

            if (*tcount < MAX_TXN) {
                sprintf(txn[*tcount], "OTP Withdraw %d", amount);
                (*tcount)++;
            }

            printf("OTP verified. Please collect your cash.\n");
            return balance;
        } else {
            attempts--;
            printf("Wrong OTP! Attempts left: %d\n", attempts);
        }
    }

    printf("OTP verification failed. Transaction cancelled.\n");
    return balance;
}

// Transfer Money
int transferMoney(int balance, char txn[][50], int *tcount) {
    char accNo[20];
    int amount;

    printf("Enter receiver account number: ");
    scanf("%s", accNo);

    printf("Enter amount to transfer: ");
    scanf("%d", &amount);

    if (amount <= 0) {
        printf("Invalid amount!\n");
        return balance;
    }

    if (amount > balance) {
        printf("Insufficient balance!\n");
        return balance;
    }

    balance -= amount;

    if (*tcount < MAX_TXN) {
        sprintf(txn[*tcount], "Transfer %d to A/C %s", amount, accNo);
        (*tcount)++;
    }

    printf("Transfer successful to account %s\n", accNo);
    return balance;
}

// Change PIN (Permanent)
void changePin(int *pin) {
    int oldPin, newPin, confirmPin;

    printf("Enter old PIN: ");
    oldPin = getHiddenPin();

    if (oldPin == *pin) {
        printf("\nEnter new PIN: ");
        newPin = getHiddenPin();

        printf("\nConfirm new PIN: ");
        confirmPin = getHiddenPin();

        if (newPin == confirmPin) {
            *pin = newPin;
            savePin(newPin);   // ?? SAVE TO FILE
            printf("\nPIN changed successfully.\n");
        } else {
            printf("\nPIN mismatch! Try again.\n");
        }
    } else {
        printf("\nWrong old PIN!\n");
    }
}

// Show Transactions
void showTransactions(char txn[][50], int tcount) {
    int i;
    if (tcount == 0) {
        printf("No transactions available.\n");
        return;
    }

    printf("\n--- Transaction History ---\n");
    for (i = 0; i < tcount; i++) {
        printf("%d. %s\n", i + 1, txn[i]);
    }
}

// Save PIN to file
void savePin(int pin) {
    FILE *fp = fopen("pin.txt", "w");
    if (fp != NULL) {
        fprintf(fp, "%d", pin);
        fclose(fp);
    }
}

// Load PIN from file
int loadPin() {
    FILE *fp = fopen("pin.txt", "r");
    int pin;

    if (fp != NULL) {
        fscanf(fp, "%d", &pin);
        fclose(fp);
        return pin;
    }

    return 1234; // default PIN
}