
#include <iostream>

#include <ansi/colors.hpp>

// a little dancing for isatty
#ifdef BOOST_WINDOWS_API
#	include <io.h>
#	define isatty _isatty
#elif BOOST_POSIX_API
#	ifdef BOOST_HAS_UNISTD_H
#		include <unistd.h>
#	else
int isatty(int)
{
	return true;
}
#	endif
#endif

using namespace util::ansi;

int main (int argc, char* argv[])
{
	if (isatty(STDOUT_FILENO)) {
		std::locale loc(std::locale(), new color_facet(true));
		std::cout.imbue(loc);
	}

	std::cout << color_setting(green) << "Hello Green World!" << reset_all << std::endl;
	return 0;
}