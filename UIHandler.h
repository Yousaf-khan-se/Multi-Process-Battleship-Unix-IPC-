#ifndef UIHANDLER_H
#define UIHANDLER_H

#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/ioctl.h>
#include <limits>

using namespace std;

class Message
{
private:
    string text;
    int duration;
    static struct winsize w;

    static void updateConsoleDimensions()
    {
        // Get the terminal size
        if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) != 0)
        {
            std::cerr << "Error getting terminal size." << std::endl;
        }
        // std::cout << "Height: " << w.ws_row << ", Width: " << w.ws_col << std::endl;
    }

public:
    Message(string text = "", float duration = 0.05)
    {
        this->duration = (int)(duration * 1000000);
        this->text = text;
    }

    static int getConsoleRows()
    {
        if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) != 0)
        {
            std::cerr << "Error getting terminal size." << std::endl;
        }

        return w.ws_row;
    }

    static int getConsoleCols()
    {
        if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) != 0)
        {
            std::cerr << "Error getting terminal size." << std::endl;
        }

        return w.ws_col;
    }

    static void leftPadding(int value)
    {
        for (int i = 0; i < value; i++)
        {
            cout << " ";
        }
    }
    static void topPadding(int value)
    {
        for (int i = 0; i < value; i++)
        {
            cout << "\n";
        }
    }

    static void topPaddingTillCenter()
    {
        updateConsoleDimensions();
        topPadding(w.ws_row / 2);
    }
    static void leftPaddingTillCenter(int msgSize = 0)
    {
        updateConsoleDimensions();
        leftPadding(w.ws_col / 2 - msgSize);
    }

    static void paddingTillCenter(int msgSize = 0)
    {
        topPaddingTillCenter();
        leftPaddingTillCenter(msgSize);
    }

    void print(string msg = "")
    {
        if (msg != "")
            this->text = msg;

        for (int i = 0; i < this->text.length(); i++)
        {
            cout << text[i];
            cout.flush();
            usleep(this->duration);
        }
        cout << "\n";
    }

    void printInCenter(string msg = "")
    {
        if (msg != "")
            this->text = msg;

        Message::paddingTillCenter(this->text.length());
        print();
    }

    void printInTopCenter(string msg = "")
    {
        if (msg != "")
            this->text = msg;

        cout << endl;
        Message::leftPaddingTillCenter(this->text.length());
        print();
    }

    static void clearConsole()
    {
        std::cout << "\033[2J\033[1;1H";
    }
    static void pause()
    {
        std::cout << "Press Enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    void setText(string text)
    {
        this->text = text;
    }
    void setDuration(float duration)
    {
        this->duration = (int)(duration * 1000000);
    }

    string getText()
    {
        return this->text;
    }
    float getDuration() const
    {
        return static_cast<float>(duration) / 1000000; // Return in seconds
    }
};

winsize Message::w = {0};

#endif // Q1_MESSAGE_H