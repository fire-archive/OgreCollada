/*
Copyright (c) 2008 NetAllied Systems GmbH

This file is part of COLLADASaxFrameworkLoader.

Licensed under the MIT Open Source License, 
for details please see LICENSE file or the website
http://www.opensource.org/licenses/mit-license.php
*/

#ifndef __COLLADASAXFWL_NODELOADER_H__
#define __COLLADASAXFWL_NODELOADER_H__

#include "COLLADASaxFWLPrerequisites.h"
#include "COLLADASaxFWLFilePartLoader.h"

#include "COLLADAFWInstanceGeometry.h"

#include <stack>
#include <set>

namespace COLLADAFW
{ 
	class Transformation;
	class Node;
}


namespace COLLADASaxFWL
{

	/** Imports the entire visual scene and sends it to the writer. */
	class NodeLoader : public FilePartLoader 
	{
	private:
		/** Stack of nodes.*/
		typedef std::stack<COLLADAFW::Node*> NodeStack;

		/** Set of MaterialBindings*/
		typedef std::set<COLLADAFW::InstanceGeometry::MaterialBinding> MaterialBindingsSet;

		/** Set of TextureCoordinateBinding*/
		typedef std::set<COLLADAFW::InstanceGeometry::TextureCoordinateBinding> TextureCoordinateBindingSet;

		/** Stack of nodes to traverse back in node hierarchy. Array and contents will be delete in destructor.*/
		NodeStack mNodeStack;

		/** The transformation, that is currently being parsed. Null if none is being parsed.*/
		COLLADAFW::Transformation* mCurrentTransformation;

		/** The number of floats that have been received since the last begin__* method 
		by the transformation data* methods. This is used to know where the next received number must 
		be placed in the transformation.*/
		size_t mTransformationNumbersReceived;

		/** Instance geometry currently being filled.*/
		COLLADAFW::InstanceGeometry* mCurrentInstanceGeometry;

		/** Material binding currently being filled.*/
		COLLADAFW::InstanceGeometry::MaterialBinding* mCurrentMaterialBinding;

		/** Set of all material bindings of the current instance geometry.*/
		MaterialBindingsSet mCurrentMaterialBindings;

		/** Set of all TextureCoordinate bindings of the current instance geometry.*/
		TextureCoordinateBindingSet mCurrentTextureCoordinateBindings;

		/** The material info of the geometry instantiated in the current instance geometry.*/
		GeometryMaterialIdInfo* mCurrentMaterialInfo;

	public:

		/** Constructor. */
		NodeLoader(IFilePartLoader* callingFilePartLoader);

		/** Destructor. */
		virtual ~NodeLoader();

	protected:

		/** This method handles the beginning of a node element, independent of its parent.*/
		bool beginNode( const node__AttributeData& attributeData );

		/** This method handles the ending of a node element, independent of its parent.*/
		bool endNode();

	private:

		/** Disable default copy ctor. */
		NodeLoader( const NodeLoader& pre );

		/** Disable default assignment operator. */
		const NodeLoader& operator= ( const NodeLoader& pre );

		/** Store a root node, i.e. a node that does not has a node as parent.*/
		virtual void handleRootNode( COLLADAFW::Node* rootNode ) = 0;

		/** This method handles the beginning of a transformation independent of its type.*/
		template<class Transformationtype>
		bool beginTransformation();

		/** This method handles the ending of a transformation independent of its type.*/
		bool endTransformation();

		/** Sax callback function for the beginning of nodes, as child of a node.*/
		virtual bool begin__node__node( const node__AttributeData& attributeData );

		/** Sax callback function for the ending of nodes, as child of a node.*/
		virtual bool end__node__node();


		/** Sax callback function for the beginning of a translate element.*/
		virtual bool begin__node__translate( const translate__AttributeData& attributeData );

		/** Sax callback function for the ending of a translate element.*/
		virtual bool end__node__translate();

		/** Sax callback function for the float data of a translate element.*/
		virtual bool data__node__translate( const double* data, size_t length );


		/** Sax callback function for the beginning of a rotate element.*/
		virtual bool begin__node__rotate( const rotate__AttributeData& attributeData );

		/** Sax callback function for the ending of a rotate element.*/
		virtual bool end__node__rotate();

		/** Sax callback function for the float data of a rotate element.*/
		virtual bool data__node__rotate( const double* data, size_t length );


		/** Sax callback function for the beginning of a matrix element.*/
		virtual bool begin__matrix( const matrix__AttributeData& attributeData );

		/** Sax callback function for the ending of a matrix element.*/
		virtual bool end__matrix();

		/** Sax callback function for the float data of a rotate element.*/
		virtual bool data__matrix( const double* data, size_t length );


		/** Sax callback function for the beginning of a scale element.*/
		virtual bool begin__scale( const scale__AttributeData& attributeData );

		/** Sax callback function for the ending of a scale element.*/
		virtual bool end__scale();

		/** Sax callback function for the float data of a scale element.*/
		virtual bool data__scale( const double* data, size_t length );

        virtual bool begin__skew( const skew__AttributeData& attributeData );
        virtual bool end__skew();
        virtual bool data__skew( const double* value, size_t length );

		virtual bool begin__lookat( const lookat__AttributeData& attributeData );
		virtual bool end__lookat();
		virtual bool data__lookat( const double* value, size_t length );

		/** Sax callback function for the beginning of an instance geometry element.*/
		virtual bool begin__node__instance_geometry( const instance_geometry__AttributeData& attributeData );

		/** Sax callback function for the ending of an instance geometry element.*/
		virtual bool end__node__instance_geometry();


		/** We do not need to do anything here.*/
		virtual bool begin__instance_geometry__bind_material(){return true;}

		/** We do not need to do anything here.*/
		virtual bool end__instance_geometry__bind_material(){return true;}

		/** We do not need to do anything here.*/
		virtual bool begin__bind_material__technique_common(){return true;}

		/** We do not need to do anything here.*/
		virtual bool end__bind_material__technique_common(){return true;}

		/** Create new current bind material and set basic attributes.*/
		virtual bool begin__instance_material( const instance_material__AttributeData& attributeData );
		
		/** We store all instance_material informations in a set.*/
		virtual bool end__instance_material();


		/** We store all bind vertex informations in a set.*/
		virtual bool begin__bind_vertex_input( const bind_vertex_input__AttributeData& attributeData );

		/** We do not need to do anything here.*/
		virtual bool end__bind_vertex_input(){ return true; }


		/** Sax callback function for the beginning of an instance node element.*/
		virtual bool begin__instance_node( const instance_node__AttributeData& attributeData );

		/** We don't need to do anything here.*/
		virtual bool end__instance_node(){return true;}


		/** Appends the instance camera to the current node.*/
		virtual bool begin__instance_camera( const instance_camera__AttributeData& attributeData );

		/** We don't need to do anything here.*/
		virtual bool end__instance_camera(){return true;}


		/** Appends the instance light to the current node.*/
		virtual bool begin__instance_light( const instance_light__AttributeData& attributeData );

		/** We don't need to do anything here.*/
		virtual bool end__instance_light(){return true;}

	};

} // namespace COLLADASAXFWL

#endif // __COLLADASAXFWL_NODELOADER_H__
