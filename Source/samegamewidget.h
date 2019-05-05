/*
    SameGame
    Copyright (C) 2011  Jari Karppinen

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SAMEGAMEWIDGET_H
#define SAMEGAMEWIDGET_H

#include <QWidget>

class QMouseEvent;
class QPaintEvent;

class SameGameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SameGameWidget(QWidget *parent, int rows, int cols);
    ~SameGameWidget();

    int getCols() { return this->numCols; }
    int getRows() { return this->numRows; }
    int getNumPieces() { return this->numPieces; }
    int getPieceAt(int x, int y) { return this->playField[y][x]; }
    int getScore() { return this->score; }
    int getHighScore() { return this->highScore; }
    bool isGameOver() { return this->gameOver; }
    int countNeighbours(int x, int y);
    void removePieces(int x, int y, int color);
    void restart();

signals:
    void scoreChanged(int value);
    void highscoreChanged(int value);
    void quitGame();

public slots:

protected:
    void decreaseNumPieces(int count) { this->numPieces -= count; }
    void resetScore() { this->score = 0; emit(scoreChanged(score)); }
    void increaseScore(int count);
    bool noCombinations();
    int recursiveRemovePieces(int x, int y, int color);
    void updatePlayField();

    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

    bool gameOver;
    int score;
    int highScore;
    int numRows;
    int numCols;
    int numPieces;
    int **playField;
};

#endif // SAMEGAMEWIDGET_H
