#define _GNU_SOURCE
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<errno.h>

#define MAXLEN 20
#define MAXWORDS 100
#define WORDLEN 25
#define bool int
#define true 1
#define false 0


char lowercase(char c) {
    char s;
    if(c >= 65 && c <= 90) {
        s = c + 32;
        return s;
    } 
    else {
        return c;
    }
}

bool isWordGuessed(const char* word, char* lg) {
    int num = 0;
    size_t won = strlen(word);
    size_t lgn = strlen(lg);
    for(int i=0; i < won; i++ ) {
        for(int j = 0; j < lgn; j++) {
            if( *(lg + j) == *(word + i) ) {
                num++;
                goto L3;
           }    
        }
        L3:
        ;
    }
    if(num == won) {
        return true;
    }
    else {
        return false;
    }
} 

void getGuessedWord(const char* word, char* lig) {
    char gessedWord[WORDLEN] ;
    size_t won = strlen(word);
    size_t lgn = strlen(lig);
    int z = 0;
    for(int i=0; i < won; i++) {
        bool flag = false;
        for (int j=0; j<lgn; j++) {
            if( *(lig + j) == *(word + i) ) {
                gessedWord[z] = *(word + i);
                z++;
                flag = true;
                goto L2;
            }
        }
        L2:
        ;
        if (!flag) {
            gessedWord[z] = '_';
            z++;
        }
    }
    gessedWord[z] = '\0';
    
    for(int y=0; y < z; y++) {
        printf("%c", gessedWord[y]);
    }
}



void getAvailableLetters(const char* lg) {
    const char* letters = "abcdefghijklmnopqrstuvwxyz" ;
	char available[WORDLEN];
    int z = 0, i, j;
    size_t len = strlen(letters);
    size_t lgn = strlen(lg);
	for ( i =0 ; i < len; i++) {
	bool flag = false;
        for ( j = 0; j < lgn ; j++ ) {
			if ( *(lg+j) == *(letters+i)) {
				flag = true;
                goto L1;
			}
		}
        L1:
        ;
	    if(!flag) {
            available[z] = *(letters+i);
            z = z + 1;
   		}
	}
    available[z] = '\0';
    for(int y=0; y < z; y++) {
        printf("%c", available[y]);
    }
   
}

void startHangMan(const char* sword) {
    int misses = 0;
    char inputchar;
    char sa[9];
    int z = 0;
    size_t swn = strlen(sword);
    
    printf("Welcome To HangMan Game\n");
    printf("I am thinking of a word that is %zu letters long\n", swn);

    for(int g=0; g<swn; g++) {
        printf("_");
    }
    printf("\n\n");
    printf("Miss: 0  Enter a letter: ");
    while(misses <= 8) {
        printf("\n");
        scanf("%c", &inputchar); // takiing two chars instead on one
        if(inputchar != '\n') {

        inputchar = lowercase(inputchar);

        bool saflag = false;
        size_t san = strlen(sa);
        if (san >= 1) {
        for(int q=0; q<san; q++) {
            if(inputchar == sa[q]) {
                printf("You already entered %c \n", inputchar);
                char* ew = sa;
                getGuessedWord(sword, ew);
                printf("\n");
                saflag = true;
                goto L4;
            }
        }
        L4:
        ;
        }

        if(!saflag) {
            sa[z] = inputchar;
            z++;

            bool flagm = false;
            for(int c=0; c < swn; c++) {
                if( inputchar ==  *(sword + c)) {
                    flagm = true;
                    if(isWordGuessed(sword, sa)) {
                        printf("%s\n", sword);
                        printf("Game Sucessfully Completed\n");
                        return;
                    }
                    else {
                        sa[z] = '\0';
                        char* ew = sa;
                        getGuessedWord(sword, ew);
                        printf("\n");
                    }
                    goto L5;
                }
            }
            L5:
            ;
            if(!flagm) {
                printf("Wrong input\n");
                misses++;
                sa[z] = '\0';
                char* we = sa;
                getGuessedWord(sword, we);
            }
        }
        if(misses <= 8) {
            printf("\n\n");
            printf("Miss: %d", misses);
            printf("  Enter a letter from: ");
            getAvailableLetters(sa);
        } 


        } 
    } 
    printf("\n\nGame Over\n");
    return;
}


int main(void) {
#if 1 
   // char* blist[MAXWORDS];
    int z = 0; 
    FILE	*words;										/* input-file pointer */
    char	*words_file_name = "words.txt";		/* input-file name    */
    char    *line = NULL;
    size_t  len = 0;
    ssize_t read;
    char a[MAXWORDS][MAXLEN];
    char* bli[10];
    words	= fopen( words_file_name, "r" );
    if ( words == NULL ) {
        fprintf ( stderr, "couldn't open file '%s'; %s\n",
                words_file_name, strerror(errno) );
        exit (EXIT_FAILURE);
    }
    while((read = getline(&line, &len, words)) != -1) {
   //     *(blist +z) = line;
        strcpy(a[z],line);
        *(*(a + z) + (read -1)) = '\0';
        z++;
    }
    if( fclose(words) == EOF ) {			/* close input file   */
        fprintf ( stderr, "couldn't close file '%s'; %s\n",
                words_file_name, strerror(errno) );
        exit (EXIT_FAILURE);
    }

#endif
    srand(time(NULL));
    int r = rand() % z; 

    const char* sword = *(a + r);
 
    startHangMan(sword);
}
