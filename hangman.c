#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>


void ruleBook()
{
  char anyKey; //variable to store/simulate key press

  printf("\n\n"); //Rules
  printf("                             The Rules                                \n");
  printf("-----------------------------------------------------------------------\n");
  printf("|You have 6 lives, each incorrect letter in your guess, is a lost life|\n");
  printf("|With each lost life comes a new hangman body part                    |\n");
  printf("|You may enter in entire word guesses                                 |\n");
  printf("|Best of luck, and may the best man(Hangman) win                      |\n");
  printf("-----------------------------------------------------------------------\n");
  printf("press any key to continue: ");
  scanf("%c", &anyKey);

}

void showHangman(int lives) //Function to show hangman, based on lives left number
{
  char man[8][15] ={
                   "  _______     \n", //Array to store hangman
                   " |       |    \n",
                   " |       |    \n",
                   " |            \n",
                   " |            \n",
                   " |            \n",
                   " |___________ \n",
                   " |___________|\n",
                  };
  if(lives == 5) //Depending on the number of lives left, the bodypart will be
  {              //updated in the array

      man[3][9]= 'O'; //head
  }
  else if(lives == 4)
  {
      man[3][9]= 'O'; //head
      man[4][9]= '|'; //body
  }
  else if(lives == 3)
  {
      man[3][9]= 'O'; //head
      man[4][9]= '|'; //body
      man[4][8]= '/'; //arm1
  }
  else if(lives == 2)
  {
      man[3][9]= 'O'; //head
      man[4][9]= '|'; //body
      man[4][8]= '/'; //arm1
      man[4][10]= '\\'; //arm2
  }
  else if(lives == 1)
  {
      man[3][9]= 'O'; //head
      man[4][9]= '|'; //body
      man[4][8]= '/'; //arm1
      man[4][10]= '\\'; //arm2
      man[5][8]= '/'; //leg1
  }
  else if(lives == 0)
  {
      man[3][9]= 'X'; //dead head
      man[4][9]= '|'; //body
      man[4][8]= '/'; //arm1
      man[4][10]= '\\'; //arm2
      man[5][8]= '/'; //leg1
      man[5][10]= '\\'; //leg2
  }

  int i, j;

  for (i = 0; i < 8; i ++) //Printing the 2d array to display on screen
  {
      for (j = 0; j < 15; j ++)
      {
        printf("%c", man[i][j]);
      }
  }
}

void displayWord(char string[13], int lenString) //Function to display string with
{                                                //gaps
  int i = 0;

  for (i = 0; i < lenString; i ++)
  {
    printf("%c ", string[i]);
  }
  printf("\n");
}

int inString(char geuss, char string[13], int lenString) //Function to check
{                                                        //if value is in string
  int i;

  for(i = 0; i < lenString; i ++)
  {
    if (string[i] == geuss)
    {
      return 1;
    }
  }
  return 0;
}


int checkGameWon(char string[13], int strLen) //Function to check if game is won
{                                             //by seeing if any blank spots remain
  int i;

  for (i = 0; i < strLen; i ++)
  {
    if (string[i] == '_')
    {
      return 0;
    }
  }

  return 1;
}

void welcome() //Large welcome function
{
  printf(" **    **     ***     **    **   *****   **    **     ***    **    **\n");
  printf(" **    **    ** **    ***   **  **       ***  ***    ** **   ***   **\n");
  printf(" **    **   **   **   ****  **  **       ** ** **   **   **  ****  **\n");
  printf(" ********  *********  ** ** **  **  ***  **    **  ********* ** ** **\n");
  printf(" **    **  **     **  ** ** **  **   **  **    **  **     ** ** ** **\n");
  printf(" **    **  **     **  **  ****  **   **  **    **  **     ** **  ****\n");
  printf(" **    **  **     **  **   ***   ******  **    **  **     ** **   ***\n");
}

int main()
{
  welcome(); //call welcome
  ruleBook(); //display rules
  srand((unsigned int) time(NULL)); //seed random numbers


  printf("\x1B[1;1H\x1B[2J"); //clear screen

//--------------------------------
  FILE *fp; //creating file pointer

  char ans[15]; //variable where random word will be stored
  int counter, randLineNum; //counter to count current line number and random line number

  randLineNum = rand() % (213) + 1; //Creating a random line number between 1 and 233
                                    // as their are 233 words in text file,
                                    //random line number will represent which word we will look for

  fp = fopen("words.txt", "r"); //opening text file for reading information
  counter = 0; //setting counter to 0, as we have not counted line number yet

  while(!feof(fp)) //while we haven't reached the end of the file
  {
    counter += 1; //counter += 1, add how many lines have been read so far
    fscanf(fp, "%s", ans); //scanf in current line value

    if (counter == randLineNum) //if we are on the pre set random line,
    {                           //we have found our random word, so break!
      break;
    }
  }

  fclose(fp); //close the file
//---------------------------------
  char usrBuffer[26], usrInput, incorrectGuesses[6];
  int ansLen, i, gameState, j, lives, numGuesses;

  ansLen = strlen(ans);
  gameState = 1; //setting game state to True
  lives = 6; //giving 6 lives
  numGuesses = 0; //setting number of guesses, it will be used to index
                  //into the incorrectGuesses array

  char currentState[ansLen + 1]; // creating array of length of unkown word (ans),
                                //+ 1 is to store terminating char 0

  for (i = 0; i < ansLen; i ++)
  {
    currentState[i] = '_'; //setting all spots in array to equal blank '_'
  }
  currentState[ansLen] = 0; //setting terminating char to be 0

  for (i = 0; i < 6; i ++)
  {
    incorrectGuesses[i] = '0'; //setting all values in incorrect geusses = to '0',
  }                           //to ensure that we can control what is printed from this array later


  do //do play game while gamestate = 1
  {
    showHangman(lives); //show current hangman
    displayWord(currentState, ansLen); //display current word state
    printf("Please enter in your guess: "); //asking for geusses
    scanf("%s", usrBuffer); //setting guess to usrBuffer as we want to later filter this input
    getchar();

    printf("\x1B[1;1H\x1B[2J"); //clearing screen
    for (i = 0; i < strlen(usrBuffer); i ++) //the double for loop is used to compare each element of
    {                                        //buffer string with each element of the answer string

      usrInput = tolower(usrBuffer[i]); //making sure uppercase inputs are ignored
      //as soon as we get the usrInput
      //we need to check the count

      if (inString(usrInput, ans, ansLen) == 0) //checking if geuss is in string
      {                                         //if not, take away a life as guess is wrong
        lives -= 1;
        incorrectGuesses[numGuesses] = usrInput; //adding to array of wrong guesses
        numGuesses += 1;                         //adding to number of geusses as next time
      }                                          //we will index into next slot

      if (lives == 0) //if no lives left
      {
        showHangman(lives); //show Hangman
        printf("You lost\n"); //print loss mesage
        printf("The word was: %s\n", ans);
        gameState = 0; //set gameState to False, to break from main loop
      }

      for (j = 0; j < ansLen; j ++)
      {
        if (usrInput == ans[j]) //the double for loop comparison is in this if statement
        {
          currentState[j] = usrInput; //setting the correct user guess to the correct location of the array
        }

      }

    }

    if (checkGameWon(currentState, ansLen) == 1) //if game is won
    {
      showHangman(lives); //display hangman
      printf("You had %i lives left\n", lives); //print winning message
      printf("You WON!!!!\n");
      gameState = 0; //set gameState to False to break from main loop
    }

    if (gameState == 1) //only if the game is still going
    {
      printf("Incorrect Guesses: "); //display the incorrect guesses so far
      for (i = 0; i < 6; i ++)
      {
        if (incorrectGuesses[i] == '0') //making sure we don't print the extra slots
        {                               //of incorrectGuesses as these mistakes have not been made yet
          break;
        }
        printf("%c ", incorrectGuesses[i]);
      }
      printf("\n");
    }

  }
  while (gameState == 1); //do play game while gamestate = 1
}
