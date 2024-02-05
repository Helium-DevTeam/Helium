module;

export module Helium.Commands.Lexer;

import Helium.Commands.Concepts;

import <cctype>;
import <format>;
#include <iterator>
import <memory>;
import <optional>;
import <print>;
import <span>;
import <string>;

import <plf_hive.h>;

import <gsl/gsl>;

import <scope_guard.hpp>;

import <nameof.hpp>;

export namespace helium::commands
{
	enum class TokenCategory
	{
		TOKEN_PLAIN_STRING,
		TOKEN_INTEGER,
		TOKEN_FLOATING_POINT,
		TOKEN_BOOLEAN,
		TOKEN_QUOTED_STRING
	};

	template <concepts::IsString StrType_>
	struct Token
	{
		using StringType = StrType_;

		TokenCategory token_type;
		typename StringType::const_iterator begin_iterator;
		std::basic_string_view<typename StringType::value_type> token_view;

		auto toString() const -> std::string
		{
			return std::format(
				"Token[.token_type = {}, .begin_iterator = {}, .token_view = {}]",
				nameof::nameof_enum(this->token_type),
				*this->begin_iterator,
				this->token_view
			);
		}
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
		typename StringType::const_iterator current_iterator_;

	public:
		CommandLexer()
			:
		raw_command_(),
		tokens_(),
		current_iterator_(this->raw_command_.cbegin())
		{}

		auto parseCommand(std::string const& command) -> void
		{
			this->raw_command_ = command;
			this->current_iterator_ = this->raw_command_.cbegin();
			this->parseCommand();
		}

		auto parseCommand() -> void
		{
			std::println("Parsing Command : {}" , this->raw_command_);
			while(auto next_token = this->getNextToken())
			{
				this->tokens_.insert(next_token.value());
				std::println("{}", next_token.value().toString());
			}
		}

		auto isParsed() const noexcept -> bool
		{
			return this->current_iterator_ == this->raw_command_.cend();
		}

		auto getNextToken() -> std::optional<TokenType>
		{
			for(; this->current_iterator_ < this->raw_command_.cend(); ++this->current_iterator_)
			{
				if(std::isblank(*this->current_iterator_))
				{
					continue;
				}

				if(std::isdigit(*this->current_iterator_) or *this->current_iterator_ == '-')
				{
					bool is_fp = false;
					bool invalid_fp = false;
					typename StringType::const_iterator begin_iterator = current_iterator_;
					++this->current_iterator_;

					while(this->current_iterator_ < this->raw_command_.cend())
					{
						sg::make_scope_guard([this] { ++this->current_iterator_; });
						if(*this->current_iterator_ == '.')
						{
							if(is_fp == true)
							{
								invalid_fp = true;
								this->current_iterator_ = begin_iterator;
								break;
							}
							is_fp = true;
							continue;
						}
						if(std::isdigit(*this->current_iterator_))
						{
							continue;
						}
						break;
					}

					if(not invalid_fp) {
						if(not is_fp)
						{
							return TokenType{
								TokenCategory::TOKEN_INTEGER,
								begin_iterator,
								std::string_view{this->raw_command_}.substr(
									std::distance(this->raw_command_.cbegin(), begin_iterator), 
									std::distance(begin_iterator, this->current_iterator_)
								)
							};
						}
						else
						{
							return TokenType{
								TokenCategory::TOKEN_FLOATING_POINT,
								begin_iterator,
								std::string_view{this->raw_command_}.substr(
									std::distance(this->raw_command_.cbegin(), begin_iterator), 
									std::distance(begin_iterator, this->current_iterator_)
								)
							};
						}
					}
				}

				if(*this->current_iterator_ == '\"' or *this->current_iterator_ == '\'')
				{
					
				}

				if(*this->current_iterator_ == 't' or *this->current_iterator_ == 'f')
				{
					if(this->raw_command_.substr(std::distance(this->raw_command_.cbegin(), this->current_iterator_), 4) == "true")
					{
						auto result = TokenType {
							TokenCategory::TOKEN_BOOLEAN,
							this->current_iterator_,
							std::string_view{this->raw_command_}.substr(
								std::distance(this->raw_command_.cbegin(), this->current_iterator_), 
								4
							)
						};
						this->current_iterator_ += 4;
						return result;
					}
					if(this->raw_command_.substr(std::distance(this->raw_command_.cbegin(), this->current_iterator_), 5) == "false")
					{
						auto result = TokenType {
							TokenCategory::TOKEN_BOOLEAN,
							this->current_iterator_,
							std::string_view{this->raw_command_}.substr(
								std::distance(this->raw_command_.cbegin(), this->current_iterator_), 
								5
							)
						};
						this->current_iterator_ += 5;
						return result;
					}
				}

				typename StringType::const_iterator begin_iterator = current_iterator_;
				while(this->current_iterator_ < this->raw_command_.cend() and (not std::isblank(*this->current_iterator_)))
				{
					++this->current_iterator_;
				}
				return TokenType {
					TokenCategory::TOKEN_PLAIN_STRING,
					begin_iterator,
					std::string_view{this->raw_command_}.substr(
						std::distance(this->raw_command_.cbegin(), begin_iterator), 
						std::distance(begin_iterator, this->current_iterator_)
					)
				};
			}
			return std::nullopt;
		}
	};
}
