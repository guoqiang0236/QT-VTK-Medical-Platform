#pragma once
#ifdef GLOBALCONFIG_EXPORTS
#define GLOBALCONFIG_API __declspec(dllexport)
#else
#define GLOBALCONFIG_API __declspec(dllimport)
#endif