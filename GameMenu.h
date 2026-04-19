#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <iostream>
#include "UIHandler.h"

using namespace std;

class Menu
{
private:
    int choice;
public:

    void printMenu()
    {
        Message::leftPaddingTillCenter(9);
        std::cout << "   1. Start Game" << endl;
        Message::leftPaddingTillCenter(10);
        std::cout << "    2. Instruction  " << endl;
        Message::leftPaddingTillCenter(17);
        std::cout << "           3. Quit  " << endl;
        
    tryAgain:
        cout << "Enter your choice..." << endl;
        cin >> choice;

        if (choice > 3 || choice < 1)
        {
            cout << "Invalid Input" << endl;
            goto tryAgain;
        }
    }

    void PrintInstructions()
    {
        string instructions = R"(
                                ### Battleship Game Instructions ###

                                Welcome to the Battleship Game! This is a two-player game played on a 5x5 grid, where each player tries to sink the opponent's fleet of ships by guessing their positions. Follow the instructions below to set up and play the game.

                                --- Game Setup ---
                                1. Players: The game is played between Player 1 and Player 2. Each player runs a separate process.
                                2. Game Board:
                                - Each player has a private 5x5 grid.
                                - Each grid can hold:
                                    - Empty spaces.
                                    - Ships of fixed sizes (2, 3, and 4 spaces long).
                                - Players must place their ships on the grid before the game starts, ensuring that no ships overlap.
                                3. Ship Placement:
                                - Ships can be placed either horizontally or vertically.
                                - Validate ship placement to avoid overlapping and ensure they fit within the grid.

                                --- Game Flow ---
                                #### Player 1 Process ####
                                1. Place Ships:
                                - Player 1 places their ships on their grid.
                                2. Send Guess:
                                - Player 1 sends a guess (row, column) to Player 2 through Pipe 1.
                                3. Receive Response:
                                - Player 1 waits for Player 2’s response (Hit or Miss) through Pipe 1.
                                4. Check for Win:
                                - If all of Player 2’s ships are hit, Player 1 wins, and the game ends.
                                - If not, control is passed to Player 2.

                                #### Player 2 Process ####
                                1. Place Ships:
                                - Player 2 places their ships on their grid.
                                2. Receive Guess:
                                - Player 2 receives Player 1’s guess (row, column) through Pipe 1.
                                3. Check Hit or Miss:
                                - Player 2 checks if the guess hits or misses a ship on their grid.
                                - Player 2 sends the response (Hit or Miss) back to Player 1 through Pipe 1.
                                4. Send Guess:
                                - Player 2 sends a guess (row, column) to Player 1 through Pipe 2.
                                5. Receive Response:
                                - Player 2 waits for Player 1’s response (Hit or Miss) through Pipe 2.
                                6. Check for Win:
                                - If all of Player 1’s ships are hit, Player 2 wins, and the game ends.
                                - If not, control is passed back to Player 1.

                                --- Turn-Based Gameplay ---
                                - Players alternate turns guessing the opponent's ship positions.
                                - After each guess, the opponent responds with:
                                - H for a hit.
                                - M for a miss.
                                - Players must wait for the opponent's response before making their next guess.

                                --- Game Termination ---
                                - The game ends when one player successfully sinks all three of the opponent's ships.
                                - Each ship requires multiple hits based on its size (e.g., a ship of size 3 requires 3 hits to sink).
                                - Once a player sinks all the opponent's ships, the game declares the winner and both processes terminate gracefully.

                                --- Synchronization ---
                                - The pipes facilitate communication and ensure that only one player can make a move at a time.
                                - The game ensures proper synchronization so that one player cannot make multiple guesses in a row without waiting for the other player's move.

                                --- Pipes Error Handling ---
                                - Implement error handling for the pipes to ensure reliable communication.
                                - If there is a failure to send or receive data through the pipes, the game should handle this gracefully.

                                --- Tips for Players ---
                                - Pay attention to your opponent's guesses and responses to strategize your own moves.
                                - Make sure to validate ship placements before the game starts.
                                - Keep track of hits and misses to identify patterns in your opponent's ship placement.

                                Good luck, and may the best strategist win!
                                )";
        Message msg(instructions, 0.0008);
        msg.print();
        Message::pause();
    }

    int getChoice()
    {
        return choice;
    }
};

#endif // Q1_GAMEMENU_H