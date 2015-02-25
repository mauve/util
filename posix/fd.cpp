/*
 * Copyright (C) 2012, All rights reserved, Mikael Olenfalk <mikael@olenfalk.se>
 */

#include <posix/fd.hpp>
#include <iostream>
#include <cerrno>

#ifdef _WIN32
#include <io.h>
#endif

namespace posix {

fd::fd (int fdnum)
	: _fd(fdnum)
{}

fd::fd (fd&& other)
	: _fd(other._fd)
{
	other._fd = -1;
}

fd::fd ()
	: _fd(-1)
{}

fd::~fd ()
{
	close ();
}

bool fd::valid () const
{
	return _fd >= 0;
}

boost::system::error_code fd::close ()
{
	if (_fd < 0)
		return boost::system::error_code(boost::system::errc::success,
				boost::system::generic_category());

#ifdef _WIN32
	::_close(_fd);
#else
  ::close(fd);
#endif
	return boost::system::error_code(errno,
			boost::system::generic_category());
}

void fd::assign (int fdnum)
{
	(void) close();
	_fd = fdnum;
}

int fd::get () const
{
	return _fd;
}

fd& fd::operator= (fd&& other)
{
	assign (other._fd);
	other._fd = -1;
	return *this;
}

bool operator== (const fd& l, const fd& r)
{
	return l.get() == r.get();
}

bool operator!= (const fd& l, const fd& r)
{
	return l.get() != r.get();
}

bool operator<  (const fd& l, const fd& r)
{
	return l.get() < r.get();
}

std::ostream& operator<< (std::ostream& os, const fd& f)
{
	return os << f.get();
}

}  // namespace posix

