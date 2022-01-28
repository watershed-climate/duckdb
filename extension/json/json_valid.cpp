#include "duckdb/parser/parsed_data/create_scalar_function_info.hpp"
#include "json_common.hpp"
#include "json_functions.hpp"

namespace duckdb {

static void ValidFunction(DataChunk &args, ExpressionState &state, Vector &result) {
	auto &inputs = args.data[0];
	UnaryExecutor::Execute<string_t, bool>(inputs, result, args.size(),
	                                       [&](string_t input) { return JSONCommon::GetRootUnsafe(input); });
}

CreateScalarFunctionInfo JSONFunctions::GetValidFunction() {
	return CreateScalarFunctionInfo(ScalarFunction("json_valid", {LogicalType::VARCHAR}, LogicalType::BOOLEAN,
	                                               ValidFunction, false, nullptr, nullptr, nullptr));
}

} // namespace duckdb
