#pragma once

#include <Core/UUID.h>
#include <Scripting/HamsterBehaviour.h>

class PyHamsterBehaviour : Hamster::HamsterBehaviour {
public:
  using Hamster::HamsterBehaviour::HamsterBehaviour;

  void OnUpdate() override {
    PYBIND11_OVERRIDE(void, Hamster::HamsterBehaviour, OnUpdate, );
  }
};

void HamsterBehaviourBinding(pybind11::module_ m) {
  pybind11::class_<Hamster::HamsterBehaviour, PyHamsterBehaviour>(
      m, "HamsterBehaviour")
      .def(pybind11::init<Hamster::UUID, std::shared_ptr<Hamster::Scene>>())
      .def("OnUpdate", &Hamster::HamsterBehaviour::OnUpdate)
      // .def_property("transform", &);
      .def_property("transform", &Hamster::HamsterBehaviour::GetTransform,
                    &Hamster::HamsterBehaviour::SetTransform);
}
