#include "stdafx.h"
#include "graphics.h"
#include "pixel.h"

BEGIN_NAMESPACE_2(SSDF,Graphics)
void DrawLine( const Point& _pt0, const Point& _pt1, const Pixel& color, Mat& img ){
	float width   = (float) img.cols;
	float height  = (float) img.rows;
	Point p0( _pt0.x * width, _pt0.y * height );
	Point p1( _pt1.x * width, _pt1.y * height );
	cv::line( img, p0, p1, color );
}
END_NAMESPACE_2


