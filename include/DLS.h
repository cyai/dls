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
    void addToLedger(string fromPk, string toPk, double amount, string sign,
                     string prevHash, string newHash, int transactionId);

    static string generatePrivateKey();

    static string generatePublicKey(const string& privateKey);

    static string createSignature(const string& privateKey, const string& data);

    static string generateHash(string prevHash, int txnId, string fromPk,
                               string toPk, double amount, string sign);

    static bool verifySignature(const string& publicKey,
                                const string& signature, const string& data);

   private:
    static string deducePrivateKey(const string& publicKey);
};