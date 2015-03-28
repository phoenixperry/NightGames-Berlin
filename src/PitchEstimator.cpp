//
//  PitchEstimator.cpp
//  http_example
//
//  Created by Phoenix Perry on 15/03/15. - this is from Joshua Nobel's book programming interactivity - it's here for a sample. I'm just building off it. 
//
//

#include "pitchEstimator.h"
//record of all possible pitches
const string note[120] ={
    "C -1", "C#-1", "D -1", "D#-1", "E -1", "F -1", "F#-1", "G -1", "G#-1", "A -1", "A#-1", "B -1",
    "C 0", "C#0", "D 0", "D#0", "E 0", "F 0", "F#0", "G 0", "G#0", "A 0", "A#0", "B 0",
    "C 1", "C#1", "D 1", "D#1", "E 1", "F 1", "F#1", "G 1", "G#1", "A 1", "A#1", "B 1",
    "C 2", "C#2", "D 2", "D#2", "E 2", "F 2", "F#2", "G 2", "G#2", "A 2", "A#2", "B 2",
    "C 3", "C#3", "D 3", "D#3", "E 3", "F 3", "F#3", "G 3", "G#3", "A 3", "A#3", "B 3",
    "C 4", "C#4", "D 4", "D#4", "E 4", "F 4", "F#4", "G 4", "G#4", "A 4", "A#4", "B 4",
    "C 5", "C#5", "D 5", "D#5", "E 5", "F 5", "F#5", "G 5", "G#5", "A 5", "A#5", "B 5",
    "C 6", "C#6", "D 6", "D#6", "E 6", "F 6", "F#6", "G 6", "G#6", "A 6", "A#6", "B 6",
    "C 7", "C#7", "D 7", "D#7", "E 7", "F 7", "F#7", "G 7", "G#7", "A 7", "A#7", "B 7",
    "C 8", "C#8", "D 8", "D#8", "E 8", "F 8", "F#8", "G 8", "G#8", "A 8", "A#8", "B 8"
};

const float notefreq[120] =
{
    16.35f,   17.32f,   18.35f,   19.45f,    20.60f,    21.83f,    23.12f,    24.50f,    25.96f,    27.50f,    29.14f,    30.87f,
    32.70f,   34.65f,   36.71f,   38.89f,    41.20f,    43.65f,    46.25f,    49.00f,    51.91f,    55.00f,    58.27f,    61.74f,
    65.41f,   69.30f,   73.42f,   77.78f,    82.41f,    87.31f,    92.50f,    98.00f,   103.83f,   110.00f,   116.54f,   123.47f,
    130.81f,  138.59f,  146.83f,  155.56f,   164.81f,   174.61f,   185.00f,   196.00f,   207.65f,   220.00f,   233.08f,   246.94f,
    261.63f,  277.18f,  293.66f,  311.13f,   329.63f,   349.23f,   369.99f,   392.00f,   415.30f,   440.00f,   466.16f,   493.88f,
    523.25f,  554.37f,  587.33f,  622.25f,   659.26f,   698.46f,   739.99f,   783.99f,   830.61f,   880.00f,   932.33f,   987.77f,
    1046.50f, 1108.73f, 1174.66f, 1244.51f,  1318.51f,  1396.91f,  1479.98f,  1567.98f,  1661.22f,  1760.00f,  1864.66f,  1975.53f,
    2093.00f, 2217.46f, 2349.32f, 2489.02f,  2637.02f,  2793.83f,  2959.96f,  3135.96f,  3322.44f,  3520.00f,  3729.31f,  3951.07f,
    4186.01f, 4434.92f, 4698.64f, 4978.03f,  5274.04f,  5587.65f,  5919.91f,  6271.92f,  6644.87f,  7040.00f,  7458.62f,  7902.13f,
    8372.01f, 8869.84f, 9397.27f, 9956.06f, 10548.08f, 11175.30f, 11839.82f, 12543.85f, 13289.75f, 14080.00f, 14917.24f, 15804.26f
};
pitchEstimator::~pitchEstimator() {
    
    
    delete inputL; // clean up after yourself
    delete inputR;
}

void pitchEstimator::setup(){
    /* some standard setup stuff*/
    
    ofEnableAlphaBlending();
    ofSetupScreen();
    ofBackground(0, 0, 0);
    ofSetVerticalSync(true);
    
    sampleRate 			= 44100;
    initialBufferSize	= 512;
    
    inputL = new float[initialBufferSize];
    inputR = new float[initialBufferSize];
    
    fft.setup(16384, 1024, 512);
    octaveAnalyzer.setup(44100, 1024, 10);
    
    soundStream.setup(this, 2, 2, 44100, initialBufferSize, 4);
    estimatedPitch[0] = estimatedPitch[1] = estimatedPitch[2] = 0.f;
    
}

void pitchEstimator::update(){
    ofSetColor(255, 255, 255, 255);
    ofSetColor(255, 255, 255, 255);

}

void pitchEstimator::draw(){
    
    ofSetColor(255, 255, 255, 255);
    int i;
    for(i = 0; i < octaveAnalyzer.nAverages; i++) {
        ofRect(i * 11, ofGetHeight()/2 - (octaveAnalyzer.averages[i] * 4), 11, octaveAnalyzer.averages[i] * 8);
    }
    
}

void pitchEstimator::audioOut (float * output, int bufferSize, int nChannels){
//    
//    for (int i = 0; i < bufferSize; i++)
//    {
//        wave = sine.sinebuf4(abs(estimatedPitch[0])) + sine1.sinebuf4(abs(estimatedPitch[1])) + sine1.sinebuf4(abs(estimatedPitch[2]));
//        
//        mix.stereo(wave/3.f, outputs, 0.5);
//        
//        output[i*nChannels    ] = outputs[0];
//        output[i*nChannels + 1] = outputs[1];
//    }
    
}

void pitchEstimator::audioIn  (float * input, int bufferSize, int nChannels){
    
    double lIn, rIn;
    
    int i;
    for (i = 0; i < bufferSize; i++){
        
        lIn = input[i*2];
        if(fft.process(lIn)) {
            fft.magsToDB();
            octaveAnalyzer.calculate(fft.magnitudesDB);
        }
        
        rIn = input[i*2 + 1];
        if(fft.process(rIn)) {
            fft.magsToDB();
            octaveAnalyzer.calculate(fft.magnitudesDB);
        }
        
    }
    
    bin_number = bin_number1 = bin_number2 = 0;
    largests[0] = largests[1] = largests[2] = 0.f;
    for (i = 0; i < fft.bins; i++) {
        if(abs(fft.magnitudesDB[i]) > largests[0]) {
            
            largests[2] = largests[1];
            largests[1] = largests[0];
            largests[0] = abs(fft.magnitudesDB[i]);
            //cout<< "largest number " + ofToString(largests[0]) << endl;
            
            bin_number2 = bin_number1;
            bin_number1 = bin_number;
            bin_number = i;

            
        }
    }
    
    if(largests[0] > 12.0)
        estimatedPitch[0] = ( (float) bin_number / fft.bins) * (sampleRate * 0.5);
    else
        estimatedPitch[0] = 0.f;
    
    if(largests[1] > 12.0)
        estimatedPitch[1] = ( (float) bin_number1 / fft.bins) * (sampleRate * 0.5);
    else
        estimatedPitch[1] = 0.f;
    
    if(largests[2] > 12.0)
        estimatedPitch[2] = ( (float) bin_number2 / fft.bins) * (sampleRate * 0.5);
    else
        estimatedPitch[2] = 0.f;
    
   // cout << bin_number << " " << estimatedPitch[0] << " " << octaveAnalyzer.spectrumFrequencySpan << endl;
    
  
    for(int i=0; i< 120; i++)
    {
        if((estimatedPitch[0] >= notefreq[i]) && (estimatedPitch[0] <= notefreq[i+1]))
        {
          //  cout << "note found " << note[i] << endl;
            loudestFrequency = notefreq[i];
            loudestNote = note[i];
        }
    }
    

}
