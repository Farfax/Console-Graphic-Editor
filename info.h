#pragma once
class Info_t
{
public:
	char Type;
	Vector2i_t StartPoint;
	Vector2i_t EndPoint;
	Array_t < Vector2i_t> PosXY;
	Array_t < int> Colors;//secret Member
	int Color;
	bool isVisible;

	Info_t(char Type, Vector2i_t StartPoint, Vector2i_t EndPoint, int Color, bool isVisible)
	{
		this->Type = Type;
		this->StartPoint = StartPoint;
		this->EndPoint = EndPoint;
		this->Color = Color;
		this->isVisible = isVisible;
	}
	Info_t()
	{
		this->Type = NULL;
		this->StartPoint = Vector2i_t(0, 0);
		this->EndPoint = Vector2i_t(0, 0);
		this->Color = 0;
		this->isVisible = 0;
	}
	Info_t(const Info_t& InfoToSet)
	{
		this->Type = InfoToSet.Type;
		this->StartPoint = InfoToSet.StartPoint;
		this->EndPoint = InfoToSet.EndPoint;
		this->Color = InfoToSet.Color;
		this->isVisible = InfoToSet.isVisible;
	}

	Info_t getInfo()
	{
		return *this;
	}

	inline bool operator==(const Info_t& SecondOperant)
	{
		if (this->Type == SecondOperant.Type && this->StartPoint == SecondOperant.StartPoint && this->EndPoint == SecondOperant.EndPoint && this->Color == SecondOperant.Color && this->isVisible == SecondOperant.isVisible)
			return true;
		else
			return false;
	}
	inline bool operator!=(const Info_t& SecondOperant) { return !(*this == SecondOperant); }
};

class BasicInfo_t
{
public:
	BasicInfo_t()
	{
		textmode(8);			//setting console
		settitle("Maciej Kuligowski 165291");
		_setcursortype(_NOCURSOR);
	}

	int KeyCode = 0;
	Vector2i_t CursorPos = DEFAULT_CURSOR_POS;
	int FileMarksCount = 0;
	int DrawColor = DEFAULT_CURSOR_COLOR, BackGroundColor = BLACK;
	bool ArrowIsPressed = false;
	static int ExtraWidth, ExtraHeight;
	static int ImageWidth, ImageHeight;
	Mode CurrentMode = DefaultMode;
};

enum Side_t
{
	Up,
	Down,
	Left,
	Right
};
int BasicInfo_t::ExtraWidth = 0;
int BasicInfo_t::ExtraHeight = 0;
int BasicInfo_t::ImageWidth = 0;
int BasicInfo_t::ImageHeight = 0;