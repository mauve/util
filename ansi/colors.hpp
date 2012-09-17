/*
 * Copyright (C) 2012, All rights reserved, Mikael Olenfalk <mikael@olenfalk.se>
 */

/**
 * @file
 *
 * @brief A simple API to add ANSI coloring to programs using IOstream
 *
 * On *NIX terminals colors can be added to console programs by printing
 * ANSI control sequences to stdout or stderr. Usually this functionality
 * is only supported when stdout and stderr are interactive. On POSIX systems
 * isatty() can be used to check whether stdout is a TTY or not, on Windows
 * the function is called _isatty().
 *
 * @example ansi/color.cpp
 */


#ifndef UTIL_ANSI_COLORS_HPP_
#define UTIL_ANSI_COLORS_HPP_

#include <iostream>
#include <locale>
#include <string>

namespace util {

namespace ansi {

/**
 * @brief The available colors
 *
 * When streaming these to an std::ostream directly they will
 * converted to its string-name so.
 *
 * @code
 *   std::cout << util::ansi::black << std::endl;
 * @endcode
 *
 * Will result in the string "black" being printed to std::cout,
 * in order to change the color use the class color_setting instead.
 */
enum color_t {
	black, red, green, yellow, blue, magenta,
	cyan, white, ignore, default_setting
};

class color_setting;

/**
 * @brief A facet which needs to be imbued into the std::ostream
 *        so that colors can be changed.
 *
 * The facet handles all the actual interaction with the console,
 * in order to enable colors for a std::ostream you have to imbue
 * it first:
 *
 * @code
 *   if (std::isatty(STDOUT_FILENO)) {
 * 	   std::locale loc(std::locale(), new util::ansi::color_facet(true));
 *     std::cout.imbue(loc);
 *   }
 * @endcode
 *
 * None of the API in this file has any effect unless a facet
 * has been imbued first.
 */
class color_facet :
	public std::locale::facet
{
public:
	static const std::locale::id id;

	/** @brief Constructs a <b>disabled</b> facet. */
	color_facet ();
	/** @brief Constructs a facet. */
	color_facet (bool enabled);

	/** @brief Enables or disables the facet. */
	void enable (bool enabled) const;
	/** @brief Returns whether the facet is enabled or not. */
	bool is_enabled () const;

	/**
	 * @brief Resets the stream to its default color setting.
	 *
	 * Usually you do not call this method yourself instead you
	 * use util::ansi::reset_all() like this:
	 *
	 * @code
	 *   std::cout << util::ansi::reset_all;
	 * @endcode
	 */
	void apply_reset (std::ostream& os) const;

	/** @brief Changes the color settings according to the settings
	 *         stored in @a set.
	 *
	 * Usually you do not call this method yourself instead you
	 * use color_setting like this:
	 *
	 * @code
	 *   using namespace util::ansi;
	 *   std::cout << color_setting(red, white) << "Hello" << std::endl;
	 * @endcode
	 */
	void apply_color (std::ostream& os, const color_setting& set) const;

private:
	mutable bool _is_enabled;
};

/**
 * @brief Foreground and background setting.
 *
 * In order to change the color of the output of a stream you
 * use this class to first represent a color combination and
 * then you stream it to a std::ostream with the color_facet
 * imbued.
 *
 * @code
 *   using namespace util::ansi;
 *   std::cout << color_setting(red, white) 
 *             << "Red text on white background" << std::endl;
 *
 *   color_setting warning_color(yellow);
 *   std::cout << warning_color << "This is a warning" << std::endl;
 * @endcode
 */
class color_setting
{
public:
	/**
	 * @brief Creates a color_setting object with the
	 *        specified foreground and background colors.
	 *
	 * Creates a color_setting object with the specified foreground
	 * color of @a fg and background color of @bg.
	 * To specify a color_setting with only foreground or background
	 * color specified set the other property to util::ansi::ignore.
	 */
	color_setting (color_t fg, color_t bg = ignore);

	/** @brief Returns the specified foreground color */
	color_t foreground() const;
	/** @brief Returns the specified background color */
	color_t background() const;

private:
	color_t _fg, _bg;
};

/**
 * @brief Resets all color properties to their defaults.
 *
 * In order to reset the colors on a stream pipe this
 * function into the stream:
 *
 * @code
 *   std::cout << util::ansi::reset_all << std::endl;
 * @endcode
 */
std::ostream& reset_all (std::ostream& os);

// just prints the color's name
std::ostream& operator<< (std::ostream& os, const color_t clr);

/**
 * @brief Changes the color setting of the stream.
 *
 * If a color_facet has been imbued on the stream changes the color
 * setting on the stream to the settings specified in the
 * color_settings object.
 *
 * If the stream has no color_facet or if the color_facet has
 * its enabled flag set to false then this operation will not
 * have any effects.
 *
 * @code
 *   using namespace util::ansi;
 *   std::cout << color_setting(red, white) 
 *             << "Red text on white background" << std::endl;
 *
 *   color_setting warning_color(yellow);
 *   std::cout << warning_color << "This is a warning" << std::endl;
 * @endcode
 */
std::ostream& operator<< (std::ostream& os, const color_setting& set);

/**
 * @brief Converts from a string to color_t.
 *
 * For example the string "black" is converted to the enum
 * value of black. If the parameter @a color_name is not
 * any of the names specified in the enum color_t the value
 * default_setting is returned.
 */
color_t from_string (const std::string& color_name);

/**
 * @brief Converts from color_t to string.
 *
 * For example converts the color_t value black is converted
 * to "black". If the parameter @a color is not any of the
 * specified enum color_t values then "default_setting" is
 * returned.
 */
std::string to_string (color_t color);

/*
 * Predefined color_settings for ease of use.
 */
extern const color_setting
	fg_black, /**< foreground black, background ignore */
	fg_red, /**< foreground red, background ignore */
	fg_green, /**< foreground green, background ignore */
	fg_yellow, /**< foreground yellow, background ignore */
	fg_blue, /**< foreground blue, background ignore */
	fg_magenta, /**< foreground magenta, background ignore */
	fg_cyan, /**< foreground cyan, background ignore */
	fg_white, /**< foreground white, background ignore */
	fg_default_setting, /**< foreground default, background ignore */
	bg_black, /**< foreground ignore, background black */
	bg_red, /**< foreground ignore, background red */
	bg_green, /**< foreground ignore, background green */
	bg_yellow, /**< foreground ignore, background yellow */
	bg_blue, /**< foreground ignore, background blue */
	bg_magenta, /**< foreground ignore, background magenta */
	bg_cyan, /**< foreground ignore, background cyan */
	bg_white, /**< foreground ignore, background white */
	bg_default_setting; /**< foreground ignore, background default */

}  // namespace ansi

}  // namespace util

#endif /* UTIL_ANSI_COLORS_HPP_ */
