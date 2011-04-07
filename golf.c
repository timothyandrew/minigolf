//------------------------------------------------------------------------------

#include <graphics.h>
#include <math.h>

//------------------------------------------------------------------------------

const dolek_x = 550;
const dolek_y = 100;
const dolek_r = 10;

//------------------------------------------------------------------------------

struct Punkt
{
	int x;
	int y;
};

//------------------------------------------------------------------------------

int key;

double pilka_x = 30;
double pilka_y = 100;
int pilka_r = 7;
int pilka_polozenie = 1;

int sila = 1;
int kat = 0;

int szybkosc = 3;

//------------------------------------------------------------------------------

int getch_ex(void)
{
	char ch;
	
	ch = getch();
   if (ch == 0)
		ch = getch();
		
	return ch;
}

//------------------------------------------------------------------------------

#define PI 3.14159265

double stopnie2radiany(double stopnie)
{
	return (stopnie * PI / 180);
}

//------------------------------------------------------------------------------

void RysujPoleGolfowe(void)
{
	struct Punkt Punkty[13];
	
	Punkty[ 0].x = 10;
	Punkty[ 0].y = 20;
	Punkty[ 1].x = 300;
	Punkty[ 1].y = 20;
	Punkty[ 2].x = 320;
	Punkty[ 2].y = 60;
	Punkty[ 3].x = 380;
	Punkty[ 3].y = 60;
	Punkty[ 4].x = 460;
	Punkty[ 4].y = 10;
	Punkty[ 5].x = 590;
	Punkty[ 5].y = 10;
	Punkty[ 6].x = 590;
	Punkty[ 6].y = 190;
	Punkty[ 7].x = 460;
	Punkty[ 7].y = 190;
	Punkty[ 8].x = 400;
	Punkty[ 8].y = 140;
	Punkty[ 9].x = 320;
	Punkty[ 9].y = 140;
	Punkty[10].x = 300;
	Punkty[10].y = 180;
	Punkty[11].x = 10;
	Punkty[11].y = 180;
	Punkty[12].x = 10;
	Punkty[12].y = 20;
	
	setcolor(BROWN);
	setfillstyle(SOLID_FILL, BROWN);
	bar(0, 0, 600, 201);
 
	setcolor(GREEN);
	setfillstyle(SOLID_FILL, GREEN);
	fillpoly(13, (int*)Punkty); 
}


//------------------------------------------------------------------------------

void RysujDolek(void)
{
	setcolor(BLACK);
	setfillstyle(SOLID_FILL, BLACK);
	fillellipse(dolek_x, dolek_y, dolek_r, dolek_r); 
}

//------------------------------------------------------------------------------

void RysujPilke(void)
{
	setcolor(WHITE);
	setlinestyle(SOLID_LINE, 0, 1);
	setfillstyle(XHATCH_FILL, WHITE);
	fillellipse(pilka_x, pilka_y, pilka_r, pilka_r); 
}

void WymazPilke(void)
{
	setcolor(GREEN);
	setlinestyle(SOLID_LINE, 0, 1);
	setfillstyle(SOLID_FILL, GREEN);
	fillellipse(pilka_x, pilka_y, pilka_r, pilka_r);
}

//------------------------------------------------------------------------------

void RysujKierunek(void)
{
	setcolor(BLACK);
	setlinestyle(SOLID_LINE, 0, 1);
	moveto(pilka_x, pilka_y);
	lineto(pilka_x + 50*cos(stopnie2radiany(kat)), pilka_y + 50*sin(stopnie2radiany(kat)));
}

void WymazKierunek(void)
{
	setcolor(GREEN);
	setlinestyle(SOLID_LINE, 0, 1);
	moveto(pilka_x, pilka_y);
	lineto(pilka_x + 50*cos(stopnie2radiany(kat)), pilka_y + 50*sin(stopnie2radiany(kat)));
}

//------------------------------------------------------------------------------

void RysujSzybkosc(void)
{
	setcolor(WHITE);
	settextjustify(LEFT_TEXT, CENTER_TEXT);
	switch (szybkosc)
	{
		case 1: outtextxy(10, 15, "Predkosc: wolna"); break;
		case 2: outtextxy(10, 15, "Predkosc: srednia"); break;
		case 3: outtextxy(10, 15, "Predkosc: szybka"); break;
	}
}

void WymazSzybkosc(void)
{
	setcolor(BROWN);
	setlinestyle(SOLID_LINE, 0, 1);
	setfillstyle(SOLID_FILL, BROWN);
	bar(0, 0, 170, 20);	
}

//------------------------------------------------------------------------------

void WybierzPolozeniePilki(void)
{
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	setcolor(WHITE);
	outtextxy(300, 220, "Strzalka w lewo  - polozenie pilki");
	outtextxy(300, 240, "Strzalka w prawo - polozenie_pilki");
	outtextxy(300, 260, "PageUp - szybsza animacja");
	outtextxy(300, 280, "PageDown - wolniejsza animacja");
	outtextxy(300, 300, "ENTER - akceptacja");

	do
	{
		key = getch_ex();
		
		WymazPilke();
		WymazSzybkosc();

		if (key == KEY_LEFT)
			if (pilka_polozenie > 1)
				pilka_polozenie--;	
			else
				pilka_polozenie = 3;
		
		if (key == KEY_RIGHT)
			if (pilka_polozenie < 3)
				pilka_polozenie++;	
			else
				pilka_polozenie = 1;

		if (key == KEY_PGUP)
			if (szybkosc < 3)
				szybkosc++;	

		if (key == KEY_PGDN)
			if (szybkosc > 1)
				szybkosc--;	
			
		switch (pilka_polozenie)
		{
			case 1: 	pilka_x = 30;
						pilka_y = 100;
						break;
			case 2: 	pilka_x = 200;
						pilka_y = 70;
						break;
			case 3: 	pilka_x = 450;
						pilka_y = 150;
						break;
		}
	
		RysujPilke();
		RysujSzybkosc();
	}
	while (key != VK_RETURN);
}

//------------------------------------------------------------------------------

void WybierzKierunekSile(void)
{
	setfillstyle(SOLID_FILL, BLACK);
	bar(0, 202, 600, 320);

	settextjustify(CENTER_TEXT, CENTER_TEXT);
	setcolor(WHITE);
	outtextxy(300, 220, "Strzalka w lewo  - wybor kierunku");
	outtextxy(300, 240, "Strzalka w prawo - wybor kierunku");
	outtextxy(300, 300, "ENTER - uderzenie");

	do
	{
		key = getch_ex();
		
		WymazKierunek();		

		if (key == KEY_LEFT)
			if (kat > -90)
				kat -= 1;	
			else
				kat = 90;

		if (key == KEY_RIGHT)
			if (kat < 90)
				kat += 1;	
			else
				kat = -90;

		RysujPilke();
		RysujKierunek();
	}
	while (key != VK_RETURN);
	WymazKierunek();		
}

//------------------------------------------------------------------------------

bool Trafienie(void)
{
	double OdlegloscDolkaPilki;
	OdlegloscDolkaPilki = sqrt(pow(abs(pilka_x - dolek_x), 2) + pow(abs(pilka_y - dolek_y), 2));
	
	if (OdlegloscDolkaPilki <= (dolek_r - pilka_r))
		return true;
	else
		return false;
}

//------------------------------------------------------------------------------

bool Banda(void)
{
	if ((getpixel(pilka_x + pilka_r + 1, pilka_y) == BROWN) || 
	    (getpixel(pilka_x, pilka_y - pilka_r - 1) == BROWN) ||
	    (getpixel(pilka_x, pilka_y + pilka_r + 1) == BROWN))
		return true;
	else
		return false;
}

//------------------------------------------------------------------------------

void Uderzenie(void)
{
	setfillstyle(SOLID_FILL, BLACK);
	bar(0, 202, 600, 320);
	
	for (int i = 1; i < 200 * szybkosc; i++)
	{
		WymazPilke();

		pilka_x = pilka_x + cos(stopnie2radiany(kat));
		pilka_y = pilka_y + sin(stopnie2radiany(kat));

		RysujDolek();
		RysujPilke();
		
		if (Banda())
		{
			settextjustify(CENTER_TEXT, CENTER_TEXT);
			setcolor(WHITE);
			outtextxy(300, 220, "Banda");
			return;
		}

		if (Trafienie())
		{
			settextjustify(CENTER_TEXT, CENTER_TEXT);
			setcolor(WHITE);
			outtextxy(300, 220, "Trafienie - GRATULACJE");
			return;
		}

		delay(10);
	}
}

//------------------------------------------------------------------------------

void main(void)
{
	initwindow(600, 320);
	
	RysujPoleGolfowe();
	RysujDolek();
	RysujPilke();
	RysujSzybkosc();
	
	WybierzPolozeniePilki();
	RysujKierunek();
	WybierzKierunekSile();
	Uderzenie();
	getch();	
	closegraph();
}

//------------------------------------------------------------------------------

