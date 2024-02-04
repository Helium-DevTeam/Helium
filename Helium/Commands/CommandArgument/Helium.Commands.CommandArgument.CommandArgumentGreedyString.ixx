export module Helium.Commands.CommandArgument.CommandArgumentGreedyString;

import Helium.Commands.CommandBase;
import Helium.Commands.Concepts;

export namespace helium::commands {
	class CommandArgumentGreedyString
		: public CommandBase<CommandArgumentGreedyString>, public details::TagCommandArgument {
	public:
		using super = CommandBase<CommandArgumentGreedyString>;
	};
}