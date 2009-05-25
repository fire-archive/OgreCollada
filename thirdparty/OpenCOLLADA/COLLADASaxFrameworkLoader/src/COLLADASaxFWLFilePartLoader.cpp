/*
    Copyright (c) 2008 NetAllied Systems GmbH

    This file is part of COLLADASaxFrameworkLoader.

    Licensed under the MIT Open Source License, 
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#include "COLLADASaxFWLStableHeaders.h"
#include "COLLADASaxFWLFilePartLoader.h"

#include <cassert>


namespace COLLADASaxFWL
{

	FilePartLoader::FilePartLoader( IFilePartLoader* callingFilePartLoader )
		: mCallingFilePartLoader(callingFilePartLoader)
	{
		assert(callingFilePartLoader);
	}

    //------------------------------
	FilePartLoader::~FilePartLoader()
	{
	}

	//------------------------------
	void FilePartLoader::finish()
	{
		mCallingFilePartLoader->setMeAsParser();
	}

	//------------------------------
	const COLLADABU::URI& FilePartLoader::getFileUri()
	{
		return mCallingFilePartLoader->getFileUri();
	}


	//------------------------------
	void FilePartLoader::setParser(IFilePartLoader* parserToBeSet)
	{
		mCallingFilePartLoader->setParser(parserToBeSet);
	}

} // namespace COLLADASaxFWL
