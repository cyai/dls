// #include "../include/Node.h"
#include "Node.cpp"

Ledger::Ledger() {
    head = NULL;
    tail = NULL;
}

void Ledger::addTransaction(string prevHash, int txnId, string fromPk,
                            string toPk, double amount, string sign,
                            string newHash) {
    Node* newNode =
        new Node(prevHash, txnId, fromPk, toPk, amount, sign, newHash);

    if (isEmpty()) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

bool Ledger::isEmpty() const { return head == NULL; }

void Ledger::printLedger() const {
    Node* current = head;
    while (current != NULL) {
        cout << "-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*"
                "-*-*-*-*-*-*-*-*-*-*-*"
             << endl
             << endl;
        cout << "Transaction ID: " << current->transactionId << endl;
        cout << "From Public Key: " << current->_fromPublicKey << endl;
        cout << "To Public Key: " << current->toPublickKey << endl;
        cout << "Amount: " << current->amount << endl;
        cout << "Signature: " << current->signature << endl;
        cout << "Final Hash: " << current->finalHash << endl;
        cout << endl;
        current = current->next;
    }
}

Node* Ledger::getLatestTransaction() { return tail; }

int Ledger::countTransactions() {
    Node* current = head;
    int count = 0;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

void Ledger::filterTransactionsByFrom(string fromPublicKey) {
    Node* current = head;
    while (current != NULL) {
        if (current->_fromPublicKey == fromPublicKey) {
            cout << "Transaction ID: " << current->transactionId << endl;
            cout << "From Public Key: " << current->_fromPublicKey << endl;
            cout << "To Public Key: " << current->toPublickKey << endl;
            cout << "Amount: " << current->amount << endl;
            cout << "Signature: " << current->signature << endl;
            cout << "Final Hash: " << current->finalHash << endl;
            cout << endl;
        }
        current = current->next;
    }
}

void Ledger::filterTransactionsByTo(string toPublicKey) {
    Node* current = head;
    while (current != NULL) {
        if (current->toPublickKey == toPublicKey) {
            cout << "Transaction ID: " << current->transactionId << endl;
            cout << "From Public Key: " << current->_fromPublicKey << endl;
            cout << "To Public Key: " << current->toPublickKey << endl;
            cout << "Amount: " << current->amount << endl;
            cout << "Signature: " << current->signature << endl;
            cout << "Final Hash: " << current->finalHash << endl;
            cout << endl;
        }
        current = current->prev;
    }
}

