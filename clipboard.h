#pragma once
class Clipboard
{
	Rectangle View;
	Array_t<Vector2i_t>PosXY;
	Array_t<int> Color;
	Array_t<Shapes*>* DrawnObjs;
	BasicInfo_t * BasicInfo;
	Vector2i_t Start;
	Pasted_t *toPast = nullptr;
	Vector2i_t End;
	
public:
	Clipboard(Array_t<Shapes*>* DrawnObjs, BasicInfo_t* BasicInfo) :
		DrawnObjs(DrawnObjs),
		BasicInfo(BasicInfo)
	{}

	static bool isEmpty;
	static Vector2i_t Size;
	static bool canPast;
	static bool isCopy;

	void Draw()	//Interactive Coping, Light Selected Space
	{
		DrawnObjs->Add(new Rectangle); 
		(*DrawnObjs->end())->setStart(BasicInfo->CursorPos);
		(*DrawnObjs->end())->setColor(DARKGRAY);
		Clipboard::isCopy = true;
		Clipboard::Start = BasicInfo->CursorPos;
	}
	void Quit()
	{
		delete *DrawnObjs->end();
		DrawnObjs->Erase();
		Clipboard::isCopy = false;
	}
	//Swap End with Start
	void Swap()
	{
		Vector2i_t temp = Clipboard::End;
		Clipboard::Start = Clipboard::End;
		Clipboard::End = Clipboard::Start;

	}
	void CreatePasted(Vector2i_t * Pos, int* Colors)
	{
		Pos = PosXY.begin();
		Colors = Color.begin();

		toPast = new Pasted_t(Pos, Colors, PosXY.Length());

	}
	void UpdateStatus()
	{
		Clipboard::isCopy = false;
		Clipboard::Size = getShapeSize();
		Clipboard::isEmpty = false;
		Clipboard::canPast = true;
	}
	//Copying Selected Pixel
	void Analyze()
	{
		int i = 0;
		
		Clipboard::End = BasicInfo->CursorPos;
		Vector2i_t toCheck = Clipboard::Start;

		for(int j=0;j<=abs(Clipboard::Start.x-Clipboard::End.x);j++)
		{	
			for (auto ObjToCheck = DrawnObjs->begin(); ObjToCheck != DrawnObjs->end(); ObjToCheck++)	//Change object to check Point
			{
				for (int i = 0; i <= abs(Clipboard::Start.y - Clipboard::End.y); i++) 	 //Check All y in Column, If Active then Save to PASTE
				{				
					if ((*ObjToCheck)->Intersect(toCheck))
					{
						Vector2i_t  temp = (toCheck);
						PosXY.Add(temp);
						Color.Add(((*ObjToCheck)->getColor()));
					}

					if (Clipboard::Start.y - Clipboard::End.y < 0)
						(toCheck.y)++;
					else
						(toCheck.y)--;

				}

					toCheck.y = Clipboard::Start.y;
			}

			if (toCheck.x - Clipboard::End.x < 0)
				(toCheck.x)++;
			else
				(toCheck.x)--;
		}

		delete *DrawnObjs->end();

		CreatePasted(PosXY.begin(), Color.begin());	// Create Past to Draw

		if (Clipboard::End > Clipboard::Start)	// End is on left Side Start Swap it
			Swap();

		UpdateStatus();
		DrawnObjs->Erase();
	}
	// Check if User Can Paste
	static void CheckPasting(BasicInfo_t BasicInfo)
	{
		if (Dimension_t::getImageDimension()->isInside(Vector2i_t(abs(BasicInfo.CursorPos.x + Clipboard::Size.x), abs(BasicInfo.CursorPos.y + Clipboard::Size.y))) && Clipboard::isEmpty == false)
			Clipboard::canPast = true;
		else
			Clipboard::canPast = false;

	}

	Vector2i_t getShapeSize()	//Return Selected Size
	{
		return Vector2i_t(abs(Clipboard::End.x - Clipboard::Start.x), abs(Clipboard::End.y - Clipboard::Start.y));
	}
	void Paste()
	{
		toPast->Slide(BasicInfo->CursorPos - Clipboard::Start);
		toPast->Draw();
		DrawnObjs->Add(toPast);
		Reset();
	}
	// Set Variable to Default
	void Reset()
	{
		toPast = nullptr;
		Color.Clear();
		Start = Vector2i_t(0, 0);
		PosXY.Clear();
		Clipboard::Size = Vector2i_t(0, 0);
		Clipboard::isEmpty = true;
		Clipboard::canPast = false;
	}
};

bool Clipboard::isEmpty = true;
Vector2i_t Clipboard::Size = Vector2i_t(0,0);
bool Clipboard::canPast = false;
bool Clipboard::isCopy = false;