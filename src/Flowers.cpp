//
//  Flowers.cpp
//  http_example
//
//  Created by Phoenix Perry on 24/05/15.
//
//

#include "Flowers.h"
#define NUMBER_OF_KEYS 10

Flowers::Flowers(SerialReader *serial_, OscData *oscData_,ofBaseApp *app){
    serial = serial_;
    oscData = oscData_;

    soundStream.setup(app, 2, 0, 41000, 256, 4);
    ControlGenerator midiNote = synth.addParameter("midiNumber");
    ControlGenerator noteFreq = ControlMidiToFreq().input(midiNote);
    Generator tone = SawtoothWave().freq(noteFreq);
    
    tone = LPF12().input(tone).Q(2).cutoff((noteFreq*2) +SineWave().freq(3)*0.5*noteFreq);
    // It's just a steady tone until we modulate the amplitude with an envelope
    ControlGenerator envelopeTrigger = synth.addParameter("trigger");
    
    Generator toneWithEnvelope = tone * ADSR().attack(0.01).decay(1.5).sustain(0).release(0).trigger(envelopeTrigger).legato(true);
    // let's send the tone through some delay
    Generator toneWithDelay = StereoDelay(0.5,.7).input(toneWithEnvelope).wetLevel(0.1).feedback(0.2);
    synth.setOutputGen(toneWithDelay);
}

void Flowers::trigger(){
    static int twoOctavePentatonicScale[10] = {0, 2, 4, 7, 9, 12, 14, 16, 19, 21};
    
    int degreeToTrigger = floor(ofClamp(scaleDegree, 0, 9));
    
    // set a parameter that we created when we defined the synth
    synth.setParameter("midiNumber", 44 + twoOctavePentatonicScale[degreeToTrigger]);
    
    // simply setting the value of a parameter causes that parameter to send a "trigger" message to any
    // using them as triggers
    synth.setParameter("trigger", 1);
}
void Flowers::audioRequested (float * output, int bufferSize, int nChannels){
    synth.fillBufferOfFloats(output, bufferSize, nChannels);
}

void Flowers::update(){
    int num1 = serial->pad12;
    int num2 = serial->pad13;
    int num3 = serial->pad14;
    int average = num1 + num2 + num3/3;
    average = ofMap(average, 0, 420, 0, 1023);
    trigger();
    
    int newScaleDegree = average * NUMBER_OF_KEYS / ofGetWindowWidth();
    if(ofGetMousePressed() && ( newScaleDegree != scaleDegree )){
        scaleDegree = newScaleDegree;
        trigger();
    }else{
        scaleDegree = newScaleDegree;
    }

}
