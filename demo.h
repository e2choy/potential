#pragma once
#include "stdafx.h"
#include "polygon.h"
#include "potential.h"

BEGIN_NAMESPACE(SSDF)
class Demo{

public:
  Demo();
  ~Demo();

  //create an implicit surface with two sets of potentials
  void Run();

  //create a single charged field
  void RunSimple();

private:
  //steps of our algorithm
  void  SetupMTest();
  void  CreatePotential( const Polygon& polygon, Potentials& pots );
  void  CreateMasks();

  void  ProcessImage();
  void  ProcessPixel( int x, int y );
  float ComputeDistance( const Potentials& pots, const Point& pt );

  void  ShowImages();

  size_t    m_width;
  size_t    m_height;
  int       m_degree;               //degree of the potentials
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
};
END_NAMESPACE
