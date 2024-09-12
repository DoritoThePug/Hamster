#include <pybind11/embed.h>
#include <pybind11/pybind11.h>

#include "Components.h"
#include "Core.h"
#include "HamsterBehaviour.h"
#include "Library.h"
#include "UUID.h"

int add(int a, int b) { return a + b; }

PYBIND11_MODULE(Hamster, m) {
  Vec2Binding(m);
  Vec3Binding(m);
  UUIDBinding(m);
  TransformBinding(m);
  HamsterBehaviourBinding(m);
  ScenePtrBinding(m);

  m.def("add", &add);
}
