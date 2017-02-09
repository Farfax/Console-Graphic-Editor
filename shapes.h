#pragma once

class Shapes //TODO DONE Abstract Class for Shapes object
{
public:
	virtual ~Shapes() {}

	virtual Array_t<Vector2i_t> getPosArray() = 0;
	virtual void Draw() = 0;
	virtual void DrawToPoint(Vector2i_t) = 0;
	virtual void setVisible(bool) = 0;
	virtual void setColor(int) = 0;
	virtual int getColor() = 0;
	virtual Vector2i_t getEndPoint() = 0;
	virtual void setStart(Vector2i_t) = 0;
	virtual Info_t getInfo() = 0;
	virtual void BuildFromInfo(Info_t) = 0;
	virtual void Slide(Vector2i_t) = 0;
	virtual bool Intersect(Vector2i_t) = 0;
};

