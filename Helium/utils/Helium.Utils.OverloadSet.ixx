/*
 * Helium is an open source software distributed under the MIT license.
 * Please refer to Helium.Main.ixx for full license info.
 */

export module Helium.Utils.OverloadSet;

import <concepts>;

import <boost/mp11.hpp>;

namespace helium::utils::details {
	//We need this until MSVC support the CWG2518/P2593R1 "static_assert(false)"
	//If a future version of MSVC officially support the feature, this variable
	//template could be removed by simply switching to static_assert(false)
	template<typename dummy>
	constexpr bool dependent_false = false;
}

export namespace helium::utils {	
	template <typename ... Ts>
	struct OverloadSet : public Ts... {
		using Ts::operator()...;

		consteval auto operator()(auto ... dummy) -> void { 
			//We need this until MSVC support the C++26 Pack Indexing
			//If a future version of MSVC officially support the feature,
			//the boost::mp11::mp_nth_element should be replaced by pack...[I]
			static_assert(
				details::dependent_false<boost::mp11::mp_nth_element<0, Ts>>, 
				"Unsupported type."
			); 
		}
	};
}