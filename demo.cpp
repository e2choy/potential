#include "stdafx.h"
#include "demo.h"
#include "pixel.h"
#include "graphics.h"

BEGIN_NAMESPACE(SSDF)
Demo::Demo(){
  m_width = 400;
  m_height = 400;
}

void Demo::Run(){

  //create the potentials
  SetupMTest();
  ProcessImage();
}

void Demo::SetupMTest(){
  Points pts;
  pts.push_back( Point(0.2f,0.2f) );
  pts.push_back( Point(0.8f,0.2f) );
  pts.push_back( Point(0.8f,0.8f) );
  pts.push_back( Point(0.6f,0.8f) );
  pts.push_back( Point(0.6f,0.4f) );
  pts.push_back( Point(0.4f,0.4f) );
  pts.push_back( Point(0.4f,0.8f) );
  pts.push_back( Point(0.2f,0.8f) );

  //create a line potential for each point
  //of the line segment
  int degree = 1;
  for( size_t i = 0; i < pts.size(); ++i ){
    LinePotential* pot = new LinePotential( pts[i], pts[(i+1)%pts.size()], degree);
    m_compPot.AddPotential( pot );
    m_pots.push_back( pot );
  }
}

void Demo::ProcessImage(){
  //create the image of the appropriate size
  m_img = Mat( m_height, m_width, CV_8UC4, Pixel::CYAN );

  //compute the potentials for the entire image
  for( size_t y = 0; y < m_height; ++y ){
    for( size_t x = 0; x < m_width; ++x ){
    }
  }

  //draw the line segments of the image
  for( Potential* pot : m_pots ){
    LinePotential* lpot = dynamic_cast<LinePotential*>( pot );
    Point p0 = lpot->GetPoint( 0 );
    Point p1 = lpot->GetPoint( 1 );
    Graphics::DrawLine( p0, p1, Pixel::BLACK, m_img );

  }

  //show the image
  cv::imshow( "img", m_img );
}

END_NAMESPACE

