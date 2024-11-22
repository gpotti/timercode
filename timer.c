/**
 * @file timer.c
 * @brief Timer API for an embedded system.
 * 
 * This file implements a timer module with the following functionality:
 * - Initialize a timer.
 * - Set a timer with a specific duration.
 * - Decrement the timer value periodically.
 * - Trigger an interrupt when the timer reaches zero.
 * - Reset the timer to its initial state.
 * 
 * ## Overview
 * This timer API simulates the behavior of a hardware timer. It allows
 * users to configure a timer, track its countdown, and handle interrupts
 * when the countdown is complete.
 */

#include <stdio.h>
#include <stdbool.h>

/// Maximum timer duration
#define MAX_DURATION 255

/**
 * @struct Timer
 * @brief Represents the state of a timer.
 */
typedef struct {
    int value;          /**< Current value of the timer (0 to MAX_DURATION). */
    bool enabled;       /**< Indicates whether the timer is active. */
    bool interrupt_flag; /**< Indicates whether the timer has triggered an interrupt. */
} Timer;

/**
 * @brief Initializes the timer to its default state.
 * 
 * @param timer Pointer to the Timer object to initialize.
 */
void initTimer(Timer* timer) {
    timer->value = 0;
    timer->enabled = false;
    timer->interrupt_flag = false;
}

/**
 * @brief Sets the timer with a specific duration and enables it.
 * 
 * @param timer Pointer to the Timer object to modify.
 * @param duration Duration to set (1 to MAX_DURATION).
 * @return true if the timer was successfully set, false otherwise.
 * @note The duration must be within the range 1 to MAX_DURATION.
 */
bool setTimer(Timer* timer, int duration) {
    if (duration > 0 && duration <= MAX_DURATION) {
        timer->value = duration;
        timer->enabled = true;
        timer->interrupt_flag = false;
        return true;
    }
    return false;
}

/**
 * @brief Decrements the timer value by 1 if it is enabled and greater than 0.
 * 
 * @param timer Pointer to the Timer object to modify.
 * @return true if the timer value was decremented, false otherwise.
 */
bool decrementTimer(Timer* timer) {
    if (timer->enabled && timer->value > 0) {
        timer->value--;
        return true;
    }
    return false;
}

/**
 * @brief Checks and triggers an interrupt if the timer reaches zero.
 * 
 * @param timer Pointer to the Timer object to check.
 * @return true if an interrupt was triggered, false otherwise.
 */
bool triggerInterrupt(Timer* timer) {
    if (timer->enabled && timer->value == 0) {
        timer->interrupt_flag = true;
        timer->enabled = false;
        return true;
    }
    return false;
}

/**
 * @brief Resets the timer to its default state.
 * 
 * @param timer Pointer to the Timer object to reset.
 */
void resetTimer(Timer* timer) {
    timer->value = 0;
    timer->enabled = false;
    timer->interrupt_flag = false;
}

/**
 * @brief Demonstrates the timer functionality.
 * 
 * @note This is an example usage of the Timer API.
 */
int main() {
    Timer myTimer;
    initTimer(&myTimer);

    printf("Initializing Timer...\n");

    if (setTimer(&myTimer, 5)) {
        printf("Timer set to 5.\n");
    } else {
        printf("Failed to set timer.\n");
    }

    while (myTimer.enabled) {
        if (decrementTimer(&myTimer)) {
            printf("Timer decremented: %d\n", myTimer.value);
        }

        if (triggerInterrupt(&myTimer)) {
            printf("Interrupt triggered!\n");
        }
    }

    printf("Resetting Timer...\n");
    resetTimer(&myTimer);

    printf("Timer reset. Enabled: %d, Value: %d, Interrupt: %d\n", 
           myTimer.enabled, myTimer.value, myTimer.interrupt_flag);

    return 0;
}

