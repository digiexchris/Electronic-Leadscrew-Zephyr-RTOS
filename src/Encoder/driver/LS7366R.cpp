#include "Encoder/driver/LS7366R.hpp"
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/spi.h>
#include <cstdint>
#include <cstddef>

LS7366R::LS7366R() : Encoder::Encoder(),
    myState{false, false, false, false, false, false, false, false} {
}

void LS7366R::Init() {

    // Enable clocks for GPIOA and SPI1
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_GPIOB);
    rcc_periph_clock_enable(RCC_SPI1);

    // SPI GPIOs
    gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_50_MHZ,
                  GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, 
                  GPIO5 | GPIO7); // SCK, MOSI
    gpio_set_mode(GPIOA, GPIO_MODE_INPUT,
                  GPIO_CNF_INPUT_FLOAT, 
                  GPIO6); // MISO

    // CS Pin
    gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_50_MHZ,
                  GPIO_CNF_OUTPUT_PUSHPULL, 
                  GPIO4);
    gpio_set(GPIOA, GPIO4); // Set CS high

    spi_init_master(SPI1, SPI_CR1_BAUDRATE_FPCLK_DIV_64,
                    SPI_CR1_CPOL_CLK_TO_0_WHEN_IDLE, 
                    SPI_CR1_CPHA_CLK_TRANSITION_1, 
                    SPI_CR1_DFF_8BIT, SPI_CR1_MSBFIRST);

    spi_enable(SPI1);


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
    // Initiate SPI communication
    StartCS();

    // Send opcode
    spi_send(SPI1, opCode);
    while (!(SPI_SR(SPI1) & SPI_SR_TXE)); // Wait for transmit buffer to empty

    if(data != nullptr){
        // Send data
        spi_send(SPI1, *data);
        while (!(SPI_SR(SPI1) & SPI_SR_TXE)); // Wait for transmit buffer to empty
    }

    EndCS();
}

void LS7366R::Update() {
    StartCS(); // Initiate SPI transaction

    /////////////// Buffer CNTR in OTR ///////////////

    spi_send(SPI1, LOAD_OTR); // Send the read CNTR command
    while (!(SPI_SR(SPI1) & SPI_SR_TXE)); // Wait for transmit buffer to empty

    //it's more important that the current timestamp matches the current count for the position loop
    //so set it as soon as the LOAD_OTR is done
    uint16_t timestamp = 0;//TODO SYSTICK OR SOMETHING, and manage timer overflow();

    ///////////// Read CNTR /////////////

    // Send the read CNTR command
    spi_send(SPI1, READ_OTR);

    // Read 4 bytes from CNTR register
    uint32_t count = 0;
    for (int i = 0; i < 4; i++) {
        spi_send(SPI1, 0x00); // Send dummy byte
        while (!(SPI_SR(SPI1) & SPI_SR_RXNE)); // Wait for receive buffer to fill
        count = (count << 8) | spi_read(SPI1); // Shift and append received byte
    }

    ///////////// Read STR /////////////

    // Send the read STR command
    spi_send(SPI1, READ_STR);
    while (!(SPI_SR(SPI1) & SPI_SR_TXE)); // Wait for transmit buffer to empty

    // Read 1 byte from STR register
    uint8_t status = 0;
    spi_send(SPI1, 0x00); // Send dummy byte
    while (!(SPI_SR(SPI1) & SPI_SR_RXNE)); // Wait for receive buffer to fill
    status = spi_read(SPI1); // Read received byte

    EndCS(); // End SPI transaction

    // Extract the status bits
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
    