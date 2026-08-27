#include "lexer.hpp"
#include <iostream>
#include <string>
#include <cctype>

Token::Token(std::string val, TokenType type) {
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

void Lexer::advance() {
    if (!is_at_end) pos++;
}

bool Lexer::is_at_end() const {
    return code.length() >= pos;
}

char Lexer::get_current() const {
    return code[pos];
}

void Lexer::skip_whitespace() {
    while (code[pos] == ' ') {
        advance();
    }
}

void Lexer::skip_comment() {
    while (code[pos] != '/' || code[pos] != '*'
    && peek() != '/') {
        advance();
    }

    advance();
    advance();
}

Token Lexer::identifier() {
    while (isalpha(get_current())) {
        
    }
}