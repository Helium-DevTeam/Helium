/*
 * Helium is an open source software distributed under the MIT license.
 * Please refer to Helium.Main.ixx for full license info.
 */

export module Helium.Commands.CommandDispatcher;

import Helium.Commands.Concepts;

export namespace helium::commands {
	class CommandDispatcher {
	public:
		template <typename Command>
		constexpr auto registerCommand(Command&& command) -> void {
			
		}
	};
}