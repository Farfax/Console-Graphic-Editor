#pragma once
class ArrowControler_t
{
	Scrollbars_t* Bars;
	BasicInfo_t* BasicInfo;
	Vector2i_t OldPos = Vector2i_t(BasicInfo->CursorPos);
	void AltArrowControler()
	{
		switch (BasicInfo->KeyCode)
		{
		case ALT_RIGHT: // ->
			(BasicInfo->CursorPos.x)++;
			break;

		case ALT_LEFT: // <-
			(BasicInfo->CursorPos.x)--;
			break;

		case ALT_DOWN: // \/
			(BasicInfo->CursorPos.y)++;
			break;

		case ALT_UP: // ^
			(BasicInfo->CursorPos.y)--;
			break;
		}
	}
	void MoveArrowControler()
	{
		switch (BasicInfo->KeyCode)
		{
		case UP:
			(BasicInfo->CursorPos.y)--;
			break;

		case DOWN:
			(BasicInfo->CursorPos.y)++;
			break;

		case LEFT:
			(BasicInfo->CursorPos.x)--;
			break;

		case RIGHT:
			(BasicInfo->CursorPos.x)++;
			break;
		}
	}
	void ScrollArrowControler()
	{
		switch (BasicInfo->KeyCode)
		{
		case CTRL_UP: // ctrl+arrow scroll screen Up
			if (BasicInfo_t::ExtraHeight > 0)
				Bars->Slide(Vector2i_t(0, -1));
			break;

		case CTRL_DOWN: //down
			if (BasicInfo_t::ExtraHeight > 0)
				Bars->Slide(Vector2i_t(0, 1));
			break;

		case CTRL_RIGHT: //right
			if (BasicInfo_t::ExtraWidth > 0)
				Bars->Slide(Vector2i_t(-1, 0));
			break;

		case CTRL_LEFT: // left
			if (BasicInfo_t::ExtraWidth > 0)
				Bars->Slide(Vector2i_t(1, 0));
		}
	}
	void DimensionLimit()
	{
		if (FileManager::getFileName() != nullptr && strcmp(FileManager::getFileName(), "File Not Exist"))	// Don't let Move when Cursor isn't inside Image
			if (Dimension_t::getImageDimension()->isInside(BasicInfo->CursorPos) == false)
				BasicInfo->CursorPos = OldPos;
	}
public:
	ArrowControler_t(Scrollbars_t* Bars, BasicInfo_t* BasicInfo) :
		Bars(Bars),
		BasicInfo(BasicInfo)
	{
		BasicInfo->KeyCode = getch();

		if (Clipboard::isCopy == true)
			AltArrowControler();
		else
			MoveArrowControler();

		ScrollArrowControler();
		DimensionLimit();
	}
};