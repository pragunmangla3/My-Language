#pragma once //only include this file once, if it is included more than once

#include <vector>
#include <string>

namespace simpleparser{

    using namespace std;

    enum TokenType{
        WHITESPACE, // never a type of token
        IDENTIFIER,
        INTEGER_LITERAL,
        STRING_LITERAL,
        OPERATOR,
        STRING_ESCAPE_SEQUENCE,
        POTENTIAL_DOUBLE
    };

    class Token{
    public:
        enum TokenType mType{WHITESPACE};
        string mText;
        // these are for error handling situations
        size_t mStartOffset{0};
        size_t mEndOffset{0};
        size_t mLineNumber{0};
    };

    class Tokenizer {
    public:
        vector<Token> parse(const string &inProgram);

    private:
        void endToken(Token &token, vector<Token> &tokens);
    };

}




