#include "Console.h"

Console::Console(std::shared_ptr<Hamster::Scene> scene)
    : Panel(std::move(scene), true) {
  m_ClientLogger = m_Scene->GetClientLogger();
};

void Console::Render() {
  if (!ImGui::Begin("Console", &m_WindowOpen)) {
    ImGui::End();

    return;
  }

  size_t index = m_ClientLogger->GetTailIndex();
  size_t bufSize = m_ClientLogger->GetBufferSize();
  const std::vector<Hamster::LogEntry> &buffer = m_ClientLogger->GetBuffer();

  for (int i = 0; i < bufSize; i++) {
    std::string mes = buffer[index].message;

    if (!mes.empty()) {
      ImGui::TextUnformatted(mes.c_str());
    }

    index = (index + 1) % bufSize;
  }

  ImGui::End();
}
