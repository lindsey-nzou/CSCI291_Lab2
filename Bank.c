#include <stdio.h>

#define INITIAL_BALANCE 1000
#define MAX_TRANSACTIONS 100

int main() {
    int transactions[] = {200, -150, -500, -400, -50, -200, 300};
    int num_transactions = sizeof(transactions) / sizeof(transactions[0]);
    int tobeprocessed[MAX_TRANSACTIONS];
    int tobeprocessed_count = 0;
    int balance = INITIAL_BALANCE;

    printf("Initial balance: %d AED\n", balance);

    // Process each transaction
    for (int i = 0; i < num_transactions; i++) {
        int transaction = transactions[i];
        
        if (transaction < 0 && balance + transaction < 0) {
            // Mark as invalid or impossible if the withdrawl exceeds balance
            printf("Invalid transaction: Withdrawal of %d AED exceeds current balance.\n", -transaction);
            tobeprocessed[tobeprocessed_count++] = transaction;
        } else {
            // Update the balance for valid transactions
            balance += transaction;
            printf("Processed transaction: %d AED, New balance: %d AED\n", transaction, balance);

            if (balance == 0) {
                // Stop processing further transactions if balance reaches 0
                printf("Balance has reached 0. No further transactions will be processed.\n");
                for (int j = i + 1; j < num_transactions; j++) {
                    tobeprocessed[tobeprocessed_count++] = transactions[j];
                }
                break;
            }
        }
    }

    // Print final balance
    printf("\nFinal balance: %d AED\n", balance);

    // Print contents of tobeprocessed array
    if (tobeprocessed_count > 0) {
        printf("Unprocessed transactions:\n");
        for (int i = 0; i < tobeprocessed_count; i++) {
            printf("%d ", tobeprocessed[i]);
        }
        printf("\n");
    } else {
        printf("All transactions were successfully processed.\n");
    }

    return 0;
}
