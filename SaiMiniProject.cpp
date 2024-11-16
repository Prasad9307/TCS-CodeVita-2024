#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    int initialBalance, operations, currentSnapshot = 0;
    cin >> initialBalance >> operations;

    vector<int> transactions;
    vector<int> snapshots = {initialBalance};

    for (int i = 0; i < operations; i++) {
        string command;
        cin >> command;

        if (command == "read") {
            cout << snapshots[currentSnapshot] << endl;
        } 
        else if (command == "credit" || command == "debit") {
            int amount;
            cin >> amount;
            if (command == "credit") {
                snapshots[currentSnapshot] += amount;
                transactions.push_back(amount);
            } else {
                snapshots[currentSnapshot] -= amount;
                transactions.push_back(-amount);
            }
        } 
        else if (command == "abort") {
            int transactionIndex;
            cin >> transactionIndex;
            if (transactionIndex > 0 && transactionIndex <= transactions.size()) {
                snapshots[currentSnapshot] -= transactions[transactionIndex - 1];
                transactions[transactionIndex - 1] = 0;
            }
        } 
        else if (command == "rollback") {
            int snapshotIndex;
            cin >> snapshotIndex;
            if (snapshotIndex > 0 && snapshotIndex <= snapshots.size()) {
                currentSnapshot = snapshotIndex - 1;
                snapshots.resize(currentSnapshot + 1);
            }
        } 
        else if (command == "commit") {
            snapshots.push_back(snapshots[currentSnapshot]);
            currentSnapshot++;
        }
    }

    return 0;
}
