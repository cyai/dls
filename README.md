# Decentralised Ledger System

## Introduction

We hang out a lot. And we spend a lot. And sometimes we loose track of <i>who ows how much to whom </i> .

So we allot one person the power of handelling a ledger. And we trust him to keep track of all the transactions. But what if he makes a mistake? Or what if he is not honest? Or what if he is not available?

Well we dont seem to trust our friends (🤫 I didn't say that). So??

> > Why not use a decentralised ledger system?

## What is a Decentralised Ledger System?

A decentralised ledger system is a system where the ledger is not maintained by a single person but by a group of people. And the ledger is not stored in a single place but in multiple places. And the ledger is not controlled by a single entity but by multiple entities.

## How does it work?

The ledger is maintained by a group of people called <b>nodes</b>. Each node has a copy of the ledger. And each node has the power to add a transaction to the ledger. And each node has the power to validate a transaction.

## What is the advantage?

Since the ledger is maintained by multiple nodes, it is difficult to tamper with the ledger. And since the ledger is maintained by multiple nodes, it is difficult to loose the ledger. And since the ledger is maintained by multiple nodes, it is difficult to make a mistake in the ledger.

## How did we implement it?

We implemented a decentralised ledger system using <b>blockchain</b>. A blockchain is a chain of blocks where each block contains a list of transactions. And each block is linked to the previous block. And each block is validated by the nodes.

## Tell you an example:

-   I have a ledger with 1000 coins.
-   I want to give 100 coins to Mohil.
-   I create a transaction, send coins to Mohil.
-   I update my own ledger.
-   I sign the tranasction with my `pirvate key`.
-   I broadcast the transaction everyone else.
-   Everyone else validate the transaction. How? They check my `public key` and my `signature`. They run an function which will return a boolean value showing if the signature made by the `public key` associated with the `private key` is valid or not.
-   If the transaction is valid, everyone else add the transaction to the ledger.
-   Everyone create a node containing the transaction.
-   They update their own ledger.
-   Then we check if everyone's ledger is same and honest. We see the last node of the ledger. We check the hash. If the hash is same, we are good to go. If not, we have to see which majority ledger is correct and report the rest of the ledgers.

## Say no more. I am in. How do I use it?

1. Clone the repository
2. Run the bash file to compile and run the code: `./run.sh`

    > If you get a permission denied error, run `chmod +x run.sh` and then run `./run.sh`

3. Follow the instructions on the terminal
4. Enjoy ☺️

## Contributors

-   Aarav Singh Luthra
-   Aryan Daga
-   Mohil A
-   Niyati Singh
-   Preesha K
-   Vardhaman Kalloli
