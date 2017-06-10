#pragma once

#include <Homie.h>

class SwitchNode
{
public:

  SwitchNode(const char* name);
  void begin(long pin, long debounceInterval);
  void setup();
  void loop();
  bool isPressed() const;
  
private:

  const char* m_name;
  HomieNode* m_switchStateNode;

  Bounce m_switch;
  int m_lastSwitchState;
};
