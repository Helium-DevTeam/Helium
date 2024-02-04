export module Helium.Commands.CommandArgument.CommandArgumentBoolean;

import Helium.Commands.CommandBase;
import Helium.Commands.Concepts;

export namespace helium::commands {
	class CommandArgumentBoolean
		: public CommandBase<CommandArgumentBoolean>, public details::TagCommandArgument {
	public:
		using super = CommandBase<CommandArgumentBoolean>;
	};
}