/*
 Copyright (C) 2012 Duncan Sung W. Kim (duncansungwkim.blogspot.com)
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 
 */

#pragma once
#ifndef __OgreAssistKit_AndroidUtil_h__
#define __OgreAssistKit_AndroidUtil_h__

#include <android_native_app_glue.h>

#include <OgreDataStream.h>


namespace OgreAssistKit
{


class AndroidAssetManager
{
// Methods
public:
	AndroidAssetManager() ;
	bool Init( AAssetManager* a_pAssetMgr ) ;
	Ogre::DataStreamPtr OpenFileAsStream( const Ogre::String& fileName ) ;

	
	
// Attributes
private:
	AAssetManager* m_pAssetMgr ;
};


// Inline Routines

inline AndroidAssetManager::AndroidAssetManager() :
	m_pAssetMgr(NULL)
{
}

} // namespace OgreAssistKit
#endif // __OgreAssistKit_AndroidUtil_h__
