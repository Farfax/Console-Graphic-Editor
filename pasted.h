#pragma once
#include"Shapes.h"

class Pasted_t :
	public Shapes
{
	Array_t<Vector2i_t> PosXY;
	Array_t<int> Color;
	Vector2i_t Start;
	bool isVisible;
public:
	Pasted_t()
	{
	}

	Pasted_t(Vector2i_t* Pos, int* Color, int Length) : //TODO right copt
		isVisible(true)
	{
		for (int i = 0; i < Length; i++)
		{
			this->PosXY.Add(*(Pos + i));
			this->Color.Add(*(Color + i));
		}

	}
	Array_t<Vector2i_t> getPosArray()
	{
		return PosXY;
	}

	void Draw()
	{
		int i = 0;
		for (auto It = PosXY.begin(); It != PosXY.rEnd(); It++)
		{
			gotoxy(*It);
			textbackground(*(Color.begin() +i));
			putch(' ');
			i++;
		}
		textbackground(BLACK);

	}

	void DrawToPoint(Vector2i_t NotImportant)
	{
		Draw();
	}

	Vector2i_t getEndPoint()
	{
		return *(PosXY.end());
	}

	void  SlidetoNewPos(Vector2i_t newPos)
	{
			for (auto It = PosXY.begin(); It != PosXY.rEnd(); It++)
			*It += newPos;
	}

	void setVisible(bool isVisbile)
	{
		this->isVisible = isVisbile;
	}

	int getColor()
	{
		return *(Color.end());
	}

	void setColor(int Color)
	{
		this->Color.Add(Color);
	}

	void setStart(Vector2i_t Start)
	{
		this->Start = Start;
	}

	Info_t getInfo()
	{
		Info_t Info('P', Vector2i_t(0, 0), Vector2i_t(0, 0), NULL, true);
		
		for (int i = 0; i < PosXY.Length(); i++)
		{
			Info.PosXY.Add(*(PosXY.begin() + i));
			Info.Colors.Add(*(Color.begin() + i));
		}
		return Info;
	}

	void BuildFromInfo(Info_t BuildInfo)
	{
		PosXY = BuildInfo.PosXY;
		Color = BuildInfo.Colors;
		isVisible = true;
		Draw();
	}

	void Slide(Vector2i_t Step)
	{
		for (auto toSlide = PosXY.begin(); toSlide != PosXY.rEnd(); toSlide++)
			*toSlide += Step;
	}

	bool Intersect(Vector2i_t toCheck)
	{
		for (auto PosiX = PosXY.begin(); PosiX != PosXY.rEnd(); PosiX++)
			if (toCheck == *PosiX)
				return true;

		return false;
	}
};