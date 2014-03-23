#if (defined HAVE_SPI || defined HAVE_UART || defined HAVE_LED)
# include <libopencm3/stm32/rcc.h>
# include <libopencm3/stm32/gpio.h>
#endif
#if defined HAVE_SPI
# include <libopencm3/stm32/spi.h>
#endif

#ifdef HAVE_UART
/** USART pins on X4 (dedicated 4-pin connector) */
# define RCC_USART1_PORT  RCC_GPIOA
# define USART1_PORT      GPIOA
# define USART1_TX_PIN    GPIO9  /* X4 pin 3 */
# define USART1_RX_PIN    GPIO10 /* X4 pin 2 */
/** Alias USART_CONSOLE to USART1 for simplicity */
# define USART_CONSOLE    USART1
/** USART pins on connector X7 */
# define RCC_USART3_PORT  RCC_GPIOC
# define USART3_PORT      GPIOC
# define USART3_TX_PIN    GPIO10  /* X7 pin 1 */
# define USART3_RX_PIN    GPIO11  /* X7 pin 2 */
# define USART3_CLK_PIN   GPIO12 /* X7 pin 3 */
#endif // def HAVE_UART

/** Green LED */
#if defined HAVE_LED
# define RCC_LED_GREEN_PORT  RCC_GPIOD
# define LED_GREEN_PORT      GPIOD
# define LED_GREEN_PIN       GPIO2

/** Red LED */
# define RCC_LED_RED_PORT    RCC_GPIOA
# define LED_RED_PORT        GPIOA
# define LED_RED_PIN         GPIO15
#endif // def HAVE_LED

#ifdef HAVE_SPI
/** SPI pins on connector X8 */
# define RCC_SPI1_PORT  RCC_GPIOA
# define SPI1_PORT      GPIOA
# define SPI1_MOSI_PIN  GPIO7  /* X8 pin 3 */
# define SPI1_MISO_PIN  GPIO6  /* X8 pin 6 */
# define SPI1_SCL_PIN   GPIO5  /* X8 pin 5 */
# define SPI1_NSS_PIN   GPIO4  /* X8 pin 8 */
# define SPI1_GPIO_AF   GPIO_AF5
#endif // def HAVE_SPI
