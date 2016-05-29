#include "stdafx.h"
#include "graphics.h"
#include "pixel.h"
#include "color.h"
#include "polygon.h"
/////////////////////////////////////////////////////////////////
BEGIN_NAMESPACE(SSDF)
  class Polygon;
END_NAMESPACE
/////////////////////////////////////////////////////////////////
BEGIN_NAMESPACE_2(SSDF,Graphics)
/////////////////////////////////////////////////////////////////
void DrawLine( const Point& _pt0, const Point& _pt1, const Pixel& color, Mat& img ){
	float width   = (float) img.cols;
	float height  = (float) img.rows;
	Point p0( _pt0.x * width, _pt0.y * height );
	Point p1( _pt1.x * width, _pt1.y * height );
	cv::line( img, p0, p1, color );
}
/////////////////////////////////////////////////////////////////
void DrawIsocontours( const Mat& imgF, Mat& img, float freq ){
  img = Mat( imgF.cols, imgF.rows, CV_8UC4, Pixel::CYAN );
  for( int y = 0; y < imgF.rows; ++y ){
    for( int x = 0; x < imgF.cols; ++x ){
      float sum = imgF.at<float>(y,x);
      float ang = sum * 2.0f * 3.1415 * freq;
      float val = (std::sin( ang ) + 1.0f)/2.0f;
      Color c;
      if ( val > 0.5f ){
        c = Color::GRAY;
      }
      else{
        c = Color::WHITE;
      }

      img.at<Vec4b>(y,x) = c.ToScalar();
    }
  }
}
/////////////////////////////////////////////////////////////////
void MatFltToRGBA( const Mat& img, Mat& out ){
    Mat temp;
    cv::cvtColor(img,temp,CV_GRAY2RGBA);
    temp.convertTo( out, CV_8UC4, 255 );
}
/////////////////////////////////////////////////////////////////
void DrawRectangle( const Rect& r, const cv::Scalar& color, Mat& img ){
    float width = (float) img.cols;
    float height = (float) img.rows;
    RectI b( 
        (int)(r.x * width), 
        (int)(r.y * height),
        (int)(r.width * width), 
        (int)(r.height * height) );
    cv::rectangle( img, b, color );
}
/////////////////////////////////////////////////////////////////
void FillRectangle( const Rect& r, const cv::Scalar& color, Mat& img ){
    float width = (float) img.cols;
    float height = (float) img.rows;
    RectI b( 
        (int)(r.x * width), 
        (int)(r.y * height),
        (int)(r.width * width), 
        (int)(r.height * height) );
    cv::rectangle( img, b, color, -1 );
}
/////////////////////////////////////////////////////////////////
void FillPolygon( const Polygon& poly, const cv::Scalar& color, Mat& img ){
  //get the number of paths and the number of contours
  std::vector< std::vector<cv::Point> > pts;

  float width = img.cols;
  float height = img.rows;
  const Polygon::Paths& paths = poly.GetPaths();
  for( const Polygon::Path& path : paths ){
    std::vector<cv::Point> _pts;
    for( const Point& pt : path ){
      cv::Point _pt(pt.x*width,pt.y*height);
      _pts.push_back(_pt);
    }
    pts.push_back( _pts );
  }

  cv::fillPoly( img, pts, color );
}
/////////////////////////////////////////////////////////////////
END_NAMESPACE_2


