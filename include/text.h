#ifndef TEXT_H
#define TEXT_H

#include <vector>
#include <iostream>
#include <map>
#include <set>
#include <memory>
#include <string>
#include <sstream>
#include <fstream>


class QueryResult;

class TextQuery {
public:
    TextQuery(std::ifstream &in);
    QueryResult query(const std::string &keyword) const;

private:
    std::shared_ptr<std::vector<std::string>> m_data;
    std::map<std::string, std::shared_ptr<std::set<int>>> m_wordToLineMap;

};

class QueryResult {
public:
    friend std::ostream& print(std::ostream &out, const QueryResult &result);
    QueryResult(const std::string &keyword, std::shared_ptr<std::set<int>> lines, std::shared_ptr<std::vector<std::string>> data) 
        : m_word(keyword), m_lines(lines), m_data(data) { }

    
private:
    std::string m_word;
    std::shared_ptr<std::set<int>> m_lines;
    std::shared_ptr<std::vector<std::string>> m_data;
};

#endif