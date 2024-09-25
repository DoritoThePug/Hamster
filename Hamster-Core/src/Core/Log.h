#ifndef LOG_H
#define LOG_H

#include <string>

namespace Hamster {
enum LogType { Info, Warning, Error };

struct LogEntry {
  LogType type;
  std::string message;
};

class Logger {
public:
  Logger(size_t bufferSize);

  void Log(LogType type, const std::string &message);
  const std::vector<LogEntry> &GetBuffer() { return m_Buffer; }

  [[nodiscard]] bool IsFull() { return m_Full; }
  [[nodiscard]] size_t GetHeadIndex() { return m_Head; }
  [[nodiscard]] size_t GetTailIndex() { return m_Tail; }
  [[nodiscard]] size_t GetBufferSize() { return m_Buffer.size(); }

private:
  size_t m_Head = 0;
  size_t m_Tail = 0;
  const size_t m_BufferSize;
  std::vector<LogEntry> m_Buffer;
  bool m_Full;
};

class Log {
public:
  static void Init(size_t maxBufSize = 100);

  static std::shared_ptr<Logger> GetCoreLogger() { return m_CoreLogger; }
  static std::shared_ptr<Logger> GetClientLogger() { return m_ClientLogger; }

private:
  static inline std::shared_ptr<Logger> m_CoreLogger;
  static inline std::shared_ptr<Logger> m_ClientLogger;
};
} // namespace Hamster

#define HAMSTER_CORE_LOG(type, message)                                        \
  Hamster::Log::GetCoreLogger()->Log(type, message);
#define HAMSTER_LOG(type, message)                                             \
  Hamster::Log::GetClientLogger()->Log(type, message);

#endif // !LOG_H
