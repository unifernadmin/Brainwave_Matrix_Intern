#include <stdio.h>
#include <string.h>

#define MAX_ACCOUNTS 100

typedef struct {
    char name[50];
    int accountNumber;
    int pin;
    double balance;
} Account;

Account accounts[MAX_ACCOUNTS];
int accountCount = 0;
int currentAccountIndex = -1;

void createAccount() {
    if (accountCount >= MAX_ACCOUNTS) {
        printf("❌ Cannot create more accounts!\n");
        return;
    }

    Account newAccount;
    printf("Enter Name: ");
    getchar();  
    fgets(newAccount.name, 50, stdin);
    newAccount.name[strcspn(newAccount.name, "\n")] = '\0';

    newAccount.accountNumber = 1000 + accountCount;
    printf("Set a 4-digit PIN: ");
    scanf("%d", &newAccount.pin);
    newAccount.balance = 0;

    accounts[accountCount++] = newAccount;

    printf("\n✅ Account Created Successfully!\n");
    printf("📌 Your Account Number: %d\n", newAccount.accountNumber);
}

void loginAccount() {
    int accountNumber, pin;
    printf("Enter Account Number: ");
    scanf("%d", &accountNumber);
    printf("Enter PIN: ");
    scanf("%d", &pin);

    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == accountNumber && accounts[i].pin == pin) {
            currentAccountIndex = i;
            printf("\n✅ Login Successful! Welcome, %s!\n", accounts[i].name);
            return;
        }
    }
    printf("❌ Invalid Account Number or PIN!\n");
}

void deposit() {
    if (currentAccountIndex == -1) {
        printf("❌ Please login first!\n");
        return;
    }
    
    double amount;
    printf("Enter Deposit Amount: ₹");
    scanf("%lf", &amount);
    
    if (amount > 0) {
        accounts[currentAccountIndex].balance += amount;
        printf("\n✅ ₹%.2lf Deposited Successfully!\n", amount);
    } else {
        printf("❌ Invalid Amount!\n");
    }
}

void withdraw() {
    if (currentAccountIndex == -1) {
        printf("❌ Please login first!\n");
        return;
    }

    double amount;
    printf("Enter Withdrawal Amount: ₹");
    scanf("%lf", &amount);

    if (amount > 0 && amount <= accounts[currentAccountIndex].balance) {
        accounts[currentAccountIndex].balance -= amount;
        printf("\n✅ ₹%.2lf Withdrawn Successfully!\n", amount);
    } else {
        printf("❌ Insufficient Balance or Invalid Amount!\n");
    }
}

void transferMoney() {
    if (currentAccountIndex == -1) {
        printf("❌ Please login first!\n");
        return;
    }

    int receiverAccount;
    double amount;
    printf("Enter Receiver's Account Number: ");
    scanf("%d", &receiverAccount);
    printf("Enter Transfer Amount: ₹");
    scanf("%lf", &amount);

    if (amount <= 0 || amount > accounts[currentAccountIndex].balance) {
        printf("❌ Insufficient Balance or Invalid Amount!\n");
        return;
    }

    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == receiverAccount) {
            accounts[currentAccountIndex].balance -= amount;
            accounts[i].balance += amount;
            printf("\n✅ ₹%.2lf successfully transferred to %s!\n", amount, accounts[i].name);
            return;
        }
    }
    printf("❌ Receiver Account Not Found!\n");
}

void accountSummary() {
    if (currentAccountIndex == -1) {
        printf("❌ Please login first!\n");
        return;
    }

    printf("\n💳 Account Summary:\n");
    printf("👤 Name: %s\n", accounts[currentAccountIndex].name);
    printf("🏦 Account Number: %d\n", accounts[currentAccountIndex].accountNumber);
    printf("💰 Balance: ₹%.2lf\n", accounts[currentAccountIndex].balance);
}

void logout() {
    if (currentAccountIndex == -1) {
        printf("❌ No account is currently logged in!\n");
        return;
    }

    printf("\n👋 Logged Out Successfully!\n");
    currentAccountIndex = -1;
}

int main() {
    int choice;

    while (1) {
        printf("\n========== 🏦 ONLINE BANKING SYSTEM 🏦 ==========\n");
        printf("1️⃣ Create Account\n");
        printf("2️⃣ Login\n");
        printf("3️⃣ Deposit Money\n");
        printf("4️⃣ Withdraw Money\n");
        printf("5️⃣ Transfer Money\n");
        printf("6️⃣ Account Summary\n");
        printf("7️⃣ Logout\n");
        printf("8️⃣ Exit\n");
        printf("===============================================\n");
        printf("👉 Enter Your Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createAccount(); break;
            case 2: loginAccount(); break;
            case 3: deposit(); break;
            case 4: withdraw(); break;
            case 5: transferMoney(); break;
            case 6: accountSummary(); break;
            case 7: logout(); break;
            case 8: printf("\n🚪 Exiting... Thank You!\n"); return 0;
            default: printf("❌ Invalid Choice! Try Again.\n");
        }
    }
}
