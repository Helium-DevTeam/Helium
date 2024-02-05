module;

export module Helium.Commands.Lexer;

import Helium.Commands.Concepts;

import <memory>;
import <span>;
import <string>;

import <plf_hive.h>;

import <gsl/gsl>;

export namespace helium::commands
{
	enum class TokenCategory
	{
		TOKEN_PLAIN_STRING,
		TOKEN_INTEGER,
		TOKEN_FLOATING_POINT,
		TOKEN_BOOLEAN,
		TOKEN_QUOTED_STRING,
	};

	template <concepts::IsString StrType_>
	struct Token
	{
		using StringType = StrType_;

		TokenCategory token_type;
		typename StringType::iterator begin_iterator;
		std::span<typename StringType::value_type> token_span;
	};

	template <concepts::IsString StrType_>
	class CommandLexer
	{
	public:
		using StringType = StrType_;
		using TokenType = Token<StringType>;
	private:
		StringType raw_command_;
		plf::hive<TokenType> tokens_;

	public:
		explicit CommandLexer(std::string const& command)
			: raw_command_(command)
		{
			this->parseCommand();
		}

		auto parseCommand() -> void
		{
			typename StringType::iterator const current_iterator = this->raw_command_.cbegin();
			for(auto const& current_char : this->raw_command_)
			{
				
			}
		}
	};
}
