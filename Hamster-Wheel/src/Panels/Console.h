#ifndef CONSOLE_H
#define CONSOLE_H

#include <Gui/Panel.h>

class Console : public Hamster::Panel {
public:
  explicit Console(std::shared_ptr<Hamster::Scene> scene)
      : Panel(std::move(scene), true) {};

  void Render() override;
};

#endif // !CONSOLE_H
