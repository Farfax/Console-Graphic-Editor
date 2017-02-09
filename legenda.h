#pragma once
class Menu_t
{
	char *names[LEGEND_SIZE] =
	{ "Esc = wyjscie",
		"strzalki=poruszanie",
		"spacja = Bialy/Czarny",
		"i= Domyslny",
		"o= Wczytaj",
		"n= Utworz nowy",
		"s= Zapisz",
		"l= rysowanie lini" ,
		"k=rysowanie prostokata",
		"1234567890qwerty= wybor koloru" ,
		"ctr+strzalki=przewijanie ekranu",
		"Backspace=cofnij", "alt+strzalki= zaznacz",
		"c= kopiuj",
		"p=wklej",
		"f=wypelnij",
		"enter = zmiana koloru tla"
	};
public:
	void Draw()
	{
		textcolor(MENU_COLOR);
		for (int i = 0; i < LEGEND_SIZE - 1; i++)
		{
			gotoxy(LEGEND_POS + Vector2i_t(0, i)); //Go Down to draw another text
			cputs(names[i]);
		}
	}

};