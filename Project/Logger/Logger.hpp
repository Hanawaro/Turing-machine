#ifndef LOGGER_HPP
#define LOGGER_HPP

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>

using namespace std::string_literals;

class Logger {
public:
    enum Status { NONE, MESSAGE, ERROR, WARNING, SUCSESS, PROCESS, ALL };
    
    static void Init(void);
    static void Init(Status l_Status);
    static void SetStatus(Status l_Status);

    static void LogMessage(const std::string& l_Message);
    static void LogProcess(const std::string& l_Message);
    static void LogSucsess(const std::string& l_Message);
    static void LogWarning(const std::string& l_Message);
    static void LogError(const std::string& l_Message);

    static void Destroy(void);
private:
    static Status m_Status;
    static std::string m_LogName;
};

#endif
