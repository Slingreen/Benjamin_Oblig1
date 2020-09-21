/**********************************************************************************************************
 *      1st obligatory assignment, tic tac toe
 *
 *      A program that allows you to play tic tac toe
 *          Either against an AI or other player
 *
 *  @file    Benjamin_Oblig1.CPP
 *  @author  Benjamin A.E. Darici
 */

#include <iostream>
#include <cstdlib>
#include <ctime>

void game();
void printBoard();
void choice();
bool checkWin();
char Read_Command(const char* c);

char valg[9];   //  Array that gets filled with X-es and O-es depending on players
int t = 0;      //  Turn counter, if it reaches 9, the board is filled and it is a tie!
bool ai = false;//  AI bool

enum gameState { gameOver, Player1, Player2};
gameState turn = Player1;


//  Main function with menu
int main()
{
    char command;
    command = Read_Command("(1) or (2) players?\nQ to quit");

    while (command != 'Q')
    {
        std::cin.ignore(32767, '\n');
        switch (command)
        {
        case '1': ai = true; game(); break;     //  Enables AI
        case '2': ai = false; game(); break;    //  Disables AI
        default:  break;
        }
        command = Read_Command("(1) or (2) players?\nQ to quit");
    }
}


//  The game loop
void game()
{   
    printBoard();
    while (turn)
    {    
        std::cout << "\n It is turn:" << t << '\n';
        choice();
        printBoard();

        if (t > 4)  //  If there has been more than 4 turns, checks if anyone has won yet
        {
            if (true == checkWin()) 
            {
                std::cout 
                    << "Game over! " 
                    << (ai ? ((turn % 2) ? "AI" : "You") :((turn % 2) ? "Player 2" : "Player 1"))
                    << " won!\n\n";
                turn = gameOver;
                break;
            }
        }
        if (t == 9) //  Checks if the entire board is filled
        {
            turn = gameOver;
            std::cout << "Game over, it's a tie!\n\n";
        }
    }
    //  Resets all variables before the next game
    turn = Player1;
    t = 0;
    std::fill_n(valg, 9, 0);
}


//  Prints the current board of tic tac toe
void printBoard()
{
    std::cout << "---------------\n";
    for (int i = 0; i < 9; i++) 
    {
        std::cout << " | ";
        if (valg[i])
        {
            std::cout << valg[i];
        }
        else 
        {
            std::cout << i + 1;
        }
            
        
        if ((i + 1) % 3 == 0)
        {
            std::cout << " |\n";
        }

    }
    std::cout << "---------------\n";
}


//  Checks the player or ai choice and adds it to the board
void choice()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // set initial seed value to system clock

    char input[200] = "";   //  Array to read player input
    int  number = 0;        //  The chosen number
    bool wrong = false;     //  Bool to check if it is a valid number
    
    

    if(ai && turn % 2 == 0) //  Checks if the AI is enabled and if it is its turn
    { 
        do  //  Loop that chooses AI's number
        {
            wrong = false;
            number = std::rand() % 9 + 1;
            if (valg[number - 1])
            {
                wrong = true;
            }
        } while (wrong);
    }
    else    //  If AI is not enabled
    {
        std::cout   //  Writes out player turn
            << ((turn % 2) ? "Player 1" : "Player 2")
            << " - Write a number from 1-9:  ";

        do {    //  Loop to determine if player input is valid...
            wrong = false;
            std::cin.getline(input, 200);   //  Gets input
            number = atoi(input);           //  Tries to turn input to int
            if (number == 0 && input[0] != '0') //  Checks if input is a valid int
            {
                wrong = true;   std::cout << "\nERROR: Not an integer\n\n";
            }

            if (number >= 1 && number <= 9) //  Checks if input is within bounds...
            {
                if (valg[number - 1])       //  ...And in that case checks if the choice is free
                {
                    wrong = true;   std::cout << "\nERROR: Already taken\n\n";
                }
            }

        } while (wrong || number < 1 || number > 9);    //  ... while choice is not valid or within bounds
    }

    if (turn - 1)   //  Checks if it was player 2's turn...
    {
        valg[number -1] = 'O';  //  Places player's choice
        turn = Player1;         //  Now it is player 1's turn
    }  
    else    //  ...else it is player 1's turn
    {
        valg[number -1] = 'X';  //  Places player's choice
        turn = Player2;         //  Now it is player 2's turn
    }
    t++;    //  Turn count goes up
}


//  Checks if anyone has won yet
bool checkWin()
{
    //  Checks diagonal 1-5-9
    if (valg[0] == valg[4] && valg[0] == valg[8] && valg [0]) 
    {
        return true;
    }
        
    //  Checks diagonal 3-5-7
    if (valg[2] == valg[4] && valg[2] == valg[6] && valg[2])
    {
        return true;
    }
     
    //  Checks vertical, e.g. 1-4-7
    for (int i = 0; i < 3; i++) 
    {
        if (valg[i] == valg[i + 3] && valg[i] == valg[i + 6] && valg[i])
        {
            return true;
        }
    }

    //  Checks horizontal, e.g. 1-2-3
    for (int i = 0; i < 7; i+=3)
    {
        if (valg[i] == valg[i + 1] && valg[i] == valg[i + 2] && valg[i])
        {
            return true;
        }
    }

    return false;
}


// A tiny function just to read input commands
char Read_Command(const char* c)
{
    char command;
    std::cout << c << ":  ";
    std::cin >> command;
    return(toupper(command));
}