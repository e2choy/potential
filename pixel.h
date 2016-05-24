#pragma once
#include "stdafx.h"

class Pixel : public cv::Scalar{
public:
    Pixel(){}
    Pixel( int b, int g, int r, int a ):cv::Scalar(b,g,r,a){}
    Pixel( int b, int g, int r ):cv::Scalar(b,g,r,255){}
    Pixel( const cv::Scalar& rhs):cv::Scalar(rhs){}
    Pixel( const cv::Vec4b& c ):cv::Scalar(c[0],c[1],c[2],c[3]){}

    cv::Vec4b     ToVec4b() const;
    operator      cv::Vec4b() const { return ToVec4b(); }
public:
    static const Pixel WHITE;
    static const Pixel GRAY;
    static const Pixel BLACK;
    static const Pixel BLUE;
    static const Pixel GREEN;
    static const Pixel RED;
    static const Pixel VIOLET;
    static const Pixel PURPLE;
    static const Pixel CYAN;
    static const Pixel YELLOW;
    static const Pixel ORANGE;
};

