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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

class QAction;
class QLabel;
class QMenu;

class SameGameWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void updateScore(int value);
    void updateHighscore(int value);

private slots:
    void newGame();
    void rules();
    void about();

private:
    void createActions();
    void createMenus();

    QMenu *gameMenu;
    QMenu *helpMenu;

    QAction *newGameAct;
    QAction *quitAct;
    QAction *rulesAct;
    QAction *aboutAct;

    SameGameWidget *game;

    QLabel *scoreLabel;
    QLabel *highscoreLabel;
};

#endif // MAINWINDOW_H
