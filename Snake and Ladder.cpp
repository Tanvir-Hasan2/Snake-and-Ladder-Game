#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <graphics.h>
#include <string.h>
#include <process.h>
#include<dos.h>
// path for graphics drivers
#define PATH "..\\bgi"

//
void down(int p);
//To get the position of mouse cordinates
void getpos(int sx,int sy,int b);
//used for drawing window of main board
void windo1();
  // ladder position cells
  int ladder[5][2]={{10,28},{17,37},{32,62},{45,84},{78,97}};
  // snake position cells
  int snake[5][2]={{34,16},{44,21},{68,47},{79,60},{95,73}};
  // for storung dice values single/ double mode
  int one_dice=0,prev1_dice=0,prev2_dice=0,sec_dice=0;
  // void pointer for memmory allocation
  void *d1,*d2;

  unsigned int sd1,sd2;
  // mouse interrupts functions and libraries
		union REGS i,o;
		void initmouse() // initinlizing mouse functions and drivers
		{
			i.x.ax=0;
			int86(0x33,&i,&o);//raising interrupts
		}
		void showmouseptr()// interrupts for showing mouse pointer
		{
			i.x.ax=1;
			int86(0x33,&i,&o);
		}
		void hidemouseptr() // interrupts for hiding mouse pointer
		{
			i.x.ax=2;
			int86(0x33,&i,&o);
		}
		//interrupts to get mouse pointer positions which is read from registers
		void getmousepos(int *button,int *x,int *y)
		{
			i.x.ax=3;
			int86(0x33,&i,&o);

			*button=o.x.bx;
			*x=o.x.cx;
			*y=o.x.dx;
		}
		// restrict mouse pointer in a rectangle area,,
		void restrictmouseptr(int x1,int y1,int x2,int y2)
		{
			i.x.ax=7;
			i.x.cx=x1;
			i.x.dx=x2;
			int86(0x33,&i,&o);
			i.x.ax=8;
			i.x.cx=y1;
			i.x.dx=y2;
			int86(0x33,&i,&o);
		}


// used for drawing outline for button to make up effect
void up(int x,int y,int w,int z)
      {
      setcolor(7);
      line(x,y,w,y);
      line(x,y,x,z);
      setcolor(0);
      line(w,y,w,z);
      line(x,z,w,z);
      }
// used for drawing outline for button to make down effect
void dow(int x,int y,int w,int z)
      {
      setcolor(0);
      line(x,y,w,y);
      line(x,y,x,z);
      setcolor(7);
      line(w,y,w,z);
      line(x,z,w,z);
     }
// function for creating button with color
void bcreate(int x,int y,int w,int z,int col)
      {

	setcolor(7);
	rectangle(x,y,w,z);
	setcolor(8);
	setfillstyle(SOLID_FILL,8);
	rectangle(x+1,y+1,w,z);
	floodfill(x+5,y+5,8);
	setfillstyle(SOLID_FILL,col);
	bar(x+5,y+5,w-5,z-5);
}

////////////////////////////
// creating main window of Snake and Ladder program
void createwindo(int x,int y,int w,int z,int col)
      {
	setcolor(8);
	rectangle(x,y,w,z);
	setcolor(7);
	setfillstyle(SOLID_FILL,8);
	rectangle(x+1,x+1,w-1,z-1);
	floodfill(x+3,y+3,7);
	setcolor(7);
	setfillstyle(SOLID_FILL,col);
	rectangle(x+30,y+30,w-20,z-20);
	floodfill(x+32,y+32,7);
	setcolor(BLACK);
	line(x+30,y+30,x+30,z-20);
	line(x+31,y+31,x+31,z-19);
	line(x+30,y+30,w-20,y+30);
	line(x+31,y+31,w-20,y+31);
	setfillstyle(SOLID_FILL,8);
	settextstyle(DEFAULT_FONT,0,1);
	setcolor(0);
	rectangle(249,7,386,22);
	setcolor(15);
	rectangle(250,8,385,21);
	rectangle(248,6,387,23);
	setfillstyle(1,0);
	floodfill(307,13,15);
	outtextxy(260,12,"SNAKE & LADDERS ");
	settextstyle(SMALL_FONT,0,4);
	setcolor(2);

	bcreate(530,53,615,85,15);
	bcreate(530,90,615,111,15);

	bcreate(528,400,614,440,11);
	bcreate(528,348,614,388,11);
	//mode
	bcreate(468,150,562,170,0);
	bcreate(468,175,562,195,0);

	//SCORE
	bcreate(475,290,515,325,0);
	bcreate(550,290,590,325,0);

	settextstyle(0,0,0);
	setcolor(0);
	line(526,220,596,220);
	line(465,239,535,239);
	line(526,220,465,239);
	line(596,220,535,239);
	rectangle(465,239,535,246);
	line(535,246,596,226);
	line(596,220,596,226);

	setfillstyle(5,3);
	floodfill(473,244,0);
	setfillstyle(4,3);
	floodfill(541,240,0);
	setfillstyle(9,11);
	floodfill(524,230,0);
//dice on board
	setcolor(15);
	setfillstyle(1,12);
	rectangle(517,200,549,221);
	bar(518,201,548,220);
	rectangle(507,207,539,228);
	bar(508,208,538,227);
	line(517,200,507,207);
	line(539,208,549,200);
	line(539,228,549,221);
	floodfill(514,205,15);
	floodfill(541,223,15);
	setcolor(12);
	line(548,221,540,221);
	line(517,201,517,206);
	setcolor(0);


	outtextxy(487,264,"SCORE BOARD");
	outtextxy(472,139,"GAME MODE :");
//       /rectangle
	rectangle(458,275,527,328);
	rectangle(534,275,603,328);
	//icon
	setfillstyle(1,4);
	bar(509,363,490,373);
	setfillstyle(1,14);
	bar(509,414,491,424);

	setcolor(15);
	outtextxy(492,304,"0");
	outtextxy(566,304,"0");
	outtextxy(492,157,"Single");
	outtextxy(462,279,"PLAYER-1");
	outtextxy(538,279,"PLAYER-2");

	setcolor(7);
	outtextxy(492,182,"Double");



	setcolor(0);
	outtextxy(536,357,"Player-1");
	outtextxy(536,370,"ROLL DICE");
	outtextxy(536,409,"Player-2");
	outtextxy(536,422,"ROLL DICE");
	outtextxy(541,65,"NEW GAME");
	outtextxy(537,98,"EXIT GAME");

	line(535,366,602,366);
	line(535,418,602,418);
	setcolor(15);
	settextstyle(SMALL_FONT,0,4);
	outtextxy(30,462,"Project Team : Tanvir, Mostary,Ashik..");

}

// drawing board for playing game
void board()
{
int i,j,x=73,y=76;
char cc[3],num=100;
int m=2;

setcolor(15);
setfillstyle(1,2);
bar(61,61,439,439);
setcolor(0);
rectangle(60,60,440,440);
line(98,60,98,440);
line(136,60,136,440);
line(174,60,174,440);
line(212,60,212,440);
line(250,60,250,440);
line(288,60,288,440);
line(326,60,326,440);
line(364,60,364,440);
line(402,60,402,440);

line(60,98,440,98);
line(60,136,440,136);
line(60,174,440,174);
line(60,212,440,212);
line(60,250,440,250);
line(60,288,440,288);
line(60,326,440,326);
line(60,364,440,364);
line(60,402,440,402);
settextstyle(0,0,0);
setcolor(0);
setfillstyle(1,15);
x=73;
y=76;
num=100;
m=2;
// for printing cell number and white cells

for(i=0;i<10;i++)
{

for(j=0;j<10;j++)
{

if(m==2)
{
if(j%2)
floodfill(x,y,0);

}
else
{
if(!(j%2))
floodfill(x,y,0);
}

// printing number in graphics mode with  formatted output
sprintf(cc,"%d",num);

num--;
outtextxy(x,y,cc);
x+=38;
}
if(m==3)
m=2;
else

m=3;
x=73;
y+=38;

}
setcolor(1);

//ladder 10->28
line(70,414,147,335);
line(71,414,148,335);
line(86,427,165,344);
line(87,427,166,344);

line(80,405,95,419);
line(80,404,95,418);
line(100,384,116,396);
line(100,383,116,395);
line(118,366,135,376);
line(118,367,135,377);
line(139,344,155,355);
line(139,345,155,356);

//ladder 17->37
line(181,385,186,312);
line(182,385,187,312);
line(209,385,198,314);
line(210,385,199,314);

line(182,377,208,377);
line(183,354,205,353);
line(185,333,202,332);
line(186,319,199,318);

//ladder 32->62
line(369,300,384,194);
line(370,300,385,194);
line(385,302,397,198);
line(386,302,398,198);

line(370,295,387,295);
line(373,276,388,279);
line(376,256,391,260);
line(377,241,392,245);
line(381,222,395,226);
line(383,207,396,209);

//ladder 45->84

line(259,261,303,122);
line(258,261,302,122);
line(273,261,313,123);
line(272,261,312,123);

line(262,254,275,254);
line(266,237,280,238);
line(272,218,285,221);
line(277,202,289,204);
line(283,185,295,187);
line(288,168,300,167);
line(294,148,305,149);
line(299,131,310,131);

//ladder 78->97

line(150,147,187,87);
line(151,147,188,87);
line(165,152,199,87);
line(166,152,200,87);

line(153,141,170,144);
line(163,128,178,128);
line(174,109,188,109);
line(185,92,196,95);

///////snakes
setfillstyle(9,5);
setcolor(1);
fillellipse(242,382,2,2);
fillellipse(246,379,2,2);
fillellipse(247,379,2,2);
fillellipse(249,378,2,2);
fillellipse(252,375,2,2);
fillellipse(251,370,2,2);
fillellipse(250,365,2,2);
fillellipse(248,354,3,2);
fillellipse(248,362,3,2);
fillellipse(245,358,3,2);
fillellipse(252,351,3,2);
fillellipse(261,351,3,2);
fillellipse(266,353,3,2);
fillellipse(284,348,3,2);
fillellipse(288,340,3,2);
fillellipse(275,351,3,2);
fillellipse(285,336,3,2);
fillellipse(283,329,3,2);
fillellipse(284,319,3,2);
fillellipse(287,317,3,2);
fillellipse(257,350,3,2);
fillellipse(270,352,3,2);
fillellipse(281,350,3,2);
fillellipse(286,345,2,2);
fillellipse(285,333,2,2);
fillellipse(283,323,2,2);
fillellipse(291,316,2,2);
fillellipse(295,316,2,2);

//head fillellipse(299,313,3,2);

//snake 21->
fillellipse(420,358,3,2);
fillellipse(415,357,3,2);
fillellipse(404,350,3,2);
fillellipse(398,343,3,2);
fillellipse(392,335,3,2);
fillellipse(374,319,3,2);
fillellipse(362,315,3,2);
fillellipse(346,317,3,2);
fillellipse(333,313,3,2);
fillellipse(325,304,3,2);
fillellipse(319,293,3,2);
fillellipse(315,284,3,2);
fillellipse(316,289,3,2);
fillellipse(315,280,3,2);
fillellipse(321,298,3,2);
fillellipse(327,308,3,2);
fillellipse(323,301,3,2);

fillellipse(330,311,3,2);
fillellipse(337,315,3,2);
fillellipse(341,317,3,2);
fillellipse(352,317,3,2);
fillellipse(357,316,3,2);
fillellipse(368,313,3,2);
fillellipse(373,315,3,2);
fillellipse(374,323,3,2);
fillellipse(374,326,3,2);
fillellipse(375,330,3,2);
fillellipse(378,334,3,2);
fillellipse(383,334,3,2);
fillellipse(388,335,3,2);
fillellipse(393,337,3,2);
fillellipse(397,339,3,2);
fillellipse(399,348,3,2);
fillellipse(408,352,3,2);
fillellipse(411,354,3,2);
//snake 47
fillellipse(155,205,3,2);
fillellipse(158,207,3,2);
fillellipse(162,209,3,2);
fillellipse(170,227,3,2);
fillellipse(169,219,3,2);
fillellipse(169,236,3,2);
fillellipse(169,247,3,2);
fillellipse(173,257,3,2);
fillellipse(181,264,3,2);
fillellipse(175,260,3,2);
fillellipse(165,212,3,2);
fillellipse(168,216,3,2);
fillellipse(171,222,3,2);
fillellipse(170,231,3,2);
fillellipse(170,241,3,2);
fillellipse(172,252,3,2);
fillellipse(178,262,3,2);
fillellipse(184,266,3,2);
//snake 60

fillellipse(86,225,3,2);
fillellipse(90,221,3,2);
fillellipse(95,217,3,2);
fillellipse(101,212,3,2);
fillellipse(105,204,3,2);
fillellipse(106,196,3,2);
fillellipse(106,189,3,2);
fillellipse(106,179,3,2);
fillellipse(109,170,3,2);
fillellipse(112,164,3,2);
fillellipse(109,167,3,2);
fillellipse(107,174,3,2);
fillellipse(106,184,3,2);
fillellipse(106,194,3,2);
fillellipse(105,200,3,2);
fillellipse(103,208,3,2);
fillellipse(98,215,3,2);
fillellipse(92,219,3,2);
fillellipse(88,222,3,2);
//snake 73->94
fillellipse(285,87,3,2);
fillellipse(289,89,3,2);
fillellipse(295,91,3,2);
fillellipse(300,97,3,2);
fillellipse(305,104,3,2);
fillellipse(311,109,3,2);
fillellipse(320,113,3,2);
fillellipse(330,117,3,2);
fillellipse(338,122,3,2);
fillellipse(342,127,3,2);
fillellipse(345,132,3,2);
fillellipse(347,138,3,2);
fillellipse(350,142,3,2);
fillellipse(350,145,3,2);
fillellipse(298,93,3,2);
fillellipse(302,101,3,2);
fillellipse(307,107,3,2);
fillellipse(315,113,3,2);
fillellipse(325,112,3,2);
fillellipse(334,119,3,2);
fillellipse(340,125,3,2);
fillellipse(328,114,3,2);
//heads...
setfillstyle(6,14);
setcolor(0);
fillellipse(299,312,4,3);
fillellipse(314,276,4,3);
fillellipse(152,202,4,3);
fillellipse(116,161,4,3);
fillellipse(280,84,4,3);
//player button





}

// splash screen
void splash()
{
int j,t,sx,sy,b,nex,star;
char dd[15];
setfillstyle(1,15);
bar(105,105,getmaxx()-125,getmaxy()-105);
setfillstyle(1,10);
bar(105,105,195,getmaxy()-105);
setcolor(0);
rectangle(106,106,getmaxx()-126,getmaxy()-106);
setfillstyle(1,12);
setcolor(0);
rectangle(245,145,290,190);
rectangle(266,166,310,210);
line(245,145,266,166);
line(245,190,266,210);
line(290,145,310,166);
floodfill(261,196,0);
floodfill(296,159,0);
bar(245,145,290,190);
bar(266,166,310,210);
// drawing dice
rectangle(266,166,310,210);
line(245,145,266,166);
line(245,190,266,210);
line(290,145,310,166);
line(245,145,290,145);
line(245,145,245,190);
line(310,210,331,182);
line(331,182,310,182);
setfillstyle(1,7);
setcolor(7);
floodfill(315,195,0);
line(310,210,331,182);
line(331,182,311,182);

setfillstyle(5,14);
fillellipse(275,259,2,2);
setcolor(12);
setfillstyle(1,15);
fillellipse(275,176,4,4);
fillellipse(299,176,4,4);
fillellipse(275,199,4,4);
fillellipse(299,199,4,4);
fillellipse(287,187,4,4);
fillellipse(252,160,3,4);
fillellipse(261,197,3,4);
fillellipse(256,179,3,4);
fillellipse(262,150,4,3);
fillellipse(284,150,4,3);
fillellipse(273,160,4,3);
fillellipse(296,160,4,3);

// drawing big snake body

setcolor(0);

moveto(338,239);
lineto(325,238);
lineto(314,233);
lineto(301,229);
lineto(293,227);
lineto(285,229);
lineto(277,234);
lineto(275,237);
lineto(278,245);
lineto(270,249);
lineto(259,250);
lineto(254,252);
lineto(253,258);
lineto(255,264);
lineto(260,268);
lineto(264,272);
lineto(270,274);
lineto(280,276);
lineto(292,275);
lineto(304,272);
lineto(316,270);
lineto(322,271);
lineto(325,275);
lineto(323,283);
lineto(320,290);
lineto(307,314);
lineto(299,321);
lineto(295,322);
lineto(294,321);
lineto(301,313);
lineto(306,301);
moveto(308,306);
lineto(304,300);
lineto(295,297);
lineto(283,298);
lineto(268,304);
lineto(272,300);
lineto(286,294);
lineto(300,292);
lineto(309,289);
lineto(314,281);
lineto(319,275);
moveto(298,273);
lineto(301,276);
lineto(309,276);
lineto(312,278);
lineto(308,285);
lineto(306,290);
moveto(302,299);
lineto(301,308);
lineto(289,322);
lineto(291,327);
lineto(303,326);
lineto(313,316);
lineto(321,301);
lineto(329,287);
lineto(338,281);
moveto(284,276);
lineto(274,273);
lineto(268,270);
lineto(264,264);
lineto(261,260);

lineto(257,259);
lineto(253,259);
moveto(282,248);
lineto(287,251);
lineto(294,255);
lineto(304,258);
lineto(310,255);
lineto(315,249);
lineto(315,245);
lineto(310,241);
lineto(304,241);
lineto(298,245);
lineto(294,247);
lineto(288,249);
lineto(282,247);

ellipse(304,248,0,360,4,4);
moveto(321,244);
lineto(314,237);
lineto(307,234);
lineto(301,236);
lineto(294,241);
lineto(288,244);
moveto(280,262);
lineto(281,257);
lineto(278,254);
lineto(273,254);
lineto(270,257);
ellipse(275,259,0,360,3,3);
moveto(297,230);
lineto(290,231);
lineto(284,233);
lineto(279,237);
lineto(282,242);
moveto(273,276);
lineto(277,284);
lineto(284,290);
lineto(280,281);
lineto(281,276);
moveto(263,272);
lineto(264,280);
lineto(270,288);
lineto(267,278);
lineto(268,274);
moveto(329,287);
lineto(332,280);
lineto(336,272);
lineto(333,267);
moveto(338,267);
lineto(379,265);
lineto(415,265);
lineto(442,260);
lineto(459,255);
lineto(478,247);
lineto(483,239);
moveto(334,284);
lineto(388,279);
lineto(457,265);
lineto(479,254);
lineto(485,240);
lineto(486,219);
lineto(480,206);
lineto(451,175);
lineto(410,155);
lineto(381,142);
lineto(380,133);
lineto(392,128);
lineto(421,119);
lineto(446,111);
lineto(467,107);
moveto(335,239);
lineto(361,240);
lineto(404,242);
lineto(425,241);
lineto(438,239);
lineto(447,235);
lineto(455,229);
lineto(457,225);
lineto(456,221);
lineto(449,212);
lineto(409,186);
lineto(369,168);
lineto(353,150);
lineto(355,128);
lineto(364,118);
lineto(381,109);
lineto(388,106);
moveto(334,239);
lineto(340,244);
lineto(340,253);
lineto(388,253);
lineto(387,247);
lineto(382,241);
moveto(407,242);
lineto(413,247);
lineto(416,255);
lineto(442,250);
lineto(460,242);
lineto(474,232);
lineto(479,220);
lineto(475,207);
lineto(466,196);
lineto(458,197);
lineto(451,202);
lineto(458,209);
lineto(461,216);
lineto(459,224);
lineto(452,231);
moveto(456,181);
lineto(449,184);
lineto(445,191);
lineto(416,171);
lineto(397,164);
lineto(398,157);
lineto(408,154);
moveto(403,107);
lineto(406,112);
lineto(402,117);
lineto(383,119);
lineto(373,125);
lineto(370,133);
lineto(372,143);
lineto(382,151);
lineto(375,153);
lineto(371,158);
lineto(360,151);
lineto(357,140);
lineto(359,124);
// filling color for snke after drawig outline....


setfillstyle(9,2);
floodfill(398,254,0);

setfillstyle(1,4);
floodfill(314,290,0);

setfillstyle(9,14);
floodfill(366,248,0);
floodfill(439,245,0);
floodfill(420,166,0);
floodfill(365,133,0);

setfillstyle(6,0);
floodfill(262,266,0);

setfillstyle(1,9);
floodfill(297,254,0);

setfillstyle(1,12);
floodfill(304,248,0);
setcolor(0);
setfillstyle(1,15);
fillellipse(304,248,2,2);

settextstyle(0,0,2);
setcolor(2);
outtextxy(116,129,"S");
outtextxy(116,149,"N");
outtextxy(116,169,"A");
outtextxy(116,189,"K");
outtextxy(116,209,"E");
outtextxy(116,229,"S");

outtextxy(141,217,"&");
outtextxy(169,221,"L");
outtextxy(169,241,"A");
outtextxy(169,261,"D");
outtextxy(169,281,"D");
outtextxy(169,301,"E");
outtextxy(169,321,"R");
outtextxy(169,341,"S");
setcolor(0);
outtextxy(114,128,"S");
outtextxy(114,148,"N");
outtextxy(114,168,"A");
outtextxy(114,188,"K");
outtextxy(114,208,"E");
outtextxy(114,228,"S");

outtextxy(140,215,"&");
outtextxy(167,220,"L");
outtextxy(167,240,"A");
outtextxy(167,260,"D");
outtextxy(167,280,"D");
outtextxy(167,300,"E");
outtextxy(167,320,"R");
outtextxy(167,340,"S");
settextstyle(0,0,0);
setcolor(7);
outtextxy(203,137,"THE UPS AND DOWN");
outtextxy(259,218,"OF VIRTUAL LIFE..");

   setcolor(0);
   outtextxy(201,135,"THE UPS AND DOWN");
   outtextxy(257,216,"OF VIRTUAL LIFE..");

   settextstyle(2,0,3);
   settextstyle(2,0,0);
   setcolor(0);
   outtextxy(138,122,"'Dr.Md.Abir Hossain'");
   setcolor(8);
   outtextxy(108,352,"Project Team:   Tanvir, Mostary,Ashik");
   setcolor(0);
   line(138,134,193,134);
   line(138,136,193,136);
   outtextxy(119,110,"Idea from");
   outtextxy(187,344,"1.0");
setcolor(1);
setfillstyle(1,9);
//ladder

bar(392,127,400,241);
bar(392,278,400,359);

bar(448,110,456,229);
bar(448,266,456,350);

bar(397,137,448,142);
bar(397,176,448,181);
bar(397,216,448,221);
bar(397,286,448,291);
bar(397,337,448,342);

setfillstyle(1,1);
bar(392,127,398,241);
bar(392,278,398,361);

bar(448,110,454,231);
bar(448,266,454,352);

bar(397,137,448,140);
bar(397,176,448,179);
bar(397,216,448,219);
bar(397,286,448,289);
bar(397,337,448,340);

setfillstyle(6,10);
bar(337,269,348,280);
bar(351,269,359,280);
bar(362,269,370,278);
bar(373,268,380,277);
bar(383,268,391,276);
bar(393,267,400,275);
bar(403,267,410,272);
bar(413,267,421,271);
bar(424,266,430,269);
bar(433,264,441,266);
bar(443,262,451,264);
bar(452,259,460,262);
bar(462,256,467,258);
bar(468,253,474,255);
bar(476,248,480,251);
setcolor(0);
rectangle(223,364,380,369);
setfillstyle(1,0);
//progress bar
  nex=224;
  star=2;
 for(j=10,t=10;j<49;)
  {
  t++;
  j++;
   bar(nex,365,nex+star,368);
   nex+=star;
   nex+=2;
  delay(190);

 }
}



// move dice in board to next cell
  void move(int x,int y,int sel)
  {
  if(sel==1)
   {
	setfillstyle(1,4);
	setcolor(14);
	rectangle(x-1,y-1,x+10,y+10);

   }
  else
  {
	setfillstyle(1,14);
	setcolor(12);
	rectangle(x-1,y-1,x+10,y+10);

  }
	bar(x,y,x+9,y+9);

  }

//change position of dice in board
void changeposition(int num,int player)
{
       num--;
       if(player==1)
       move(417-(num%10*38),427-(num/10*38),1);
       if(player==2)
       move(417-(num%10*38),405-(num/10*38),2);
}

// save image portion before any paint function
void saveimageportion(int num,int player)
{


  if(player==1)
   {
    sd1=imagesize(416-(num%10*38),426-(num/10*38),(417-(num%10*38))+10,(427-(num/10*38))+10);
    d1 = malloc(sd1);
    getimage(416-(num%10*38),426-(num/10*38),(417-(num%10*38))+10,(427-(num/10*38))+10,d1);
   }

  if(player==2)
    {

     sd2=imagesize(416-(num%10*38),404-(num/10*38),(417-(num%10*38))+10,(407-(num/10*38))+10);
     d2 = malloc(sd2);
     getimage(416-(num%10*38),404-(num/10*38),(417-(num%10*38))+10,(407-(num/10*38))+10,d2);

    }

}

// restore save image to correct location
void putimageportion(int num,int player)
{

  if(player==1)
   {
    putimage(416-(num%10*38),426-(num/10*38),d1,0);
   }

  if(player==2)
    {
     putimage(416-(num%10*38),404-(num/10*38),d2,0);
    }


}

// drawing dice after playing
void dicerun(int num)
{
    setcolor(12);
    setfillstyle(1,12);
    bar(508,209,537,226);
    setcolor(15);
    setfillstyle(1,15);

    if(num==1)
    fillellipse(522,217,3,1);

    if(num==2)
    {
	fillellipse(511,211,3,1);
	fillellipse(533,224,3,1);
    }

    if(num==3)
    {
    fillellipse(511,211,3,1);
    fillellipse(533,224,3,1);
    fillellipse(522,217,3,1);

    }
    if(num==4)
    {
    fillellipse(511,211,3,1);
    fillellipse(511,224,3,1);
    fillellipse(533,211,3,1);
    fillellipse(533,224,3,1);

    }
    if(num==5)
    {
    fillellipse(511,211,3,1);
    fillellipse(511,224,3,1);
    fillellipse(533,211,3,1);
    fillellipse(533,224,3,1);
    fillellipse(522,217,3,1);

    }
    if(num==6)
    {
    fillellipse(511,211,3,1);
    fillellipse(511,217,3,1);
    fillellipse(511,224,3,1);
    fillellipse(533,211,3,1);
    fillellipse(533,217,3,1);
    fillellipse(533,224,3,1);
    }

}


void loading (){
      cleardevice();

	settextstyle(1,0,3);
	setcolor(5);
	outtextxy(130,200,"WELCOM TO GAMING ZONE");
	setcolor(4);
	outtextxy(200,400-30,"LOADING....");
	setcolor(GREEN);
	for(int i=0;i<290;++i)
	{
		setfillstyle(1,3);
		bar3d(110+i,350-30,400,380-30,10,1);
		delay(10);
	}
      	cleardevice();


}

void front_page()
{


	setcolor(RED);
	setfillstyle(1,0);
	bar3d(70,45,500,90,10,1);
	setcolor(3);
	settextstyle(1,0,3);
	int yy=30;
	outtextxy(200,140-yy,"PRESENTED BY ");
	outtextxy(120,52,"   C++ GRAPHICS PROJECT  ");
	setcolor(GREEN);
	settextstyle(1,0,2);
	outtextxy(50,200-yy,"TANVIR HASAN");
	outtextxy(50,250-yy-20,"IT-20038");
	outtextxy(50,300-yy-40,"1st Year 2nd Semester");

	outtextxy(350,200-yy,"Mst.MOSTARY KHATUN");
	outtextxy(350,250-yy-20,"IT-20036");
	outtextxy(350,230,"1st Year 2nd Semester");

	setcolor(CYAN);
	outtextxy(150,270,"SUPERVISED BY:");
	setcolor(GREEN);
	outtextxy(150,300,"Dr.Md.ABIR HOSSAIN");
	outtextxy(150,330,"ASSOCIATE  PROFESSOR");
	outtextxy(150,360,"Dept. Of ICT");

	setcolor(CYAN);
	settextstyle(1,0,3);

	//----------------
	outtextxy(10,400,"Mawlana Bhashani Science And Technology University");
	setcolor(3);
	setcolor(RED);
	outtextxy(150,440,"Press Any Key To continue");

	getch();

}



// main function...

void main()
{       // detect graphics driver and graphics mode....
	int gd=DETECT,gm;
	int i,j,b,sx,sy,z,col,x1,y1,w1,z1;
	char dd[20],dc[5];
	int num;
	int dice=0,k,l,chance=1,selemode=1,end=0;
	int one_dice=0,prev1_dice=0,prev2_dice=0,sec_dice=0;

	void *d1,*d2,*result;
	unsigned int sd1,sd2,resarea;
	// initilizing mouse functions
	initmouse();
	// these libraries for making stand alon program by inserting
	// graphics libraries,, so no need to put the BGI path in the program
	//The program will work without graphics driver in the system..
	// for all steps refere document inside TC\DOC

/*	registerfarbgidriver(EGAVGA_driver_far);
	registerfarbgifont(sansserif_font_far);
	registerfarbgifont(triplex_font_far);
	registerfarbgifont(small_font_far);
	initgraph(&gd,&gm,NULL);
*/
	// initilizing graphics driver
	initgraph(&gd,&gm,PATH);

	front_page();
	loading();

	// getting maximum x and y size of active or current display mode
	w1=getmaxx(),z1=getmaxy();
	x1=0;
	y1=0;

	// drawing splash screen
	splash();
	// clearing display device and its memory for main window drawing
	cleardevice();
	// drawing snake and ladder game outline window
	createwindo(x1,y1,w1,z1,9);
	// drawing game board cells for playing
	board();
	// showing mouse pointer after drwaing all graphics windows
	showmouseptr();

/* main loop and only one infinite loop for the program to run every time
 for getting input from the devices.. this loop will be exited
 when the "Exit" button is clicked.
 */

while(1)
{


	// this was used to get the mouse position every time to
	// identify the current position of mouse for each functions
	// mouse cordinates was stored in sx and sy variables..

	getmousepos(&b,&sx,&sy);
	// used to give action for single nd double button clicked actions
	// and selemode variable is set
	// single

	// b variable is used for checking buton status..
	// b=1 left button clicked
	if(b==1&&sx>468&&sy>150&&sx<562&&sy<170)
	{
	settextstyle(0,0,0);
	hidemouseptr();
	setcolor(7);
	outtextxy(492,182,"Double");
	setcolor(15);
	outtextxy(492,157,"Single");
	showmouseptr();
	selemode=1;
	end=0;
	 one_dice=0;
	 sec_dice=0;
	 putimageportion(prev1_dice,1);
	 putimageportion(prev2_dice,2);
	 chance=1;
	setcolor(15);
	rectangle(528,348,614,388);
	setcolor(9);
	rectangle(528,400,614,440);
	setcolor(0);
	outtextxy(484,304,"ллл");
	outtextxy(556,304,"ллл");
	setcolor(15);
	outtextxy(484,304,"0");
	outtextxy(558,304,"0");
    setcolor(12);
    setfillstyle(1,12);
    bar(508,209,537,226);
	}
// double
	if(b==1&&sx>468&&sy>175&&sx<562&&sy<195)
	{
	hidemouseptr();
	setcolor(15);
	outtextxy(492,182,"Double");
	setcolor(7);
	outtextxy(492,157,"Single");
	showmouseptr();
	selemode=2;
	end=0;
	 one_dice=0;
	 sec_dice=0;
	 putimageportion(prev1_dice,1);
	 putimageportion(prev2_dice,2);
	 chance=1;
	setcolor(15);
	rectangle(528,348,614,388);
	setcolor(9);
	rectangle(528,400,614,440);
	setcolor(0);
	outtextxy(484,304,"ллл");
	outtextxy(556,304,"ллл");
	setcolor(15);
	outtextxy(484,304,"0");
	outtextxy(558,304,"0");
    setcolor(12);
    setfillstyle(1,12);
    bar(508,209,537,226);
	}

	if(b==1&&sx>530&&sy>53&&sx<615&&sy<85)
	{
	settextstyle(0,0,0);
	end=0;
	 one_dice=0;
	 sec_dice=0;
	 putimageportion(prev1_dice,1);
	 putimageportion(prev2_dice,2);
	 chance=1;
	setcolor(15);
	rectangle(528,348,614,388);
	setcolor(9);
	rectangle(528,400,614,440);
	setcolor(0);
	outtextxy(484,304,"ллл");
	outtextxy(556,304,"ллл");
	setcolor(15);
	outtextxy(484,304,"0");
	outtextxy(558,304,"0");
    setcolor(12);
    setfillstyle(1,12);
    bar(508,209,537,226);

	}

	if(b==1)
	{
///////////////////////////////////////////////////////

	if(end==0&&chance==1&&b==1&&sx>528&&sy>348&&sx<614&&sy<388)
	{

	//  player 1	bcreate(528,348,614,388,11);

	//loop runs contnously when mouse button was pressed and stops
	//when mouse button is released..

	dice=0;

	while(b==1)
	{
	getmousepos(&b,&sx,&sy);
	dice++;
	if(dice==7)
	dice=1;
	}
	dicerun(dice);
	// hiding mouse and waiting for one more chance / click when dice = 6

	hidemouseptr();
	if(dice==6)
	{
	setcolor(15);
	rectangle(528,348,614,388);
	setcolor(9);
	rectangle(528,400,614,440);
	chance=1;
	}
	else
	{
	setcolor(9);
	rectangle(528,348,614,388);
	setcolor(15);
	rectangle(528,400,614,440);
	chance=2;
	}
	// show mouse pointer
	showmouseptr();
	one_dice+=dice;

	for(i=0;i<5;i++)
	for(j=0;j<1;j++)
	{
	 if(ladder[i][j]==one_dice)
	  one_dice=ladder[i][1];
	 if(snake[i][j]==one_dice)
	  one_dice=snake[i][1];

	}
	sound(400);
	delay(500);
	nosound();

	if(one_dice<=100)
	{
	num=one_dice;
	num--;
	putimageportion(prev1_dice,1);
	saveimageportion(num,1);
	changeposition(one_dice,1);
	prev1_dice=one_dice-1;
	}
	else
	{
	one_dice-=dice;
	}

	sprintf(dc,"%d",one_dice);

	setcolor(0);
	outtextxy(484,304,"ллл");
	setcolor(15);
	outtextxy(485,304,dc);


	if(one_dice==100)
	{
	end=1;

	hidemouseptr();
	resarea=imagesize(190,170,435,320);
	result=malloc(resarea);
	getimage(190,170,435,320,result);

	setfillstyle(1,0);
	setcolor(15);
	rectangle(190,170,435,320);
	bar(191,171,434,319);
	outtextxy(258,242,"PLAYER 1 WON");
	rectangle(369,272,415,280);
	rectangle(378,261,404,271);
	line(378,261,384,255);
	line(384,255,377,209);
	line(405,209,399,255);
	line(399,255,404,261);
	ellipse(391,209,0,360,14,3);
	setfillstyle(1,8);
	floodfill(391,234,15);
	setfillstyle(1,4);
	floodfill(386,267,15);
	setfillstyle(1,1);
	floodfill(386,276,15);
	setfillstyle(1,7);
	floodfill(391,208,15);
	settextstyle(2,0,0);
	setcolor(14);
	outtextxy(280,303,"press any key to continue..");
	getch();
	putimage(190,170,result,0);
	free(result);
	showmouseptr();
	}
	settextstyle(0,0,0);
	}

//////////////////////////////////////////////////////////////
 // double mode for two player
 if(selemode==2&&end==0&&chance==2&&b==1&&sx>528&&sy>400&&sx<614&&sy<440)
	{

	dice=0;
	while(b==1)
	{
	getmousepos(&b,&sx,&sy);
	dice++;
	if(dice==7)
	dice=1;
	}
	dicerun(dice);

       hidemouseptr();
	if(dice==6)
	{
	setcolor(9);
	rectangle(528,348,614,388);
	setcolor(15);
	rectangle(528,400,614,440);
	chance=2;
	}
	else
	{
	setcolor(15);
	rectangle(528,348,614,388);
	setcolor(9);
	rectangle(528,400,614,440);
	chance=1;
	}

	showmouseptr();
	sec_dice+=dice;

	for(i=0;i<5;i++)
	for(j=0;j<1;j++)
	{
	 if(ladder[i][j]==sec_dice)
	  sec_dice=ladder[i][1];
	 if(snake[i][j]==sec_dice)
	  sec_dice=snake[i][1];

	}
	sound(400);
	delay(500);
	nosound();


	if(sec_dice<=100)
	{
	num=sec_dice;
	num--;
	putimageportion(prev2_dice,2);
	saveimageportion(num,2);
	changeposition(sec_dice,2);
	prev2_dice=sec_dice-1;
	}
	else
	{
	sec_dice-=dice;
	}


	sprintf(dc,"%d",sec_dice);
	setcolor(0);
	outtextxy(556,304,"ллл");
	setcolor(15);
	outtextxy(557,304,dc);


	if(sec_dice==100)
	{
	end=1;
	hidemouseptr();
	resarea=imagesize(190,170,435,320);
	result=malloc(resarea);
	getimage(190,170,435,320,result);

	setfillstyle(1,0);
	setcolor(15);
	rectangle(190,170,435,320);
	bar(191,171,434,319);
	outtextxy(258,242,"PLAYER 2 WON");
	rectangle(369,272,415,280);
	rectangle(378,261,404,271);
	line(378,261,384,255);
	line(384,255,377,209);
	line(405,209,399,255);
	line(399,255,404,261);
	ellipse(391,209,0,360,14,3);
	setfillstyle(1,8);
	floodfill(391,234,15);
	setfillstyle(1,4);
	floodfill(386,267,15);
	setfillstyle(1,1);
	floodfill(386,276,15);
	setfillstyle(1,7);
	floodfill(391,208,15);
	settextstyle(2,0,0);
	setcolor(14);
	outtextxy(280,303,"press any key to continue..");
	getch();
	putimage(190,170,result,0);
	free(result);
	showmouseptr();

	}

	}
//////////////////////////////////////////computer mode play
	else
	if(selemode==1&&end==0&&chance==2)
	{

       // computer mode
	dice=random(6);
	if(dice==0)
	dice=1;
	dicerun(dice);
	hidemouseptr();
	if(dice==6)
	{
	setcolor(9);
	rectangle(528,348,614,388);
	setcolor(15);
	rectangle(528,400,614,440);
	chance=2;
	}
	else
	{
	setcolor(15);
	rectangle(528,348,614,388);
	setcolor(9);
	rectangle(528,400,614,440);
	chance=1;
	}

	showmouseptr();
	sec_dice+=dice;

	for(i=0;i<5;i++)
	for(j=0;j<1;j++)
	{
	 if(ladder[i][j]==sec_dice)
	  sec_dice=ladder[i][1];
	 if(snake[i][j]==sec_dice)
	  sec_dice=snake[i][1];

	}
	sound(200);
	delay(500);
	sound(300);
	delay(200);
	sound(500);
	delay(100);
	nosound();


	if(sec_dice<=100)
	{
	num=sec_dice;
	num--;
	putimageportion(prev2_dice,2);
	saveimageportion(num,2);
	changeposition(sec_dice,2);
	prev2_dice=sec_dice-1;
	}
	else
	{
	sec_dice-=dice;
	}


	sprintf(dc,"%d",sec_dice);
	setcolor(0);
	outtextxy(556,304,"ллл");
	setcolor(15);
	outtextxy(557,304,dc);


	if(sec_dice==100)
	{
	end=1;
		hidemouseptr();
	resarea=imagesize(190,170,435,320);
	result=malloc(resarea);
	getimage(190,170,435,320,result);

	setfillstyle(1,0);
	setcolor(15);
	rectangle(190,170,435,320);
	bar(191,171,434,319);
	outtextxy(258,242,"COMPUTER WON");
	rectangle(369,272,415,280);
	rectangle(378,261,404,271);
	line(378,261,384,255);
	line(384,255,377,209);
	line(405,209,399,255);
	line(399,255,404,261);
	ellipse(391,209,0,360,14,3);
	setfillstyle(1,8);
	floodfill(391,234,15);
	setfillstyle(1,4);
	floodfill(386,267,15);
	setfillstyle(1,1);
	floodfill(386,276,15);
	setfillstyle(1,7);
	floodfill(391,208,15);
	settextstyle(2,0,0);
	setcolor(14);
	outtextxy(280,303,"press any key to continue..");
	getch();
	putimage(190,170,result,0);
	free(result);
	showmouseptr();
	}

	}

////////////////////////////////////////////////////
    }

       // exit button pressed
	if(b==1&&sx>530&&sy>90&&sx<615&&sy<111)
	{
	break;
	}
}

 // close graphics mode
 closegraph();
 // restore to CRT mode  normal text mode
 restorecrtmode();
}

