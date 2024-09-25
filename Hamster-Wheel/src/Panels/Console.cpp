#include "Console.h"

void Console::Render() {
  if (!ImGui::Begin("Console", &m_WindowOpen)) {
    ImGui::End();

    return;
  }

  size_t index = m_Scene->GetClientLogger()->GetTailIndex();
  size_t bufSize = m_Scene->GetClientLogger()->GetBufferSize();
  const std::vector<Hamster::LogEntry> &buffer =
      Hamster::Log::GetClientLogger()->GetBuffer();

  for (int i = 0; i < bufSize; i++) {
    std::string mes = buffer[index].message;

    if (!mes.empty()) {
      ImGui::TextUnformatted(mes.c_str());
    }

    index = (index + 1) % bufSize;
  }

  ImGui::End();
}
