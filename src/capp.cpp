#include "capp.h"
#include "HRender.h"
#include <stdlib.h> 
#include <3ds.h>
#include <stdio.h>
#include "Title_bin.h"

Render Rend;
Capp::Capp()
{
  gameState = State::Mmenu; 
  rows = 20;
  cols = 20;
  select_x = 10;
  select_y = 5;
  movesMade = 0;
  maxMoves = 40;
  oldColor = 0;
  menu_x = 160;
  menu_y = 120;
  madeMove = false;
}
void Capp::input()
{
   touchPosition myPos;
   hidTouchRead(&myPos);
   u16 posX = myPos.px;
   u16 posY = myPos.py;
   hidScanInput();
   u32 kDown = hidKeysDown();
  if (gameState == State::Mmenu)
  {
    if (posX >=100 && posX <= 180 && posY >= 90 && posY <= 120)
	{
	   randBoard();
	   gameState = State::Ggame;
	}
	if (posX >=100 && posX <= 180 && posY >= 130 && posY <= 160)
	{
	   gameState = State::Quit;
	}
    if (kDown & KEY_A)
	{
	  gameState = State::Ggame;
	}
  }
  if (gameState == State::Ggame)
  {
  
    if (posX >10 && posX <= 90 && posY >= 5 && posY <= 30)
	{
	   madeMove = true;
	   updateBoard(0);
	   
	}
	if (posX >=10 && posX <= 90 && posY >= 35 && posY <= 60)
	{
	   madeMove = true;
	   updateBoard(1);
	}
	if (posX >=10 && posX <= 90 && posY >= 65 && posY <= 90)
	{
	   madeMove = true;
	   updateBoard(2);
	}
	if (posX >=10 && posX <= 90 && posY >= 95 && posY <= 120)
	{
	   madeMove = true;
	   updateBoard(3);
	   
	}
	if (posX >=10 && posX <= 90 && posY >= 125 && posY <= 150)
	{
	   madeMove = true;
	   updateBoard(4);
	}
	if (posX >=10 && posX <= 90 && posY >= 155 && posY <= 180)
	{
	   madeMove = true;
	   updateBoard(5);
	   
	}
	if (posX >=240 && posX <= 318 && posY >= 208 && posY <= 238)
	{
	  posX = 0;
	  posY = 0;
	  gameState = State::Mmenu;
	  
	}
	
}
}
void Capp::draw()
{ 
   char buffer[110];
  if (gameState == State::Mmenu)
  {
  
    Rend.clearTop();
	Rend.clearBottom();
	//top screen 
	Rend.drawFillRect(1,1,400,240,0,0,255,Rend.topl);
	Rend.gfxDrawSprite(GFX_TOP,GFX_LEFT,(u8*)Title_bin,240,400,0,0);
	//bottom screen
	Rend.drawFillRect(1,1,320,240,0,0,255,Rend.bottom);
	Rend.drawFillRect(120,80,200,170,192,192,192,Rend.bottom);
	sprintf(buffer, "Start");
	Rend.drawString(buffer,140,100,255,0,0,Rend.bottom,GFX_BOTTOM);
	sprintf(buffer, "Quit");
	Rend.drawString(buffer,140,140,255,0,0,Rend.bottom,GFX_BOTTOM);
	Rend.screenRender();
  }
  if (gameState == State::Ggame)
  {
   Rend.clearBottom();
   Rend.clearTop();
   //top screen
   Rend.drawFillRect(1,1,400,240,0,0,153,Rend.topl);
   Rend.drawRect(1,1,399,239,0,128,255,Rend.topl);
   Rend.drawFillRect(20,21,380,221,160,160,160,Rend.topl); 
   Rend.drawRect(20,21,380,221,0,128,255,Rend.topl);
   Rend.drawRect(100,20,300,220,0,0,0,Rend.topl);
   //draw the littleboxes
   int gx;
   int gy;
   for (int r = 0; r < rows;r++)
   {
     for (int c = 0; c<cols;c++)
	 {
	   gx = (r*10)+100; // 0,0 = 100,20
	   gy = (c*10)+20;
	   switch (Board[r][c])
	   {
	   case 0:Rend.drawFillRect(gx,gy,gx+10,gy+10,204,0,0,Rend.topl); break;
	   case 1:Rend.drawFillRect(gx,gy,gx+10,gy+10,255,128,0,Rend.topl); break;
	   case 2:Rend.drawFillRect(gx,gy,gx+10,gy+10,255,255,0,Rend.topl); break;
	   case 3:Rend.drawFillRect(gx,gy,gx+10,gy+10,128,255,0,Rend.topl); break;
	   case 4:Rend.drawFillRect(gx,gy,gx+10,gy+10,127,0,255,Rend.topl); break;
	   case 5:Rend.drawFillRect(gx,gy,gx+10,gy+10,255,0,255,Rend.topl); break;
	   }
	 }
   }
   //bottom screen
   Rend.drawFillRect(1,1,319,239,0,0,204,Rend.bottom);
   Rend.drawRect(1,1,319,239,0,128,255,Rend.bottom);
   //background color buttons
   Rend.drawFillRect(2,1,95,200,192,192,192,Rend.bottom);
   //color buttons
   Rend.drawFillRect(10,5,90,30,204,0,0,Rend.bottom);
    Rend.drawFillRect(10,35,90,60,255,128,0,Rend.bottom);
	 Rend.drawFillRect(10,65,90,90,255,255,0,Rend.bottom);
	  Rend.drawFillRect(10,95,90,120,128,255,0,Rend.bottom);
	   Rend.drawFillRect(10,125,90,150,127,0,255,Rend.bottom);
		Rend.drawFillRect(10,155,90,180,255,0,255,Rend.bottom);
	// draw selector box
	    Rend.drawRect(select_x,select_y,select_x+80,select_y+25,255,255,255,Rend.bottom);
		Rend.drawRect(select_x+1,select_y+1,select_x+79,select_y+24,255,255,255,Rend.bottom);    
	// draw text	
		Rend.drawFillRect(220,2,318,50,192,192,192,Rend.bottom);
		sprintf(buffer, "Moves Made");
	    Rend.drawString(buffer,230,2,0,0,0,Rend.bottom,GFX_BOTTOM);
		sprintf(buffer, "%d",movesMade);
	    Rend.drawString(buffer,230,12,0,0,0,Rend.bottom,GFX_BOTTOM);
		sprintf(buffer, "/");
	    Rend.drawString(buffer,250,12,0,0,0,Rend.bottom,GFX_BOTTOM);
		sprintf(buffer, "%d",maxMoves);
	    Rend.drawString(buffer,270,12,0,0,0,Rend.bottom,GFX_BOTTOM);
		
    //draw exit buttons
	    Rend.drawFillRect(240,208,318,238,255,0,0,Rend.bottom);
		Rend.drawRect(240,208,318,238,204,229,255,Rend.bottom);
		sprintf(buffer, "Exit");
	    Rend.drawString(buffer,250,220,255,255,255,Rend.bottom,GFX_BOTTOM);
   Rend.screenRender();
  }
}
void Capp::init()
{
// sets board to zero
randBoard();
}

void Capp::randBoard()
{
int color = 0;  //color corresponds to ints
for (int i = 0;i<rows;i++)
{
  for (int h = 0; h<cols;h++)
  {
    color = rand() % 6 ; 
    Board[i][h] = color;
	
  }
} 
  oldColor = Board[0][0];
  movesMade = 0;
}

void Capp::update()
{
  int total = 0;
  if(madeMove == true)
  {
   movesMade +=1;
   madeMove = false;
  }
  if (movesMade > maxMoves)
  {
  gameState = State::Mmenu;
  }
  for (int i = 0;i<rows;i++)
{
  for (int h = 0; h<cols;h++)
  {
    if (Board[i][h] == Board[0][0])
	{
	  total+=1;
	  if (total == (rows*cols))
	  {
	   gameState = State::Mmenu;
	  }
	}
  }
  
}
}
int Capp::testFlood(int r, int c,int newcol)
{

   if (Board[r][c] != newcol && Board[r][c] == oldColor)
   {
   Board[r][c] = newcol;
   if (r < rows-1)
   {  testFlood(r+1,c,newcol); }
   if (c < cols-1)
   {  testFlood(r,c+1,newcol); }
   if (r > 0)
   {  testFlood(r-1,c,newcol); }
   if (c > 0)
   {  testFlood(r,c-1,newcol); }
   }
   return 0;
}
int  Capp::updateBoard(int ncolor)
{    
	 oldColor = Board[0][0]; 
	 if (ncolor == oldColor)
	 {
	   return 0;
	 }
	 testFlood(0,0,ncolor);
	 update();
     return 0;
     
}


