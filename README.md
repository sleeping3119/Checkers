# Checkers Console Game

A simple console-based Checkers game implemented in C++. This project offers a classic two-player experience with turn-based gameplay, piece movement, capture mechanics, and win condition checking.

## Features

* **Interactive Console Interface**: Play directly in your terminal with character-based graphics for the board and pieces.
* **Two-Player Mode**: Enjoy head-to-head matches with a friend.
* **Dynamic Board Initialization**: The game board dimensions and initial piece layout are loaded from a configuration file (`load.txt`), allowing for easy customization.
* **Turn Management**: Clearly indicates whose turn it is (Player 1/Green or Player 2/Red).
* **Piece Movement and Capture**: Supports standard checkers movement and jumping over opponent's pieces.
* **Score Tracking**: Keeps track of captured pieces and displays the score for each player.
* **Win Conditions**: Automatically declares a winner when one player has no pieces left.
* **Error Handling**: Provides prompts for invalid moves or selections.

## How to Compile and Run

This game is designed for a Windows environment due to its use of `windows.h` and `conio.h` for console manipulation and graphics.

### Prerequisites

* A C++ compiler (e.g., MinGW, MSVC)

### Steps

1.  **Save the files**: Ensure `Checkers.cpp` and `load.txt` are in the same directory.
2.  **Compile**: Open your terminal or command prompt, navigate to the directory containing the files, and compile `Checkers.cpp` using your C++ compiler. For example, using g++:
    ```bash
    g++ Checkers.cpp -o checkers.exe
    ```
3.  **Run**: Execute the compiled program:
    ```bash
    .\checkers.exe
    ```

## How to Play

1.  **Start Game**: Upon running, the game will prompt you to enter names for Player 1 and Player 2.
2.  **Turns**: The game randomly determines who goes first.
3.  **Piece Selection**: When it's your turn, you will be prompted to enter the row and column (1-indexed) of the piece you wish to move.
    * Player 1 (Green) uses lowercase 'o' pieces.
    * Player 2 (Red) uses uppercase 'O' pieces.
4.  **Move Selection**: After selecting a piece, you will be prompted to enter the row and column (1-indexed) of your desired destination.
5.  **Valid Moves**:
    * Pieces can move diagonally forward one square to an empty space.
    * Pieces can jump over an opponent's piece diagonally forward to an empty square immediately beyond the captured piece. The captured piece is removed.
    * You cannot land on a square already occupied by another piece.
    * The game provides prompts for illegal moves.
6.  **Win**: The game ends when one player has captured all of the opponent's pieces.

## License

This project is open-sourced under the MIT License.