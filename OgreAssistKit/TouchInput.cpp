/*
 Copyright (C) 2012 Duncan Sung W. Kim (duncansungwkim.blogspot.com)
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 
 */
#include "TouchInput.h"


namespace OgreAssistKit
{


TouchInput::TouchInput( float a_fWidth, float a_fHeight, ::Ogre::OrientationMode a_ort ) :
    m_fWidth(a_fWidth), m_fHeight(a_fHeight), m_ort(a_ort), m_pLsnr(NULL)
{
    DecideToSwapWidthAndHeight( a_ort ) ;
}



void TouchInput::set_Orientation( ::Ogre::OrientationMode a_ort )
{
    if( m_ort == a_ort )
        return ;
    
    m_ort = a_ort ;
    
    DecideToSwapWidthAndHeight( a_ort ) ;
}



void TouchInput::DecideToSwapWidthAndHeight( ::Ogre::OrientationMode a_newOrt )
{
    if( ::Ogre::OR_PORTRAIT==a_newOrt || ::Ogre::OR_DEGREE_180==a_newOrt )
    {
        if( m_fWidth > m_fHeight )
        {
            std::swap( m_fWidth, m_fHeight ) ;
        }
        return ;
    }

    if( ::Ogre::OR_LANDSCAPELEFT==a_newOrt || ::Ogre::OR_LANDSCAPERIGHT==a_newOrt )
    {
        if( m_fWidth < m_fHeight )
        {
            std::swap( m_fWidth, m_fHeight ) ;
        }
        return ;        
    }
}



void TouchInput::AddTouch( float a_fX, float a_fY )
{
    switch( m_ort )
    {
    case ::Ogre::OR_LANDSCAPELEFT :
        std::swap( a_fX, a_fY ) ;
        a_fY = m_fHeight - a_fY ;
        break ;
        
    case ::Ogre::OR_LANDSCAPERIGHT :
        std::swap( a_fX, a_fY ) ;
        a_fX = m_fWidth - a_fX ;
        break ;
            
    case ::Ogre::OR_DEGREE_180 :
        a_fX = m_fWidth - a_fX ;
        a_fY = m_fHeight - a_fY ;
        break ;
            
    default : ;
    }
    
    //::fprintf( stderr, "%i,%i\n", (int)a_fX, (int)a_fY ) ;
    m_curTouches.push_back( ::Ogre::Vector2(a_fX/m_fWidth, a_fY/m_fHeight) ) ;
}




} // namespace OgreAssistKit
