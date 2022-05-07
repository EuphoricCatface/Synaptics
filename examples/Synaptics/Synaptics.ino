#include "Synaptics.h"

Synaptics *device = nullptr;

void print_data(bool data_packet=false) {
  Serial.print(device->data[0], HEX);
  Serial.print(" ");
  Serial.print(device->data[1], HEX);
  Serial.print(" ");
  Serial.print(device->data[2], HEX);
  Serial.print(" ");
  if (!data_packet) {
    Serial.println();
    return;
  }
  Serial.print(device->data[3], HEX);
  Serial.print(" ");
  Serial.print(device->data[4], HEX);
  Serial.print(" ");
  Serial.println(device->data[5], HEX);
}

void setup(void) {
  Serial.begin(115200);
  device = new Synaptics(3, 2);
  Serial.println("Init done!");
  // device->set_mode(0x00); // Relative mode
  // device->set_mode(0x80); // "Old" absolute mode
  device->set_mode(0x81); // "New" absolute mode
  Serial.print("read_modes: "); // this is done inside the c-tor
  print_data();
  Serial.print("identify: ");
  device->identify();
  print_data();
  Serial.print("read_capabilities: ");
  device->read_capabilities();
  print_data();
  Serial.print("read_ext_cap: ");
  device->read_ext_cap();
  print_data();
  Serial.print("read_ext_cap_0c: ");
  device->read_ext_cap_0c();
  print_data();
  Serial.print("read_modelid: ");
  device->read_modelid();
  print_data();
  Serial.println("sleep for 5 secs...");
  delay(5000);
  device->enable();
}

void loop(){
  device->read_data();
  int x, y;
  uint8_t z, w;
  bool r, l, m;
  x = device->getX(); y = device->getY(); z = device->getZ(); w = device->getW();
  r = device->rightClicked(); l = device->leftClicked(); m = device-> middleClicked();
  if (!(x | y | z | w) && !(r | l | m))
    return;
  print_data(true);
  Serial.print("getZ: ");
  Serial.print(z);
  Serial.print(", ");
  
  Serial.print("getW: ");
  Serial.print(w);
  Serial.print(", ");
  
  Serial.print("getX: ");
  Serial.print(x);
  Serial.print(", ");
  
  Serial.print("getY: ");
  Serial.print(y);
  Serial.println();

  Serial.print("left: ");
  Serial.print(l);
  Serial.print(", ");

  Serial.print("right: ");
  Serial.print(r);
  Serial.print(", ");

  Serial.print("middle: ");
  Serial.print(m);
  Serial.println();
  delay(20);
}
