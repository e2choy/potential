#pragma once

#include "stdafx.h"
#include "pixel.h"

BEGIN_NAMESPACE(SSDF)
//polygon class used to compute offsets
class Polygon{
public:
  typedef std::vector<Points> Paths;
  typedef Points Path;

  Polygon();
  Polygon( const Points& pts );


  void            AddPath( const Path& path );
  Polygon         OffsetPolygon( float offset, int precision );
  const Paths&    GetPaths() const;
  Paths&          GetPaths();
private:
  std::vector<Points> m_paths;            //all paths must be closed
};
END_NAMESPACE

//draw the polygon
BEGIN_NAMESPACE_2(SSDF,Graphics)
  void DrawPolygon( const Polygon& poly, const Pixel& color, Mat& img );
END_NAMESPACE_2

