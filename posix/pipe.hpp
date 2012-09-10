/*
 * Copyright (C) 2012, All rights reserved, Mikael Olenfalk <mikael@olenfalk.se>
 */

#ifndef UTIL_POSIX_PIPE_HPP_
#define UTIL_POSIX_PIPE_HPP_

#include <boost/move/move.hpp>
#include <boost/system/error_code.hpp>

namespace util {

namespace posix {

class pipe :
	public boost::noncopyable
{
	BOOST_MOVABLE_BUT_NOT_COPYABLE(pipe);

public:
	pipe ();
	pipe (BOOST_RV_REF(pipe) other);
	~pipe ();

	boost::system::error_code close ();

	int read_end () const;
	int steal_read_end ();

	int write_end () const;
	int steal_write_end ();

	pipe& operator= (BOOST_RV_REF(pipe) other);

private:
	int _read, _write;
};

}  // namespace posix

}  // namespace util

#endif /* UTIL_POSIX_PIPE_HPP_ */
