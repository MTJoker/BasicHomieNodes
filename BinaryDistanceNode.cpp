#include "BinaryDistanceNode.hpp"

BinaryDistanceNode::BinaryDistanceNode(const char* name, HomieNode& node)
:
m_name(name),
m_node(node),
m_lastTimeMeasure(0),
m_lastDistance(0),
m_measureInterval(0),
m_state(UNKNOWN),
m_availHysteresis(0),
m_availHysteresisDone(0),
m_unavailHysteresis(0),
m_unavailHysteresisDone(0),
m_unavailableThreshold(0)
{
}

void BinaryDistanceNode::begin(uint8_t triggerPin, uint8_t echoPin, long unavailableThreshold, long measureInterval, long measureHysteresis)
{
  m_pPing = new NewPing(triggerPin, echoPin, 200);
  m_unavailableThreshold = unavailableThreshold;
  m_measureInterval = measureInterval;
  m_availHysteresis = measureHysteresis;
  m_unavailHysteresis = measureHysteresis;
}

void BinaryDistanceNode::setup()
{
  m_node.setProperty("distance").send(String(0));
  m_node.setProperty("state").send("unknown");
}

void BinaryDistanceNode::loop()
{
  unsigned long now = millis();

  if(now - m_lastTimeMeasure >= m_measureInterval * 1000UL || m_lastTimeMeasure == 0) 
  {
    // ping 10 times and build median to filter out errors
    unsigned long us = m_pPing->ping_median(10, 200);
    unsigned long distance = m_pPing->convert_cm(us);

    Homie.getLogger() << m_name << ": Distance is " << distance << "cm" << endl;

    m_lastTimeMeasure = millis();
    
    if(distance != m_lastDistance)
    { 
      m_node.setProperty("distance").send(String(distance)); 
      m_lastDistance = distance;
    }
      
    if( (distance >= m_unavailableThreshold) || (distance == 0) ) 
    {
      // unavailable
      m_unavailHysteresisDone++;
      m_availHysteresisDone = 0;
    }
    else  
    {
      // available
      m_availHysteresisDone++;
      m_unavailHysteresisDone = 0;
    }

    if(m_availHysteresisDone >= m_availHysteresis)
    {
      m_availHysteresisDone = 0;

      if(m_state != AVAILABLE)
      {
        m_state = AVAILABLE;
        m_node.setProperty("state").send("available");
      }
    }
    else if(m_unavailHysteresisDone >= m_unavailHysteresis)
    {
      m_unavailHysteresisDone = 0;

      if(m_state != UNAVAILABLE)
      {
        m_state = UNAVAILABLE;
        m_node.setProperty("state").send("unavailable");
      }
    }
  }
}

