#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Function prototypes
void addTransaction(int type, string categories[], string dates[], double amounts[], int &transactionCount, double &total_income, double &total_expense);
void viewTransactions(string categories[], string dates[], double amounts[], int transactionCount);
void calculateNetWorth(double total_income, double total_expense);
void viewPastTransactionsFromFile();

int main() {
    string categories[100], dates[100]; // To store transaction data
    double amounts[100];
    int transactionCount = 0; // Total number of transactions
    double total_income = 0, total_expense = 0; // Totals for income and expense
    int choice;

    do {
        // Display menu
        cout << "\nPersonal Finance Tracker\n";
        cout << "1. Add Income\n";
        cout << "2. Add Expense\n";
        cout << "3. View Transactions\n";
        cout << "4. Calculate Net Worth\n";
        cout << "5. View Past Transactions from File\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Handle user choices
        if (choice == 1) {
            addTransaction(1, categories, dates, amounts, transactionCount, total_income, total_expense);
        } else if (choice == 2) {
            addTransaction(2, categories, dates, amounts, transactionCount, total_income, total_expense);
        } else if (choice == 3) {
            viewTransactions(categories, dates, amounts, transactionCount);
        } else if (choice == 4) {
            calculateNetWorth(total_income, total_expense);
        } else if (choice == 5) {
            viewPastTransactionsFromFile();
        } else if (choice == 6) {
            cout << "Exiting...\n";
            return 0;
        } else {
            cout << "Invalid choice! Please try again.\n";
        }
    } while (true); // Loop until user chooses to exit
}

// Function to add income or expense
void addTransaction(int type, string categories[], string dates[], double amounts[], int &transactionCount, double &total_income, double &total_expense) {
    string category, date;
    double amount;

    cout << "Enter category: ";
    cin >> category;

    cout << "Enter amount: ";
    cin >> amount;

    cout << "Enter date (DD/MM/YYYY): ";
    cin >> date;

    if (type == 1) { // Income
        total_income += amount; // Add to total income
    } else if (type == 2) { // Expense
        amount = -amount;       // Expenses are negative
        total_expense += amount;
    }

    // Save the transaction in memory
    categories[transactionCount] = category;
    amounts[transactionCount] = amount;
    dates[transactionCount] = date;
    transactionCount++;

    // Save the transaction to the file
    ofstream file("finance_log.txt", ios::app); // Open file in append mode
    if (!file) {
        cout << "Error: Unable to open file for writing.\n";
        return; // Exit the function if file cannot be opened
    }
    // Write the transaction details to the file
    file << "Category: " << category << "\n";
    file << "Amount: " << amount << "\n";
    file << "Date: " << date << "\n";
    file << "--------------------\n";
    file.close(); // Close the file after writing

    cout << "Transaction added successfully!\n";
}

// Function to view all transactions from memory
void viewTransactions(string categories[], string dates[], double amounts[], int transactionCount) {
    if (transactionCount == 0) {
        cout << "No transactions to display.\n";
        return;
    }

    cout << "\nAll Transactions:\n";
    for (int i = 0; i < transactionCount; i++) {
        cout << "Category: " << categories[i] << "\n";
        cout << "Amount: " << amounts[i] << "\n";
        cout << "Date: " << dates[i] << "\n";
        cout << "--------------------\n";
    }
}

// Function to view all past transactions from file
void viewPastTransactionsFromFile() {
    ifstream file("finance_log.txt"); // Open file in read mode
    if (!file) {
        cout << "Error: Unable to open file for reading.\n";
        return; // Exit the function if file cannot be opened
    }

    cout << "\nPast Transactions:\n";
    string line;
    while (getline(file, line)) { // Read each line from the file
        cout << line << "\n";
    }

    file.close(); // Close the file after reading
}

// Function to calculate and display net worth
void calculateNetWorth(double total_income, double total_expense) {
    double netWorth = total_income + total_expense;
    cout << "Net Worth: " << netWorth << "\n";

    // Save net worth to the file
    ofstream file("finance_log.txt", ios::app); // Open file in append mode
    if (file.is_open()) {
        file << "Net Worth: " << netWorth << "\n";
        file.close(); // Close the file after writing
    } else {
        cout << "Error: Unable to open file for writing.\n";
    }
}
