#pragma once
#ifndef __OgreAssistKit_TouchInput_h__
#define __OgreAssistKit_TouchInput_h__
namespace OgreAssistKit
{


typedef std::vector< ::Ogre::Vector2 > Touches_t ;
class TouchInput ;

class TouchListener
{
public:
    virtual void OnTouchesBegun( TouchInput* a_pSender, const Touches_t& a_curTouches, const Touches_t& a_oldTouches ) {}
    virtual void OnTouchesMoved( TouchInput* a_pSender, const Touches_t& a_curTouches, const Touches_t& a_oldTouches ) {}
    virtual void OnTouchesEnd( TouchInput* a_pSender, 
                               const Touches_t& a_curTouches, const Touches_t& a_oldTouches, unsigned a_uTapCount ) {}
    virtual void OnTouchesCancelled( TouchInput* a_pSender ) {}
};



class TouchInput
{
// Construction and Destruction
public:
    TouchInput( float a_fWidth, float a_fHeight, ::Ogre::OrientationMode a_ort ) ;



// Methods
public:
    void SetListener( TouchListener* pLsnr ) ;
    ::Ogre::Vector2 ToPixels( const ::Ogre::Vector2& coord ) const ;



// Properties
public:
    void set_Orientation( ::Ogre::OrientationMode ort ) ;
    float get_fAreaWidth() const { return m_fWidth ; }
    float get_fAreaHeight() const { return m_fHeight ; }


    
// For @class OgreAssistKit_UIWindow
public:
    void AddTouch( float fX, float fY ) ;
    void OnBeginning() ;
    void OnBegun() ;
    void OnMoving() ;
    void OnMoved() ;
    void OnEnding() ;
    void OnEnded( unsigned uTapCount ) ;
    void OnCancelled() ;

// Types
public:



// Private Subroutines
private:
    void DecideToSwapWidthAndHeight( ::Ogre::OrientationMode a_newOrt ) ;



// Attributes
private:
    float m_fWidth, m_fHeight ;
    ::Ogre::OrientationMode m_ort ;
    Touches_t m_curTouches ;
    Touches_t m_oldTouches ;
    TouchListener* m_pLsnr ;
};

    
// Inline Routines
    
inline void TouchInput::SetListener( OgreAssistKit::TouchListener* a_pLsnr )
{
    m_pLsnr = a_pLsnr ;
}


inline ::Ogre::Vector2 TouchInput::ToPixels( const ::Ogre::Vector2& a_coord ) const
{
    return ::Ogre::Vector2( a_coord.x * m_fWidth, a_coord.y * m_fHeight ) ;
}


inline void TouchInput::OnCancelled()
{
    if( NULL != m_pLsnr )
        m_pLsnr->OnTouchesCancelled( this ) ;
}


inline void TouchInput::OnBeginning()
{
    m_curTouches.resize(0) ;
    m_oldTouches.resize(0) ;    
}


inline void TouchInput::OnBegun()
{
    if( NULL != m_pLsnr )
        m_pLsnr->OnTouchesBegun( this, m_curTouches, m_oldTouches ) ;
}


inline void TouchInput::OnMoving()
{
    m_curTouches.swap( m_oldTouches ) ;
    m_curTouches.resize(0) ; 
}


inline void TouchInput::OnMoved()
{
    if( NULL != m_pLsnr )
        m_pLsnr->OnTouchesMoved( this, m_curTouches, m_oldTouches ) ;
}


inline void TouchInput::OnEnding()
{
    m_curTouches.swap( m_oldTouches ) ;
    m_curTouches.resize(0) ;
}


inline void TouchInput::OnEnded( unsigned a_uTapCount )
{
    if( NULL != m_pLsnr )
        m_pLsnr->OnTouchesEnd( this, m_curTouches, m_oldTouches, a_uTapCount ) ;
}


} //namespace OgreAssistKit
#endif
