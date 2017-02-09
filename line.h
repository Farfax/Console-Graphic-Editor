#pragma once
#include "shapes.h"

class Line
	:public Shapes
{
	Vector2i_t Start;
	Vector2i_t EndPoint;
	Array_t<Vector2i_t> PosXY;
	bool isVisible;
	int Color;

public:
	Line() :
		isVisible(false),
		Color(DARKGRAY)
	{}
	~Line() {
	}
	Vector2i_t getEndPoint()
	{
		return EndPoint;
	}	
	int getColor()
	{
		return Color;
	}
	Array_t<Vector2i_t> getPosArray()
	{
		return PosXY;
	}
	void Slide(Vector2i_t Step)
	{
		for (auto toSlide = PosXY.begin(); toSlide != PosXY.rEnd(); toSlide++)
			*toSlide += Step;
	}

	void setColor(int Color)
	{
		this->Color = Color;
	}
	void setStart(Vector2i_t Start)
	{
		this->Start = Start;
	}

	void setEndPoint(Vector2i_t End)
	{
		EndPoint = End;
	}

	void BuildFromInfo(Info_t Info)
	{
		this->Start = Info.StartPoint;
		this->EndPoint = Info.EndPoint;
		this->Color = Info.Color;
		this->isVisible = Info.isVisible;
		DrawToPoint(this->EndPoint);
	}
	Info_t getInfo()
	{
		return Info_t('L', Start, EndPoint, Color, isVisible);
	}
	void setVisible(bool isVisible)
	{
		this->isVisible = isVisible;
	}
	void AddOnePoint(Vector2i_t PointToAdd)
	{
		PosXY.Add(PointToAdd);
	}
	void DrawToPoint(Vector2i_t Point)
	{
		Vector2i_t CurrentPoint(Start);

		EndPoint = Point;

		//Ukosna
		if (EndPoint.x != Start.x  && Point.y != Start.y)
		{
			while (EndPoint.x != CurrentPoint.x &&EndPoint.y != CurrentPoint.y)
			{
				PosXY.Add(CurrentPoint);

				if ((Start.x - EndPoint.x) < 0)
					CurrentPoint += Vector2i_t(1, 0);
				else
					CurrentPoint += Vector2i_t(-1, 0);

				if ((Start.y - EndPoint.y) < 0)
					CurrentPoint += Vector2i_t(0, 1);
				else
					CurrentPoint += Vector2i_t(0, -1);
			}
			PosXY.Add(Point);
			setEndPoint(Point);
			return;
		}
		else if (Point.x != Start.x)
		{	
			//Poziom
			while (Point.x != CurrentPoint.x)
			{
				PosXY.Add(CurrentPoint);

				if ((Start.x - EndPoint.x) < 0)
					CurrentPoint += Vector2i_t(1, 0);
				else
					CurrentPoint += Vector2i_t(-1, 0);
			}
			PosXY.Add(Point);
			setEndPoint(Point);
			return;
		}
		else if (Point.y != Start.y) //Pion
		{
			while (Point.y != CurrentPoint.y)
			{
				PosXY.Add(CurrentPoint);

				if ((Start.y - EndPoint.y) < 0)
					CurrentPoint += Vector2i_t(0, 1);
				else
					CurrentPoint += Vector2i_t(0, -1);
			}
			PosXY.Add(Point);
			setEndPoint(Point);
			return;
		}
	}

	void Draw()
	{
		Draw('*', FULL_COLOR_MODE_ON, SECURE_MODE_ON);
	}
	//Draw Symbol or Color 
	void Draw(int Symbol, bool FullColor, bool SecureMode) // SecureMode let draw only in dimension
	{
		textcolor(Color);

		for (auto toDraw = PosXY.begin(); toDraw != PosXY.rEnd(); toDraw++)
		{
			gotoxy(*toDraw);

			if (FullColor == true)
				textbackground(Color);

			if( SecureMode==0 || ((toDraw->x >= DEFAULT_CURSOR_POS.x) && (toDraw->x < DEFAULT_CURSOR_POS.x + BasicInfo_t::ImageWidth) && (toDraw->y >= DEFAULT_CURSOR_POS.y) && (toDraw->y < DEFAULT_CURSOR_POS.y + BasicInfo_t::ImageHeight)))
				putch(Symbol);
		}

		textbackground(BLACK);
		if (this->isVisible == false)
			PosXY.Clear();
	}
	// Return true if Point is a part of Border
	bool Intersect(Vector2i_t toCheck)
	{
			if (PosXY.InArray(toCheck) == true)
				return true;

		return false;

	}
};