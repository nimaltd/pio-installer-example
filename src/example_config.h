/**
 * @file        example_config.h
 * @brief       Build time configuration for the example library.
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
 * @note        Your settings go between the USER CODE markers. The installer
 *              replaces the rest of this file on every update and keeps what
 *              is between them, so a setting you changed is never lost. The
 *              library is in your project's lib folder, so the settings are
 *              your project's own, for every environment it builds.
 */

#ifndef EXAMPLE_CONFIG_H
#define EXAMPLE_CONFIG_H

/*
 * ****************************************************************************************************
 * Configuration
 * ****************************************************************************************************
*/

/* USER CODE BEGIN EXAMPLE_CONFIGURATION */

/* Milliseconds between two times example_due() says yes. Change it, install
   the library again, and see it kept. From 1 to 86400000, a day. */
#define EXAMPLE_PERIOD_MS           500U

/* What example_hello() starts its line with. */
#define EXAMPLE_GREETING            "Hello from example"

/* USER CODE END EXAMPLE_CONFIGURATION */

#endif /* EXAMPLE_CONFIG_H */
