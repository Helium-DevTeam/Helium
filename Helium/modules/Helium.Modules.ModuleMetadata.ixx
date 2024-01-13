module;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined(_WIN64)
	#define BOOST_UUID_RANDOM_PROVIDER_FORCE_WINCRYPT
#endif

#include <boost/container_hash/hash.hpp>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

#include <neargye/semver.hpp>

export module Helium.Modules.ModuleMetadata;

import <string>;
import <optional>;
import <vector>;

export namespace helium::modules {
	struct ModuleMetadata {
		ModuleMetadata() {
			this->uuid = boost::uuids::random_generator()();
		}

		struct ModuleDependency {
			std::string									name;
			semver::version								version;
		};
		std::string										entry;
		std::string										name;
		semver::version									version;
		boost::uuids::uuid								uuid;
		std::optional<std::string>						description;
		std::optional<std::string>						author;
		std::optional<std::vector<ModuleDependency>>	dependencies;
		std::optional<std::vector<ModuleDependency>>	optional_dependencies;
		std::optional<std::vector<ModuleDependency>>	conflicts;
		std::optional<std::vector<ModuleDependency>>	load_before;
	};

	struct ModuleMetadataHash {
		auto operator()(helium::modules::ModuleMetadata const& metadata) const noexcept -> std::size_t {
			return boost::hash<boost::uuids::uuid>()(metadata.uuid);
		}
	};
}