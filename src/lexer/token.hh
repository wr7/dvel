#pragma once

#include <optional>
#include <string>
#include <string_view>

namespace dvel {
	enum struct BracketType {
		Parenthesis,
		Square,
		Curly,
	};

	enum struct SymbolType {
		Dot,
		Comma,
		Semicolon,
		Equals,
	};

	class Token {
		public:
			enum struct Type {
				OpeningBracket,
				ClosingBracket,

				String,
				Identifier,

				Symbol,
			};

			consteval Token(std::string_view s);

			Token(const Token& d) = delete;
			Token(Token&& d);
			~Token();

			Type type() const;

			// Displays any `Token` as a string
			std::string to_string() const;

			static Token opening(BracketType);
			static Token closing(BracketType);
			static Token identifier(std::string_view);
			static Token string(std::string&& string);

			std::optional<BracketType> as_opening() const;
			std::optional<BracketType> as_closing() const;

			std::optional<std::string_view> as_string() const;
			std::optional<std::string_view> as_identifier() const;

			std::optional<SymbolType> as_symbol() const;
		private:
			Type m_type;
			union {
				std::string_view m_identifier;
				std::string      m_string;
				BracketType      m_bracket_type;

				SymbolType       m_symbol;
			};

			inline Token() noexcept {};
	};
}
