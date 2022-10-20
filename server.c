#include "server.h"
ST_accountsDB_t accounts_database[255] = { {5000,"123456789123456789"},{10000,"987654321987654321"},{15000,"123698744789632112"}};
ST_transaction transactions_database[255] = { 0 };
uint8_t stolen_card_array[255]={0};
uint16_t index = 0;
uint16_t transSeqNum = 0;
EN_transState_t recieveTransactionData(ST_transaction* transData) {

	if (transData->transState == 1) {
		printf("insuffecient fund\n");
		return DECLINED_INSUFFECIENT_FUND;
	}
	else if (transData->transState == 2) {
		printf("stolen card\n");
		return DECLINED_STOLEN_CARD;
	}
	else if (transData->transState == 3) {
		printf("server error\n");
		return INTERNAL_SERVER_ERROR;
	}
	else if (transData->transState == 0) {
		printf("approved\n");
		return APPROVED;
	}

}
EN_serverError_t isValidAccount(ST_cardData_t* cardData) {
	uint16_t i = 0;
	uint16_t j = 0;
	for (i; i < 4; i++) {
		if (strcmp(cardData->primaryAccountNumber, accounts_database[i].primaryAccountNumber) == 0) {
			index = i;
			printf("account is valid\n");
			return OK;
		}
		if (strcmp(cardData->primaryAccountNumber, accounts_database[i].primaryAccountNumber) != 0) {
			j++;

		}

		if (j == 3) {
			printf("no account found\n");
			return ACCOUNT_NOT_FOUND;
		}
	}

}
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData) {
	termData->maxTransAmount = accounts_database[index].balance;
	if (termData->transAmount > termData->maxTransAmount) {
		printf("Low balance\n");
		return LOW_BALANCE;
	}
	else {
		printf("enough balance\n");
		return OK;
	}
}
EN_serverError_t saveTransaction(ST_transaction* transData) {
	uint16_t j = 0;
	if (transData->transState == 1) {
		printf("insuffecient fund\n");
		return SAVING_FAILED;
	}
	else if (transData->transState == 2) {
		printf("stolen card\n");
		return SAVING_FAILED;
	}

	j = getTransaction(transSeqNum, transData);
	if (j == 1) {
		printf("max transaction limit\n");
		return SAVING_FAILED;
	}
	// update the database of transactions
	else {
		transactions_database[transSeqNum] = *transData;
		return OK;
	}
}
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction* transData) {
	printf("transaction Sequence Number = %f\n", transactionSequenceNumber);
	if (transactionSequenceNumber > 4 || transactionSequenceNumber < 0) {
		return SAVING_FAILED;
	}
	if (transData->transactionSequenceNumber = transactionSequenceNumber) {
		transData->terminalData.maxTransAmount = accounts_database[index].balance;
		transData->terminalData.maxTransAmount = transData->terminalData.maxTransAmount - transData->terminalData.transAmount;
		accounts_database[index].balance = transData->terminalData.maxTransAmount;
		printf("transaction is completed and balance is updated\n");
		printf("new balance is %f\n", transData->terminalData.maxTransAmount);
		transactionSequenceNumber++;
		return OK;
	}
	return SAVING_FAILED; // as the process is not completed
}
EN_transState_t report_stolen_card() {
	uint16_t i=0;
	EN_cardError_t j;
	EN_serverError_t x;
	EN_terminalError_t y;
	ST_cardData_t* CARD;
	j = getCardPAN(&CARD);
		y = isValidCardPAN(&CARD);
		 x= isValidAccount(&CARD);
		if (y == OK && x== OK) {
			stolen_card_array[i] = CARD->primaryAccountNumber;
			//printf("%c", stolen_card_array[i]);
			i++;
			
		}
		return DECLINED_STOLEN_CARD;

}
