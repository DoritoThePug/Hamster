#include <Core/Application.h>
#include <Core/Scene.h>
#include <Events/ScriptingEvent.h>
#include <memory>
#include <pybind11/pybind11.h>

void ScenePtrBinding(pybind11::module_ &m) {
  pybind11::class_<Hamster::Scene, std::shared_ptr<Hamster::Scene>>(m, "Scene");
}

void AppInstanceBinding(pybind11::module_ &m) {
  pybind11::class_<Hamster::Application>(m, "Application");
}

void EventDispatcherPtrBinding(pybind11::module_ &m) {
  pybind11::class_<Hamster::EventDispatcher,
                   std::shared_ptr<Hamster::EventDispatcher>>(
      m, "EventDispatcher");
}

// void ScriptingEventDispatcherBinding(pybind11::module_ &m) {
//   pybind11::class_<Hamster::ScriptingEventDispatcher,
//                    std::shared_ptr<Hamster::ScriptingEventDispatcher>>(
//       m, "ScriptingEventDispatcher")
//       .def("subscribe", &Hamster::ScriptingEventDispatcher::Subscribe);
// }
