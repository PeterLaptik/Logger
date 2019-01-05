#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>

class Logger
{
    public:
        Logger();
        Logger(const std::string filename);
        virtual ~Logger();

        bool Info(const std::string &message);
        bool Debug(const std::string &message);
        bool Error(const std::string &message);
        bool Warning(const std::string &message);

        void SetShowTime(bool showTime = true) {m_WriteLogTime = showTime;}
        bool GetShowTime(void) {return m_WriteLogTime;}

    protected:

    private:
        bool CreateLogFile(const std::string filename = "");
        inline bool WriteMessage(const char *msgType, const std::string &message);

        std::ofstream *m_log_file;
        bool m_IsLogFileCreated;
        bool m_WriteLogTime;
};

#endif // LOGGER_H
