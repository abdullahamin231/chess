#include<iostream>
#include<SFML/Graphics.hpp>
#include "board.h"
#include "Texture.h"
#include "piece.h"

using namespace std;
using namespace sf;

int main(){
    RenderWindow window(VideoMode(1280, 960), "chess hopefully");
    board b;
    int x = -1, y = -1;
    bool selected = false;
    int turn = 0;
    Text turnText;
    Font font;
    font.loadFromFile("font/RobotoMono-Regular.ttf");
    turnText.setFont(font);
    turnText.setCharacterSize(40);
    turnText.setFillColor(Color::White);
    turnText.setPosition(970, 50);
    turnText.setString("Turn : White");

    Text checkText;
    checkText.setFont(font);
    checkText.setCharacterSize(25);
    checkText.setFillColor(Color::White);
    checkText.setPosition(970, 150);

    while(window.isOpen()){
        Event event;
        while(window.pollEvent(event)){
            if(event.type == Event::Closed){
                window.close();
            } else if (event.type == Event::KeyPressed){
                if (event.key.code == Keyboard::P){
                    b.printState();
                } else if (event.key.code == Keyboard::T){
                    cout << "Turn : " << ((turn == 0) ? " white " : " black ") << endl;
                } else if (event.key.code == Keyboard::K){
                    b.printKP();
                } 
            } else if ((event.type == Event::MouseButtonPressed) && (event.mouseButton.button == Mouse::Left) && selected ){
                int targetX = Mouse::getPosition(window).y / 120;
                int targetY = Mouse::getPosition(window).x / 120;
                if(b.legalMove(x, y, targetX, targetY, b.getSquare()[x][y], b.getSquare()[targetX][targetY], turn)){
                    b.updateBoard(x, y, targetX, targetY, turn);
                    turn = (turn + 1) % 2;
                    turnText.setString("Turn : " + ((turn == 0) ? string("White") : string("Black")));
                    PieceType kingColor = (turn == 1) ? Black : White; // The color of the king we want to check
                    if (b.isKingInCheck(kingColor)) {
                        string k = (kingColor == White) ? "BLACK" : "WHITE";
                        string t = (turn == 0) ? "WHITE" : "BLACK";
                        cout << t << " KING\n IN CHECK BY " <<  k << endl;
                        checkText.setString(t+" KING \n IN CHECK BY \n" + k);
                    }
                }
                selected = false;
            } else if ((event.type == Event::MouseButtonPressed) && (event.mouseButton.button == Mouse::Left)){
                selected = true;
                x = Mouse::getPosition(window).y / 120;
                y = Mouse::getPosition(window).x / 120;
            } 
        }
        window.clear(Color(48,48,48, 235));
        b.draw(window);
        b.displayLegalMoves(window, x, y, turn, b.getBlocks(), b.getKP());
        window.draw(turnText);
        window.draw(checkText);
        window.display();
    }
    return 0;
}