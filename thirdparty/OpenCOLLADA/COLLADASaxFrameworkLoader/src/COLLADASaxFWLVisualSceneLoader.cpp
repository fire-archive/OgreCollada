/*
    Copyright (c) 2008 NetAllied Systems GmbH

    This file is part of COLLADASaxFrameworkLoader.

    Licensed under the MIT Open Source License, 
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#include "COLLADASaxFWLStableHeaders.h"
#include "COLLADASaxFWLVisualSceneLoader.h"

#include "COLLADAFWVisualScene.h"
#include "COLLADAFWIWriter.h"


namespace COLLADASaxFWL
{

	VisualSceneLoader::VisualSceneLoader( IFilePartLoader* callingFilePartLoader )
		: NodeLoader(callingFilePartLoader),
		mVisualScene(new COLLADAFW::VisualScene())
	{
	}

    //------------------------------
	VisualSceneLoader::~VisualSceneLoader()
	{
	}


	//------------------------------
	void VisualSceneLoader::handleRootNode( COLLADAFW::Node* rootNode )
	{
		mVisualScene->getRootNodes().append(rootNode);	
	}

	//------------------------------
	bool VisualSceneLoader::begin__visual_scene__node( const node__AttributeData& attributeData )
	{
		return beginNode(attributeData);
	}

	//------------------------------
	bool VisualSceneLoader::end__visual_scene__node()
	{
		return endNode();
	}

	//------------------------------
	bool VisualSceneLoader::end__visual_scene()
	{
		bool success = writer()->writeVisualScene(mVisualScene);
		delete mVisualScene;
		finish();
		return success;
	}


} // namespace COLLADASaxFWL
