/**
 * @file        example.c
 * @brief       A small library made to try lib-installer on: a period that never blocks.
 * @version     1.4.0
 *
 * @author      Nima Askari (NimaLTD)
 * @email       nima.askari@gmail.com
 * @github      https://www.github.com/nimaltd
 * @linkedin    https://www.linkedin.com/in/nimaltd
 * @youtube     https://www.youtube.com/@nimaltd
 * @instagram   https://instagram.com/github.nimaltd
 *
 * @copyright   (c) 2026 Nima Askari (NimaLTD)
 *              SPDX-License-Identifier: Apache-2.0
 *              See LICENSE.md in the project root for the full license text.
 *
 * @note        Plain C with nothing but the C library, so every framework
 *              builds it the same way.
 */

/*
 * ****************************************************************************************************
 * Includes
 * ****************************************************************************************************
*/

#include "example.h"
#include <stdio.h>

/*
 * ****************************************************************************************************
 * Public function implementations
 * ****************************************************************************************************
*/

/*****************************************************************************************************/
/**
 * @brief Start a period of EXAMPLE_PERIOD_MS from now_ms.
 *
 * @param[out] handle  The period to start.
 * @param[in]  now_ms  The time now, in ms: millis(), HAL_GetTick() or your own count.
 */
void example_init(example_t *handle, uint32_t now_ms)
{
    if (handle != NULL)
    {
        handle->start = now_ms;
        handle->count = 0U;
    }
}

/*****************************************************************************************************/
/**
 * @brief Whether the period has passed by now_ms. Returns at once, and starts the next one when it has.
 *
 * @param[in,out] handle  Period from example_init().
 * @param[in]     now_ms  The time now, in ms, from the same clock example_init() was given.
 * @return true once every EXAMPLE_PERIOD_MS, false in between.
 */
bool example_due(example_t *handle, uint32_t now_ms)
{
    bool due = false;

    /* Subtracted, never added, so the answer stays right when a 32 bit
       millisecond count wraps round after 49 days. */
    if ((handle != NULL) && ((now_ms - handle->start) >= (uint32_t)EXAMPLE_PERIOD_MS))
    {
        /* The next period starts where this one should have ended, not now,
           so a loop that comes back late does not make the rhythm drift. */
        handle->start += (uint32_t)EXAMPLE_PERIOD_MS;
        handle->count++;
        due = true;
    }

    return due;
}

/*****************************************************************************************************/
/**
 * @brief How many times example_due() has said yes.
 *
 * @param[in] handle  Period from example_init().
 * @return The count since example_init(), 0 for a NULL handle.
 */
uint32_t example_count(const example_t *handle)
{
    return (handle != NULL) ? handle->count : 0U;
}

/*****************************************************************************************************/
/**
 * @brief Write EXAMPLE_GREETING and how many periods have passed into text, for you to print.
 *
 * @param[in]  handle  Period from example_init().
 * @param[out] text    Where the line goes, such as "Hello from example 3".
 * @param[in]  size    The size of text. A line that does not fit is cut short.
 * @return text, so the call can go straight into printf() or Serial.println().
 *         An empty line when there is no text to write into.
 */
const char *example_hello(const example_t *handle, char *text, size_t size)
{
    if ((text == NULL) || (size == 0U))
    {
        return "";
    }

    (void)snprintf(text, size, "%s %lu", EXAMPLE_GREETING, (unsigned long)example_count(handle));

    return text;
}
