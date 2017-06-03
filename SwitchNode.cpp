#include "SwitchNode.hpp"

const long DEBOUNCE_INTERVAL_DEFAULT = 50;

SwitchNode::SwitchNode(const char* name)
:
HomieNode(name, "status"),
m_name(name),
m_isPressed(false)
{
}

void SwitchNode::begin(long pin)
{
  pinMode(pin, INPUT_PULLUP);

  m_switch.attach(pin);
  m_switch.interval(DEBOUNCE_INTERVAL_DEFAULT);  
}

void SwitchNode::setup()
{
  setProperty("status").send("unknown");
}

void SwitchNode::loop()
{
  m_switch.update();
  
  if(m_switch.rose())
  {
    Homie.getLogger() << m_name << ": Status is open" << endl;
    setProperty("status").send("open"); 
    m_isPressed = false;
  }
  else if(m_switch.fell())
  {
    Homie.getLogger() << m_name << ": Status is closed" << endl;
    setProperty("status").send("closed"); 
    m_isPressed = true;
  }
}

bool SwitchNode::isPressed() const
{
  return m_isPressed;
}

