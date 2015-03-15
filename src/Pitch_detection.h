//
//  Pitch_detection.h
//  http_example
//
//  Created by Phoenix Perry on 11/03/15.
//
//

#ifndef __http_example__Pitch_detection__
#define __http_example__Pitch_detection__

#include <stdio.h>
#include "aubio.h"
#include "fvec.h"
#include "ofMain.h"
class Pitch_detection{
public:
    
    void setup();
    void processAudio(float * buffer, int bufferSize);
    
    ~Pitch_detection();
    
    float pitch;
    float amplitude;
    float confidence;
    
    // ------------------------------------------------------------------
    // internal aubio variables
    
    uint_t win_s;							/* window size */
    uint_t hop_s;							/* hop size */
    uint_t samplerate;						/* samplerate */
    uint_t channels;						/* number of channel */
    
    fvec_t * out;
    fvec_t * in;
    aubio_pitch_t * pitch_output ;
    
    // ------------------------------------------------------------------
};
// ------------------------------------------------------------------

#endif /* defined(__http_example__Pitch_detection__) */
