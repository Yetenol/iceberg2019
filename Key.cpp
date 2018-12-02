#include "Key.h"

Key::Key(int8_t _pin) {
    pin = _pin;
}
Key::Key(int8_t _pin, uint32_t _preDelay) {
    pin = _pin;
    preDelay = _preDelay;
}
Key::Key(int8_t _pin, uint32_t _preDelay, uint32_t _postDelay) {
    pin = _pin;
    preDelay = _preDelay;
    postDelay = _postDelay;
}
Key::Key(int8_t _pin, uint32_t _preDelay, uint32_t _postDelay, uint32_t _repititionDelay) {
    pin = _pin;
    preDelay = _preDelay;
    postDelay = _postDelay;
    repititionDelay = _repititionDelay;
}

bool Key::stroke() {
    return active && clicks == 1;
}
bool Key::permanent() {
    return active && clicks > 1;
}
bool Key::click() {
    return active;
}

void Key::update() {
    if(digitalRead(pin)) {
        // Knopf ist losgelassen
        cooldownTimer = 0;
        clicks = 0;
    } else {
        // Knopf wird gedrückt
        if (cooldownTimer == 0) cooldown(preDelay); // Erstmaliges Drücken
        if (millis() >= cooldownTimer) {
            // Nächster Klick
            clicks++;
            active = true;
            if(clicks == 1) cooldown(postDelay);
            else cooldown(repititionDelay);
        } else active = false; // Warte auf nächsten Klick
    }
}

void Key::cooldown(uint32_t delay) {
    if(delay + 1 == 0) cooldownTimer = -1;
    else cooldownTimer = millis() + delay;
}