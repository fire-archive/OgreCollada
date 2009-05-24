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

#include <iostream>
#include <string>
#include <cstring>

#include "GeneratedSaxParserCoutErrorHandler.h"
#include "COLLADASaxFWLLoader.h"
#include "OgreColladaWriter.h"
#include "COLLADAFWRoot.h"

int main(int argc, char** argv)
{
	if (argc != 5)
	{
		std::cerr << "Usage: -i <input file> -o <output dir>" << std::endl;
		return -1;
	}

	std::string inputFileName;
	std::string outputDir;
	if ( strcmp(argv[1], "-i") == 0 )
	{
		inputFileName = argv[2];
		outputDir = argv[4];
	}
	else
	{
		inputFileName = argv[4];
		outputDir = argv[2];
	}
	std::cout << "input: " << inputFileName << ", out: " << outputDir << std::endl;

	// There are two different ErrorHandler interfaces -> we cannot use the cout default impl
	// TODO use an error handler
//	GeneratedSaxParser::CoutErrorHandler errorHandler;
//	COLLADASaxFWL::Loader loader(&errorHandler);
	COLLADASaxFWL::Loader loader;
	OgreCollada::OgreWriter writer(outputDir);
	COLLADAFW::Root root(&loader, &writer);

	if ( !root.loadDocument(inputFileName) )
		return -1;

	return 0;
}
