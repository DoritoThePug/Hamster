#include <Core/Components.h>
#include <glm/glm.hpp>
#include <pybind11/pybind11.h>

namespace py = pybind11;

void TransformBinding(py::module_ &m) {
  py::class_<Hamster::Transform>(m, "Transform")
      .def(py::init<glm::vec2, float, glm::vec2>())
      .def_readwrite("position", &Hamster::Transform::position);
}
