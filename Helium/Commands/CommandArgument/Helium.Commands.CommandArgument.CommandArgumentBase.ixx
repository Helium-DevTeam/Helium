module;

export module Helium.Commands.CommandArgument.CommandArgumentBase;

import Helium.Commands.CommandBase;
import Helium.Commands.Concepts;

export namespace helium::commands {
	template <typename Derived_>
	class CommandArgumentBase : public CommandBase<CommandArgumentBase<Derived_>>, public details::TagCommandArgument {
	public:
		using super = CommandBase<CommandArgumentBase<Derived_>>;
	};
}