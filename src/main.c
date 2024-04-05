/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

/*
 * Get configuration from the devicetree
 */
#define LED0_NODE DT_ALIAS(led0)
#if !DT_NODE_HAS_STATUS(LED0_NODE, okay)
#error "Unsupported board: led0 devicetree alias is not defined"
#endif

#define TOUCH0_NODE DT_ALIAS(touch0)

#if !DT_NODE_HAS_STATUS(TOUCH0_NODE, okay)
#error "Unsupported board: touch0 devicetree alias is not defined"
#endif

static const struct gpio_dt_spec button = GPIO_DT_SPEC_GET_OR(SW0_NODE, gpios, {0});
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct  gpio_dt_spec touch0 =  GPIO_DT_SPEC_GET_OR(LED0_NODE, gpios, {0});
static struct gpio_callback touch_cb_data;

void touch_activated(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
    printf("Touch activated at %" PRIu32 "\n", k_cycle_get_32());
    gpio_pin_toggle_dt(&led);
}

int main(void)
{
    int ret;

    if (!gpio_is_ready_dt(&led)) {
        return 0;
    }

    ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        return 0;
    }

    if (!gpio_is_ready_dt(&touch0)) {
        printf("Error: touch device %s is not ready\n",
               touch0.port->name);
        return 0;
    }

    ret = gpio_pin_configure_dt(&touch0, GPIO_INPUT);
    if (ret < 0) {
        printf("Error %d: failed to configure %s pin %d\n",
               ret, touch0.port->name, touch0.pin);
        return 0;
    }

    ret = gpio_pin_interrupt_configure_dt(&touch0, GPIO_INT_EDGE_TO_ACTIVE);
        if (ret != 0) {
        printf("Error %d: failed to configure interrupt on %s pin %d\n",
            ret, touch0.port->name, touch0.pin);
        return 0;
    }

    gpio_init_callback(&touch_cb_data, touch_activated, BIT(touch0.pin));
    gpio_add_callback(touch0.port, &touch_cb_data);
    printf("Set up button at %s pin %d\n", touch0.port->name, touch0.pin);

    printf("Board: %s\n", CONFIG_BOARD);

    while (1) {
        k_msleep(SLEEP_TIME_MS);
    }
    return 0;
}