//
// Created by Robert on 1/18/2022.
//

#ifndef MODERN_CHESS_PIECESTATS_H
#define MODERN_CHESS_PIECESTATS_H


#include <array>
#include <ostream>
#include "Piece.h"

enum class PieceScores {
    pawn = 1, knight = 3, bishop = 3, rook = 5, queen = 9, king = 200
};
enum class PieceVal {
    pawn = 4, knight = 8, bishop = 16, rook = 32, queen = 64, king = 128
};


template <Side side>
class PieceStats {

    std::array<int, 6> nrPieces;

public:
    PieceStats();

    void addPiece(unsigned pieceVal, bool subtract = false);
    int getSumPieces();

    int getScore();
    void resetPieces();
    void setStats(std::vector<std::shared_ptr<Piece>> &pieces);

    friend std::ostream &operator<<(std::ostream &os, PieceStats<side> &stats) {
        os << (side == Side::WHITE ? "Alb: " : "Negru: ") << stats.getScore() << '\n';
        os << "Pioni: " << stats.nrPieces[0] << " ";
        os << "Cai: " << stats.nrPieces[1] << "  ";
        os << "Nebuni: " << stats.nrPieces[2] << "  ";
        os << "Ture: " << stats.nrPieces[3] << "  ";
        os << "Regine: " << stats.nrPieces[4] << "  ";
        os << "Rege: " << stats.nrPieces[5] << "\n";

        return os;
    }

};


#endif //MODERN_CHESS_PIECESTATS_H
