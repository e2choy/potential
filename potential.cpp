#include "stdafx.h"
#include "potential.h"
#include "util.h"

BEGIN_NAMESPACE(SSDF)

LinePotential::LinePotential( int degree ) : m_degree( degree ){
}

LinePotential::LinePotential( const Point& p0, const Point& p1, int degree):m_degree(degree){
  m_pts.push_back( p0 );
  m_pts.push_back( p1 );
}

Point LinePotential::GetPoint( size_t index ) const{
  assert( index < m_pts.size() );
  return m_pts[index];
}

float LinePotential::ComputePotential( const Point& p ) const{
  assert( m_pts.size() == 2 );

  //compute the distance from point to line
  Point p0 = m_pts[0];
  Point p1 = m_pts[1];
  Point near = Math::ProjectPointToLine( p0, p1, p );
  float x0 = Math::Distance(p0, near);
  float x1 = Math::Distance(p1, near);
  float y = Math::Distance( near, p );
  
  //compute the potential
  switch( m_degree){
    case 1:
      {
        //linear newtonian potential
        float a1 = x1 + sqrt( x1*x1 + y*y );
        float a0 = x0 + sqrt( x0*x0 + y*y );
        float a = std::log(std::fabs(a1)) - std::log(std::fabs(a0));
        return a;
      }
      break;
    case 2:
      {
        //quadratic potential
      }
      break;
    case 3:
      {
        //cubic potential
      }
    case 4:
      {
      }
      break;
    default:
      {
        assert(false);
      }
      break;
  };
  return 0.0f;
}

/////////////////////////////////////////////////////////////////
CompositePotential::CompositePotential(){
}

void CompositePotential::AddPotential( Potential* p ){
  m_pots.push_back( p );
}

float CompositePotential::ComputePotential( const Point& pt ) const{
  float total = 0.0f;
  for( Potential* p : m_pots ){
    total += p->ComputePotential( pt );
  }
  return total;
}

END_NAMESPACE

