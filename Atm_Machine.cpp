#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

#ifdef _WIN32
    #define CLEAR_SCREEN "cls"
#else
    #define CLEAR_SCREEN "clear"
#endif

struct Transaction {
    string type;
    double amount;
};

double balance = 5000.00;
int pin = 4321;
vector<Transaction> transactions;

void clearScreen() {
    system(CLEAR_SCREEN);
}

void showMenu() {
    cout << "\n🏧 Welcome to ATM\n";
    cout << "--------------------------------\n";
    cout << " 1️⃣  Check Balance 💰\n";
    cout << " 2️⃣  Deposit Money 💵\n";
    cout << " 3️⃣  Withdraw Money 💸\n";
    cout << " 4️⃣  Mini Statement 📜\n";
    cout << " 5️⃣  Change PIN 🔑\n";
    cout << " 6️⃣  Exit 🚪\n";
    cout << "--------------------------------\n";
    cout << "👉 Enter your choice: ";
}

void checkBalance() {
    cout << "\n💰 Your current balance: ₹" << balance << endl;
}

void deposit() {
    double amount;
    cout << "\n💵 Enter deposit amount: ₹";
    cin >> amount;
    if (amount > 0) {
        balance += amount;
        transactions.push_back({"Deposit", amount});
        cout << "✅ Deposited ₹" << amount << " successfully!\n";
    } else {
        cout << "❌ Invalid amount!\n";
    }
}

void withdraw() {
    double amount;
    cout << "\n💸 Enter withdrawal amount: ₹";
    cin >> amount;
    if (amount > 0 && amount <= balance) {
        balance -= amount;
        transactions.push_back({"Withdraw", amount});
        cout << "✅ Withdrawn ₹" << amount << " successfully!\n";
    } else {
        cout << "❌ Insufficient funds or invalid amount!\n";
    }
}

void miniStatement() {
    cout << "\n📜 Last 5 Transactions 📜\n";
    if (transactions.empty()) {
        cout << "No transactions yet.\n";
    } else {
        int start = transactions.size() > 5 ? transactions.size() - 5 : 0;
        for (size_t i = start; i < transactions.size(); i++) {
            cout << "🔹 " << transactions[i].type << ": ₹" << transactions[i].amount << endl;
        }
    }
}

void changePin() {
    int oldPin, newPin;
    cout << "\n🔑 Enter current PIN: ";
    cin >> oldPin;
    if (oldPin == pin) {
        cout << "🔑 Enter new PIN: ";
        cin >> newPin;
        pin = newPin;
        cout << "✅ PIN changed successfully!\n";
    } else {
        cout << "❌ Incorrect PIN!\n";
    }
}

bool authenticate() {
    int inputPin, attempts = 3;
    while (attempts > 0) {
        cout << "\n🔐 Enter PIN to continue: ";
        cin >> inputPin;
        if (inputPin == pin) {
            return true;
        } else {
            attempts--;
            cout << "❌ Incorrect PIN! Attempts left: " << attempts << endl;
        }
    }
    return false;
}

int main() {
    if (!authenticate()) {
        cout << "\n🚫 Too many failed attempts! Exiting...\n";
        return 1;
    }

    int choice;
    do {
        clearScreen();
        showMenu();
        cin >> choice;
        clearScreen();

        switch (choice) {
            case 1: checkBalance(); break;
            case 2: deposit(); break;
            case 3: withdraw(); break;
            case 4: miniStatement(); break;
            case 5: changePin(); break;
            case 6: cout << "🙏 Thank you for using our ATM! Have a great day! 😊\n"; break;
            default: cout << "⚠️ Invalid choice! Try again.\n";
        }

        if (choice != 6) {
            cout << "\n🔄 Press Enter to return to the menu...";
            cin.ignore();
            cin.get();
        }

    } while (choice != 6);

    return 0;
}
