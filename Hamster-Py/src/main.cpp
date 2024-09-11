#include <pybind11/embed.h>
#include <pybind11/pybind11.h>

#include "HamsterBehaviour.h"
#include "Library.h"
#include "UUID.h"

int add(int a, int b) { return a + b; }

PYBIND11_MODULE(Hamster, m) {
  Vec2Binding(m);
  Vec3Binding(m);
  UUIDBinding(m);
  HamsterBehaviourBinding(m);

  m.def("add", &add);
}
