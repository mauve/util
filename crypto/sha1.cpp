
#include <crypto/sha1.hpp>
#include <crypto/_detail/sha1.h>

#include <stdexcept>

namespace util {

namespace crypto {

/*
 * sha1_compute_hash
 */
std::string sha1_compute_hash (const char* buffer, std::size_t length)
{
	unsigned char digest[20];
	ShaHash((const unsigned char*)buffer, length, digest);
	return std::string(digest, digest + 20);
}

std::string sha1_compute_hash (const std::string& buffer)
{
	return sha1_compute_hash (buffer.c_str(), buffer.length());
}

/*
 * sha1
 */

struct sha1::context
{
	SHA1Context ctx;

	SHA1Context* get ()
	{
		return &ctx;
	}
};

sha1::sha1 ()
	: _context(new context)
{}

sha1::~sha1 ()
{}

void sha1::input (const char* buffer, std::size_t length)
{
	SHA1Input(_context->get(), (const unsigned char*)buffer, length);
}

void sha1::input (const std::string& buffer)
{
	SHA1Input(_context->get(), (const unsigned char*)buffer.c_str(), buffer.length());
}

std::string sha1::finish ()
{
	unsigned char digest[20];
	SHA1Finish(_context->get(), digest);
	return std::string(digest, digest + 20);
}

/*
 * sha1_hmac
 */

struct sha1_hmac::context
{
	SHA1HmacContext ctx;

	SHA1HmacContext* get ()
	{
		return &ctx;
	}
};

sha1_hmac::sha1_hmac ()
{}

sha1_hmac::sha1_hmac (const std::string& key)
{
	reset (key);
}

sha1_hmac::sha1_hmac (const char* key, std::size_t length)
{
	reset (key, length);
}

sha1_hmac::~sha1_hmac ()
{}

void sha1_hmac::reset (const std::string& key)
{
	reset (key.c_str(), key.length());
}

void sha1_hmac::reset (const char* key, std::size_t length)
{
	if (!_context)
		_context.reset(new context);
	SHA1HmacReset(_context->get(), (const unsigned char*)key, length);
}

void sha1_hmac::input (const char* buffer, std::size_t length)
{
	if (!_context)
		throw std::invalid_argument("no key set");
	SHA1HmacInput(_context->get(), (const unsigned char*)buffer, length);
}

void sha1_hmac::input (const std::string& buffer)
{
	input (buffer.c_str(), buffer.length());
}

std::string sha1_hmac::finish ()
{
	if (!_context)
		throw std::invalid_argument("no key set");
	std::string result;
	unsigned char digest[20];
	SHA1HmacFinish(_context->get(), digest);
	result.assign(digest, digest + 20);
	return result;
}

}  // namespace crypto

}  // namespace util

