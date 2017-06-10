#include "SwitchNode.hpp"

SwitchNode::SwitchNode(const char* name)
:
m_name(name),
m_lastSwitchState(-1)
{
  m_switchStateNode = new HomieNode(name, "status");
}

void SwitchNode::begin(long pin, long debounceInterval)
{
  pinMode(pin, INPUT_PULLUP);

  m_switch.attach(pin);
  m_switch.interval(debounceInterval);  
}

void SwitchNode::setup()
{
  m_switchStateNode->setProperty("status").send("unknown");
}

void SwitchNode::loop()
{
  m_switch.update();

  int currentSwitchState = m_switch.read();

  if(currentSwitchState != m_lastSwitchState)
  {
    if(HIGH == currentSwitchState)
    {
       Homie.getLogger() << m_name << ": Status is open" << endl;
       m_switchStateNode->setProperty("status").send("open"); 
    }
    else
    {
      Homie.getLogger() << m_name << ": Status is closed" << endl;
      m_switchStateNode->setProperty("status").send("closed"); 
    }

    m_lastSwitchState = currentSwitchState;
  }
}

bool SwitchNode::isPressed() const
{
  return (LOW == m_lastSwitchState) ? true : false;
}

