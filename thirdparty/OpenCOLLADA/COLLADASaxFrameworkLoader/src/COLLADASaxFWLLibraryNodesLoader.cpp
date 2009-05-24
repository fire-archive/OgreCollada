/*
    Copyright (c) 2008 NetAllied Systems GmbH

    This file is part of COLLADASaxFrameworkLoader.

    Licensed under the MIT Open Source License, 
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#include "COLLADASaxFWLStableHeaders.h"
#include "COLLADASaxFWLLibraryNodesLoader.h"
#include "COLLADAFWIWriter.h"
#include "COLLADAFWLibraryNodes.h"


namespace COLLADASaxFWL
{

    //------------------------------
	LibraryNodesLoader::LibraryNodesLoader(IFilePartLoader* callingFilePartLoader)
		: NodeLoader(callingFilePartLoader),
		mLibraryNodes(new COLLADAFW::LibraryNodes())
	{
	}
	
    //------------------------------
	LibraryNodesLoader::~LibraryNodesLoader()
	{
	}

	//------------------------------
	void LibraryNodesLoader::handleRootNode( COLLADAFW::Node* rootNode )
	{
		mLibraryNodes->getNodes().append(rootNode);
	}

	//------------------------------
	bool LibraryNodesLoader::begin__library_nodes__node( const node__AttributeData& attributeData )
	{
		return beginNode(attributeData);
	}

	//------------------------------
	bool LibraryNodesLoader::end__library_nodes__node()
	{
		return endNode();
	}

	//------------------------------
	bool LibraryNodesLoader::end__library_nodes()
	{
		bool success = writer()->writeLibraryNodes(mLibraryNodes);
		delete mLibraryNodes;
		finish();
		return success;
	}

} // namespace COLLADASaxFWL
