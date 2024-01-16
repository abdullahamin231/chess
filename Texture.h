#pragma once
#include<SFML/Graphics.hpp>
using namespace sf;

enum PieceType{
    None = 0,
    King = 1,
    Pawn = 2,
    Knight = 3,
    Bishop = 4,
    Rook = 5,
    Queen = 6,
    White = 8,
    Black = 16
};


enum TextureIndex {
    blackKing, blackPawn, blackKnight, blackBishop, blackRook, blackQueen, whiteKing, whitePawn, whiteKnight, whiteBishop, whiteRook, whiteQueen,
};

class allTextures{
private:
    Texture textures[12];
public:
    allTextures();
    Texture& getTexture(PieceType type, PieceType color);
};