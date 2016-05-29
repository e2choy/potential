#pragma once
#include "stdafx.h"

BEGIN_NAMESPACE(SSDF)

/////////////////////////////////////////////////////////////////
class Potential{
public:
  Potential(){};
  virtual float ComputePotential( const Point& pt ) const = 0;
  virtual float ComputeDistance( const Point& pt ) const = 0;
  virtual ~Potential(){}
}; 
typedef std::vector<Potential*> Potentials;

/////////////////////////////////////////////////////////////////
class LinePotential : public Potential{
public:
  LinePotential( int degree );
  LinePotential( const Point& p0, const Point& p1, int degree = 1 );
  virtual float ComputePotential( const Point& pt ) const;
  virtual float ComputeDistance( const Point& pt ) const;
  Point GetPoint( size_t index ) const;
private:
  Points m_pts;
  int m_degree;
};
/////////////////////////////////////////////////////////////////
class CompositePotential : public Potential{
public:
  CompositePotential( int degree = 1);
  void SetDegree( int degree );
  void AddPotential( Potential* );
  virtual float ComputePotential( const Point& pt ) const;
  virtual float ComputeDistance( const Point& pt ) const;
private:
  Potentials m_pots;
  int m_degree;
};
/////////////////////////////////////////////////////////////////
class DlLinePotential : public Potential{
public:
  DlLinePotential( int degree );
  DlLinePotential( const Point& p0, const Point& p1, int degree = 1 );
  virtual float ComputePotential( const Point& pt ) const;
  virtual float ComputeDistance( const Point& pt ) const;
  Point GetPoint( size_t index ) const;
private:
  Points m_pts;
  int m_degree;
};

END_NAMESPACE


