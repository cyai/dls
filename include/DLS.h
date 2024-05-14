#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>
#include <string>

#include "Ledger.h"

class DLS {
   public:
    static Ledger standardLedger;

    void printLedger();
    //     void printLedger() {
    //         standardLedger.printLedger();
    //     }
    void addToLedger(string fromPk, string toPk, double amount, string sign,
                     string prevHash, string newHash, int transactionId);
    //     void addToLedger(string fromPk, string toPk, double amount, string
    //     sign, string prevHash, string newHash, int transactionId) {
    //         standardLedger.addTransaction(prevHash, transactionId, fromPk,
    //         toPk, amount, sign, newHash);
    //     }

    static string generatePrivateKey();
    //     static string generatePrivateKey() {
    //         random_device rd;
    //         mt19937 gen(rd());
    //         uniform_int_distribution<> distrib(0, 15);

    //         string privateKey = "";
    //         for (int i = 0; i < 64; i++) {  // Generating a longer private
    //         key
    //             int randomNum = distrib(gen);
    //             privateKey += "0123456789ABCDEF"[randomNum];
    //         }

    //         return privateKey;
    //     }

    static string generatePublicKey(const string& privateKey);
    //     static string generatePublicKey(const string& privateKey) {
    //         string publicKey = "";
    //         for (char c : privateKey) {
    //             int digit = c >= 'A' ? c - 'A' + 10 : c - '0';
    //             int transformedDigit = digit ^ 0xF;
    //             publicKey += "0123456789ABCDEF"[transformedDigit];
    //         }
    //         reverse(publicKey.begin(), publicKey.end());
    //         return publicKey;
    //     }

    static string createSignature(const string& privateKey, const string& data);
    //     static string createSignature(const string& privateKey, const string&
    //     data) {
    //         srand(time(NULL));

    //         string input = privateKey + data;
    //         int inputValue = 0;
    //         for (char c : input) {
    //             inputValue += c;
    //         }

    //         int signature = (inputValue * 997 + 31) % 100000;
    //         for (char c : input) {
    //             signature = (signature * 31 + c) % 100000;
    //         }

    //         signature = (signature * 997 + 31) % 100000;
    //         return to_string(signature);
    //     }

    static string generateHash(string prevHash, int txnId, string fromPk,
                               string toPk, double amount, string sign);
    //     static string generateHash(string prevHash, int txnId, string fromPk,
    //     string toPk, double amount, string sign) {
    //         string input = prevHash + to_string(txnId) + fromPk + toPk +
    //         to_string(amount) + sign; hash<string> hasher; size_t hash = 0;
    //         for (char c : input) {
    //             hash = ((hash << 5) + hash) + c; // hash * 33 + c
    //         }
    //         return to_string(hash & 0xFF); // Keep only the lowest 8 bits
    //     }

    static bool verifySignature(const string& publicKey,
                                const string& signature, const string& data);
    //     static bool verifySignature(const string& publicKey, const string&
    //     signature, const string& data) {
    //         string deducedPrivateKey = deducePrivateKey(publicKey);
    //         string expectedSignature = createSignature(deducedPrivateKey,
    //         data); return expectedSignature == signature;
    //     }

   private:
    static string deducePrivateKey(const string& publicKey);
    //     static string deducePrivateKey(const string& publicKey) {
    //         string privateKey = "";
    //         string reversedPublicKey = publicKey;
    //         reverse(reversedPublicKey.begin(), reversedPublicKey.end());

    //         for (char c : reversedPublicKey) {
    //             int digit = c >= 'A' ? c - 'A' + 10 : c - '0';
    //             int transformedDigit = digit ^ 0xF;
    //             privateKey += "0123456789ABCDEF"[transformedDigit];
    //         }

    //         return privateKey;
    //     }
};