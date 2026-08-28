#include "lexer.hpp"
#include "magic_enum.hpp"
#include <iostream>
#include <string>
#include <cctype>
#include <unordered_map>
#include <print>

namespace lexer {
    Token::Token(std::string value, TokenType type) {
        this->value = std::move(value);
        this->type = type;
    }

    Lexer::Lexer(const std::string& source) {
        code = source;
        pos = 0;
    }

    char Lexer::peek() const {
        if (pos + 1 >= code.length()) return '\0';
        return code[pos + 1];
    }

    void Lexer::advance(int i) {
        pos += i;
        if (pos > code.length()) {
            pos = code.length();
        }
    }

    bool Lexer::is_at_end() const {
        return pos >= code.length();
    }

    char Lexer::get_current() const {
        if (is_at_end()) return '\0';
        return code[pos];
    }

    void Lexer::skip_whitespace() {
        while (!is_at_end() && (code[pos] == ' ' || code[pos] == '\t' || code[pos] == '\r' || code[pos] == '\n')) {
            advance(1);
        }
    }

    void Lexer::skip_comment() {
        advance(2);

        while (!is_at_end()) {
            if (code[pos] == '*' && peek() == '/') {
                advance(2);
                return;
            }
            advance(1);
        }
    }

    Token Lexer::identifier() {
        std::string word = "";

        while (!is_at_end() && (isalnum(get_current()) || get_current() == '_')) {
            word += get_current();
            advance(1);
        }

        if (keywords.contains(word)) {
            return Token{word, keywords.at(word)};
        }

        return Token{word, TokenType::Identifier};
    }

    Token Lexer::number() {
        std::string num = "";
        bool has_decimal = false;

        while (!is_at_end() && (isdigit(get_current()) || get_current() == '.')) {
            if (get_current() == '.') {
                if (has_decimal) {
                    break;
                }
                has_decimal = true;
            }

            num += get_current();
            advance(1);
        }

        TokenType type = has_decimal ? TokenType::FloatLiteral : TokenType::IntegerLiteral;
        return Token{num, type};
    }

    Token Lexer::string() {
        std::string str = "";
        advance(1);

        while (!is_at_end() && get_current() != '"') {
            str += get_current();
            advance(1);
        }

        if (is_at_end()) {
            return Token{"Unterminated string literal", TokenType::Error};
        }

        advance(1);
        return Token{str, TokenType::StringLiteral};
    }

    Token Lexer::character() {
        std::string chr = "";
        advance(1);

        if (is_at_end()) {
            return Token{"Unterminated character literal", TokenType::Error};
        }

        chr = get_current();
        advance(1);

        if (get_current() != '\'') {
            return Token{"Unterminated character literal", TokenType::Error};
        }

        advance(1);
        return Token{chr, TokenType::CharLiteral};
    }

    Token Lexer::symbol() {
        if (pos + 1 < code.length()) {
            std::string two_char = code.substr(pos, 2);

            if (symbols.contains(two_char)) {
                advance(2);
                return Token{two_char, symbols.at(two_char)};
            }
        }

        std::string one_char(1, get_current());

        if (symbols.contains(one_char)) {
            advance(1);
            return Token{one_char, symbols.at(one_char)};
        }

        advance(1);
        return Token{one_char, TokenType::Unknown};
    }

    void Lexer::add_token(Token T) {
        tokens.emplace_back(T.value, T.type);
    }

    std::vector<Token> Lexer::tokenize() {
        tokens.clear();

        while (!is_at_end()) {
            skip_whitespace();

            if (is_at_end()) break;

            char c = code[pos];

            if (c == '/' && peek() == '*') {
                skip_comment();
            }
            else if (isalpha(c) || c == '_') {
                add_token(identifier());
            }
            else if (isdigit(c)) {
                add_token(number());
            }
            else if (c == '"') {
                add_token(string());
            }
            else if (c == '\'') {
                add_token(character());
            }
            else {
                add_token(symbol());
            }
        }

        return tokens;
    }

    void Lexer::print_tokens(const std::vector<Token> &tokens) {
        for (auto &T : tokens) {
            std::println("Token Type = [{}]", magic_enum::enum_name(T.type));
            std::println("Value = \"{}\"", T.value);
            std::println("");
        }
    }
}