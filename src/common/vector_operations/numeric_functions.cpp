//===--------------------------------------------------------------------===//
// numeric_inplace_operators.cpp
// Description: This file contains the implementation of numeric inplace ops
// += *= /= -= %=
//===--------------------------------------------------------------------===//

#include "common/operator/numeric_functions.hpp"
#include "common/vector_operations/binary_loops.hpp"
#include "common/vector_operations/unary_loops.hpp"
#include "common/vector_operations/vector_operations.hpp"

using namespace duckdb;
using namespace std;

//===--------------------------------------------------------------------===//
// Abs
//===--------------------------------------------------------------------===//
void VectorOperations::Abs(Vector &input, Vector &result) {
	UNARY_TYPE_CHECK(input, result);
	switch (input.type) {
	case TypeId::TINYINT:
		templated_unary_loop<int8_t, int8_t, operators::Abs>(input, result);
		break;
	case TypeId::SMALLINT:
		templated_unary_loop<int16_t, int16_t, operators::Abs>(input, result);
		break;
	case TypeId::INTEGER:
		templated_unary_loop<int32_t, int32_t, operators::Abs>(input, result);
		break;
	case TypeId::BIGINT:
		templated_unary_loop<int64_t, int64_t, operators::Abs>(input, result);
		break;
	case TypeId::DECIMAL:
		templated_unary_loop<double, double, operators::Abs>(input, result);
		break;
	default:
		throw InvalidTypeException(input.type, "Invalid type for abs");
	}
}

//===--------------------------------------------------------------------===//
// Round
//===--------------------------------------------------------------------===//
void VectorOperations::Round(Vector &input, Vector &precision, Vector &result) {
	UNARY_TYPE_CHECK(input, result);
	if (!TypeIsInteger(precision.type)) {
		throw InvalidTypeException(precision.type,
		                           "Invalid type for rounding precision");
	}

	switch (input.type) {
	case TypeId::TINYINT:
	case TypeId::SMALLINT:
	case TypeId::INTEGER:
	case TypeId::BIGINT:
		VectorOperations::Copy(input, result);
		break;
	case TypeId::DECIMAL:
		precision.Cast(TypeId::TINYINT);
		templated_binary_loop<double, int8_t, double, operators::Round>(
		    input, precision, result);
		break;
	default:
		throw InvalidTypeException(input.type, "Invalid type for round");
	}
}
