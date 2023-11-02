
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led0)
/* The devicetree node identifier for the "sw0" alias. */
#define SW0_NODE	DT_ALIAS(sw0)

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec button = GPIO_DT_SPEC_GET(SW0_NODE, gpios);

int main(void)
{
	int ret;
	int temp=0;

	if (!gpio_is_ready_dt(&led) || (!gpio_is_ready_dt(&button))) {
		return 0;
	}

	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return 0;
	}

	while (1) {
			int val = gpio_pin_get_dt(&button);
			printk("val = %d",val);

			if (val > 0 && temp == 0) {
				temp = 1;
				printk("temp = 1");

			
			}
			else if(val > 0 && temp == 1) {
				temp = 0;
				printk("temp = 0");
			}

			
			gpio_pin_set_dt(&led, temp);
			printk("temp vaut %d",temp);
			



			
			k_msleep(SLEEP_TIME_MS);
	}
	return 0;
}
