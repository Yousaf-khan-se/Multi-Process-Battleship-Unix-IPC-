#include <cstdlib>
#include <ctime>
#include <fcntl.h>
#include <iomanip>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <termios.h>
#include <unistd.h>
#include <sstream>

#include "Q1_GameBoard.h"
#include "Q1_GameMenu.h"
#include "Q1_Message.h"
#include "Q1_ProcessCommunication.h"

#define R 0
#define W 1

using namespace std;

void extractRC(string &input, int &r, int &c)
{
  r = input[0] - 'r';
  c = input[1] - 'c';
}

string makeRC(int r, int c)
{
  return to_string(r) + to_string(c);
}

void GameLogic()
{
  pid_t player1PID = -2, player2PID = -2;
  int pipe1[2], pipe2[2];
  if (pipe(pipe1) == -1 || pipe(pipe2) == -1)
  {
    cerr << "Pipe creation failed!" << endl;
    exit(1);
  }

  if ((player1PID = fork()) && (player2PID = fork()))
  {
    // Parent Process
    if (player1PID == -1)
    {
      cerr << "Failed to fork player 1" << endl;
      exit(1);
    }

    if (player2PID == -1)
    {
      cerr << "Failed to fork player 2" << endl;
      exit(1);
    }

    close(pipe1[R]);
    close(pipe1[W]);
    close(pipe2[R]);
    close(pipe2[W]);

    wait(NULL);
    wait(NULL);
  }
  else
  {
    ProcessCommunication pc1(pipe1);
    ProcessCommunication pc2(pipe2);
    string playerName;
    String str;
    Message msg;
    int r;
    int c;
    int score = 0;
    msg.clearConsole();
    // Two CHild Processes for player 1 and player 2
    if (player1PID == 0)
    {
      msg.printInCenter("To Player 1:- Enter Your Name: ");
      getline(cin, playerName);

      GameBoard p1Board(playerName);
      for (int i = 1; i <= 3; i++)
      {
        msg.clearConsole();
        msg.printInTopCenter("To Player " + p1Board.getPlayerName() +
                             ":- Place your Ships ");
        cout << endl;
        p1Board.printBoard();

        cout << "Enter the row Number for ship:no:" + i + " : ";
        cin >> r;
        cout << "Enter the column Number for ship:no:" + i + " : ";
        cin >> c;
        p1Board.placeShips(new BoardCoordinates(r, c));
      }
      pc1.Write("P2 Place Ships");

      if (pc2.Read() == "Start the Game")
      { // Do nothing
      }

      while (true)
      {
        msg.clearConsole();
        msg.printInTopCenter("To Player " + p1Board.getPlayerName() +
                             ":- Enter Coordinates to hit player 2 ships");
        cout<<"Enter x coordinate: ";
        cin>r;
        cout<<"Enter y coordinate: ";
        cin>>y;

        pc1.Write(makeRC(r,y));
        str = pc1.Read();
        if(str == "Hit")
        {
          msg.printInTopCenter("Congrats you Hit the Ship!");
          score++;
        }
        else if(str == "Mis")
        {
          msg.printInTopCenter("You Missed!")
        }

      }

      exit(0);
    }
    else if (player2PID == 0)
    {
      if (pc1.Read() == "P2 Place Ships")
      {
        GameBoard p2Board(playerName);
        for (int i = 1; i <= 3; i++)
        {
          msg.clearConsole();
          msg.printInTopCenter("To Player " + p2Board.getPlayerName() +
                               ":- Place your Ships ");
          cout << endl;
          p2Board.printBoard();

          cout << "Enter the row Number for ship:no:" + i + " : ";
          cin >> r;
          cout << "Enter the column Number for ship:no:" + i + " : ";
          cin >> c;
          p2Board.placeShips(new BoardCoordinates(r, c));
        }
        pc2.Write("Start the Game");
      }

      while (true)
      {
      }

      msg.printInCenter("To Player 2:- Enter Your Name: ");
      getline(cin, playerName);
      exit(0);
    }
  }
}

void MenuHandler()
{
  Message::clearConsole();

  Menu menu;

  menu.printMenu();

  switch (menu.getChoice())
  {
  case 1:
  {
    Message msg("Lets Start the Game!");
    msg.clearConsole();
    msg.printInCenter();
    GameLogic();
  }
  break;
  case 2:
    menu.PrintInstructions();
    break;
  case 3:
    exit(0);
    break;

  default:
    break;
  }
}

void GameLoop()
{
  while (1)
  {
    MenuHandler();
  }
}
int main()
{
  // GameLoop();
  GameLogic();

  Message msg;
  msg.printInCenter("Displaying the short Message...");

  //     class CustomException : public std::runtime_error {
  // public:
  //     CustomException(const std::string &message)
  //         : std::runtime_error(message) {}
  // };

  // void someFunction() {
  //     throw CustomException("CustomException from someFunction");
  // }

  // int main() {
  //     try {
  //         someFunction();
  //     } catch (const CustomException &e) {
  //         std::string errorMsg = e.what();
  //         if (errorMsg.find("someFunction") != std::string::npos) {
  //             std::cout << "Exception came from someFunction: " << errorMsg
  //             << std::endl;
  //         }
  //     }
  // }
  return 0;
}