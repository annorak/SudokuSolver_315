#include "sudoku.h"

int checkRows(Square *** sudoku, Box ** boxes)
{
    int i, j, k;

    // Holds the number of possibilities per value for the row
    int totalPossible[9];

    // Holds the position of a confirmed solution
    int position[9];

    // loops through all rows
    for (i = 0; i < 9; i++)
    {
        // initiliaze the two arrays
        for (j = 0; j < 9; j++)
        {
            totalPossible[j] = 0;
            position[j] = 0;
        }
        
        // loops through each position in the row
        for (j = 0; j < 9; j++)
        {
            // if square is already solved, go to next square
            if (sudoku[i][j]->number != 0)
                continue;
            
            // loops through all the possibles
            for (k = 0; k < 9; k++)
            {
                // check if value k is possible
                if (sudoku[i][j]->possible[k] == 0)
                {
                    // adds 1 to the possibilities for this value
                    totalPossible[k]++;

                    // reserves the position of the possibility
                    position[k] = j;
                }
            }

        }

        // loops through each value
        for (k = 0; k < 9; k++)
        {
            // if there is only one possibility for a value, execute if statement
            if(totalPossible[k] == 1)
            {
                // updates the sudoku struct to the solved value
                sudoku[i][position[k]]->number = k + 1;
                sudoku[i][position[k]]->solvable = 0;
                UNSOLVED--;

                updateSudoku(sudoku, i, position[k]);
                updateBoxes(sudoku, i, position[k]);

                return 1;
            }
        }
    }
}