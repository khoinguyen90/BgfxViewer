#include "Platform.h"

namespace MimicViewer
{
	extern void print(const char* format, ...)
	{
		MV_ASSERT(format);

		static char buffer[4096] = "";

		va_list argptr;
		va_start(argptr, format);
		vsprintf(buffer, format, argptr);
		va_end(argptr);

		std::cout << buffer << std::flush;
	}

	extern int strcmpnocase(const char* s1, const char* s2)
	{
#ifdef GP_PLATFORM_LINUX
		return strcasecmp(s1, s2);
#elif GP_PLATFORM_WINDOWS
		return _strcmpi(s1, s2);
#elif GP_PLATFORM_MACOS
		return strcasecmp(s1, s2);
#elif GP_PLATFORM_ANDROID
		return strcasecmp(s1, s2);
#elif GP_PLATFORM_IOS
		return strcasecmp(s1, s2);
#else
		GP_ERROR("Fix me !");
		return 0;
#endif
	}
}