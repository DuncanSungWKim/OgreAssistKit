
namespace OgreAssistKit
{
class TouchInput ;
Ogre::OrientationMode ToOgre( UIDeviceOrientation a_ort ) ;
}



@interface OgreAssistKit_UIWindow : UIWindow
{
@public
    OgreAssistKit::TouchInput* m_pTouchInput ;
}

void CleanUpOgre( OgreAssistKit_UIWindow* oSelf ) ;

@end
