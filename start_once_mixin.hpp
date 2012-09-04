/*
 * Copyright (C) 2012, All rights reserved, Mikael Olenfalk <mikael@olenfalk.se>
 */

#ifndef UTIL_START_ONCE_MIXIN_HPP_
#define UTIL_START_ONCE_MIXIN_HPP_

#include <boost/thread/mutex.hpp>

namespace util {

//
// This is a mixin class which
// can be used to remove a lot of boilerplate
// when you implement classes which should
// only be started once
//
class start_once_mixin
{
public:
	start_once_mixin ();
	~start_once_mixin ();

	void start ();
	void stop ();

	bool running () const;

protected:
	// default impl does nothing
	virtual void _on_start ();

	// default impl does nothing
	virtual void _on_stop ();

private:
	mutable boost::mutex _mutex;
	enum { NOT_STARTED, STARTED, STOPPED } _state;
};

}  // namespace util

#endif /* UTIL_START_ONCE_MIXIN_HPP_ */
