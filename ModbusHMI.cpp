#include "ModbusHMI.h"

// CONSTRUCTORS //
ModbusHMI::ModbusHMI() {
    startAddress = 0x00;
    numCoils = 16;
    numDiscreteInputs = 16;
    numHoldingRegisters = 16;
    numInputRegisters = 16;
    
    c = new bool[16];
    for (int i = 0; i < 16; i++) {
        c[i] = 0;
    }

    // Create discrete input array and 0
    di = new bool[16];
    for (int i = 0; i < 16; i++) {
        di[i] = 0;
    }

    // Create holding register array and 0
    hr = new int[16];
    for (int i = 0; i < 16; i++) {
        hr[i] = 0;
    }

    // Create input register array and 0
    ir = new int[16];
    for (int i = 0; i < 16; i++) {
        ir[i] = 0;
    }
}

ModbusHMI::ModbusHMI(int startAddress, int coils, int inputs, int holdingRegister,
                     int inputRegister) {
    this->startAddress = startAddress;
    this->numCoils = coils;
    this->numDiscreteInputs = inputs;
    this->numHoldingRegisters = holdingRegister;
    this->numInputRegisters = inputRegister;

    // Create coil array and 0
    c = new bool[coils];
    for (int i = 0; i < coils; i++) {
        c[i] = 0;
    }

    // Create discrete input array and 0
    di = new bool[inputs];
    for (int i = 0; i < inputs; i++) {
        di[i] = 0;
    }

    // Create holding register array and 0
    hr = new int[holdingRegister];
    for (int i = 0; i < holdingRegister; i++) {
        hr[i] = 0;
    }

    // Create input register array and 0
    ir = new int[inputRegister];
    for (int i = 0; i < inputRegister; i++) {
        ir[i] = 0;
    }

}

ModbusHMI::~ModbusHMI() {
    delete[] c;
    delete[] di;
    delete[] hr;
    delete[] ir;
}

// SETTERS //
void ModbusHMI::SetStartAddress(int address) {
    startAddress = address;
}

void ModbusHMI::SetNumCoils(int coils) {
    numCoils = coils;
    delete[] c;
    c = new bool[coils];
    for (int i = 0; i < coils; i++) {
        c[i] = 0;
    }
}

void ModbusHMI::SetNumDiscreteInputs(int inputs) {
    numDiscreteInputs = inputs;
    delete[] di;
    di = new bool[inputs];
    for (int i = 0; i < inputs; i++) {
        di[i] = 0;
    }
}

void ModbusHMI::SetNumHoldingRegisters(int registers) {
    numHoldingRegisters = registers;
    delete[] hr;
    hr = new int[registers];
    for (int i = 0; i < registers; i++) {
        hr[i] = 0;
    }
}

void ModbusHMI::SetNumInputRegisters(int registers) {
    numInputRegisters = registers;
    delete[] ir;
    ir = new int[registers];
    for (int i = 0; i < registers; i++) {
        ir[i] = 0;
    }
}

// FUNCTIONS //
void ModbusHMI::StartServer() {
    Serial.println("Starting Server...");
    while(!server.begin()){
        Serial.println("Failed to start Modbus TCP Server!");
        while(1);
    }
    Serial.println("Server started succesfully");
}

void ModbusHMI::Configure() {
    Serial.println("Configuring I/O...");
    server.configureCoils(startAddress, numCoils);
    server.configureDiscreteInputs(startAddress, numDiscreteInputs);
    server.configureHoldingRegisters(startAddress, numHoldingRegisters);
    server.configureInputRegisters(startAddress, numInputRegisters);
    Serial.println("I/O Configured");
}

void ModbusHMI::UpdateCoils(){//Read the Coil bits from the Modbus Library
    for(int i = 0; i < numCoils; i++){
        c[i] = server.coilRead(i);
    }
}

void ModbusHMI::UpdateInputs(){ //Write the Input bits to the Modbus Library
    for(int i = 0; i < numDiscreteInputs; i++){
        server.discreteInputWrite(i,di[i]);
    }
}

void ModbusHMI::UpdateHoldingRegisters(){ //Read the Holding Register words from the Modbus Library
    for(int i = 0; i < numHoldingRegisters; i++){
        hr[i] = server.holdingRegisterRead(i);
    }
}

void ModbusHMI::UpdateInputRegisters(){ //Write the Input Registers to the Modbus Library
    for(int i = 0; i < numInputRegisters; i++){
        server.inputRegisterWrite(i,ir[i]);
    }
}
