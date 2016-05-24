#pragma once
#include "stdafx.h"

BEGIN_NAMESPACE(SSDF)

/////////////////////////////////////////////////////////////////
class Potential{
public:
  Potential(){};
  virtual float ComputePotential( const Point& pt ) const = 0;

}; 
typedef std::vector<Potential*> Potentials;

/////////////////////////////////////////////////////////////////
class LinePotential : public Potential{
public:
  LinePotential( int degree );
  LinePotential( const Point& p0, const Point& p1, int degree = 1 );
  virtual float ComputePotential( const Point& pt ) const;
  Point GetPoint( size_t index ) const;
private:
  Points m_pts;
  int m_degree;
};
/////////////////////////////////////////////////////////////////
class CompositePotential : public Potential{
public:
  CompositePotential();
  void AddPotential( Potential* );
  virtual float ComputePotential( const Point& pt ) const;
private:
  Potentials m_pots;
};

END_NAMESPACE


