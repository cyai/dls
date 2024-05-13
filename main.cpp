// #include "src/DLS.cpp"
// #include "src/Ledger.cpp"
// #include "src/Wallet.cpp"
#include "src/utils.cpp"


int main() {
    int choice;
    Wallet* wallets = new Wallet[100];
    int walletCounter = 0;
    

    DLS dls;
    string password;

    cout<< "\n\n\n<-***-***-***-***-***-***-***-***-***-***-***-***->"<<endl;
    cout << "Welcome to our Decentralized Ledger System!" << endl;
    cout<< "<-***-***-***-***-***-***-***-***-***-***-***-***->"<<endl;

    while(choice!=6){
        cout << "\n\n>>> Choose an option:" << endl;
        cout << "1. Add a new wallet" << endl;
        cout << "2. Send money between wallets" << endl;
        cout << "3. View Ledger" << endl;
        cout << "4. View balance" << endl;
        cout << "5. Display Wallets"<<endl;
        cout << "6. Exit" << endl<<endl<<endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice=0;
        }
        cout<<"\n\n\n";

        switch (choice) {
            case 1: {
                wallets[walletCounter] = Wallet(0);
                cout << "Enter the name of the wallet:" << endl;
                cin >> wallets[walletCounter].name;
                cout << "🤫 Enter a password for the wallet number " << walletCounter + 1<< " : ";
                do {
                    cin >> password;
                    if (password.length()<8){
                        cout<<"🫣 Password must be atleast 8 characters long. Please enter again: ";
                    }
                } while (password.length()<8);
                wallets[walletCounter].setPassword(password);

                cout << "🔐 Password set successfully!" << endl<<endl;

                cout << "🤑 Enter initial balance for the new wallet : ";
                cin >> wallets[walletCounter].balance;

                cout<<"# Your wallet no is: "<<walletCounter+1<<endl;
                cout<<"🔑 Your Public Key is: "<<wallets[walletCounter].publicKey<<endl;
                cout<<"🤫 Your Private Key is: "<<wallets[walletCounter].getPrivateKey()<<endl;
                cout<<"[NOTE: Keep your private key safe and do not share it with anyone.]"<<endl<<endl;
                cout << "🎉 Wallet created successfully!" << endl;

                cout << "--> " << wallets[walletCounter].balance << " rupees added to the wallet." << endl << endl;
                walletCounter++;
                break;
            }

            case 2: {
                string sender, recipient;
                double amount;
                cout << "\n\n\n";
                cout << "🫳 Enter the wallet name of the SENDER: ";
                cin >> sender;
                cout << "🫴 Enter the wallet name of the RECIPIENT: ";
                cin >> recipient;
                cout << "💰 Enter the amount to be sent: ";
                cin >> amount;
                cout << "🫣 Enter the password for the sender's wallet: ";
                cin >> password;
                cout << endl;

                Wallet* senderWallet, *recipientWallet;

                for (int i = 0; i < Wallet::walletCounter; i++) {
                    if (wallets[i].name == sender) {
                        senderWallet = &wallets[i];

                        if (password != senderWallet->getPassword()){
                            cout<<"😕 Invalid password. Please try again."<<endl;
                            break;
                        }
                    }
                    if (wallets[i].name == recipient) {
                        recipientWallet = &wallets[i];
                    }
                }
                if (senderWallet == NULL || recipientWallet == NULL) {
                    cout << "😕 Invalid wallet name. Please try again." << endl;
                    break;
                }

                cout<<endl<<endl<<"⏳ Making transaction......"<<endl<<endl;
                Ledger ledger = send(recipientWallet->publicKey, senderWallet->publicKey, amount, wallets);

                
                break;
            }

            case 3: {
                cout << "\n\n\n";
                cout << "📜 Ledger:" << endl <<endl;
                dls.printLedger();
                cout<<"-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*"<<endl<<endl<<endl;
                break;
            }

            case 4: {
                string walletName;
                cout << "💳 Enter the wallet name: ";
                cin >> walletName;

                for (int i = 0; i < Wallet::walletCounter; i++) {
                    if (wallets[i].name == walletName) {
                        cout << "💸 Balance: " << wallets[i].balance << endl;
                        break;
                    }
                }
                break;
            }

            case 5: {
                cout << "📜 Wallets:" << endl;
                for (int i = 0; i < Wallet::walletCounter; i++) {
                    if (wallets[i].name != "") {
                        cout << "Wallet " << i + 1 << ": " << wallets[i].name << endl;
                    }
                }
                break;
            }

            case 6: {
                cout << "🙌 Thank you for using our DLS system! 😘" << endl;
                return 0;
            }

            default: {
                cout << "😕 Invalid choice. Please try again." << endl;
                choice = 0;
                break;
            }

        }
    }

    delete[] wallets;

    return 0;
}