#include "logger.h"
#include <ctime>
#include <filesystem>
#include <fstream>
#include <ios>
#include <iostream>
#include <map>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <system_error>

Logger::Logger(std::string name, int level, bool stdOut, bool fileOut, std::string filePath) {
  _loggerName = name;
  _stdOut = stdOut;
  _fileOut = fileOut;
  _filePath = filePath;
  _logLevel = level;
  
  if (fileOut == true && filePath == "") {
    std::cerr << "Error: Logger \"" << name << "\" set to file out but filepath not provided. Logging to std out.\n";
    _fileOut = false;
  }
  if (fileOut == false && stdOut == false) {
    std::cout << "Warning: Logger \"" << name << "\" set to no file out and no standard out.  Logs will not be generated.";
  }

  _logLevelMap = {
    {0, "DEBUG"},
    {1, "INFO"},
    {2, "WARNING"},
    {3, "ERROR"}
  };
}

void Logger::debug(std::string logMessage) {
  if (_logLevel > 0) {
    return;
  }
  std::string logLine = _generateLogLine(logMessage, 0);
  _logToOutputs(logLine);
}

void Logger::info(std::string logMessage) {
  if (_logLevel > 1) {
    return;
  }
  std::string logLine = _generateLogLine(logMessage, 1);
  _logToOutputs(logLine);
}

void Logger::warn(std::string logMessage) {
  if (_logLevel > 2) {
    return;
  }
  std::string logLine = _generateLogLine(logMessage, 2);
  _logToOutputs(logLine);
}

void Logger::error(std::string logMessage) {
 if (_logLevel > 3) {
   return;
 }
  std::string logLine = _generateLogLine(logMessage, 3);
  _logToOutputs(logLine);
}

void Logger::_logToOutputs(std::string logLine) {
  if (logLine.empty() || logLine.back() != '\n') {
    logLine += '\n';
  }
  if (_stdOut) {
    std::cout << logLine;
  }
  if (_fileOut) {
    _appendLineToFile(_filePath, logLine);
  }
}

std::string Logger::_generateLogLine(std::string logMessage, int logLevel) {
  std::ostringstream oss;
  oss << _logLevelMap[logLevel] << " | " << _loggerName << " | " << _getISOTimestamp() << " | " << logMessage;
  return oss.str();
}

std::string Logger::_getISOTimestamp() {
  const auto now = std::chrono::system_clock::now();
  const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
  const std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
  std::tm* tm = std::gmtime(&currentTime);
  
  std::ostringstream oss;
  oss << std::put_time(tm, "%Y-%m-%dT%H:%M:%S");
  oss << "." << std::setfill('0') << std::setw(3) << ms.count() << "Z";

  return oss.str();
}

void Logger::_appendLineToFile(const std::string& filePath, const std::string& logLine) {
  std::filesystem::path filePathObj(filePath);
  std::filesystem::path dirPathObj = filePathObj.parent_path();

  if (!dirPathObj.empty()) {
    std::error_code ec;
    if (!std::filesystem::create_directories(dirPathObj, ec)) {
      if (ec) {
        std::cerr << "Error creating log directory '" << dirPathObj.string() << "': " << ec.message() << std::endl;
      }
    }
  }

  std::ofstream outputFile(filePath, std::ios::app);
  if (!outputFile.is_open()) {
    std::cerr << "Error: Could not open file at path '" << filePath << "'.\n";
    return;
  }

  outputFile << logLine;
  outputFile.close();
}
