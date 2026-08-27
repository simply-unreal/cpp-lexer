#include "lexer.hpp"
#include <iostream>
#include <string>
#include <cctype>
#include <unordered_map>

Token::Token(std::string value, TokenType type) {
    this->value = value;
    this->type = type;
}

Lexer::Lexer(const std::string& source) {
    code = source;
}

char Lexer::peek() const {
    if (code.length() + 1 >= pos) return ' ';
    return code[pos + 1];
}

void Lexer::advance(int i) {
    if (pos + i <= code.length()) {
        pos += i;
    } else {
        pos = code.length();
    }
}

bool Lexer::is_at_end() const {
    return code.length() >= pos;
}

char Lexer::get_current() const {
    return code[pos];
}

void Lexer::skip_whitespace() {
    while (code[pos] == ' ') {
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
    
    while (isalnum(get_current()) || get_current() == '_') {
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

    while (isdigit(get_current()) || get_current() == '.') {
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

    while (get_current() != '"' && !is_at_end()) {
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

    chr = get_current();
    advance(1);

    if (get_current() != '\'') {
        return Token{"Unterminated character literal", TokenType::Error};
    }

    return Token{chr, TokenType::CharLiteral};
}