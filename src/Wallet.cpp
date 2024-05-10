#include "DLS.cpp"

Wallet::Wallet() : balance(100) {
    privateKey = DLS::generatePrivateKey();
    publicKey = DLS::generatePublicKey(privateKey);
    walletCounter++;
}

string Wallet::getPassword() const { return password; }

string Wallet::getPrivateKey() const { return privateKey; }

void Wallet::setPassword(string pass) { password = pass; }

string Wallet::createTransaction(double amount, string recipientPublicKey,
                                 Wallet wallets[]) {
    cout << "Creating transaction..." << endl;
    cout << "Amount to be sent: " << amount << endl;
    if (amount <= 0 || amount > balance) {
        cout << "Invalid transaction amount. Amount must be greater than 0 and "
                "less than or equal to balance."
             << endl;
        return "";
    }

    int transactionId = ++transactionCounter;
    string data = to_string(transactionId) + publicKey + recipientPublicKey +
                  to_string(amount);
    string signature = DLS::createSignature(privateKey, data);
    string newHash = DLS::generateHash(getLastTransactionGraph()["Final Hash"],
                                       transactionId, publicKey,
                                       recipientPublicKey, amount, signature);
    ledger.addTransaction(getLastTransactionGraph()["Final Hash"],
                          transactionId, publicKey, recipientPublicKey, amount,
                          signature, newHash);
    balance -= amount;
    for (int i = 0; i < walletCounter; i++) {
        if (wallets[i].publicKey == recipientPublicKey) {
            wallets[i].balance += amount;
        }
    }
    cout << amount << " sucessfully send to " << recipientPublicKey
         << ". New balance: " << balance << endl;
    return signature;
}

void Wallet::addToLedger(string fromPublicKey, string toPublicKey,
                         double amount, string sign) {
    map<string, string> prevTrans = getLastTransactionGraph();
    int transactionId = ++transactionCounter;
    string newHash =
        DLS::generateHash(prevTrans["Final Hash"], transactionId, fromPublicKey,
                          toPublicKey, amount, sign);
    ledger.addTransaction(prevTrans["Final Hash"], transactionId, fromPublicKey,
                          toPublicKey, amount, sign, newHash);
}

map<string, string> Wallet::getLastTransactionGraph() {
    map<string, string> transactionGraph;
    Node* lastTransaction = ledger.getLatestTransaction();
    if (lastTransaction) {
        transactionGraph["Prev Hash"] = lastTransaction->previousHash;
        transactionGraph["Transaction ID"] =
            to_string(lastTransaction->transactionId);
        transactionGraph["From Public Key"] = lastTransaction->_fromPublicKey;
        transactionGraph["To Public Key"] = lastTransaction->toPublickKey;
        transactionGraph["Amount"] = to_string(lastTransaction->amount);
        transactionGraph["Signature"] = lastTransaction->signature;
        transactionGraph["Final Hash"] = lastTransaction->finalHash;
    }
    return transactionGraph;
}

int Wallet::walletCounter = 0;
