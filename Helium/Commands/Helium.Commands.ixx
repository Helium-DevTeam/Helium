module;

#define BOOST_UT_DISABLE_MODULE
#include <boost/ut.hpp>

export module Helium.Commands;

export import Helium.Commands.CommandArgument;
export import Helium.Commands.CommandLiteral;

import Helium.Base;

import <cstdint>;
import <limits>;
import <string>;
import <string_view>;
import <type_traits>;
import <utility>;

namespace helium::command::details {
	template <typename Derived>
	class CRTPHelper {
	public:
		auto underlyingClass() -> Derived& { return static_cast<Derived&>(*this); }
		auto underlyingClass() const -> Derived const& { return static_cast<Derived const&>(*this); }
	};

	struct TagCommandLiteral {};
	struct TagCommandArgument {};
}

namespace helium::command {
	template <typename Derived>
	class CommandBase;
}

export namespace helium::command::concepts {
	template <typename Command>
	concept IsCommandBase = std::derived_from<Command, CommandBase<Command>>;

	template <typename Command>
	concept IsCommandLiteral = std::derived_from<Command, details::TagCommandLiteral>;

	template <typename Command>
	concept IsCommandArgument = std::derived_from<Command, details::TagCommandArgument>;
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
		[[nodiscard]] constexpr auto then(Next&& next_node) && {
			return Derived(std::move(this->underlyingClass()));
		}

		template <std::invocable Callback>
			requires concepts::IsCommandArgument<Derived>
		[[nodiscard]] constexpr auto execute(Callback&& callback) && {
			return Derived(std::move(this->underlyingClass()));
		}
	};

	class CommandStringLiteral
		: public CommandBase<CommandStringLiteral>, details::TagCommandLiteral {
	private:
		std::string string_literal_;
	public:
		constexpr CommandStringLiteral(std::string_view string_literal) : string_literal_(string_literal) 
		{}
	};

	template <std::integral IntegerType = std::int64_t>
	struct IntegerBoundMin { IntegerType value = std::numeric_limits<IntegerType>::min(); };

	template <std::integral IntegerType = std::int64_t>
	struct IntegerBoundMax { IntegerType value = std::numeric_limits<IntegerType>::max(); };

	template <std::integral IntegerType_ = std::int64_t>
	class IntegerBound {
	public:
		using IntegerType = IntegerType_;
		using IntegerBoundMaxType = IntegerBoundMax<IntegerType>;
		using IntegerBoundMinType = IntegerBoundMin<IntegerType>;

	private:
		IntegerBoundMaxType max_{};
		IntegerBoundMinType min_{};

	public:
		constexpr IntegerBound(IntegerBoundMax max, IntegerBoundMin min) : max_(max), min_(min)
		{}
		constexpr IntegerBound(IntegerBoundMin min) : IntegerBound(IntegerBoundMaxType{}, min)
		{}
		constexpr IntegerBound(IntegerBoundMax max) : IntegerBound(max, IntegerBoundMinType{})
		{}
		constexpr IntegerBound(IntegerBoundMin min, IntegerBoundMax max) : IntegerBound(max, min) 
		{}
		constexpr IntegerBound() : IntegerBound(IntegerBoundMaxType{}, IntegerBoundMinType{})
		{}
	};

	template <std::integral IntegerType = std::int64_t>
	class CommandArgumentInteger
		: public CommandBase<CommandArgumentInteger<IntegerType>>, details::TagCommandArgument {
	public:
		constexpr CommandArgumentInteger()
		{}
	};
}

namespace helium::command::test {
	using namespace boost::ut;

	auto testModule() -> void {
		"Helium.Command Module Test #1"_test = [] {
			CommandDispatcher dispatcher;

			dispatcher.registerCommand(
				CommandStringLiteral{"awa"}.then(
					CommandStringLiteral{"owo"}.then(
						CommandArgumentInteger{}
					)
				)
			);
		};
	}
}