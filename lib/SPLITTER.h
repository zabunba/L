#ifndef SPLITTER_H
#define SPLITTER_H

#include <string_view>
#include <vector>
#include <cctype>

std::vector<std::string_view> lineTokens(std::string_view source) {
    std::vector<std::string_view> lines;
    size_t start = 0;
    size_t end = 0;

    while ((end = source.find('\n', start)) != std::string_view::npos) {
        lines.push_back(source.substr(start, end - start));
        start = end + 1;
    }

    if (start < source.size()) {
        lines.push_back(source.substr(start));
    }

    return lines;
}
std::vector<std::string_view> tokenizeLine(std::string_view line) {
    std::vector<std::string_view> tokens;
    const char* current = line.data();
    const char* end = line.data() + line.size();

    while (current < end) {
        // Handle newline explicitly
        if (*current == '\n') {
            tokens.push_back(std::string_view(current, 1));
            current++;
            continue;
        }

        // Skip other whitespace
        while (current < end && std::isspace(static_cast<unsigned char>(*current)) && *current != '\n') {
            current++;
        }
        if (current >= end) break;

        const char* start = current;

        if (*current == '"') {
            start = current;
            current++;
            while (current < end && *current != '"') {
                current++;
            }
            if (current < end) {
                current++;
            }
            tokens.push_back(std::string_view(start, current - start));
        }
        else if (std::isdigit(static_cast<unsigned char>(*current))) {
            while (current < end && std::isdigit(static_cast<unsigned char>(*current))) {
                current++;
            }

            if (current < end && *current == '.') {
                current++;
                while (current < end && std::isdigit(static_cast<unsigned char>(*current))) {
                    current++;
                }
            }

            if (current + 2 < end && *current == 'r' && *(current + 1) == 'e' && *(current + 2) == 'm') {
                current += 3;
            }
            else if (current + 1 < end &&
                    ((*current == 'p' && *(current + 1) == 'x') ||
                     (*current == 'v' && *(current + 1) == 'h') ||
                     (*current == 'v' && *(current + 1) == 'w'))) {
                current += 2;
            }
            else if (current < end && *current == '%') {
                current++;
            }

            tokens.push_back(std::string_view(start, current - start));
        }
        else if (std::isalpha(static_cast<unsigned char>(*current)) || *current == '_') {
            while (current < end && (std::isalnum(static_cast<unsigned char>(*current)) || *current == '_')) {
                current++;
            }
            tokens.push_back(std::string_view(start, current - start));
        }
        else if (std::ispunct(static_cast<unsigned char>(*current))) {
            current++;
            tokens.push_back(std::string_view(start, current - start));
        }
    }
    return tokens;
}


#endif