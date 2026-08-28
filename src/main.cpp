#include <iostream>
#include "lexer.hpp"

int main() {
    std::string source_code = R"(
        fn main() {
            let x = 42;
            let msg = "Hello, world!";
            /* This is a comment */
            return x;
        }
    )";

    lexer::Lexer my_lexer(source_code);
    auto tokens = my_lexer.tokenize();
    my_lexer.print_tokens(tokens);

    return 0;
}