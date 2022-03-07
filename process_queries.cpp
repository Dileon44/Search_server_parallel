#include "process_queries.h"

#include <string>
#include <vector>
//#include <execution>
//#include <algorithm>
//#include <utility>

std::vector<std::vector<Document>> ProcessQueries(
    const SearchServer& search_server,
    const std::vector<std::string>& queries)
{
    std::vector<std::vector<Document>> search_results(queries.size());
    transform(
        std::execution::par,
        queries.begin(), queries.end(),
        search_results.begin(),
        [&search_server](const std::string& query) {
            return search_server.FindTopDocuments(query);
        }
    );

    return search_results;
}

std::list<Document> ProcessQueriesJoined(
    const SearchServer& search_server,
    const std::vector<std::string>& queries)
{
    std::list<Document> all_finded_documents;
    for (auto& documents : ProcessQueries(search_server, queries)) {
        for (auto& document : documents) {
            all_finded_documents.push_back(std::move(document));
        }
    }
    return all_finded_documents;
}