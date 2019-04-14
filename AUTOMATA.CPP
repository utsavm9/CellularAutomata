//Libraries
#include <conio.h>
#include <iostream.h>
#include <ctype.h>
#include <iomanip.h>
#include <math.h>

//Matrix constants
#define height 42
#define width 78
#define heightS 21

//Characters for Border
#define BTMRC ((char) 217)
#define BTMLC ((char) 192)
#define TOPRC ((char) 191)
#define TOPLC ((char) 218)
#define VERTB ((char) 179)
#define HORIB ((char) 196)

//Characters for cells
#define TOPC ((char) 223)
#define BTMC ((char) 220)
#define BOTH ((char) 219)
#define NONE ' '

//Menu
#define MENU ((char) 240)
#define NOMENU 0
#define MENU1 1
#define MENUC 2
#define MENUW 3
#define ABOUT 4
#define HELPM 5

//Pattern for Game of Life
#define GOSPER 1
#define GALAXY 2
#define K5 3
#define QUEEN 4
#define FIGURE 8
#define WEEK 7
#define CROSS 5


//Represents the pointer on the screen
struct Pointer {
  int x;
  int y;
  int justEdited;
} pointer;


//Initializations
int cells [2] [height] [width];        //Cell Board
char screenCells [heightS] [width];    //Screen Cells
int c = 0;                             //Current board
int conway = 1;                        //Is Conway's CA Active
int menu = NOMENU;                     //Current Menu
long int generations = 0;              //Generations count
int ruleD = 150, ruleB[8];             //Rules for Wolfram CA
int justInput = 0;                     //Smoothes input for Wolfram Rule



//Saved Patterns
/*****************************************************************/
//GOSPER
const int gosperH = 9, gosperW = 36;
int gosperP[gosperH][gosperW] = 
        { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
				  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,
				  0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
				  0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
				  1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
				  1,1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,
				  0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
				  0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
				  0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
//WEEKENDER
const int weekH = 16, weekW = 11;
int weekP[weekH][weekW] = 
        { 0,0,0,0,0,0,0,0,1,0,0,
			    0,0,0,0,0,0,1,1,0,1,1,
			    0,0,0,1,0,1,0,0,1,0,0,
			    0,0,0,1,0,0,0,0,0,0,0,
			    0,1,0,1,0,0,0,0,0,0,0,
			    1,0,0,1,0,0,0,0,0,0,0,
			    1,0,0,0,1,1,0,0,0,0,0,
			    0,0,0,0,1,1,0,0,0,0,0,
			    0,0,0,0,1,1,0,0,0,0,0,
			    1,0,0,0,1,1,0,0,0,0,0,
			    1,0,0,1,0,0,0,0,0,0,0,
			    0,1,0,1,0,0,0,0,0,0,0,
			    0,0,0,1,0,0,0,0,0,0,0,
			    0,0,0,1,0,1,0,0,1,0,0,
			    0,0,0,0,0,0,1,1,0,1,1,
			    0,0,0,0,0,0,0,0,1,0,0};

//QUEEN BEE SHUTTLE
const int queenH = 7, queenW = 22;
int queenP[queenH][queenW] = 
       { 0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,
			   0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,
			   0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,
			   1,1,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,1,
			   1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,1,
			   0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,
			   0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0 };

//58P5H1V1
const int k5H = 23, k5W = 23;
int k5P[k5H][k5W] = 
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,
		     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,
		     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,
		     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,0,0,1,
		     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		     0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,0,0,1,
		     0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,0,
		     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,1,1,0,
		     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,
		     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		     0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,
		     0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,
		     0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,
		     0,0,0,0,0,1,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
		     0,0,0,0,0,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
		     0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		     0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		     0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		     0,0,1,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		     1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		     1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		     0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

//FIGURE 8
const int figureH = 6, figureW = 6;
int figureP[figureH][figureW] = 
        { 1,1,0,0,0,0,
				  1,1,0,1,0,0,
				  0,0,0,0,1,0,
				  0,1,0,0,0,0,
				  0,0,1,0,1,1,
				  0,0,0,0,1,1};

//KOK'S GALAXY
const int galaxyH = 9, galaxyW = 9;
int galaxyP[galaxyH][galaxyW] = 
        { 0,0,1,0,0,1,0,1,0,
				  1,1,0,1,0,1,1,1,0,
				  0,1,0,0,0,0,0,0,1,
				  1,1,0,0,0,0,0,1,0,
				  0,0,0,0,0,0,0,0,0,
				  0,1,0,0,0,0,0,1,1,
				  1,0,0,0,0,0,0,1,0,
				  0,1,1,1,0,1,0,1,1,
				  0,1,0,1,0,0,1,0,0};


//CROSS
const int crossH = 8, crossW = 8;
int crossP[crossH][crossW] =
           { 0,0,1,1,1,1,0,0,
			       0,0,1,0,0,1,0,0,
			       1,1,1,0,0,1,1,1,
			       1,0,0,0,0,0,0,1,
			       1,0,0,0,0,0,0,1,
			       1,1,1,0,0,1,1,1,
			       0,0,1,0,0,1,0,0,
			       0,0,1,1,1,1,0,0};

/********************************************************************/

//Initializes the screen cells
void initializeScreen() {
  for (int h = 0; h < heightS; ++h)
    for (int w = 0; w < width; ++w)
      screenCells[h][w] = NONE;
}


//Initializes all cells for 2 boards to 0
void initializeCells() {
  generations = 0;
  for (int j = 0; j < height; ++j)
    for (int k = 0; k < width; ++k)
      cells[0][j][k] = cells[1][j][k] = 0;
}


//Inserts an array of char into a row of the screenCells
void insert(char c[], int row) {
  for (int i = 0; (c[i] != '\0') && (i < 77); ++i)
    screenCells[row][i] = c[i];
}


void screenMenu() {
  initializeScreen();

  //Printing main menu
  if (menu == MENU1) {
    char text1[77] = "  (1) Change Cellular Automaton ";
    char text2[77] = "  (2) Load a 'Game of Life' pattern";
    char text3[77] = "  (3) Load an 'Elementary CA' Rule No.";
    char text4[77] = "  (4) About Cellular Automata";
    char text5[77] = "  (5) Help on Controls";
    char text6[77] = "  << Press M to exit menu";
    char text7[77] ="  Program by Harsh Vardhan Singh, Ishvik Kumar Singh and Utsav Munendra";
    insert(text1,2); insert(text2,4); insert(text3,5); insert(text4,7); insert(text5,8);
    insert(text6,18); insert(text7,20);
  }

  //Printing About Menu
  else if (menu == ABOUT) {
    char text2[77]="  We exist in a complex world, a universe governed by the complex rules of   ";
    char text3[77]="  all sciences. In computational world, it happens that complex systems are  ";
    char text4[77]="  relatively easy to achieve, as evident by the existance of millions of     ";
    char text5[77]="  video games and virtual environments. But in cellular automata, we explore ";
    char text6[77]="  the 'simplest' complex systems which are governed by the simplest rules.   ";
    char text7[77]="  By definition, a complex system is a system of many simple agents that work";
    char text8[77]="  together to exhibit complex, intelligent behavior.                         ";
    char text9[77]="  Stephen Wolfram's Elementary CA is one of most recent and major 1D CA. By  ";
    char text10[77]="  stacking successive generations over one another, various patterns emerge  ";
    char text11[77]="  which can be classified as uniform, oscillating, random and complex. The   ";
    char text12[77]="  next generation is computed through the rule which is a number from 0-255  ";
    char text13[77]="  John Conway's Game of Life is a 2D CA with the fate of cells in the grid   ";
    char text14[77]="  depending upon the number of neighbours around it. Cells with 3 neighbours,";
    char text15[77]="  whether dead or alive, come to life by reproduction, and live cells with 2 ";
    char text16[77]="  neighbours survive. All rest die from underpopulation or crowding.         ";
    char text18[77]="  << Press M to go to Main Menu                                              ";
    insert(text2,1); insert(text3,2); insert(text4,3); insert(text5,4); insert(text6,5);
    insert(text7,6); insert(text8,7); insert(text13,9); insert(text14,10); insert(text15,11);
    insert(text16,12); insert(text9,14); insert(text10,15); insert(text11,16); 
    insert(text12,17); insert(text18,20);
  }

  //Printing Help menu
  else if (menu == HELPM) {
    char text1[30]  = "  (W)    Move pointer up";
    char text2[30]  = "  (A)    Move pointer left";
    char text3[30]  = "  (S)    Move pointer right";
    char text4[30]  = "  (D)    Move pointer down";
    char text5[30]  = "  (C)    Clear cell grid";
    char text6[30]  = "  (K)    Make cell alive/dead";
    char text7[30]  = "  (X)    Exit program";
    char text8[30]  = "  (M)    Control menu";
    char text9[30]  = "  Space  Next generation";
    char text10[30] = "  1-9    Choose menu options";
    char text11[40] = "  << Press M to go back to Main Menu";
    insert(text1,2); insert(text2,3); insert(text3,4); insert(text4,5); 
    insert(text5,7); insert(text6,8); insert(text7,9); insert(text8,10);
     insert(text9,12); insert(text10,13); insert(text11,20);
  }

  //Printing Wolfram's Menu
  else if (menu == MENUW) {
    char text1[60]  = "  Enter Rule Number Below:";
    char text2[60]  = "  Numbers outside 0-255 inclusive range will";
    char text3[60]  = "  matched to a rule inside the range.";
    char text4[60]  = "  Interesting Rules";
    char text5[60]  = "  Serpinski's Triangle: 18, 22, 126, 129, 181";
    char text6[60]  = "  Fractal Triangles: 60, 110";
    char text7[77]  = "  Complex Triangles: 30, 57, 62, 73, 75, 101, 105, 109, 150 ";
    char text8[60]  = "  Complex Patterns: 45, 89, 107 ";
    char text9[60]  = "  Other: 54, 99, 250" ;
    char text11[40] = "  << Press M to go back to Main Menu ";
    insert(text1,2); insert(text2,4); insert(text3,5); insert(text4,8); 
    insert(text8,9); insert(text7,10); insert(text5,11); insert(text6,12);
    insert(text9,13); insert(text11,20);
  }

  //Printing Conway's Menu
  else if (menu == MENUC) {
    char text1[60]  = "  Choose among the following:";
    char text2[60]  = "  (1) Gosper Glider Gun";
    char text3[60]  = "  (2) Weekender";
    char text4[60]  = "  (3) Queen Bee Shuttle";
    char text5[60]  = "  (4) Figure 8";
    char text6[60]  = "  (5) Kok's Galaxy";
    char text7[77]  = "  (6) Cross";
    char text8[60]  = "  (7) 58P5H1V1";
    char text11[40] = "  << Press M to go back to Main Menu ";
    insert(text1,2); insert(text2,4); insert(text3,5); insert(text4,6); 
    insert(text5,7); insert(text6,8); insert(text7,9); insert(text8,10); 
    insert(text11,20);
  }
}

//Loads a Conway CA pattern on the board
void load(int pattern) {
  menu = NOMENU;
  conway = 1;
  int h,w;

  switch(pattern) {
  int h,w,i,j;
    case GOSPER:                        //Gosper Glider Gun
      h = gosperH;
      w = gosperW;
      for (i = 0; i < h; ++i) {
	int next;
	int down = (pointer.y+i)%height;
	for (int j = 0; j < w; ++j) {
	  next = (pointer.x+j)%width;
	  cells[c][down][next] = gosperP[i][j];
	}
	next = pointer.x;
	down = pointer.y;
      }
    break;

    case WEEK:                          //Weekender
      h = weekH;
      w = weekW;
      for (i = 0; i < h; ++i) {
	int next;
	int down = (pointer.y+i)%height;
	for (int j = 0; j < w; ++j) {
	  next = (pointer.x+j)%width;
	  cells[c][down][next] = weekP[i][j];
	}
	next = pointer.x;
	down = pointer.y;
      }
    break;
    case QUEEN:                         //Queen Bee Shutler
      h = queenH;
      w = queenW;
      for (i = 0; i < h; ++i) {
	int next;
	int down = (pointer.y+i)%height;
	for (int j = 0; j < w; ++j) {
	  next = (pointer.x+j)%width;
	  cells[c][down][next] = queenP[i][j];
	}
	next = pointer.x;
	down = pointer.y;
      }
    break;
    case GALAXY:                        //Kok's Galaxy
      h = galaxyH;
      w = galaxyW;
      for (i = 0; i < h; ++i) {
	int next;
	int down = (pointer.y+i)%height;
	for (int j = 0; j < w; ++j) {
	  next = (pointer.x+j)%width;
	  cells[c][down][next] = galaxyP[i][j];
	}
	next = pointer.x;
	down = pointer.y;
      }
    break;

    case CROSS:                         //Cross
      h = crossH;
      w = crossW;
      for (i = 0; i < h; ++i) {
	int next;
	int down = (pointer.y+i)%height;
	for (int j = 0; j < w; ++j) {
	  next = (pointer.x+j)%width;
	  cells[c][down][next] = crossP[i][j];
	}
	next = pointer.x;
	down = pointer.y;
      }
    break;

    case FIGURE:                        //Figure 8
      h = figureH;
      w = figureW;
      for (i = 0; i < h; ++i) {
	int next;
	int down = (pointer.y+i)%height;
	for (int j = 0; j < w; ++j) {
	  next = (pointer.x+j)%width;
	  cells[c][down][next] = figureP[i][j];
	}
	next = pointer.x;
	down = pointer.y;
      }
    break;
    case K5:                           //58P5H1V1
      h = k5H;
      w = k5W;
      for (i = 0; i < h; ++i) {
	int next;
	int down = (pointer.y+i)%height;
	for (int j = 0; j < w; ++j) {
	  next = (pointer.x+j)%width;
	  cells[c][down][next] = k5P[i][j];
	}
	next = pointer.x;
	down = pointer.y;
      }
    break;
  }
}


void printCells() {

  clrscr();

  if (!menu) {
    //Determining pointer characteristics
    int up = (pointer.y % 2 == 0)? 1 : 0;

    //Translating board cells to screen cells
    for (int r = 0; r < height; r+=2) {
      for (int w = 0; w < width; ++w) {
	int r2 = r/2;
	if (cells[c][r][w] && cells[c][r+1][w])
	  screenCells[r2][w] = BOTH;
	else if (cells[c][r][w] && !cells[c][r+1][w])
	  screenCells[r2][w] = TOPC;
	else if (!cells[c][r][w] && cells[c][r+1][w])
	  screenCells[r2][w] = BTMC;
	else screenCells[r2][w] = NONE;

	//Placing pointer on the screen and hiding when board is just edited
	if (!pointer.justEdited && (pointer.y==r || pointer.y==r+1) && pointer.x==w) {

	  //Non-overlapping cell and pointer on same screen cell
	  if ((up && screenCells[r2][w] == BTMC) ||
	     (!up && screenCells[r2][w] == TOPC))
	    screenCells[r2][w] = BOTH;

	  //Overlapping cell and pointer in same screen cell
	  else if ((up && screenCells[r2][w] == TOPC) ||
	     (!up && screenCells[r2][w] == BTMC))
	    screenCells[r2][w] = NONE;

	  //Two cells and the pointer in the same screen cell
	  else if (screenCells[r2][w] == BOTH)
	    if (up) screenCells[r2][w] = BTMC;
	    else screenCells[r2][w] = TOPC;

	  //Only pointer in the screen cell
	  else if (screenCells[r2][w] == NONE)
	    if (up) screenCells[r2][w] = TOPC;
	    else screenCells[r2][w] = BTMC;
	}
      }
    }
  }
  //If a menu is active, that menu is printed
  else screenMenu();

  //Printing Header
  textbackground(7);
  textcolor(RED);
  cprintf("  ");
  cprintf("%c ", MENU);
  if (menu) textbackground(3);
  cprintf(" M");
  textcolor(BLACK);
  cprintf("enu ");                           //Menu
  textbackground(7);
  cprintf("                  ");
  textcolor(0);
  textbackground(14);                        //Title
  if (!menu) {
    if (conway)
      cprintf("  Conway's Game of Life  ");
    else
      cprintf(" Wolfram's Elementary CA ");
  }
  else if (menu == ABOUT) cprintf("    Cellular Automata    ");
  else if (menu == MENU1) cprintf("        Main Menu        ");
  else if (menu == HELPM) cprintf("     Program Controls    ");
  else if (menu == MENUW) cprintf("    Enter Wolfram Rule   ");
  else if (menu == MENUC) cprintf("Load Conway Configuration");
  textbackground(7);
  cprintf("                     E");        //Exit
  textcolor(RED);
  cprintf("x");
  textcolor(BLACK);
  cprintf("it  ");
  textbackground(BLACK);
  textcolor(7);

  //Printing screen and the box
  for (int h = -1; h <= heightS; ++h)
    for (int w = -1; w <= width; ++w) {
      if (h==-1) {
	if (w==-1)  cout << TOPLC;
	else if (w==width) cout << TOPRC;
	else cout << HORIB;
      }
      else if (h==heightS) {
	if (w==-1)  cout << BTMLC;
	else if (w==width) cout << BTMRC;
	else cout << HORIB;
      }
      else if (w==-1 || w==width) cout << VERTB;
      else cout << screenCells[h][w];
  }

  //Printing footer
  cout << "  Generation: " << setw(6) << generations;
  if (conway && !menu)
    cout << "                     ";
  else if (!menu)
    cout << "            Rule: " << setw(3) << ruleD;

  if (!menu) {
    //Printing Conway CA controls
    if (conway)
      cout << "                   W " << (char) 30 <<"  A "
	   << ((char) 17) << "  S " << ((char) 31) << "  D "
	   << ((char) 16) << " ";

    //Printing  Wolfram CA controls
    else
      cout << "                              A " << (char) 17 <<"  D "
	   << ((char) 16);
  }
  else if (menu == MENUW) {
    cout << "\tRule: ";      //Printing the rule for input if
  }                          //Wolfram Menu is active
}


//Returns number of Moore neighbours of a cell
int getMooreNeighbours(int c1, int h, int w) {

  int left  = ((w <= 0)? width-1 : w-1);        //Boundary wrapping
  int right = ((w >= width-1)? 0 : w+1);
  int top   = ((h <= 0)? height-1: h-1);
  int bottm = ((h >= height-1)? 0 : h+1);

  return (cells[c1][top][left] + cells[c1][top][w] + cells[c1][top][right] +
	  cells[c1][h][left] + cells[c1][h][right] +
	  cells[c1][bottm][left] + cells[c1][bottm][w] + cells[c1][bottm][right]);
}


//Converts decimal Wolfram rule to its binary equivalent
void ruleD_B() {
  int D = ruleD;
  for (int i = 7; i >= 0; --i) {
    if (pow(2,i) <= D) {
      D -= pow(2,i);
      ruleB[i] = 1;
    } else ruleB[i] = 0;
  }
}


void nextConwayGen() {
  int p = c;       //Index of previous board
  c = !c;          //Current board changed
  ++generations;

  //Computing the fate for every cell
  for (int h = 0; h < height; ++h)
    for (int w = 0; w < width; ++w) {
      int num = getMooreNeighbours(p,h,w);       //Getting neighbours

      //John Conway's Rules
      cells[c][h][w]=0;
      if ((cells[p][h][w] && num==2) || (num==3))
	cells[c][h][w] = 1;
    }
}


void nextWolframGen() {
  ++generations;

  //Shifting previous generations up
  for (int r = 0; r < height-1; ++r)
    for (int w = 0; w < width; ++w)
      cells[c][r][w] = cells[c][r+1][w];

  //Computing current generation
  for (int i = 0; i < width; ++i) {
    int row = height-1;
    int left = (i==0)? width-1: i-1;         //Boundary Wrapped
    int right= (i==width-1)? 0: i+1;
    int n = (4*cells[c][row-1][left]) +      //Cell state converted
	    (2*cells[c][row-1][i]) +         //to an index in the binary
	       cells[c][row-1][right];       //rule array.

    //Determining cell state from rule
    cells[c][row][i] = ruleB[n];
  }
}


void main() {
  clrscr();
  //Initializations
  char input = '-';
  pointer.x = width/2;            //Pointer initial locations
  pointer.y = height/2;
  c = pointer.justEdited = 0;
  ruleD_B();
  cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t    Press any key to start";

  //Program exit controller
  while (input != 'x') {

    //Input from user
    if (!justInput) input = tolower(getch());
    else {
      input = '-';         //For smooth exit from Wolfram Menu
      justInput = 0;
    }

    if (!menu) {
      //Displaying board
      switch (input) {
	case 'w':                                       //Up
	  if (conway) {
	    if (--pointer.y < 0) pointer.y = height-1;
	    pointer.justEdited = 0;
	  }
	  break;
	case 'a':                                       //Left
	  if (--pointer.x < 0) pointer.x = width-1;
	  pointer.justEdited = 0;
	  break;
	case 's':
	  if (conway) {                                 //Down
	    if (++pointer.y >= height) pointer.y = 0;
	    pointer.justEdited = 0;
	  }
	  break;
	case 'd':                                       //Right
	  if (++pointer.x >= width) pointer.x = 0;
	  pointer.justEdited = 0;
	  break;
	case 'k':                                       //Cell
	  cells[c][pointer.y][pointer.x] = !cells[c][pointer.y][pointer.x];
	  pointer.justEdited = 1;
	  break;
	case ' ':                                       //Next Generation
	  (conway)? nextConwayGen(): nextWolframGen();
	  break;
	case 'c':                                       //Clear Board
	  initializeCells();
	  break;
	case 'm':                                       //Display Menu 1
	  menu = MENU1;
	  break;
      }
    }
    //Displaying Menu 1
    else if (menu == MENU1) {
	switch (input) {
	  case 'm':                              //Exit Menu
	    menu = NOMENU;
	    break;
	  case '1':                              //Change CA
	    conway = !conway;
	    menu = NOMENU;
	    initializeCells();
	    pointer.y = height-1;
	    break;
	  case '2':                              //Enter Conway pattern
	    menu = MENUC;
	    break;
	  case '3':                              //Enter Wolfram Rule
	    menu = MENUW;
	    break;
	  case '5':                              //Help Menu
	    menu = HELPM;
	    break;
	  case '4':                              //About CA
	    menu = ABOUT;
	    break;
	}
    }
    //Displaying Conway Menu
    else if (menu == MENUC) {
      switch(input) {
	case 'm':                                //Exit menu
	  menu = MENU1;
	  break;
	case '1':                                //Load Gosper Glider Gun
	  load(GOSPER);
	  break;
	case '2':                                //Load Weekender
	  load(WEEK);
	  break;
	case '3':                                //Load Queen Bee Shutler
	  load(QUEEN);
	  break;
	case '4':                                //Load Figure 8
	  load(FIGURE);
	  break;
	case '5':                                //Load Kok's Galaxy
	  load(GALAXY);
	  break;
	case '6':                                //Load Cross
	  load(CROSS);
	  break;
	case '7':                                //Load 58P5H1V1
	  load(K5);
	  break;
      }
    }
    //Controlling other menu's exit
    else {
      if (input == 'm')
	menu = MENU1;
    }
    //Printing the screen
    printCells();

    //Input for Wolfram Rule
    if (menu == MENUW) {
      cin >> ruleD;
      menu = NOMENU;                    //Menu exit
      justInput = 1;
      conway = 0;                       //Wolfram Actived
      initializeCells();                //Board Initialized
      pointer.y = height-1;             //Pointer relocated
      if (ruleD < 0)   ruleD = -ruleD;  //Error Check
      if (ruleD > 256) ruleD %= 256;
      ruleD_B();                        //Decimal Rule to Binary
    }
  }
}