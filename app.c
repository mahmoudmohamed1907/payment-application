#include "app.h"
void appStart(void)
{
    uint16_t x = 0;
    uint16_t j = 0;
    uint8_t pressed;
    ST_cardData_t CardData;
    ST_cardData_t* CardDataPtr;
    CardDataPtr = &CardData;
    ST_terminalData_t TermData = { 0,1,"12/12/2020" };
    ST_terminalData_t* TermDataPtr;
    TermDataPtr = &TermData;
    ST_transaction transData = { CardData,TermData,0,0 };
    ST_transaction* transDataPtr;
    transDataPtr = &transData;
    uint32_t transactionSequenceNumber = 0;
    while (1)
    {
        scanf_s("%c", &pressed);
        if (pressed == '9') {x= report_stolen_card(); }
        else {
            transData.transState = 0;
            // Collecting Card Data

            j = getCardHolderName(CardDataPtr);
            if (j != 0)
            {
                printf("Name Format is not correct\n");
                transData.transState = 2;
                continue;
            }
            j = 0;
            j = getCardExpiryDate(CardDataPtr);
            if (j != 0)
            {
                printf("Expiration date format is not correct\n");
                transData.transState = 2;
                continue;
            }
            j = 0;
            j = isValidCardPAN(CardDataPtr);
            if (j != 0)
            {
                printf("PAN Format is not correct\n");
                transData.transState = 2;
                continue;
            }
            //Checking if card is stolen or not
            if (x = DECLINED_STOLEN_CARD)
            {
                printf("This card is stolen,you can't proceed any transactions\n");
                exit(0);
            }
            j = 0;
            //getting Transaction Date
            getTransactionDate(TermDataPtr);
            printf("Today's Date is ");
            for (uint8_t i = 0; i < 10; i++)
            {
                printf("%c", TermData.transactionDate[i]);
                TermData.transactionDate[i] = TermData.transactionDate[i];
            }
            printf("\n");

            //checking if the card is expired or not
            j = isCardExpired(CardData, TermData);
            if (j != 0)
            {
                printf("Card Expired\n");
                continue;
            }
            else
            {
                j = 0;
            }
            // getting transaction amount 
            j = getTransactionAmount(TermDataPtr);
            if (j != 0)
            {
                continue;
            }
            transDataPtr->terminalData.transAmount = TermDataPtr->transAmount;
            j = 0;
            //Setting max amount
            j = setMaxAmount(TermDataPtr);
            if (j != 0)
            {
                continue;
            }
            transDataPtr->terminalData.maxTransAmount = TermDataPtr->maxTransAmount;
            j = 0;
            j = isBelowMaxAmount(transDataPtr);
            if (j != 0)
            {
                transData.transState = 2;
                continue;
            }
            j = 0;
            //checking if the account is valid or not
            j = isValidAccount(CardDataPtr);
            if (j != 0)
            {
                transData.transState = 2;
                continue;
            }
            j = 0;
            //checking the available amount
            j = isAmountAvailable(TermDataPtr);
            if (j != 0)
            {
                transData.transState = 1;
                continue;
            }
            j = 0;
            
            //checking the validity of the account
            j = saveTransaction(transDataPtr);
            transData.transactionSequenceNumber++;
        };
    };
};
