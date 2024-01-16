#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include<fstream>
#include "/home/abdullah/repos/chess/Texture.h"

using namespace sf;
using namespace  std;

// forward declaration of allTextures class (just like fn prototyping)
class allTextures;

enum kingPositions{
    wK = 0, bK = 1
};


class board{

private:
    // rows, columns
    const int x = 8; const int y = 8;
    Color white{233,237,204};
    Color black{119,153,84};

    // actual state of the board represented numerically
    int** Square = new int*[8];

    // handles rendering the board
    RectangleShape** block = new RectangleShape*[x];
    Vector2f block_size{120.0f, 120.0f};
    Vector2f offset{-5.0f, -5.0f};
    int** KingPos = new int*[2];

public:
    allTextures t;
    board();
    ~board();
    void draw(RenderWindow& window);
    void printState();
    int** getSquare();
    int** getKP();
    void printKP();
    bool isKingInCheck(PieceType kingColor);
    RectangleShape** getBlocks();
    void UnmakeMove(int currentX, int currentY, int targetX, int targetY, int& turn, int targetPiece);
    void updateBoard(int currentX, int currentY, int targetX, int targetY, int& turn);
    bool legalMove(int currentX, int currentY, int targetX, int targetY, int currentPiece, int targetPiece, int& turn);
    void displayLegalMoves(RenderWindow& window, int x, int y, int& turn, RectangleShape** block, int** KP);
};