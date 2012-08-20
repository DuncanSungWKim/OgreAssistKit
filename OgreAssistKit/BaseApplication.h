/*
-----------------------------------------------------------------------------
Filename:    BaseApplication.h
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _ 
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/                              
      Tutorial Framework
      http://www.ogre3d.org/tikiwiki/
-----------------------------------------------------------------------------
*/
#ifndef __BaseApplication_h_
#define __BaseApplication_h_

#ifdef TARGET_OS_IPHONE
#define OGRE_STATIC_GLES 1
#endif
#ifdef __ANDROID__
#define OGRE_STATIC_GLES2 1
#endif

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>
#if (OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS) || (OGRE_PLATFORM == OGRE_PLATFORM_ANDROID)
#include <OgreStaticPluginLoader.h>
#endif

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#if (OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS) || (OGRE_PLATFORM == OGRE_PLATFORM_ANDROID)
#include <OISMultiTouch.h>
#else
#include <OISMouse.h>
#endif

#include <SdkTrays.h>
#include <SdkCameraMan.h>
#if (OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS)
#include <macUtils.h>
#endif
#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
#include "AndroidUtil.h"
#endif

class BaseApplication : public Ogre::FrameListener, public Ogre::WindowEventListener, public OIS::KeyListener,
#if (OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS) || (OGRE_PLATFORM == OGRE_PLATFORM_ANDROID)
    public OIS::MultiTouchListener,
#else
    public OIS::MouseListener,
#endif
    OgreBites::SdkTrayListener
{
public:
    BaseApplication( bool enableOIS = true ) ;
    virtual ~BaseApplication(void);

    virtual void go(void);
    virtual bool setup();
#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
	virtual bool setup( struct android_app* pAndroidApp ) ;
#endif
    virtual void destroyScene(void);
    Ogre::Root* get_pRoot() const { return mRoot ; }
    Ogre::RenderWindow* get_pRenderWindow() const { return mWindow ; }
    
protected:
    virtual bool configure(void);
    virtual void chooseSceneManager(void);
    virtual void createCamera(void);
    virtual void createFrameListener(void);
    virtual void createScene(void) = 0; // Override me!
    virtual void createViewports(void);
    virtual void setupResources(void);
    virtual void createResourceListener(void);
    virtual void loadResources(void);
	void loadPlugins( const Ogre::DataStreamPtr& stream ) ;

    // Ogre::FrameListener
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

    // OIS::KeyListener
    virtual bool keyPressed( const OIS::KeyEvent &arg );
    virtual bool keyReleased( const OIS::KeyEvent &arg );
    
#if (OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS) || (OGRE_PLATFORM == OGRE_PLATFORM_ANDROID)
    // OIS::MultiTouchEvent
    virtual bool touchMoved( const OIS::MultiTouchEvent &arg );
    virtual bool touchPressed( const OIS::MultiTouchEvent &arg );
    virtual bool touchReleased( const OIS::MultiTouchEvent &arg );
    virtual bool touchCancelled( const OIS::MultiTouchEvent& evt )
    { return true ; }
#else
    // OIS::MouseListener
    virtual bool mouseMoved( const OIS::MouseEvent &arg );
    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
#endif

    // Ogre::WindowEventListener
    //Adjust mouse clipping area
    virtual void windowResized(Ogre::RenderWindow* rw);
    //Unattach OIS before window shutdown (very important under Linux)
    virtual void windowClosed(Ogre::RenderWindow* rw);

    Ogre::Root *mRoot;
    Ogre::Camera* mCamera;
    Ogre::SceneManager* mSceneMgr;
    Ogre::RenderWindow* mWindow;
    Ogre::String mResourcesCfg;
    Ogre::String mPluginsCfg;

    // OgreBites
    OgreBites::SdkTrayManager* mTrayMgr;
    OgreBites::SdkCameraMan* mCameraMan;       // basic camera controller
    OgreBites::ParamsPanel* mDetailsPanel;     // sample details panel
    bool mCursorWasVisible;                    // was cursor visible before dialog appeared
    bool mShutDown;

    //OIS Input devices
    OIS::InputManager* mInputManager;
    bool m_enableOIS ;
#if (OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS) || (OGRE_PLATFORM == OGRE_PLATFORM_ANDROID)
    OIS::MultiTouch* mMouse;
    Ogre::StaticPluginLoader m_StaticPluginLoader ;
#else
    OIS::Mouse*    mMouse;
#endif
    OIS::Keyboard* mKeyboard;

#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
public:
	OgreAssistKit::AndroidAssetManager m_androidAssetMgr ;
#endif
};

#endif // #ifndef __BaseApplication_h_
