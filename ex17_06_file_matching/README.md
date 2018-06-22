17.6 (File Matching) In commercial data processing, it’s common to have several files in each 
application system. In an accounts receivable system, for example, there is generally a master 
file containing detailed information about each customer, such as the customer’s name, address, telephone
number, outstanding balance, credit limit, discount terms, contract arrangements and, possibly, a
condensed history of recent purchases and cash payments.

As transactions occur (e.g., sales are made and cash payments arrive), they’re entered into a
file. At the end of each business period (a month for some companies, a week for others and a day
in some cases), the file of transactions (called trans.dat) is applied to the master file (called 
oldmast.dat), thus updating each account's record of purchases and payments. During an updating run, 
the master file is rewritten as a new file (newmast.dat), which is then used at the end of the next
business period to begin the updating process again.

File-matching programs must deal with certain problems that do not exist in single-file programs. 
For example, a match does not always occur. A customer on the master file might not have
made any purchases or cash payments in the current business period, and therefore no record for
this customer will appear on the transaction file. Similarly, a customer who did make some purchases 
or cash payments may have just moved to this community, and the company may not have
had a chance to create a master record for this customer.

Use the statements from Exercise 17.3 as a basis for writing a complete file-matching accounts
receivable program. Use the account number on each file as the record key for matching purposes.
Assume that each file is a sequential file with records stored in increasing order by account number.
When a match occurs (i.e., records with the same account number appear on both the master
and transaction files), add the dollar amount on the transaction file to the current balance on the
master file, and write the newmast.dat record. (Assume purchases are indicated by positive
amounts on the transaction file and payments are indicated by negative amounts.) When there is a
master record for a particular account but no corresponding transaction record, merely write the
master record to newmast.dat. When there is a transaction record but no corresponding master
record, print the error message "Unmatched transaction record for account number ..." (fill in
the account number from the transaction record).

17.7 (File Matching Test Data) After writing the program of Exercise 17.6, write a simple program 
to create some test data for checking out the program. Use the following sample account data:

Master file<br>Account number | Name | Balance
 :----------------------------| :--- | :------
100 | Alan Jones | 348.17
300 | Mary Smith | 27.19
500 | Sam Sharp | 0.00
700 | Suzy Green | –14.22

Transaction file<br>Account number | Transaction amount
:--- | :---
100 | 27.14
300 | 62.11
400 | 100.56
900 | 82.17

17.8 (File Matching Test) Run the program of Exercise 17.6, using the files of test data created
in Exercise 17.7. Print the new master file. Check that the accounts have been updated correctly.

17.9 (File Matching Enhancement) It’s common to have several transaction records with the
same record key, because a particular customer might make several purchases and cash payments
during a business period. Rewrite your accounts receivable file-matching program of Exercise 17.6
to provide for the possibility of handling several transaction records with the same record key. 
Modify the test data of Exercise 17.7 to include the following additional transaction records:

Account number | Dollar amount
:--- | :---
300 | 83.89
700 | 80.78
700 | 1.53
