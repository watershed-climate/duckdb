//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/operator/numeric_cast.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb/common/operator/cast_operators.hpp"
#include "duckdb/common/types/hugeint.hpp"

namespace duckdb {

template <class SRC, class DST>
static bool TryCastWithOverflowCheck(SRC value, DST &result) {
	if (NumericLimits<SRC>::IsSigned() != NumericLimits<DST>::IsSigned()) {
		if (NumericLimits<SRC>::IsSigned()) {
			// signed to unsigned conversion
			if (NumericLimits<SRC>::Digits() > NumericLimits<DST>::Digits()) {
				if (value < 0 || value > (SRC)NumericLimits<DST>::Maximum()) {
					return false;
				}
			} else {
				if (value < 0) {
					return false;
				}
			}
			result = (DST)value;
			return true;
		} else {
			// unsigned to signed conversion
			if (NumericLimits<SRC>::Digits() >= NumericLimits<DST>::Digits()) {
				if (value <= (SRC)NumericLimits<DST>::Maximum()) {
					result = (DST)value;
					return true;
				}
				return false;
			} else {
				result = (DST)value;
				return true;
			}
		}
	} else {
		// same sign conversion
		if (NumericLimits<DST>::Digits() >= NumericLimits<SRC>::Digits()) {
			result = (DST)value;
			return true;
		} else {
			if (value < SRC(NumericLimits<DST>::Minimum()) || value > SRC(NumericLimits<DST>::Maximum())) {
				return false;
			}
			result = (DST)value;
			return true;
		}
	}
}

template <>
bool TryCastWithOverflowCheck(float value, int32_t &result) {
	if (!(value >= -2147483648.0f && value < 2147483648.0f)) {
		return false;
	}
	result = int32_t(value);
	return true;
}

template <>
bool TryCastWithOverflowCheck(float value, int64_t &result) {
	if (!(value >= -9223372036854775808.0f && value < 9223372036854775808.0f)) {
		return false;
	}
	result = int64_t(value);
	return true;
}

template <>
bool TryCastWithOverflowCheck(double value, int64_t &result) {
	if (!(value >= -9223372036854775808.0 && value < 9223372036854775808.0)) {
		return false;
	}
	result = int64_t(value);
	return true;
}

template <>
bool TryCastWithOverflowCheck(double input, float &result) {
	if (input < (double)NumericLimits<float>::Minimum() || input > (double)NumericLimits<float>::Maximum()) {
		return false;
	}
	auto res = (float)input;
	if (std::isnan(res) || std::isinf(res)) {
		return false;
	}
	result = res;
	return true;
}

//===--------------------------------------------------------------------===//
// Cast Numeric -> bool
//===--------------------------------------------------------------------===//
template <>
bool TryCastWithOverflowCheck(bool value, bool &result) {
	result = bool(value);
	return true;
}

template <>
bool TryCastWithOverflowCheck(int8_t value, bool &result) {
	result = bool(value);
	return true;
}

template <>
bool TryCastWithOverflowCheck(int16_t value, bool &result) {
	result = bool(value);
	return true;
}

template <>
bool TryCastWithOverflowCheck(int32_t value, bool &result) {
	result = bool(value);
	return true;
}

template <>
bool TryCastWithOverflowCheck(int64_t value, bool &result) {
	result = bool(value);
	return true;
}

template <>
bool TryCastWithOverflowCheck(uint8_t value, bool &result) {
	result = bool(value);
	return true;
}

template <>
bool TryCastWithOverflowCheck(uint16_t value, bool &result) {
	result = bool(value);
	return true;
}

template <>
bool TryCastWithOverflowCheck(uint32_t value, bool &result) {
	result = bool(value);
	return true;
}

template <>
bool TryCastWithOverflowCheck(uint64_t value, bool &result) {
	result = bool(value);
	return true;
}

template <>
bool TryCastWithOverflowCheck(float value, bool &result) {
	result = bool(value);
	return true;
}

template <>
bool TryCastWithOverflowCheck(double value, bool &result) {
	result = bool(value);
	return true;
}

template <>
bool TryCastWithOverflowCheck(hugeint_t input, bool &result) {
	result = input.upper != 0 || input.lower != 0;
	return true;
}

//===--------------------------------------------------------------------===//
// Cast bool -> Numeric
//===--------------------------------------------------------------------===//
template <>
bool TryCastWithOverflowCheck(bool value, int8_t &result) {
	result = int8_t(value);
	return true;
}

template <>
bool TryCastWithOverflowCheck(bool value, int16_t &result) {
	result = int16_t(value);
	return true;
}

template <>
bool TryCastWithOverflowCheck(bool value, int32_t &result) {
	result = int32_t(value);
	return true;
}

template <>
bool TryCastWithOverflowCheck(bool value, int64_t &result) {
	result = int64_t(value);
	return true;
}

template <>
bool TryCastWithOverflowCheck(bool value, uint8_t &result) {
	result = uint8_t(value);
	return true;
}

template <>
bool TryCastWithOverflowCheck(bool value, uint16_t &result) {
	result = uint16_t(value);
	return true;
}

template <>
bool TryCastWithOverflowCheck(bool value, uint32_t &result) {
	result = uint32_t(value);
	return true;
}

template <>
bool TryCastWithOverflowCheck(bool value, uint64_t &result) {
	result = uint64_t(value);
	return true;
}

template <>
bool TryCastWithOverflowCheck(bool value, float &result) {
	result = float(value);
	return true;
}

template <>
bool TryCastWithOverflowCheck(bool value, double &result) {
	result = double(value);
	return true;
}

template <>
bool TryCastWithOverflowCheck(bool input, hugeint_t &result) {
	result.upper = 0;
	result.lower = input ? 1 : 0;
	return true;
}

//===--------------------------------------------------------------------===//
// Cast Numeric -> hugeint
//===--------------------------------------------------------------------===//
template <>
bool TryCastWithOverflowCheck(int8_t value, hugeint_t &result) {
	return Hugeint::TryConvert(value, result);
}

template <>
bool TryCastWithOverflowCheck(int16_t value, hugeint_t &result) {
	return Hugeint::TryConvert(value, result);
}

template <>
bool TryCastWithOverflowCheck(int32_t value, hugeint_t &result) {
	return Hugeint::TryConvert(value, result);
}

template <>
bool TryCastWithOverflowCheck(int64_t value, hugeint_t &result) {
	return Hugeint::TryConvert(value, result);
}

template <>
bool TryCastWithOverflowCheck(uint8_t value, hugeint_t &result) {
	return Hugeint::TryConvert(value, result);
}

template <>
bool TryCastWithOverflowCheck(uint16_t value, hugeint_t &result) {
	return Hugeint::TryConvert(value, result);
}

template <>
bool TryCastWithOverflowCheck(uint32_t value, hugeint_t &result) {
	return Hugeint::TryConvert(value, result);
}

template <>
bool TryCastWithOverflowCheck(uint64_t value, hugeint_t &result) {
	return Hugeint::TryConvert(value, result);
}

template <>
bool TryCastWithOverflowCheck(float value, hugeint_t &result) {
	return Hugeint::TryConvert(value, result);
}

template <>
bool TryCastWithOverflowCheck(double value, hugeint_t &result) {
	return Hugeint::TryConvert(value, result);
}

template <>
bool TryCastWithOverflowCheck(hugeint_t value, hugeint_t &result) {
	result = value;
	return true;
}

//===--------------------------------------------------------------------===//
// Cast Hugeint -> Numeric
//===--------------------------------------------------------------------===//
template <>
bool TryCastWithOverflowCheck(hugeint_t value, int8_t &result) {
	return Hugeint::TryCast(value, result);
}

template <>
bool TryCastWithOverflowCheck(hugeint_t value, int16_t &result) {
	return Hugeint::TryCast(value, result);
}

template <>
bool TryCastWithOverflowCheck(hugeint_t value, int32_t &result) {
	return Hugeint::TryCast(value, result);
}

template <>
bool TryCastWithOverflowCheck(hugeint_t value, int64_t &result) {
	return Hugeint::TryCast(value, result);
}

template <>
bool TryCastWithOverflowCheck(hugeint_t value, uint8_t &result) {
	return Hugeint::TryCast(value, result);
}

template <>
bool TryCastWithOverflowCheck(hugeint_t value, uint16_t &result) {
	return Hugeint::TryCast(value, result);
}

template <>
bool TryCastWithOverflowCheck(hugeint_t value, uint32_t &result) {
	return Hugeint::TryCast(value, result);
}

template <>
bool TryCastWithOverflowCheck(hugeint_t value, uint64_t &result) {
	return Hugeint::TryCast(value, result);
}

template <>
bool TryCastWithOverflowCheck(hugeint_t value, float &result) {
	return Hugeint::TryCast(value, result);
}

template <>
bool TryCastWithOverflowCheck(hugeint_t value, double &result) {
	return Hugeint::TryCast(value, result);
}

struct NumericTryCast {
	template <class SRC, class DST>
	static inline bool Operation(SRC input, DST &result, bool strict = false) {
		return TryCastWithOverflowCheck(input, result);
	}
};

struct NumericCast {
	template <class SRC, class DST>
	static inline DST Operation(SRC input) {
		DST result;
		if (!NumericTryCast::Operation(input, result)) {
			throw InvalidInputException(CastExceptionText<SRC, DST>(input));
		}
		return result;
	}
};

} // namespace duckdb
