#include "Synaptics.h"

Synaptics *device = nullptr;

void print_data(bool data_packet=false) {
  Serial.print(device->data[0], HEX);
  Serial.print(" ");
  Serial.print(device->data[1], HEX);
  Serial.print(" ");
  Serial.print(device->data[2], HEX);
  Serial.print(" ");
  if (!data_packet) return;
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
  device->set_mode(0x81);
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
  print_data();
  Serial.print("getZ: ");
  Serial.print(device->getZ());
  Serial.print(", ");
  
  Serial.print("getW: ");
  Serial.print(device->getW());
  Serial.print(", ");
  
  Serial.print("getX: ");
  Serial.print(device->getX());
  Serial.print(", ");
  
  Serial.print("getY: ");
  Serial.print(device->getY());
  Serial.println();
  delay(20);
}
