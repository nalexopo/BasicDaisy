#ifndef LFO_H
#define LFO_H



class lfo
{
    public:

    lfo(){};
    lfo(float sample_rate)
    {
        Init(sample_rate);
    }
    ~lfo(){};

    enum waveform
    {
        WAVE_SIN,
        WAVE_TRI,
        WAVE_SAW,
        WAVE_RAMP,
        WAVE_SQUARE,
        WAVE_POLYBLEP_TRI,
        WAVE_POLYBLEP_SAW,
        WAVE_POLYBLEP_SQUARE,
        WAVE_LAST,
    };

    void Init(float sample_rate)
    {
        sampleRate_     = sample_rate;
        freq_           = 10.0f;
        phase_inc_      = CalcPhaseInc(freq_);
        waveform_       = WAVE_SIN;
        sqpulse_duty_   = 0.5f;
        gain_           = 0.5f;
        phase_          = 0.0f;
        eoc_            = false;
    }

    void SetFreq(float freq);
    void SetGain(float gain)
    {
        gain_ = gain;
    }
    void SetWaveform(enum waveform waveform)
    {
        waveform_ = waveform;
    }


    float Process(void);
    private:
    float   CalcPhaseInc(float f);
    enum waveform waveform_;
    float   freq_, sampleRate_, phase_inc_, phase_, gain_, sqpulse_duty_;
    bool    eoc_;

};



#endif //LFO_H   