#include <pybind11/pybind11.h>

#include <Core/Log.h>
#include <string>

void LoggingEnumBinding(pybind11::module_ &m) {
  pybind11::enum_<Hamster::LogType>(m, "log_type")
      .value("Info", Hamster::LogType::Info)
      .value("Warning", Hamster::LogType::Warning)
      .value("Error", Hamster::LogType::Error);
}
