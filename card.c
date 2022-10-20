#include "card.h"
EN_cardError_t getCardHolderName(ST_cardData_t* cardData) {

	printf("Enter Card Holder Name\n");
	gets(cardData->cardHolderName);
	if (strlen(cardData->cardHolderName) == NULL) {
		printf("no name\n");
		return WRONG_NAME;
	}
	else if (strlen(cardData->cardHolderName) < 20 && strlen(cardData->cardHolderName) != NULL) {
		printf("name below 20\n");
		return WRONG_NAME;
	}
	else if (strlen(cardData->cardHolderName) > 24) {
		printf("name more than 24\n");
		return WRONG_NAME;
	}
	else
		printf("ok\n");
		return OK; 

}
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData){
	printf("Enter Card Expiry Date in the format MM/YY\n");
	gets(cardData->cardExpirationDate);
	if (strlen(cardData->cardExpirationDate) == 5) {
		printf("OK\n");
		return OK;
	}
	else if (strlen(cardData->cardExpirationDate) < 5 || strlen(cardData->cardExpirationDate) > 5) {
		printf("wrong format\n");
		return WRONG_EXP_DATE;
	}
	


}
EN_cardError_t getCardPAN(ST_cardData_t* cardData){
	printf("Enter Card Pan\n");
	gets(cardData->primaryAccountNumber);
	if (strlen(cardData->primaryAccountNumber) == NULL) {
		printf("no number entered\n");
		return WRONG_PAN;
	}
	else if (strlen(cardData->primaryAccountNumber) < 16 ) {
		printf("number below 16\n");
		return WRONG_PAN;
	}
	else if (strlen(cardData->primaryAccountNumber) > 19) {
		printf("number is more than 19\n");
		return WRONG_PAN;
	}
	else
		printf("ok\n");
	return OK;
}
