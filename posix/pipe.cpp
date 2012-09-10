/*
 * Copyright (C) 2012, All rights reserved, Mikael Olenfalk <mikael@olenfalk.se>
 */

#include "pipe.hpp"

#include <unistd.h>

#include <boost/system/error_code.hpp>
#include <boost/system/system_error.hpp>

namespace util {

namespace posix {

pipe::pipe ()
	: _read(-1), _write(-1)
{
	int pipes[2] = {0};
	if (::pipe(pipes) < 0)
	{
		throw boost::system::system_error(errno,
				boost::system::get_posix_category());
	}

	_read  = pipes[0];
	_write = pipes[1];
}

pipe::pipe (BOOST_RV_REF(pipe) other)
	: _read(other.steal_read_end()),
	  _write(other.steal_write_end())
{}

pipe::~pipe ()
{
	(void) close();
}

boost::system::error_code pipe::close ()
{
	int errno_code = 0;
	if (_read != -1) {
		if (::close(_read) < 0)
			errno_code = errno;
	}

	if (_write != -1) {
		if (::close(_write) < 0)
			errno_code = errno;
	}

	_read = -1;
	_write = -1;

	return boost::system::error_code(errno_code,
			boost::system::get_posix_category());
}

int pipe::read_end() const
{
	return _read;
}

int pipe::steal_read_end()
{
	int r = _read;
	_read = -1;
	return r;
}

int pipe::write_end() const
{
	return _write;
}

int pipe::steal_write_end()
{
	int w = _write;
	_write = -1;
	return w;
}

pipe& pipe::operator= (BOOST_RV_REF(pipe) other)
{
	close ();
	_read = other.steal_read_end();
	_write = other.steal_write_end();
	return *this;
}

}  // namespace posix

}  // namespace util
