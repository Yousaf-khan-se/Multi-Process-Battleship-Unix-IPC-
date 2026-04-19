#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "BoardCoordinates.h"
#include <iostream>
#include <string>

class GameBoard
{
private:
    char **board;
    int boardSize;
    int MaxNoOfShips;
    int noOfShipsPlaced;
    bool hideShips;
    int noOfHits;
    int MaxHitLimit;
    std::string boardPlayerName;

    struct Ship
    {
        int size;
    };

    Ship *ships; // Declared as class member

    void leftPadding(int value)
    {
        for (int i = 0; i < value; i++)
        {
            std::cout << " ";
        }
    }

public:
    GameBoard(std::string boardPlayerName, int boardSize = 5, int MaxNoOfShips = 3)
        : boardPlayerName(boardPlayerName), boardSize(boardSize + 1), MaxNoOfShips(MaxNoOfShips),
          noOfShipsPlaced(0), hideShips(false), noOfHits(0), MaxHitLimit(0)
    {
        ships = new Ship[MaxNoOfShips];
        for (int i = 0; i < MaxNoOfShips; i++)
        {
            ships[i].size = 2 + i;
            MaxHitLimit += ships[i].size;
        }

        board = new char *[boardSize];
        for (int i = 0; i < boardSize; i++)
        {
            board[i] = new char[boardSize];
        }

        char nums = 49;   // nums = 1 in character
        char alphas = 97; // alphas = a in character
        for (int i = 1; i < boardSize; i++)
        {
            board[0][i] = nums++;
            board[i][0] = alphas++;
        }
        board[0][0] = ' ';
        for (int i = 1; i < boardSize; i++)
        {
            for (int j = 1; j < boardSize; j++)
            {
                board[i][j] = '_';
            }
        }
    }

    void printBoard(int lPadding = 0)
    {
        for (int i = 0; i < boardSize; i++)
        {
            for (int j = 0; j < boardSize; j++)
            {
                leftPadding(lPadding);
                if (hideShips && this->board[i][j] == 'S')
                    std::cout << '_' << "| ";
                else
                    std::cout << this->board[i][j] << "| ";
            }
            std::cout << std::endl;
        }
    }

    bool placeShips(BoardCoordinates St_Coordinates, char direction, int shipLength)
    {
        if (this->noOfShipsPlaced == this->MaxNoOfShips)
        {
            throw std::runtime_error("No Ships are Available! (All the Ships Have been placed already)");
        }

        int r = St_Coordinates.getR();
        int c = St_Coordinates.getC();
        int b_size = this->boardSize;

        if (r < 1 || c < 1 || r >= b_size || c >= b_size)
        {
            throw std::runtime_error("Starting Coordinates of the ship are out of bounds!");
        }

        switch (direction)
        {
        case 'u':
            if (r - shipLength + 1 < 1)
            {
                throw std::runtime_error("Ending Coordinates of the ships are getting out of upper bounds!");
            }
            for (int i = 0; i < shipLength; i++)
            {
                if (this->board[r - i][c] == 'S')
                {
                    throw std::runtime_error("Coordinates of the ships are overlapping with other ships to the upper side of the ship!");
                }
                this->board[r - i][c] = 'S'; // Place ship upwards
            }
            break;
        case 'd':
            if (r + shipLength - 1 >= b_size)
            {
                throw std::runtime_error("Ending Coordinates of the ships are getting out of lower bounds!");
            }
            for (int i = 0; i < shipLength; i++)
            {
                if (this->board[r + i][c] == 'S')
                {
                    throw std::runtime_error("Coordinates of the ships are overlapping with other ships to the lower side of the ship!");
                }
                this->board[r + i][c] = 'S'; // Place ship downwards
            }
            break;
        case 'l':
            if (c - shipLength + 1 < 1)
            {
                throw std::runtime_error("Ending Coordinates of the ships are getting out of left bounds!");
            }
            for (int i = 0; i < shipLength; i++)
            {
                if (this->board[r][c - i] == 'S')
                {
                    throw std::runtime_error("Coordinates of the ships are overlapping with other ships to the left side of the ship!");
                }
                this->board[r][c - i] = 'S'; // Place ship left
            }
            break;
        case 'r':
            if (c + shipLength - 1 >= b_size)
            {
                throw std::runtime_error("Ending Coordinates of the ships are getting out of right bounds!");
            }
            for (int i = 0; i < shipLength; i++)
            {
                if (this->board[r][c + i] == 'S')
                {
                    throw std::runtime_error("Coordinates of the ships are overlapping with other ships to the right side of the ship!");
                }
                this->board[r][c + i] = 'S'; // Place ship right
            }
            break;
        default:
            return false;
        }
        this->noOfShipsPlaced++;
        return true;
    }

    bool placeShips(BoardCoordinates *St_Coordinates, char direction, int shipLength)
    {
        if (this->noOfShipsPlaced == this->MaxNoOfShips)
        {
            throw std::runtime_error("No Ships are Available! (All the Ships Have been placed already)");
        }

        int r = St_Coordinates->getR();
        int c = St_Coordinates->getC();
        int b_size = this->boardSize;

        if (r < 1 || c < 1 || r >= b_size || c >= b_size)
        {
            throw std::runtime_error("Starting Coordinates of the ship are out of bounds!");
        }

        switch (direction)
        {
        case 'u':
            if (r - shipLength + 1 < 1)
            {
                throw std::runtime_error("Ending Coordinates of the ships are getting out of upper bounds!");
            }
            for (int i = 0; i < shipLength; i++)
            {
                if (this->board[r - i][c] == 'S')
                {
                    throw std::runtime_error("Coordinates of the ships are overlapping with other ships to the upper side of the ship!");
                }
                this->board[r - i][c] = 'S'; // Place ship upwards
            }
            break;
        case 'd':
            if (r + shipLength - 1 >= b_size)
            {
                throw std::runtime_error("Ending Coordinates of the ships are getting out of lower bounds!");
            }
            for (int i = 0; i < shipLength; i++)
            {
                if (this->board[r + i][c] == 'S')
                {
                    throw std::runtime_error("Coordinates of the ships are overlapping with other ships to the lower side of the ship!");
                }
                this->board[r + i][c] = 'S'; // Place ship downwards
            }
            break;
        case 'l':
            if (c - shipLength + 1 < 1)
            {
                throw std::runtime_error("Ending Coordinates of the ships are getting out of left bounds!");
            }
            for (int i = 0; i < shipLength; i++)
            {
                if (this->board[r][c - i] == 'S')
                {
                    throw std::runtime_error("Coordinates of the ships are overlapping with other ships to the left side of the ship!");
                }
                this->board[r][c - i] = 'S'; // Place ship left
            }
            break;
        case 'r':
            if (c + shipLength - 1 >= b_size)
            {
                throw std::runtime_error("Ending Coordinates of the ships are getting out of right bounds!");
            }
            for (int i = 0; i < shipLength; i++)
            {
                if (this->board[r][c + i] == 'S')
                {
                    throw std::runtime_error("Coordinates of the ships are overlapping with other ships to the right side of the ship!");
                }
                this->board[r][c + i] = 'S'; // Place ship right
            }
            break;
        default:
            return false;
        }
        this->noOfShipsPlaced++;
        return true;
    }

    bool isHit(BoardCoordinates hitCords)
    {
        if (board[hitCords.getR()][hitCords.getC()] == 'S')
        {
            board[hitCords.getR()][hitCords.getC()] = 'H';
            this->noOfHits++;
            return true;
        }
        return false;
    }

    bool getShipsHiddenStatus() const
    {
        return hideShips;
    }

    void setShipsHiddenStatus(bool hideShips)
    {
        this->hideShips = hideShips;
    }

    bool isGameOver() const
    {
        return noOfHits >= MaxHitLimit;
    }

    string getPlayerName() const
    {
        return this->boardPlayerName;
    }

    ~GameBoard()
    {
        for (int i = 0; i < this->boardSize; i++)
        {
            delete[] this->board[i]; // Delete each row
        }
        delete[] this->board;
        delete[] ships; // Correctly delete the dynamically allocated ships array
    }
};

#endif // Q1_GAMEBOARD_H
