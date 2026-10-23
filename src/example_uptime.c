/**
 * @file        example_uptime.c
 * @brief       How long the board has been running. The uptime option of the example library.
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
 */

/*
 * ****************************************************************************************************
 * Includes
 * ****************************************************************************************************
*/

#include "example_uptime.h"

/*
 * ****************************************************************************************************
 * Public function implementations
 * ****************************************************************************************************
*/

/*****************************************************************************************************/
/**
 * @brief now_ms, the milliseconds since start up, in hours, minutes and seconds.
 *
 * @param[in] now_ms  Milliseconds since start up: millis(), HAL_GetTick() or your own count.
 * @return Hours, minutes and seconds.
 */
example_uptime_t example_uptime(uint32_t now_ms)
{
    example_uptime_t uptime;
    uint32_t         seconds = now_ms / 1000UL;

    uptime.hours   = (uint32_t)(seconds / 3600UL);
    uptime.minutes = (uint8_t)((seconds / 60UL) % 60UL);
    uptime.seconds = (uint8_t)(seconds % 60UL);

    return uptime;
}
