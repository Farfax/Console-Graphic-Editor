#pragma once
#include"Line.h"

class Rectangle : //TODO  DONE Make Fucking Rectangle Class, (And Abstract Shapes would  be so cool)
	public Shapes
{
	//TODO Filling with love( Filling Shapes with Colours)
	Vector2i_t LeftCorner;
	Vector2i_t EndPoint;
	Line *Side;
	bool isVisible;
	int Color;

public:
	Rectangle() :
		Side(new Line[4]),
		Color(DARKGRAY),
		isVisible(false)
	{}
	~Rectangle()
	{
		delete[] Side;
	}

	void Slide(Vector2i_t Step)
	{
		for (int i = 0; i < 4; i++)
			Side[i].Slide(Step);
	}
	int getColor()
	{
		return Color;
	}
	Vector2i_t getEndPoint()
	{
		return EndPoint;
	}
	Vector2i_t getLeftCorner()
	{
		return LeftCorner;
	}
	Info_t getInfo()
	{
		return Info_t('R', LeftCorner, EndPoint, Color, isVisible);
	}
	void BuildFromInfo(Info_t Info)
	{
		this->LeftCorner = Info.StartPoint;
		this->EndPoint = Info.EndPoint;
		this->Color = Info.Color;
		this->isVisible = Info.isVisible;
		DrawToPoint(this->EndPoint);
	}
	void setVisible(bool isVisible)
	{
		this->isVisible = isVisible;
	}
	void setColor(int Color)
	{
		this->Color = Color;
	}
	void setStart(Vector2i_t Start)
	{
		LeftCorner = Start;
	}
	void DrawToPoint(Vector2i_t Point)
	{

		Side[0].setStart(LeftCorner); /// Upper Side
		Side[3].setStart(LeftCorner); // Left Side

		for (int i = 1; i < 3; i++)
			Side[i].setStart(Point);

		for (int i = 0; i < 2; i++)
		{
			Side[i].DrawToPoint(Vector2i_t(Point.x, LeftCorner.y));
			Side[i + 2].DrawToPoint(Vector2i_t(LeftCorner.x, Point.y));
		}

		EndPoint = Point;
	}

	void Draw()
	{
		Draw('*', FULL_COLOR_MODE_ON,SECURE_MODE_ON);
	}
	bool isInside(Vector2i_t toCheck)
	{
		if (toCheck.x > LeftCorner.x && toCheck.x < EndPoint.x && toCheck.y>LeftCorner.y && toCheck.y<EndPoint.y)
			return true;
		else
			return false;
	}
	// Draw Symbol or FullColor 
	void Draw(int Symbol, bool FullColor, bool SecureMode)
	{
		for (int i = 0; i < 4; i++)
		{
			Side[i].setVisible(1);
			Side[i].setColor(this->Color);
			Side[i].Draw(Symbol, FullColor,SecureMode);
		}

		if (isVisible == false)
		{
			delete[] Side;
			Side = new Line[4];
		}
	}
	Array_t<Vector2i_t> getPosArray()
	{
		Array_t<Vector2i_t> tmp;

		for (int i = 0; i < 4; i++)
			tmp += Side[i].getPosArray();

		return tmp;
	}
	bool Intersect(Vector2i_t toCheck)
	{
		for (int i = 0; i < 4; i++)
			if (Side[i].Intersect(toCheck) == true)
				return true;

		return false;

	}
};