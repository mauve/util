#ifndef __MATH__ROUND_UP_HPP__
#define __MATH__ROUND_UP_HPP__

namespace math
{

/*** Rounds up @a input to next multiple of @a multiple */
template <typename Integer>
inline Integer round_up(Integer input, Integer multiple)
{
  if (multiple == 0) {
    return input;
  }

  auto remainder = input % multiple;
  if (remainder == 0)
    return input;
  return input + multiple - remainder;
}

}  // namespace math

#endif  // __ROUND_UP_HPP__