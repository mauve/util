
#include <util/crypto/shannon.hpp>
#include <util/crypto/_detail/shannon_impl.h>

namespace util {

namespace crypto {

struct shannon::context
{
	shn_ctx ctxt;

	shn_ctx* get ()
	{
		return &ctxt;
	}
};

shannon::shannon ()
{}

shannon::shannon(const std::string& key)
{
	set_key (key);
}

shannon::~shannon()
{}

void shannon::set_key (const std::string& key)
{
	set_key (key.c_str(), key.length());
}

void shannon::set_key (const unsigned char* key, std::size_t length)
{
	if (!_context)
		_context.reset (new context);
	shn_key(_context->get(), key, length);
}

void shannon::set_nonce (const std::string& nonce)
{
	set_nonce (nonce.c_str(), nonce.length());
}

void shannon::set_nonce (const unsigned char* nonce, std::size_t length)
{
	if (!_context)
		throw std::invalid_argument("no key set");
	shn_nonce(_context->get(), nonce, length);
}

void shannon::encrypt (unsigned char* buffer, std::size_t length)
{
	if (!_context)
		throw std::invalid_argument("no key set");
	shn_encrypt(_context->get(), buffer, length);
}

void shannon::decrypt (unsigned char* buffer, std::size_t length)
{
	if (!_context)
		throw std::invalid_argument("no key set");
	shn_decrypt(_context->get(), buffer, length);
}

void shannon::finish (unsigned char* buffer, std::size_t length)
{
	if (!_context)
		throw std::invalid_argument("no key set");
	shn_finish(_context->get(), buffer, length);
	return buf;
}

}  // namespace crypto

}  // namespace util
