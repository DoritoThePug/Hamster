#pragma once

#include <iostream>
#include <ostream>
#include <string>

#include "Core/UUID.h"

namespace Hamster {
	class Texture {
	public:
		Texture(const std::string &texturePath);

		void BindTexture();

		[[nodiscard]] const std::string &GetTexturePath() const {
			return m_TexturePath;
		}

		void SetUUID(UUID uuid) { m_UUID = uuid; };
		UUID GetUUID() { return m_UUID; };

		void SetName(std::string name) { m_TextureName = name; }
		std::string GetName() { return m_TextureName; }

	private:
		unsigned int m_ID;
		const std::string m_TexturePath;
		std::string m_TextureName = "Untitled Texture";
		UUID m_UUID;
	};
}

