#ifndef CLASS_PR3000_H
#define CLASS_PR3000_H

class ClassPR3000
{
private:
    float m_fWindSpeed = 0;   // 风速，0~20m/s
    int m_nWindDirection = 0; // 风向，0~359度（从正北开始，顺时针计算）

public:
    float getWindSpeed();
    void setWindSpeed(float fWS);

    int getWindDirection();
    void setWindDirection(int nWD);
};

#endif // CLASS_PR3000_H
