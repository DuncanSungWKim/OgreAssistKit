/*
 Copyright (C) 2012 Duncan Sung W. Kim (duncansungwkim.blogspot.com)
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 
 */
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



void OgreAssistKit_UIWindow_CleanUp( OgreAssistKit_UIWindow* a_oSelf )
{
    if( NULL == a_oSelf->m_pTouchInput )
        return ;
    
    delete a_oSelf->m_pTouchInput ;
    a_oSelf->m_pTouchInput = NULL ;
}



-(void) dealloc
{
    OgreAssistKit_UIWindow_CleanUp( self ) ;
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
