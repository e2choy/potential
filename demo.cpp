#include "stdafx.h"
#include "demo.h"
#include "pixel.h"
#include "graphics.h"
#include "polygon.h"
#include "color.h"
#include "util.h"

BEGIN_NAMESPACE(SSDF)

/////////////////////////////////////////////////////////////////
Demo::Demo(){
  m_width = 400;
  m_height = 400;
  m_offset = 0.07;
  m_A = 0.0f;
  m_B = 0.5f;
}
/////////////////////////////////////////////////////////////////
Demo::~Demo(){
  for( Potential* p : m_intPots ){
    delete p;
  }
  for( Potential* p : m_extPots ){
    delete p;
  }
}
/////////////////////////////////////////////////////////////////
void Demo::SetParameters( float offset, float A, float B ){
  m_offset = offset;
  m_A = A;
  m_B = B;
}

/////////////////////////////////////////////////////////////////
void Demo::RunSimple(){
  //demonstration
  Potential* pot = new DlLinePotential( Point(0.25,0.5), Point(0.75,0.5), 3 );
  //Potential* pot = new LinePotential( Point(0.25,0.5), Point(0.75,0.5), 1 );
  m_combDist = Mat( m_height, m_width, CV_32F, cv::Scalar(-1.0f));
  for( size_t y = 0; y < m_height; ++y ){
    for( size_t x = 0; x < m_width; ++x ){
      Point pt(x/(float)m_width, y/(float)m_height);
      float dist = pot->ComputeDistance( pt );
      m_combDist.at<float>(y,x) = dist;
      //m_combDist.at<float>(y,x) = 1.0f/pot->ComputePotential( 
      //    Point(x/(float)m_width, y/(float)m_height) );
      //m_combDist.at<float>(y,x) = Math::DistancePointToLine( Point(0,0.5),Point(1,0.5),pt );
    }
  }

  //get derivatives value at 0.5,0.5
  float deriv = Math::FiniteDifferences(
      pot->ComputeDistance(Point(0.5,0.5001-0.0001f)),
      pot->ComputeDistance(Point(0.5,0.5001+0.0001f)),
      0.0001f
      );
  cout << "derivative is " << deriv << endl;
  cv::imshow("combDist", m_combDist );
  Mat combIso;
  Graphics::DrawIsocontours( m_combDist, combIso, 32.0 );
  cv::imshow( "combIso",combIso);
  cv::imwrite("combIso.png", combIso );
  delete pot;
}
/////////////////////////////////////////////////////////////////
void Demo::Run(){
  //create the images
  m_img = Mat( m_height, m_width, CV_8UC4, Pixel::CYAN );
  m_combDist = Mat( m_height, m_width, CV_32F, cv::Scalar(-1.0f));
  m_intDist = Mat( m_height, m_width, CV_32F, cv::Scalar(-1.0f));
  m_intMask = Mat( m_height, m_width, CV_32F, cv::Scalar(-1.0f) );

  m_extDist = Mat( m_height, m_width, CV_32F, cv::Scalar(-1.0f));
  m_extMask = Mat( m_height, m_width, CV_32F, cv::Scalar(-1.0f) );

  SetupMTest();
  ProcessImage();
  ShowImages();
}
/////////////////////////////////////////////////////////////////
void Demo::SetupMTest(){
  //create the potentials
  Points pts;
  pts.push_back( Point(0.2f,0.2f) );
  pts.push_back( Point(0.8f,0.2f) );
  pts.push_back( Point(0.8f,0.8f) );
  pts.push_back( Point(0.6f,0.8f) );
  pts.push_back( Point(0.6f,0.4f) );
  pts.push_back( Point(0.4f,0.4f) );
  pts.push_back( Point(0.4f,0.8f) );
  pts.push_back( Point(0.2f,0.8f) );

  //LinePotential* pot = new LinePotential( Point(0.25,0.5), Point(0.75,0.5), 2 );
  //m_compPot.AddPotential( pot );

  //create the interior and exterior contours
  m_intPoly = Polygon( pts );
  m_extPoly = m_intPoly.OffsetPolygon( m_offset, 3 );

  //create the potentials
  CreatePotentials( m_intPoly, m_intPots );
  CreatePotentials( m_extPoly, m_extPots );

  //create masks
  CreateMasks();
}
/////////////////////////////////////////////////////////////////
void Demo::CreateMasks(){
  //show mask
  Graphics::FillPolygon( m_intPoly, cv::Scalar(1), m_intMask );
  Graphics::FillPolygon( m_extPoly, cv::Scalar(1), m_extMask );
}
/////////////////////////////////////////////////////////////////
void Demo::ProcessImage(){
  //compute the potentials for the entire image
  for( size_t y = 0; y < m_height; ++y ){
    for( size_t x = 0; x < m_width; ++x ){
      ProcessPixel( x, y );
    }
  }
}
/////////////////////////////////////////////////////////////////
void Demo::ProcessPixel( int x, int y ){
  //compute the potential of the interior and exterior contour
  //and blend together

  //compute the interior distance
  Point pt ( x/(float)m_width, y/(float)m_height );
  float intDist = ComputeDistance( m_intPots, pt );
  //compute the sign using the mask
  if( m_intMask.at<float>( y, x ) > 0.5f ){
    intDist *= -1.0f;
  }
  m_intDist.at<float>( y, x ) = intDist;
  

  //compute the exterior distance
  float extDist = ComputeDistance( m_extPots, pt );
  //compute the sign using the mask
  if( m_extMask.at<float>( y, x ) < 0.5f ){
    extDist *= -1.0f;
  }
  m_extDist.at<float>( y, x ) = extDist;

  //compute the blended distance
  float dI = intDist;
  float dE = extDist;
  float   ratio = dI / (dI + dE);
  float   distE = -1.0f*(m_A + dE * m_B);
  float   distI = m_A + dI * m_B;

  //if( dI < 0.0f ) ratio = 0.0f;
  //if( dE < 0.0f ) ratio = 1.0f;

  //compute the distance to the midway contour
  float dist =  Math::Smoothstep( ratio )*distI + 
                Math::Smoothstep( 1 - ratio )*distE;
  m_combDist.at<float>( y, x ) = dist;
}
/////////////////////////////////////////////////////////////////
void Demo::ShowImages(){
  //show image
  Graphics::MatFltToRGBA( m_combDist, m_img );
  Graphics::DrawPolygon( m_intPoly, Pixel::BLUE, m_img );
  Graphics::DrawPolygon( m_extPoly, Pixel::RED, m_img );
  cv::imshow( "img",m_img );
  cv::imshow( "combDist", m_combDist );
  Mat combIso;
  Graphics::DrawIsocontours( m_combDist, combIso, 32.0 );
  //Graphics::DrawPolygon( m_intPoly, Pixel::BLUE, combIso );
  //Graphics::DrawPolygon( m_extPoly, Pixel::RED, combIso );
  cv::imshow( "combIso",combIso);
  //cv::imwrite("img.png", m_img);

  //show interior contour
  Mat intIso;
  Graphics::DrawIsocontours( m_intDist, intIso, 32.0 );
  cv::imshow( "intIso",intIso );
  cv::imshow( "intDist",m_intDist);
  //cv::imshow( "intPolyMask",m_intMask ); 
  //cv::imwrite("intIso.png", intIso);

  //show exterior contour
  Mat extIso;
  Graphics::DrawIsocontours( m_extDist, extIso, 32.0 );
  cv::imshow( "extIso",extIso);
  cv::imshow( "extDist",m_extDist);
  //cv::imshow( "extPolyMask", m_extMask );
}


/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
DlDemo::DlDemo( int degree ):m_degree(degree){
}
/////////////////////////////////////////////////////////////////
void  DlDemo::CreatePotentials( const Polygon& polygon, Potentials& pots ){
  for( const Polygon::Path& path : polygon.GetPaths()){
    for( size_t i = 0; i < path.size(); ++i ){
      Potential* pot = new DlLinePotential( path[i], path[(i+1)%path.size()], m_degree );
      pots.push_back( pot );
    }
  }
}
/////////////////////////////////////////////////////////////////
float DlDemo::ComputeDistance( const Potentials& pots, const Point& pt ){
  float total = 0.0f;
  for( Potential* p : pots ){
    total += p->ComputePotential( pt );
  }
  float pot = total;
  //normalize depending on degree
  float norm = 0.0f;
  switch( m_degree ){
    case 1:
      norm = 2.0f;
      break;
    case 3:
      norm = 4.0/3.0;
      break;
    default:
      assert( false );
      throw std::exception();
      break;
  };

  float dist = std::pow(std::abs(pot/norm), -1.0f/m_degree);
  return dist;
}


/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
SlDemo::SlDemo( int degree ):m_degree(degree){
}
/////////////////////////////////////////////////////////////////
void SlDemo::CreatePotentials( const Polygon& polygon, Potentials& pots ){
  for( const Polygon::Path& path : polygon.GetPaths()){
    for( size_t i = 0; i < path.size(); ++i ){
      Potential* pot = new LinePotential( path[i], path[(i+1)%path.size()], m_degree );
      pots.push_back( pot );
    }
  }
}
/////////////////////////////////////////////////////////////////
float SlDemo::ComputeDistance( const Potentials& pots, const Point& pt ){
  float total = 0.0f;
  for( Potential* p : pots ){
    total += p->ComputePotential( pt );
  }
  float pot = total;
  float dist = std::pow(1.0f / pot, 1.0f/(float)m_degree);
  return dist;
}
END_NAMESPACE

