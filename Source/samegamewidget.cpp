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

#include <QtGui>

#include <cstdlib>
#include <ctime>

#include "samegamewidget.h"

SameGameWidget::SameGameWidget(QWidget *parent, int rows, int cols) :
    QWidget(parent),
    gameOver(false),
    score(0),
    highScore(0),
    numRows(rows),
    numCols(cols),
    numPieces(rows*cols),
    playField(0)
{
    setMinimumSize(40*cols, 40*rows);

    playField = new int *[numRows];
    playField[0] = new int[numRows * numCols];

    memset(playField[0], 0, numRows * numCols * sizeof(int));

    for (int i = 1; i < numRows; i++)
            playField[i] = playField[i - 1] + numCols;

    restart();
}

SameGameWidget::~SameGameWidget()
{
    delete[] playField[0];
    delete[] playField;
}

int SameGameWidget::countNeighbours(int x, int y)
{
    int color = playField[y][x];
    int count = 0;

    if (color > 0)
    {
        if (x > 0 && playField[y][x-1] == color)
            count++;
        if (x < numCols-1 && playField[y][x+1] == color)
            count++;
        if (y > 0 && playField[y-1][x] == color)
            count++;
        if (y < numRows-1 && playField[y+1][x] == color)
            count++;
    }

    return count;
}

void SameGameWidget::removePieces(int x, int y, int color)
{
    int count = recursiveRemovePieces(x, y, color);
    decreaseNumPieces(count);
    increaseScore((count - 1) * (count - 1));
    if (getNumPieces() == 0)
            increaseScore(getScore());
    updatePlayField();
}

void SameGameWidget::restart()
{
    gameOver = false;
    resetScore();
    numPieces = numRows * numCols;

    srand(time(NULL));

    for (int y = 0; y < numRows; y++)
    {
        for (int x = 0; x < numCols; x++)
        {
            playField[y][x] = 1 + rand() % 4;
        }
    }

    emit(scoreChanged(score));

    repaint(0, 0, width(), height());
}

void SameGameWidget::increaseScore(int count)
{
    score += count;
    emit(scoreChanged(this->score));
    if (score > highScore)
    {
        highScore = score;
        emit(highscoreChanged(this->score));
    }
}

bool SameGameWidget::noCombinations()
{
    int row, col;

    for (col = numCols - 1; col >= 0; col--)
    {
        for (row = numRows - 1; row >= 0; row--)
        {
            if (playField[row][col] == 0)
                continue;
            if ((col < numCols - 1 && playField[row][col + 1] == playField[row][col]) ||
                (row < numRows - 1 && playField[row + 1][col] == playField[row][col]))
                return false;
        }
    }

    return true;
}

int SameGameWidget::recursiveRemovePieces(int x, int y, int color)
{
    if (playField[y][x] == color)
    {
        int count = 1;
        playField[y][x] = 0;
        if (x > 0)
            count += recursiveRemovePieces(x-1, y, color);
        if (x < numCols-1)
            count += recursiveRemovePieces(x+1, y, color);
        if (y > 0)
            count += recursiveRemovePieces(x, y-1, color);
        if (y < numRows-1)
            count += recursiveRemovePieces(x, y+1, color);
        return count;
    }

    return 0;
}

void SameGameWidget::updatePlayField()
{
    int x, y, z;

    for (x = numCols - 1; x >= 0; x--)
    {
        for (y = numRows - 1; y >= 0; y--)
        {
            if (playField[y][x] > 0)
                continue;
            z = y - 1;
            while (z >= 0 && playField[z][x] == 0)
                z--;
            if (z >= 0)
            {
                playField[y][x] = playField[z][x];
                playField[z][x] = 0;
            }
        }
        if (playField[numRows - 1][x] == 0)
        {
            for (y = numRows - 1; y >= 0; y--)
            {
                for (z = x + 1; z < numCols; z++)
                {
                    playField[y][z - 1] = playField[y][z];
                    playField[y][z] = 0;
                }
            }
        }
    }

    gameOver = noCombinations();
}

void SameGameWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        int mx = event->pos().x();
        int my = event->pos().y();
        int col = mx * getCols() / width();
        int row = my * getRows() / height();
        if (countNeighbours(col, row) > 0)
        {
            removePieces(col, row, getPieceAt(col, row));
            repaint(0, 0, width(), height());
        }
        if (isGameOver())
        {
            QMessageBox msgBox;
            if (getNumPieces() == 0)
            {
                msgBox.setWindowTitle(tr("Congratulations!"));
                msgBox.setText(tr("Congratulations, you won the game with %1 points!").arg(getScore()));
            }
            else
            {
                msgBox.setWindowTitle(tr("Game over!"));
                msgBox.setText(tr("Game over, you got %1 points.").arg(getScore()));
            }
            msgBox.setInformativeText(tr("Do you want to play again?"));
            /*QPushButton *no = */msgBox.addButton(tr("Not really"), QMessageBox::NoRole);
            QPushButton *yes = msgBox.addButton(tr("Sure"), QMessageBox::YesRole);
            msgBox.setDefaultButton(yes);
            msgBox.exec();
            if (msgBox.clickedButton() == yes)
            {
                restart();
            }
            else
            {
                emit(quitGame());
            }
        }
    }
}

void SameGameWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.fillRect(dirtyRect, QColor(0,0,0));

    QColor colors[5] =
    {
        QColor(0x00, 0x00, 0x00),
        QColor(0xff, 0x00, 0x00),
        QColor(0x00, 0xff, 0x00),
        QColor(0x00, 0x00, 0xff),
        QColor(0xff, 0xff, 0x00)
    };

    int ox = dirtyRect.left();
    int oy = dirtyRect.top();
    int ow = dirtyRect.right() - ox;
    int oh = dirtyRect.bottom() - oy;

    int dw = 65536 * ow / getCols();
    int dh = 65536 * oh / getRows();

    for (int y = 0; y < getRows(); y++)
    {
        for (int x = 0; x < getCols(); x++)
        {
            int c = getPieceAt(x,y);
            if (c > 0)
            {
                QRect rect(ox + ((x * dw) / 65536) + 1, oy + ((y * dh) / 65536) + 1, (dw / 65536) - 1, (dh / 65536) - 1);
                painter.setBrush(colors[c]);
                painter.drawEllipse(rect);
            }
        }
    }
}
