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

  void Log(LogEntry &entry);
  const std::vector<LogEntry> &Get() { return m_Buffer; }

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
} // namespace Hamster

#endif // !LOG_H
