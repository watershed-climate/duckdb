#include "duckdb/parser/parsed_data/create_secret_info.hpp"

#include "duckdb/parser/parsed_data/create_info.hpp"

namespace duckdb {

CreateSecretInfo::CreateSecretInfo(OnCreateConflict on_conflict, SecretPersistMode persist_mode)
    : ParseInfo(ParseInfoType::CREATE_SECRET_INFO), on_conflict(on_conflict), persist_mode(persist_mode), named_parameters() {
}

unique_ptr<CreateSecretInfo> CreateSecretInfo::Copy() const {
	auto result = make_uniq<CreateSecretInfo>(on_conflict, persist_mode);
	result->type = type;
	result->provider = provider;
	result->name = name;
	result->scope = scope;
	result->named_parameters = named_parameters;
	return result;
}

} // namespace duckdb
