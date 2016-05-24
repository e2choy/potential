#include "stdafx.h"
#include "util.h"

BEGIN_NAMESPACE_2(SSDF,Math)

Point ProjectPointToLine( const Point& p0, const Point& p1, const Point& p ){
  //compute the original line in Ax+By=C form
  float A = p1.y - p0.y;
  float B = p0.x - p1.x;
  float C = A * p0.x + B* p0.y;

  //compute the line perpendicular
  float A_, B_, C_;
  A_ = B;
  B_ = -A;
  C_ = A_* p.x + B_ * p.y;

  //check if they intersect 
  float det = A * B_ - A_ * B;

  //cant happen lines perpendicular
  assert( det != 0.0f );              
  float x = (B_*C - B*C_)/det;
  float y = (A*C_ - A_*C)/det;

  return Point(x,y);
}

float DistancePointToLine( const Point& p0, const Point& p1, const Point& p ){
  //find the nearest point to the line
  Point nearest = ProjectPointToLine( p0, p1, p );
  float distance = Distance( nearest, p );
  return distance;
}

float SquareDistance( const Point& p0, const Point& p1 ){
  float ret = std::pow(p0.x - p1.x, 2) + std::pow(p0.y - p1.y, 2);
  return ret;
}

float Distance( const Point& p0, const Point& p1 ){
  float ret = SquareDistance(p0,p1);
  ret = std::sqrt( static_cast<float>(ret) );
  return ret;
}
END_NAMESPACE_2

