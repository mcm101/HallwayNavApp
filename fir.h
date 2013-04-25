#ifndef FIR_H
#define FIR_H

#define MAX_TAPS 32; // doesn't fucking work!

typedef struct
{
  int taps;
  float coeffs[32];
  int next_sample;
  float samples[32];
} filter;

extern filter* fir_create(int, float*);
extern float fir_filter(filter*, float);

#endif /* FIR_H */
