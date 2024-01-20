#pragma once

#include "core/util/buffer.h"
#include "core/util/diagnostics.h"
#include "token.h"
#include <optional>
#include <string>
#include <vector>

namespace xlang {

enum class LexerState {
    none,
    identifier,
    string_literal,
};

class Lexer {
  public:
    Lexer() = default;
    ~Lexer() = default;

    LexerState state = LexerState::none;

    inline auto lex(std::string input, Diagnostics& diagnostics)
        -> std::vector<Token> {
        return lex(Buffer<std::string>(input), diagnostics);
    }

    auto lex(Buffer<std::string> input, Diagnostics& diagnostics)
        -> std::vector<Token>;

    void printTokens();
};

} // namespace xlang
