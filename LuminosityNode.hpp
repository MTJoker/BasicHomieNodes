#pragma once

#include <Homie.h>
#include <AS_BH1750.h>

class LuminosityNode
{
public:

  LuminosityNode(const char* name);
  void begin(unsigned long intervalRead, unsigned long intervalPublish);
  void setup();
  void loop();
  float getLastValue() const;

private:

  const char* m_name;
  
  HomieNode* m_node;
  
  AS_BH1750 m_sensor;
  
  float m_lastLuxValue;
  float m_lastLuxValuePublish;

  unsigned long m_timeLastRead;
  unsigned long m_intervalRead;
  
  unsigned long m_timeLastPublish;
  unsigned long m_intervalPublish;
};

