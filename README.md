### 📝 Project README: Multi-Process Battleship (Unix IPC)

Copy and paste the content below into a `README.md` file in your repository.

# Multi-Process Battleship (Unix IPC)

A classic Battleship strategy game implemented in C++ that leverages **Linux System Programming** concepts. Unlike a standard terminal game, this project runs Player 1 and Player 2 as separate system processes that communicate in real-time using **Unix Pipes**.


## 🚀 Core Concepts Demonstrated
This project serves as a practical implementation of several computer science and systems programming concepts:
* **Inter-Process Communication (IPC):** Uses unidirectional pipes to pass game coordinates and hit/miss statuses between two concurrent processes.
* **Process Management:** Utilizes `fork()` to create child processes and `wait()` for process synchronization.
* **Object-Oriented Programming (OOP):** Encapsulates game logic, UI rendering, and communication protocols into modular classes.
* **Low-Level System Calls:** Interfaces with the terminal via `ioctl` and `termios` to handle dynamic console resizing and stylized text output.

## ✨ Features
* **Two-Player Local Gameplay:** Each player manages their own private grid and fleet.
* **Dynamic UI:** Includes a typewriter-style text animation and automatic center-alignment based on your terminal window size.
* **Validation Logic:** Prevents overlapping ships and ensures all moves stay within the 5x5 grid boundaries.
* **Customizable Fleet:** Players can place ships of different sizes (2, 3, and 4 units) horizontally or vertically.

## 🛠️ Configuration & Installation

### Prerequisites
* A **Unix-based environment** (Linux, macOS, or WSL on Windows) is required because the project relies on `<unistd.h>` and Unix Pipes.
* `g++` compiler.

### Compilation
Open your terminal in the project directory and run:
```bash
g++ main.cpp -o battleship
```

### Running the Game
To start the game:
```bash
./battleship
```

## 🎮 How to Play
1.  **Main Menu:** Choose "Start Game" to begin or "Instructions" to view the rules.
2.  **Ship Placement:** * Enter the starting coordinates (row and column).
    * Choose a direction (Up, Down, Left, Right).
    * The game will validate if the ship fits and isn't overlapping.
3.  **The Battle:** * Players take turns entering coordinates to fire upon the opponent's grid.
    * The system communicates the result (Hit/Miss) through pipes and updates the game state.
4.  **Victory:** The first player to sink all of the opponent's ships wins!

## 📁 Project Structure
* `main.cpp`: The engine that handles process forking and the primary game loop.
* `GameBoard.h`: Manages the 5x5 grid, ship placement logic, and hit detection.
* `PipeManager.h`: A wrapper for pipe read/write operations to simplify IPC.
* `UIHandler.h`: Utilities for console manipulation, padding, and "typewriter" text effects.
* `GameMenu.h`: Logic for the interactive start menu.

---
