#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
static float balance = 0;
static float tracker = 0;
static float rebet = 0;
/*
Exit Error Codes:
1 - pSize exceeds maximum value of 30. int array pCards can only hold 30 values.
2 - dSize exceeds maximum value of 30. int array dCards can only hold 30 values.
3 - scanning float when depositing error. Usually happens when user inputs a character.
4 - scanning float when placing bet error. Usually happens when user inputs a character.
*/


float deposit(float x);
float placebet(float balance);
int play(float bet);
void gameUpdate(int *pCards, int *dCards, int pSize, int dSize);
void splitUpdate(int *pCards, int *dCards, int pSize, int dSize, int pSize2);

void splitUpdate(int *pCards, int *dCards, int pSize1, int dSize, int pSize2){
	int dTot = 0;
	int dAce = 0;
	int pTot1 = 0;
	int pTot2 = 0;
	int pAce1 = 0;
	int pAce2 = 0;
	system("CLS");
	printf("Current Balance = %.2f\nBet = %.2f\n\n",balance,tracker);
	printf("Dealer Shows: ");
	for(int i = 0; i < dSize; i++){
		if(dCards[i] == 1){
			printf("A ");
			dTot += 11;
			dAce++;
		}else{
			printf("%d ",dCards[i]);
			dTot += dCards[i];
		}
	}
	Sleep(100);
	if(dTot > 21 && dAce > 0){
		dTot -= 10;
		dAce = 0;
	}
	printf("(%d)",dTot);
	printf("\n");
	printf("Player Hand 1 Shows: ");
	for(int i = 0; i < pSize1; i++){
		if(pCards[i] == 1){
			printf("A ");
			pTot1 += 11;
			pAce1++;
		}else{
			printf("%d ",pCards[i]);
			pTot1 += pCards[i];
		}
	}
	if(pTot1 > 21 && pAce1 > 0){
		pTot1 -= 10;
		pAce1 = 0;
	}
	printf("(%d)",pTot1);
	printf("\nPlayer Hand 2 Shows: ");
	for(int i = 15; i < pSize2 + 15; i++){
		if(pCards[i] == 1){
			printf("A ");
			pTot2 += 11;
			pAce2++;
		}else{
			printf("%d ",pCards[i]);
			pTot2 += pCards[i];
		}
	}
	if(pTot2 > 21 && pAce2 > 0){
		pTot2 -= 10;
		pAce2 = 0;
	}
	printf("(%d)",pTot1);
	printf("\n");
}

void gameUpdate(int *pCards, int*dCards, int pSize, int dSize){
	int dTot = 0;
	int dAce = 0;
	int pTot = 0;
	int pAce = 0;
	system("CLS");
	printf("Current Balance = %.2f\nBet = %.2f\n\n",balance,tracker);
	printf("Dealer Shows: ");
	for(int i = 0; i < dSize; i++){
		if(dCards[i] == 1){
			printf("A ");
			dTot += 11;
			dAce++;
		}else{
			printf("%d ",dCards[i]);
			dTot += dCards[i];
		}
	}
	Sleep(100);
	if(dTot > 21 && dAce > 0){
		dTot -= 10;
		dAce = 0;
	}
	printf("(%d)",dTot);
	printf("\n");
	printf("Player Shows: ");
	for(int i = 0; i < pSize; i++){
		Sleep(100);
		if(pCards[i] == 1){
			printf("A ");
			pTot += 11;
			pAce++;
		}else{
			printf("%d ",pCards[i]);
			pTot += pCards[i];
		}
		if(pTot > 21 && pAce > 0){
			pAce--;
			pTot-=10;
		}
	}
	Sleep(100);
	printf("(%d)",pTot);
	printf("\n");
	Sleep(100);
}

float deposit(float x){
	float y;
	int ctr = 0;
	do{
		ctr++;
		system("CLS");
		printf("Deposit Amount: ");
		scanf("%f",&y);
		if(ctr > 2500){
			exit(3);
		}
		if(y > 0)
			return y;
		printf("Invalid Amount.\nPlease Try Again.\n");
	}while(1);
}

float placebet(float balance){
	float bet;
	printf("(Enter 1 For Rebet)\n(Enter 2 For All-In)\nEnter Bet Amount: ");
	do{
		scanf("%f",&bet);
		if(bet < 0.1 && bet > -0.1)
			exit(4);
		if(bet == 1){
			bet = rebet;
		}
		if(bet == 2){
			bet = balance;
		}
		if(bet > 0 && bet <= balance)
			break;
		else if(bet > balance){
			printf("You do not have enough balance to cover your bet.\nPlease enter valid bet amount: ");
			continue;
		}
		printf("Bet must be larger than 0.\nPlease enter valid bet amount: ");
	}while(1);
	float bj = 1.5 * bet;
	rebet = bet;
	tracker = bet;
	//Return 0-Lose 1-Win 2-Push 3-Blackjack 4-Double Win 5- Double Lose 6- Split 2-win 7 Split 1-win 8 Split 2-lose//
	switch(play(bet)){
		case 0:
			printf("\nYou lost %.2f \n",bet);
			getch();
			return balance-bet;
		break;
		case 1:
			printf("\nYou won %.2f \n",bet);
			getch();
			return balance+bet;
		break;
		case 2:
			getch();
			return balance;
		break;
		case 3:
			printf("\nYou won %.2f \n",bet*1.5);
			getch();
			return balance+bj;
		break;
		case 4:
			printf("\nYou won %.2f \n",bet*2);
			getch();
			return (balance+bet+bet);
		break;
		case 5:
			printf("\nYou lost %.2f \n",bet*2);
			getch();
			return (balance-bet-bet);
		break;
		default:
			getch();
		break;
	}
}

int play(float bet){
	system("CLS");
	printf("Current Balance = %.2f\nBet = %.2f\n\n",balance,tracker);
	int pCards[30];
	int dCards[30];
	do{
		dCards[0] = rand() % 13;
	}while(dCards[0] == 0);
	//dCards[0] = 1;//ForceDealerAce
	if (dCards[0] > 10)
		dCards[0] = 10;
	if(dCards[0] == 1)
		printf("Dealer Shows: A (11)\n");
	else
		printf("Dealer Shows: %d\n",dCards[0]);
	do{
		pCards[0] = rand() % 13;
	}while(pCards[0] == 0);
	do{
		pCards[1] = rand() % 13;
	}while(pCards[1] == 0);
	if (pCards[0] > 10)
		pCards[0] = 10;
	if (pCards[1] > 10)
		pCards[1] = 10;
	int pTotal,dTotal;
	printf("Player Shows: ");
	//pCards[0] = 1;pCards[1] =10;//Force BlackJack
	//pCards[0] = 1;pCards[1] =1;//Force Pair A's
	if((pCards[0] == 1 && pCards[1] == 10)||(pCards[0] == 10 && pCards[1] == 1)){
		if(dCards[0] == 1 || dCards[0] == 10){
			do{
				dCards[1] = rand() % 13;
			}while(dCards == 0);
			if(dCards[1] >= 10){
				if(dCards[0] == 1){
					system("CLS");
					printf("Dealer Shows: A 10\nPlayer Shows: A 10\nPUSH\n");
					return 2;
				}
			}
			if(dCards[1] == 1 && dCards[0] == 10){
				system("CLS");
				printf("Dealer Shows: A 10\nPlayer Shows: A 10\nPUSH\n");
				return 2;
			}
		}
		printf("A 10 \nBlack Jack! Player wins %.2f\n",bet*1.5);
		return 3;
	}else{
		for(int i = 0; i < 2; i++){
			if(pCards[i] == 1){
				printf("A ");
			}else{
				printf("%d ",pCards[i]);
			}
		}
	}
	int tempVal = pCards[0] + pCards[1];
	if(pCards[0] == 1 || pCards[1] == 1)
		tempVal += 10;
	printf("(%d)",tempVal);
	printf("\n");
	int action;
	int fMove = 0;
	int dSize = 1;
	int pSize = 2;
	int Doubled = 0;
	int is21 = 0;
	int isSplit = 0;
	int inHand = 1;
	int spSize1 = 2;
	int spSize2 = 2;
	//action: 0-stand 1-hit 2-double 3-split//
	do{
		if((pCards[0] == pCards[1])&&(fMove == 0)){
			printf("Stand[0] Hit[1] Double[2] Split[3]\n");
		}else if(fMove == 0){
			printf("Stand[0] Hit[1] Double[2]\n");
		}else{
			printf("Stand[0] Hit[1]\n");
		}
		
		if(Doubled != 1 && is21 != 1){
			printf("Enter action: ");
			action = (getch() - 48);
		}
		if((action == 3 && pCards[0] != pCards[1])||(action < 0 || action > 3)){
			system("CLS");
			gameUpdate(pCards, dCards, pSize, dSize);
			printf("Invalid Action TRY AGAIN\n");
			continue;
		}		
		if(action == 0 || Doubled == 1 || is21 == 1){
			int dTot = 0;
			fMove = 1;
			do{
				dTot = 0;
				do{
					dCards[dSize] = rand() % 13;
				}while(dCards[dSize] == 0);
				if (dCards[dSize] > 10)
					dCards[dSize] = 10;
				dSize++;
				if(dSize == 31)
					exit(2);
				int dAce = 0;
				for(int i = 0; i < dSize; i++){
					if(dCards[i] == 1){
						dTot += 11;
						dAce ++;
					}else{
						dTot += dCards[i];
					}
					if(dTot > 21 && dAce > 0){
						dAce = 0;
						dTot-=10;
					}else if(dTot > 21 && dAce == 0){
						gameUpdate(pCards, dCards, pSize, dSize);
						Sleep(100);
						printf("\nDealer Bust\n");
						if(Doubled == 1)
							return 4;
						return 1;
					}
					if(dTot >= 17){
						int tempTot = 0;
						int tempAce = 0;
						for(int i = 0; i < pSize; i++){
							if(pCards[i] == 1){
								tempAce++;
								tempTot+=11;
							}else{
								tempTot+=pCards[i];
							}
							if(tempTot > 21){
								if(tempAce == 0){
									printf("\nPlayer Busts\n");
									if (Doubled == 1)
										return 5;
									return 0;
								}else if(tempAce > 0){
									tempAce--;
									tempTot -=10;
									continue;
								}
							}
						}
						gameUpdate(pCards, dCards, pSize, dSize);
						Sleep(100);
						if(tempTot == dTot){
							if((dCards[0] == 1 && dCards[1] == 10)||(dCards[0] == 10 && dCards[1] == 1)){
								printf("Dealer BlackJack");
								if(Doubled == 1)
									return 5;
								else
									return 0;
							}
							printf("\nPUSH\n");
							return 2;
						}else if(tempTot > dTot){
							printf("\nPlayer Wins \n");
							if(Doubled == 1)
								return 4;
							return 1;
						}else{
							printf("\nDealer Wins \n");
							if(Doubled == 1)
								return 5;
							return 0;
						}
					}
				}	
			}while(dTot < 17);
		}else if(action == 1){
			if(isSplit == 1){
				if(inHand == 1){
					do{
						pCards[spSize1] = rand() % 13;
					}while(pCards[spSize1] == 0);
					if (pCards[spSize1] > 10)
						pCards[spSize1] = 10;
					spSize1++;
				}else{
					do{
						pCards[spSize2] = rand() % 13;
					}while(pCards[spSize2] == 0);
					if (pCards[spSize2] > 10)
						pCards[spSize2] = 10;
					spSize2++;
					
				}
				splitUpdate(pCards,dCards,spSize1,dSize,spSize2);
			}else{
				fMove = 1;
				do{
					pCards[pSize] = rand() % 13;
				}while(pCards[pSize] == 0);
				if (pCards[pSize] > 10)
					pCards[pSize] = 10;
				pSize++;
				if(pSize == 31)
					exit(1);
				gameUpdate(pCards, dCards, pSize, dSize);
				Sleep(100);
				int pTot = 0;
				int pAce = 0;
				for(int i = 0; i < pSize; i++){
					if(pCards[i] == 1){
						pTot += 11;
						pAce ++;
					}else{
						pTot += pCards[i];
					}
					while(pTot > 21 && pAce > 0){
						pAce--;
						pTot -=10;
					}
					if(pTot > 21 && pAce == 0){
						gameUpdate(pCards, dCards, pSize, dSize);
						printf("\nPlayer Bust\nEnter any character to continue: ");
						return 0;
					}
				}
				if(pTot == 21){
					is21 = 1;
				}
			}
		}else if(action == 2 && fMove == 0){
			if(balance < bet * 2){
				printf("Not enough balance to double down.\n");
				continue;
			}
			fMove = 1;
			Doubled = 1;
			do{
				pCards[pSize] = rand() % 13;
			}while(pCards[pSize] == 0);
			if(pCards[pSize] > 10)
				pCards[pSize] = 10;
			pSize++;
			int tempValP = 0;
			int tempValPa = 0;
			for(int i = 0; i < pSize; i++){
				if(pCards[i] == 1){
					tempValP += 11;
					tempValPa++;
				}else{
					tempValP += pCards[i];
				}
				if(tempValP > 21 && tempValPa > 0){
					tempValP -= 10;
					tempValPa--;
				}
			}
			if(tempValP > 21){
				gameUpdate(pCards, dCards, pSize, dSize);
				printf("\nPlayer Bust\nEnter any character to continue: \n");
				return 5;
			}
		}else if(action == 3 && fMove == 0){
			pCards[15] = pCards[1];
			do{
				pCards[1] = rand() % 13;
			}while(pCards[1] == 0);
			do{
				pCards[16] = rand() % 13;
			}while(pCards[16]== 0);
			if(pCards[1] > 10)
				pCards[1] = 10;
			if(pCards[16] > 10)
				pCards[16] = 10;
			isSplit = 1;
			fMove = 1;
			splitUpdate(pCards,dCards,spSize1,dSize,spSize2);
		}
	}while(1);
}

int main(){
	srand(time(NULL));
	printf("-------------------------------\n");
	printf("---------------@---------------\n");
	printf("--------------@@@--------------\n");
	printf("-------------@@@@@-------------\n");
	printf("-----------@@@@@@@@@-----------\n");
	printf("---------@@@@@@@@@@@@@---------\n");
	printf("-------@@@@@@@@@@@@@@@@@-------\n");
	printf("----@@@@@@@@@@@@@@@@@@@@@@@----\n");
	printf("---@@@@@@@@@@@@@@@@@@@@@@@@@---\n");
	printf("--@@@@@@@@@@@@@@@@@@@@@@@@@@@--\n");
	printf("-@@@@@@@@@@@@@@@@@@@@@@@@@@@@@-\n");
	printf("--@@@@@@@@@@@-@@@-@@@@@@@@@@@--\n");
	printf("---@@@@@@@@@--@@@--@@@@@@@@@---\n");
	printf("------@@@@----@@@----@@@@------\n");
	printf("-------------@@@@@-------------\n");
	printf("----------@@@@@@@@@@@----------\n");
	printf("---------@@@@@@@@@@@@@---------\n");
	printf("-------------------------------\n");
	printf("-----------BlackJack-----------\n");
	printf("------Made-by-KingEvariste-----\n");
	printf("-------------------------------\n");
	printf("---Press-Any-Key-to-Continue---\n");
	printf("-------------------------------\n");
	printf("\n\nhttps://github.com/KingEvariste\n\n");
	getch();
	system("CLS");
	do{
		balance = deposit(balance);
		if(balance < 0.1 && balance > -0.1){
			exit(3);
		}
		while(balance > 0){
			system("CLS");
			printf("Balance: %.2f\n",balance);
			balance = placebet(balance);
		}
		system("CLS");
		printf("You ran out of money.\nPress Enter to Deposit more!");
		getch();
	}while(1);
	return 0;	
}
