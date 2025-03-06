# Chess Game -C++ Implementation 

This is a simple command-line Chess game built using C++. The game allows two players to play chess on a standard 8x8 chessboard. The game logic supports piece movement, valid moves, turn-taking, and check/checkmate detection.

# Features
Full support for all chess pieces: King, Queen, Rook, Bishop, Knight, Pawn.
Check and Checkmate detection.
Basic castling and en passant support.
Pawn promotion when reaching the 8th rank.
Input validation for moves.
Simple ASCII-based board display.
Requirements
To compile and run the chess game, you need:

A C++ compiler (e.g., GCC, Clang, MSVC).
C++17 or later (for modern language features).
Installation
1. Clone the repository:
bash
Copy
git clone https://github.com/yourusername/chess-game.git
cd chess-game
2. Compile the game:
For Linux/macOS (using g++):

bash
Copy
g++ -std=c++11 -o chess main.cpp
For Windows (using MinGW or MSVC):

bash
Copy
g++ -std=c++11 -o chess.exe main.cpp
3. Run the game:
bash
Copy
./chess
On Windows:

bash
Copy
chess.exe
Usage
Once the game is running, the board will be displayed in the terminal. Players will take turns entering their moves using algebraic notation (e.g., e2e4, g1f3). The game will validate each move and update the board accordingly.

Example Input:
To move a pawn from e2 to e4, type: e2e4
To move a knight from g1 to f3, type: g1f3
The game will continue until either a checkmate is achieved or a draw condition is met (stalemate, insufficient material, etc.).

# Game Rules
Players alternate turns, starting with white.
The board is displayed after every move.
The game ends if one player is checkmated or a draw condition occurs.
Pawns can move forward one square or two squares from their starting position.
Castling is possible when the king and rook have not moved.
En passant is supported if the move is valid.
Players can promote pawns upon reaching the 8th rank.
File Structure
bash
Copy
/chess-game
├── main.cpp            # Main game loop and logic
├── board.cpp           # Chess board representation and logic
├── board.h             # Header file for board.cpp
├── piece.cpp           # Chess pieces (King, Queen, etc.) logic
├── piece.h             # Header file for piece.cpp
└── README.md           # This file
# Contributing
If you would like to contribute to this project, feel free to fork the repository and submit a pull request with your proposed changes. All contributions are welcome!

# Issues and Bugs
Please report any issues or bugs by opening an issue on the repository page.

# License
This project is licensed under the MIT License - see the LICENSE file for details.

