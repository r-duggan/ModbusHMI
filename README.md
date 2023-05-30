# ModbusHMI
For use with P1AM-100 to C-More HMI

## Example

``` c++
#include <P1AM.h>
#include <Ethernet.h>
#include <ArduinoModbus.h>
#include <ArduinoRS485.h>
#include "ModbusHMI.h"

// Ethernet Communication Setup
byte mac[] = {0x60, 0x52, 0xD0, 0x07, 0x40, 0xD7};
IPAddress ip(192, 168, 1, 1);
EthernetServer server(502);
EthernetClient clients[8];
int client_cnt;

ModbusHMI hmi(0x00, 32, 32, 32, 32);

void setup() {

    Serial.begin(115200); // Initialize serial communication
    while (!P1.init()) { 
        } // Wait for modules to connect

    // Initialize all outputs to OFF on startup
    P1.writeDiscrete(0x0000, 2); 

    Ethernet.begin(mac, ip);    // Start Ethernet Connection
    server.begin();

    hmi.StartServer();
    hmi.Configure();

}

void loop() {

    //Checks for ethernet clients
    EthernetClient newClient = server.accept();
    if(newClient){
        for(byte i = 0; i < 8; i++){
            if(!clients[i]){
                clients[i] = newClient;
                client_cnt++;
                Serial.print("Client Accept: ");
                Serial.print(newClient.remoteIP());
                Serial.print(", Total: ");
                Serial.println(client_cnt);
                break;
            }
        }
    }

    //If there are packets available, receive them and process them.
    for (byte i = 0; i < 8; i++){
        if (clients[i].available()){ //if data is available
            hmi.server.accept(clients[i]);
            hmi.server.poll();
        }
    }

    hmi.UpdateInputs();
    hmi.UpdateInputRegisters();
    hmi.UpdateCoils();
    hmi.UpdateHoldingRegisters();
}
```
