#include "polygon.h"
#include "clipper/clipper.hpp"
#include "graphics.h"

using namespace ClipperLib;
BEGIN_NAMESPACE(SSDF)

/////////////////////////////////////////////////////////////////
Polygon::Polygon(){
}
/////////////////////////////////////////////////////////////////
Polygon::Polygon( const Points& pts ){
  m_paths.push_back( pts );
}
/////////////////////////////////////////////////////////////////
void Polygon::AddPath( const Path& path ){
  m_paths.push_back( path );
}
/////////////////////////////////////////////////////////////////
const Polygon::Paths&    Polygon::GetPaths() const{
  return m_paths;
}
/////////////////////////////////////////////////////////////////
Polygon::Paths&    Polygon::GetPaths() {
  return m_paths;
}
/////////////////////////////////////////////////////////////////
Polygon Polygon::OffsetPolygon( float offset, int precision ){
  //assume canonical coordinates scaled by precision
  ClipperLib::Paths         sol;      //solution to the offset
  ClipperLib::ClipperOffset co;       //clipper offset library
  float scale = std::pow(10.0f, (float) precision);

  //iterate through all paths
  for( const Points& path : m_paths ){

    //create a single path
    ClipperLib::Path subject;
    for( const Point& pt : path ){
      ClipperLib::IntPoint intPt( 
          pt.x * scale,
          pt.y * scale
      );
      subject << intPt;
    }

    //add the path
    co.AddPath( subject, ClipperLib::jtSquare, ClipperLib::etClosedPolygon );
  }

  //run the solution
  Polygon ret;
  co.Execute( sol, offset * scale );
  for( const ClipperLib::Path& path : sol ){
    //iterate through the points
    //cout << "number of points is "<< path.size() << endl;
    Polygon::Path polyPath;
    for( const ClipperLib::IntPoint& intPt : path ){
      Point p( intPt.X / scale, intPt.Y / scale );
      polyPath.push_back( p );
    }
    ret.AddPath( polyPath );
  }
 
  return ret; 
}

END_NAMESPACE

/////////////////////////////////////////////////////////////////
BEGIN_NAMESPACE_2(SSDF,Graphics)
  void DrawPolygon( const Polygon& poly, const Pixel& color, Mat& img ){
    //iterate through all paths
    const Polygon::Paths paths = poly.GetPaths();
    for( const Polygon::Path& path : paths ){
      //iterate through all points of a path and draw it
      for( size_t i = 0; i < path.size(); ++i ){
        Point p0 = path[i];
        Point p1 = path[(i+1)%path.size()];
        Graphics::DrawLine( p0, p1, color, img ); 
      }
    }
  }
END_NAMESPACE_2
