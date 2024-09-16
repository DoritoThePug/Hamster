//
// Created by Jaden on 31/08/2024.
//

#ifndef PROJECTSERIALISER_H
#define PROJECTSERIALISER_H

#include "Project.h"

namespace Hamster {
class ProjectSerialiser {
public:
  explicit ProjectSerialiser(std::shared_ptr<Project> project)
      : m_Project(std::move(project)) {};

  void Serialise(std::ostream &out);

  static ProjectConfig Deserialise(std::istream &in);

private:
  std::shared_ptr<Project> m_Project;
};
} // namespace Hamster

#endif // PROJECTSERIALISER_H
