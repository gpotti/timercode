/**
 * @file timer_modes.c
 * @brief Timer state transitions with multiple modes (Countdown, Stopwatch, Disabled).
 */

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Maximum duration of the timer.
 */
#define MAX_DURATION 10

/**
 * @brief Timer modes.
 */
typedef enum {
    MODE_DISABLED,  /**< Timer is disabled. */
    MODE_COUNTDOWN, /**< Countdown mode. */
    MODE_STOPWATCH  /**< Stopwatch mode. */
} TimerMode;

/**
 * @brief Timer state variables.
 */
typedef struct {
    int timer_value;      /**< Current value of the timer. */
    bool timer_enabled;   /**< Whether the timer is enabled. */
    bool interrupt_flag;  /**< Whether an interrupt is triggered. */
    TimerMode timer_mode; /**< Current mode of the timer. */
} TimerState;

/**
 * @brief Initializes the timer.
 * @param state Pointer to the timer state.
 */
void initTimer(TimerState *state) {
    state->timer_value = 0;
    state->timer_enabled = false;
    state->interrupt_flag = false;
    state->timer_mode = MODE_DISABLED;
}

/**
 * @brief Sets the timer in Countdown mode.
 * @param state Pointer to the timer state.
 * @param value New timer value (must be within 1 to MAX_DURATION).
 */
void setCountdownTimer(TimerState *state, int value) {
    if (value > 0 && value <= MAX_DURATION) {
        state->timer_value = value;
        state->timer_enabled = true;
        state->interrupt_flag = false;
        state->timer_mode = MODE_COUNTDOWN;
    }
}

/**
 * @brief Decrements the timer value by 1 in Countdown mode.
 * @param state Pointer to the timer state.
 */
void decrementTimer(TimerState *state) {
    if (state->timer_enabled && state->timer_mode == MODE_COUNTDOWN && state->timer_value > 0) {
        state->timer_value--;
    }
}

/**
 * @brief Increments the timer value in Stopwatch mode.
 * @param state Pointer to the timer state.
 */
void incrementStopwatch(TimerState *state) {
    if (state->timer_enabled && state->timer_mode == MODE_STOPWATCH) {
        state->timer_value++;
    }
}

/**
 * @brief Triggers an interrupt in Countdown mode.
 * @param state Pointer to the timer state.
 */
void triggerInterrupt(TimerState *state) {
    if (state->timer_enabled && state->timer_mode == MODE_COUNTDOWN && state->timer_value == 0) {
        state->interrupt_flag = true;
        state->timer_enabled = false;
        state->timer_mode = MODE_DISABLED;
    }
}

/**
 * @brief Resets the timer.
 * @param state Pointer to the timer state.
 */
void resetTimer(TimerState *state) {
    state->timer_value = 0;
    state->timer_enabled = false;
    state->interrupt_flag = false;
    state->timer_mode = MODE_DISABLED;
}
