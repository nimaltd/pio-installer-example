/**
 * @file        example.h
 * @brief       A small library made to try pio-installer on: a period that never blocks.
 * @version     1.0.0
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
 * @note        It reads no clock of its own: every call is given the time, in
 *              milliseconds, by the code calling it. So it builds with every
 *              framework, and on PlatformIO's native platform too. Its
 *              settings are in example_config.h, between its USER CODE lines:
 *              EXAMPLE_PERIOD_MS and EXAMPLE_GREETING.
 */

#ifndef EXAMPLE_H
#define EXAMPLE_H

/*
 * ****************************************************************************************************
 * Includes
 * ****************************************************************************************************
*/

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "example_config.h"

/*
 * ****************************************************************************************************
 * Configuration checks
 * ****************************************************************************************************
*/

#ifndef EXAMPLE_PERIOD_MS
#error "EXAMPLE_PERIOD_MS is not defined. Add it to example_config.h"
#elif (EXAMPLE_PERIOD_MS < 1U) || (EXAMPLE_PERIOD_MS > 86400000U)
#error "EXAMPLE_PERIOD_MS must be from 1 to 86400000"
#endif

#ifndef EXAMPLE_GREETING
#error "EXAMPLE_GREETING is not defined. Add it to example_config.h"
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/*
 * ****************************************************************************************************
 * Types
 * ****************************************************************************************************
*/

/*****************************************************************************************************/
/**
 * @brief One period. Declare one for each thing that repeats, and hand it to example_init().
 */
typedef struct
{
    uint32_t start; /**< Time in ms when the period under way began. */
    uint32_t count; /**< Times example_due() has said yes.          */

} example_t;

/*
 * ****************************************************************************************************
 * Public function prototypes
 * ****************************************************************************************************
*/

/*****************************************************************************************************/
/**
 * @brief Start a period of EXAMPLE_PERIOD_MS from now_ms.
 */
void example_init(example_t *handle, uint32_t now_ms);

/*****************************************************************************************************/
/**
 * @brief Whether the period has passed by now_ms. Returns at once, and starts the next one when it has.
 */
bool example_due(example_t *handle, uint32_t now_ms);

/*****************************************************************************************************/
/**
 * @brief How many times example_due() has said yes.
 */
uint32_t example_count(const example_t *handle);

/*****************************************************************************************************/
/**
 * @brief Write EXAMPLE_GREETING and how many periods have passed into text, for you to print.
 */
const char *example_hello(const example_t *handle, char *text, size_t size);

#ifdef __cplusplus
}
#endif

#endif /* EXAMPLE_H */
