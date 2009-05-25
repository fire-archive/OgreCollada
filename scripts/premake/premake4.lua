verbose = 1
-- A solution contains projects, and defines the available configurations
solution "MyApplication"
	configurations { "DebugStatic", "ReleaseStatic", "DebugShared", "ReleaseShared" }
	language "C++"
	rootpath = "../../"
	libdirs ( path.join(rootpath, "libs") )
	--_ACTION is undefined if not specified not command line
	if _ACTION then 
		location ( path.join(rootpath, path.join("build", _ACTION) ) )
	end

	configuration { "*Static" }
		kind "StaticLib"
	configuration { "*Shared" }
		kind "SharedLib"		
	configuration { "Debug*" }
		defines { "DEBUG" }
		objdir ( location() )
	configuration {"Release*"}
		defines { "NDEBUG" }
		objdir ( location() )

	configuration {} -- reset the configuration filter
	-------------------------------------------------------------------------------
	-- COLLADABaseUtils
	project "COLLADABaseUtils"
		targetdir ( path.join(rootpath, "lib") )
		links { "boost_system", "boost_filesystem", "boost_regex"}
		basepath = path.join(rootpath, "thirdparty/OpenCOLLADA")
		files { path.join(basepath, "COLLADABaseUtils/include/**.h"),  path.join(basepath, "COLLADABaseUtils/src/**.cpp"),
						path.join(basepath, "COLLADABaseUtils/include/UTF/**.h"),  path.join(basepath, "COLLADABaseUtils/src/UTF/**.c") 
				}
		includedirs { 
						path.join(basepath, "COLLADABaseUtils/include"),
						path.join(basepath, "COLLADABaseUtils/include/UTF"), 
				}
		configuration { "Debug*" }
			targetname ( "COLLADABaseUtils_d" )
		configuration {"Release*"}
			targetname ( "COLLADABaseUtils" )

	configuration {} -- reset the configuration filter
	-------------------------------------------------------------------------------
	-- GeneratedSaxParser
	project "GeneratedSaxParser"
		targetdir ( path.join(rootpath, "lib") )
		configuration { "linux", "gmake" }
			--retrieve libXML2 build options from pkg-config
			buildoptions { "`pkg-config --cflags libxml-2.0`" }
			linkoptions { "`pkg-config --libs libxml-2.0`" }
		configuration {}
		links { "COLLADABaseUtils" }
		basepath = path.join(rootpath, "thirdparty/OpenCOLLADA")
		files { 
						path.join(basepath, "GeneratedSaxParser/include/**.h"),  path.join(basepath, "GeneratedSaxParser/src/**.cpp"),
				}
		includedirs {
						path.join(basepath, "GeneratedSaxParser/include"),
				}
		configuration { "Debug*" }
			targetname ( "GeneratedSaxParser_d" )
		configuration {"Release*"}
			targetname ( "GeneratedSaxParser" )

	configuration {} -- reset the configuration filter
	-------------------------------------------------------------------------------
	-- COLLADABaseUtils
	project "COLLADAFramework"
		targetdir ( path.join(rootpath, "lib") )
		links { "COLLADABaseUtils" }
		basepath = path.join(rootpath, "thirdparty/OpenCOLLADA")
		files { 
						path.join(basepath, "COLLADAFramework/include/**.h"),  path.join(basepath, "COLLADAFramework/src/**.cpp"),
				}
		includedirs { 
						path.join(basepath, "COLLADAFramework/include"),
						path.join(basepath, "COLLADABaseUtils/include"),
				}
		configuration { "Debug*" }
			targetname ( "COLLADAFramework_d" )
		configuration {"Release*"}
			targetname ( "COLLADAFramework" )

	configuration {} -- reset the configuration filter
	-------------------------------------------------------------------------------
	-- COLLADASaxFrameworkLoader
	project "COLLADASaxFrameworkLoader"
		targetdir ( path.join(rootpath, "lib") )
		links { "COLLADABaseUtils", "COLLADAFramework", "GeneratedSaxParser" }
		basepath = path.join(rootpath, "thirdparty/OpenCOLLADA")
		files { 
						path.join(basepath, "COLLADASaxFrameworkLoader/include/**.h"),  path.join(basepath, "COLLADASaxFrameworkLoader/src/**.cpp"),
				}
		includedirs {
						path.join(basepath, "COLLADASaxFrameworkLoader/include"),
						path.join(basepath, "COLLADAFramework/include"),
						path.join(basepath, "GeneratedSaxParser/include"),
						path.join(basepath, "COLLADABaseUtils/include"),
						"/usr/include/libxml2"
				}
		configuration { "Debug*" }
			targetname ( "COLLADASaxFrameworkLoader_d" )
		configuration {"Release*"}
			targetname ( "COLLADASaxFrameworkLoader" )

	configuration {} -- reset the configuration filter
	-------------------------------------------------------------------------------
	-- OgreCollada library
	project "OgreCOLLADA"
		targetdir ( path.join(rootpath, "lib") )
		configuration { "linux", "gmake" }
			--retrieve Ogre build options from pkg-config
			buildoptions { "`pkg-config --cflags OGRE`" } 
			linkoptions { "`pkg-config --libs OGRE`" }
		configuration {}
		links {"COLLADABaseUtils", "GeneratedSaxParser", "COLLADAFramework", "COLLADASaxFrameworkLoader"}
		files { 
				path.join(rootpath, "include/**.h"),  path.join(rootpath, "src/**.cpp"),
				}
		basepath = path.join(rootpath, "thirdparty/OpenCOLLADA");
		includedirs { 
						path.join(rootpath, "include"),
						path.join(basepath, "COLLADABaseUtils/include"),
						path.join(basepath, "COLLADAFramework/include"),
						path.join(basepath, "COLLADASaxFrameworkLoader/include"),
						path.join(basepath, "GeneratedSaxParser/include")
					}
		configuration { "Debug*" }
			targetname ( "OgreCOLLADA_d" )
		configuration { "Release*" }
			targetname ( "OgreCOLLADA" )

	configuration {} -- reset the configuration filter
	-------------------------------------------------------------------------------
	-- 	OgreColladaConverter command line utility
	project "OgreColladaConverter"
		targetdir ( path.join(rootpath, path.join("tools","bin")) )
		configuration { "linux", "gmake" }
			--retrieve Ogre and libXML2 build options from pkg-config
			buildoptions { "`pkg-config --cflags OGRE`" } 
			buildoptions { "`pkg-config --cflags libxml-2.0`" }
			linkoptions { "`pkg-config --libs OGRE`" }
			linkoptions { "`pkg-config --libs libxml-2.0`" }
		configuration {}
		links {"OgreCOLLADA", "COLLADASaxFrameworkLoader", "GeneratedSaxParser", "COLLADAFramework", "COLLADABaseUtils", "boost_regex" }
		kind "ConsoleApp"
		files { 
				path.join(rootpath, "tools/Converter/src/**.cpp")
			}
		basepath = path.join(rootpath, "thirdparty/OpenCOLLADA");
		includedirs { 
				path.join(basepath, "COLLADABaseUtils/include"),
				path.join(basepath, "COLLADAFramework/include"),
				path.join(basepath, "GeneratedSaxParser/include"),
				path.join(basepath, "COLLADASaxFrameworkLoader/include"),
				path.join(rootpath, "include")
				}
		configuration { "Debug*" }
-- 			targetname ( "OgreColladaConverter_d" )
		configuration {"Release*"}
			targetname ( "OgreColladaConverter" )

	configuration {} -- reset the configuration filter
	-------------------------------------------------------------------------------
	-- 	OgreColladaConverter command line utility
	project "OgreCOLLADAViewer"
		prebuildcommands("rcc " .. path.join(rootpath, "tools/Data/") .. "OgreCOLLADAViewer.qrc -o " .. path.join(rootpath,"tools/Viewer/include/") .. "OgreCOLLADAViewer.res.h" );
		prebuildcommands("uic " .. path.join(rootpath, "tools/Data/forms/") .. "OgreCOLLADAViewer.ui -o " .. path.join(rootpath,"tools/Viewer/include/") .. "OgreCOLLADAViewer.ui.h" );
		prebuildcommands("moc " .. path.join(rootpath, "tools/Viewer/include/") .. "TestWidget.h -o " .. path.join(rootpath,"tools/Viewer/src/") .. "TestWidget.moc.cpp" )
		prebuildcommands("moc " .. path.join(rootpath, "tools/Viewer/include/") .. "QOgreWidget.h -o " .. path.join(rootpath,"tools/Viewer/src/") .. "QOgreWidget.moc.cpp" )
		prebuildcommands("moc " .. path.join(rootpath, "tools/Viewer/include/") .. "OgreCOLLADAViewer.h -o " .. path.join(rootpath,"tools/Viewer/src/") .. "OgreCOLLADAViewer.moc.cpp" )
		targetdir ( path.join(rootpath, path.join("tools","bin")) )
		configuration { "linux", "gmake" }
			--retrieve Ogre and libXML2 build options from pkg-config
			buildoptions { "`pkg-config --cflags OGRE`" }
			buildoptions { "`pkg-config --cflags QtCore QtUiTools QtGui`" } 
			linkoptions { "`pkg-config --libs OGRE`" }
			linkoptions { "`pkg-config --libs QtCore QtGui QtUiTools`" }
		configuration {}
		links {"OgreCOLLADA", "COLLADASaxFrameworkLoader", "GeneratedSaxParser", "COLLADAFramework", "COLLADABaseUtils", "boost_regex" }
		kind "ConsoleApp"
		files { 
-- 				path.join(rootpath, "tools/Viewer/src/QOgreWidget.moc.cpp"), path.join(rootpath, "tools/Viewer/src/TestWidget.moc.cpp"),
				path.join(rootpath, "tools/Viewer/include/**.h"), path.join(rootpath, "tools/Viewer/src/**.cpp"),
			}
		basepath = path.join(rootpath, "thirdparty/OpenCOLLADA");
		includedirs { 
				path.join(rootpath, "tools/Viewer/include"),
				path.join(basepath, "COLLADABaseUtils/include"),
				path.join(basepath, "COLLADAFramework/include"),
				path.join(basepath, "GeneratedSaxParser/include"),
				path.join(basepath, "COLLADASaxFrameworkLoader/include"),
				path.join(rootpath, "include")
				}
		configuration { "Debug*" }
			targetname ( "OgreCOLLADAViewer_d" )
		configuration {"Release*"}
			targetname ( "OgreCOLLADAViewer" )

	configuration () -- reset the configuration filter