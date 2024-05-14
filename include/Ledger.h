#include <iostream>
#include <string>

#include "Node.h"

using namespace std;

class Ledger {
   private:
    Node* head;
    Node* tail;

   public:
    Ledger();
    // Ledger() {
    //     head = NULL;
    //     tail = NULL;
    // }

    void addTransaction(string prevHash, int txnId, string fromPk, string toPk,
                        double amount, string sign, string newHash);

    // void addTransaction(string prevHash, int txnId, string fromPk, string
    // toPk, double amount, string sign, string newHash) {
    //     Node* newNode = new Node(prevHash, txnId, fromPk, toPk, amount, sign,
    //     newHash);

    //     if (isEmpty()) {
    //         head = tail = newNode;
    //     } else {
    //         tail->next = newNode;
    //         newNode->prev = tail;
    //         tail = newNode;
    //     }
    // }

    bool isEmpty() const;
    // bool isEmpty() const {
    //     return head == NULL;
    // }

    void printLedger() const;

    // void printLedger() {
    //     Node* current = head;
    //     while (current != NULL) {
    //         cout <<
    //         "-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*"<<endl<<endl;
    //         cout << "Transaction ID: " << current->transactionId << endl;
    //         cout << "From Public Key: " << current->_fromPublicKey << endl;
    //         cout << "To Public Key: " << current->toPublickKey << endl;
    //         cout << "Amount: " << current->amount << endl;
    //         cout << "Signature: " << current->signature << endl;
    //         cout << "Final Hash: " << current->finalHash << endl;
    //         cout << endl;
    //         current = current->next;
    //     }
    // }

    Node* getLatestTransaction();
    // Node* getLatestTransaction() {
    //     return tail;
    // }

    int countTransactions();
    // int countTransactions() {
    //     Node* current = head;
    //     int count = 0;
    //     while (current != NULL) {
    //         count++;
    //         current = current->next;
    //     }
    //     return count;
    // }

    void filterTransactionsByFrom(string fromPublicKey);

    // void filterTransactionsByFrom(string fromPublicKey) {
    //     Node* current = head;
    //     while (current != NULL) {
    //         if (current->_fromPublicKey == fromPublicKey) {
    //             cout << "Transaction ID: " << current->transactionId << endl;
    //             cout << "From Public Key: " << current->_fromPublicKey <<
    //             endl; cout << "To Public Key: " << current->toPublickKey <<
    //             endl; cout << "Amount: " << current->amount << endl; cout <<
    //             "Signature: " << current->signature << endl; cout << "Final
    //             Hash: " << current->finalHash << endl; cout << endl;
    //         }
    //         current = current->next;
    //     }
    // }

    void filterTransactionsByTo(string toPublicKey);
    // void filterTransactionsByTo(string toPublicKey) {
    //     Node* current = head;
    //     while (current != NULL) {
    //         if (current->toPublickKey == toPublicKey) {
    //             cout << "Transaction ID: " << current->transactionId << endl;
    //             cout << "From Public Key: " << current->_fromPublicKey <<
    //             endl; cout << "To Public Key: " << current->toPublickKey <<
    //             endl; cout << "Amount: " << current->amount << endl; cout <<
    //             "Signature: " << current->signature << endl; cout << "Final
    //             Hash: " << current->finalHash << endl; cout << endl;
    //         }
    //         current = current->prev;
    //     }
    // }
};