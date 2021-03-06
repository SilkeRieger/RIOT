/*
 * Copyright (C) 2014 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser General
 * Public License v2.1. See the file LICENSE in the top level directory for more
 * details.
 */

/**
 * @ingroup     boards_openmote-cc2538
 * @{
 *
 * @file
 * @brief       Peripheral MCU configuration for the OpenMote-cc2538 board
 *
 * @author      Hauke Petersen <hauke.petersen@fu-berlin.de>
 * @author      Sebastian Meiling <s@mlng.net>
 */

#ifndef PERIPH_CONF_H
#define PERIPH_CONF_H

#include "cc2538_gpio.h"
#include "periph_cpu.h"

#ifdef __cplusplus
 extern "C" {
#endif

/**
 * @name    Clock system configuration
 * @{
 */
/*
 * 0: use internal 32KHz RCOSC
 * 1: use external 32KHz XOSC
 */
#ifndef SYS_CTRL_OSC32K_USE_XTAL
#define SYS_CTRL_OSC32K_USE_XTAL        (1)
#endif
/*
 * 0: use internal 16MHz RCOSC
 * 1: use external 32MHz XOSC, required for RF operation
 */
#ifndef SYS_CTRL_OSC_USE_XTAL
#define SYS_CTRL_OSC_USE_XTAL           (1)
#endif

#if SYS_CTRL_OSC_USE_XTAL
#define CLOCK_OSC           (XOSC32M_FREQ)
#else
#define CLOCK_OSC           (RCOSC16M_FREQ)
#endif

#if SYS_CTRL_OSC32K_USE_XTAL
#define CLOCK_OSC32K        (XOSC32K_FREQ)    /* XCOSC frequency */
#else
#define CLOCK_OSC32K        (RCOSC32K_FREQ)    /* XCOSC frequency */
#endif

/* System clock frequency 32MHz */
#define CLOCK_CORECLOCK     (CLOCK_OSC)
/* I/O clock rate setting 16MHz */
#define CLOCK_IO            (CLOCK_OSC / 2)
/** @} */
/**
 * @name    Timer configuration
 *
 * General purpose timers (GPT[0-3]) are configured consecutively and in order
 * (without gaps) starting from GPT0, i.e. if multiple timers are enabled.
 *
 * @{
 */
static const timer_conf_t timer_config[] = {
    {
        .chn = 2,
        .cfg = GPTMCFG_16_BIT_TIMER, /* required for XTIMER */
    },
    {
        .chn = 1,
        .cfg = GPTMCFG_32_BIT_TIMER,
    },
    {
        .chn = 2,
        .cfg = GPTMCFG_16_BIT_TIMER,
    },
    {
        .chn = 1,
        .cfg = GPTMCFG_32_BIT_TIMER,
    },
};

#define TIMER_NUMOF         ARRAY_SIZE(timer_config)
#define TIMER_IRQ_PRIO      1
/** @} */

/**
 * @name ADC configuration
 * @{
 */
#define SOC_ADC_ADCCON3_EREF  SOC_ADC_ADCCON3_EREF_AVDD5

static const adc_conf_t adc_config[] = {
    GPIO_PIN(0, 2), /**< GPIO_PA2 = AD4_PIN */
    GPIO_PIN(0, 3), /**< GPIO_PA3 = CTS_DI07_PIN */
    GPIO_PIN(0, 4), /**< GPIO_PA4 = AD5_PIN */
    GPIO_PIN(0, 5), /**< GPIO_PA5 = AD6_PIN */
    GPIO_PIN(0, 6), /**< GPIO_PA6 = ON_SLEEP_PIN */
};

#define ADC_NUMOF           ARRAY_SIZE(adc_config)
/** @} */

/**
 * @name    UART configuration
 * @{
 */
static const uart_conf_t uart_config[] = {
    {
        .dev      = UART0_BASEADDR,
        .rx_pin   = GPIO_PIN(0, 0),
        .tx_pin   = GPIO_PIN(0, 1),
#ifdef MODULE_PERIPH_UART_HW_FC
        .cts_pin  = GPIO_UNDEF,
        .rts_pin  = GPIO_UNDEF
#endif
    }
};

/* interrupt function name mapping */
#define UART_0_ISR          isr_uart0

/* macros common across all UARTs */
#define UART_NUMOF          ARRAY_SIZE(uart_config)
/** @} */

/**
 * @name    I2C configuration
 * @{
 */
#define I2C_IRQ_PRIO            1

static const i2c_conf_t i2c_config[] = {
    {
        .speed = I2C_SPEED_FAST,    /**< bus speed */
        .scl_pin = GPIO_PIN(1, 3),  /**< GPIO_PB3, OpenBattery */
        .sda_pin = GPIO_PIN(1, 4)   /**< GPIO_PB4, OpenBattery */
    },
};

#define I2C_NUMOF               ARRAY_SIZE(i2c_config)
/** @} */

/**
 * @name    SPI configuration
 * @{
 */
static const spi_conf_t spi_config[] = {
    {
        .num      = 0,
        .mosi_pin = GPIO_PIN(0, 5),
        .miso_pin = GPIO_PIN(0, 4),
        .sck_pin  = GPIO_PIN(0, 2),
        .cs_pin   = GPIO_PIN(0, 3)
    },
};

#define SPI_NUMOF           ARRAY_SIZE(spi_config)
/** @} */

/**
 * @name    Radio peripheral configuration
 * @{
 */
#define RADIO_IRQ_PRIO      1
/** @} */

#ifdef __cplusplus
} /* end extern "C" */
#endif

#endif /* PERIPH_CONF_H */
/** @} */
