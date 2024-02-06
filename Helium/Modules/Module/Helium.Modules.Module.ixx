/*
 * Helium is an open source software distributed under the MIT license.
 * Please refer to Helium.Main.ixx for full license info.
 */

module;

//#include <boost/dll.hpp>
//#include <boost/dll/smart_library.hpp>
//#include <boost/dll/import_mangled.hpp>
//#include <boost/dll/import_class.hpp>

export module Helium.Modules.Module;

import <memory>;

import Helium.Base;

export namespace helium::modules {
	enum class ModuleState {
		Empty,
		Enabled,
		Disabled,
	};

	class Module : public HeliumObject {
	private:
		ModuleState state_{ModuleState::Empty};
		//std::shared_ptr<boost::dll::experimental::smart_library> module_;

	public:

	};
}