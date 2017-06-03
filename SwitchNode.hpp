#pragma once

#include <Homie.h>

class SwitchNode
{
public:

  SwitchNode(const char* name, HomieNode& node, uint8_t pin);
  void begin();
  void setup();
  void loop();
  bool isPressed() const;
  
private:

  const char* m_name;
  HomieNode& m_node;
  bool m_isPressed;

  Bounce m_switch;
};
