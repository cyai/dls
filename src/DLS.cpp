#include "Ledger.cpp"
// #include "../include/Ledger.h"

void DLS::printLedger() { standardLedger.printLedger(); }

void DLS::addToLedger(string fromPk, string toPk, double amount, string sign,
                      string prevHash, string newHash, int transactionId) {
    standardLedger.addTransaction(prevHash, transactionId, fromPk, toPk, amount,
                                  sign, newHash);
}

string DLS::generatePrivateKey() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, 15);

    string privateKey = "";
    for (int i = 0; i < 64; i++) {  // Generating a longer private key
        int randomNum = distrib(gen);
        privateKey += "0123456789ABCDEF"[randomNum];
    }

    return privateKey;
}

string DLS::generatePublicKey(const string& privateKey) {
    string publicKey = "";
    for (char c : privateKey) {
        int digit = c >= 'A' ? c - 'A' + 10 : c - '0';
        int transformedDigit = digit ^ 0xF;
        publicKey += "0123456789ABCDEF"[transformedDigit];
    }
    reverse(publicKey.begin(), publicKey.end());
    return publicKey;
}

string DLS::createSignature(const string& privateKey, const string& data) {
    srand(time(NULL));

    string input = privateKey + data;
    int inputValue = 0;
    for (char c : input) {
        inputValue += c;
    }

    int signature = (inputValue * 997 + 31) % 100000;
    for (char c : input) {
        signature = (signature * 31 + c) % 100000;
    }

    signature = (signature * 997 + 31) % 100000;
    return to_string(signature);
}

string DLS::generateHash(string prevHash, int txnId, string fromPk, string toPk,
                         double amount, string sign) {
    string input =
        prevHash + to_string(txnId) + fromPk + toPk + to_string(amount) + sign;
    hash<string> hasher;
    size_t hash = 0;
    for (char c : input) {
        hash = ((hash << 5) + hash) + c;  // hash * 33 + c
    }
    return to_string(hash & 0xFF);  // Keep only the lowest 8 bits
}

bool DLS::verifySignature(const string& publicKey, const string& signature,
                          const string& data) {
    string deducedPrivateKey = deducePrivateKey(publicKey);
    string expectedSignature = createSignature(deducedPrivateKey, data);
    return expectedSignature == signature;
}

string DLS::deducePrivateKey(const string& publicKey) {
    string privateKey = "";
    string reversedPublicKey = publicKey;
    reverse(reversedPublicKey.begin(), reversedPublicKey.end());

    for (char c : reversedPublicKey) {
        int digit = c >= 'A' ? c - 'A' + 10 : c - '0';
        int transformedDigit = digit ^ 0xF;
        privateKey += "0123456789ABCDEF"[transformedDigit];
    }

    return privateKey;
}

Ledger DLS::standardLedger;
