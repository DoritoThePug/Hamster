#include <pybind11/pybind11.h>

#include "Core.h"
#include "Library.h"
#include "Utils.h"
#include "Renderer.h"


PYBIND11_MODULE(Hamster, m) {
	ApplicationBinding(m);
	GameObjectBinding(m);

	Vec2Binding(m);
	Vec3Binding(m);

	AssetManagerBinding(m);
	
	TextureBinding(m);
}