#ifndef __PLATFORM_H_HEADER__
#define __PLATFORM_H_HEADER__

#pragma once

// Definition des versions de la biblioth�que
#define NKENTSUU_VERSION_MAJOR      1
#define NKENTSUU_VERSION_MINOR      0
#define NKENTSUU_VERSION_PATCH      0
#define NKENTSUU_VERSION_IS_RELEASE false


#if defined(_WIN64)

	// Plateforme Windows
	#define NKENTSUU_PLATFORM_WINDOWS64
	#define NKENTSUU_PLATFORM_WINDOWS
	#define STR_PLATFORM "Window64"
	#ifndef NOMINMAX
	#define NOMINMAX
	#endif

	// Ajoutez la détection UWP ici
	#if defined(USE_UWP)
	#define NKENTSUU_PLATFORM_UWP
		#define STR_PLATFORM "UWP64"
	#endif

#elif defined(_WIN32)

	// Plateforme Windows
	#define NKENTSUU_PLATFORM_WINDOWS32
	#define NKENTSUU_PLATFORM_WINDOWS
	#define STR_PLATFORM "Window32"
	#ifndef NOMINMAX
		#define NOMINMAX
	#endif

	// Ajoutez la détection UWP ici
	#if defined(USE_UWP)
	#define NKENTSUU_PLATFORM_UWP
		#define STR_PLATFORM "UWP32"
	#endif

#elif defined(__APPLE__) && defined(__MACH__)

	// Plateforme Apple, verification de laquelle il s'agit
	#include "TargetConditionals.h"

	#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR

		// iOS
		#define NKENTSUU_PLATFORM_IOS
		#define NKENTSUU_PLATFORM_APPLE
		#define STR_PLATFORM "IOS"

		// Ajoutez la détection UIKit ici
		#if defined(USE_UIKIT)
		#define NKENTSUU_PLATFORM_UIKIT
		#define STR_PLATFORM "UIKIT"
		#endif

	#elif TARGET_OS_MAC

		// MacOS
		#define NKENTSUU_PLATFORM_MACOS
		#define NKENTSUU_PLATFORM_APPLE
		#define STR_PLATFORM "Macos"

	#else

		// Syst�me Apple non pris en charge
		#error Ce systeme d'exploitation Apple n'est pas pris en charge par la bibliotheque NKENTSUU
		#define STR_PLATFORM "NotDefine"

	#endif

#elif defined(__unix__)

	// Systeme UNIX, v�rification duquel il s'agit
	#if defined(__ANDROID__) || defined(ANDROID)

		// Android
		#define NKENTSUU_PLATFORM_ANDROID
		#define NKENTSUU_PLATFORM_UNIX
		#define STR_PLATFORM "Android"

	#elif defined(__linux__)

		// Linux
		#define NKENTSUU_PLATFORM_LINUX
		#define NKENTSUU_PLATFORM_UNIX
		#define STR_PLATFORM "Linux"

		// Ajoutez la détection XCB ici
		#if defined(USE_XCB)
		#define NKENTSUU_PLATFORM_XCB
		#define STR_PLATFORM "XCB"
		#endif

		// Ajoutez la détection Xlib ici
		#if defined(USE_XLIB)
		#define NKENTSUU_PLATFORM_XLIB
		#define STR_PLATFORM "XLIB"
		#endif

		// Ajoutez la détection WAYLAND ici
		#if defined(USE_WAYLAND)
		#define NKENTSUU_PLATFORM_WAYLAND
		#define STR_PLATFORM "Wayland"
		#endif

	#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)

		// FreeBSD
		#define NKENTSUU_PLATFORM_FREEBSD
		#define NKENTSUU_PLATFORM_UNIX
		#define STR_PLATFORM "FreeBSD"

	#elif defined(__OpenBSD__)

		// OpenBSD
		#define NKENTSUU_PLATFORM_OPENBSD
		#define NKENTSUU_PLATFORM_UNIX
		#define STR_PLATFORM "OpenBSD"

	#elif defined(__NetBSD__)

		// NetBSD
		#define NKENTSUU_PLATFORM_NETBSD
		#define NKENTSUU_PLATFORM_UNIX
		#define STR_PLATFORM "NetBSD"

	#elif defined(__NDS__)

        // Nintendo DS
        #define NKENTSUU_PLATFORM_NDS
        #define NKENTSUU_PLATFORM_GAME_CONSOLE
		#define STR_PLATFORM "NDS"

    #elif defined(__PS4__)

        // PlayStation 4
        #define NKENTSUU_PLATFORM_PS4
        #define NKENTSUU_PLATFORM_GAME_CONSOLE
		#define STR_PLATFORM "PS4"

    #elif defined(__PS5__)

        // PlayStation 5
        #define NKENTSUU_PLATFORM_PS5
        #define NKENTSUU_PLATFORM_GAME_CONSOLE
		#define STR_PLATFORM "PS5"

    #elif defined(__PS3__)

        // PlayStation 3
        #define NKENTSUU_PLATFORM_PS3
        #define NKENTSUU_PLATFORM_GAME_CONSOLE
		#define STR_PLATFORM "PS3"

    #elif defined(__PS2__)

        // PlayStation 2
        #define NKENTSUU_PLATFORM_PS2
        #define NKENTSUU_PLATFORM_GAME_CONSOLE
		#define STR_PLATFORM "PS2"

    #elif defined(__XBOX__)

        // Xbox
        #define NKENTSUU_PLATFORM_XBOX
        #define NKENTSUU_PLATFORM_GAME_CONSOLE
		#define STR_PLATFORM "XBOX"

	#else

	// Systeme UNIX non pris en charge
	#error Ce systeme d'exploitation UNIX n'est pas pris en charge par la bibliotheque NKENTSUU
	#define STR_PLATFORM "NotDefine"

	#endif

#elif defined(NDS)
	// Nintendo DS
    #define NKENTSUU_PLATFORM_NINTENDO_DS 7
	#define STR_PLATFORM "NDS"

#elif defined(__EMSCRIPTEN__)
	// WebAssembly
	#define NKENTSUU_PLATFORM_WASM
	#define STR_PLATFORM "WASM"

#else

	// Syst�me non pris en charge
	#define NKENTSUU_PLATFORM_NO_DEFINE
	#error Ce systeme d'exploitation n'est pas pris en charge par la bibliotheque NKENTSUU
	#define STR_PLATFORM "NotDefine"

#endif



////////////////////////////////////////////////////////////
// Definition d'aides pour creer des macros d'importation/exportation portables pour chaque module
////////////////////////////////////////////////////////////
#ifndef NKENTSUU_STATIC

	#if defined(NKENTSUU_PLATFORM_WINDOWS)

	// Les compilateurs Windows necessitent des mots-cles specifiques (et diff�rents) pour l'exportation et l'importation
	#define NKENTSUU_API_EXPORT __declspec(dllexport)
	#define NKENTSUU_API_IMPORT __declspec(dllimport)

	// Pour les compilateurs Visual C++, nous devons egalement desactiver cet avertissement ennuyeux C4251
	#ifdef _MSC_VER
		#pragma warning(disable : 4251)
	#endif

	#else // Linux, FreeBSD, Mac OS X

	#define NKENTSUU_API_EXPORT __attribute__((__visibility__("default")))
	#define NKENTSUU_API_IMPORT __attribute__((__visibility__("default")))

	#endif

#else

// La compilation statique n'a pas besoin de macros d'importation/exportation
#define NKENTSUU_API_EXPORT
#define NKENTSUU_API_IMPORT

#endif

#ifdef NKENTSUU_EXPORTS
	#define NKENTSUU_API NKENTSUU_API_EXPORT
#else
	#define NKENTSUU_API NKENTSUU_API_IMPORT
#endif

// Inlining
#if defined(__clang__) || defined(__gcc__)

#define NKENTSUU_INLINE			__attribute__((always_inline)) inline
#define NKENTSUU_NO_INLINE		__attribute__((noinline))

#elif defined(_MSC_VER)

#define NKENTSUU_INLINE			__forceinline
#define NKENTSUU_NO_INLINE		__declspec(noinline)

#else

#define NKENTSUU_INLINE			static inline
#define NKENTSUU_NO_INLINE

#endif

#ifdef NKENTSUU_DEBUG
	#include <cassert>
	#if defined(NKENTSUU_PLATFORM_WINDOWS)
		#define NKENTSUU_ASSERT_BREAK __debugbreak();
	#elif defined(NKENTSUU_PLATFORM_UNIX)
		#include <signal.h>
		#define NKENTSUU_ASSERT_BREAK raise(SIGTRAP);
	#elif defined(NKENTSUU_PLATFORM_APPLE)
		#define NKENTSUU_ASSERT_BREAK __builtin_debugtrap();
	#else
		#error "Platform doesn't support debugbreak yet!"
		#define NKENTSUU_ASSERT_BREAK
	#endif
#endif

#include <string>

namespace nkentsuu{
	class Platform{
		public:
		static std::string GetPlatform(){
			return STR_PLATFORM;
		}

		static bool IsExport(){
			#ifdef NKENTSUU_EXPORTS
				return true;
			#else
				return false;
			#endif
		}

		static bool IsStaticLinking(){
			#if !defined(NKENTSUU_STATIC)
				return false;
			#else
				return true;
			#endif
		}
	};
}


#endif /* __PLATFORM_H_HEADER__ */
