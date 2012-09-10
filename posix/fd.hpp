/*
 * Copyright (C) 2012, All rights reserved, Mikael Olenfalk <mikael@olenfalk.se>
 */

#ifndef UTIL_POSIX_FD_HPP_
#define UTIL_POSIX_FD_HPP_

#include <iosfwd>

#include <boost/system/error_code.hpp>
#include <boost/move/move.hpp>

namespace util {

namespace posix {

class fd
{
	BOOST_MOVABLE_BUT_NOT_COPYABLE(fd);

public:
	explicit fd (int fdnum);
	fd (BOOST_RV_REF(fd) other);
	fd ();
	~fd ();

	bool valid () const;

	boost::system::error_code close ();
	void assign (int fdnum);
	int get () const;

	fd& operator= (int fdnum);
	fd& operator= (BOOST_RV_REF(fd) other);

private:
	int _fd;
};

bool operator== (const fd& l, const fd& r);
bool operator!= (const fd& l, const fd& r);
bool operator<  (const fd& l, const fd& r);

std::ostream& operator<< (std::ostream& os, const fd& f);

}  // namespace posix

}  // namespace util

#endif /* UTIL_POSIX_FD_HPP_ */
