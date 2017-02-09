#pragma once
#include "legenda.h"

class DrawManager_t 		
{
	BasicInfo_t* BasicInfo;
	bool isEmpty;

	void DrawMenu()
	{
		Menu_t Menu;
		Menu.Draw();
	}
	void DrawKeyCode()
	{
		textcolor(MENU_COLOR);
		char txt[32] = "kod klawisza: 0x";

		gotoxy(KEYCODE_POS);

		if (BasicInfo->ArrowIsPressed)
		{
			txt[16] = '0';
			txt[17] = '0';
			txt[18] = ' ';
			txt[19] = '0';
			txt[20] = 'x';
			_itoa(BasicInfo->KeyCode, txt + 21, 16);
		}
		else
			_itoa(BasicInfo->KeyCode, txt + 16, 16);

		BasicInfo->ArrowIsPressed = 0;
		cputs(txt);
	}
	void DrawMode()
	{
		textcolor(MENU_COLOR);
		gotoxy(INFO_MODE_POS);
		switch (BasicInfo->CurrentMode)
		{
		case LineMode:
			cputs("LineDrawing");
			break;

		case RectangleMode:
			if (Clipboard::isCopy == false)
				cputs("RectangleDrawing");
			else
				cputs("CopyMode");
			break;

		default:
			cputs("DefaultMode");
			break;
		}
	}
	void DrawClipboard()
	{
		gotoxy(CAN_PAST_POS);
		if (Clipboard::canPast == true)
			cputs("Mozna Wkleic");
		else
			cputs("Nie Mozna Wkleic");

		char Buffer[255] = { NULL };
		gotoxy(CLIPBOARD_SIZE_POS);
		_itoa(Clipboard::Size.x, Buffer, 10);
		cputs(Buffer);
		cputs(" x ");
		memset(Buffer, NULL, 255);
		_itoa(Clipboard::Size.y, Buffer, 10);
		cputs(Buffer);

		gotoxy(EMPTY_CLIPBOARD_POS);
		if (Clipboard::isEmpty == true)
			cputs("Schowek jest pusty");
		else
			cputs("Schowek jest pelny");
		
	}
	void DrawCursorPos()
	{
		textcolor(MENU_COLOR);
		char txtX[8] = { "X:" };
		char txtY[8] = { "Y:" };

		_itoa(BasicInfo->CursorPos.x, txtX + 2, 10);
		_itoa(BasicInfo->CursorPos.y, txtY + 2, 10);

		gotoxy(CURSOR_INFO_POSX);
		cputs(txtX);

		gotoxy(CURSOR_INFO_POSY);
		cputs(txtY);
	}
	void DrawUndo()
	{
		if (isEmpty == false && BasicInfo->CurrentMode != LineMode && BasicInfo->CurrentMode != RectangleMode) //DrawnObjs.IsEmpty()
		{
			gotoxy(UNDO_STATUS_POS);
			cputs("Undo jest dostepne");
		}
		else
		{
			gotoxy(UNDO_STATUS_POS);
			cputs("Undo nie jest dostepne");
		}
	}
	void DrawFileName()
	{
		gotoxy(FILE_NAME_POS);
		if (FileManager::getFileName() == nullptr)
			cputs("No Name");
		else
			cputs(FileManager::getFileName());
	}
	void DrawCursor()
	{
		textcolor(BasicInfo->DrawColor);
		textbackground(BasicInfo->BackGroundColor);
		gotoxy(BasicInfo->CursorPos);
		putch('*');
	}
	void DrawImageDimension()
	{
		if (Dimension_t::getImageDimension() != nullptr)
			Dimension_t::getImageDimension()->Draw('X', false, false);
	}
	// DrawBookMarks
	void DrawScrolls()
	{
		gotoxy(Scrollbars_t::XBar);
		cputs("=");

		gotoxy(Scrollbars_t::YBar);
		cputs("|");
	}
public:
	DrawManager_t(BasicInfo_t *BasicInfo, bool isEmpty):
		BasicInfo(BasicInfo),
		isEmpty(isEmpty)
	{
		Draw();
	}
	void Draw()
	{
		DrawImageDimension();
		DrawMenu();
		DrawMode();
		DrawUndo();
		DrawKeyCode();
		DrawCursorPos();
		DrawFileName();
		DrawScrolls();
		DrawClipboard();
		DrawCursor();
	}

};
