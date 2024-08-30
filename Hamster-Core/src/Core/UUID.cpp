//
// Created by Jaden on 28/08/2024.
//

#include "UUID.h"

#include <iostream>

Hamster::UUID::UUID()  : m_UUID(boost::uuids::random_generator()())  {
    // std::cout << m_UUID << std::endl;
}

Hamster::UUID::UUID(boost::uuids::uuid uuid) {
    m_UUID = uuid;
}
