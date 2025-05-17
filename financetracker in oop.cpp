#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Transaction {
public:
    string category;
    string date;
    double amount;

    Transaction() {}
    Transaction(string cat, string dt, double amt) {
        category = cat;
        date = dt;
        amount = amt;
    }

    void display() const {
        cout << "Category: " << category << "\nAmount: " << amount << "\nDate: " << date << "\n--------------------\n";
    }
};

class FinanceTracker {
private:
    Transaction transactions[100];
    int transactionCount = 0;
    double total_income = 0;
    double total_expense = 0;

public:
    void addTransaction(int type) {
        string category, date;
        double amount;

        cout << "Enter category: ";
        cin >> category;
        cout << "Enter amount: ";
        cin >> amount;
        cout << "Enter date (DD/MM/YYYY): ";
        cin >> date;

        if (type == 1) total_income += amount;
        else if (type == 2) {
            amount = -amount;
            total_expense += amount;
        }

        transactions[transactionCount] = Transaction(category, date, amount);
        transactionCount++;

        ofstream file("finance_log.txt", ios::app);
        if (file) {
            file << "Category: " << category << "\n";
            file << "Amount: " << amount << "\n";
            file << "Date: " << date << "\n";
            file << "--------------------\n";
            file.close();
        }
        cout << "Transaction added successfully!\n";
    }

    void viewTransactions() {
        if (transactionCount == 0) {
            cout << "No transactions to display.\n";
            return;
        }

        cout << "\nAll Transactions:\n";
        for (int i = 0; i < transactionCount; i++) {
            cout << "Transaction #" << i + 1 << "\n";
            transactions[i].display();
        }
    }

    void editTransaction() {
        int index;
        viewTransactions();
        cout << "Enter transaction number to edit: ";
        cin >> index;
        index--;

        if (index < 0 || index >= transactionCount) {
            cout << "Invalid transaction number.\n";
            return;
        }

        string category, date;
        double amount;

        cout << "Enter new category: ";
        cin >> category;
        cout << "Enter new amount: ";
        cin >> amount;
        cout << "Enter new date (DD/MM/YYYY): ";
        cin >> date;

        // Adjust totals
        if (transactions[index].amount > 0) total_income -= transactions[index].amount;
        else total_expense -= transactions[index].amount;

        if (amount > 0) total_income += amount;
        else total_expense += amount;

        // Update
        transactions[index] = Transaction(category, date, amount);

        cout << "Transaction updated successfully!\n";
    }

    void deleteTransaction() {
        int index;
        viewTransactions();
        cout << "Enter transaction number to delete: ";
        cin >> index;
        index--;

        if (index < 0 || index >= transactionCount) {
            cout << "Invalid transaction number.\n";
            return;
        }

        // Adjust totals
        if (transactions[index].amount > 0) total_income -= transactions[index].amount;
        else total_expense -= transactions[index].amount;

        for (int i = index; i < transactionCount - 1; i++) {
            transactions[i] = transactions[i + 1];
        }
        transactionCount--;

        cout << "Transaction deleted successfully!\n";
    }

    void calculateNetWorth() {
        double netWorth = total_income + total_expense;
        cout << "Net Worth: " << netWorth << "\n";

        ofstream file("finance_log.txt", ios::app);
        if (file.is_open()) {
            file << "Net Worth: " << netWorth << "\n";
            file.close();
        } else {
            cout << "Error: Unable to open file for writing.\n";
        }
    }

    void viewPastTransactionsFromFile() {
        ifstream file("finance_log.txt");
        if (!file) {
            cout << "Error: Unable to open file for reading.\n";
            return;
        }

        cout << "\nPast Transactions:\n";
        string line;
        while (getline(file, line)) {
            cout << line << "\n";
        }

        file.close();
    }
};


int main() {
    FinanceTracker tracker;
    int choice;

    do {
        cout << "\nPersonal Finance Tracker\n";
        cout << "1. Add Income\n";
        cout << "2. Add Expense\n";
        cout << "3. View Transactions\n";
        cout << "4. Edit Transaction\n";
        cout << "5. Delete Transaction\n";
        cout << "6. Calculate Net Worth\n";
        cout << "7. View Past Transactions from File\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: tracker.addTransaction(1); break;
            case 2: tracker.addTransaction(2); break;
            case 3: tracker.viewTransactions(); break;
            case 4: tracker.editTransaction(); break;
            case 5: tracker.deleteTransaction(); break;
            case 6: tracker.calculateNetWorth(); break;
            case 7: tracker.viewPastTransactionsFromFile(); break;
            case 8: cout << "Exiting...\n"; return 0;
            default: cout << "Invalid choice! Try again.\n";
        }
    } while (true);
}
