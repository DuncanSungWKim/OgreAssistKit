
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
