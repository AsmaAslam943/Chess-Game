// Chess.h - Main header file
#pragma once
#include <vector>
#include <string>
#include <iostream>

enum class PieceType { EMPTY, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING };
enum class Color { NONE, WHITE, BLACK };

struct Position {
    int x; // File (column): 0-7 representing a-h
    int y; // Rank (row): 0-7 representing 1-8
    
    Position(int x = 0, int y = 0) : x(x), y(y) {}
    
    bool isValid() const {
        return x >= 0 && x < 8 && y >= 0 && y < 8;
    }
    
    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }
    
    std::string toString() const {
        return std::string(1, 'a' + x) + std::to_string(8 - y);
    }
};

class Piece {
private:
    PieceType type;
    Color color;
    Position position;
    bool hasMoved;

public:
    Piece(PieceType type = PieceType::EMPTY, Color color = Color::NONE, Position pos = Position()) 
        : type(type), color(color), position(pos), hasMoved(false) {}

    PieceType getType() const { return type; }
    Color getColor() const { return color; }
    Position getPosition() const { return position; }
    bool getHasMoved() const { return hasMoved; }
    
    void setPosition(const Position& pos) { 
        position = pos; 
        hasMoved = true;
    }
    
    char getSymbol() const;
    bool isValidMove(const Position& target, const std::vector<std::vector<Piece>>& board) const;
};

class ChessBoard {
private:
    std::vector<std::vector<Piece>> board;
    Color currentTurn;
    bool whiteKingInCheck;
    bool blackKingInCheck;
    bool gameOver;
    std::string gameResult;
    
    // Private methods for game logic
    bool isCheck(Color kingColor) const;
    bool isCheckmate(Color kingColor) const;
    bool isStalemate() const;
    
public:
    ChessBoard();
    
    void resetBoard();
    void printBoard() const;
    bool movePiece(const Position& from, const Position& to);
    std::vector<Position> getValidMoves(const Position& pos) const;
    
    Color getCurrentTurn() const { return currentTurn; }
    bool isGameOver() const { return gameOver; }
    std::string getGameResult() const { return gameResult; }
    
    Piece getPieceAt(const Position& pos) const { 
        if (!pos.isValid()) return Piece();
        return board[pos.y][pos.x]; 
    }
};