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

#include "OgreColladaWriter.h"
#include "OgreColladaMesh.h"

namespace OgreCollada {

//------------------------------
const Ogre::String OgreWriter::RESOURCE_GROUP_NAME = "OGRE_COLLADA";

//------------------------------
OgreWriter::OgreWriter(const std::string& outdir)
 : mOutdir(outdir)
{

}

//------------------------------
OgreWriter::~OgreWriter()
{
}

//------------------------------
void OgreWriter::start()
{
	// is this necessary ???
	new Ogre::Root();
}

//------------------------------
void OgreWriter::finish()
{
	delete Ogre::Root::getSingletonPtr();
}

//------------------------------
bool OgreWriter::writeGeometry ( const COLLADAFW::Geometry* geometry )
{
	// TODO handle different geometry types
	if (geometry->getType() == COLLADAFW::Geometry::GEO_TYPE_MESH)
	{
		COLLADAFW::Mesh* mesh = (COLLADAFW::Mesh*) geometry;
		Mesh converter(mesh);
		return converter.convert(mOutdir);
	}
	return true;
}

}
