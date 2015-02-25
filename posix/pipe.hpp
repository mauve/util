/*
 * Copyright (C) 2012, All rights reserved, Mikael Olenfalk <mikael@olenfalk.se>
 */

#ifndef UTIL_POSIX_PIPE_HPP_
#define UTIL_POSIX_PIPE_HPP_

#include <boost/noncopyable.hpp>
#include <boost/system/error_code.hpp>

namespace posix {

class pipe :
	public boost::noncopyable
{
public:
	pipe ();
	pipe (pipe&& other);
	~pipe ();

	boost::system::error_code close ();

	int read_end () const;
	int steal_read_end ();

	int write_end () const;
	int steal_write_end ();

	pipe& operator= (pipe&& other);

private:
	int _read, _write;
};

}  // namespace posix

#endif /* UTIL_POSIX_PIPE_HPP_ */
