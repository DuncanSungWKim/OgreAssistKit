/*
 Copyright (C) 2012 Duncan Sung W. Kim (duncansungwkim.blogspot.com)
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 
 */

#include "AndroidUtil.h"

#include <OgreArchiveManager.h>
#include <Android/OgreAPKFileSystemArchive.h>
#include <Android/OgreAPKZipArchive.h>

namespace OgreAssistKit
{

bool AndroidAssetManager::Init( AAssetManager* a_pAssetMgr )
{
	m_pAssetMgr = a_pAssetMgr ;

	Ogre::ArchiveManager& arMgr = Ogre::ArchiveManager::getSingleton() ;
	arMgr.addArchiveFactory( new Ogre::APKFileSystemArchiveFactory( a_pAssetMgr ) ) ;
	arMgr.addArchiveFactory( new Ogre::APKZipArchiveFactory( a_pAssetMgr ) ) ;

	return true ;
}



Ogre::DataStreamPtr AndroidAssetManager::OpenFileAsStream( const Ogre::String& a_fileName )
{
	Ogre::DataStreamPtr streamPtr ;
	AAsset* pAsset = ::AAssetManager_open( m_pAssetMgr, a_fileName.c_str(), AASSET_MODE_BUFFER ) ;
	if( NULL == pAsset )
		return streamPtr ;

	// reads all the data.
	off_t uLen = AAsset_getLength( pAsset ) ;
	void* pMembuf = OGRE_MALLOC( uLen, Ogre::MEMCATEGORY_GENERAL ) ;
	memcpy( pMembuf, AAsset_getBuffer(pAsset), uLen ) ;
	::AAsset_close( pAsset ) ;
	
	streamPtr = Ogre::DataStreamPtr( new Ogre::MemoryDataStream( pMembuf, uLen, true, true ) ) ;
	return streamPtr;
}

} // namespace OgreAssistKit