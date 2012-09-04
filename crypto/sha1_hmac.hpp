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

class sha1_hmac
{
public:
	sha1_hmac ();
	sha1_hmac (const std::string& key);

	void reset (const unsigned char* key, std::size_t length);
	void reset (const std::string& key);

	void input (const unsigned char* buffer, std::size_t length);

	std::string finish ();

private:
	struct context;
	boost::scoped_ptr<context> _context;
};

}  // namespace crypto

}  // namespace util


#endif /* SHA1_HMAC_HPP_ */
