#pragma once
#include "stdafx.h"

class Pixel;

BEGIN_NAMESPACE_2(SSDF,Graphics)
void DrawLine( const Point& _pt0, const Point& _pt1, const Pixel& color, Mat& img );
END_NAMESPACE_2
