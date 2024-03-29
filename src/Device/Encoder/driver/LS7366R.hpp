// #pragma once
// #include "Device/Encoder/IEncoder.hpp"
// #include "LR7366R-constants.hpp"
// #include <zephyr/device.h>
// #include <zephyr/drivers/gpio.h>
// #include <zephyr/drivers/spi.h>
// #include <zephyr/kernel.h>
// #include <zephyr/sys/printk.h>

// namespace Device::Encoder {

// class LS7366R : public Encoder {
// public:
//   struct State {
//     bool carry;  // counter overflow
//     bool borrow; // counter underflow
//     bool compare;
//     bool idx;
//     bool counterEnable; // 0 is disabled, 1 is enabled
//     bool powerLoss;
//     bool direction; // 0 is count down, 1 is count up
//     bool sign;      // 0 is positive, 1 is negative
//   };
// `
//   LS7366R();
//   void Init();
//   void UpdateMotionParams() override;

// private:
//   void PrivWrite(const uint8_t opCode, const uint8_t *data);
//   void StartCS();
//   void EndCS();
//   State myState;

//   const device *spiDev; // the SPI used for the encoder
//   spi_cs_control spiCS;
//   spi_config spiCFG;
// };

// } //