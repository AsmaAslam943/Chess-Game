#include "Chess.h"
#include <iostream>
#include <string>

int main() {
    ChessBoard board;
    bool gameRunning = true;
    
    while (gameRunning) {
        // Clear screen (works on most terminals)
        std::cout << "\033[2J\033[1;1H";
        
        // Print the current board state
        board.printBoard();
        
        if (board.isGameOver()) {
            std::cout << "Game over: " << board.getGameResult() << std::endl;
            std::cout << "Play again? (y/n): ";
            char playAgain;
            std::cin >> playAgain;
            
            if (playAgain == 'y' || playAgain == 'Y') {
                board.resetBoard();
            } else {
                gameRunning = false;
            }
            
            continue;
        }
        
        // Get move from the player
        std::string from, to;
        std::cout << "Enter move (e.g., e2 e4): ";
        std::cin >> from >> to;
        
        if (from == "quit" || from == "exit") {
            gameRunning = false;
            continue;
        }
        
        // Convert algebraic notation to board position
        auto convertPos = [](const std::string& str) -> Position {
            if (str.length() != 2) return Position(-1, -1);
            int x = str[0] - 'a';
            int y = 8 - (str[1] - '0');
            return Position(x, y);
        };
        
        Position fromPos = convertPos(from);
        Position toPos = convertPos(to);
        
        if (!fromPos.isValid() || !toPos.isValid()) {
            std::cout << "Invalid position! Press Enter to continue...";
            std::cin.ignore(10000, '\n');
            std::cin.get();
            continue;
        }
        
        if (!board.movePiece(fromPos, toPos)) {
            std::cout << "Invalid move! Press Enter to continue...";
            std::cin.ignore(10000, '\n');
            std::cin.get();
        }
    }
    
    std::cout << "Thanks for playing!" << std::endl;
    return 0;
}