/**
 * @file ScoringSystem.cpp
 * @author your name (you@domain.com)
 * @brief Utility application for Qwirkle games
 * @version 0.1
 * @date 2022-08-07
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "ScoringSystem.h"

ScoringSystem::ScoringSystem()
{
}

ScoringSystem::~ScoringSystem()
{
}

int ScoringSystem::countPoints(Board *board, int row, int column)
{
    int score = 0;
    score = countPointsVertical(board, row, column) + countPointsHorizontal(board, row, column);

    return score;
}

int ScoringSystem::countPointsVertical(Board *board, int row, int column)
{
    int points = 0;
    if (board != nullptr)
    {
        int row_count = board->getTiles2DVector().size();
        int column_count = board->getTiles2DVector().at(row).size();

        while (isTileNorthOf(board, row, column) && row >= 0)
        {
            points++;
            row--;
        }

        while (isTileSouthOf(board, row, column) && row < row_count)
        {
            points++;
            row++;
        }
    }

    if (points >= 5)
    {
        yellQwirkle();
        points += QWIRKLE_BONUS;
    }

    return points;
}

int ScoringSystem::countPointsHorizontal(Board *board, int row, int column)
{
    int points = 0;
    if (board != nullptr)
    {
        int row_count = board->getTiles2DVector().size();
        int column_count = board->getTiles2DVector().at(row).size();

        while (isTileEastOf(board, row, column) && column >= 0)
        {
            points++;
            column--;
        }

        while (isTileWestOf(board, row, column) && column < column_count)
        {
            points++;
            column++;
        }
    }

    if (points >= 5)
    {
        yellQwirkle();
        points += QWIRKLE_BONUS;
    }

    return points;
}

bool ScoringSystem::isTileEastOf(Board *board, int row, int column)
{
    bool theresATileEastOfHere = false;
    if (board->getTileAt(row, column + 1) != nullptr)
    {
        theresATileEastOfHere = true;
    }
    return theresATileEastOfHere;
}

bool ScoringSystem::isTileWestOf(Board *board, int row, int column)
{
    bool theresATileWestOfHere = false;
    if (board->getTileAt(row, column - 1) != nullptr)
    {
        theresATileWestOfHere = true;
    }
    return theresATileWestOfHere;
}

bool ScoringSystem::isTileNorthOf(Board *board, int row, int column)
{
    bool theresATileNorthOfHere = false;
    if (board->getTileAt(row - 1, column) != nullptr)
    {
        theresATileNorthOfHere = true;
    }
    return theresATileNorthOfHere;
}

bool ScoringSystem::isTileSouthOf(Board *board, int row, int column)
{
    bool theresATileSouthOfHere = false;
    if (board->getTileAt(row + 1, column) != nullptr)
    {
        theresATileSouthOfHere = true;
    }
    return theresATileSouthOfHere;
}

void ScoringSystem::yellQwirkle()
{
    std::cout << QWIRKLE_CRY << std::endl;
}
