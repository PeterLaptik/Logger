#include "Logger.h"

#if defined(_WIN16) | defined(_WIN32) | defined(_WIN64)
    #define PATH_SEPERATOR "\\"
#else
    #define PATH_SEPERATOR "/"
#endif

extern "C"
{
    char* logger_c_get_date(void);
    char* logger_c_get_path(void);
}

/** File name **/
static const char *m_log_file_name = "log.txt";

/** Messages types **/
static const char LOG_MES_INFO[] = "INFO: ";
static const char LOG_MES_WARNING[] = "WARNING: ";
static const char LOG_MES_ERROR[] = "ERROR: ";
static const char LOG_MES_DEBUG[] = "DEBUG: ";
static const char LOG_TEXT_TIME_MARGIN[] = " - ";

Logger::Logger()
{
    m_IsLogFileCreated = CreateLogFile();
    m_WriteLogTime = true;
}

Logger::Logger(const std::string filename)
{
    m_IsLogFileCreated = CreateLogFile(filename);
    m_WriteLogTime = true;
}

Logger::~Logger()
{
    if (m_IsLogFileCreated)
    {
        m_log_file->close();
        delete m_log_file;
    }
}

bool Logger::CreateLogFile(const std::string filename)
{
    char *programPath = logger_c_get_path();

    if (programPath==NULL)  // error getting current program path
        return false;

    std::string filePath(programPath);
    filePath += PATH_SEPERATOR;
    if (filename.length()==0)
    {
        filePath += m_log_file_name;    // filename by default
    }
    else
    {
        filePath += filename;
    }
    m_log_file = new std::ofstream(filePath.c_str()); // create log-file
    return true;
}

bool Logger::Info(const std::string &message)
{
    return WriteMessage(LOG_MES_INFO, message);
}

bool Logger::Debug(const std::string &message)
{
    return WriteMessage(LOG_MES_DEBUG, message);
}

bool Logger::Warning(const std::string &message)
{
    return WriteMessage(LOG_MES_WARNING, message);
}

bool Logger::Error(const std::string &message)
{
    return WriteMessage(LOG_MES_ERROR, message);
}

bool Logger::WriteMessage(const char *msgType, const std::string &message)
{
    if (!m_IsLogFileCreated)
        return false;

    std::string messageToWrite(msgType);                           // create message

    if (m_WriteLogTime)
    {
        messageToWrite += logger_c_get_date();
        messageToWrite += LOG_TEXT_TIME_MARGIN;
    }

    messageToWrite += message;
    messageToWrite += "\n";
    m_log_file->write(messageToWrite.c_str(), messageToWrite.length()); // write message
    return true;
}
