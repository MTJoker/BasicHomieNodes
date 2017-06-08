#include "LuminosityNode.hpp"

LuminosityNode::LuminosityNode(const char* name)
:
m_name(name),
m_intervalRead(0),
m_intervalPublish(0),
m_lastLuxValue(-1),
m_lastLuxValuePublish(-1),
m_timeLastPublish(0)
{
  m_node = new HomieNode(name, "luminosity");
}

void LuminosityNode::begin(unsigned long intervalRead, unsigned long intervalPublish)
{
  m_intervalRead = intervalRead;
  m_intervalPublish = intervalPublish;
  m_sensor.begin();
}

void LuminosityNode::setup()
{
  m_node->setProperty("unit").send("lux");
}

void LuminosityNode::loop()
{
  unsigned long now = millis();

  if(now - m_timeLastRead >= m_intervalRead * 1000UL || m_timeLastRead == 0) 
  {
    m_lastLuxValue = m_sensor.readLightLevel();
    m_timeLastRead = millis();

    if(now - m_timeLastPublish >= m_intervalPublish * 1000UL || m_timeLastPublish == 0) 
    {
      Homie.getLogger() << m_name << ": Luminosity is" << m_lastLuxValue << " lux" << endl;
      
      if(m_lastLuxValue != m_lastLuxValuePublish)
      {
        m_node->setProperty("lux").send(String(m_lastLuxValue));
        m_lastLuxValuePublish = m_lastLuxValue;
      }
      
      m_timeLastPublish = millis();
    }
  }
}

float LuminosityNode::getLastValue() const
{
  return m_lastLuxValue;
}

