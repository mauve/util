
#include <crypto/sha1_hmac.hpp>
#include <crypto/_detail/sha1.h>

#include <stdexcept>

namespace util {

namespace crypto {

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

