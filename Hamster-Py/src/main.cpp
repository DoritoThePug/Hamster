#include <pybind11/embed.h>
#include <pybind11/pybind11.h>

#include "Components.h"
#include "Core.h"
#include "HamsterBehaviour.h"
#include "Input.h"
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
  AppInstanceBinding(m);
  // EventDispatcherPtrBinding(m);
  //
  // TODO CHANGE APPLICATION TO A POINTER INSTEAD OF REFERENCE THATS WHY ITS
  // FAILING
  //
  KeyCodeEnumBinding(m);

  m.def("add", &add);
}
