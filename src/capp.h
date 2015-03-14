#ifndef CAPP_H
#define CAPP_H
#include <3ds.h>
class Capp
{
public:
Capp();
enum State {Intro,Mmenu,Ggame,Quit};
enum Setting {Easy, Light, Medium, Hard}; // coming soon maybe?.
int gameState;
void init();
void input();
void draw();
void update();
private:
int testFlood(int r, int c, int newcol);
int updateBoard(int ncolor);
int oldColor;
void randBoard();
int Board[20][20];
int rows;
int cols;
int select_x;
int select_y;
int menu_x;
int menu_y;
int movesMade;
int maxMoves;
bool madeMove;


};

#endif