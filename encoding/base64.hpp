
#ifndef __ENCODING__BASE64_HPP__
#define __ENCODING__BASE64_HPP__

#include <string>
#include <vector>
#include <cstdint>

namespace encoding
{
namespace base64
{

/*** Returns whether @a c is a valid base64 character */
bool is_base64(std::uint8_t c);

/*** Returns the base64 length of a blob of length @a length */
std::size_t compute_encoded_length(std::size_t length);

/*** Returns the base64 encoded version of @a blob of length @a length */
std::string encode(const std::uint8_t* blob, std::size_t length);

/*** Returns the base64 encoded version of @a blob */
std::string encode(const std::vector<std::uint8_t>& blob);

/*** Encodes the blob denoted by @a input and @a input_length into the
 *   the supplied buffer @a output with length @a output_length.
 *
 *   Returns true if the entire @a input was encoded.
 */
bool encode(const std::uint8_t* input, std::size_t input_length,
  char* output, std::size_t output_length);

/*** Returns the decoded blob encoded in @a b64 */
std::vector<std::uint8_t> decode(const std::string& b64);

}  // namespace base64
}  // namespace encoding

#endif  // __BASE64_HPP__