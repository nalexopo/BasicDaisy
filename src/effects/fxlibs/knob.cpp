#include "knob.h"
#include <math.h>

void knob::Init(Curve curve, float min, float max)
{
    pmin_   = min;
    pmax_   = max;
    pcurve_ = curve;
    lmin_   = logf(min < 0.0000001f ? 0.0000001f : min);
    lmax_   = logf(max);
}

void knob::UnityCalibrate(float offset, float scale, float zero_lim, float one_lim)
{
    unity_offset_ = offset;
    unity_scale_ = scale;
    unity_zero_lim_ = zero_lim;  
    unity_one_lim_  = one_lim;
}

float knob::UnityProcess(float adcfloat)
{
    float ret;
    ret = unity_scale_ * adcfloat + unity_offset_;
    if (ret < unity_zero_lim_)
        ret = 0.f;
    if (ret > unity_one_lim_)
        ret = 1.f;

    return ret;
}

float knob::Process(float adcfloat)
{

    float unity_processed = UnityProcess(adcfloat);
    switch(pcurve_)
    {
        case LINEAR: val_ = unity_processed ; break;
        case LOGARITHMIC:
            val_ = unity_processed;
            val_ = val_ * val_ ;
            break;
        case EXPONENTIAL:
            if (unity_processed  < unity_zero_lim_)
            {
                val_ = 0.f;
            }
            else
            {
                val_ = expf((unity_processed * (lmax_ - lmin_)) + lmin_);
            }
            break;
        case CUBE:
            val_ = unity_processed;
            val_ = (val_ * (val_ * val_));
            break;
        default: break;
    }
    return val_;
}