/*
    Copyright (c) 2008 NetAllied Systems GmbH

    This file is part of COLLADASaxFrameworkLoader.

    Licensed under the MIT Open Source License, 
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#ifndef __COLLADASAXFWL_LIBRARYIMAGESLOADER_H__
#define __COLLADASAXFWL_LIBRARYIMAGESLOADER_H__

#include "COLLADASaxFWLPrerequisites.h"
#include "COLLADASaxFWLFilePartLoader.h"

namespace COLLADAFW
{
	class Image;
}


namespace COLLADASaxFWL
{

	/** Loads all the images in a library images.  */
	class LibraryImagesLoader : public FilePartLoader 
		{
	private:
		/** The current image.*/
		COLLADAFW::Image* mCurrentImage;

		/** The part of the uri of the current image, already received by data__image__init_from().*/
		COLLADAFW::ArrayPrimitiveType<ParserChar> mCurrentImageURIPart;

	public:

        /** Constructor. */
		LibraryImagesLoader( IFilePartLoader* callingFilePartLoader );

        /** Destructor. */
		virtual ~LibraryImagesLoader();

		/** Finishes loading a library images.*/
		virtual bool end__library_images();

		
		/** Creates a new image.*/
		virtual bool begin__library_images__image( const image__AttributeData& attributeData );

		/** Sends image to the writer.*/
		virtual bool end__library_images__image();


		/** Set source type.*/
		virtual bool begin__image__init_from();

		/** Set the image uri.*/
		virtual bool end__image__init_from();

		/** Set the image uri.*/
		virtual bool data__image__init_from( const ParserChar* data, size_t length );


		/** Set source type.*/
		virtual bool begin__data();

		/** We don't need to do anything here.*/
		virtual bool end__data(){return true;}

		/** Store data in current image.*/
		virtual bool data__data( const ParserChar* data, size_t length );

	private:

        /** Disable default copy ctor. */
		LibraryImagesLoader( const LibraryImagesLoader& pre );

        /** Disable default assignment operator. */
		const LibraryImagesLoader& operator= ( const LibraryImagesLoader& pre );

	};

} // namespace COLLADASAXFWL

#endif // __COLLADASAXFWL_LIBRARYIMAGESLOADER_H__
