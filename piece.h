#pragma once
#include<SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class Piece{
public:
    static void drawLegalMoves(RenderWindow& window, int** Square, int x, int y, int& turn, RectangleShape** block, int** KP);
};