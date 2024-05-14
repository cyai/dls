#include <algorithm>
#include <ctime>
#include <iostream>
#include <map>
#include <random>
#include <string>

using namespace std;

class Node {
   public:
    string previousHash;
    string _fromPublicKey;
    string toPublickKey;
    double amount;
    string signature;
    string finalHash;
    int transactionId;
    Node* next;
    Node* prev;

    Node(string, int, string, string, double, string, string);
    // Node(string prevHash, int txnId, string fromPk, string toPk, double amt,
    // string sign, string newHash) {
    //     previousHash = prevHash;
    //     transactionId = txnId;
    //     _fromPublicKey = fromPk;
    //     toPublickKey = toPk;
    //     amount = amt;
    //     signature = sign;
    //     finalHash = newHash;
    //     next = NULL;
    //     prev = NULL;
    // }
};