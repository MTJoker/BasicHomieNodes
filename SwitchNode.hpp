#pragma once

#include <Homie.h>

class SwitchNode : public HomieNode
{
public:

  SwitchNode(const char* name);
  void begin(long pin);
  void setup();
  void loop();
  bool isPressed() const;
  
private:

  const char* m_name;
  bool m_isPressed;

  Bounce m_switch;
};
