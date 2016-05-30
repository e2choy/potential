#pragma once
#include "stdafx.h"
#include "polygon.h"
#include "potential.h"

BEGIN_NAMESPACE(SSDF)
/////////////////////////////////////////////////////////////////
class Demo{
public:
  Demo();
  virtual ~Demo();

  //set the parameters of the algorithm
  //offset = offset distance
  //A = constant offset
  //B = scaled potential offset
  void SetParameters( float offset, float A, float B );

  //create a single charged field
  void RunSimple();

  //create an implicit surface with two sets of potentials
  void Run();
private:
  //steps of our algorithm
  void  SetupMTest();
  virtual void  CreatePotentials( const Polygon& polygon, Potentials& pots ) = 0;
  void  CreateMasks();

  void  ProcessImage();
  void  ProcessPixel( int x, int y );
  virtual float ComputeDistance( const Potentials& pots, const Point& pt ) = 0;

  void  ShowImages();

  size_t    m_width;
  size_t    m_height;
  Mat                 m_img;        //image to show 4 channel (RGBA)
  Mat                 m_combDist;   //created field (float)
  Mat                 m_combWeight; //mapping to weights

  Polygon             m_intPoly;        //interior contour
  Mat                 m_intMask;        //mask of interior contour (int)
  Potentials          m_intPots;        //interior potentials 
  Mat                 m_intDist;        //interior distance of potentials

  Polygon             m_extPoly;        //exterior contour
  Mat                 m_extMask;        //mask of exterior contour (int)
  Potentials          m_extPots;        //interior potentials 
  Mat                 m_extDist;        //ext distance of potentials
private:
  //parameters of the algorithm
  float               m_offset;
  float               m_A;
  float               m_B;
};
/////////////////////////////////////////////////////////////////
class DlDemo : public Demo{
public:
  DlDemo( int degree );
  virtual void  CreatePotentials( const Polygon& polygon, Potentials& pots );
  virtual float ComputeDistance( const Potentials& pots, const Point& pt );
private:
  int       m_degree;               //degree of the potentials
};
/////////////////////////////////////////////////////////////////
class SlDemo : public Demo{
public:
  SlDemo( int degree );
  virtual void  CreatePotentials( const Polygon& polygon, Potentials& pots );
  virtual float ComputeDistance( const Potentials& pots, const Point& pt );
private:
  int       m_degree;               //degree of the potentials
};
END_NAMESPACE
