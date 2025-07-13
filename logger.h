#ifndef LOGGER_HEADER
#define LOGGER_HEADER

#include <map>
#include <string>
class Logger { 
  public: 
    Logger(std::string name, int level, bool stdOut, bool fileOut, std::string fileName);

    void setLevel(int level);

    void debug(std::string logMessage);
    void info(std::string logMessage);
    void warn(std::string logMessage);
    void error(std::string logMessage);

  private: 
    std::string _loggerName;
    std::string _filePath;
    int _logLevel;
    
    bool _stdOut, _fileOut;

    std::map<int, std::string> _logLevelMap;

    void _logToOutputs(std::string logLine);
    std::string _generateLogLine(std::string logMessage, int logLevel);
    std::string _getISOTimestamp();
    void _appendLineToFile(const std::string& filePath, const std::string& logLine);
};

#endif // !LOGGER_HEADER
