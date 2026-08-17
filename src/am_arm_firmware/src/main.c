#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "print_rtf.h"

// Define FreeRTOS continuous execution loop timing frequencies
#define MOTOR_CONTROL_TICK_RATE_MS pdMS_TO_TICKS(1)  // Deterministic 1kHz execution
#define TELEMETRY_TICK_RATE_MS     pdMS_TO_TICKS(100) // 10Hz log tracking iteration

// Global mock state representing mechanical joint angles
volatile float joint_encoder_positions[6] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

void vMotorControlTask(void *pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();
    print_rtf_system_status("MOTOR_CORE", "Deterministic 1kHz closed-loop position engine online.", 0);

    for (;;) {
        // Hard Real-Time Constraint Zone: process position corrections
        for (int i = 0; i < 6; ++i) {
            // Read target trajectory command registers, calculate PID, write to PWM lines
            joint_encoder_positions[i] += 0.001f; 
        }

        // Delay task until precisely 1 millisecond has passed from the previous wake time
        vTaskDelayUntil(&xLastWakeTime, MOTOR_CONTROL_TICK_RATE_MS);
    }
}

void vTelemetryLoggingTask(void *pvParameters) {
    for (;;) {
        char status_buffer[64];
        snprintf(status_buffer, sizeof(status_buffer), "Axis 1 Position: %.3f rad | Filament Extruder Nominal.", joint_encoder_positions[0]);
        
        // Print structured logs using the RTF library definitions
        print_rtf_system_status("TELEMETRY", status_buffer, 0);

        vTaskDelay(TELEMETRY_TICK_RATE_MS);
    }
}

int main(void) {
    // 1. Initialize bare-metal hardware clocks, timers, and communication buses (UART/SPI)
    
    // 2. Instantiate FreeRTOS deterministic task channels
    xTaskCreate(vMotorControlTask, "MotorControl", 256, NULL, 3, NULL); // Highest priority
    xTaskCreate(vTelemetryLoggingTask, "Telemetry", 256, NULL, 1, NULL);   // Lower priority

    // 3. Hand control over to the real-time scheduler
    print_rtf_system_status("KERNEL", "Starting FreeRTOS deterministic kernel scheduler...", 0);
    vTaskStartScheduler();

    // The program execution path only hits this line if there is insufficient RAM to boot the kernel
    print_rtf_system_status("KERNEL", "Critical Kernel allocation failure detected!", 2);
    for (;;);
    return 0;
}
