module;

export module Helium.Modules.ModuleManager;

import <unordered_map>;
import <memory>;

import Helium.Base;
import Helium.Modules.ModuleMetadata;
import Helium.Modules.Module;

export namespace helium::modules {
	

	class ModuleManager : public HeliumObject {
	private:
		std::unordered_map<ModuleMetadata, std::shared_ptr<Module>, ModuleMetadataHash> module_map;

	public:
		[[nodiscard]] static auto getInstance() -> ModuleManager& {
			static ModuleManager instance;
			return instance;
		}
	};
}