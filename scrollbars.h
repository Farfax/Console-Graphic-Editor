#pragma once
class Scrollbars_t
{
	Array_t<Shapes*>*Drawnobj;
	Vector2i_t CurrentLocation;

	//Don't Let slide in infinity
	bool CanSlide(Vector2i_t Step)
	{
		if (CurrentLocation.x <= DEFAULT_CURSOR_POS.x)
			if (Step == Vector2i_t(-1, 0))
				return false;

		if (CurrentLocation.y <= DEFAULT_CURSOR_POS.y)
			if (Step == Vector2i_t(0, -1))
				return false;

		if (CurrentLocation.x == DEFAULT_CURSOR_POS.x + BasicInfo_t::ExtraWidth)
			if (Step == Vector2i_t(1, 0))
				return false;

		if (CurrentLocation.y == DEFAULT_CURSOR_POS.y + BasicInfo_t::ExtraHeight)
			if (Step == Vector2i_t(0, 1))
				return false;

		return true;
	}
public:
	Scrollbars_t(Array_t<Shapes*>*Drawnobj) :
		Drawnobj(Drawnobj),
		CurrentLocation(DEFAULT_CURSOR_POS)
	{}

	static Vector2i_t XBar, YBar; 

	void UpdateBarsPos(Vector2i_t Step)
	{
		if(Step.x!=0)
			Scrollbars_t::XBar-=Step;
		else
			Scrollbars_t::YBar-=Step;

	}
	void Slide(Vector2i_t Step)
	{
		if (Drawnobj->Length() == 0)
			return;						//There is nothing to do, so just end it
		
		if (CanSlide(Step) == false)
			return;

		CurrentLocation += Step;

			for (auto Obj = Drawnobj->begin(); Obj!= Drawnobj->rEnd(); Obj++)
				(*Obj)->Slide(Step);

			UpdateBarsPos(Step);

	}
	static void ResetScrollbars()
	{
		Scrollbars_t::XBar = DIMENSION_LOCATION_POS + Vector2i_t(BasicInfo_t::ImageWidth+1, 0);
		Scrollbars_t::YBar = DIMENSION_LOCATION_POS + Vector2i_t(0, BasicInfo_t::ImageHeight+1);
	}
	
};
Vector2i_t Scrollbars_t::XBar = DIMENSION_LOCATION_POS;
Vector2i_t Scrollbars_t::YBar = DIMENSION_LOCATION_POS;