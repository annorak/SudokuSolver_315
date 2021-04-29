/* Neccesary Import Statements
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

/* CNIT 315 - Final Project: Sudoku Solver
 * 
 * @author Varun Viswanathan, Cole Hutchcraft, Michael Harman, Chris Risk, Connor Rice 
 * @author viswana8@purdue.edu, 
 * @Lab Section Friday 11:30 - 1:20, TA - Zahra Ghorrati
 * @version 1.0, April 28 2021
 * @file sudokuSolverFinal.c
 * 
 * This program solves precreated sudoku puzzles (if possible) and calls a public API 
 * to return back to the user the time and date in the Eastern Time Zone. 
 *  
 */
 
// N is the size of the 2D matrix   N*N
#define N 9

// Sudoku struct to hold the different puzzles
struct Sudoku
{
  int grid[N][N];
};

struct Sudoku easyPuzzle;
struct Sudoku mediumPuzzle;
struct Sudoku hardPuzzle;

/**
 * function to fill space with dashes for 
 * easier readability 
 * return nothing, void method 
 */
void spaceFiller(){
     printf("--------------------------------------------------------------\n");
}

/**
 * function to print the grid for 
 * easier readability 
 * return nothing, void method 
 */
void print(int arr[N][N]){
     for (int i = 0; i < N; i++)
      {
         for (int j = 0; j < N; j++)
            printf("%d ",arr[i][j]);
         printf("\n");
       }
}

/**
 * function to check whether it will be  
 * legal to assing num to row and col 
 * return int, for legality 
 */
int isSafe(int grid[N][N], int row, int col, int num){

    /*Iterate to see if same num is found 
    in similar row, then return 0 if thats true
    */
    for (int x = 0; x <= 8; x++)
        if (grid[row][x] == num)
            return 0;

    /*Iterate to see if same num  is found 
    in similar column, then return 0 if thats true
    */
    for (int x = 0; x <= 8; x++)
        if (grid[x][col] == num)
            return 0;
 
    /*Iterate to see if same num is found in 
    3 x 3 matrix, then return 0 if thats true
    */
    int startRow = row - row % 3,
                 startCol = col - col % 3;
   
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j +
                          startCol] == num)
                return 0;
    

    //otherwise return 1
    return 1;
}
 
/* Takes a partially filled-in grid and attempts
to assign values to all unassigned locations in
such a way to meet the requirements for
Sudoku solution (non-duplication across rows,
columns, and boxes) */

/**
 * function to assign values for all 
 * unsassigned locations and solve the actual puzzle.
 * ensures non-duplication for rows, columns, and boxes
 * return solvability
 */
int solvePuzzle(int grid[N][N], int row, int col)
{

    /*Check if 8 row, 9th column 
    have been reached (given 0 indexed matrix)
    and return true to avoid backtracking
    */
    if (row == N - 1 && col == N)
        return 1;

    /*Check to see if column value becomes 9
    and move to next row with column 0
    */
    if (col == N)
    {
        row++;
        col = 0;
    }

    /*Check to see if current posisiton 
    is already filled and iterate for next column
    */
    if (grid[row][col] > 0)
        return solvePuzzle(grid, row, col + 1);
 
    for (int num = 1; num <= N; num++)
    {

        /*Check to see if the place is sage to place 
        value (1-9) in the given row and column and then
        move to next column
        */
        if (isSafe(grid, row, col, num)==1)
        {
            
            /*Assign the number ot the current position of the grid 
            given the assigned num is correct for posiiton 
            */
            grid[row][col] = num;

            /*Checking possibility for next column
            */
            if (solvePuzzle(grid, row, col + 1)==1)
                return 1;
        }

        /* Remove assinged num if 
        assumption is wrong and attempt 
        again with a different num value
        */
        grid[row][col] = 0;
    }
    return 0;
}

/**
 * function to get output from the API call and
 * put it into a pointer. Also includes formatting 
 * and parsing of the string output to be printed
 * return nothing, void method
 */
void printOutput(char *stringOutput, size_t size, size_t nmemb, void *stream)
{

// API call follows: {"$id":"1"
// "currentDateTime":"2021-04-27T22:27-04:00"
// "utcOffset":"-04:00:00"
// "isDayLightSavingsTime":true
// "dayOfTheWeek":"Tuesday"
// "timeZoneName":"Eastern Standard Time"
// "currentFileTime":132640360474356102
// "ordinalDate":"2021-117"
// "serviceResponse":null}    

    char *delim = strtok(stringOutput, ",");

    //printing parts of the string, add delim to go to next line
        printf("------World Time API------\n\n");
        delim = strtok(NULL, ","); //first line junk (blank)
        printf("Date & time: ");
        printf("%s\n\n",delim + 18); //currentDateTime 
        delim = strtok(NULL, ","); //next line
        delim = strtok(NULL, ","); //utcOffset (blank)
        delim = strtok(NULL, ","); //isDayLightSavingsTime (blank)
        printf("Day of the week: ");
        printf("%s\n\n",delim + 15); //dayOfTheWeek
        delim = strtok(NULL, ","); //next line
        printf("Timezone: ");
        printf("%s\n\n",delim + 15); //timeZoneName
        delim = strtok(NULL, ","); //next line
        delim = strtok(NULL, ","); //currentFileTime (blank)
        delim = strtok(NULL, ","); //ordinalDate (blank)
        delim = strtok(NULL, ","); //serviceResponse (blank)
        printf("--------------------------\n\n");

}

/**
 * main function to call all other functions 
 * and execute the sudoku solver program. 
 */
int main()
{
    spaceFiller();

    int menuSelection = 0;

    CURL *curl;

    curl = curl_easy_init();
    if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "http://worldclockapi.com/api/json/est/now");
    /* example.com is redirected, so we tell libcurl to follow redirection */ 
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, printOutput);
 
    /* Perform the request, res will get the return code */ 
 
    curl_easy_perform(curl);
    
    /* always cleanup */ 
    curl_easy_cleanup(curl);

    printf("Welcome to the Sudoku Solver C Program!\n\n");

    /*Do while loop to execute the basic menu and functions 
    of the Sudoku Solver program 
    */
    do{
        spaceFiller();

        //Different user inputs 
        printf("Please select from the below menu what difficulty of puzzle you would like to solve: \n");
        printf("1. Puzzle Difficulty: Easy\n");
        printf("2. Puzzle Difficulty: Medium\n");
        printf("3. Puzzle Difficulty: Hard\n");
        printf("4. Exit program\n");
        spaceFiller();

        scanf("%d", &menuSelection);

        printf("You chose option number: %d\n\n", menuSelection);


        //If user selected Easy puzzle 
        if(menuSelection == 1){
             easyPuzzle.grid[N][N] =    
                       {{ 3, 0, 6, 5, 0, 8, 4, 0, 0 },
                       { 5, 2, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 8, 7, 0, 0, 0, 0, 3, 1 },
                       { 0, 0, 3, 0, 1, 0, 0, 8, 0 },
                       { 9, 0, 0, 8, 6, 3, 0, 0, 5 },
                       { 0, 5, 0, 0, 9, 0, 6, 0, 0 },
                       { 1, 3, 0, 0, 0, 0, 2, 5, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 7, 4 },
                       { 0, 0, 5, 2, 0, 6, 3, 0, 0 }} ;
            if (solvePuzzle(easyPuzzle.grid, 0, 0)==1)
                print(easyPuzzle.grid);
            else
                printf("No solution exists\n");
        }
        
        //If user selected Medium puzzle 
        else if(menuSelection == 2){
                        mediumPuzzle.grid[N][N] =    
                        { { 2, 0, 0, 0, 0, 0, 1, 0, 0 },
                        { 0, 8, 3, 0, 0, 0, 0, 0, 0 },
                        { 1, 0, 0, 6, 8, 0, 4, 0, 0 },
                        { 3, 0, 0, 0, 0, 6, 0, 0, 0 },
                        { 0, 9, 8, 0, 7, 0, 3, 1, 0 },
                        { 0, 0, 0, 9, 0, 0, 0, 0, 7 },
                        { 0, 0, 2, 0, 9, 4, 0, 0, 1 },
                        { 0, 0, 9, 0, 6, 0, 2, 5, 0 },
                        { 0, 0, 6, 1, 0, 0, 0, 0, 9 } };
            if (solvePuzzle(mediumPuzzle.grid, 0, 0)==1)
                print(mediumPuzzle.grid);
            else
                printf("No solution exists\n");
        }

        //If user selected Hard puzzle (unsolvable to show that functionality) 
        else if(menuSelection == 3){
                        hardPuzzle.grid[N][N] =     
                         { { 0, 0, 0, 0, 7, 0, 0, 0, 0 },
                         { 0, 4, 0, 0, 0, 9, 0, 5, 0 },
                         { 8, 0, 0, 6, 2, 0, 9, 0, 3 },
                         { 6, 0, 0, 0, 3, 0, 2, 0, 0 },
                         { 0, 0, 9, 0, 8, 0, 4, 0, 0 },
                         { 0, 0, 5, 0, 5, 0, 0, 0, 6 },
                         { 4, 0, 3, 0, 6, 7, 0, 0, 9 },
                         { 0, 5, 0, 8, 0, 0, 0, 1, 0 },
                         { 0, 0, 0, 0, 9, 0, 0, 0, 0 } };
            if (solvePuzzle(hardPuzzle.grid, 0, 0)==1)
                print(hardPuzzle.grid);
            else
                printf("No solution exists\n");
        }

        //User wants to stop program execution 
        else if(menuSelection == 4){
            break;
        }
        }
        while (0 == 0);

    }
    return 0;
}