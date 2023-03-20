/*  
     Description:      I made a turn based shooting game with the use of c language

     Programmed by:    Zhienj Bigalbal  S19A

     Last modified:    12/30/2022

     Version:          2.5.3
*/
#include <stdio.h>
#include <stdlib.h>

/* 
    This function displays the result of the game

    Precondition: mode must be a number

    @param mode is the basis for whether the player won or lost the game
*/

void 
showResults(int mode, int score) 
{
    char cTemp;
    printf("\n\nFinal Score: %d\n\n", score);
    // Displays a congratulatory message if the value of mode is 1 and displays a losing statement if the value of mode is not 1
    if(mode == 1) 
        printf("You won! Congratulations!\n\n");
    else 
        printf("You lose! Better luck next time!\n\n"); 
    printf("Press enter to continue..."); scanf("%c", &cTemp);
}

/* 
    This function is the one responsible for printing the whole board

    Precondition: x and y coordinates of the enemies must be within the range of the board and the x coordinate of the player must be within the range of the board's width

    @param x1 is the x coordinate of enemy 1

    @param y1 is the y coordinate of enemy 1

    @param x2 is the x coordinate of enemy 2

    @param y2 is the y coordinate of enemy 2

    @param x3 is the x coordinate of enemy 3

    @param y3 is the y coordinate of enemy 3

    @param x is the x coordinate of the player
*/
void 
showBoard(int x1, 
            int y1, 
            int x2, 
            int y2, 
            int x3, 
            int y3, 
            int x)
{
    system("cls");
    // Loop that iterates for an amount of time equal to the height of the board(including the horizontal borders)
    for (int i = 0; i < 9; i++) 
    {
        // Loop that iterates for an amount of time equal to the width of the board(including the vertical borders)
        for (int j = 0; j < 9; j++) 
        {
            printf("\033[0;32m");
            // Prints the horizontal borders when the loop is on the 1st, 7th, and last line
            if(i == 0 || i == 6 || i == 8) {
                if(j == 8) printf("-*");
                else printf("-");
            }
            // Prints the different characters present for each tile including the vertical borders
            else 
            {
                if (j == 0 || j == 2 || j == 4 || j == 6 || j == 8) {
                    if(j == 8 && i != 7) printf("|%d", i);
                    else if(j == 8 && i == 7) printf("|*");
                    else printf("|");
                }
                else 
                {
                    printf("\033[0;31m");
                    if(x == j && 7 == i) 
                        printf("P");
                    else if(x1 == j && y1 == i) 
                        printf("X");
                    else if(x2 == j && y2 == i) 
                        printf("X");
                    else if(x3 == j && y3 == i) 
                        printf("X");
                    else 
                        printf(" ");
                    printf("\033[0;33m");
                }
            }
            printf("\033[0;33m");
        } printf("\n");
    }
}

/* 
    This function is responsible for all of the player's action during the game

    Precondition: choice must be within 1-3, the x and y coordinates of the enemies must be within the range of the board, and the x coordinate of the player must be within the range of the board's width

    @param choice is player's choice of action
    
    @param x is the x coordinate of the player

    @param validMove determines whether the move is valid or not(if there is a space to move to)

    @param x1 is the x coordinate of enemy 1

    @param y1 is the y coordinate of enemy 1

    @param x2 is the x coordinate of enemy 2

    @param y2 is the y coordinate of enemy 2

    @param x3 is the x coordinate of enemy 3

    @param y3 is the y coordinate of enemy 3

    @param score is the current score of the player

    @param movement is the current movement cycle of the enemies
*/
void 
movePlayer(int choice, 
            int *x, 
            int *validMove, 
            int *x1, 
            int *y1, 
            int *x2, 
            int *y2, 
            int *x3, 
            int *y3, 
            int *score, 
            int *movement)
{
    // This conditional statement subtracts 2 from the player's x axis when the value of the choice variable is 1, meaning that the player chose to move left
    if(choice == 1)
    {
        // This conditional statement checks if the player is not at the left most side of the board, it then sets the validMove to 0 if there are no more spaces to move to
        if(*x != 1) 
            *x -= 2; 
        else 
            *validMove = 0;
    }
    // This conditional statement adds 2 from the player's x axis when the value of the choice variable is 2, meaning that the player chose to move right
    else if(choice == 2)
    {
        // This conditional statement checks if the player is not at the right most side of the board, it then sets the validMove to 0 if there are no more spaces to move to
        if(*x != 7) 
            *x += 2; 
        else 
            *validMove = 0;
    }
    // This conditional statement is the one responsible for shooting through enemies, killing enemies, and respawning enemies
    else if(choice == 3)
    {
        *validMove = 1;
        int enemyHit = 0;
        // This conditional statement checks if enemy 1 is in line with the player, it then kills the enemy and respawns it to its right spawn point if yes.
        if(*x1 == *x) 
        {
            enemyHit = 1;
            *y1 = 1;
            if(*movement == 0 || *movement == 1 || *movement == 3)
            {
                int xMove = 1;
                while((*y2 == 1 && *x2 == xMove) || (*y3 == 1 && *x3 == xMove))
                    xMove += 2;
                *x1 = xMove;
            }
            else if(*movement == 2)
            {
                int xMove = 3;
                while((*y2 == 1 && *x2 == xMove) || (*y3 == 1 && *x3 == xMove))
                    xMove += 2;
                *x1 = xMove;
            }
        }
        // This conditional statement checks if enemy 2 is in line with the player, it then kills the enemy and respawns it to its right spawn point if yes.
        if(*x2 == *x) 
        {
            enemyHit = 1;
            *y2 = 1;
            if(*movement == 0 || *movement == 1 || *movement == 3)
            {
                int xMove = 1;
                while((*y1 == 1 && *x1 == xMove) || (*y3 == 1 && *x3 == xMove))
                    xMove += 2;
                *x2 = xMove;
            }
            else if(*movement == 2)
            {
                int xMove = 3;
                while((*y1 == 1 && *x1 == xMove) || (*y3 == 1 && *x3 == xMove))
                    xMove += 2;
                *x2 = xMove;
            }
        }
        // This conditional statement checks if enemy 3 is in line with the player, it then kills the enemy and respawns it to its right spawn point if yes.
        if(*x3 == *x) 
        {
            enemyHit = 1;
            *y3 = 1;
            if(*movement == 0 || *movement == 1 || *movement == 3)
            {
                int xMove = 1;
                while((*y1 == 1 && *x1 == xMove) || (*y2 == 1 && *x2 == xMove))
                    xMove += 2;
                *x3 = xMove;
            }
            else if(*movement == 2)
            {
                int xMove = 3;
                while((*y1 == 1 && *x1 == xMove) || (*y2 == 1 && *x2 == xMove))
                    xMove += 2;
                *x3 = xMove;
            }
        }

        if(enemyHit == 1) *score += 10;
    }
    else
        *validMove = 0;
}

/* 
    This function is responsible for all of the enemies movement during the game

    Precondition: choice must be within 1-3, the x and y coordinates of the enemies must be within the range of the board, and the x coordinate of the player must be within the range of the board's width
    
    @param x is the x coordinate of the player

    @param x1 is the x coordinate of enemy 1

    @param y1 is the y coordinate of enemy 1

    @param x2 is the x coordinate of enemy 2

    @param y2 is the y coordinate of enemy 2

    @param x3 is the x coordinate of enemy 3

    @param y3 is the y coordinate of enemy 3

    @param movement is the current movement cycle of the enemies

    @param end determines if the game should end meaning that the enemies reached the bottom
*/
void 
moveEnemy(int *x, 
            int *x1, 
            int *y1, 
            int *x2,
            int *y2, 
            int *x3, 
            int *y3, 
            int *movement, 
            int *end)
{
    // moves all the enemies to the right if the current movement cycle value is at 0, it only moves the enemies that has spaces that can move to
    if(*movement == 0)
    {
        for (int i = 7; i > 0; i--)
        {
            if(*x1 == i && *x1 != 7)
            {
                if(*y1 == *y2 || *y1 == *y3)
                {
                    if(*y1 == *y2 && *y1 == *y3)
                    {
                        if(*x1 + 2 != *x2 && *x1 + 2 != *x3)
                            *x1 += 2;
                    }
                    else if(*y1 == *y2 && *x1 + 2 != *x2)
                        *x1 += 2;
                    else if(*y1 == *y3 && *x1 + 2 != *x3)
                        *x1 += 2;
                }
                else
                    *x1 += 2;
            }
            if(*x2 == i && *x2 != 7)
            {
                if(*y2 == *y1 || *y2 == *y3)
                {
                    if(*y2 == *y1 && *y2 == *y3)
                    {
                        if(*x2 + 2 != *x1 && *x2 + 2 != *x3)
                            *x2 += 2;
                    }
                    else if(*y2 == *y1 && *x2 + 2 != *x1)
                        *x2 += 2;
                    else if(*y2 == *y3 && *x2 + 2 != *x3)
                        *x2 += 2;
                }
                else
                    *x2 += 2;
            }
            if(*x3 == i && *x3 != 7)
            {
                    if(*y3 == *y1 || *y3 == *y2)
                    {
                        if(*y3 == *y1 && *y3 == *y2)
                        {
                            if(*x3 + 2 != *x1 && *x3 + 2 != *x2)
                                *x3 += 2;
                        }
                        else if(*y3 == *y1 && *x3 + 2 != *x1)
                            *x3 += 2;
                        else if(*y3 == *y2 && *x3 + 2 != *x2)
                            *x3 += 2;
                    }
                    else
                        *x3 += 2;
            }
        }     
        *movement += 1;
    }
    // moves all the enemies downwards if the current movement cycle value is at 1 or 3, it only moves the enemies that has spaces that can move to
    else if(*movement == 1 || *movement == 3)
    {
        for (int i = 5; i > 0; i--)
        {
            if(*y1 == i)
            {
                if(*y1 == 5) 
                {
                    *y1 += 2;
                    *end = 1;

                    showBoard(*x1, *y1, *x2, *y2, *x3, *y3, *x);
                }
                else
                    *y1 += 1;
            }
            if(*y2 == i)
            {
                if(*y2 == 5) 
                {
                    *y2 += 2;
                    *end = 1;

                    showBoard(*x1, *y1, *x2, *y2, *x3, *y3, *x);
                }
                else
                    *y2 += 1;
            }
            if(*y3 == i)
            {
                if(*y3 == 5) 
                {
                    *y3 += 2;
                    *end = 1;

                    showBoard(*x1, *y1, *x2, *y2, *x3, *y3, *x);
                }
                else
                    *y3 += 1;
            }
        }

        if(*movement == 3) 
            *movement = 0;
        else 
            *movement+=1;
    }
    // moves all the enemies to the left if the current movement cycle value is at 2, it only moves the enemies that has spaces that can move to
    else if(*movement == 2)
    {
        for (int i = 0; i < 8; i++)
        {
            if(*x1 == i && *x1 != 1)
            {
                if(*y1 == *y2 || *y1 == *y3)
                {
                    if(*y1 == *y2 && *y1 == *y3)
                    {
                        if(*x1 - 2 != *x2 && *x1 - 2 != *x3)
                            *x1 -= 2;
                    }
                    else if(*y1 == *y2 && *x1 - 2 != *x2)
                        *x1 -= 2;
                    else if(*y1 == *y3 && *x1 - 2 != *x3)
                        *x1 -= 2;
                }
                else
                    *x1 -= 2;
            }
            if(*x2 == i && *x2 != 1)
            {
                if(*y2 == *y1 || *y2 == *y3)
                {
                    if(*y2 == *y1 && *y2 == *y3)
                    {
                        if(*x2 - 2 != *x1 && *x2 - 2 != *x3)
                            *x2 -= 2;
                    }
                    else if(*y2 == *y1 && *x2 - 2 != *x1)
                        *x2 -= 2;
                    else if(*y2 == *y3 && *x2 - 2 != *x3)
                        *x2 -= 2;
                }
                else
                    *x2 -= 2;
            }
            if(*x3 == i && *x3 != 1)
            {
                if(*y3 == *y1 || *y3 == *y2)
                {
                    if(*y3 == *y1 && *y3 == *y2)
                    {
                        if(*x3 - 2 != *x1 && *x3 - 2 != *x2)
                            *x3 -= 2;
                    }
                    else if(*y3 == *y1 && *x3 - 2 != *x1)
                        *x3 -= 2;
                    else if(*y3 == *y2 && *x3 - 2 != *x2)
                        *x3 -= 2;
                }
                else
                    *x3 -= 2;
            }
        }   
        *movement+=1;
    }
}

/*  
    The main function is the one responsible 
    for the entire flow of the game
    Pre-condition: Not Applicable
*/
int 
main() 
{
    // variable declarations for some varaiables that is utilized inside the main function
    int movement = 0;
    char ch;

    int x = 1, score = 0, end = 0;
    int x1 = 1, x2 = 3, x3 = 5;
    int y1 = 1, y2 = 1, y3 = 1;

    // a do-while loop that keeps looping until the player looses or win the game
    do{
        system("cls");
        int choice, validMove = 1; 
        // calls the showBoard function that displays the board
        showBoard(x1, y1, x2, y2, x3, y3, x);

        // displays the current score as well as the actions the player can choose from
        printf("Score: %d\n", score);
        printf("Actions:\n");
        printf(" 1 - move left\n");
        printf(" 2 - move right\n");
        printf(" 3 - fire laser\n");

        // asks the player for their choice of action
        printf("Input action: "); 
        scanf("%d", &choice); 
        scanf("%c", &ch);

        // calls the movePlayer function that is in charge of the player's choice of action
        movePlayer(choice, &x, &validMove, &x1, &y1, &x2, &y2, &x3, &y3, &score, &movement);
        // calls the moveEnemy function that moves the enemies if the player's move is valid
        if(validMove == 1) 
            moveEnemy(&x, &x1, &y1, &x2, &y2, &x3, &y3, &movement, &end);
        
    }while(score != 100 && end == 0);
    // conditional statement that shows a winning screen if the value of score is greater than or equal to 100 and displays a losing screen if the enemies reach the end
    if(score >= 100) 
        showResults(1, score);
    else if(end == 1) 
        showResults(0, score);
 
    return 0;
}