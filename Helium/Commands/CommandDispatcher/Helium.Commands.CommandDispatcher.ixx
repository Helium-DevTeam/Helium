export module Helium.Commands.CommandDispatcher;

import Helium.Commands.Concepts;

export namespace helium::commands {
	class CommandDispatcher {
	public:
		template <concepts::IsCommandBase Command>
		constexpr auto registerCommand(Command&& command) -> void {
			
		}
	};
}