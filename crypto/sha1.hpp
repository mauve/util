/*
 * sha1_hmac.hpp
 *
 *  Created on: Aug 13, 2012
 *      Author: olenfalk
 */

#ifndef SHA1_HMAC_HPP_
#define SHA1_HMAC_HPP_

#include <string>

#include <boost/smart_ptr/scoped_ptr.hpp>
#include <boost/noncopyable.hpp>

namespace util {

namespace crypto {

std::string sha1_compute_hash (const char* buffer, std::size_t length);
std::string sha1_compute_hash (const std::string& buffer);

class sha1 :
	public boost::noncopyable
{
public:
	sha1 ();
	~sha1 ();

	void input (const char* buffer, std::size_t length);
	void input (const std::string& buffer);

	std::string finish ();

private:
	struct context;
	boost::scoped_ptr<context> _context;
};

class sha1_hmac :
	public boost::noncopyable
{
public:
	sha1_hmac ();
	sha1_hmac (const std::string& key);
	sha1_hmac (const char* key, std::size_t length);
	~sha1_hmac ();

	void reset (const char* key, std::size_t length);
	void reset (const std::string& key);

	void input (const char* buffer, std::size_t length);
	void input (const std::string& buffer);

	std::string finish ();

private:
	struct context;
	boost::scoped_ptr<context> _context;
};

}  // namespace crypto

}  // namespace util


#endif /* SHA1_HMAC_HPP_ */
