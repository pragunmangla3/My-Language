//
// Created by pragu on 7/22/2022.
//

#include "Tokenizer.h"
#include <stdexcept>

namespace simpleparser {

    using namespace std;

    // This function just loops over text in the program, making a standard state machine
    // example - when we encounter //, we just activate a boolean to ignore everything after it and take it as comment
    vector<Token> Tokenizer::parse(const string &inProgram) {
        vector<Token> tokens;
        Token currentToken;
        currentToken.mLineNumber = 1;

        for (char currCh: inProgram) {

            if (currentToken.mType == STRING_ESCAPE_SEQUENCE) {
                switch (currCh) {
                    case 'n':
                        currentToken.mText.append(1, '\n');
                        break;
                    case 'r':
                        currentToken.mText.append(1, '\r');
                        break;
                    case 't':
                        currentToken.mText.append(1, '\t');
                        break;
                    case '\\':
                        currentToken.mText.append(1, '\\');
                        break;
                    default:
                        throw runtime_error(
                                string("unknown escape sequence: \\") + string(1, currCh) + "in string on line"
                                + to_string(currentToken.mLineNumber) + ".");
                        break;
                }
            }

            switch (currCh) {
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    if (currentToken.mType == WHITESPACE) {
                        currentToken.mText.append(1, currCh);
                        currentToken.mType = INTEGER_LITERAL;
                    } else {
                        currentToken.mText.append(1, currCh);
                    }
                    break;
                case '.':
                    if (currentToken.mType == WHITESPACE) {
                        currentToken.mText.append(1, currCh);
                        currentToken.mType = INTEGER_LITERAL;
                    } else {
                        currentToken.mText.append(1, currCh);
                    }
                    break;
                case '{':
                case '}':
                case '(':
                case ')':
                case '=':
                case '-':
                case '+':
                case '*':
                case '/':
                case ';':
                case ',':
                    if (currentToken.mType != STRING_LITERAL) {
                        endToken(currentToken, tokens);
                        currentToken.mText.append(1, currCh);
                        currentToken.mType = STRING_LITERAL;
                        endToken(currentToken, tokens);
                    } else {
                        currentToken.mText.append(1, currCh);
                    }
                    break;
                case ' ':
                case '\t':
                    endToken(currentToken, tokens);
                    break;
                case '\r':
                case '\n':
                    endToken(currentToken, tokens);
                    ++currentToken.mLineNumber;
                    break;
                case '"' :      // not even saving this inside token, just the chars inside it
                    if (currentToken.mType != STRING_LITERAL) {
                        endToken(currentToken, tokens);
                        currentToken.mType = STRING_LITERAL;
                        currentToken.mText.append(1, currCh);
                    } else {
                        endToken(currentToken, tokens);
                    }
                    break;
                case '\\':    // this is single backslash, not double
                    if (currentToken.mType == STRING_LITERAL) {
                        currentToken.mType = STRING_ESCAPE_SEQUENCE;
                    } else {
                        endToken(currentToken, tokens);
                        currentToken.mType = OPERATOR;
                        currentToken.mText.append(1, currCh);
                        endToken(currentToken, tokens);
                    }
                    break;
                default:
                    break;

            }

        }

        return tokens;
    }

    void Tokenizer::endToken(Token &token, vector<Token> &tokens) {
        if (token.mType != WHITESPACE) {
            tokens.push_back(token);
        }
        token.mType = WHITESPACE;
        token.mText.erase();

    }
}


