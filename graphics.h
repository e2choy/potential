#pragma once
#include "stdafx.h"

class Pixel;
BEGIN_NAMESPACE(SSDF)
  class Polygon;
END_NAMESPACE

BEGIN_NAMESPACE_2(SSDF,Graphics)
void MatFltToRGBA( const Mat& img, Mat& out );
void DrawLine( const Point& _pt0, const Point& _pt1, const Pixel& color, Mat& img );
void DrawIsocontours( const Mat& matF, Mat& img, float freq = 32.0f );
void DrawRectangle( const Rect& r, const cv::Scalar& color, Mat& img );
void FillRectangle( const Rect& r, const cv::Scalar& color, Mat& img );
void FillPolygon( const Polygon& poly, const cv::Scalar& color, Mat& img );
END_NAMESPACE_2
