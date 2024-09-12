#include <Core/Scene.h>
#include <memory>
#include <pybind11/pybind11.h>

void ScenePtrBinding(pybind11::module_ &m) {
  pybind11::class_<Hamster::Scene, std::shared_ptr<Hamster::Scene>>(m, "Scene");
}
