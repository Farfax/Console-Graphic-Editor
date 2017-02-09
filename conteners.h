#pragma once
enum Mode
{
	DefaultMode,
	LineMode,
	RectangleMode,
	QuitMode,
	CopyMode
};

template <class typ>
class Array_t
{
	typ * Value;
	int Size;
public:
	Array_t() :
		Size(0),
		Value(nullptr)
		//FreeSpace(0)
	{}
	~Array_t()
	{
		Clear();
	}
	int Length()
	{
		return Size;
	}
	void Clear()
	{
		if (Size > 0)
		{
			delete[]Value;
			Value = nullptr;
			Size = 0;
		}
	}
	bool IsEmpty()
	{
		if (Size == 0)
			return true;
		else
			return false;
	}

	//void Resize(int NewSize)
	//{
	//	if (Size <= 0)
	//	{
	//		Size = NewSize;
	//		Value = new typ[Size];
	//		FreeSpace = Size;
	//		return;
	//	}
	//	
	//	if (FreeSpace > 0)
	//		Size -= FreeSpace;

	//	typ* Temp = new typ[Size];

	//	for (int i = 0; i < Size; i++)
	//		Temp[i] = Value[i];

	//	delete[] Value;
	//	Value = new typ[NewSize];

	//	for (int i = 0; i <Size; i++)
	//		Value[i] = Temp[i];

	//	delete[] Temp;
	//	
	//	FreeSpace = NewSize - Size;
	//	Size = NewSize;
	//}

	Array_t<typ>& operator+=(Array_t<typ> rhs)
	{
		for (int i = 0; i < rhs.Length(); i++)
			this->Add(rhs.Value[i]);

		return *this;
	}
	bool InArray(typ toCheck)
	{
		for (int i = 0; i < Size; i++)
			if (Value[i] == toCheck)
				return true;

		return false;
	}
	void Add(typ ValueToAdd)
	{
		if (Size <= 0)
		{
			Size = 1;
			Value = new typ[Size];
			Value[0] = ValueToAdd;
			return;
		}

		typ* Temp = new typ[Size + 1];

		memcpy(Temp, Value, Size * sizeof(typ));
		Temp[Size] = ValueToAdd;

		delete[] Value;
		Value = Temp;
		Size++;
	}
	typ* end()
	{
		if (Size > 0)
			return Value + Size - 1;
		else
			return nullptr;
	}
	typ* rEnd()
	{
		if (Size > 0)
			return (Value + Size);
		else
			return nullptr;
	}
	typ* rBegin()
	{
		if (Size > 0)
			return (Value - 1);
		else
			return nullptr;
	}
	typ* begin()
	{
		if (Size > 0)
			return Value;
		else
			return nullptr;
	}
	void Erase()
	{
		if (Size <= 0)
		{
			Size = 0;
			Value = nullptr;
			return;
		}

		//if (FreeSpace > 0)
		//{
		//	Size -= FreeSpace;
		//	FreeSpace = 0;
		//}

		Size--;

		typ* Temp = new typ[Size];

		memcpy(Temp, Value, Size * sizeof(typ));

		delete[] Value;
		Value = new typ[Size];
		memcpy(Value, Temp, Size * sizeof(typ));

		delete[] Temp;
	}
};

template<class typ>
inline Array_t<typ> operator+(Array_t<typ> lhs, Array_t<typ>& rhs)
{
	lhs += rhs;
	return lhs;
}
class Vector2i_t
{
public:
	int x, y;

	Vector2i_t() :
		x(0),
		y(0)
	{}
	Vector2i_t(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	Vector2i_t& operator+=(const Vector2i_t& SecondVector)
	{
		this->x += SecondVector.x;
		this->y += SecondVector.y;
		return *this;
	}
	Vector2i_t& operator-=(const Vector2i_t& SecondVector)
	{
		this->x -= SecondVector.x;
		this->y -= SecondVector.y;
		return *this;
	}
	Vector2i_t& operator=(const Vector2i_t& FirstVector)
	{
		this->x = FirstVector.x;
		this->y = FirstVector.y;
		return *this;
	}

};

inline bool operator==(const Vector2i_t& lhs, const Vector2i_t& rhs)
{
	if (lhs.x == rhs.x && lhs.y == rhs.y)
		return true;
	else
		return false;
}
inline bool operator!=(const Vector2i_t& lhs, const Vector2i_t& rhs)
{
	return !operator==(lhs, rhs);
}

// Return true if Left Operant is on the left Side of Right Operant
inline bool operator>(const Vector2i_t& lhs, const Vector2i_t& rhs)
{
	if (lhs.x <= rhs.x)
		return true;
	else
		return false;
}
// Return true if Left Operant is Upper then Right Operant
inline bool operator<(const Vector2i_t& lhs, const Vector2i_t& rhs)
{
	if (lhs.y <= rhs.y)
		return true;
	else
		return false;
}

inline Vector2i_t operator+(Vector2i_t FirstVector, const Vector2i_t& SecondVector)
{
	FirstVector += SecondVector;
	return FirstVector;
}

inline Vector2i_t operator-(Vector2i_t FirstVector, const Vector2i_t& SecondVector)
{

	FirstVector -= Vector2i_t(SecondVector.x, SecondVector.y);
	return FirstVector;
}

void gotoxy(Vector2i_t);