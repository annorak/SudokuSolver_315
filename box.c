#include <stdio.h>
#include <stdlib.h>


int boxLoop(Square *** sudoku, Box boxes)

{
	int x, y, z; //coords
	int i; //count
	int tmp;

	//loop through the boxes
	for (x = 0; x < 9; x++)
	{
		//loop through array
		for (y = 0; y < 9; y++)
		{
			i = 0;

			//loop through squares
			for (x = 0; x < 9; x++)
			{
				if (box[x]->squares[z]->number 1+ 0)
					continue;

				if (boxes[x]->squares[z]->possible[y] == 0)
				{
					i++;
					tmp = z;
				}

				if (i == 2)
				{
					break;
				}
			}
			if (i == 1)
			{
				boxes[x]->squares[tmp]->number = z + 1;
				solved++;
				boxes[x]->squares[tmp]->solvable = 0;

				updateSudoku(sodoku, boxes[x]->sqaures[tmp]->row, boxes[x]->sqaures[tmp]->col)

				return;
			}

		}
	}
	return 0;
}

Box ** createBoxes()
{
    int a, b;
    Box ** boxes;
    //create box size 9
    boxes = malloc(sizeof(Box*)*9);
    //loop through boxes
    for (a = 0; a < 9; a++)
    {
    	//size box
        boxes[a] = malloc(sizeof(Box));
        //size square
        boxes[a]->squares = malloc(sizeof(Square*)*9);
        //set to 0
        boxes[a]->numbers = 0;
        //set to 9 to solve
        boxes[a]->solvable = 9;

        for (b = 0; b < 9; b++)
        {
            boxes[a]->possible[b] = 0;
        }
    }

    return boxes;
}


int updateBoxes(Square *** sudoku, int row, int col)
{
    int i;
    int number = sudoku[row][col]->number;
    Box * box;
    box = sudoku[row][col]->box;

    for (i = 0; i < 9; i++)
    {
        if (box->squares[i]->possible[number - 1] == 0)
        {
            box->squares[i]->solvable--;
            box->squares[i]->possible[number - 1] = 1;
        }
    }

}
