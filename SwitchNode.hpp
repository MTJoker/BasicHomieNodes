#pragma once

#include <Homie.h>

class SwitchNode
{
public:

  enum State
  {
    UNKNOWN,
    OPEN,
    CLOSED
  };

  SwitchNode(const char* name, HomieNode& node, uint8_t pin);
  void begin();
  void setup();
  void loop();
  
private:

  const char* m_name;
  HomieNode& m_node;
  State m_state;

  Bounce m_switch;
};
