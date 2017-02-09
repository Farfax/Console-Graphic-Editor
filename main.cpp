#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "conio2.h"

#include "preprocessor.h"
#include "conteners.h"
#include "info.h"
#include "line.h"
#include "rectangle.h"
#include "pasted.h"
#include "filling.h"
#include "scrollbars.h"
#include "dimension.h"
#include "fileManager.h"
#include "clipboard.h"
#include "drawManager.h"
#include "eventHandler.h"

/* Class Scheme 
1)Private Variable

2)Private Methods

3)Constructor
4)Destructor

5)Public Variable

6)Public Methods

7)Operator Overloads
*/

void gotoxy(Vector2i_t Point)
{
	gotoxy(Point.x, Point.y);
}

int main(int argc, char ** argv)
{				

	BasicInfo_t BasicInfo;
	EventHandler_t EventHandler(&BasicInfo);
	DrawManager_t* DrawManager = nullptr;

	if (argc > 1)
		EventHandler.LoadFile(argv[1]);
	do
	{
		textbackground(BLACK);
		clrscr();

		if (EventHandler.DrawnObjs.IsEmpty() == false)
			for (Shapes** objtodraw = (EventHandler.DrawnObjs.begin()); objtodraw != EventHandler.DrawnObjs.rEnd(); objtodraw++)
				(*objtodraw)->Draw();

		DrawManager = new DrawManager_t(&BasicInfo, EventHandler.DrawnObjs.IsEmpty());
		delete DrawManager;
		DrawManager = nullptr;

		BasicInfo.KeyCode = getch();

		EventHandler.LookForEvent();

	} while (BasicInfo.CurrentMode != QuitMode);

	return 0;
}
