#include "ClassGY39.h"

int ClassGY39::getIllumination()
{
    return m_nIllumination;
}

void ClassGY39::setIllumination(int nIllumi)
{
    m_nIllumination = nIllumi;
}

float ClassGY39::getTemperature()
{
    return m_fTemperature;
}

void ClassGY39::setTemperature(float fTemp)
{
    m_fTemperature = fTemp;
}

float ClassGY39::getPressure()
{
    return m_fPressure;
}

void ClassGY39::setPressure(float fPres)
{
    m_fPressure = fPres;
}

int ClassGY39::getHumidity()
{
    return m_nHumidity;
}

void ClassGY39::setHumidity(int nHumi)
{
    m_nHumidity = nHumi;
}

int ClassGY39::getAltitude()
{
    return m_nAltitude;
}

void ClassGY39::setAltitude(int nAlti)
{
    m_nAltitude = nAlti;
}
