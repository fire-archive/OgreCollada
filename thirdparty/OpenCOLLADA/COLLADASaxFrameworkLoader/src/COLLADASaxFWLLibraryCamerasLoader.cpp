/*
    Copyright (c) 2008 NetAllied Systems GmbH

    This file is part of COLLADASaxFrameworkLoader.

    Licensed under the MIT Open Source License, 
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#include "COLLADASaxFWLStableHeaders.h"
#include "COLLADASaxFWLLibraryCamerasLoader.h"

#include "COLLADAFWIWriter.h"
#include "COLLADAFWCamera.h"

namespace COLLADASaxFWL
{

    //------------------------------
	LibraryCamerasLoader::LibraryCamerasLoader( IFilePartLoader* callingFilePartLoader )
		: FilePartLoader(callingFilePartLoader)
		, mCurrentCamera(0)
		, mCurrentCameraHasX(false)
		, mCurrentCameraHasY(false)
		, mCurrentCameraHasAspectRatio(false)
	{
	}

    //------------------------------
	LibraryCamerasLoader::~LibraryCamerasLoader()
	{
	}

	//------------------------------
	void LibraryCamerasLoader::resetCurrentValues()
	{
		mCurrentCamera = 0;
		mCurrentCameraHasX = false;
		mCurrentCameraHasY = false;
		mCurrentCameraHasAspectRatio = false;
	}

	//------------------------------
	bool LibraryCamerasLoader::end__library_cameras()
	{
		finish();
		return true;
	}

	//------------------------------
	bool LibraryCamerasLoader::begin__camera( const camera__AttributeData& attributeData )
	{
		mCurrentCamera = FW_NEW COLLADAFW::Camera( getUniqueIdFromId( attributeData.id, COLLADAFW::Camera::ID()).getObjectId() );

		if ( attributeData.name )
			mCurrentCamera->setName( (const char*) attributeData.name );
		else if ( attributeData.id )
			mCurrentCamera->setName( (const char*) attributeData.id );

		return true;
	}

	//------------------------------
	bool LibraryCamerasLoader::end__camera()
	{
		// we need to determine the description type
		// X = 1, Y = 2, aspect ratio = 4
		int descriptionType = (mCurrentCameraHasX ? 1 : 0) +
							  (mCurrentCameraHasY ? 2 : 0) +
							  (mCurrentCameraHasAspectRatio ? 4 : 0);
		switch ( descriptionType )
		{
		case 1:
			mCurrentCamera->setDescriptionType(COLLADAFW::Camera::SINGLE_X);
			break;
		case 2:
			mCurrentCamera->setDescriptionType(COLLADAFW::Camera::SINGLE_Y);
			break;
		case 3:
			mCurrentCamera->setDescriptionType(COLLADAFW::Camera::X_AND_Y);
			break;
		case 5:
			mCurrentCamera->setDescriptionType(COLLADAFW::Camera::ASPECTRATIO_AND_X);
			break;
		case 6:
			mCurrentCamera->setDescriptionType(COLLADAFW::Camera::ASPECTRATIO_AND_Y);
			break;
		default:
			mCurrentCamera->setDescriptionType(COLLADAFW::Camera::UNDEFINED);
		}

		bool success = writer()->writeCamera(mCurrentCamera);
		FW_DELETE mCurrentCamera;
		resetCurrentValues();
		return success;
	}

	//------------------------------
	bool LibraryCamerasLoader::begin__perspective()
	{
		mCurrentCamera->setCameraType(COLLADAFW::Camera::PERSPECTIVE);
		return true;
	}

	//------------------------------
	bool LibraryCamerasLoader::begin__orthographic()
	{
		mCurrentCamera->setCameraType(COLLADAFW::Camera::ORTHOGRAPHIC);
		return true;
	}

	//------------------------------
	bool LibraryCamerasLoader::data__xfov( double value )
	{
		mCurrentCamera->setXFov( value );
		mCurrentCameraHasX = true;
		return true;
	}

	//------------------------------
	bool LibraryCamerasLoader::data__yfov( double value )
	{
		mCurrentCamera->setYFov( value );
		mCurrentCameraHasY = true;
		return true;
	}


	//------------------------------
	bool LibraryCamerasLoader::data__xmag( double value )
	{
		mCurrentCamera->setXMag( value );
		mCurrentCameraHasX = true;
		return true;
	}

	//------------------------------
	bool LibraryCamerasLoader::data__ymag( double value )
	{
		mCurrentCamera->setYMag( value );
		mCurrentCameraHasY = true;
		return true;
	}

	//------------------------------
	bool LibraryCamerasLoader::data__perspective__aspect_ratio( double value )
	{
		mCurrentCamera->setAspectRatio(value);
		mCurrentCameraHasAspectRatio = true;
		return true;
	}

	//------------------------------
	bool LibraryCamerasLoader::data__perspective__znear( double value )
	{
		mCurrentCamera->setNearClippingPlane(value);
		return true;
	}

	//------------------------------
	bool LibraryCamerasLoader::data__perspective__zfar( double value )
	{
		mCurrentCamera->setFarClippingPlane(value);
		return true;
	}

	//------------------------------
	bool LibraryCamerasLoader::data__orthographic__aspect_ratio( double value )
	{
		mCurrentCamera->setAspectRatio(value);
		mCurrentCameraHasAspectRatio = true;
		return true;
	}

	//------------------------------
	bool LibraryCamerasLoader::data__orthographic__znear( double value )
	{
		mCurrentCamera->setNearClippingPlane(value);
		return true;
	}

	//------------------------------
	bool LibraryCamerasLoader::data__orthographic__zfar( double value )
	{
		mCurrentCamera->setFarClippingPlane(value);
		return true;
	}



} // namespace COLLADASaxFWL
