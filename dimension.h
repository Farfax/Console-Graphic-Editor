#pragma once
class Dimension_t
{
	static Rectangle* ImageDimension;

public:
	static Rectangle* getImageDimension()
	{
		return ImageDimension;
	}
	static Vector2i_t getEndPoint()
	{
		return ImageDimension->getEndPoint() - Vector2i_t(-1, -1);	// We need Last Point IN Dimension
	}

	static Rectangle* setImageDimension()
	{
		if (ImageDimension != nullptr)
			delete ImageDimension;

		ImageDimension = new Rectangle;
		ImageDimension->setStart(DIMENSION_LOCATION_POS);
		ImageDimension->setVisible(1);
		ImageDimension->DrawToPoint(DEFAULT_CURSOR_POS + Vector2i_t(BasicInfo_t::ImageWidth, BasicInfo_t::ImageHeight));	// We need DRAWABLE Size so we need add size to Cursor Location

		return ImageDimension;
	}
	
	static void setImageDimension(Rectangle* ImageDimension)
	{
		Dimension_t::ImageDimension = ImageDimension;
	}
};

Rectangle* Dimension_t::ImageDimension = nullptr;