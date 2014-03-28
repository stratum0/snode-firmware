#define HAVE_SPI
#define HAVE_LED
#include "snode.h"

void init_led(void);
void init_spi(void);
void toggle_led(void);
void led_on(void);
void led_off(void);

void init_led(void) {
	rcc_periph_clock_enable(RCC_LED_GREEN_PORT);
  gpio_mode_setup(LED_GREEN_PORT,
		GPIO_MODE_OUTPUT,
		GPIO_PUPD_NONE,
		LED_GREEN_PIN);
}

void led_on(void) {
	gpio_set(LED_GREEN_PORT, LED_GREEN_PIN);
}
void led_off(void) {
	gpio_clear(LED_GREEN_PORT, LED_GREEN_PIN);
}
void toggle_led(void) {
	gpio_toggle(LED_GREEN_PORT, LED_GREEN_PIN);
}

void init_spi(void) {
	rcc_periph_clock_enable(RCC_SPI1_PORT);
	gpio_mode_setup(SPI1_PORT,
		GPIO_MODE_AF,
		GPIO_PUPD_PULLUP,
		SPI1_MOSI_PIN | SPI1_MISO_PIN | SPI1_NSS_PIN | SPI1_SCL_PIN);
	gpio_set_output_options(SPI1_PORT,
		GPIO_OTYPE_PP,
		GPIO_OSPEED_10MHZ,
		SPI1_MOSI_PIN | SPI1_MISO_PIN | SPI1_NSS_PIN | SPI1_SCL_PIN);
	gpio_set_af(SPI1_PORT,
		SPI1_GPIO_AF,
		SPI1_MOSI_PIN | SPI1_MISO_PIN | SPI1_NSS_PIN | SPI1_SCL_PIN);

	rcc_periph_clock_enable(RCC_SPI1);
	spi_enable(SPI1);
	spi_init_master(SPI1,
		1000,
		/*SPI_CR1_BAUDRATE_FPCLK_DIV_64,*/
		SPI_CR1_CPOL_CLK_TO_0_WHEN_IDLE,
		/*SPI_CR1_CPHA_CLK_TRANSITION_2,*/
		SPI_CR1_CPHA_CLK_TRANSITION_1,
		SPI_CR1_DFF_8BIT,
		/*SPI_CR1_DFF_16BIT,*/
		SPI_CR1_LSBFIRST);
	/* Set NSS management to software.
	 * Note:
	 * Setting nss high is very important, even if we are controlling the GPIO
	 * ourselves this bit needs to be at least set to 1, otherwise the spi
	 * peripheral will not send any data out.
	 */
	spi_set_nss_high(SPI1);
}

int main(void) {
	init_spi();
	init_led();
	led_on();

	uint32_t i;
	while(1) {
		char buf[] = {'S','t','r','a','t','u','m','0',0x0};
		uint32_t n;
		toggle_led();
		for(n = 0; n <= sizeof(buf); ++n) {
			spi_write(SPI1, buf[n]);
			/* Apparently we have to wait here, otherwise bits get scrambled up */
			for(i = 0; i < 200; i++) { __asm__("nop"); }
		}
		toggle_led();
		for(i = 0; i < 500000; i++) { __asm__("nop"); }
	}
}
/* vim: set ai si ts=2 sw=2 : */
