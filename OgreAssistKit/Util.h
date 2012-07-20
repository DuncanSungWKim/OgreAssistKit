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

void DollyCamera( ::Ogre::Camera* pCam, const::Ogre::Vector2& aim,
                  ::Ogre::Vector2 curTouch1, ::Ogre::Vector2 curTouch2,
                  ::Ogre::Vector2 oldTouch1, ::Ogre::Vector2 oldTouch2,
                  float a_fDistRate = 500.0f ) ;
    

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
