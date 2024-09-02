//
// Created by Jaden on 28/08/2024.
//

#ifndef UUID_H
#define UUID_H

#include <boost/container_hash/hash.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

namespace Hamster {
    class UUID {
    public:
        UUID();

        UUID(boost::uuids::uuid uuid);

        std::string GetUUIDString() { return boost::uuids::to_string(m_UUID); }
        [[nodiscard]] boost::uuids::uuid GetUUID() const { return m_UUID; }

        [[nodiscard]] static bool IsNil(UUID uuid) { return uuid.GetUUID().is_nil(); }
        [[nodiscard]] static UUID GetNil() { return {boost::uuids::nil_uuid()}; }

    private:
        boost::uuids::uuid m_UUID;
        static boost::uuids::random_generator m_RandomGenerator;
    };
}

namespace std {
    template<>
    struct hash<Hamster::UUID> {
        std::size_t operator()(const Hamster::UUID &uuid) const {
            return boost::hash<boost::uuids::uuid>()(uuid.GetUUID());
        }
    };

    template<>
    struct equal_to<Hamster::UUID> {
        bool operator()(const Hamster::UUID &lhs, const Hamster::UUID &rhs) const {
            return lhs.GetUUID() == rhs.GetUUID();
        }
    };
}

#endif //UUID_H
