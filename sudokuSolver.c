#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

// N is the size of the 2D matrix   N*N
#define N 9

int *puzzle;
int solved = 0;

// Contents from puzzle.c:
// v
// v
// v
// v

int *createPuzzle(int difficulty){

    // 0 means unassigned cells
     int easyGrid[N][N] = { { 3, 0, 6, 5, 0, 8, 4, 0, 0 },
                         { 5, 2, 0, 0, 0, 0, 0, 0, 0 },
                         { 0, 8, 7, 0, 0, 0, 0, 3, 1 },
                         { 0, 0, 3, 0, 1, 0, 0, 8, 0 },
                         { 9, 0, 0, 8, 6, 3, 0, 0, 5 },
                         { 0, 5, 0, 0, 9, 0, 6, 0, 0 },
                         { 1, 3, 0, 0, 0, 0, 2, 5, 0 },
                         { 0, 0, 0, 0, 0, 0, 0, 7, 4 },
                         { 0, 0, 5, 2, 0, 6, 3, 0, 0 } };

    
	int medGrid[N][N] = { { 2, 0, 0, 0, 0, 0, 1, 0, 0 },
                        { 0, 8, 3, 0, 0, 0, 0, 0, 0 },
                        { 1, 0, 0, 6, 8, 0, 4, 0, 0 },
                        { 3, 0, 0, 0, 0, 6, 0, 0, 0 },
                        { 0, 9, 8, 0, 7, 0, 3, 1, 0 },
                        { 0, 0, 0, 9, 0, 0, 0, 0, 7 },
                        { 0, 0, 2, 0, 9, 4, 0, 0, 1 },
                        { 0, 0, 9, 0, 6, 0, 2, 5, 0 },
                        { 0, 0, 6, 1, 0, 0, 0, 0, 9 } };
	
	
	int hardGrid[N][N] = { { 0, 0, 0, 0, 7, 0, 0, 0, 0 },
                         { 0, 4, 0, 0, 0, 9, 0, 5, 0 },
                         { 8, 0, 0, 6, 2, 0, 9, 0, 3 },
                         { 6, 0, 0, 0, 3, 0, 2, 0, 0 },
                         { 0, 0, 9, 0, 8, 0, 4, 0, 0 },
                         { 0, 0, 5, 0, 5, 0, 0, 0, 6 },
                         { 4, 0, 3, 0, 6, 7, 0, 0, 9 },
                         { 0, 5, 0, 8, 0, 0, 0, 1, 0 },
                         { 0, 0, 0, 0, 9, 0, 0, 0, 0 } };

    if (difficulty = 1){
        *puzzle = malloc(easyGrid);
        
    }
    else if (difficulty = 2){
        *puzzle = malloc(medGrid);
        
    }
    else if (difficulty = 3){
        *puzzle = malloc(hardGrid);
        
    }

    return *puzzle;
}

// Checks whether it will be legal 
// to assign num to the
// given row, col
int checkPuzzle(int grid[N][N], int row,
                       int col, int num)
{
     
    // Check if we find the same num
    // in the similar row , we return 0
    for (int x = 0; x <= 8; x++)
        if (grid[row][x] == num)
            return 0;
 
    // Check if we find the same num in the
    // similar column , we return 0
    for (int x = 0; x <= 8; x++)
        if (grid[x][col] == num)
            return 0;
 
    // Check if we find the same num in the
    // particular 3*3 matrix, we return 0
    int startRow = row - row % 3,
                 startCol = col - col % 3;
   
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j +
                          startCol] == num)
                return 0;
 
    return 1;
}

/* Takes a partially filled-in grid and attempts
to assign values to all unassigned locations in
such a way to meet the requirements for
Sudoku solution (non-duplication across rows,
columns, and boxes) */
int solveSudoku(int grid[N][N], int row, int col){
     
    // Check if we have reached the 8th row
    // and 9th column (0
    // indexed matrix) 
    if (row == N - 1 && col == N)
        return 1;
 
    //  Check if column value  becomes 9 ,
    //  we move to next row and
    //  column start from 0
    if (col == N)
    {
        row++;
        col = 0;
    }
   
    // Check if the current position
    // of the grid already contains
    // value >0, we iterate for next column
    if (grid[row][col] > 0)
        return solveSudoku(grid, row, col + 1);
 
    for (int num = 1; num <= N; num++)
    {
         
        // Check if it is safe to place
        // the num (1-9)  in the
        // given row ,col  ->we move to next column
        if (checkPuzzle(grid, row, col, num)==1)
        {
            /* assigning the num in the
               current (row,col)
               position of the grid
               and assuming our assined num
               in the position
               is correct     */
            grid[row][col] = num;
           
            //  Checking for next possibility with next
            //  column
            if (solveSudoku(grid, row, col + 1)==1)
                return 1;
        }
       
        // Removing the assigned num ,
        // since our assumption
        // was wrong , and we go for next
        // assumption with
        // diff num value
        grid[row][col] = 0;
    }
    return 0;
}
 

void main(){

    int *foo = createPuzzle(1);

    print(*foo);

    // if (solveSuduku(grid, 0, 0)==1)
    //     print(grid);
    // else
    //     printf("No solution exists");
 

}

int *createSudoku(){
    createPuzzle();
}

// code from curltest.c
// v
// v
// v
// v
// v

void printOutput(char *stringOutput, size_t size, size_t nmemb, void *stream)
{    
  printf("\n%s\n", stringOutput);
}

// int main(void)
// {
//				CURL CODE MOVED INTO BOTTOM MAIN() FUNCTION
//   return 0;
// }

// code from sudoku.c
// v
// v
// v
// v


/* A utility function to print grid */
void print(int arr[N][N])
{
     for (int i = 0; i < N; i++)
      {
         for (int j = 0; j < N; j++)
            printf("%d ",arr[i][j]);
         printf("\n");
       }
}

// // Main function that will be giving
// // the user a menu choice for puzzle
// // difficulty along with printing the 
// // solved sudoku puzzle. 
// int main()
// {
	
//	 printf("Welcome to the Sudoku Solver C Program!\n\n");

//	 printf("Please select from the below menu what difficulty of puzzle you would like to solve:"\n");
//	 printf("Puzzle Difficulty: Easy\n");
//	 printf("Puzzle Difficulty: Medium\n");
//	 printf("Puzzle Difficulty: Hard\n");

// 	int ** puzzle;
// 	int status; 
	
// 	Sudoku * sudoku;
	
// 	puzzle = createPuzzle();
	
// 	sudoku ( setUpPuzzle(puzzle);
	
// 	printPuzzle(sudoku->squares);
	
// 	while (solved < 81)
// 	{
// 		status = checkPuzzle(sudoku->squares, sudoku->boxes);
		
// 		if (status == 0)
// 		{
// 			printf("The program failed to solve the Sudoku puzzle.\n");
// 			break;
// 		}
// 	}
		
// 	printPuzzle(sudoku->squares);
		
//   CURL *curl;

//   curl = curl_easy_init();
//   if(curl) {
//     curl_easy_setopt(curl, CURLOPT_URL, "http://worldtimeapi.org/api/ip.txt");
//     /* example.com is redirected, so we tell libcurl to follow redirection */ 
//     curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
//     curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, printOutput);
 
//     /* Perform the request, res will get the return code */ 
 
//     curl_easy_perform(curl);
    
//     /* always cleanup */ 
//     curl_easy_cleanup(curl);
//   }

// 	return 0;
// }


