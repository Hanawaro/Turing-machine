#include <Logger.hpp>

#include <fstream>
#include <ctime>

Logger::Status Logger::m_Status = Logger::Status::SUCSESS;
std::string Logger::m_LogName = "";

void Logger::Init(void) {
    char buffer[255] = { 0 };
    time_t seconds = time(NULL);
    tm* timeinfo = localtime(&seconds);
    strftime(buffer, 80, "%d-%B-%Y %H-%M-%S.log", timeinfo);
    m_LogName = buffer;
    
    std::ofstream tmp(m_LogName);
    tmp.close();
    
    if (m_Status >= Logger::Status::SUCSESS) {
        strftime(buffer, 80, "[ SUCSESS | %H:%M:%S]  ", timeinfo);
        std::cout << buffer << "Logger initialize" << std::endl;
    }
}

void Logger::Init(Status l_Status) {
    SetStatus(l_Status);
    
    char buffer[255] = { 0 };
    time_t seconds = time(NULL);
    tm* timeinfo = localtime(&seconds);
    strftime(buffer, 80, "%d-%B-%Y %H-%M-%S.log", timeinfo);
    m_LogName = buffer;
    
    std::ofstream tmp(m_LogName);
    tmp.close();
    
    if (m_Status >= Logger::Status::SUCSESS) {
        strftime(buffer, 80, "[ SUCSESS | %H:%M:%S]  ", timeinfo);
        std::cout << buffer << "Logger initialize" << std::endl;
    }
}

void Logger::SetStatus(Status l_Status) {
    m_Status = l_Status;
}

void Logger::LogMessage(const std::string& l_Message) {
    if (m_Status >= Logger::Status::MESSAGE) {
        char buffer[255] = { 0 };
        time_t seconds = time(NULL);
        tm* timeinfo = localtime(&seconds);
        strftime(buffer, 80, "[ MESSAGE | %H:%M:%S]  ", timeinfo);
            
        std::fstream tmp(m_LogName, std::ios::app | std::ios::in);
        tmp << buffer << l_Message << std::endl;
        tmp.close();
        
        std::cout << buffer << l_Message << std::endl;
    }
}

void Logger::LogSucsess(const std::string& l_Message) {
    if (m_Status >= Logger::Status::SUCSESS) {
        char buffer[255] = { 0 };
        time_t seconds = time(NULL);
        tm* timeinfo = localtime(&seconds);
        strftime(buffer, 80, "[ SUCSESS | %H:%M:%S]  ", timeinfo);

        std::fstream tmp(m_LogName, std::ios::app | std::ios::in);
        tmp << buffer << l_Message << std::endl;
        tmp.close();
        
        std::cout << buffer << l_Message << std::endl;
    }
}

void Logger::LogWarning(const std::string& l_Message) {
    if (m_Status >= Status::WARNING) {
        char buffer[255] = { 0 };
        time_t seconds = time(NULL);
        tm* timeinfo = localtime(&seconds);
        strftime(buffer, 80, "[ WARNING | %H:%M:%S]  ", timeinfo);
        
        std::fstream tmp(m_LogName, std::ios::app | std::ios::in);
        tmp << buffer << l_Message << std::endl;
        tmp.close();
        
        std::cout << buffer << l_Message << std::endl;
    }
}

void Logger::LogError(const std::string& l_Message) {
    if (m_Status >= Logger::Status::ERROR) {
        char buffer[255] = { 0 };
        time_t seconds = time(NULL);
        tm* timeinfo = localtime(&seconds);
        strftime(buffer, 80, "[ ERROR | %H:%M:%S]  ", timeinfo);
        
        std::fstream tmp(m_LogName, std::ios::app | std::ios::in);
        tmp << buffer << l_Message << std::endl;
        tmp.close();
        
        std::cout << buffer << l_Message << std::endl;
    }
}

void Logger::LogProcess(const std::string& l_Message) {
    if (m_Status >= Logger::Status::PROCESS) {
        char buffer[255] = { 0 };
        time_t seconds = time(NULL);
        tm* timeinfo = localtime(&seconds);
        strftime(buffer, 80, "[ PROCESS | %H:%M:%S]  ", timeinfo);

        std::fstream tmp(m_LogName, std::ios::app | std::ios::in);
        tmp << buffer << l_Message << std::endl;
        tmp.close();
        
        std::cout << buffer << l_Message << std::endl;
    }
}


void Logger::Destroy(void) {
    if (m_Status >= Logger::Status::SUCSESS) {
        char buffer[255] = { 0 };
        time_t seconds = time(NULL);
        tm* timeinfo = localtime(&seconds);
        strftime(buffer, 80, "[ SUCSESS | %H:%M:%S]  ", timeinfo);

        std::cout << buffer << "Logger closed" << std::endl;
    }
}




