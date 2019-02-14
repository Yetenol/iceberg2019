#include "Orientation.h"

/*********************************************************************
  Constructor
*********************************************************************/
Orientation::Orientation() : Adafruit_BNO055(55) {
    setCooldown(100);
}

void Orientation::init() {
  if (!begin()) debug("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
}

void Orientation::update() {
  sensors_event_t event;
  getEvent(&event);
  io.xOrientation.set(event.orientation.x);
  io.yOrientation.set(event.orientation.y);
  io.zOrientation.set(event.orientation.z);
}

Orientation orientation;