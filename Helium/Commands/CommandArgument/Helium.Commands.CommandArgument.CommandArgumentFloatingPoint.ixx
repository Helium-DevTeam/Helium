export module Helium.Commands.CommandArgument.CommandArgumentFloatingPoint;

import Helium.Commands.CommandBase;
import Helium.Commands.Concepts;

export namespace helium::commands {
	class CommandArgumentFloatingPoint
		: public CommandBase<CommandArgumentFloatingPoint>, public details::TagCommandArgument {
	public:
		using super = CommandBase<CommandArgumentFloatingPoint>;
	};
}