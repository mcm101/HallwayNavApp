#include "fir.h"

filter *fir_create(int taps, float *coeffs)
{
  int i;
  
  filter *f = (filter *) malloc(sizeof(filter));
  
  if (taps > 32) taps = 32;
  
  f->next_sample = 0;
  f->taps = taps;
  
  for (i = 0; i < taps; i++)
  {
    f->samples[i] = 0;
    f->coeffs[i] = coeffs[i];
  }
  
  return f;
}

float fir_filter(filter *f, float val)
{
  float sum = 0;
  int i, j;
  // assign new value to "next" slot
  f->samples[f->next_sample] = val;
  // calculate a weighted sum
  // i tracks the next coeficeint
  // j tracks the samples w/wrap-around
  for (i = 0, j = f->next_sample; i < f->taps; i++)
  {
    sum += f->coeffs[i] * f->samples[j++];
    if (j == f->taps) j = 0;
  }
  
  if(++(f->next_sample) == f->taps)
    f->next_sample = 0;
  
  return(sum);
}

