//
// Created by Jaden on 28/08/2024.
//

#include "UUID.h"

#include <iostream>

namespace Hamster {
    UUID::UUID() : m_UUID(boost::uuids::random_generator()()) {
        // std::cout << m_UUID << std::endl;
    }

    UUID::UUID(boost::uuids::uuid uuid) {
        m_UUID = uuid;
    }

    void UUID::Serialise(std::ostream &out, const UUID &uuid) {
        boost::uuids::uuid uuidValue = uuid.GetUUID();

        out.write(reinterpret_cast<const char *>(&uuidValue), uuidValue.size());
    }

    UUID UUID::Deserialise(std::istream &in) {
        boost::uuids::uuid uuidValue;

        in.read(reinterpret_cast<char *>(&uuidValue), uuidValue.size());

        return {uuidValue};
    }
}
