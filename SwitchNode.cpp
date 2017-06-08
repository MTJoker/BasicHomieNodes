#include "SwitchNode.hpp"

const long DEBOUNCE_INTERVAL_DEFAULT = 50;

SwitchNode::SwitchNode(const char* name)
:
m_name(name),
m_isPressed(false)
{
  m_switchStateNode = new HomieNode(name, "status");
}

void SwitchNode::begin(long pin)
{
  pinMode(pin, INPUT_PULLUP);

  m_switch.attach(pin);
  m_switch.interval(DEBOUNCE_INTERVAL_DEFAULT);  
}

void SwitchNode::setup()
{
  m_switchStateNode->setProperty("status").send("unknown");
}

void SwitchNode::loop()
{
  m_switch.update();
  
  if(m_switch.rose())
  {
    Homie.getLogger() << m_name << ": Status is open" << endl;
    m_switchStateNode->setProperty("status").send("open"); 
    m_isPressed = false;
  }
  else if(m_switch.fell())
  {
    Homie.getLogger() << m_name << ": Status is closed" << endl;
    m_switchStateNode->setProperty("status").send("closed"); 
    m_isPressed = true;
  }
}

bool SwitchNode::isPressed() const
{
  return m_isPressed;
}

