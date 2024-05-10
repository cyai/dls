// #include "Wallet.cpp"
// #include "Ledger.cpp"
// #include "DLS.cpp"
#include "Wallet.cpp"

Wallet* checkWalletExistance(string publicKey, Wallet wallets[]) {
    Wallet* wallet = NULL;
    for (int i = 0; i < Wallet::walletCounter; i++) {
        if (wallets[i].publicKey == publicKey) {
            wallet = &wallets[i];
            return wallet;
        }
    }
    return wallet;
}

void deleteNodeAndRevertBalance(string recipientPublicKey, string senderPublicKey, double amount, Wallet wallets[]){
    cout<<"Multiple chains detected. Reverting the balance. 😕"<<endl;

    for (int i=0; i<Wallet::walletCounter; i++){
        if (wallets[i].publicKey==recipientPublicKey){
            wallets[i].balance-=amount;
        }
        if (wallets[i].publicKey==senderPublicKey){
            wallets[i].balance+=amount;
        }
    }

    cout<<"Balance reverted successfully. 🥲"<<endl;
    cout<<"Removing the transaction from the ledger. 😞"<<endl;

    for (int i=0; i<Wallet::walletCounter; i++){
        wallets[i].ledger.getLatestTransaction()->prev->next=NULL;
    }

    cout<<"Transaction removed successfully."<<endl;
}


Ledger send(string recipientPublicKey, string senderPublicKey, double amount, Wallet wallets[]){  //is it a list of wallets?
        Wallet* senderWallet = checkWalletExistance(senderPublicKey, wallets);
        if (senderWallet == NULL) {
            cout << "Invalid Sender Public Key. Transaction failed." << endl;
            return Ledger();
        }

        Wallet* recipientWallet = checkWalletExistance(recipientPublicKey, wallets);
        if (recipientWallet == NULL) {
            cout << "Invalid Recipient Public Key. Transaction failed." << endl;
            return Ledger();
        }

        cout<<"Amout to be sent: "<<amount<<endl;
        string transacSignature=senderWallet->createTransaction(amount,recipientPublicKey, wallets);
        cout<<"Transaction Signature: "<<transacSignature<<endl;


        for (int i = 0; i < Wallet::walletCounter; i++) {
            if (&wallets[i] != senderWallet) {
                wallets[i].addToLedger(senderPublicKey, recipientPublicKey, amount, transacSignature);
            }
        }

        //chains_verify : kinda unecessary to make it its own fn imo
        map<string, int> chainsDetials;
        for (int i=0; i<Wallet::walletCounter; i++){
                chainsDetials[wallets[i].getLastTransactionGraph()["Final Hash"]]=0;
        }

        for (int i=0; i<Wallet::walletCounter; i++){
                map<string, string> walletDetials = wallets[i].getLastTransactionGraph();
                chainsDetials[walletDetials["Final Hash"]]++;
        }

        vector<string> maximumFrequencyHashes;
        int maximumFrequency = chainsDetials.begin()->second;

        for (auto it=chainsDetials.begin(); it!=chainsDetials.end(); it++){
            if (it->second > maximumFrequency){
                maximumFrequency = it->second;
                maximumFrequencyHashes.clear();
                maximumFrequencyHashes.push_back(it->first);
            } else if (it->second == maximumFrequency) {
                maximumFrequencyHashes.push_back(it->first);
            }
        }

        // If there is more than one hash with the maximum frequency, delete the node and revert the balance
        if (maximumFrequencyHashes.size() > 1) {
            deleteNodeAndRevertBalance(recipientPublicKey, senderPublicKey, amount, wallets);
            return Ledger();
        }

        string maximumFrequencyHash = maximumFrequencyHashes[0];
        // TODO: Handle the case where multiple chains have the same maximum frequency
        
        vector<Wallet> failedWallets;

        
        for (int i=0; i<Wallet::walletCounter; i++){
            if (wallets[i].getLastTransactionGraph()["Final Hash"]!=maximumFrequencyHash){
                cout<<"Chain verification failed for Wallet "<<i+1<<". Taking maximum frequency chain."<<endl;
                failedWallets.push_back(wallets[i]);
                return Ledger();
            }
        }


        Wallet* successfulWallet = NULL;
        for (int i = 0; i < Wallet::walletCounter; i++) {
            bool isFailed = false;
            for (const Wallet& failedWallet : failedWallets) {
                if (&wallets[i] == &failedWallet) {
                    isFailed = true;
                    break;
                }
            }
            if (!isFailed) {
                successfulWallet = &wallets[i];
                break;
            }
        }

        DLS dls;
        map<string, string> lastTransactionDetails = successfulWallet->getLastTransactionGraph();
        dls.standardLedger.addTransaction(lastTransactionDetails["Final Hash"],
                                           stoi(lastTransactionDetails["Transaction ID"]),
                                           lastTransactionDetails["From Public Key"],
                                           lastTransactionDetails["To Public Key"],
                                           stod(lastTransactionDetails["Amount"]),
                                           lastTransactionDetails["Signature"],
                                           lastTransactionDetails["Final Hash"]);

        return dls.standardLedger;
}