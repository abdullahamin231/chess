#include "piece.h"
#include <SFML/Graphics.hpp>
#include "board.h"
#include<iostream>

using namespace std;
using namespace sf;

bool check = false;
bool* checkP = &check;

void checkAndDrawMove(int x, int y, int dx, int dy, PieceType color, RenderWindow &window, RectangleShape* legalBlocks, int** Square) {
    for (int i = 1; i <= 7; i++) {
        int newX = x + i * dx;
        int newY = y + i * dy;

       

        if (newX < 0 || newX >= 8 || newY < 0 || newY >= 8) {
            break; // Check if we're out of the board bounds
        }

        if ((Square[newX][newY] & 24) == color) {
            // Stop if there is a piece of the same color
            break;
        }
        legalBlocks[newX + newY].setPosition(newY * 120, newX * 120);
        window.draw(legalBlocks[newX + newY]);


        if (Square[newX][newY] & 7) {
            // Stop if there is a piece in the way
            break;
        }
        
        // Draw legal move if the square is empty (None)
        if ((Square[newX][newY] & 7) == None) {
            legalBlocks[newX + newY].setPosition(newY * 120, newX * 120);
            window.draw(legalBlocks[newX + newY]);
        }
    }
}



void Piece::drawLegalMoves(RenderWindow& window, int** Square, int x, int y, int& turn, RectangleShape** block, int** KP){
    
    PieceType piece = (PieceType)(Square[x][y] & 7);
    PieceType color = (PieceType)(Square[x][y] & 24);
    RectangleShape* legalBlocks = new RectangleShape[21]; // where 21 is the max legal moves possible for an individual piece
    for(int i = 0; i < 21; i++){
        legalBlocks[i].setSize(Vector2f(120, 120));
        legalBlocks[i].setFillColor(Color(150,255,150, 180));
    }

    if((color == White)){
        switch(piece){
            case King:
                for(int n = -1; n <= 1; n++){
                    for(int m = -1; m <= 1; m++){
                        if(x+n >= 0 && x+n <= 7 && y+m >= 0 && y+m <= 7 && (Square[x+n][y+m] & 24) != White){
                            legalBlocks[(n+1)*3 + (m+1)].setPosition((y+m)*120, (x+n)*120);
                            window.draw(legalBlocks[(n+1)*3 + (m+1)]);
                        }
                    }
                }
                break;
            case Pawn:
                if(x != 6){
                    if(x-1 >= 0 && y-1 >= 0 && y+1 <= 7 && (Square[x-1][y] & 24) != White){
                        if((Square[x-1][y+1] & 24) == Black && (Square[x-1][y-1] & 24) == Black){
                            legalBlocks[1].setPosition((y-1)*120, (x-1)*120);
                            window.draw(legalBlocks[1]);
                            legalBlocks[2].setPosition((y+1)*120, (x-1)*120);
                            window.draw(legalBlocks[2]);

                        } else if((Square[x-1][y-1] & 24) == Black){

                            legalBlocks[1].setPosition((y-1)*120, (x-1)*120);
                            window.draw(legalBlocks[1]);
                        } else if ((Square[x-1][y+1] & 24) == Black){
                            legalBlocks[1].setPosition((y+1)*120, (x-1)*120);
                            window.draw(legalBlocks[1]);
                        }
                        if ((Square[x-1][y] & 7) == None){
                            
                            legalBlocks[0].setPosition(y*120, (x-1)*120);
                            window.draw(legalBlocks[0]);
                        }
                    }
                } else {
                    if(x - 1 >= 0 && x - 2 >= 0  && (Square[x-1][y] & 24) != White  && (Square[x-2][y] & 24) != White){
                        legalBlocks[0].setPosition(y*120, (x-1)*120);
                        legalBlocks[1].setPosition(y*120, (x-2)*120);
                        window.draw(legalBlocks[0]);
                        window.draw(legalBlocks[1]);
                    }
                }
                break;
            case Knight:
                for(int n = -2; n <= 2; n++){
                    for(int m = -2; m <= 2; m++){
                        if(abs(n) + abs(m) == 3 && x+n >= 0 && x+n <= 7 && y+m >= 0 && y+m <= 7 && (Square[x+n][y+m] & 24) != White){
                            legalBlocks[(n+2) + (m+2)].setPosition((y+m)*120, (x+n)*120);
                            window.draw(legalBlocks[(n+2) + (m+2)]);

                        }
                    }
                }
                break;
            case Bishop:
                for(int n = -1; n <= 1; n++){
                    for(int m = -1; m <= 1; m++){
                        if(abs(n) == abs(m)){
                            for(int i = 1; i <= 7; i++){
                                if(x+n*i >= 0 && x+n*i <= 7 && y+m*i >= 0 && y+m*i <= 7){
                                    if((Square[x+n*i][y+m*i] & 24) != White){
                                        legalBlocks[(n+1)*3 + (m+1)].setPosition((y+m*i)*120, (x+n*i)*120);
                                        window.draw(legalBlocks[(n+1)*3 + (m+1)]);

                                    }
                                    if((Square[x+n*i][y+m*i] & 24) == Black)
                                            break;
                                    if((Square[x+n*i][y+m*i] & 24) != None)
                                        break;
                                }
                            }
                        }
                    }
                }
                break;
            case Rook:
            // Usage in your main code
                checkAndDrawMove(x, y, 1, 0, White, window, legalBlocks, Square); // Check right
                checkAndDrawMove(x, y, -1, 0, White, window, legalBlocks, Square); // Check left
                checkAndDrawMove(x, y, 0, 1, White, window, legalBlocks, Square); // Check down
                checkAndDrawMove(x, y, 0, -1, White, window, legalBlocks, Square); // Check up
                break;
            case Queen:
                checkAndDrawMove(x, y, 1, 0, White, window, legalBlocks, Square); // Check right
                checkAndDrawMove(x, y, -1, 0, White, window, legalBlocks, Square); // Check left
                checkAndDrawMove(x, y, 0, 1, White, window, legalBlocks, Square); // Check down
                checkAndDrawMove(x, y, 0, -1, White, window, legalBlocks, Square); // Check up
                for(int n = -1; n <= 1; n++){
                    for(int m = -1; m <= 1; m++){
                        if(abs(n) == abs(m)){
                            for(int i = 1; i <= 7; i++){
                                if(x+n*i >= 0 && x+n*i <= 7 && y+m*i >= 0 && y+m*i <= 7){
                                    if((Square[x+n*i][y+m*i] & 24) != White){
                                        legalBlocks[(n+1)*3 + (m+1)].setPosition((y+m*i)*120, (x+n*i)*120);
                                        window.draw(legalBlocks[(n+1)*3 + (m+1)]);

                                    }
                                    if((Square[x+n*i][y+m*i] & 24) != None)
                                        break;
                                }
                            }
                        }
                    }
                }
            default:
                break;
        }
    } else {
        switch(piece){
            case King:
                for(int n = -1; n <= 1; n++){
                    for(int m = -1; m <= 1; m++){
                        if(x+n >= 0 && x+n <= 7 && y+m >= 0 && y+m <= 7 && (Square[x+n][y+m] & 24) != Black){
                            legalBlocks[(n+1)*3 + (m+1)].setPosition((y+m)*120, (x+n)*120);
                            window.draw(legalBlocks[(n+1)*3 + (m+1)]);
                        }
                    }
                }
                break;
            case Pawn:
                if(x != 1){
                    if(x+1 <= 7 && (Square[x+1][y] & 24) != Black){
                        if((Square[x+1][y+1] & 24) == White && (Square[x+1][y-1] & 24) == White){
                            legalBlocks[1].setPosition((y-1)*120, (x+1)*120);
                            window.draw(legalBlocks[1]);

                            legalBlocks[2].setPosition((y+1)*120, (x+1)*120);
                            window.draw(legalBlocks[2]);

                        } else if((Square[x+1][y-1] & 24) == White){
                            legalBlocks[1].setPosition((y-1)*120, (x+1)*120);
                            
                            window.draw(legalBlocks[1]);
                        } else if ((Square[x+1][y+1] & 24) == White){
                            
                            legalBlocks[1].setPosition((y+1)*120, (x+1)*120);
                            window.draw(legalBlocks[1]);
                        } 
                        if ((Square[x+1][y] & 7) == None){
                            legalBlocks[0].setPosition(y*120, (x+1)*120);
                            window.draw(legalBlocks[0]);
                        }
                        
                    }
                } else {
                    if(x + 1 <= 7 && x + 2 <= 7  && (Square[x+1][y] & 24) != Black  && (Square[x+2][y] & 24) != Black){
                        legalBlocks[0].setPosition(y*120, (x+1)*120);
                        legalBlocks[1].setPosition(y*120, (x+2)*120);
                        window.draw(legalBlocks[0]);
                        window.draw(legalBlocks[1]);
                    }
                }
                break;
            case Knight:
                for(int n = -2; n <= 2; n++){
                    for(int m = -2; m <= 2; m++){
                        if(abs(n) + abs(m) == 3 && x+n >= 0 && x+n <= 7 && y+m >= 0 && y+m <= 7 && (Square[x+n][y+m] & 24) != Black){

                            legalBlocks[(n+2) + (m+2)].setPosition((y+m)*120, (x+n)*120);
                            window.draw(legalBlocks[(n+2) + (m+2)]);
                        }
                    }
                }
                break;
            case Bishop:
                for(int n = -1; n <= 1; n++){
                    for(int m = -1; m <= 1; m++){
                        if(abs(n) == abs(m)){
                            for(int i = 1; i <= 7; i++){
                                if(x+n*i >= 0 && x+n*i <= 7 && y+m*i >= 0 && y+m*i <= 7){
                                    if((Square[x+n*i][y+m*i] & 24) != Black){
                                        legalBlocks[(n+1)*3 + (m+1)].setPosition((y+m*i)*120, (x+n*i)*120);
                                        window.draw(legalBlocks[(n+1)*3 + (m+1)]);
                                    }
                                    if((Square[x+n*i][y+m*i] & 24) == White)
                                            break;
                                    if((Square[x+n*i][y+m*i] & 24) != None)
                                        break;
                                }
                            }
                        }
                    }
                }
                break;
            case Rook:
                checkAndDrawMove(x, y, 1, 0, Black, window, legalBlocks, Square); // Check right
                checkAndDrawMove(x, y, -1, 0, Black, window, legalBlocks, Square); // Check left
                checkAndDrawMove(x, y, 0, 1, Black, window, legalBlocks, Square); // Check down
                checkAndDrawMove(x, y, 0, -1, Black, window, legalBlocks, Square); // Check up
                break;
            case Queen:
                checkAndDrawMove(x, y, 1, 0, Black, window, legalBlocks, Square); // Check right
                checkAndDrawMove(x, y, -1, 0, Black, window, legalBlocks, Square); // Check left
                checkAndDrawMove(x, y, 0, 1, Black, window, legalBlocks, Square); // Check down
                checkAndDrawMove(x, y, 0, -1, Black, window, legalBlocks, Square); // Check up
                for(int n = -1; n <= 1; n++){
                    for(int m = -1; m <= 1; m++){
                        if(abs(n) == abs(m)){
                            for(int i = 1; i <= 7; i++){
                                if(x+n*i >= 0 && x+n*i <= 7 && y+m*i >= 0 && y+m*i <= 7){
                                    if((Square[x+n*i][y+m*i] & 24) != Black){
                                        legalBlocks[(n+1)*3 + (m+1)].setPosition((y+m*i)*120, (x+n*i)*120);
                                        window.draw(legalBlocks[(n+1)*3 + (m+1)]);
                                    }
                                    if((Square[x+n*i][y+m*i] & 24) != None)
                                        break;
                                }
                            }
                        }
                    }
                }
            default:
                break;
        }
    }

    delete[] legalBlocks;
}