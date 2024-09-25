#include "HamsterPCH.h"

#include "Log.h"

namespace Hamster {
Logger::Logger(size_t bufferSize)
    : m_BufferSize(bufferSize), m_Buffer(bufferSize) {}

void Logger::Log(LogEntry &entry) {
  m_Buffer[m_Tail] = entry;

  m_Tail = (m_Tail + 1) % m_BufferSize;

  if (m_Tail == m_Head) {
    m_Full = true;
    m_Head = (m_Head + 1) % m_BufferSize;
  } else {
    m_Full = false;
  }
}
} // namespace Hamster
