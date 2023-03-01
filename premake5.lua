workspace "sln-eelua"
  configurations { "Release", "Debug" }

  project "eelua"
    kind "SharedLib"
    language "C"
    files { "src/*.cpp", "src/*.h", "include/*.h", "include/*.cpp"}

    includedirs { "include" }
    libdirs { "lib" }
    links { "lua51" }

    configuration "Debug"
      defines { "DEBUG" }
      symbols "On"
	  linkoptions {"/MTd"}
	  staticruntime "On"
			
    configuration "Release"
      defines { "NDEBUG" }
      optimize "On"
	  linkoptions {"/MT"}
	  staticruntime "On"
	  
    configuration { "gmake" }
      linkoptions { "-Wall -static-libgcc" }


