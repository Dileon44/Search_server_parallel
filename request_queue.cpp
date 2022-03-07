#include "request_queue.h"

using std::string;
using std::vector;

RequestQueue::RequestQueue(const SearchServer& search_server) : search_server_(search_server) {}

vector<Document> RequestQueue::AddFindRequest(const string& raw_query, DocumentStatus status) {
    return AddFindRequest(raw_query, [status](int document_id, DocumentStatus document_status, int rating) {
        return document_status == status;
        });
}

vector<Document> RequestQueue::AddFindRequest(const string& raw_query) {
    return AddFindRequest(raw_query, DocumentStatus::ACTUAL);
}

uint64_t RequestQueue::GetNoResultRequests() const {
    return number_empty_answer_;
}