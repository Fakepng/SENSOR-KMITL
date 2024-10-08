// --------------------------------------------
// Description: GPIO pin definitions for ESP32
// --------------------------------------------

#ifndef gpio_h
#define gpio_h

// General purpose input/output

/*
In: pulled up
Out: OK
Note: outputs PWM signal at boot, must be LOW to enter flashing mode
*/
#define D0   0

/*
In: TX pin
Out: OK
Note: debug output at boot
*/
#define D1   1

/*
In: OK
Out: OK
Note: connected to on-board LED, must be left floating or LOW to enter flashing mode
*/
#define D2   2

/*
In: OK
Out: RX pin
Note: HIGH at boot
*/
#define D3   3
#define D4   4

/*
In: OK
Out: OK
Note: must be HIGH during boot, outputs PWM signal at boot, strapping pin
*/
#define D5   5

/*
In: OK
Out: OK
Note: must be LOW during boot, boot fails if pulled high, strapping pin
*/
#define D12 12
#define D13 13

/*
In: OK
Out: OK
Note: outputs PWM signal at boot
*/
#define D14 14

/*
In: OK
Out: OK
Note: must be HIGH during boot, outputs PWM signal at boot, strapping pin
*/
#define D15 15
#define D16 16
#define D17 17
#define D18 18
#define D19 19
#define D21 21
#define D22 22
#define D23 23
#define D25 25
#define D26 26
#define D27 27
#define D32 32
#define D33 33

// Input only
#define D34 34
// Input only
#define D35 35
// Input only
#define D36 36
// Input only
#define D39 39

// Built-in LED
#define LED_BUILTIN D2

// Internal touch sensor
/*
The ESP32 has 10 internal capacitive touch sensors. These can sense variations in anything that holds an electrical charge, like the human skin. So they can detect variations induced when touching the GPIOs with a finger. These pins can be easily integrated into capacitive pads and replace mechanical buttons. The capacitive touch pins can also be used to wake up the ESP32 from deep sleep.
*/

#define TOUCH_0 D4
#define TOUCH_1 D0
#define TOUCH_2 D2
#define TOUCH_3 D15
#define TOUCH_4 D13
#define TOUCH_5 D12
#define TOUCH_6 D14
#define TOUCH_7 D27
#define TOUCH_8 D33
#define TOUCH_9 D32

// Analog to digital converter
/*
The ESP32 has 18 x 12 bits ADC input channels
*/

#define ADC0 D36
#define ADC3 D39
#define ADC4 D32
#define ADC5 D33
#define ADC6 D34
#define ADC7 D35
#define ADC10 D4
#define ADC11 D0
#define ADC12 D2
#define ADC13 D15
#define ADC14 D13
#define ADC15 D12
#define ADC16 D14
#define ADC17 D27
#define ADC18 D25
#define ADC19 D26

// Digital to analog converter
/*
There are 2 x 8 bits DAC channels on the ESP32 to convert digital signals into analog voltage signal outputs
*/

#define DAC1 D25
#define DAC2 D26

// // RTC GPIOs
// /*
// There is RTC GPIO support on the ESP32. The GPIOs routed to the RTC low-power subsystem can be used when the ESP32 is in deep sleep. These RTC GPIOs can be used to wake up the ESP32 from deep sleep when the Ultra Low Power (ULP) co-processor is running. The following GPIOs can be used as an external wake up source.
// */

// #define RTC_D0  D36
// #define RTC_D3  D39
// #define RTC_D4  D34
// #define RTC_D5  D35
// #define RTC_D6  D25
// #define RTC_D7  D26
// #define RTC_D8  D33
// #define RTC_D9  D32
// #define RTC_D10 D4
// #define RTC_D11 D0
// #define RTC_D12 D2
// #define RTC_D13 D15
// #define RTC_D14 D13
// #define RTC_D15 D12
// #define RTC_D16 D14
// #define RTC_D17 D27

// I2C
#define I2C_SDA D21
#define I2C_SCL D22

// SPI
#define SPI_VSPI_MOSI D23
#define SPI_VSPI_MISO D19
#define SPI_VSPI_CLK  D18
#define SPI_VSPI_CS   D5
#define SPI_HSPI_MOSI D13
#define SPI_HSPI_MISO D12
#define SPI_HSPI_CLK  D14
#define SPI_HSPI_CS   D15

// Serial

#define SERIAL_TX0 D1
#define SERIAL_RX0 D3
// #define SERIAL_TX1 D10
// #define SERIAL_RX1 D11
// #define SERIAL_TX2 D17
// #define SERIAL_RX2 D16

#endif