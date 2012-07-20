/*
 Copyright (C) 2012 Duncan Sung W. Kim (duncansungwkim.blogspot.com)
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 */
#pragma once
#ifndef __OgreAssistKit_Util_h__
#define __OgreAssistKit_Util_h__

// Common Headers
#include <OgreRoot.h>
#include <OgreStringConverter.h>
//*/

namespace OgreAssistKit
{



void GetNativeWidthHeight( int iHandle, unsigned int& uWidth, unsigned int& uHeight ) ;

void PanCamera( ::Ogre::Camera* pCam, const ::Ogre::Vector3& subjCenter,
                const ::Ogre::Vector2& curTouch, const ::Ogre::Vector2& oldTouch ) ;


    
inline void DollyCamera( ::Ogre::Camera* a_pCam, const::Ogre::Vector2& a_aim,
                         float a_fDistance )
{
    ::Ogre::Ray ray ;
    a_pCam->getCameraToViewportRay( a_aim.x, a_aim.y, &ray ) ;
    a_pCam->moveRelative( ray.getDirection() * a_fDistance ) ;
}



inline float DiffDistance( const ::Ogre::Vector2 a_curTouch1, const ::Ogre::Vector2 a_curTouch2,
                           const ::Ogre::Vector2 a_oldTouch1, const ::Ogre::Vector2 a_oldTouch2 )
{
    float fCurDist = a_curTouch1.distance( a_curTouch2 ) ;
    float fOldDist = a_oldTouch1.distance( a_oldTouch2 ) ;
    float fDistDiff = fCurDist - fOldDist ;
    return fDistDiff ;
}



inline 
::Ogre::RenderWindow* 
    CreateRenderWindowWithNative( ::Ogre::Root* a_pRoot, int a_iHandle,
                                  const char* a_pTitle = "Main RenderWindow" )
{
    ::Ogre::NameValuePairList miscParam ;
    miscParam["externalWindowHandle"] = ::Ogre::StringConverter::toString( a_iHandle ) ;
    unsigned int uWidth, uHeight ;
    GetNativeWidthHeight( a_iHandle, uWidth, uHeight ) ;
    return a_pRoot->createRenderWindow( a_pTitle, uWidth, uHeight, false, &miscParam ) ;
}


    
} // namespace OgreAssistKit
#endif // __OgreAssistKit_Util_h__
