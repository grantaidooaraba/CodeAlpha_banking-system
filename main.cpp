#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;



// TRANSACTION CLASS 
class Transaction {

public:

    string type;
    double amount;
    string details;

    Transaction(string t, double a, string d) {

        type = t;
        amount = a;
        details = d;
    }
};




//  ACCOUNT CLASS 
class Account {

private:

    int accountNumber;
    double balance;

    vector<Transaction> history;

public:

    // Constructor
    Account(int accNum, double initialBalance = 0) {

        accountNumber = accNum;
        balance = initialBalance;
    }


    // Deposit Function
    void deposit(double amount) {

        balance += amount;

        history.push_back(
            Transaction(
                "Deposit",
                amount,
                "Money Deposited"
            )
        );

        cout << "Deposit successful.\n";
    }


    // Withdraw Function
    void withdraw(double amount) {

        if (amount > balance) {

            cout << "Insufficient balance.\n";
            return;
        }

        balance -= amount;

        history.push_back(
            Transaction(
                "Withdrawal",
                amount,
                "Money Withdrawn"
            )
        );

        cout << "Withdrawal successful.\n";
    }


    // Transfer Function
    void transfer(Account &receiver, double amount) {

        if (amount > balance) {

            cout << "Insufficient balance.\n";
            return;
        }

        // Sender loses money
        balance -= amount;

        // Receiver gains money
        receiver.balance += amount;


        // Sender transaction history
        history.push_back(
            Transaction(
                "Transfer Sent",
                amount,
                "Transferred to account "
                + to_string(receiver.accountNumber)
            )
        );


        // Receiver transaction history
        receiver.history.push_back(
            Transaction(
                "Transfer Received",
                amount,
                "Received from account "
                + to_string(accountNumber)
            )
        );

        cout << "Transfer successful.\n";
    }


    // Display Balance
    void displayBalance() {

        cout << fixed << setprecision(2);

        cout << "Current Balance: GHS "
             << balance
             << endl;
    }


    // Display Account Info
    void displayAccountInfo() {

        cout << "\n===== ACCOUNT INFO =====\n";

        cout << "Account Number: "
             << accountNumber
             << endl;

        cout << fixed << setprecision(2);

        cout << "Balance: GHS "
             << balance
             << endl;
    }


    // Show Transaction History
    void showTransactions() {

        cout << "\n===== TRANSACTION HISTORY =====\n";

        if (history.empty()) {

            cout << "No transactions available.\n";
            return;
        }

        for (Transaction t : history) {

            cout << t.type
                 << " | Amount: GHS "
                 << fixed
                 << setprecision(2)
                 << t.amount
                 << " | "
                 << t.details
                 << endl;
        }
    }


    // Getter for account number
    int getAccountNumber() {

        return accountNumber;
    }
};






//  CUSTOMER CLASS 
class Customer {

private:

    string name;

    vector<Account> accounts;

public:

    // Constructor
    Customer(string n) {

        name = n;
    }


    // Create Account
    void createAccount(
        int accountNumber,
        double initialBalance
    ) {

        Account newAccount(
            accountNumber,
            initialBalance
        );

        accounts.push_back(newAccount);

        cout << "Account created successfully.\n";
    }


    // Find Account
    Account* findAccount(int accountNumber) {

        for (auto &acc : accounts) {

            if (
                acc.getAccountNumber()
                == accountNumber
            ) {

                return &acc;
            }
        }

        return nullptr;
    }


    // Display Customer Info
    void displayCustomerInfo() {

        cout << "\n===== CUSTOMER INFO =====\n";

        cout << "Customer Name: "
             << name
             << endl;

        cout << "Number of Accounts: "
             << accounts.size()
             << endl;
    }
};


int main() {

    string customerName;

    cout << "Enter customer name: ";
    getline(cin, customerName);


    // Create customer object
    Customer customer(customerName);


    // Number of accounts
    int numAccounts;

    cout << "Enter number of accounts: ";
    cin >> numAccounts;


    // Create accounts
    for (int i = 0; i < numAccounts; i++) {

        int accNum;
        double balance;

        cout << "\n===== Account "
             << i + 1
             << " =====\n";

        cout << "Enter account number: ";
        cin >> accNum;

        cout << "Enter initial balance: ";
        cin >> balance;

        customer.createAccount(
            accNum,
            balance
        );
    }



    // MENU SYSTEM
    int choice;

    while (true) {

        cout << "\n\n========== BANK MENU ==========\n";

        cout << "1. Deposit\n";
        cout << "2. Withdraw\n";
        cout << "3. Transfer\n";
        cout << "4. View Balance\n";
        cout << "5. View Transaction History\n";
        cout << "6. View Account Info\n";
        cout << "7. Exit\n";

        cout << "\nEnter choice: ";
        cin >> choice;



        //  DEPOSIT 
        if (choice == 1) {

            int accNum;
            double amount;

            cout << "Enter account number: ";
            cin >> accNum;

            Account* acc =
                customer.findAccount(accNum);

            if (acc != nullptr) {

                cout << "Enter amount: ";
                cin >> amount;

                acc->deposit(amount);
            }

            else {

                cout << "Account not found.\n";
            }
        }



        //  WITHDRAW 
        else if (choice == 2) {

            int accNum;
            double amount;

            cout << "Enter account number: ";
            cin >> accNum;

            Account* acc =
                customer.findAccount(accNum);

            if (acc != nullptr) {

                cout << "Enter amount: ";
                cin >> amount;

                acc->withdraw(amount);
            }

            else {

                cout << "Account not found.\n";
            }
        }



        //  TRANSFER 
        else if (choice == 3) {

            int senderNum;
            int receiverNum;

            double amount;

            cout << "Enter sender account number: ";
            cin >> senderNum;

            cout << "Enter receiver account number: ";
            cin >> receiverNum;

            Account* sender =
                customer.findAccount(senderNum);

            Account* receiver =
                customer.findAccount(receiverNum);

            if (
                sender != nullptr &&
                receiver != nullptr
            ) {

                cout << "Enter amount: ";
                cin >> amount;

                sender->transfer(
                    *receiver,
                    amount
                );
            }

            else {

                cout << "One or both accounts not found.\n";
            }
        }



        //  VIEW BALANCE 
        else if (choice == 4) {

            int accNum;

            cout << "Enter account number: ";
            cin >> accNum;

            Account* acc =
                customer.findAccount(accNum);

            if (acc != nullptr) {

                acc->displayBalance();
            }

            else {

                cout << "Account not found.\n";
            }
        }



        //  TRANSACTION HISTORY
        else if (choice == 5) {

            int accNum;

            cout << "Enter account number: ";
            cin >> accNum;

            Account* acc =
                customer.findAccount(accNum);

            if (acc != nullptr) {

                acc->showTransactions();
            }

            else {

                cout << "Account not found.\n";
            }
        }



        //  ACCOUNT INFO 
        else if (choice == 6) {

            int accNum;

            cout << "Enter account number: ";
            cin >> accNum;

            Account* acc =
                customer.findAccount(accNum);

            if (acc != nullptr) {

                acc->displayAccountInfo();
            }

            else {

                cout << "Account not found.\n";
            }
        }



        //  EXIT
        else if (choice == 7) {

            cout << "Exiting program...\n";

            break;
        }



        //  INVALID 
        else {

            cout << "Invalid choice.\n";
        }
    }


    return 0;
}
