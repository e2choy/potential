#pragma once
#include "stdafx.h"
#include "potential.h"

BEGIN_NAMESPACE(SSDF)
class Demo{

public:
  Demo();
  void Run();

private:
  void SetupMTest();
  void ProcessImage();
  void ProcessPixel( int x, int y );
  void OffsetPolygon();

  int m_width;
  int m_height;
  Mat m_img;
  CompositePotential  m_compPot;
  Potentials          m_pots;
};
END_NAMESPACE
