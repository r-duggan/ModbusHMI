/*
 * HMI Class
 * Contains data and controls for modbus HMI
 */

#ifndef MODBUSHMI_H
#define MODBUSHMI_H

#include <Ethernet.h>
#include <ArduinoModbus.h>
#include <ArduinoRS485.h>

using namespace std;

class ModbusHMI {
    private:
        int startAddress; 

        int numCoils;
        int numDiscreteInputs;
        int numHoldingRegisters;
        int numInputRegisters;

    public:

        bool* c;
        bool* di;
        int* hr;
        int* ir;

        ModbusTCPServer server;

        // SETTERS //
        void SetStartAddress(int);

        void SetNumCoils(int);
        void SetNumDiscreteInputs(int);
        void SetNumHoldingRegisters(int);
        void SetNumInputRegisters(int);

        // CONSTRUCTOR //
        ModbusHMI();
        ModbusHMI(int, int, int, int, int);
        ~ModbusHMI();

        // FUNCTIONS //
        void StartServer();
        void Configure();
        void UpdateCoils();
        void UpdateInputs();
        void UpdateHoldingRegisters();
        void UpdateInputRegisters();

};

#endif
