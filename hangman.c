#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <unistd.h>


#define UP_ARROW 72
#define DOWN_ARROW 80
#define ENTER 13
#define CLEAR_SCREEN printf("\e[1;1H\e[2J")

#ifdef _WIN32
#define SLEEP(ms) Sleep(ms)
#elif defined(__linux__)||defined(__APPLE__)
#define SLEEP(ms) usleep((ms)*1000);
#endif


typedef struct{
    char word[21];
    char clue1[11];
    char clue2[11];
    char clue3[11];
}hangman;

typedef struct{
    char name[11];
    int score;
}player;

player User;
hangman genshin;

int key();
void gamePlay();
void clearScreen();
void printMenu();
void howToPlay();
void printLeaderboard();
void getName();
void debug();
void saveScore();

int main(){
    int select = 1;
    int t = 0;
    do{
    clearScreen();
    printMenu(select);
    switch(key()){
        case 0:
        continue;
        break;
        case 1:
        select--;
        if(select<1) select = 4;
        break;
        case 2:
        select++;
        if(select>4) select = 1;
        break;
        case 3:
        switch(select){
            case 1:
            clearScreen();
            getName();
            break;
            case 2:
            clearScreen();
            howToPlay();
            break;
            case 3:
            clearScreen();
            printLeaderboard();
            break;
            case 4:
            t = 1;
            break;
        }
        break;
    }
    }while(t!=1);
     for(int i =5; i>0; i--){
        clearScreen();
        printf("Thanks For Playing\n");
        printf("Exiting Program in %d", i);
        SLEEP(1000);
     }
     
    return 0;
}
int compare(const void *a, const void *b){
    return ((player*)b)->score - ((player*)a)->score;
}
void debug(){
    printf("alamak\n");
}

void saveScore(){
    FILE *fp;
    fp = fopen ("scoreboard.txt", "a");
    fprintf(fp, "%s#%d\n", User.name, User.score);
    fclose(fp);
}

void getName() {
    int t;
    do {
        clearScreen();
        printf("Enter your name (must be less than 10 characters, type \"exit\" to go back to the menu): ");
        scanf("%[^\n]", User.name);
        getchar();
        if (strlen(User.name) > 10) {
            printf("Name must be less than 10 characters.\n");
            getchar();
            t = 1;
        } else if (strcasecmp(User.name, "exit") == 0) {
            t = 0;
        } else {
            // debug();
            clearScreen();
            gamePlay();
            t = 0;
        }
    } while (t == 1);
}

void getWord(){
    hangman p[500];
    FILE *fp = fopen("wordlist.txt", "r");
    if(fp == NULL){
        printf("Error getting a word, wordlist.txt not found");
        getchar();
    }
    int c = 0;
    while(fscanf(fp, "%[^#]#%[^#]#%[^#]#%[^\n]", p[c].word, p[c].clue1, p[c].clue2, p[c].clue3)!= EOF){
        c++;
    }
    int r = rand() % c;
    strcpy(genshin.word, p[r].word);
    strcpy(genshin.clue1, p[r].clue1);
    strcpy(genshin.clue2, p[r].clue2);
    strcpy(genshin.clue3, p[r].clue3);
}
void gamePlay(){
    getWord();
    printf("Masih dalam tahap pengembangan ;-;\n");
    printf("Menyimpan skor %d", User.score);
    saveScore();
    getchar();
}  
void printLeaderboard(){
    player p[500];
    int c = 0;
    FILE *fp;
    fp = fopen("scoreboard.txt", "r");
    if(fp == NULL){
        printf("Error print leaderboard, maybe some file issue");
        getchar();
    }
    while(fscanf(fp, "%[^#]#%d\n", p[c].name, &p[c].score)!= EOF){
        c++;
    }
    qsort(p, c, sizeof(player), compare);
    printf("===== LEADERBOARD =====\n");
    printf("|   NAME   |   SCORE  |\n");
    printf("=======================\n");
    for(int i=0; i<c; i++){
        printf("|%-10s|%-10d|\n",p[i].name, p[i].score);
    }
    printf("=======================\n");
    printf("Press any key to continue.....");
    getchar();
    
}
void clearScreen(){
    CLEAR_SCREEN;
}
int key(){
    int c = getch();
    switch(c){
        case UP_ARROW:
            return 1;
            break;
        case DOWN_ARROW:
            return 2;
            break;
        case ENTER:
            return 3;
            break;
        default:
            return 0;
            break;
    }
}
void printMenu(int select){
    const char *logo =
        "                                                                                  \n"
        "                                               ____                              \n"
        "  ,----..                                    ,'  , `.                            \n"
        " /   /   \\                                ,-+-,.' _ |                            \n"
        "|   :     :                   ,---,    ,-+-. ;   , ||                     ,---,  \n"
        ".   |  ;. /               ,-+-. /  |  ,--.'|'   |  ;|                 ,-+-. /  | \n"
        ".   ; /--`      ,---.    ,--.'|'   | |   |  ,', |  ':    ,--.--.     ,--.'|'   | \n"
        ";   | ;  __    /     \\  |   |  ,\"' | |   | /  | |  ||   /       \\   |   |  ,\"' | \n"
        "|   : |.' .'  /    /  | |   | /  | | '   | :  | :  |,  .--.  .-. |  |   | /  | | \n"
        ".   | '_.' : .    ' / | |   | |  | | ;   . |  ; |--'    \\__\\/ : . .  |   | |  | | \n"
        "'   ; : \\  | '   ;   /| |   | |  |/  |   : |  | ,       ,\" .--.; |  |   | |  |/  \n"
        "'   | '/  .' '   |  / | |   | |--'   |   : '  |/       /  /  ,.  |  |   | |--'   \n"
        "|   :    /   |   :    | |   |/       ;   | |`-'       ;  :   .'   \\ |   |/       \n"
        " \\   \\ .'     \\   \\  /  '---'        |   ;/           |  ,     .-./ '---'        \n"
        "  `---`        `----'                '---'             `--`---'                 \n"
        "                                                                                  \n";

    printf(logo);
    const char *menu[]=
    { 
    "1. Play\n",
    "2. How To Play\n",
    "3. Leaderboard\n",
    "4. Exit\n"
    };
     int menuSize = sizeof(menu)/sizeof(menu[0]);
    
    for(int i = 0; i < menuSize; i++){
        if(i+1 == select){
            printf("-> %s", menu[i]);
        }
        else printf("   %s", menu[i]);
    }
}

void  howToPlay(){
    puts("                             How To Play                 ");
    puts("========================================================================");
    puts("1. Player will be given a random Genshin character");
    puts("2. Player can only guess one letter at a time");
    puts("3. If the letter is in the word, it will be revealed");
    puts("4. If the player guesses the word, player will get a score");
    puts("5. If the letter is not in the word, the player will lose a life");
    puts("6. If the player loses all lives, the game will end");
    puts("7. If the player die when the score above zero it will\n   save to the leaderboard, else it will not");
    puts("8. Player's score depend on the clue usage: \n    0 clues = 2x score\n    1 clues = 1.5x score\n    2 clues = 1.25x score\n    3 clues = 1x score");
    puts("Press any to continue.....");
    getchar();
}


