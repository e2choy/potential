#include "polygon.h"
#include "clipper/clipper.hpp"

using namespace ClipperLib;
BEGIN_NAMESPACE(SSDF)
//polygon class used to compute offsets
//class Polygon{
//public:
//  typedef std::vector<Points> Paths;
//
//  Polygon( const Points& pts );
//
//  void      SetPrecision( int precision );
//  Polygon   OffsetPolygon( float offset );
//private:
//  std::vector<Points> m_paths;            //all paths must be closed
//  int                 m_precision;
//};
Polygon::Polygon( const Points& pts ){
  m_paths.push_back( pts );
}

void Polygon::SetPrecision( int precision ){
  m_precision = precision;
}

Polygon Polygon::OffsetPolygon( float offset, int precision ){

  ClipperLib::ClipperOffset clip_offset;
  for( const Points& path : m_paths ){
  }
}
END_NAMESPACE
