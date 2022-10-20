#include "terminal.h"
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {
	printf("Enter Transaction Date in the format DD/MM/YYYY\n");
	gets(termData->transactionDate);
	if (strlen(termData->transactionDate) == 0) {
		printf("no date entered\n");
		return WRONG_DATE;
	}
	else if (strlen(termData->transactionDate) < 10) {
		printf("date below 10\n");
		return WRONG_DATE;
	}
	else if (strlen(termData->transactionDate) > 10) {
		printf("date is more than 10\n");
		return WRONG_DATE;
	}
	else
		printf("ok\n");
	return OK;
}
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData){
	printf("check if the card expired or not\n");
	if (cardData.cardExpirationDate[3] < termData.transactionDate[8]) {
		printf("expired card\n");
		return EXPIRED_CARD;
	}

	else if (cardData.cardExpirationDate[3] == termData.transactionDate[8] &&
		cardData.cardExpirationDate[4] < termData.transactionDate[9]) {
		printf("expired card\n");
		return EXPIRED_CARD;
	}

	else if (cardData.cardExpirationDate[3] == termData.transactionDate[8] &&
		cardData.cardExpirationDate[4] == termData.transactionDate[9] &&
		cardData.cardExpirationDate[0] < termData.transactionDate[3])
	{
		printf("expired card\n");
		return EXPIRED_CARD;
	}

	else if (cardData.cardExpirationDate[3] == termData.transactionDate[8] &&
		cardData.cardExpirationDate[4] == termData.transactionDate[9] &&
		cardData.cardExpirationDate[0] == termData.transactionDate[3] &&
		cardData.cardExpirationDate[1] < termData.transactionDate[4])
	{
		printf("expired card\n");
		return EXPIRED_CARD;
	}
	else if (cardData.cardExpirationDate[3] == termData.transactionDate[8] &&
		cardData.cardExpirationDate[4] == termData.transactionDate[9] &&
		cardData.cardExpirationDate[0] == termData.transactionDate[3] &&
		cardData.cardExpirationDate[1] == termData.transactionDate[4])
	{
		printf("ok\n");
		return OK;
	}
	else {
		printf("ok\n");
		return OK;
	}
}
EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData){

	int j = 1;

	j = getCardPAN(cardData);
	if (j == 0)
	{
		printf("valid card\n");
		return OK;
	}
	else
	{
		printf("PAN is not allowed\n");
		return INVALID_CARD;
	}


}
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {
	
	printf("Enter transaction amount\n");
	scanf_s("%f",&termData->transAmount);
	if ((termData->transAmount) <= 0) {
		printf("invalid amount\n");
		return INVALID_AMOUNT;
	}
	else
		printf("transaction amount is valid\n");
		return OK;
}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData){
	
	if (termData->transAmount > termData->maxTransAmount) {
		printf("Exceed Max Amount\n");
		return EXCEED_MAX_AMOUNT;
	}
	else
		printf("transAmount is accepted");
	return OK;
}
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData){
	printf("Enter max amount\n");
	scanf_s("%f", &termData->maxTransAmount);
	if (termData->maxTransAmount <= 0) {
		printf("invalid max amount\n");
		return INVALID_MAX_AMOUNT;
	}
	else
		printf("valid max amount\n");
	return OK;
}