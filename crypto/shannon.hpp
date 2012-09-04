
#ifndef SHANNON_HPP_
#define SHANNON_HPP_

#include <string>
#include <vector>

#include <boost/noncopyable.hpp>
#include <boost/smart_ptr/scoped_ptr.hpp>
#include <boost/type_traits/is_pod.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/call_traits.hpp>

namespace util {

namespace crypto {

class shannon :
	public boost::noncopyable
{
public:
	shannon ();
	shannon (const std::string& key);
	~shannon ();

	void set_key (const std::string& key);
	void set_key (const unsigned char* key, std::size_t length);

	void set_nonce (const std::string& nonce);
	void set_nonce (const unsigned char* nonce, std::size_t length);

	template <typename T>
	typename boost::enable_if< boost::is_pod<T> >::type
	set_nonce (boost::call_traits<T>::type nonce)
	{
		set_nonce (&nonce, sizeof(nonce));
	}

	void encrypt (unsigned char* buffer, std::size_t length);
	void decrypt (unsigned char* buffer, std::size_t length);

	void finish (unsigned char* buffer, std::size_t length);

	template <typename T>
	typename boost::enable_if< boost::is_pod<T>, T>::type
	finish ()
	{
		T result;
		finish (&result, sizeof(result));
		return result;
	}

private:
	struct context;
	boost::scoped_ptr<context> _context;
};

}  // namespace crypto

}  // namespace util


#endif /* SHANNON_HPP_ */
