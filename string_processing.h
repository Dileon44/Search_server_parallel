#pragma once

#include <string>
#include <vector>
#include <set>
#include <string_view>

#include "log_duration.h"

//std::vector<std::string> SplitIntoWords(const std::string& text);
std::vector<std::string_view> SplitIntoWords(std::string_view str);

//template <typename StringContainer>
//std::set<std::string> MakeUniqueNonEmptyStrings(const StringContainer& strings) {
//    std::set<std::string> non_empty_strings;
//    for (const std::string& str : strings) {
//        if (!str.empty()) {
//            non_empty_strings.insert(str);
//        }
//    }
//    return non_empty_strings;
//}

template <typename StringContainer>
std::set<std::string, std::less<>> MakeUniqueNonEmptyStrings(const StringContainer& strings) {
    //std::vector<std::string> non_empty_strings(strings.begin(), strings.end());
    std::set<std::string, std::less<>> non_empty_strings;
    for (const std::string_view& str : strings) {
        if (!str.empty()) {
            non_empty_strings.insert(std::string(str));
        }
    }
    return non_empty_strings;
}