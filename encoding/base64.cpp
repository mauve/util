
#include "base64.hpp"
#include "math/round_up.hpp"

namespace base64
{

static const std::string base64_chars =
  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
  "abcdefghijklmnopqrstuvwxyz"
  "0123456789+/";


inline bool is_base64(std::uint8_t c)
{
  return (isalnum(c) || (c == '+') || (c == '/'));
}

std::size_t compute_encoded_length(std::size_t length)
{
  return math::round_up(4 * (length / 3), 4u);
}

bool encode(const std::uint8_t* input, std::size_t input_length,
  char* output, std::size_t output_length)
{
  if (!input || !output || !output_length)
    return false;

  int i = 0;
  int j = 0;
  std::uint8_t char_array_3[3];
  std::uint8_t char_array_4[4];
  char* output_end = output + output_length;

  while (input_length--) {
    char_array_3[i++] = *(input++);
    if (i == 3) {
      char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
      char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
      char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
      char_array_4[3] = char_array_3[2] & 0x3f;

      for (i = 0; i < 4; i++) {
        if (output == output_end)
          return false;
        *output++ += base64_chars[char_array_4[i]];
      }

      i = 0;
    }
  }

  if (i)
  {
    for (j = i; j < 3; j++)
      char_array_3[j] = '\0';

    char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
    char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
    char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
    char_array_4[3] = char_array_3[2] & 0x3f;

    for (j = 0; (j < i + 1); j++) {
      if (output == output_end)
        return false;
      *output++ += base64_chars[char_array_4[j]];
    }

    while ((i++ < 3)) {
      if (output == output_end)
        return false;
      *output++ += '=';
    }
  }

  return true;
}

std::string encode(const std::uint8_t* buf, std::size_t length)
{
  std::string ret;
  ret.resize(compute_encoded_length(length));

  if (!encode(buf, length, &ret[0], ret.size()))
    throw std::runtime_error("encode error");
  return ret;
}

std::string encode(const std::vector<std::uint8_t>& blob)
{
  return encode(blob.data(), blob.size());
}

std::vector<std::uint8_t> decode(const std::string& encoded_string)
{
  int in_len = encoded_string.size();
  int i = 0;
  int j = 0;
  int in_ = 0;
  std::uint8_t char_array_4[4], char_array_3[3];
  std::vector<std::uint8_t> ret;

  while (in_len-- && (encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
    char_array_4[i++] = encoded_string[in_]; in_++;
    if (i == 4) {
      for (i = 0; i <4; i++)
        char_array_4[i] = base64_chars.find(char_array_4[i]);

      char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
      char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
      char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

      for (i = 0; (i < 3); i++)
        ret.push_back(char_array_3[i]);
      i = 0;
    }
  }

  if (i) {
    for (j = i; j <4; j++)
      char_array_4[j] = 0;

    for (j = 0; j <4; j++)
      char_array_4[j] = base64_chars.find(char_array_4[j]);

    char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
    char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
    char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

    for (j = 0; (j < i - 1); j++) ret.push_back(char_array_3[j]);
  }

  return ret;
}

}  // namespace base64