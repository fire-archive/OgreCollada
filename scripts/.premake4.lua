-- A solution contains projects, and defines the available configurations
solution "MyApplication"
	configurations { "DebugStatic", "ReleaseStatic", "DebugShared", "ReleaseShared" }
	language "C++"
	--_ACTION is undefined if not specified not command line
	if _ACTION then 
		location ( "../build/" .. _ACTION )
	end

	--OpenCOLLADA external: Cg
	--OpenCOLLADA external: LibXML
	--OpenCOLLADA external: MayaDataModel
	--OpenCOLLADA external: UTF

	--OpenCOLLADA library
	project "OpenCOLLADA"
		links {"Cg", "xml2"}
		basepath_thirdparty = "../thirdparty"
		basepath = "../thirdparty/OpenCOLLADA"
		files { path.join(basepath, "COLLADABaseUtils/include/**.h"),  path.join(basepath, "COLLADABaseUtils/src/**.cpp"),
						path.join(basepath, "COLLADABaseUtils/include/UTF/**.h"),  path.join(basepath, "COLLADABaseUtils/src/UTF/**.c"),
						path.join(basepath, "COLLADAFramework/include/**.h"),  path.join(basepath, "COLLADAFramework/src/**.cpp"),
						path.join(basepath, "COLLADASaxFrameworkLoader/include/**.h"),  path.join(basepath, "COLLADASaxFrameworkLoader/src/**.cpp"),
						path.join(basepath, "GeneratedSaxParser/include/**.h"),  path.join(basepath, "GeneratedSaxParser/src/**.cpp"),
-- 						path.join(basepath_thirdparty, "UTF/include/**.h"),  path.join(basepath_thirdparty, "UTF/src/**.cpp")
					}
		includedirs { 
						path.join(basepath, "COLLADABaseUtils/include"),
						path.join(basepath, "COLLADABaseUtils/include/UTF"),
						path.join(basepath, "COLLADAFramework/include"),
						path.join(basepath, "COLLADASaxFrameworkLoader/include"),
						path.join(basepath, "GeneratedSaxParser/include"),
-- 						path.join(basepath_thirdparty, "UTF/include"),
						"/usr/include/libxml2", --LibXML2 is not in search path, on Gentoo...? Why not?
					}

		configuration "DebugStatic"
			kind "StaticLib"
		configuration "DebugShared"
			kind "SharedLib"
		configuration {"DebugStatic", "DebugShared"}
			defines { "DEBUG" }
			objdir "../build/obj/debug"

		configuration "ReleaseStatic"
			kind "StaticLib"
		configuration "ReleaseShared"
			kind "SharedLib"
		configuration {"ReleaseStatic", "ReleaseShared"}
			defines { "NDEBUG" }
			objdir "../build/obj/release"

-- OgreCollada library
	project "OgreCOLLADA"
		links {"OpenCOLLADA"}
		files { "../OgreCOLLADA/include/**.h",  "../OgreCOLLADA/src/**.cpp"}
		basepath_thirdparty = "../thirdparty"
		basepath = "../thirdparty/OpenCOLLADA"
		includedirs { 
						"../OgreCOLLADA/include",
						path.join(basepath, "COLLADABaseUtils/include"),
						path.join(basepath, "COLLADAFramework/include"),
						path.join(basepath, "COLLADASaxFrameworkLoader/include"),
						path.join(basepath, "GeneratedSaxParser/include"),
-- 						path.join(basepath_thirdparty, "UTF/include"),
--						"/usr/include/libxml2", --LibXML2 is not in search path, on Gentoo...? Why not?
					}
		
		configuration "DebugStatic"
			kind "StaticLib"
		configuration "DebugShared"
			kind "SharedLib"
		configuration {"DebugStatic", "DebugShared"}
			defines { "DEBUG" }
			objdir "../build/obj/debug"

		configuration "ReleaseStatic"
			kind "StaticLib"
		configuration "ReleaseShared"
			kind "SharedLib"
		configuration {"ReleaseStatic", "ReleaseShared"}
			defines { "NDEBUG" }
			objdir "../build/obj/release"

-- 	OgreColladaConverter command line utility
	project "OgreColladaConverter"
		links {"xml2", "boost_system", "boost_filesystem", "boost_regex", "OgreMain", "OpenCOLLADA", "OgreCOLLADA"}
		kind "ConsoleApp"
		files { "../tools/Converter/src/**.cpp" }
		basepath = "../thirdparty/OpenCOLLADA"
		includedirs { 
				path.join(basepath, "COLLADABaseUtils/include"),
				path.join(basepath, "COLLADAFramework/include"),
				path.join(basepath, "GeneratedSaxParser/include"),
				path.join(basepath, "COLLADASaxFrameworkLoader/include"),
				"../OgreCOLLADA/include"
				}

		configuration {"DebugStatic", "DebugShared"}
			defines { "DEBUG" }
			objdir "../build/obj/debug"

		configuration {"ReleaseStatic", "ReleaseShared"}
			defines { "NDEBUG" }
			objdir "../build/obj/release"
-- 		
-- 		configuration "DebugStatic"
-- 			kind "StaticLib"
-- 		configuration "DebugShared"
-- 			kind "SharedLib"
-- 		configuration {"DebugStatic", "DebugShared"}
-- 			defines { "DEBUG" }
-- 			objdir "../build/obj/debug"
-- 
-- 		configuration "ReleaseStatic"
-- 			kind "StaticLib"
-- 		configuration "ReleaseShared"
-- 			kind "SharedLib"
-- 		configuration {"ReleaseStatic", "ReleaseShared"}
-- 			defines { "NDEBUG" }
-- 			build "../build/obj/release"