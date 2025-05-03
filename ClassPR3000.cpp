#include "ClassPR3000.h"

float ClassPR3000::getWindSpeed()
{
    return m_fWindSpeed;
}

void ClassPR3000::setWindSpeed(float fWS)
{
    m_fWindSpeed = fWS;
}

int ClassPR3000::getWindDirection()
{
    return m_nWindDirection;
}

void ClassPR3000::setWindDirection(int nWD)
{
    m_nWindDirection = nWD;
}
