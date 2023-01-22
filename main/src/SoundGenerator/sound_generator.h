#ifndef SOUND_GENERATOR_H
#define SOUND_GENERATOR_H
#include <Arduino.h>

const double octive_base_freq = 110.0; // A2
const double d12_root_of_2 = pow(2.0,1.0/12);
double clacFreq(uint8 note) {octive_base_freq*pow(d12_root_of_2,note);}


#define PI2 6.283185307179586232


enum waveType {
    Sine,
    Square,
    Tri,
    Saw,
    Noise
};

// sine approx
double fsin(double x) {
    double t = x*0.15915;
    t = t - (int)t;
    if (t < 0.5) {
        return (-16.0 * t * t) + (8.0 * t);
    } else {
        return (16.0 * t * t) - (16.0 * t) - (8.0 * t) + 8.0;
    }
}

// faster sin approx
double ffsin(double x) {
    float t = x*0.15915f;
    t = t-(int)t;
    return 20.785f*t*(t-0.5f)*(t-1.0f);
}



double sineWave(double freq, double dTime) {
    return ffsin(freq*dTime*PI2);
}
double twoSineWaves(double freq, double dTime) {
    return (ffsin(freq*dTime*PI2)+ffsin(freq*4*dTime+0.1*PI2)+ffsin(freq*8*dTime+0.2*PI2))*0.33;
}
double squareWave(double freq, double dTime) {
    return sineWave(freq, dTime) > 0 ? 1 : -1;
}
double triangleWave(double freq, double dTime) {
    return asin(sin((freq*PI2)*dTime)) * 2.0/PI;
    
}


double osc(double freq, double dTime, int Type) {
    switch (Type)
    {
    case 0:
        /* code */
        break;
    
    default:
        break;
    }
}





#endif