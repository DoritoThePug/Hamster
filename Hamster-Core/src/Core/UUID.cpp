//
// Created by Jaden on 28/08/2024.
//

#include "UUID.h"

Hamster::UUID::UUID()  : m_UUID(boost::uuids::random_generator()())  {

}
