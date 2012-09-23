
#include <crypto/shannon.hpp>
#include <crypto/_detail/shannon_impl.h>

#include <stdexcept>

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

void shannon::set_key (const char* key, std::size_t length)
{
	if (!_context)
		_context.reset (new context);
	shn_key(_context->get(), const_cast<unsigned char*>((const unsigned char*)key), length);
}

void shannon::set_nonce (const std::string& nonce)
{
	set_nonce (nonce.c_str(), nonce.length());
}

void shannon::set_nonce (const char* nonce, std::size_t length)
{
	if (!_context)
		throw std::invalid_argument("no key set");
	shn_nonce(_context->get(), const_cast<unsigned char*>((const unsigned char*)nonce), length);
}

void shannon::encrypt (char* buffer, std::size_t length)
{
	if (!_context)
		throw std::invalid_argument("no key set");
	shn_encrypt(_context->get(), (unsigned char*)buffer, length);
}

void shannon::decrypt (char* buffer, std::size_t length)
{
	if (!_context)
		throw std::invalid_argument("no key set");
	shn_decrypt(_context->get(), (unsigned char*)buffer, length);
}

void shannon::finish (char* buffer, std::size_t length)
{
	if (!_context)
		throw std::invalid_argument("no key set");
	shn_finish(_context->get(), (unsigned char*)buffer, length);
}

}  // namespace crypto

}  // namespace util
