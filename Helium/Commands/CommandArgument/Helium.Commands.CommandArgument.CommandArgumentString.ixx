export module Helium.Commands.CommandArgument.CommandArgumentString;

import Helium.Commands.CommandBase;
import Helium.Commands.Concepts;

export namespace helium::commands {
	class CommandArgumentString
		: public CommandBase<CommandArgumentString>, public details::TagCommandArgument {
	public:
		using super = CommandBase<CommandArgumentString>;
	};
}