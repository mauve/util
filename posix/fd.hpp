/*
 * Copyright (C) 2012, All rights reserved, Mikael Olenfalk <mikael@olenfalk.se>
 */

#ifndef UTIL_POSIX_FD_HPP_
#define UTIL_POSIX_FD_HPP_

#include <iosfwd>

#include <boost/noncopyable.hpp>
#include <boost/system/error_code.hpp>

namespace posix {

class fd :
  boost::noncopyable
{
public:
	explicit fd (int fdnum);
	fd (fd&& other);
	fd ();
	~fd ();

	bool valid () const;

	boost::system::error_code close ();
	void assign (int fdnum);
	int get () const;

	fd& operator= (fd&& other);

private:
	int _fd;
};

bool operator== (const fd& l, const fd& r);
bool operator!= (const fd& l, const fd& r);
bool operator<  (const fd& l, const fd& r);

std::ostream& operator<< (std::ostream& os, const fd& f);

}  // namespace posix

#endif /* UTIL_POSIX_FD_HPP_ */
