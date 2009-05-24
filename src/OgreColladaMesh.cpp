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

#include <strstream>

#include "OGRE/Ogre.h"
#include "OGRE/OgreDefaultHardwareBufferManager.h"

#include "COLLADAFWTriangles.h"
#include "OgreColladaMesh.h"
#include "OgreColladaWriter.h"

namespace OgreCollada {

//------------------------------
Mesh::Mesh(COLLADAFW::Mesh* mesh)
 : mMesh(mesh)
{

}

//------------------------------
Mesh::~Mesh()
{

}

//------------------------------
bool Mesh::convert(const std::string& outDir)
{
	std::cout << "handling mesh: " << mMesh->getName() << std::endl;

	// TODO in COLLADA each mesh may have different units

	if ( mMesh->getTrianglesTriangleCount() == 0 ||
			mMesh->getPolygonsCount() != 0 ||
			mMesh->getTrifansCount() != 0 ||
			mMesh->getTristripsCount() != 0
		)
	{
		// TODO support more geometric primitives
		std::cerr << "only triangles supported" << std::endl;
		return true;
	}

	Ogre::HardwareBufferManager* hwBufMgr = Ogre::HardwareBufferManager::getSingletonPtr();
	if (!hwBufMgr)
	{
		hwBufMgr = new Ogre::DefaultHardwareBufferManager();
	}

	Ogre::HardwareVertexBufferSharedPtr vertexBuffer;
	int positionsCount = (int)mMesh->getPositions().getValuesCount() /*/ 3*/;
	std::cout << "positionsCount: " << positionsCount << std::endl;
	int vertexSize;
	if ( mMesh->getPositions().getType() == COLLADAFW::MeshVertexData::DATA_TYPE_DOUBLE )
	{
		std::cout << "DOUBLES" << std::endl;
		// does it make sense to use sizeof(double) here ???
		//vertexSize = 3*sizeof(double);
		vertexSize = 3*sizeof(float);
		vertexBuffer = hwBufMgr->createVertexBuffer(
					vertexSize, // size of one whole vertex
					positionsCount, // number of vertices
					Ogre::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY,
					false); // no shadow buffer
		void* lockedBuffer = vertexBuffer->lock(Ogre::HardwareBuffer::HBL_NORMAL);
		const COLLADAFW::DoubleArray* positionsArray = mMesh->getPositions().getDoubleValues();
		std::cout << "coords:";
		for ( int i = 0; i < positionsCount; ++i)
		{
			// should we use memcpy() here ???
			//((double*)lockedBuffer)[i] = (*positionsArray)[i];
			((float*)lockedBuffer)[i] = (*positionsArray)[i];
			std::cout << " " << (*positionsArray)[i];
		}
		std::cout << std::endl;
	}
	else
	{
		std::cout << "FLOATS" << std::endl;
		vertexSize = 3*sizeof(float);
		vertexBuffer = hwBufMgr->createVertexBuffer(
					vertexSize, // size of one whole vertex
					positionsCount, // number of vertices
					Ogre::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY,
					false); // no shadow buffer
		void* lockedBuffer = vertexBuffer->lock(Ogre::HardwareBuffer::HBL_NORMAL);
		const COLLADAFW::FloatArray* positionsArray = mMesh->getPositions().getFloatValues();
		for ( int i = 0; i < positionsCount; i+=3)
		{
			((float*)lockedBuffer)[i] = (*positionsArray)[i];
		}
	}

	Ogre::MeshManager* meshMgr = Ogre::MeshManager::getSingletonPtr();
	if (!meshMgr)
	{
		// TODO delete this and the HardwareBufferManager created above
		// TODO better OGRE singleton handling
		Ogre::LogManager* logMgr = Ogre::LogManager::getSingletonPtr();
		if (!logMgr)
		{
			/*logMgr = */new Ogre::LogManager();
		}
		Ogre::ResourceGroupManager* resGroupMgr = Ogre::ResourceGroupManager::getSingletonPtr();
		if (!resGroupMgr)
		{
			/*resGroupMgr = */new Ogre::ResourceGroupManager();
		}
		meshMgr = new Ogre::MeshManager();
	}
	Ogre::MeshPtr meshPtr = meshMgr->create(
			mMesh->getName(), // TODO check if name is always present/unique
			OgreWriter::RESOURCE_GROUP_NAME, true);

	meshPtr.getPointer()->sharedVertexData = new Ogre::VertexData();
	Ogre::VertexData* vertexData = meshPtr.getPointer()->sharedVertexData;
	Ogre::VertexDeclaration* vertDecl = hwBufMgr->createVertexDeclaration();
	vertexData->vertexDeclaration = vertDecl;
	int vertexCount = positionsCount/3;
	vertexData->vertexCount = vertexCount;

	std::cout << "vertDecl VertexSize before binding: " << vertDecl->getVertexSize(0) << std::endl;

	vertexData->vertexBufferBinding = hwBufMgr->createVertexBufferBinding();
	vertexData->vertexBufferBinding->setBinding(0, vertexBuffer);

	vertDecl->addElement(0, 0, Ogre::VET_FLOAT3, Ogre::VES_POSITION);

	std::cout << "vertexSize: " << vertexSize << std::endl;
	std::cout << "vertexData->vertexCount: " << vertexData->vertexCount << std::endl;
	std::cout << "sizeof(double): " << sizeof(double) << std::endl;
	std::cout << "sizeof(float): " << sizeof(float) << std::endl;
	std::cout << "vertDecl ElementCount: " << vertDecl->getElementCount() << std::endl;
	std::cout << "vertDecl VertexSize: " << vertDecl->getVertexSize(0) << std::endl;
	std::cout << "hasGaps: " << vertexData->vertexBufferBinding->hasGaps() << std::endl;
	std::cout << "vertexBuffer->getNumVertices(): " << vertexBuffer->getNumVertices() << std::endl;
	std::cout << "vertexBuffer->getSizeInBytes(): " << vertexBuffer->getSizeInBytes() << std::endl;
	std::cout << "vertexBuffer->getVertexSize(): " << vertexBuffer->getVertexSize() << std::endl;

	COLLADAFW::MeshPrimitiveArray& meshPrimitiveArray =  mMesh->getMeshPrimitives();
	for (size_t j=0; j<meshPrimitiveArray.getCount(); ++j)
	{
		const COLLADAFW::MeshPrimitive* meshPrimitive = meshPrimitiveArray[j];
		if ( ! meshPrimitive )
			continue;

		// TODO use Utils::int2str(i) as in old OgreCollada
		std::ostringstream oss;
		oss << j;
		Ogre::SubMesh* subMesh = meshPtr->createSubMesh(oss.str());
		subMesh->indexData = new Ogre::IndexData();
		subMesh->useSharedVertices = true;
		subMesh->operationType = Ogre::RenderOperation::OT_TRIANGLE_LIST;
		switch (meshPrimitive->getPrimitiveType())
		{
		case COLLADAFW::MeshPrimitive::TRIANGLES:
			{
				const COLLADAFW::Triangles* triangles = (const COLLADAFW::Triangles*) meshPrimitive;
				const COLLADAFW::UIntValuesArray& positionIndices =  triangles->getPositionIndices();

				Ogre::HardwareIndexBufferSharedPtr indexBuffer = hwBufMgr->createIndexBuffer(
						Ogre::HardwareIndexBuffer::IT_32BIT,
						positionIndices.getCount(),
						Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY,
						false
						);
				unsigned short* lockedBuffer = static_cast<unsigned short*>(indexBuffer->lock(Ogre::HardwareBuffer::HBL_NORMAL));

				std::cout << "indices:";
				for (size_t k=0; k<positionIndices.getCount(); ++k)
				{
					lockedBuffer[k] = positionIndices[k];
					std::cout << " " << positionIndices[k];
				}
				std::cout << std::endl;
				subMesh->indexData->indexBuffer = indexBuffer;
				std::cout << "positionIndices.getCount(): " << positionIndices.getCount() << std::endl;
				break;
			}
		case COLLADAFW::MeshPrimitive::LINES:
		case COLLADAFW::MeshPrimitive::LINE_STRIPS:
		case COLLADAFW::MeshPrimitive::POINTS:
		case COLLADAFW::MeshPrimitive::POLYGONS:
		case COLLADAFW::MeshPrimitive::POLYLIST:
		case COLLADAFW::MeshPrimitive::TRIANGLE_FANS:
		case COLLADAFW::MeshPrimitive::TRIANGLE_STRIPS:
		case COLLADAFW::MeshPrimitive::UNDEFINED_PRIMITIVE_TYPE:
		default:
			// TODO handle other primitive types
			break;
		}
	}
	// TODO bounding box
	Ogre::Vector3 min (0.0, 0.0, 0.0);
	Ogre::Vector3 max (1.0, 1.0, 1.0);
	Ogre::AxisAlignedBox aabb(min, max);
	meshPtr->_setBounds(aabb);
	meshPtr->_setBoundingSphereRadius(1.0);

	std::string fileName = outDir + "/" + mMesh->getName() + ".mesh";
    Ogre::MeshSerializer meshWriter;
    meshWriter.exportMesh(meshPtr.get(), fileName);

    // TODO normals
	// TODO gaps

	return true;
}

}
