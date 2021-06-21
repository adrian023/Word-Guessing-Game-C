#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void new_game();
int try_again();
void add_word();
void choose_category();
struct category{
	char word[200];	
};

FILE *word_bank;

void main(){
	int key;
	int choice;
	do{
		printf("\nWORD GUESSING GAME\n");	
		printf("\n|1| - ADD WORD");
		printf("\n|2| - PLAY GAME");
		do{
			key=getch()-48;
		}while(key!=1 && key!=2);
		switch(key){
			case 1:
				system("cls");		
				add_word();
				system("cls");		
				break;
			case 2:
				system("cls");
				new_game();
				system("cls");		
				break;	
		}
		printf("\n\n Do you want to try again? Y/N");
		do{
			choice=getch();			
		}while(choice!=89 && choice!=121 && choice!=78 && choice!=110);
		system("cls");			
	}while(choice==89 || choice==121);

}
void choose_category(){
	int key;
	printf("\nchoose category:");
	printf("\n|1| - ANIMALS");
	printf("\n|2| - COUNTRIES");
	printf("\n|3| - FOOD");
	while(key!= 1 && key!=2 & key!=3){
		key=getch()-48;	
		switch(key){
		case 1:
			word_bank=fopen("animals.txt","r+");
			break;	
		case 2:
			word_bank=fopen("countries.txt","r+");	
			break;
		case 3:
			word_bank=fopen("foods.txt","r+");	
			break;
		default:
			printf("\nPLEASE SELECT VALID CHOICE");
			break;
		}
	}
}

void add_word(){
	printf("ADD WORD");
	choose_category();
	fseek(word_bank,0,SEEK_END);	
	char word[20];
	printf("\nEnter new word: ");
	scanf(" %s",&word);
	getchar();
	fprintf(word_bank,"\n%s",word);
	fclose(word_bank);
}
void new_game(){
	printf("GUESS THE WORD");	
	choose_category();
	fseek(word_bank,0,SEEK_SET);	
	struct category list[100];
	int i=-1,j,k;	
	char code[30];
	while( fscanf(word_bank,"%s",code) != EOF){
		i++;
		strcpy(list[i].word,code);	
	}
	fclose(word_bank);
//GENERATE RANDOM NUMBER;
	int rand_index;
	srand ( time(NULL) );	

    rand_index = (rand() % (i - 0 + 1)) + 0;

	char mys_word[100];
	strcpy(mys_word,list[rand_index].word);
	char string[100];

//GUESSING PART
	for(j=0;j<strlen(mys_word);j++){
		string[j]='_';	
	}
	int finish=0,tries=5,error,check;
	char entry;
	do{
		error=1;
		check=0;
		printf("\n\n");
		for(j=0;j<strlen(mys_word);j++){
			printf("%c ",string[j]);	
		}
		printf("\n\nEnter a letter: ");
		entry=getche();

		for(j=0;j<strlen(mys_word);j++){
			char letter=mys_word[j];
			if(entry==letter){
				error=0;
				for(k=0;k<strlen(string);k++){
					if(entry==string[k]){
					check=1;	
					break;						
					}
				}
				if(check==0){
					for(k=0;k<strlen(string);k++){
						if(entry==mys_word[k]){
							error=0;
							string[k]=entry;			
							finish++;					
						}	
				
					}
				break;
				}
			}	
		}
		printf("\n\n");
		if(error==1){
			tries--;
			printf("\nThat letter is not part of the mystery word. You have %d tries remaining",tries);
		}
		if(finish==strlen(mys_word)){
			printf("\nCONGRATULATIONS YOU GUESSED THE WORD %s!!!",string);
		}
		else if(tries==0){
			printf("\nGAME OVER!!! YOU RAN OUT OF TRIES");
			printf("\nTHE MYSTERY WORD IS %s",mys_word);
		}
	}while(finish!=strlen(mys_word) && tries!=0);
	getch();
}

int try_again(){
	int choice;
	do{
		choice=getch();			
	}while(choice!=89 && choice!=121 && choice!=78 && choice!=110);
	return choice;	
}
