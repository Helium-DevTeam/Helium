export module Helium.Commands.CommandArgument.CommandArgumentInteger;

import Helium.Commands.Concepts;
import Helium.Commands.CommandBase;

import <cstdint>;
import <concepts>;
import <limits>;

export namespace helium::commands {
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
		constexpr IntegerBound(IntegerBoundMaxType max, IntegerBoundMinType min) : max_(max), min_(min)
		{}
		constexpr IntegerBound(IntegerBoundMinType min) : IntegerBound(IntegerBoundMaxType{}, min)
		{}
		constexpr IntegerBound(IntegerBoundMaxType max) : IntegerBound(max, IntegerBoundMinType{})
		{}
		constexpr IntegerBound(IntegerBoundMinType min, IntegerBoundMaxType max) : IntegerBound(max, min) 
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