#include "string_processing.h"

#include <execution>
#include <functional>
#include <iterator>
#include <numeric>

using std::string;
using std::string_view;
using std::vector;

//vector<string> SplitIntoWords(const string& text) {
//    //LOG_DURATION("split into words: ");
//    vector<string> words;
//    string word;
//    for (const char c : text) {
//        if (c == ' ') {
//            if (!word.empty()) {
//                words.push_back(word);
//                word.clear();
//            }
//        }
//        else {
//            word += c;
//        }
//    }
//    if (!word.empty()) {
//        words.push_back(word);
//    }
//
//    return words;
//}


//
//int CountWords(std::string_view str) {
//    if (str.empty()) {
//        return 0;
//    }
//    // подсчитываем количество пробелов, за которыми следует буква
//    return std::transform_reduce(
//        std::execution::par,
//        std::next(str.begin()), str.end(),
//        str.begin(),
//        0,
//        std::plus<>{},
//        [](char c, char prev_c) {
//            return c != ' ' && prev_c == ' ';
//        }
//    ) + (str[0] != ' ');
//}

std::vector<std::string_view> SplitIntoWords(std::string_view str) {
    std::vector<std::string_view> result;
    //std::vector<std::string_view> result(CountWords(str));
    //std::vector<std::string_view> result(std::count(str.begin(), str.end(), ' '));
    const int64_t pos_end = str.npos;
    while (true) {
        int64_t space = str.find(' ');
        result.push_back(space == pos_end ? str : str.substr(0, space));
        //result.push_back(str.substr(0, space));
        if (space == pos_end) {
            break;
        }
        else {
            str.remove_prefix(space + 1);
        }
    }

    return result;
}

//// пусть теперь наша функция возвращает вектор элементов string_view
//vector<string_view> SplitIntoWords(string_view str) {
//    vector<string_view> result;
//    // 1
//    int64_t pos = 0;
//    // 2
//    const int64_t pos_end = str.npos;
//    // 3
//    while (true) {
//        // 4
//        int64_t space = str.find(' ', pos);
//        // 5
//        result.push_back(space == pos_end ? str.substr(pos) : str.substr(pos, space - pos));
//        // 6
//        if (space == pos_end) {
//            break;
//        }
//        else {
//            pos = space + 1;
//        }
//    }
//
//    return result;
//}