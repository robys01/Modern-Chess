//
// Created by Robert on 1/18/2022.
//

#include <iostream>
#include "../headers/PieceStats.h"
#include "../headers/ChessExceptions.h"

template<Side side>
PieceStats<side>::PieceStats() {

}

template<Side side>
void PieceStats<side>::addPiece(unsigned pieceVal, bool subtract) {

    int x = subtract ? -1 : 1;
    pieceVal -= (int) side;

    switch (pieceVal) {
        case (int) PieceVal::pawn:
            nrPieces[0] += x;
            break;
        case (int) PieceVal::knight:
            nrPieces[1] += x;
            break;
        case (int) PieceVal::bishop:
            nrPieces[2] += x;
            break;
        case (int) PieceVal::rook:
            nrPieces[3] += x;
            break;
        case (int) PieceVal::queen:
            nrPieces[4] += x;
            break;
        case (int) PieceVal::king:
            nrPieces[5] += x;
            break;
        default:
            throw (error_chess("Invalid piece value"));
    }

}

template<Side side>
int PieceStats<side>::getSumPieces() {
    int sum = 0;
    std::for_each(nrPieces.begin(), nrPieces.end(), [&sum](int x) { sum += x; });
    return sum;
}

template<Side side>
int PieceStats<side>::getScore() {
    int score = 0;
    score += nrPieces[0] * (int) PieceScores::pawn;
    score += nrPieces[1] * (int) PieceScores::knight;
    score += nrPieces[2] * (int) PieceScores::bishop;
    score += nrPieces[3] * (int) PieceScores::rook;
    score += nrPieces[4] * (int) PieceScores::queen;

    return score;
}


template
class PieceStats<Side::WHITE>;


template
class PieceStats<Side::BLACK>;

