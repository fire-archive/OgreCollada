/*

Copyright (c) 2009 OGRE COLLADA Team

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

#ifndef __OGRECOLLADA_WRITER_H__
#define __OGRECOLLADA_WRITER_H__

#ifndef WIN32
#include "OGRE/Ogre.h"
#else
#include "Ogre.h"
#endif

#include "COLLADAFWIWriter.h"
#include "COLLADAFWFileInfo.h"
#include "COLLADAFWVisualScene.h"
#include "COLLADAFWLibraryNodes.h"
#include "COLLADAFWGeometry.h"
#include "COLLADAFWMaterial.h"
#include "COLLADAFWEffect.h"
#include "COLLADAFWCamera.h"
#include "COLLADAFWImage.h"
#include "COLLADAFWLight.h"

namespace OgreCollada {

class OgreWriter : public COLLADAFW::IWriter {

public:

	static const Ogre::String RESOURCE_GROUP_NAME;

	OgreWriter(const std::string& outdir);
	virtual ~OgreWriter();

	virtual void cancel(const COLLADAFW::String& errorMessage){};
	virtual void start();
	virtual void finish();
	virtual bool writeGlobalAsset ( const COLLADAFW::FileInfo* asset ) { /*TODO handle units here*/return true; };
	virtual bool writeVisualScene ( const COLLADAFW::VisualScene* visualScene ) {return true;}
	virtual bool writeLibraryNodes ( const COLLADAFW::LibraryNodes* libraryNodes ) {return true;}
	virtual bool writeGeometry ( const COLLADAFW::Geometry* geometry );
	virtual bool writeMaterial( const COLLADAFW::Material* material ){return true;}
	virtual bool writeEffect( const COLLADAFW::Effect* effect ){return true;}
	virtual bool writeCamera( const COLLADAFW::Camera* camera ){return true;}
	virtual bool writeImage( const COLLADAFW::Image* image ){return true;}
	virtual bool writeLight( const COLLADAFW::Light* camera ){return true;}

private:

	std::string mOutdir;

	/** Disable default copy ctor. */
	OgreWriter ( const OgreWriter& pre );

    /** Disable default assignment operator. */
	const OgreWriter& operator= ( const OgreWriter& pre );

};

}

#endif
