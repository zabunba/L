#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <string_view>
#include <string>
#include <vector>
#include <regex>
#include <cctype>
#include <sstream>
#include <algorithm>
#include <charconv> 

enum TokenType {
    IDENTIFIER, // something
    VALUE, // 20px
    OPERATOR, // +
    CLOSE_BRACKET, // {
    OPEN_BRACKET, // }
    CLOSE_PARENTHESIS, // )
    OPEN_PARENTHESIS, // (
    KEYWORD, // print
    ENDOFLINE, // /n
    COMMENT, // !
    UNKNOWN, // sakjdn
};

const char* tokenTypeToString(TokenType t) {
    switch(t) {
        case IDENTIFIER: return "IDENTIFIER";
        case VALUE: return "VALUE";
        case OPERATOR: return "OPERATOR";
        case CLOSE_BRACKET: return "CLOSE_BRACKET";
        case OPEN_BRACKET: return "OPEN_BRACKET";
        case CLOSE_PARENTHESIS: return "CLOSE_PARENTHESIS";
        case OPEN_PARENTHESIS: return "OPEN_PARENTHESIS";
        case KEYWORD: return "KEYWORD";
        case ENDOFLINE: return "ENDOFLINE";
        case COMMENT: return "COMMENT";
        case UNKNOWN: return "UNKNOWN";
        default: return "INVALID_TOKEN_TYPE";
    }
}

struct Token {
    TokenType t;
    std::string_view  c;
};


const std::regex OPERATOR_REGEX(R"(^(==|!=|>=|<=|>|<|=|\+|-|\*|/|#)$)");

inline bool isOperator(const std::string_view& s) {
    return std::regex_match(std::string(s), OPERATOR_REGEX);
}

const std::regex VALUE_REGEX(
    "^\\d+(\\.\\d+)?"
    "(px|rem|%|vh|vw)$"
);

bool isCssValue(const std::string_view& s) {
    return std::regex_match(std::string(s), VALUE_REGEX);
}

bool isDigit(const std::string_view& s) {
    if (s.empty()) return false;
    return std::all_of(s.begin(), s.end(), ::isdigit);
}

bool isString(const std::string_view& s) {
    return s.size() >= 2 && s.front() == '"' && s.back() == '"';
}

bool isDouble(std::string_view s) {
    double result;
    const auto res = std::from_chars(s.data(), s.data() + s.size(), result);
    return res.ec == std::errc() && res.ptr == s.data() + s.size();
}

bool isBool(std::string_view s) {
    if (s.length() != 4 && s.length() != 5) {
        return false;
    }
    if (s.length() == 4) {
        return (::tolower(s[0]) == 't' &&
                ::tolower(s[1]) == 'r' &&
                ::tolower(s[2]) == 'u' &&
                ::tolower(s[3]) == 'e');
    }
    if (s.length() == 5) {
        return (::tolower(s[0]) == 'f' &&
                ::tolower(s[1]) == 'a' &&
                ::tolower(s[2]) == 'l' &&
                ::tolower(s[3]) == 's' &&
                ::tolower(s[4]) == 'e');
    }
    return false;
}

bool isIdentifier(const std::string_view& s) {
    if (s.empty()) return false;
    if (!(std::isalpha(s[0]) || s[0] == '_')) return false;
    return std::all_of(s.begin() + 1, s.end(),
        [](unsigned char c) { return std::isalnum(c) || c == '_'; });
}

inline bool isLikelyValue(std::string_view token) {
    return isDigit(token) || isDouble(token) || isString(token) || isCssValue(token) || isBool(token);
}


#endif