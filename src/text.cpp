#include "text.h"

TextQuery::TextQuery(std::ifstream &in) {
    m_data = std::make_shared<std::vector<std::string>>();
    std::string line = "";
    int lineNo = 1;
    while (getline(in, line)) {
        std::stringstream ss(line);
        std::string word;
        while (ss >> word) {
            if (m_wordToLineMap.count(word) == 0) {
                auto tmp = std::make_shared<std::set<int>>();
                m_wordToLineMap.insert({word, tmp});
            }
            m_wordToLineMap[word]->insert(lineNo);
        }
        m_data->push_back(line);
        lineNo++;
    }
}

QueryResult TextQuery::query(const std::string &keyword) const {
    
    auto it = m_wordToLineMap.find(keyword);
    static std::shared_ptr<std::set<int>> nodata(new std::set<int>());
    if (it != m_wordToLineMap.end()) {
        return QueryResult(keyword, it->second, m_data);
    } else {
        return QueryResult(keyword, nodata, m_data);
    }

}


