#include <iostream>
#include "../Model/Board.h"

const int QWIRKLE_BONUS = 6;
const std::string QWIRKLE_CRY = "\n\nQWIRKLE!\n\n";

class ScoringSystem
{
public:
    ScoringSystem();
    ~ScoringSystem();
    int countPoints(Board *, int row, int column);

private:
    int countPointsVertical(Board *board, int row, int column);
    int countPointsHorizontal(Board *board, int row, int column);
    bool isTileEastOf(Board *board, int row, int column);
    bool isTileWestOf(Board *board, int row, int column);
    bool isTileNorthOf(Board *board, int row, int column);
    bool isTileSouthOf(Board *board, int row, int column);
    void yellQwirkle();
};