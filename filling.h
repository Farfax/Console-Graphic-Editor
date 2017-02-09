//#pragma once
//
//class Filling
//{
//	Rectangle View;
//	Array_t<Vector2i_t>PosXY;
//	Array_t<int> Color;
//	Array_t<Shapes*>* DrawnObjs;
//	BasicInfo_t * BasicInfo;
//	static Vector2i_t Start;
//	Pasted_t *toPast = nullptr;
//	static Vector2i_t End;
//
//public:
//	Filling(Array_t<Shapes*>* DrawnObjs, BasicInfo_t* BasicInfo) :
//		DrawnObjs(DrawnObjs),
//		BasicInfo(BasicInfo)
//	{}
//
//	void Analyze()
//	{
//		int i = 0;
//
//		Clipboard::End = BasicInfo->CursorPos;
//		Vector2i_t toCheck = Clipboard::Start;
//		Vector2i_t temp;
//
//		for (int j = 0; j <= abs(Clipboard::Start.x - Clipboard::End.x); j++)
//		{
//			for (auto ObjToCheck = DrawnObjs->begin(); ObjToCheck != DrawnObjs->end(); ObjToCheck++)
//			{
//				for (int i = 0; i <= abs(Clipboard::Start.y - Clipboard::End.y); i++)
//				{
//					if ((*ObjToCheck)->Intersect(toCheck))
//					{
//						Vector2i_t  temp = (toCheck);
//						PosXY.Add(temp);
//						Color.Add(((*ObjToCheck)->getColor()));
//					}
//
//					if (Clipboard::Start.y - Clipboard::End.y < 0)
//						(toCheck.y)++;
//					else
//						(toCheck.y)--;
//				}
//				toCheck.y = Clipboard::Start.y;
//			}
//
//			if (toCheck.x - Clipboard::End.x < 0)
//				(toCheck.x)++;
//			else
//				(toCheck.x)--;
//		}
//		delete *DrawnObjs->end();
//		Clipboard::isCopy = false;
//		Clipboard::Size = getShapeSize();
//		Vector2i_t* Pos = PosXY.begin();
//		int * Colors = Color.begin();
//		toPast = new Pasted_t(Pos, Colors, PosXY.Length());
//
//	}
//};
