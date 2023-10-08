#pragma once

#ifdef BT_PLATAFORM_WINDOWS
	#ifdef BT_BUILD_DLL
		#define BATUMO_API __declspec(dllexport)
	#else
		#define BATUMO_API __declspec(dllimport)
	#endif
#else
	#error Batumo only support windows

#endif