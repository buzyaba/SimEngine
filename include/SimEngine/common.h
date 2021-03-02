#pragma once
#include <sstream>
#include <string>
#include <regex>
#include <vector>
#include <type_traits>

extern std::size_t currentTime;
extern std::size_t currentStep;

std::string getCWD();
std::string getPath(const std::string path);

template<typename T>
std::vector<T> ParseString(std::string s, std::string delimiter) {
    std::vector<T> res;
    const std::regex re("[0-9\\.]+");
    std::sregex_iterator iter(s.begin(), s.end(), re);
    std::sregex_iterator end;
    for(; iter != end; ++iter) {
        for(std::size_t i = 0; i < iter->size(); ++i) {
            res.push_back(static_cast<T>(std::stod((*iter)[i])));
        }
    }
    return res;
}
template<typename T>
std::vector<std::vector<T>> ParseComplexString(std::string s, std::string delimiter) {
        const std::regex re("\\(([0-9,\\.]+)\\)");
        std::vector<std::vector<T>> res;
        std::sregex_iterator iter(s.begin(), s.end(), re);
        std::sregex_iterator end;
         for(; iter != end; ++iter) {
            for(std::size_t i = 1; i < iter->size(); ++i) {
                res.push_back(ParseString<T>((*iter)[i], delimiter));
            }
         }
        return res;
}
