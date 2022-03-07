#pragma once

#include <string>
#include <vector>
#include <deque>

#include "document.h"
#include "search_server.h"

class RequestQueue {
public:
    explicit RequestQueue(const SearchServer& search_server);

    template <typename DocumentPredicate>
    std::vector<Document> AddFindRequest(const std::string& raw_query, DocumentPredicate document_predicate);
    std::vector<Document> AddFindRequest(const std::string& raw_query, DocumentStatus status);
    std::vector<Document> AddFindRequest(const std::string& raw_query);
    uint64_t GetNoResultRequests() const;

private:
    struct QueryResult {
        uint64_t time_query_;
        size_t count_query_;
        bool status_query_;
    };
    std::deque<QueryResult> requests_;
    const static int sec_in_day_ = 1440;
    const SearchServer& search_server_;
    uint64_t number_empty_answer_ = 0;
    uint64_t time_ = 0;
};

template <typename DocumentPredicate>
std::vector<Document> RequestQueue::AddFindRequest(const std::string& raw_query,
    DocumentPredicate document_predicate) {
    ++time_;
    if (requests_.size() == sec_in_day_) {
        if (number_empty_answer_ > 0 && requests_.front().status_query_ == false) {
            --number_empty_answer_;
        }
        requests_.pop_front();
    }

    auto documents = search_server_.FindTopDocuments(raw_query, document_predicate);
    if (documents.size() == 0) {
        ++number_empty_answer_;
        requests_.push_back({ time_, requests_.size(), false });
    }
    else {
        requests_.push_back({ time_, requests_.size(), true });
    }

    return documents;
}