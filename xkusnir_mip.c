
/*
This is a rather simple console application, for processing text files with predefined structure;
it means that:
 	-every line holds one type of information
	-one data chunk consists of 7 LINES
	-those data clusters are divided by '\n', empty char
	-it is alphabetically sorted by name
the input for program:
	-alpha numeric values from console
	-and text file:  "priestupky.txt"

what program does:
	-reads data from structured text file and loads it to list of structures
	-allows user to append to the list, and it sorts appended cell to already sorted list
	-allows user to print the content from list into console
	-allows user to print out palindromes (from car plates) and it also prints name (does not have to be palindrome)
	-prints monthly reward of officer
	-prints offences from given year

@author xkusnir
@date: 2018/19
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAXIMUM_STRING_SIZE 50
#define SMALL_REVENUE 3.8/100
#define BIG_REVENUE 5.2/100
#define CAR_PLATE_SIZE 8
#define LINES_PER_CELL 7
#define CUT_MONTHS 10000
#define ONE_RECORD 1
#define CUT_DAYS 100
#define CLOSED 0
#define ZERO 0
#define TRUE 1
#define PREV 1
#define END 0

typedef struct {
	char name[MAXIMUM_STRING_SIZE];
	char sex;
	int  birthYear;
	char carPlate[CAR_PLATE_SIZE];
	int  lawViolation;
	int fee;
	long datum;

}LIST_CAR_OFFENSES;

LIST_CAR_OFFENSES *loadFromTxtFile(LIST_CAR_OFFENSES *list, FILE *file_handler, int *numberOfRecords);
LIST_CAR_OFFENSES *appendToList(LIST_CAR_OFFENSES *list, int *numberOfRecords);
void fillCell(LIST_CAR_OFFENSES *list, FILE *file_handler, int counter);
void printMonthlyOffenses(LIST_CAR_OFFENSES *list, int numberOfRecords);
void printMounthlyReward(LIST_CAR_OFFENSES *list, int numberOfRecords);
void printPalindrome(LIST_CAR_OFFENSES *list, int numberOfRecords);
void printOffenses(LIST_CAR_OFFENSES *list, int numberOfRecords);
void fillList(LIST_CAR_OFFENSES *list, FILE *file_handler);
void halt(LIST_CAR_OFFENSES *list ,FILE *file_handler);


int main() {

	LIST_CAR_OFFENSES *list=NULL;
	int numberOfRecords = ZERO;
	FILE *file_handler = NULL;
	char charInput;

	while (charInput = getchar()) {

		switch (charInput) {
			case 'o':
				list = loadFromTxtFile(list, file_handler, &numberOfRecords);
				break;
			case 'v':
				printOffenses(list, numberOfRecords);
				break;
			case 'x':
				printMonthlyOffenses(list, numberOfRecords);
				break;
			case 'r':
				printMounthlyReward(list, numberOfRecords);
				break;
			case 'p':
				printPalindrome(list, numberOfRecords);
				break;
			case 'a':
				list=appendToList(list, &numberOfRecords);
				break;
			case 'k':
				halt(list, file_handler);
				break;
		}
		if('k' == charInput) break;
	}
	return END;
}

/*
	loadFromTxtFile,
		description:
		 	-is a function that loads text file called "priestupky.txt" and files the list of structures

		@param LIST_CAR_OFFENSES *pointer (which is pointer to a structure)
		@param FILE *pointer (which is pointer to a buffer)
		@param 	int *pointer (which is pointer to an integer)

		@return LIST_CAR_OFFENSES *pointer (which is pointer to a structure)
*/
LIST_CAR_OFFENSES *loadFromTxtFile(LIST_CAR_OFFENSES *list, FILE *file_handler, int *numberOfRecords) {

	int number_of_lines = ZERO;
	int counter = ZERO;
	char line[50];

	if(*numberOfRecords) {

		free(list);
	}

	if ((file_handler = fopen("priestupky.txt", "r")) == NULL) {

		printf("Subor nebol otvoreny\n");
		return list = NULL;
	}

	while (fgets(line, MAXIMUM_STRING_SIZE, file_handler) != NULL) {

		if (line[ZERO] == '\n'){
			continue;
		}

		number_of_lines++;
	}

	*numberOfRecords = number_of_lines / LINES_PER_CELL;

	if(	(list = (LIST_CAR_OFFENSES *)malloc(*numberOfRecords * sizeof(*list))) == NULL){

		printf("Pole nie je naplnene\n");
	}

	rewind(file_handler);
	fillList(list, file_handler);

	return list;
}

/*
halt,
	procedure description:
		-it deallocs memory, closes file, points pointers back to null;

	@param LIST_CAR_OFFENSES *pointer (which is pointer to a structure)
	@param  FILE *pointer (which is pointer to a buffer)
*/
void halt(LIST_CAR_OFFENSES *list ,FILE *file_handler) {

	if (fclose(file_handler)==CLOSED) {
		printf("subor sa nepodarilo uzatvorit\n");
	}

	free(list);
	list = NULL;
}

/*
fillList,
	procedure description:
		-fills whole list of structures with data

	@param LIST_CAR_OFFENSES *pointer (which is pointer to a structure)
	@param  FILE *pointer (which is pointer to a buffer)
*/
void fillList(LIST_CAR_OFFENSES *list, FILE *file_handler){

	int counter=ZERO;

	while (feof(file_handler) == END) {

		fillCell(list, file_handler, counter);

		if (!(feof(file_handler))) {
			counter++;
			fscanf(file_handler, "\n");
		}
	}
}

/*
fillCell,
	procedure description:
		-fills structure

	@param LIST_CAR_OFFENSES *pointer (which is pointer to a structure)
	@param  FILE *pointer (which is pointer to a buffer)
	@param 	positive int

*/
void fillCell(LIST_CAR_OFFENSES *list, FILE *file_handler, int counter){

	fscanf(file_handler, "%[^\n]\n", list[counter].name);
	fscanf(file_handler, "%c", &list[counter].sex);
	fscanf(file_handler, "%d", &list[counter].birthYear);
	fscanf(file_handler, "%s", list[counter].carPlate);
	fscanf(file_handler, "%d", &list[counter].lawViolation);
	fscanf(file_handler, "%d", &list[counter].fee);
	fscanf(file_handler, "%ld", &list[counter].datum);
}

/*
printOffenses,
	procedure description:
		-prints out the content of list

	@param LIST_CAR_OFFENSES *pointer (which is pointer to a structure)
	@param 	positive int
*/
void printOffenses(LIST_CAR_OFFENSES *list, int numberOfRecords){

	for (int count = ZERO; count < numberOfRecords; count++) {

		printf("meno priezvisko: %s\n", list[count].name);
		printf("pohlavie: %c\n", list[count].sex);
		printf("rok narodenia: %d\n", list[count].birthYear);
		printf("SPZ: %s\n", list[count].carPlate);
		printf("typ priestupku: %d\n", list[count].lawViolation);
		printf("vyska pokuty: %d\n", list[count].fee);
		printf("datum priestupku: %d\n\n", list[count].datum);
	}
}

/*
printPalindrome,
	procedure description:
		-prints out palindromes (from carplates) and it also prints name (does not have to be palindrome)

	@param LIST_CAR_OFFENSES *pointer (which is pointer to a structure)
	@param 	positive int
*/
void printPalindrome(LIST_CAR_OFFENSES *list, int numberOfRecords){

	char tempString[CAR_PLATE_SIZE];

	if(list==NULL){
		return;
	}

	for (int count = ZERO; count < numberOfRecords; count++) {

		strcpy(tempString, list[count].carPlate);
		strrev(tempString);

		if(strcmp(tempString, list[count].carPlate) == ZERO){
			printf("%s %s\n", list[count].name, list[count].carPlate);
		}
	}
}


/*
appendToList,
	description:
	 	-is a function that allows user to append to the list, and it sorts appended cell to already sorted list

	@param LIST_CAR_OFFENSES *pointer (which is pointer to a structure)
	@param 	int *pointer (which is pointer to an integer)

	@return LIST_CAR_OFFENSES *pointer (which is pointer to a structure)
*/
LIST_CAR_OFFENSES *appendToList(LIST_CAR_OFFENSES *list, int *numberOfRecords){

	int temp;
	char tempLine[MAXIMUM_STRING_SIZE] = "";
	char line[MAXIMUM_STRING_SIZE] = "";

	if(list==NULL){
		if(	(list = (LIST_CAR_OFFENSES *)malloc(ONE_RECORD * sizeof(*list))) == NULL){
			printf("Pole nie je naplnene\n");
		}
		*numberOfRecords = ZERO;
	}

	list= realloc(list, (*numberOfRecords+ONE_RECORD)*sizeof(*list) );

	fgetc(stdin);
	fillCell(list, stdin, *numberOfRecords);

	LIST_CAR_OFFENSES templist;

	 for (int i = *numberOfRecords; i > ZERO; i--) {
		 if(strcmp(list[i-PREV].name, list[i].name) < ZERO){
			 break;
		 }else{
			 templist= list[i-PREV];
			 list[i-PREV]=list[i];
			 list[i]=templist;
		 }
	 }
	*numberOfRecords= *numberOfRecords + ONE_RECORD;
	return list;
}

/*
printMonthlyOffenses,
 procedure description:
	 -prints out offences from desired month

	input into console: YYYYmmdd

 @param LIST_CAR_OFFENSES *pointer (which is pointer to a structure)
 @param	positive int
*/
void printMonthlyOffenses(LIST_CAR_OFFENSES *list, int numberOfRecords){

 	long curretYear;
 	fscanf(stdin, "%ld", &curretYear);

	if(numberOfRecords == ZERO){
		return;
	}

	for (int count = ZERO; count < numberOfRecords; count++) {
		if((list[count].datum/CUT_MONTHS==curretYear/CUT_MONTHS) && list[count].lawViolation == ZERO){

			printf("meno priezvisko: %s\n", list[count].name);
			printf("SPZ: %s\n", list[count].carPlate);
			printf("datum priestupku: %d\n\n", list[count].datum);
		}
	}
}

/*
printMounthlyReward,
 procedure description:
	 -prints out mounth revenue/bonus/reward for police officer from records

	input into console: YYYYmmdd

 @param LIST_CAR_OFFENSES *pointer (which is pointer to a structure)
 @param 	positive int
*/
void printMounthlyReward(LIST_CAR_OFFENSES *list, int numberOfRecords){

	double sumOfReward = ZERO;
	long curretYear;
	fscanf(stdin, "%ld", &curretYear);

	if(numberOfRecords == ZERO){
		return;
	}

	for (int count = ZERO; count < numberOfRecords; count++) {
		if(list[count].datum/CUT_DAYS == curretYear/CUT_DAYS){

			if(list[count].lawViolation == TRUE){
				sumOfReward=sumOfReward+list[count].fee*BIG_REVENUE;
			}else{
				sumOfReward=sumOfReward+list[count].fee*SMALL_REVENUE;
			}
		}
	}
	printf("%.2lf\n", sumOfReward);
}
