#include "HamsterPCH.h"

#include "Log.h"

namespace Hamster {
Logger::Logger(size_t bufferSize)
    : m_BufferSize(bufferSize), m_Buffer(bufferSize) {}

void Logger::Log(LogType type, const std::string &message) {
  m_Buffer[m_Tail] = {type, message};

  m_Tail = (m_Tail + 1) % m_BufferSize;

  if (m_Tail == m_Head) {
    m_Full = true;
    m_Head = (m_Head + 1) % m_BufferSize;
  } else {
    m_Full = false;
  }
}

void Log::Init(size_t maxBufSize) {
  m_CoreLogger = std::make_shared<Logger>(maxBufSize);
  m_ClientLogger = std::make_shared<Logger>(maxBufSize);
}
} // namespace Hamster
