#include "/home/abdullah/repos/chess/board.h"
#include "piece.h"

enum rows{
    first = 0, second = 1, seventh = 6, eighth = 7
};


board::board(){
    // Initialising the board
    for(int i = 0; i < 8; i++)
        Square[i] = new int[8];
    
    // Rendering the board
    for(int i = 0; i < x; i++)
        block[i] = new RectangleShape[y];

    for(int i = 0; i < 2; i++)
        KingPos[i] = new int[3];

    for(int i = 0; i < x; i++)
        for(int j = 0; j < y; j++){
            if(((i+j) % 2) == 0)
                block[i][j].setFillColor(white);
            else
                block[i][j].setFillColor(black);
            block[i][j].setSize(block_size);
            block[i][j].setPosition(i*block_size.x, j*block_size.y);
    }
    for(int row = 0; row < x; row++){
        for(int col = 0; col < y; col++){
            if(row == first){
                if(col == 0 || col == 7)
                    Square[row][col] = Rook | Black;
                else if(col == 1 || col == 6)
                    Square[row][col] = Knight | Black;
                else if(col == 2 || col == 5)
                    Square[row][col] = Bishop | Black;
                else if(col == 3)
                    Square[row][col] = Queen | Black;
                else if(col == 4){
                    Square[row][col] = King | Black;
                    KingPos[bK][0] = row; KingPos[bK][1] = col; KingPos[bK][2] = Black;
                
                }
            }
            else if(row == second)
                Square[row][col] = Pawn | Black;
            else if(row == seventh)
                Square[row][col] = Pawn | White;
            else if(row == eighth){
                if(col == 0 || col == 7)
                    Square[row][col] = Rook | White;
                else if(col == 1 || col == 6)
                    Square[row][col] = Knight | White;
                else if(col == 2 || col == 5)
                    Square[row][col] = Bishop | White;
                else if(col == 3)
                    Square[row][col] = Queen | White;
                else if(col == 4){
                    Square[row][col] = King | White;
                    KingPos[wK][0] = row; KingPos[wK][1] = col; KingPos[wK][2] = White;
                }
            }
            else
                Square[row][col] = None;
        }
    }
}


board::~board(){
    for(int i = 0; i < x; i++){
        delete Square[i];
        delete[] block[i];
        if(i < 2)
            delete KingPos[i];
    }
    delete[] block; delete[] Square; delete[] KingPos;
}

void board::draw(RenderWindow& window){
    for(int row = 0; row < x; row++){
        for(int col = 0; col < y; col++){
            window.draw(block[row][col]);
        }
    }
    // in printing row is left to right and column is top to bottom
    // in array row is top to bottom but print is left to right
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(Square[j][i] != None){
                Sprite s;
                s.setTexture(t.getTexture((PieceType)(Square[j][i] & 7), (PieceType)(Square[j][i] & 24)));
                s.setPosition(i*block_size.x + offset.x, j*block_size.y + offset.y);
                window.draw(s);
            }
        
        } 
    }
};

bool board::isKingInCheck(PieceType kingColor){
    kingPositions k = kingPositions((kingColor == White) ? wK : bK);
    int kingX = KingPos[k][0];
    int kingY = KingPos[k][1];
    int kingPiece = (Square[kingX][kingY] & 7);
    PieceType enemyColor = (kingColor == White) ? Black : White;
    int enemyPiece;
    int enemyX, enemyY;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            enemyPiece = Square[i][j];
            if((enemyPiece & 7) != None && (enemyPiece & 24) == enemyColor){
                enemyX = i; enemyY = j;
                if(legalMove(enemyX, enemyY, kingX, kingY, enemyPiece, kingPiece, *(KingPos[k]+2))){
                    return true;
                }
            }
        }
    }
    return false;
}

bool board::legalMove(int currentX, int currentY, int targetX, int targetY, int currentPiece, int targetPiece, int& turn){
    PieceType currentType = PieceType(currentPiece & 7);  
    PieceType currentColor = PieceType(currentPiece & 24);
    PieceType targetType = PieceType(targetPiece & 7); 
    PieceType targetColor = PieceType(targetPiece & 24);
    enum turnColor {white, black};
    
    
    if((currentColor == White && turn == black) || (currentColor == Black && turn == white)){
        return false;
    }
    if(currentColor != targetColor){
        if(currentType == Pawn){
            if(currentColor == White){
                if(currentX == 6 && (targetX == 5 || targetX == 4)){
                    return true;
                } 
            } else {
                if(currentX == 1 && (targetX == 2 || targetX == 3)){
                    return true;
                } 
            }
            if( abs(currentX - targetX) == 1 && (targetY == (currentY - 1) || targetY == (currentY + 1))){
                    return true;
            } else if (abs(currentX-targetX) == 1 && targetY == currentY && targetPiece == None){
                return true;
            }
        } else if (currentType == King){
            if(abs(currentX - targetX) == 1 && currentY == targetY){
                return true;
            } else if (abs(currentY - targetY) == 1 && currentX == targetX){
                return true;
            } else if (abs(currentX - targetX) == 1 && abs(currentY - targetY) == 1){
                return true;
            }
        } else if (currentType == Knight){
            if(abs(currentX - targetX) == 2 && abs(currentY - targetY) == 1){
                return true;
            } else if (abs(currentX - targetX) == 1 && abs(currentY - targetY) == 2){
                return true;
            }
        } else if (currentType == Bishop){
            if(abs(currentX - targetX) == abs(currentY - targetY)){
                return true;
            }
        } else if (currentType == Rook){
            if(currentX == targetX && currentY != targetY){
                return true;
            } else if (currentX != targetX && currentY == targetY){
                return true;
            }
        } else if (currentType == Queen){
            if(abs(currentX - targetX) == abs(currentY - targetY)){
                return true;
            } else if (currentX == targetX && currentY != targetY){
                return true;
            } else if (currentX != targetX && currentY == targetY){
                return true;
            }
        }
    }
    return false;

};



void board::updateBoard(int currentX, int currentY, int targetX, int targetY, int& turn){
    int temp = Square[currentX][currentY];
    Square[currentX][currentY] = None;
    if((temp & 7) == Pawn && targetX == 0)
        Square[targetX][targetY] = Queen | White;
    else if((temp & 7) == Pawn && targetX == 7)
        Square[targetX][targetY] = Queen | Black;
    else{
        if(temp == (King | White)){
            KingPos[wK][0] = targetX; KingPos[wK][1] = targetY;
        } else if (temp == (King | Black)){
            KingPos[bK][0] = targetX; KingPos[bK][1] = targetY;
        }
        Square[targetX][targetY] = temp;
    }
};

void board::UnmakeMove(int currentX, int currentY, int targetX, int targetY, int& turn, int targetPiece){
    Square[currentX][currentY] = Square[targetX][targetY];
    Square[targetX][targetY] = targetPiece;
};

void board::displayLegalMoves(RenderWindow& window, int x, int y, int& turn, RectangleShape** block, int** KP){
    if(x != -1 && y != -1 )
        Piece::drawLegalMoves(window, Square, x, y, turn, block, KP);
};

int** board::getKP(){
    return KingPos;
}

int** board::getSquare(){
    return Square;
};
RectangleShape** board::getBlocks(){
    return block;
}; 

void board::printKP(){
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 3; j++){
            cout << KingPos[i][j] << " ";
        }    
        cout << endl;
    }
};

void board::printState(){
    fstream f("board.txt", ios::app);
    f << "Board at " << endl;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            f << Square[i][j] << " ";
            cout << Square[i][j] << " ";
        } cout << endl; f << endl;
    } f << endl;
    f.close();
}