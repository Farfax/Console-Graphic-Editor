#pragma once
#include "ArrowController.h"

class EventHandler_t //TODO EventHandler is very fat asshole, divide him up into a few smaller bastards	
{
	BasicInfo_t* BasicInfo;
	Scrollbars_t Bars;
	Clipboard Copies;

	void ChangeDrawColor()
	{
		switch (BasicInfo->KeyCode)
		{
		case '0': //  
			BasicInfo->DrawColor = BLACK;
			break;

		case '1': // 
			BasicInfo->DrawColor = BLUE;
			break;

		case '2': // 
			BasicInfo->DrawColor = GREEN;
			break;

		case '3': // 
			BasicInfo->DrawColor = CYAN;
			break;

		case '4': // 
			BasicInfo->DrawColor = RED;
			break;

		case '5': // 
			BasicInfo->DrawColor = MAGENTA;
			break;

		case '6': // 
			BasicInfo->DrawColor = BROWN;
			break;

		case '7': // 
			BasicInfo->DrawColor = LIGHTGRAY;
			break;

		case '8': // 
			BasicInfo->DrawColor = DARKGRAY;
			break;

		case '9': // 
			BasicInfo->DrawColor = LIGHTBLUE;
			break;

		case 'q': // 
			BasicInfo->DrawColor = LIGHTGREEN;
			break;

		case 'w': // 
			BasicInfo->DrawColor = LIGHTCYAN;
			break;

		case 'e': // 
			BasicInfo->DrawColor = LIGHTRED;
			break;

		case 'r': // 
			BasicInfo->DrawColor = LIGHTMAGENTA;
			break;

		case 't':
			BasicInfo->DrawColor = YELLOW;
			break;

		case 'y':
			BasicInfo->DrawColor = WHITE;
			break;
		}
	}
	void UpdateFrame()
	{
		if (Dimension_t::getImageDimension() == nullptr)
			return;

		Clipboard::CheckPasting(*BasicInfo);	//Let (or not) paste from Clipboard

		if (BasicInfo->CurrentMode == LineMode || BasicInfo->CurrentMode == RectangleMode)
			(*DrawnObjs.end())->DrawToPoint(BasicInfo->CursorPos);								//interactive Drawing
	}	
	void CreateShape()
	{
		if (BasicInfo->CurrentMode == DefaultMode)
		{
			(*DrawnObjs.end())->setColor(BasicInfo->DrawColor);
			(*DrawnObjs.end())->setStart(BasicInfo->CursorPos);
		}
		else if (BasicInfo->CurrentMode == RectangleMode || BasicInfo->CurrentMode == LineMode)
		{
			BasicInfo->CurrentMode = DefaultMode;
			(*DrawnObjs.end())->DrawToPoint(BasicInfo->CursorPos);
			(*DrawnObjs.end())->setVisible(true);
		}
	}
	void QuitFromShapeMode()
	{
		if (BasicInfo->CurrentMode == LineMode || BasicInfo->CurrentMode == RectangleMode)
		{
			delete *(DrawnObjs.end());
			DrawnObjs.Erase();
			BasicInfo->CurrentMode = DefaultMode;
		}
	}
	void QuitFromCopyMode()
	{
		Copies.Quit();
		BasicInfo->CurrentMode = DefaultMode;

	}
	void LoadFile()
	{
		char*  UserName = FileManager::InputText("Wprowadz Nazwe:");

		if (UserName == NULL)	//if UserName is Empty, Back to Menu
		{
			cputs("Plik Nie istnieje");
			return;
		}

		LoadFile(UserName);
	}
	void FileMarks()
	{
		if (FileManager::FileMarks.IsEmpty() == true)
			return;

		FileManager::Save(&DrawnObjs);
		Clean();
		LoadFile(*(FileManager::FileMarks.begin() + BasicInfo->FileMarksCount));

		BasicInfo->FileMarksCount++;
		if (BasicInfo->FileMarksCount == FileManager::FileMarks.Length())
			BasicInfo->FileMarksCount = 0;
	}
	void SaveFile()
	{
		if (FileManager::getFileName() == nullptr || strcmp(FileManager::getFileName(), "No Name") == 0)
			return;

		char*  UserName = FileManager::InputText("Wprowadz Nazwe:");

		if (UserName == NULL)
			if (FileManager::getFileName() == nullptr)		//If Image isn't open and UserName is Empty, Back to Menu
				return;

		if (UserName != NULL)								//If UserName is Empty, use actual FileName
			FileManager::setFileName(UserName);

		FileManager::Save(&DrawnObjs);
		textcolor(BasicInfo->DrawColor);
	}
	void CreateFile()
	{
		char*  UserName = FileManager::InputText("Wprowadz Nazwe:");
		if (UserName == NULL)	//If Width is empty, Back to Menu
			return;

		char* tempSize = FileManager::InputText("Wprowadz Szerokosc:");
		if (tempSize == nullptr)	//If Width is empty, Back to Menu
			return;

		BasicInfo_t::ImageWidth = atoi(tempSize);

		if (BasicInfo_t::ImageWidth > 50)
		{
			BasicInfo_t::ExtraWidth = BasicInfo_t::ImageWidth - 50;
			BasicInfo_t::ImageWidth = 50;
		}

		tempSize = FileManager::InputText("Wprowadz Wysokosc:");

		if (tempSize == nullptr)	//If Height is empty, Back to Menu
			return;

		BasicInfo_t::ImageHeight = atoi(tempSize);

		if (BasicInfo_t::ImageHeight > 20)
		{
			BasicInfo_t::ExtraHeight = BasicInfo_t::ImageHeight - 20;
			BasicInfo_t::ImageHeight = 20;
		}

		Scrollbars_t::ResetScrollbars();
		FileManager::setFileName(UserName);
		Dimension_t::setImageDimension(FileManager::CreateNewFile(&DrawnObjs));
		
		Clean();
		Scrollbars_t::ResetScrollbars();

		BasicInfo->CursorPos = Vector2i_t(DEFAULT_CURSOR_POS);	//Set Cursor in Our Image
		FileManager::FileMarks.Add(UserName);
	}
	void Copy()
	{
		if (BasicInfo->CurrentMode == DefaultMode)
		{
			Copies.Reset();
			Copies.Draw();
			BasicInfo->CurrentMode = RectangleMode;
		}
		else if (BasicInfo->CurrentMode == RectangleMode && Clipboard::isCopy==true)
		{
			Copies.Analyze();
			BasicInfo->CurrentMode = DefaultMode;
		}
	}
	void Paste()
	{
		if (Clipboard::canPast == true)
		{
			Copies.Paste();
			BasicInfo->CurrentMode = DefaultMode;
			Copies.Reset();
		}
	}
	void DrawLine()
	{
		if (BasicInfo->CurrentMode == DefaultMode)
		{
			DrawnObjs.Add(new Line);
			CreateShape();
			BasicInfo->CurrentMode = LineMode;
		}
		else if (BasicInfo->CurrentMode == LineMode)
			CreateShape();
	}
	void EscEvent()
	{
		switch (BasicInfo->CurrentMode)
		{
		case LineMode:
			QuitFromShapeMode();
			break;

		case RectangleMode:
			if (Clipboard::isCopy == true)
				QuitFromCopyMode();
			else
				QuitFromShapeMode();
			break;

		default:
			BasicInfo->CurrentMode = QuitMode;
		}
	}
	void DrawRectangle()
	{
		if (BasicInfo->CurrentMode == DefaultMode)
		{
			DrawnObjs.Add(new Rectangle);
			CreateShape();
			BasicInfo->CurrentMode = RectangleMode;
		}
		else if (BasicInfo->CurrentMode == RectangleMode)
			CreateShape();
	}
	void Undo()
	{
		if (DrawnObjs.IsEmpty() == false && BasicInfo->CurrentMode != LineMode && BasicInfo->CurrentMode != RectangleMode)
		{
			delete *(DrawnObjs.end());
			DrawnObjs.Erase();
		}
	}
	void Clean()
	{
		int tempsiz = DrawnObjs.Length();
		for (int i = 0; i < tempsiz; i++)
		{
			delete *DrawnObjs.end();
			DrawnObjs.Erase();
		}
	}
public:
	EventHandler_t(BasicInfo_t *BasicInfo) :
		BasicInfo(BasicInfo),
		Bars(&DrawnObjs),
		Copies(&DrawnObjs, BasicInfo)
	{
		if (FileManager::getFileName() != nullptr)
			Dimension_t::setImageDimension(FileManager::Read(&DrawnObjs));
	}
	~EventHandler_t()
	{
		delete Dimension_t::getImageDimension();
	}

	Array_t<Shapes*> DrawnObjs;

	void LoadFile(char* Name)
	{

		FileManager::setFileName(Name);

		Clean();
		Dimension_t::setImageDimension(FileManager::Read(&DrawnObjs));
		Scrollbars_t::ResetScrollbars();
		textcolor(BasicInfo->DrawColor);
		BasicInfo->CursorPos = DEFAULT_CURSOR_POS;

		if (FileManager::FileMarks.InArray(Name) == false)
			FileManager::FileMarks.Add(Name);
	}
	void LookForEvent()
	{

		if (BasicInfo->KeyCode >= A && BasicInfo->KeyCode <= Z)	//If KeyCode is UpperCase cast it to LowerCase
			BasicInfo->KeyCode += FROM_A_TO_Z;

		switch (BasicInfo->KeyCode)
		{
		case 0:			// If Arrow is used Call ArrowControl
		{
			BasicInfo->ArrowIsPressed = true;
			ArrowControler_t ArrowControler(&Bars, BasicInfo);
			UpdateFrame();
			break;
		}

		case ESCAPE: // ESC Close application / Exit from drawing 
			EscEvent();
			break;

		case 'i':	// Load file with default image
			LoadFile("Default");
			break;

		case 'o': // load file with user name
			LoadFile();
			break;

		case 'n': // create new file with user name
			CreateFile();
			break;

		case 's': //save file in user locatiom
			SaveFile();
			break;

		case 'l': //draw line
			DrawLine();
			break;

		case 'k': // draw rectangle
			DrawRectangle();
			break;

		case BACKSPACE: // Backspace Undo
			Undo();
			break;

		case 'c': // copy selected element
			Copy();
			break;

		case 'p': // paste selected element in cursor pos
			Paste();
			break;

		case SPACE:
			if (BasicInfo->DrawColor == BLACK)
				BasicInfo->DrawColor = WHITE;
			else
				BasicInfo->DrawColor = BLACK;
			break;

		case ENTER:	//Enter Switch Backgroundcolor
			BasicInfo->BackGroundColor = (BasicInfo->BackGroundColor + 1) % 16;
			break;

		case 'z':		// File Marks
			if (MARKS_IS_ON)
				FileMarks();
			break;

		default:
			ChangeDrawColor();
			break; // Look for color to change
		}
	}
};
