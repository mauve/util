/*
 * Copyright (C) 2012, All rights reserved, Mikael Olenfalk <mikael@olenfalk.se>
 */

/*
 * simple trick to remove the need for conditional
 */

#include <process/child_options.hpp>
#include <process/stream_id.hpp>
#include <process/stream_descriptor.hpp>

#define __UTIL_PROCESS__DETAIL_SPAWNER_CPP__INCLUDING 1
#ifdef _WIN32
#	include "spawner_win32_create_process.hpp"
#else
#	include "spawner_posix_spawn.hpp"
#endif
