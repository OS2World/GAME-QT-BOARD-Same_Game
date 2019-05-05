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
#include "mainwindow.h"
#include "samegamewidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("SameGame"));

    createActions();
    createMenus();

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->setContentsMargins(2, 2, 2, 2);

    scoreLabel = new QLabel;
    scoreLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    scoreLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    updateScore(0);

    highscoreLabel = new QLabel;
    highscoreLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    highscoreLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    updateHighscore(0);

    hbox->addWidget(scoreLabel);
    hbox->addWidget(highscoreLabel);

    game = new SameGameWidget(this, 10, 16);
    game->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(game, SIGNAL(scoreChanged(int)), this, SLOT(updateScore(int)));
    connect(game, SIGNAL(highscoreChanged(int)), this, SLOT(updateHighscore(int)));
    connect(game, SIGNAL(quitGame()), this, SLOT(close()));

    vbox->addWidget(game);
    vbox->addLayout(hbox);

    QWidget *widget = new QWidget;
    widget->setLayout(vbox);
    setCentralWidget(widget);
}

MainWindow::~MainWindow()
{

}

void MainWindow::updateScore(int value)
{
    scoreLabel->setText(tr("Score: %1").arg(value));
}

void MainWindow::updateHighscore(int value)
{
    highscoreLabel->setText(tr("High: %1").arg(value));
}

void MainWindow::newGame()
{
    game->restart();
}

void MainWindow::rules()
{
    QMessageBox::information(this, tr("Rules"), tr("SameGame is a puzzle game with the following rules:\n\n"
                                                   "1. You may remove pieces provided at least two are adjacent either horizontally or vertically.\n"
                                                   "2. Let n = number of removed pieces. Then score += (n-1)^2.\n"
                                                   "3. If you remove all pieces, your score will be doubled.\n"
                                                   "4. The game ends when you have removed all pieces or there are no removable pieces."));
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About SameGame"), tr("Copyright (C) 2011  Jari Karppinen\n"
                                                      "\n"
                                                      "This program is free software: you can redistribute it and/or modify "
                                                      "it under the terms of the GNU General Public License as published by "
                                                      "the Free Software Foundation, either version 3 of the License, or "
                                                      "(at your option) any later version."
                                                      "\n"
                                                      "This program is distributed in the hope that it will be useful, "
                                                      "but WITHOUT ANY WARRANTY; without even the implied warranty of "
                                                      "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the "
                                                      "GNU General Public License for more details."
                                                      "\n"
                                                      "You should have received a copy of the GNU General Public License "
                                                      "along with this program.  If not, see <http://www.gnu.org/licenses/>."));
}

void MainWindow::createActions()
{
    newGameAct = new QAction(tr("&New game"), this);
    newGameAct->setShortcuts(QKeySequence::New);
    connect(newGameAct, SIGNAL(triggered()), this, SLOT(newGame()));

    quitAct = new QAction(tr("&Quit"), this);
    quitAct->setShortcuts(QKeySequence::Quit);
    connect(quitAct, SIGNAL(triggered()), this, SLOT(close()));

    rulesAct = new QAction(tr("&Rules"), this);
    rulesAct->setShortcuts(QKeySequence::HelpContents);
    connect(rulesAct, SIGNAL(triggered()), this, SLOT(rules()));

    aboutAct = new QAction(tr("&About"), this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
}

void MainWindow::createMenus()
{
    gameMenu = menuBar()->addMenu(tr("&Game"));
    gameMenu->addAction(newGameAct);
    gameMenu->addAction(quitAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(rulesAct);
    helpMenu->addAction(aboutAct);
}
