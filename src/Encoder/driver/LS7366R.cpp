#include "Encoder/driver/LS7366R.hpp"
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/spi.h>
#include <cstdint>
#include <cstddef>

LS7366R::LS7366R() : Encoder::Encoder(),
    myStatus{false, false, false, false, false, false, false, false} {
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

uint32_t LS7366R::GetPosition() {
    //TODO: this is naive, check for overflow and all that good stuff
    return myCount;
}

// uint16_t LS7366R::GetCountPeriod() {
//     //TODO calculate time between counts average over the number of counts.
//     //probably needs a timer to store when the update got the count from the encoder,
//     //and compare the number of counts in that interval vs the number of counts in the last interval
//     //This should go through a unit testable function in the base, probably.
//     return 0;
// }

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

void LS7366R::PrivUpdateCount() {
    StartCS(); // Initiate SPI transaction

    spi_send(SPI1, LOAD_OTR); // Send the read CNTR command
    while (!(SPI_SR(SPI1) & SPI_SR_TXE)); // Wait for transmit buffer to empty

    // Send the read CNTR command
    spi_send(SPI1, READ_OTR);

    // Read 4 bytes from CNTR register
    uint32_t count = 0;
    for (int i = 0; i < 4; i++) {
        spi_send(SPI1, 0x00); // Send dummy byte
        while (!(SPI_SR(SPI1) & SPI_SR_RXNE)); // Wait for receive buffer to fill
        count = (count << 8) | spi_read(SPI1); // Shift and append received byte
    }

    EndCS(); // End SPI transaction

    myLastCount = myCount; // Store the previous value for the next mathmania
    myLastCountUpdateTime = myCountUpdateTime;

    myCount = count; // Store the read value
    myCountUpdateTime = 0;//TODO SYSTICK OR SOMETHING, and manage timer overflow();
}

void LS7366R::PrivUpdateStatus() {
    StartCS(); // Initiate SPI transaction

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
    myStatus.carry = status & 0x01;
    myStatus.borrow = status & 0x02;
    myStatus.compare = status & 0x04;
    myStatus.idx = status & 0x08;
    myStatus.counterEnable = status & 0x10;
    myStatus.powerLoss = status & 0x20;
    myStatus.direction = status & 0x40;
    myStatus.sign = status & 0x80;
}
    