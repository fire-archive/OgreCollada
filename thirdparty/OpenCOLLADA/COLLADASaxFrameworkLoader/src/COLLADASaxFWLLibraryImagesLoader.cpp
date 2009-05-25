/*
    Copyright (c) 2008 NetAllied Systems GmbH

    This file is part of COLLADASaxFrameworkLoader.

    Licensed under the MIT Open Source License, 
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#include "COLLADASaxFWLStableHeaders.h"
#include "COLLADASaxFWLLibraryImagesLoader.h"

#include "COLLADAFWImage.h"
#include "COLLADAFWIWriter.h"


namespace COLLADASaxFWL
{

    //------------------------------
	LibraryImagesLoader::LibraryImagesLoader( IFilePartLoader* callingFilePartLoader )
		: FilePartLoader(callingFilePartLoader)
		, mCurrentImage(0)
	{

	}

    //------------------------------
	LibraryImagesLoader::~LibraryImagesLoader()
	{
	}

	//------------------------------
	bool LibraryImagesLoader::end__library_images()
	{
		finish();
		return true;
	}

	//------------------------------
	bool LibraryImagesLoader::begin__library_images__image( const image__AttributeData& attributeData )
	{
		mCurrentImage = FW_NEW COLLADAFW::Image( getUniqueIdFromId( attributeData.id, COLLADAFW::Image::ID()).getObjectId() );

		if ( attributeData.name )
			mCurrentImage->setName( (const char*) attributeData.name );
		else if ( attributeData.id )
			mCurrentImage->setName( (const char*) attributeData.id );

		if ( attributeData.format )
			mCurrentImage->setFormat( attributeData.format );
		
		mCurrentImage->setHeight( (unsigned long)attributeData.height );
		mCurrentImage->setWidth( (unsigned long)attributeData.width );
		mCurrentImage->setDepth( (unsigned long)attributeData.depth );

		return true;
	}

	//------------------------------
	bool LibraryImagesLoader::end__library_images__image()
	{
		bool success = writer()->writeImage(mCurrentImage);
		FW_DELETE mCurrentImage;
		mCurrentImageURIPart.clear();
		return success;
	}

	//------------------------------
	bool LibraryImagesLoader::begin__image__init_from()
	{
		mCurrentImage->setSourceType( COLLADAFW::Image::SOURCE_TYPE_URI );
		return true;
	}

	//------------------------------
	bool LibraryImagesLoader::end__image__init_from()
	{
		String imageUriString( mCurrentImageURIPart.getData(), mCurrentImageURIPart.getCount() );
		mCurrentImageURIPart.setCount(0);
		COLLADABU::URI imageUri( imageUriString );
		mCurrentImage->setImageURI( imageUri );
		return true;
	}

	//------------------------------
	bool LibraryImagesLoader::data__image__init_from( const ParserChar* data, size_t length )
	{
		mCurrentImageURIPart.appendValues( data, length );
		return true;
	}

	//------------------------------
	bool LibraryImagesLoader::begin__data()
	{
		// disabled see COLALDAFW::Image
		//mCurrentImage->setSourceType( COLLADAFW::Image::SOURCE_TYPE_DATA);
		return true;
	}

	//------------------------------
	bool LibraryImagesLoader::data__data( const ParserChar* data, size_t length )
	{
		// disabled see COLALDAFW::Image
		//COLLADAFW::Image::CharacterArray& dataArray = mCurrentImage->getData();
		//dataArray.appendValues( (char *)data, length );
		return true;
	}


} // namespace COLLADASaxFWL
