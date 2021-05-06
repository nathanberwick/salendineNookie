#include <SimpleTimer.h>


//SYSTEM VARIABLES
SimpleTimer timer;
bool pedalState = false;
bool buttonState = false;
bool switchState = false;
bool timerFlag = false;
int switchPin = 8;
int relayPin = 9;
int timerID;

//USER VARIABLES
int msHold = 500; //when button held for over this value, then switch is momentary

void setup() {
    pinMode(relayPin, OUTPUT);
    pinMode(switchPin, INPUT);
    timerID = timer.setInterval(msHold, setTimerFlag);
}

void pedalChange() {
    pedalState = !pedalState;
    digitalWrite(relayPin, pedalState);
    delay(10); //necessary as a "just in case" for hardware.
}

void loop() {
    timer.run();
    buttonState = digitalRead(switchPin);
    if (buttonState == HIGH && switchState == false) {
        switchState = true;
        timer.restartTimer(timerID);
        timerFlag = false;
        timerID = timer.setTimeout(msHold, setTimerFlag);
        pedalChange();
    } else if (buttonState == LOW && switchState == true) {
        timer.disable(timerID);
        switchState = false;
        if (timerFlag == true) {
            pedalChange();
        }
    }
}

void setTimerFlag() {
    timerFlag = true;
}
