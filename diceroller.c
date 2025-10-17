#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <string.h>

typedef struct{
    int diceType;
    int result; 
} RollResult;

int getRolls(char rolls[][6], int max, RollResult results[]);
int getBonus();


int main(){

char choice;
srand(time(NULL));

do{

system("cls");

RollResult results[100];


char rolls[6][6] = {0};

int sum1 = 0;
int totalThrow = getRolls(rolls, 6, results);
int bonus = getBonus();


        printf("\nYou rolled:\n");
    for (int i = 0; i < totalThrow; i++) {
        printf("D%d:%d\n", results[i].diceType, results[i].result);
    }
    for (int j = 0; j < totalThrow; j++){

        sum1 += results[j].result;
    }


int everything = bonus + sum1;
    printf("Roll sum:%d\n", sum1);
    printf("Bonus:%d\n", bonus);
    printf("Total:%d\n", everything);

    char custom[10];
    int customBonus;
    printf("\nDo you have any more more bonuses to add?\n>");
        fgets(custom, 10, stdin);
    customBonus = atoi(custom);
    int everything2 = everything + customBonus;
    if (customBonus > 0){
        printf("Total:%d\n", everything2);
    }
    
    
    printf("Press Q to exit or Enter to restart\n");
    char input[8];
    
    fgets(input, sizeof(input), stdin);
    choice = input[0];
    // for debug printf("You typed: '%c' (ASCII %d)\n", choice, choice);
    
    
}while (choice != 'q' && choice != 'Q');
printf("Goodbye");
Sleep(1000);
return 0; 
}
int getRolls(char rolls[][6], int max, RollResult results[]){

    RollResult final = {0, 0};

    int count = 0;
    int rolled;
    int diceType;

    printf("What dice?\n>");
    
    for (int i = 0; i < max; i++){

        fgets(rolls[i], 5, stdin);

        if (!strchr(rolls[i], '\n')) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF); 
        }
        rolls[i][strcspn(rolls[i], "\n")] = '\0';

        if (strlen(rolls[i]) == 0){
            break;
        }
        count++;
    }    

    int throw = 0;

    for (int i = 0; i < count; i++){

        int rollAmount;
        int diceType;
        
        
        
        sscanf(rolls[i], "%dd%d", &rollAmount, &diceType);
        for(int i = rollAmount; i > 0; i--){

            rolled = rand () % diceType + 1;
             

            results[throw].diceType = diceType;
            results[throw].result = rolled;
            throw++;
        }
        
     }
    return throw;
}

int getBonus(){
    FILE *fptr;
    fptr = fopen("dnd.txt", "r");
    if (fptr == NULL){
        printf("Error opening file.\n");
    }
    
    int values[100];
    char line[1024];
    int count = 0;

    while(fgets(line, sizeof(line), fptr) != NULL){

        if (sscanf(line, "%d", &values[count]) ==1 ){

        count++;
        }
        
    }

    printf("\nWhich stat would you like to use?: (type number)\n");
    printf("1.Attack 2.Initiative 3.Strength\n"
            "4.Dexterity 5.Constitution 6.Intelligence\n"
            "7.Wisdom 8. Charisma 9.Acrobatics\n"
            "10. Animal Handling 11.Arcana 12.Athletics\n"
            "13.Deception 14. History 15. Insight\n"
            "16.Intimidation 17.Investigation 18.Medicine\n"
            "19.Nature 20.Perception 21.Performance\n"
            "22.Persuasion 23.Religion 24.Sleight of Hand\n"
            "25.Stealth 26.Survival\n>");
    int bonusCountr;
    int bonus;
    char bonusChoice[10];
    fgets(bonusChoice, sizeof(bonusChoice), stdin);
    
    bonusCountr = atoi(bonusChoice);

    bonus = values[bonusCountr - 1];
    
    

    fclose(fptr);
    return bonus;
}

