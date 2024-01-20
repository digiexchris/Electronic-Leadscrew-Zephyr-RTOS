#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/device.h>
#include <zephyr/drivers/spi.h>
#include <stdint.h>
#include <stddef.h>

#include "Encoder/driver/LS7366R.hpp"

LS7366R::LS7366R() : Encoder::Encoder(),
    myState{false, false, false, false, false, false, false, false} {
}

void LS7366R::Init() {

    spiDev = device_get_binding("SPI_1");
    if (!spiDev) {
        //throw a fatal error   printk("SPI device not found\n");
        return;
    }

    spiCS.gpio_dev = device_get_binding("GPIO_0");

    if (!spiCS.gpio_dev) {
        //todo throw a fatal error  printk("GPIO device not found\n");
        return;
    }

    spiCS.gpio_pin = 4;
    spiCS.delay = 0;
    spiCS.gpio_dt_flags = GPIO_ACTIVE_LOW;

    spiCFG.frequency = 1000000;
    spiCFG.operation = SPI_OP_MODE_MASTER | SPI_WORD_SET(8) | SPI_TRANSFER_MSB | SPI_MODE_CPOL | SPI_MODE_CPHA;
    spiCFG.slave = 0;
    spiCFG.cs = &spiCS;
    
    //Configure and reset the LS7366R
    // cppcheck-suppress knownConditionTrueFalse 
    // cppcheck-suppress badBitmaskCheck
    const uint8_t MDR0Options = QUADRX4|SYNCH_INDX|FILTER_2|FREE_RUN;
    PrivWrite(WRITE_MDR0, &MDR0Options);

    // cppcheck-suppress knownConditionTrueFalse 
    // cppcheck-suppress badBitmaskCheck
    const uint8_t MDR1Options = IDX_FLAG|CY_FLAG|BW_FLAG|BYTE_4|EN_CNTR;
    PrivWrite(WRITE_MDR1, &MDR1Options);

    //reset it to zero (center of the signed 32 bit int range)
    PrivWrite(CLR_CNTR, nullptr);
}

void LS7366R::StartCS() {
    gpio_clear(GPIOA, GPIO4); // Set CS low
}

void LS7366R::EndCS() {
    gpio_set(GPIOA, GPIO4); // Set CS high
}

void LS7366R::PrivWrite(uint8_t opCode, const uint8_t* data) {

    struct spi_buf tx_buf[2];
    struct spi_buf_set tx_bufs;

    tx_buf[0].buf = &opCode;
    tx_buf[0].len = 1;

    tx_bufs.buffers = tx_buf;
    tx_bufs.count = (data != nullptr) ? 2 : 1;

    if (data != nullptr) {
        tx_buf[1].buf = (void *)data;
        tx_buf[1].len = 1;
    }

    spi_write(spiDev, &spiCFG, &tx_bufs);
}

void LS7366R::Update() {
    uint8_t cmd;
    uint8_t buffer[4];
    struct spi_buf tx_buf;
    struct spi_buf rx_buf;
    struct spi_buf_set tx_bufs;
    struct spi_buf_set rx_bufs;

    // Load CNTR to OTR
    cmd = LOAD_OTR;
    tx_buf.buf = &cmd;
    tx_buf.len = 1;
    tx_bufs.buffers = &tx_buf;
    tx_bufs.count = 1;

    spi_write(spi_dev, &spi_cfg, &tx_bufs);

    //it's more important that the current timestamp matches the current count for the position loop
    //so set it as soon as the LOAD_OTR is done
    uint16_t timestamp = 0;//TODO SYSTICK OR SOMETHING, and manage timer overflow();

    ///////////// Read CNTR (now in OTR) /////////////

    cmd = READ_OTR;
    tx_buf.buf = &cmd;
    tx_buf.len = 1;
    rx_buf.buf = buffer;
    rx_buf.len = 4;
    rx_bufs.buffers = &rx_buf;
    rx_bufs.count = 1;

    spi_transceive(spi_dev, &spi_cfg, &tx_bufs, &rx_bufs);

    // Convert buffer to uint32_t count
    uint32_t count = (buffer[0] << 24) | (buffer[1] << 16) | (buffer[2] << 8) | buffer[3];

    ///////////// Read STR /////////////
    cmd = READ_STR;
    tx_buf.buf = &cmd;
    tx_buf.len = 1;
    rx_buf.buf = &buffer[0];
    rx_buf.len = 1;

    spi_transceive(spi_dev, &spi_cfg, &tx_bufs, &rx_bufs);

    uint8_t status = buffer[0];

    // Extract status bits
    myState.carry = status & 0x01;
    myState.borrow = status & 0x02;
    myState.compare = status & 0x04;
    myState.idx = status & 0x08;
    myState.counterEnable = status & 0x10;
    myState.powerLoss = status & 0x20;
    myState.direction = status & 0x40;
    myState.sign = status & 0x80;


    /////////////// Store results ///////////////

    //atomically swap the stuff out so that the time matches the count in all other threads
    Status s = myStatus.load();
    s.lastCount = s.count; // Store the previous value
    s.lastTimestamp = s.timestamp;
    s.lastDirection = s.direction;
    //todo handle speed
    s.count = count; // Store the read value
    s.timestamp = timestamp;
    s.direction = myState.direction;
    //todo handle speed
    myStatus.exchange(s);
}
    