module;

#define SPDLOG_HEADER_ONLY

#include <chrono>
#include <ctime>

//this part of code is used to fix a bug of MSVC.
//the use of non-preprocessor command in the global module
//is not permitted by the ISO C++ Standard.
//If future MSVC version fix the compiler bug that this line should be removed.
using namespace std::chrono;	

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/daily_file_sink.h>

export module Helium.Logger;

import Helium.Base;

import <string>;
import <memory>;
import <vector>;
import <format>;

export namespace helium::logger {
	enum class LogLevel {
		trace = spdlog::level::trace,
		debug = spdlog::level::debug,
		info = spdlog::level::info,
		warn = spdlog::level::warn,
		error = spdlog::level::err,
		critical = spdlog::level::critical
	};

	class Logger : public HeliumObject {
	private:
		std::string name_;
		std::shared_ptr<spdlog::logger> logger_ptr_;

		[[nodiscard]] static auto initLogger(std::string const& name) -> std::shared_ptr<spdlog::logger> {
			static auto stdout_sink_
				{std::make_shared<spdlog::sinks::stdout_color_sink_mt>()};
			static auto file_sink_
				{std::make_shared<spdlog::sinks::daily_file_sink_mt>("./logs/helium-log.log", 0, 0)};
			auto vec = std::vector<spdlog::sink_ptr>{stdout_sink_, file_sink_};
			auto logger_ptr = std::make_shared<spdlog::logger>(name, begin(vec), end(vec));
			logger_ptr->set_pattern("[%Y-%m-%d %T.%e] [%^%l%$] %v");
			spdlog::register_logger(logger_ptr);
			return logger_ptr;
		}

		explicit Logger(std::string_view name) 
			:	name_(name),
				logger_ptr_(Logger::initLogger(this->name_))
		{}

	public:
		[[nodiscard]] static auto getLogger(std::string_view name) -> Logger& {
			Logger instance(name);
			return instance;
		}

		template <typename ... Args>
		auto log(LogLevel log_level, std::string_view fmt_str, Args&& ... fmt_args) const -> void {
			this->logger_ptr_->log(
				static_cast<spdlog::level::level_enum>(log_level),
				std::vformat(
					fmt_str, 
					std::make_format_args(
						std::forward<Args>(fmt_args)...
					)
				)
			);
		}

		template <typename ... Args>
		auto trace(std::string_view fmt_str, Args&& ... fmt_args) const -> void {
			this->log(LogLevel::trace, fmt_str, std::forward<Args>(fmt_args)...);
		}

		template <typename ... Args>
		auto debug(std::string_view fmt_str, Args&& ... fmt_args) const -> void {
			this->log(LogLevel::debug, fmt_str, std::forward<Args>(fmt_args)...);
		}

		template <typename ... Args>
		auto info(std::string_view fmt_str, Args&& ... fmt_args) const -> void {
			this->log(LogLevel::info, fmt_str, std::forward<Args>(fmt_args)...);
		}

		template <typename ... Args>
		auto warn(std::string_view fmt_str, Args&& ... fmt_args) const -> void {
			this->log(LogLevel::warn, fmt_str, std::forward<Args>(fmt_args)...);
		}

		template <typename ... Args>
		auto error(std::string_view fmt_str, Args&& ... fmt_args) const -> void {
			this->log(LogLevel::error, fmt_str, std::forward<Args>(fmt_args)...);
		}

		template <typename ... Args>
		auto critical(std::string_view fmt_str, Args&& ... fmt_args) const -> void {
			this->log(LogLevel::critical, fmt_str, std::forward<Args>(fmt_args)...);
		}

		template <typename ... Args>
		auto logw(LogLevel log_level, std::wstring_view fmt_str, Args&& ... fmt_args) const -> void {
			this->logger_ptr_->log(
				static_cast<spdlog::level::level_enum>(log_level),
				std::vformat(
					fmt_str, 
					std::make_wformat_args(
						std::forward<Args>(fmt_args)...
					)
				)
			);
		}

		template <typename ... Args>
		auto tracew(std::wstring_view fmt_str, Args&& ... fmt_args) const -> void {
			this->logw(LogLevel::trace, fmt_str, std::forward<Args>(fmt_args)...);
		}

		template <typename ... Args>
		auto debugw(std::wstring_view fmt_str, Args&& ... fmt_args) const -> void {
			this->logw(LogLevel::debug, fmt_str, std::forward<Args>(fmt_args)...);
		}

		template <typename ... Args>
		auto infow(std::wstring_view fmt_str, Args&& ... fmt_args) const -> void {
			this->logw(LogLevel::info, fmt_str, std::forward<Args>(fmt_args)...);
		}

		template <typename ... Args>
		auto warnw(std::wstring_view fmt_str, Args&& ... fmt_args) const -> void {
			this->logw(LogLevel::warn, fmt_str, std::forward<Args>(fmt_args)...);
		}

		template <typename ... Args>
		auto errorw(std::wstring_view fmt_str, Args&& ... fmt_args) const -> void {
			this->logw(LogLevel::error, fmt_str, std::forward<Args>(fmt_args)...);
		}

		template <typename ... Args>
		auto criticalw(std::wstring_view fmt_str, Args&& ... fmt_args) const -> void {
			this->logw(LogLevel::critical, fmt_str, std::forward<Args>(fmt_args)...);
		}
	};
}