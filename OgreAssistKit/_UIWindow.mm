
#import "_UIWindow.h"

#include "TouchInput.h"

using namespace OgreAssistKit ;



@implementation OgreAssistKit_UIWindow


-(id) initWithFrame:(CGRect)a_rcFrame
{
    self = [super initWithFrame:a_rcFrame];
    if( nil == self ) 
        return nil ;
    
    // Initialization code
    self.multipleTouchEnabled = YES ;
    
    UIDeviceOrientation ort = [ UIDevice currentDevice ].orientation ;
    m_pTouchInput = new OgreAssistKit::TouchInput( a_rcFrame.size.width, a_rcFrame.size.height, ToOgre(ort) ) ;
    if( NULL == m_pTouchInput )
        return nil ;
    
    return self;
}



void CleanUpOgre( OgreAssistKit_UIWindow* a_oSelf )
{
    if( NULL == a_oSelf->m_pTouchInput )
        return ;
    
    delete a_oSelf->m_pTouchInput ;
    a_oSelf->m_pTouchInput = NULL ;
}



-(void) dealloc
{
    CleanUpOgre( self ) ;
    [ super dealloc ] ;
}



-(void) touchesBegan:(NSSet*)a_oTouches withEvent:(UIEvent*)a_oEv
{
    m_pTouchInput->OnBeginning() ;
    
    NSArray* oTouches = [ [a_oEv allTouches] allObjects ] ;
    
    for( UITouch* oTouch in oTouches )
    {
        CGPoint pt = [ oTouch locationInView:self ] ;
        //NSLog( @"%i, %i\n", (int)pt.x, (int)pt.y ) ;
        m_pTouchInput->AddTouch( pt.x, pt.y ) ;
    }
    
    m_pTouchInput->OnBegun() ;
}



-(void) touchesMoved:(NSSet*)a_oTouches withEvent:(UIEvent*)a_oEv
{
    m_pTouchInput->OnMoving() ;
    
    NSArray* oTouches = [ [a_oEv allTouches] allObjects ] ;
    
    for( UITouch* oTouch in oTouches )
    {
        CGPoint pt = [ oTouch locationInView:self ] ;
        //NSLog( @"%i, %i\n", (int)pt.x, (int)pt.y ) ;
        m_pTouchInput->AddTouch( pt.x, pt.y ) ;
    }
    
    m_pTouchInput->OnMoved() ;
}



-(void) touchesEnded:(NSSet*)a_oTouches withEvent:(UIEvent*)a_oEv
{
    m_pTouchInput->OnEnding() ;

    NSArray* oTouches = [ [a_oEv allTouches] allObjects ] ;
    
    for( UITouch* oTouch in oTouches )
    {
        CGPoint pt = [ oTouch locationInView:self ] ;
        //NSLog( @"%i, %i\n", (int)pt.x, (int)pt.y ) ;
        m_pTouchInput->AddTouch( pt.x, pt.y ) ;
    }
    
    UITouch* oFirstTouch = [oTouches objectAtIndex:0] ;
    m_pTouchInput->OnEnded( oFirstTouch.tapCount ) ;    
}



-(void) touchesCancelled:(NSSet*)a_oTouches withEvent:(UIEvent*)a_oEv
{
    m_pTouchInput->OnCancelled() ;
}


@end



namespace OgreAssistKit
{


static ::Ogre::OrientationMode sg_curOrt = ::Ogre::OR_DEGREE_0 ;
    
::Ogre::OrientationMode ToOgre( UIDeviceOrientation a_ort )
{
    switch ( a_ort )
    {
    case UIDeviceOrientationPortrait : // Device oriented vertically, home button on the bottom
        sg_curOrt = Ogre::OR_PORTRAIT ;
        break;
            
    case UIDeviceOrientationPortraitUpsideDown : // Device oriented vertically, home button on the top
        sg_curOrt = Ogre::OR_DEGREE_180 ;
        break ;
            
    case UIDeviceOrientationLandscapeLeft : // Device oriented horizontally, home button on the right
        sg_curOrt = Ogre::OR_LANDSCAPELEFT ;
        break ;
            
    case UIDeviceOrientationLandscapeRight : // Device oriented horizontally, home button on the left
        sg_curOrt = Ogre::OR_LANDSCAPERIGHT ;
        break ;
    
    default : ;
    }

    return sg_curOrt ;
}


} // namespace OgreAssistKit
