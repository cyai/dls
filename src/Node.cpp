#include "../include/Wallet.h"

Node::Node(string prevHash, int txnId, string fromPk, string toPk, double amt, string sign, string newHash) {
    previousHash = prevHash;
    transactionId = txnId;
    _fromPublicKey = fromPk;
    toPublickKey = toPk;
    amount = amt;
    signature = sign;
    finalHash = newHash;
    next = nullptr;
    prev = nullptr;
}