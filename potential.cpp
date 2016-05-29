#include "stdafx.h"
#include "potential.h"
#include "util.h"

BEGIN_NAMESPACE(SSDF)
/////////////////////////////////////////////////////////////////
LinePotential::LinePotential( int degree ) : m_degree( degree ){
}

/////////////////////////////////////////////////////////////////
LinePotential::LinePotential( const Point& p0, const Point& p1, int degree):m_degree(degree){
  m_pts.push_back( p0 );
  m_pts.push_back( p1 );
}

/////////////////////////////////////////////////////////////////
Point LinePotential::GetPoint( size_t index ) const{
  assert( index < m_pts.size() );
  return m_pts[index];
}

/////////////////////////////////////////////////////////////////
float LinePotential::ComputePotential( const Point& p ) const{
  assert( m_pts.size() == 2 );

  //compute the distance from point to line
  Point p0 = m_pts[0];
  Point p1 = m_pts[1];
  Point near;
  float t;
  Math::ProjectPointToLine( p0, p1, p, near, t );

  float x0 = -Math::Distance(p0, near);
  if( t < 0.0f || t > 1.0f ) x0 = fabs(x0);
  float x1 = Math::Distance(p1, near);
  float y = Math::Distance( near, p );
  
  //compute the potential
  switch( m_degree){
    case 1:
      {
        //linear newtonian potential
        float a1 =2.0* (x1 + sqrt( x1*x1 + y*y ));
        float a0 =2.0* (x0 + sqrt( x0*x0 + y*y ));
        float a = std::log(std::fabs(a1)) - std::log(std::fabs(a0));
        return fabs(a);
      }
      break;
    case 2:
      {
        //quadratic potential
        float a0, a1, a;
        //if( y != 0.0f ){
        if( fabs(y) > 0.00005f ){
          a1 = atan( x1 / y ) / y;
          a0 = atan( x0 / y ) / y;
          a = a1 - a0;
        }else if( t<0.0f || t> 1.0f){
          a1 = -1.0f/x1;
          a0 = -1.0f/x0;
          a = a1 - a0;
        }else{
          a = std::numeric_limits<float>::infinity();
        }
        return fabs(a);
      }
      break;
    case 3:
      {
        //cubic potential
        float a0, a1, a;
        if( fabs(y) > 0.00005f ){
          a1 = x1/(y*y*sqrt(x1*x1 + y*y));
          a0 = x0/(y*y*sqrt(x0*x0 + y*y));
          a = a1 - a0;
        }else if( t<0.0f || t> 1.0f){
          a1 = -1.0f/(2.0f*x1*x1);
          a0 = -1.0f/(2.0f*x0*x0);
          a = a1 - a0;
        }else{
          a = std::numeric_limits<float>::infinity();
        }
        return fabs(a);
      }
    default:
      {
        assert(false);
      }
      break;
  };
  assert(false);
  return 0.0f;
}
/////////////////////////////////////////////////////////////////
float LinePotential::ComputeDistance( const Point& pt ) const{
  float pot = ComputePotential( pt );
  float dist = std::pow(1.0f / pot, 1.0f/(float)m_degree);
  return dist;
}
/////////////////////////////////////////////////////////////////
CompositePotential::CompositePotential( int degree ):m_degree(degree){
}
/////////////////////////////////////////////////////////////////
void CompositePotential::SetDegree( int degree ){
  m_degree = degree;
}
/////////////////////////////////////////////////////////////////
void CompositePotential::AddPotential( Potential* p ){
  m_pots.push_back( p );
}

/////////////////////////////////////////////////////////////////
float CompositePotential::ComputePotential( const Point& pt ) const{
  float total = 0.0f;
  for( Potential* p : m_pots ){
    total += p->ComputePotential( pt );
  }
  return total;
}
/////////////////////////////////////////////////////////////////
float CompositePotential::ComputeDistance( const Point& pt ) const{
  float pot = ComputePotential( pt );
  float dist = std::pow(1.0f / pot, 1.0f/(float)m_degree);
  return dist;
}
/////////////////////////////////////////////////////////////////
DlLinePotential::DlLinePotential( int degree ):m_degree(degree){
}
/////////////////////////////////////////////////////////////////
DlLinePotential::DlLinePotential( const Point& p0, const Point& p1, int degree ):
m_degree(degree){
  m_pts.push_back(p0);
  m_pts.push_back(p1);
}
/////////////////////////////////////////////////////////////////
float DlLinePotential::ComputePotential( const Point& pt ) const{
  assert( m_pts.size() == 2 );
  Point p0 = m_pts[0];
  Point p1 = m_pts[1];
  //a and b are distances from point x to a and x to b
  //ang is the angle between xa and xb

	//first check if colinear
	if ( Math::Colinear( p0, p1, pt ) ){
		Point near;
		float t;
    Math::ProjectPointToLine( p0, p1, pt, near, t );
		if ( t >= 0.0f && t <= 1.0f )
			return std::numeric_limits<float>::infinity();
		return 0.0f;
	}

  Vec2f xa = p0 - pt;
  Vec2f xb = p1 - pt;
  float a = cv::norm( xa );
  float b = cv::norm( xb );
  float ang = std::abs(Math::Angle( xa, xb ));
  float t = std::tan( ang / 2.0f );
  float val = (1/a + 1/b) * t;

  //compute differently depending on degree of potential

  bool cw = Math::TurnTest( p0, p1, pt );
  if ( cw ) val *= -1;
  return val;
}
/////////////////////////////////////////////////////////////////
float DlLinePotential::ComputeDistance( const Point& pt ) const{
  float potential = ComputePotential( pt );
  float dist = 1.0f/potential;
  return dist;
}
/////////////////////////////////////////////////////////////////
Point DlLinePotential::GetPoint( size_t index ) const{
  Point pt;
  return pt;
}
END_NAMESPACE

