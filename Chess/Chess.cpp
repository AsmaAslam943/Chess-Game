#include "Chess.h"
#include <iostream>

char Piece::getSymbol() const {
    char symbol = ' ';
    switch(type) {
        case PieceType::PAWN: symbol = 'P'; break;
        case PieceType::KNIGHT: symbol = 'N'; break;
        case PieceType::BISHOP: symbol = 'B'; break;
        case PieceType::ROOK: symbol = 'R'; break;
        case PieceType::QUEEN: symbol = 'Q'; break;
        case PieceType::KING: symbol = 'K'; break;
        default: return ' ';
    }
    
    return color == Color::WHITE ? symbol : tolower(symbol);
}

ChessBoard::ChessBoard() : 
    currentTurn(Color::WHITE),
    whiteKingInCheck(false),
    blackKingInCheck(false),
    gameOver(false) {
    resetBoard();
}

void ChessBoard::resetBoard() {
    // Initialize empty board
    board = std::vector<std::vector<Piece>>(8, std::vector<Piece>(8));
    
    // Set up pawns
    for (int i = 0; i < 8; ++i) {
        board[1][i] = Piece(PieceType::PAWN, Color::BLACK, Position(i, 1));
        board[6][i] = Piece(PieceType::PAWN, Color::WHITE, Position(i, 6));
    }
    
    // Set up other pieces
    // Black pieces (top of the board)
    board[0][0] = Piece(PieceType::ROOK, Color::BLACK, Position(0, 0));
    board[0][1] = Piece(PieceType::KNIGHT, Color::BLACK, Position(1, 0));
    board[0][2] = Piece(PieceType::BISHOP, Color::BLACK, Position(2, 0));
    board[0][3] = Piece(PieceType::QUEEN, Color::BLACK, Position(3, 0));
    board[0][4] = Piece(PieceType::KING, Color::BLACK, Position(4, 0));
    board[0][5] = Piece(PieceType::BISHOP, Color::BLACK, Position(5, 0));
    board[0][6] = Piece(PieceType::KNIGHT, Color::BLACK, Position(6, 0));
    board[0][7] = Piece(PieceType::ROOK, Color::BLACK, Position(7, 0));
    
    // White pieces (bottom of the board)
    board[7][0] = Piece(PieceType::ROOK, Color::WHITE, Position(0, 7));
    board[7][1] = Piece(PieceType::KNIGHT, Color::WHITE, Position(1, 7));
    board[7][2] = Piece(PieceType::BISHOP, Color::WHITE, Position(2, 7));
    board[7][3] = Piece(PieceType::QUEEN, Color::WHITE, Position(3, 7));
    board[7][4] = Piece(PieceType::KING, Color::WHITE, Position(4, 7));
    board[7][5] = Piece(PieceType::BISHOP, Color::WHITE, Position(5, 7));
    board[7][6] = Piece(PieceType::KNIGHT, Color::WHITE, Position(6, 7));
    board[7][7] = Piece(PieceType::ROOK, Color::WHITE, Position(7, 7));
    
    // Reset game state
    currentTurn = Color::WHITE;
    whiteKingInCheck = false;
    blackKingInCheck = false;
    gameOver = false;
    gameResult = "";
}

void ChessBoard::printBoard() const {
    std::cout << "  a b c d e f g h" << std::endl;
    std::cout << " +-+-+-+-+-+-+-+-+" << std::endl;
    for (int y = 0; y < 8; ++y) {
        std::cout << (8 - y) << "|";
        for (int x = 0; x < 8; ++x) {
            std::cout << board[y][x].getSymbol() << "|";
        }
        std::cout << (8 - y) << std::endl;
        std::cout << " +-+-+-+-+-+-+-+-+" << std::endl;
    }
    std::cout << "  a b c d e f g h" << std::endl;
    
    // Show current game state
    std::cout << (currentTurn == Color::WHITE ? "White" : "Black") << " to move" << std::endl;
}

bool ChessBoard::movePiece(const Position& from, const Position& to) {
    if (!from.isValid() || !to.isValid()) {
        std::cout << "Invalid position" << std::endl;
        return false;
    }
    
    Piece& piece = board[from.y][from.x];
    
    // Check if there is a piece at the starting position
    if (piece.getType() == PieceType::EMPTY) {
        std::cout << "No piece at starting position" << std::endl;
        return false;
    }
    
    // Check if it's the right player's turn
    if (piece.getColor() != currentTurn) {
        std::cout << "It's not your turn" << std::endl;
        return false;
    }
    
    // Check if the move is valid according to chess rules
    if (!piece.isValidMove(to, board)) {
        std::cout << "Invalid move for this piece" << std::endl;
        return false;
    }
    
    // Make the move
    Piece capturedPiece = board[to.y][to.x];
    board[to.y][to.x] = piece;
    board[to.y][to.x].setPosition(to);
    board[from.y][from.x] = Piece(); // Empty the starting position
    
    // Update game state
    currentTurn = (currentTurn == Color::WHITE) ? Color::BLACK : Color::WHITE;
    
    return true;
}

bool Piece::isValidMove(const Position& target, const std::vector<std::vector<Piece>>& board) const {
    // Placeholder implementation - basic validation
    if (!target.isValid() || target == position) return false;
    
    // Can't capture pieces of the same color
    if (board[target.y][target.x].getColor() == color) return false;
    
    // Specific movement rules for each piece type
    switch (type) {
        case PieceType::PAWN: {
            int direction = (color == Color::WHITE) ? -1 : 1;
            int startRow = (color == Color::WHITE) ? 6 : 1;
            
            // Forward move (1 square)
            if (target.x == position.x && target.y == position.y + direction) {
                return board[target.y][target.x].getType() == PieceType::EMPTY;
            }
            
            // Initial double move
            if (position.y == startRow && target.x == position.x && target.y == position.y + 2 * direction) {
                return board[position.y + direction][position.x].getType() == PieceType::EMPTY && 
                       board[target.y][target.x].getType() == PieceType::EMPTY;
            }
            
            // Capture diagonally
            if (std::abs(target.x - position.x) == 1 && target.y == position.y + direction) {
                return board[target.y][target.x].getType() != PieceType::EMPTY && 
                       board[target.y][target.x].getColor() != color;
            }
            
            return false;
        }
        
        // Other piece types (simplified rules)
        case PieceType::KNIGHT:
            return (std::abs(target.x - position.x) == 1 && std::abs(target.y - position.y) == 2) ||
                   (std::abs(target.x - position.x) == 2 && std::abs(target.y - position.y) == 1);
            
        case PieceType::BISHOP:
            return std::abs(target.x - position.x) == std::abs(target.y - position.y);
            
        case PieceType::ROOK:
            return target.x == position.x || target.y == position.y;
            
        case PieceType::QUEEN:
            return target.x == position.x || target.y == position.y || 
                   std::abs(target.x - position.x) == std::abs(target.y - position.y);
            
        case PieceType::KING:
            return std::abs(target.x - position.x) <= 1 && std::abs(target.y - position.y) <= 1;
            
        default:
            return false;
    }
}

std::vector<Position> ChessBoard::getValidMoves(const Position& pos) const {
    std::vector<Position> validMoves;
    if (!pos.isValid()) return validMoves;
    
    const Piece& piece = board[pos.y][pos.x];
    if (piece.getType() == PieceType::EMPTY || piece.getColor() != currentTurn) {
        return validMoves;
    }
    
    // Check all possible target positions
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            Position target(x, y);
            if (piece.isValidMove(target, board)) {
                validMoves.push_back(target);
            }
        }
    }
    
    return validMoves;
}

bool ChessBoard::isCheck(Color kingColor) const {
    // Simple stub to avoid segmentation faults
    return false;
}

bool ChessBoard::isCheckmate(Color kingColor) const {
    // Simple stub to avoid segmentation faults
    return false;
}

bool ChessBoard::isStalemate() const {
    // Simple stub to avoid segmentation faults
    return false;
}