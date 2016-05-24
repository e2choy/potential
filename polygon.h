#pragma once

#include "stdafx.h"

BEGIN_NAMESPACE(SSDF)
//polygon class used to compute offsets
class Polygon{
public:
  typedef std::vector<Points> Paths;

  Polygon( const Points& pts );

  void      SetPrecision( int precision );
  Polygon   OffsetPolygon( float offset, int precision );
private:
  std::vector<Points> m_paths;            //all paths must be closed
  int                 m_precision;
};
END_NAMESPACE

//draw the polygon

