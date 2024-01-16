#include "/home/abdullah/repos/chess/Texture.h"
#include "/home/abdullah/repos/chess/board.h"
using namespace sf;



allTextures::allTextures(){
    textures[0].loadFromFile("assets/black-king.png");
    textures[1].loadFromFile("assets/black-pawn.png");
    textures[2].loadFromFile("assets/black-knight.png");
    textures[3].loadFromFile("assets/black-bishop.png");
    textures[4].loadFromFile("assets/black-rook.png");
    textures[5].loadFromFile("assets/black-queen.png");
    textures[6].loadFromFile("assets/white-king.png");
    textures[7].loadFromFile("assets/white-pawn.png");
    textures[8].loadFromFile("assets/white-knight.png");
    textures[9].loadFromFile("assets/white-bishop.png");
    textures[10].loadFromFile("assets/white-rook.png");
    textures[11].loadFromFile("assets/white-queen.png");
}

Texture& allTextures::getTexture(PieceType type, PieceType color){
    if(color == White){
        if(type == King)
            return textures[whiteKing];
        else if(type == Pawn)
            return textures[whitePawn];
        else if(type == Knight)
            return textures[whiteKnight];
        else if(type == Bishop)
            return textures[whiteBishop];
        else if(type == Rook)
            return textures[whiteRook];
        else if(type == Queen)
            return textures[whiteQueen];
    }
    else if(color == Black){
        if(type == King)
            return textures[blackKing];
        else if(type == Pawn)
            return textures[blackPawn];
        else if(type == Knight)
            return textures[blackKnight];
        else if(type == Bishop)
            return textures[blackBishop];
        else if(type == Rook)
            return textures[blackRook];
        else if(type == Queen)
            return textures[blackQueen];
    }
    return textures[0];
}