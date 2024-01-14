#include <FreeRTOS.h>
#include <task.h>

#include "main.hpp"

#define ENCODER_UPDATE_TASK_PRIORITY 10
#define ENCODER_UPDATE_TASK_STACK_SIZE 128

#include "Encoder/IEncoder.hpp"
#if USE_LS7366R_ENCODER
    #include "Encoder/Driver/LS7366R.hpp"
    LS7366R* myEncoder;
#else
    #error "No encoder driver selected in platformio.ini!"
#endif

TaskHandle_t encoderUpdateTaskHandle;

int main() {
    #if USE_LS7366R_ENCODER
        myEncoder = new LS7366R();
    #endif

    xTaskCreate(
        UpdateEncoderTask, 
        "Encoder Update Task", 
        ENCODER_UPDATE_TASK_STACK_SIZE, 
        myEncoder, 
        ENCODER_UPDATE_TASK_PRIORITY, 
        &encoderUpdateTaskHandle);

    vTaskStartScheduler();

    for (;;);
}

void UpdateEncoderTask(void* param) {
    Encoder* encoder = static_cast<Encoder*>(param);
    for (;;) {
        encoder->Update();
        vTaskDelay(1*portTICK_PERIOD_MS);
    }
}

/*
 * Handler in case our application overflows the stack
 */
void vApplicationStackOverflowHook(
    TaskHandle_t xTask __attribute__((unused)),
    char *pcTaskName __attribute__((unused))) 
{
    for (;;);
}