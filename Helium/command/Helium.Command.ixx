module;

#define BOOST_UT_DISABLE_MODULE
#include <boost/ut.hpp>

export module Helium.Command;

import Helium.Base;

import <string>;
import <string_view>;
import <utility>;

namespace helium::command::details {
	template <typename Derived>
	class CRTPHelper {
	public:
		auto underlyingClass() -> Derived& { return static_cast<Derived&>(*this); }
		auto underlyingClass() const -> Derived const& { return static_cast<Derived const&>(*this); }
	};
}

namespace helium::command {
	template <typename Derived>
	class CommandBase;
}

export namespace helium::command::concepts {
	template <typename Command>
	concept IsCommandBase = std::derived_from<Command, CommandBase<Command>>;
}

export namespace helium::command {
	class CommandDispatcher {
	public:
		template <concepts::IsCommandBase Command>
		constexpr auto registerCommand(Command&& command) -> void {
			
		}
	};
}

export namespace helium::command {
	template <typename Derived>
	class CommandBase : public details::CRTPHelper<Derived> {
	public:
		template <typename Next>
		[[nodiscard]] constexpr auto then(Next&& next_node) &&;
	};

	class CommandStringLiteral : public CommandBase<CommandStringLiteral> {
	private:
		std::string _string_literal;
	public:
		constexpr CommandStringLiteral(std::string_view string_literal) : _string_literal(string_literal) 
		{}
	};

	template <typename Derived>
	template <typename Next>
	[[nodiscard]] constexpr auto CommandBase<Derived>::then(Next&& next_node) && {
		return CommandStringLiteral(std::move(this->underlyingClass()));
	}
}

namespace helium::command::test {
	using namespace boost::ut;

	auto testModule() -> void {
		"Helium.Command Module Test #1"_test = [] {
			CommandDispatcher dispatcher;

			dispatcher.registerCommand(
				CommandStringLiteral{"awa"}.then(
					CommandStringLiteral{"owo"}
				)
			);
		};
	}
}