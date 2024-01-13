#pragma once
#include "../IEncoder.hpp"
#include "LR7366R-constants.hpp"

class LS7366R : public Encoder {
    public:
        struct Status {
           bool carry; //counter overflow
           bool borrow; //counter underflow
           bool compare;
           bool idx;
           bool counterEnable; //0 is disabled, 1 is enabled
           bool powerLoss;
           bool direction; //0 is count down, 1 is count up
           bool sign; //0 is positive, 1 is negative
        };

        LS7366R();
        void Init();
        uint32_t GetPosition() override;
        void Update() override;
    private:
        void PrivWrite(const uint8_t opCode, const uint8_t* data);
        void PrivUpdateCount();
        void PrivUpdateStatus();
        
        void StartCS();
        void EndCS();
        Status myStatus;

};