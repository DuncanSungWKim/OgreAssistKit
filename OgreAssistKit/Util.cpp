/*
 Copyright (C) 2012 Duncan Sung W. Kim (duncansungwkim.blogspot.com)
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 
 */

// Common Headers
#include <OgreCamera.h>
//*/

#include "Util.h"

namespace OgreAssistKit
{



void PanCamera( ::Ogre::Camera* a_pCam, const ::Ogre::Vector3& a_subjCenter,
                const ::Ogre::Vector2& a_curTouch, const ::Ogre::Vector2& a_oldTouch )
{
    ::Ogre::Plane planeThruSubj( a_pCam->getDirection(), a_subjCenter ) ;
    
    ::Ogre::Ray ray ;
    a_pCam->getCameraToViewportRay( a_curTouch.x, a_curTouch.y, &ray ) ;
    ::Ogre::Vector3 curPoint = ray.getPoint( ray.intersects( planeThruSubj ).second ) ;
    
    a_pCam->getCameraToViewportRay( a_oldTouch.x, a_oldTouch.y, &ray ) ;
    ::Ogre::Vector3 oldPoint = ray.getPoint( ray.intersects( planeThruSubj ).second ) ;
    
    ::Ogre::Vector3 move = oldPoint - curPoint ;
    a_pCam->moveRelative( move ) ;
}



} // namespace OgreAssistKit
