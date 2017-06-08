#pragma once

#include <Homie.h>
#include <NewPing.h>

class BinaryDistanceNode
{
public:

  enum State
  {
    UNKNOWN,
    AVAILABLE,
    UNAVAILABLE
  };

  BinaryDistanceNode(const char* name);
  void begin(uint8_t triggerPin, uint8_t echoPin, long unavailableThreshold, long measureInterval, long measureHysteresis);
  void setup();
  void loop();
  
private:

  NewPing* m_pPing;
  const char* m_name;
  HomieNode* m_statusNode;
  unsigned int m_unavailableThreshold;
  State m_state;
  unsigned long m_lastTimeMeasure;
  unsigned long m_lastDistance;
  unsigned long m_measureInterval;
  unsigned int m_availHysteresis;
  unsigned int m_availHysteresisDone;
  unsigned int m_unavailHysteresis;
  unsigned int m_unavailHysteresisDone;
};
