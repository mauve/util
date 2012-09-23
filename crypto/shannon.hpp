
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
	~shannon ();

	void set_key (const char* key, std::size_t length);

	void set_nonce (const char* nonce, std::size_t length);

	template <typename T>
	typename boost::enable_if< boost::is_pod<T> >::type
	set_nonce (typename boost::call_traits<T>::type nonce)
	{
		set_nonce ((const char*)&nonce, sizeof(nonce));
	}

	void encrypt (char* buffer, std::size_t length);
	void decrypt (char* buffer, std::size_t length);

	void finish (char* buffer, std::size_t length);

	template <typename T>
	typename boost::enable_if< boost::is_pod<T>, T>::type
	finish ()
	{
		T result;
		finish ((char*)&result, sizeof(result));
		return result;
	}

private:
	struct context;
	boost::scoped_ptr<context> _context;
};

}  // namespace crypto

}  // namespace util


#endif /* SHANNON_HPP_ */
