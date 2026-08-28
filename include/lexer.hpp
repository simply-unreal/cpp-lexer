#pragma once
#include <string>
#include <vector>
#include <unordered_map>

namespace lexer {
    enum class TokenType {
        Error,
        Unknown,
        EndOfFile,

        Identifier,

        IntegerLiteral,
        FloatLiteral,
        StringLiteral,
        CharLiteral,

        True,
        False,

        Fn,
        Let,
        Struct,
        Import,
        Return,

        If,
        Elif,
        Else,

        While,
        For,
        In,

        Bool,
        I8,
        I16,
        I32,
        I64,
        U8,
        U16,
        U32,
        U64,
        F32,
        F64,

        Plus,
        Minus,
        Star,
        Slash,
        Percent,

        Equal,
        PlusEqual,
        MinusEqual,

        EqualEqual,
        NotEqual,

        Less,
        LessEqual,
        Greater,
        GreaterEqual,

        And,
        Or,
        Not,

        LeftParen,
        RightParen,

        LeftBrace,
        RightBrace,

        LeftBracket,
        RightBracket,

        Comma,
        Semicolon,
        Colon,
        Dot,

        Range,

        Arrow,
    };

    struct Token {
        std::string value;
        TokenType type;

        Token(std::string value, TokenType type);
    };

    class Lexer {
        public:
            Lexer(const std::string& source);

            std::vector<Token> tokenize();
            void print_tokens(const std::vector<Token> &T);

        private:
            int pos = 0;
            std::string code;
            std::vector<Token> tokens;

            std::unordered_map<std::string, TokenType> keywords = {
                {"true", TokenType::True},
                {"false", TokenType::False},
                {"fn", TokenType::Fn},
                {"let", TokenType::Let},
                {"struct", TokenType::Struct},
                {"import", TokenType::Import},
                {"return", TokenType::Return},
                {"if", TokenType::If},
                {"elif", TokenType::Elif},
                {"else", TokenType::Else},
                {"while", TokenType::While},
                {"for", TokenType::For},
                {"in", TokenType::In},
                {"bool", TokenType::Bool},
                {"u8", TokenType::U8},
                {"u16", TokenType::U16},
                {"u32", TokenType::U32},
                {"u64", TokenType::U64},
                {"i8", TokenType::I8},
                {"i16", TokenType::I16},
                {"i32", TokenType::I32},
                {"i64", TokenType::I64},
                {"f32", TokenType::F32},
                {"f64", TokenType::F64},
                {"and", TokenType::And},
                {"not", TokenType::Not},
                {"or", TokenType::Or}
            };

            std::unordered_map<std::string, TokenType> symbols = {
                {"+", TokenType::Plus},
                {"-", TokenType::Minus},
                {"*", TokenType::Star},
                {"/", TokenType::Slash},
                {"%", TokenType::Percent},
                {"+=", TokenType::PlusEqual},
                {"-=", TokenType::MinusEqual},
                {"->", TokenType::Arrow},
                {"=", TokenType::Equal},
                {"==", TokenType::EqualEqual},
                {"!=", TokenType::NotEqual},
                {"<", TokenType::Less},
                {"<=", TokenType::LessEqual},
                {">", TokenType::Greater},
                {">=", TokenType::GreaterEqual},
                {"(", TokenType::LeftParen},
                {")", TokenType::RightParen},
                {"{", TokenType::LeftBrace},
                {"}", TokenType::RightBrace},
                {"[", TokenType::LeftBracket},
                {"]", TokenType::RightBracket},
                {",", TokenType::Comma},
                {";", TokenType::Semicolon},
                {":", TokenType::Colon},
                {".", TokenType::Dot},
                {"..", TokenType::Range}
            };

            char peek() const;
            void advance(int i);
            bool is_at_end() const;
            char get_current() const;

            void skip_whitespace();
            void skip_comment();

            Token identifier();
            Token number();
            Token string();
            Token character();
            Token symbol();

            void add_token(Token T);
    };
}