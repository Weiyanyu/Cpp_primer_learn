#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>

class Employee {
public:
    Employee() {
        m_name = "";
        m_id = m_globalId++;
    }

    Employee(const std::string &name) : m_name(name) {
        m_id = m_globalId++;
    }

    Employee(const Employee &rhs) {
        m_name = rhs.m_name;
        m_id = m_globalId++;
    }

    Employee& operator=(const Employee &rhs) {
        m_name = rhs.m_name;
        m_id = m_globalId++;
        return *this;
    }


    long getId() {
        return m_id;
    }
private:
    std::string m_name;
    long m_id;
    
    static long m_globalId;
};

#endif