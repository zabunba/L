
#include <stdio.h>
#include <iostream>
#include <istream>
#include <vector>
#include <string>
#include <string_view>
#include <cstring>
#include <unordered_set>
#include "lib/DEBUG.h"
#include "lib/SPLITTER.h"
#include "lib/HEADER.h"
#include "lib/READER.h"
#include "lib/PARSER.h"
#include "lib/AST.h"

std::vector<Token> CODE;
std::unordered_set<std::string_view> KEYWORDS = { "print", "let", "const", "if", "return", "import" };




void Lexical(const char lines[]){

    std::vector<std::string_view> LINES = lineTokens(lines);

    CODE.reserve(LINES.size() * 4);


    for(const auto& line : LINES){

        std::vector<std::string_view> LINE = tokenizeLine(line);

        for(const auto& token : LINE){

            if (isOperator(token)){
                CODE.emplace_back(Token{OPERATOR, token});
            } else if (isLikelyValue(token)){
                CODE.emplace_back(Token{VALUE, token});
            } else if (token == "("){
                CODE.emplace_back(Token{OPEN_PARENTHESIS, token});
            } else if (token == ")"){
                CODE.emplace_back(Token{CLOSE_PARENTHESIS, token});
            } else if (token == "{"){
                CODE.emplace_back(Token{OPEN_BRACKET, token});
            } else if (token == "}"){
                CODE.emplace_back(Token{CLOSE_BRACKET, token});
            } else if (KEYWORDS.find(token) != KEYWORDS.end()) {
                CODE.emplace_back(Token{KEYWORD, token});
            } else if(isIdentifier(token)){
                CODE.emplace_back(Token{IDENTIFIER, token});
            } else {
                CODE.emplace_back(Token{UNKNOWN, token}); //This does not exist
            }
            
        }
        CODE.emplace_back(Token{ENDOFLINE, "\\n"});
    }


    
}


int main(int argc, char * argv[]){
    DEBUG("Start Lumen");

    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);

    if (argc > 1 && std::strcmp(argv[1], "--console") == 0) {
        std::string x;
        while ( true )
        {
            CODE.clear(); 

            std::cout << "> ";
            std::getline(std::cin, x);

            size_t first_space_pos = x.find(' ');
            std::string command = x.substr(0, first_space_pos);

            if (x == "exit"){ 
                break; 
            }

            if (command == "read") {
                size_t filename_start_pos = x.find_first_not_of(" \t", first_space_pos);

                if (filename_start_pos == std::string::npos) {
                    std::cerr << "Error: Missing filename after 'read' command." << std::endl;
                } else {
                    std::string filename = x.substr(filename_start_pos);
                    Lexical(getFile(filename.c_str()));
                }
            } else if (command == "web") {
                std::cout << "Wait for web!" << std::endl;
            } else {
                Lexical(x.c_str());
            }
            

            for (const auto& token : CODE) {
                std::cout << "Type: " << tokenTypeToString(token.t)
                        << ", Value: '" << token.c << "'" << std::endl;
            }
            
             
           
            
            //---Finish

            std::cout << "\n";
        }
        
    }
    DEBUG("End Lumen");
}