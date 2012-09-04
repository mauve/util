/*
 * Copyright (C) 2012, All rights reserved, Mikael Olenfalk <mikael@olenfalk.se>
 */

#include <util/start_once_mixin.hpp>

#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>

namespace util {

start_once_mixin::start_once_mixin()
	: _state(NOT_STARTED)
{}

start_once_mixin::~start_once_mixin()
{
	stop ();
}

void start_once_mixin::start ()
{
	boost::unique_lock<boost::mutex> lock(_mutex);

	if (_state != NOT_STARTED)
		return;

	_state = STARTED;
	_on_start ();
}

void start_once_mixin::stop ()
{
	boost::unique_lock<boost::mutex> lock(_mutex);

	if (_state != STARTED)
		return;

	_state = STOPPED;
	_on_stop ();
}

bool start_once_mixin::running () const
{
	boost::unique_lock<boost::mutex> lock(_mutex);

	return _state == STARTED;
}

void start_once_mixin::_on_start ()
{
	// default impl does nothing
}

void start_once_mixin::_on_stop ()
{
	// default impl does nothing
}

}  // namespace util

