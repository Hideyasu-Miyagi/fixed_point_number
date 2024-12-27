/*
  fixed_point_number.h

*/

#ifndef _FIXED_POINT_NUMBER_H_
#define _FIXED_POINT_NUMBER_H_

#include <cstdint>
#include <cstdio>

namespace fixed_point_number {

struct FXP_S32_31 {
  int64_t value_;
  
  constexpr FXP_S32_31() : value_(0) {}
  constexpr FXP_S32_31(int32_t _numerator, int32_t _denominator = 1) : 
      value_((int64_t)_numerator*0x0000000080000000LL/_denominator) {}
  constexpr FXP_S32_31(const FXP_S32_31& _fxp) : value_(_fxp.value_) {}
  FXP_S32_31 add(const FXP_S32_31& _fxp) const {
      FXP_S32_31 ret;
      ret.value_ = value_ + _fxp.value_;
      return ret;
  }
  FXP_S32_31 sub(const FXP_S32_31& _fxp) const {
      FXP_S32_31 ret;
      ret.value_ = value_ - _fxp.value_;
      return ret;
  }
  FXP_S32_31 mul(const FXP_S32_31& _fxp) const {
      FXP_S32_31 ret;
      ret.value_ = (int64_t)value_ / 0x00008000LL * _fxp.value_ / 0x00010000LL ;
      return ret;
  }
  FXP_S32_31 div(const FXP_S32_31& _fxp) const {
      FXP_S32_31 ret;
      ret.value_ = (int64_t)value_ * 0x00008000LL / _fxp.value_ * 0x00010000LL;
      return ret;
  }
  FXP_S32_31 operator+ (const FXP_S32_31& _value) const { return add(_value); }
  FXP_S32_31 operator- () const { FXP_S32_31 ret; ret.value_ = -value_; return ret; }
  FXP_S32_31 operator- (const FXP_S32_31& _value) const { return sub(_value); }
  FXP_S32_31 operator* (const FXP_S32_31& _value) const { return mul(_value); }
  FXP_S32_31 operator/ (const FXP_S32_31& _value) const { return div(_value); }

  friend bool operator!= (const FXP_S32_31& _a1, const FXP_S32_31& _a2) { return _a1.value_ != _a2.value_; }
  friend bool operator== (const FXP_S32_31& _a1, const FXP_S32_31& _a2) { return !(_a1 != _a2); }
  friend bool operator< (const FXP_S32_31& _a1, const FXP_S32_31& _a2)  { return _a1.value_ <  _a2.value_; }
  friend bool operator<= (const FXP_S32_31& _a1, const FXP_S32_31& _a2) { return _a1.value_ <= _a2.value_; }
  friend bool operator> (const FXP_S32_31& _a1, const FXP_S32_31& _a2)  { return _a1.value_ >  _a2.value_; }
  friend bool operator>= (const FXP_S32_31& _a1, const FXP_S32_31& _a2) { return _a1.value_ >= _a2.value_; }

  const char* toString(char* _buf, size_t _size) const {
      uint64_t int_part, frac_part;
      if (value_ < 0) {
          int_part = ((-value_)>>31)&0x7FFFFFFF;
          frac_part = (-value_)&0x7FFFFFFF;
      } else {
          int_part = ((value_)>>31)&0x7FFFFFFF;
          frac_part = (value_)&0x7FFFFFFF;
      }
      if (value_ < 0) {
          snprintf(_buf, _size, "-%llu.%03llu", int_part, frac_part*10000000000/2147483648);
      } else {
          snprintf(_buf, _size, "%llu.%03llu", int_part, frac_part*10000000000/2147483648);
      }
      return _buf;
  }
  

   int64_t toInt64() const { return value_/0x0000000080000000L; }

};

}

#endif // _FIXED_POINT_NUMBER_H_
