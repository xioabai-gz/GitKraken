#ifndef CLASS_GY39DATA_H
#define CLASS_GY39DATA_H

class ClassGY39
{
private:
    int m_nIllumination = 0;  // 照度，0~200000lux
    float m_fTemperature = 0; // 温度，-20~45℃
    float m_fPressure = 0;    // 气压，90~110kPa
    int m_nHumidity = 0;      // 湿度，0~100%RH
    int m_nAltitude = 0;      // 海拔，-200~9000m

public:
    int getIllumination();
    void setIllumination(int nIllumi);

    float getTemperature();
    void setTemperature(float fTemp);

    float getPressure();
    void setPressure(float fPres);

    int getHumidity();
    void setHumidity(int nHumi);

    int getAltitude();
    void setAltitude(int nAlti);
};

#endif // CLASS_GY39DATA_H
