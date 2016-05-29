#include "stdafx.h"
#include "util.h"

BEGIN_NAMESPACE_2(SSDF,Math)

/////////////////////////////////////////////////////////////////
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

/////////////////////////////////////////////////////////////////
void ProjectPointToLine( const Point& p0, const Point& p1, const Point& p, Point& near, float& t ){
    Vec2f _l = p0 - p1;
    float l = _l.dot(_l);

    //p0 == p1
    if( l == 0.0f ) {
      near = p0;
      t = 0.0f;
      return;
    }

    //consider the line extending the segment as v + t(w-v)
    const float _t = (p-p0).dot(p1-p0)/l;
    Vec2f proj = p0 + _t * ( p1 - p0 );
    t = _t;
    near = Point(proj[0], proj[1] );
}

/////////////////////////////////////////////////////////////////
float DistancePointToLine( const Point& p0, const Point& p1, const Point& p ){
  //find the nearest point to the line
  Point nearest = ProjectPointToLine( p0, p1, p );
  float distance = Distance( nearest, p );
  return distance;
}

/////////////////////////////////////////////////////////////////
float SquareDistance( const Point& p0, const Point& p1 ){
  float ret = std::pow(p0.x - p1.x, 2) + std::pow(p0.y - p1.y, 2);
  return ret;
}

/////////////////////////////////////////////////////////////////
float Distance( const Point& p0, const Point& p1 ){
  float ret = SquareDistance(p0,p1);
  ret = std::sqrt( static_cast<float>(ret) );
  return ret;
}
/////////////////////////////////////////////////////////////////
float Clamp( float x, float a, float b ){
    return x < a ? a : ( x > b ? b : x);
}
/////////////////////////////////////////////////////////////////
float Smoothstep( float x, float low, float high ){
    //scale, and clamp x to 0..1 range
    x = Clamp( (x - low) / (high - low), 0.0, 1.0 );

    //evaluate polynomial
    x = x*x*x*(x*(x * 6 - 15) + 10);
    x = Clamp( x, 0.0f, 1.0f );
    return x;
}
/////////////////////////////////////////////////////////////////
bool Colinear( const Point& p0, const Point& p1, const Point& p2 ){
  float val = (p1.x - p0.x)*(p2.y - p0.y) - (p1.y - p0.y)*(p2.x - p0.x);
  if ( std::fabs( val ) < 0.00001f )
    return true;
  return false;
}
/////////////////////////////////////////////////////////////////
//counter-clockwise is positive in RHS coordinate system
float Angle( const Vec2f& v0, const Vec2f& v1 ){
  float dot = v0.dot(v1);
  float det = v0[0]*v1[1] - v0[1]*v1[0];
  float angle = std::atan2(det,dot);
  return angle;
}
/////////////////////////////////////////////////////////////////
//is counter-clockwise in a RHS coordinate system
bool TurnTest( const Point& p0, const Point& p1, const Point& p2 ){
  float val = (p1.x - p0.x)*(p2.y - p0.y) - (p1.y - p0.y)*(p2.x - p0.x);
  return (val > 0);
}
END_NAMESPACE_2

