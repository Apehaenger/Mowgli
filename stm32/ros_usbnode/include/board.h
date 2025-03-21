  

#ifndef __BOARD_H
#define __BOARD_H

#ifdef __cplusplus
extern "C" {
#endif


// this is the sofware version that any other Mowgli components like MowgliRover will match against

#define MOWGLI_SW_VERSION_MAJOR              1
#define MOWGLI_SW_VERSION_BRANCH             0              /* even = stable, odd = testing/unstable */
#define MOWGLI_SW_VERSION_MINOR              2


// Versions:
//
// 1.0.2 - enabled BAGHEERA config, made BLADEMOTOR pins a fixed #define otherwise the #ifdef BLADEMOTOR_USART_ENABLED would not work
//         added #ifdef HAS_EXT_IMU to allow to switch off ext IMU code
//         External and Internal IMU seperated in ros node and main/calibration 
//


/*
 * Boards
 * BOARD_YARDFORCE500 - Mowgli Project with external IMU
 * BOARD_YARDFORCE500_BAGHEERA Bagheera Project without IMU or BLADE Motor
 */

/********************************************************************************
* YARDFORCE 500 MAINBOARD
********************************************************************************/
#ifdef BOARD_YARDFORCE500            
    #define PANEL_TYPE_YARDFORCE_500_CLASSIC    1
    // #define PANEL_TYPE_YARDFORCE_900_ECO   1

    // define to support IMU Calibration (Mag) via https://github.com/pcdangio/ros-calibration_imu
    #define SUPPORT_ROS_CALIBRATION_IMU           1     

    #define I_DONT_NEED_MY_FINGERS              1       // disables EmergencyController() (no wheel lift, or tilt sensing and stopping the blade anymore)

    #define HAS_EXT_IMU                         1       // set this if you have a external IMU

    // #define HAS_ULTRASONIC_SENSOR               1

    /// nominal max charge current is 1 Amp
    #define MAX_CHARGE_CURRENT                  1.0
    // if voltage is greater than this assume we are docked
    #define MIN_CHARGE_VOLTAGE                  5.0
    // must provide at least MIN_CHARGE_VOLTAGE when docked
    #define MIN_CHARGE_PWM                      500
    // if current is greater than this assume the battery is charging
    #define MIN_CHARGE_CURRENT                  0.2
    #define LOW_BAT_THRESHOLD                   23.5

    // when the battery voltage reaches this we stop charging
    #define BAT_CHARGE_CUTOFF_VOLTAGE           28.80
    // maximum voltage that we will ever supply to the battery
    #define MAX_CHARGE_VOLTAGE                  29.4

    // Emergency sensor timeouts
    #define WHEEL_LIFT_EMERGENCY_MILLIS         500
    #define TILT_EMERGENCY_MILLIS               500      // used for both the mechanical and accelerometer based detection
    #define STOP_BUTTON_EMERGENCY_MILLIS        20
    #define PLAY_BUTTON_CLEAR_EMERGENCY_MILLIS  2000
    #define IMU_ONBOARD_INCLINATION_THRESHOLD   0x38     // stock firmware uses 0x2C (way more allowed inclination)

    // IMU configuration options
    //#define IMU_ONBOARD_ACCELERATION            1
    //#define IMU_ONBOARD_TEMP                    1
    #define IMU_ACCELERATION                    1       // external IMU
    #define IMU_ANGULAR                         1       // external IMU
    
    // we use J18 (Red 9 pin connector as Master Serial Port)
    #define MASTER_J18 1

    // enable Drive and Blade Motor UARTS
    #define DRIVEMOTORS_USART_ENABLED 1
    #define BLADEMOTOR_USART_ENABLED 1
    #define PANEL_USART_ENABLED 1

    // our IMU hangs of a bigbanged I2C bus on J18
    #define SOFT_I2C_ENABLED 1

    #define LED_PIN GPIO_PIN_2
    #define LED_GPIO_PORT GPIOB
    #define LED_GPIO_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE()

    /* 24V Supply */
    #define TF4_PIN GPIO_PIN_5
    #define TF4_GPIO_PORT GPIOC
    #define TF4_GPIO_CLK_ENABLE() __HAL_RCC_GPIOC_CLK_ENABLE()

    /* Blade Motor nRESET - (HIGH for no RESET) */
    #define PAC5223RESET_PIN GPIO_PIN_14
    #define PAC5223RESET_GPIO_PORT GPIOE
    #define PAC5223RESET_GPIO_CLK_ENABLE() __HAL_RCC_GPIOE_CLK_ENABLE()

    /* Drive Motors - HC366 OE Pins (LOW to enable) */
    #define PAC5210RESET_PIN GPIO_PIN_15
    #define PAC5210RESET_GPIO_PORT GPIOE
    #define PAC5210RESET_GPIO_CLK_ENABLE() __HAL_RCC_GPIOE_CLK_ENABLE()

    /* Charge Control Pins - HighSide/LowSide MosFET */    
    #define CHARGE_LOWSIDE_PIN GPIO_PIN_8
    #define CHARGE_HIGHSIDE_PIN GPIO_PIN_9
    #define CHARGE_GPIO_PORT GPIOE
    #define CHARGE_GPIO_CLK_ENABLE() __HAL_RCC_GPIOE_CLK_ENABLE();

    /* Stop button - (HIGH when pressed) */
    #define STOP_BUTTON_YELLOW_PIN GPIO_PIN_0
    #define STOP_BUTTON_YELLOW_PORT GPIOC
    #define STOP_BUTTON_GPIO_CLK_ENABLE() __HAL_RCC_GPIOC_CLK_ENABLE()
    #define STOP_BUTTON_WHITE_PIN GPIO_PIN_8
    #define STOP_BUTTON_WHITE_PORT GPIOC

    /* Mechanical tilt - (HIGH when set) */
    #define TILT_PIN GPIO_PIN_8
    #define TILT_PORT GPIOA
    #define TILT_GPIO_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE()

    /* SPI3 Flash */
    #define FLASH_CLK_PIN GPIO_PIN_3 // GPIO B
    #define FLASH_MISO_PIN GPIO_PIN_4  // GPIO B
    #define FLASH_MOSI_PIN GPIO_PIN_5  // GPIO B
    #define FLASH_SPI_PORT GPIOB
    #define FLASH_SPI_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE()
    #define FLASH_nCS_PIN GPIO_PIN_15 // GPIO A
    #define FLASH_SPICS_PORT GPIOA
    #define FLASH_SPICS_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE()

    /* Wheel lift - (HIGH when set) */
    #define WHEEL_LIFT_BLUE_PIN GPIO_PIN_0
    #define WHEEL_LIFT_BLUE_PORT GPIOD
    #define WHEEL_LIFT_GPIO_CLK_ENABLE() __HAL_RCC_GPIOD_CLK_ENABLE()
    #define WHEEL_LIFT_RED_PIN GPIO_PIN_1
    #define WHEEL_LIFT_RED_PORT GPIOD

    /* Play button - (LOW when pressed) */
    #define PLAY_BUTTON_PIN GPIO_PIN_7
    #define PLAY_BUTTON_PORT GPIOC
    #define PLAY_BUTTON_GPIO_CLK_ENABLE() __HAL_RCC_GPIOC_CLK_ENABLE()

    /* Panel Buttons published in /button_state rostopic via Serial */
    #define PANEL_BUTTON_BYTES 12
    /* Byte Mapping of Bytes 5-16
      0     1     2     3     4     5     6     7     8     9     10    11    12    13    14    15    16
      
      0x55  0xaa  0x02  0x50  0x00  0x02  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00
      0x55  0xaa  0x02  0x50  0x00  0x00  0x02  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00
      0x55  0xaa  0x02  0x50  0x00  0x00  0x00  0x02  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00
      0x55  0xaa  0x02  0x50  0x00  0x00  0x00  0x00  0x02  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00
      0x55  0xaa  0x02  0x50  0x00  0x00  0x00  0x00  0x00  0x02  0x00  0x00  0x00  0x00  0x00  0x00  0x00
      0x55  0xaa  0x02  0x50  0x00  0x00  0x00  0x00  0x00  0x00  0x02  0x00  0x00  0x00  0x00  0x00  0x00
      0x55  0xaa  0x02  0x50  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x02  0x00  0x00  0x00  0x00  0x00
      0x55  0xaa  0x02  0x50  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x02  0x00  0x00  0x00  0x00
      0x55  0xaa  0x02  0x50  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x02  0x00  0x00  0x00
      0x55  0xaa  0x02  0x50  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x02  0x00  0x00
      0x55  0xaa  0x02  0x50  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x02  0x00
      0x55  0xaa  0x02  0x50  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x02
      
      55    aa    02    50    00    timer S1    S2    Lock  OK	  MON   TUE   WED   THU   FRI   SAT   SUN
    */      
    /* Rain Sensor - (LOW when pressed) */
    #define RAIN_SENSOR_PIN GPIO_PIN_2
    #define RAIN_SENSOR_PORT GPIOE
    #define RAIN_SENSOR_GPIO_CLK_ENABLE() __HAL_RCC_GPIOE_CLK_ENABLE()

    /* either J6 or J18 can be the master USART port */
#ifdef MASTER_J6    
    /* USART1 (J6 Pin 1 (TX) Pin 2 (RX)) */    
    #define MASTER_USART_INSTANCE USART1
    #define MASTER_USART_RX_PIN GPIO_PIN_10
    #define MASTER_USART_RX_PORT GPIOA
    #define MASTER_USART_TX_PIN GPIO_PIN_9
    #define MASTER_USART_TX_PORT GPIOA
    #define MASTER_USART_GPIO_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE()
    #define MASTER_USART_USART_CLK_ENABLE() __HAL_RCC_USART1_CLK_ENABLE()
    #define MASTER_USART_IRQ USART1_IRQn
#endif
#ifdef MASTER_J18
    /* UART4 (J18 Pin 7 (TX) Pin 8 (RX)) */
    #define MASTER_USART_INSTANCE UART4
    #define MASTER_USART_RX_PIN GPIO_PIN_11
    #define MASTER_USART_RX_PORT GPIOC
    #define MASTER_USART_TX_PIN GPIO_PIN_10
    #define MASTER_USART_TX_PORT GPIOC
    #define MASTER_USART_GPIO_CLK_ENABLE() __HAL_RCC_GPIOC_CLK_ENABLE()
    #define MASTER_USART_USART_CLK_ENABLE() __HAL_RCC_UART4_CLK_ENABLE()
    #define MASTER_USART_IRQ UART4_IRQn
#endif

    #ifdef DRIVEMOTORS_USART_ENABLED
        /* drive motors PAC 5210 (USART2) */
        #define DRIVEMOTORS_USART_INSTANCE USART2
        
        #define DRIVEMOTORS_USART_RX_PIN GPIO_PIN_6
        #define DRIVEMOTORS_USART_RX_PORT GPIOD

        #define DRIVEMOTORS_USART_TX_PIN GPIO_PIN_5
        #define DRIVEMOTORS_USART_TX_PORT GPIOD

        #define DRIVEMOTORS_USART_GPIO_CLK_ENABLE() __HAL_RCC_GPIOD_CLK_ENABLE()
        #define DRIVEMOTORS_USART_USART_CLK_ENABLE() __HAL_RCC_USART2_CLK_ENABLE()

        #define DRIVEMOTORS_USART_IRQ USART2_IRQn
        #define DRIVEMOTORS_MSG_LEN 12
    #endif 
    
        /* blade motor PAC 5223 (USART3) */
        #define BLADEMOTOR_USART_INSTANCE USART3
        
        #define BLADEMOTOR_USART_RX_PIN GPIO_PIN_11
        #define BLADEMOTOR_USART_RX_PORT GPIOB

        #define BLADEMOTOR_USART_TX_PIN GPIO_PIN_10
        #define BLADEMOTOR_USART_TX_PORT GPIOB

        #define BLADEMOTOR_USART_GPIO_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE()
        #define BLADEMOTOR_USART_USART_CLK_ENABLE() __HAL_RCC_USART3_CLK_ENABLE()


    #ifdef PANEL_USART_ENABLED    
        #define PANEL_USART_INSTANCE USART1

        #define PANEL_USART_RX_PIN GPIO_PIN_10
        #define PANEL_USART_RX_PORT GPIOA

        #define PANEL_USART_TX_PIN GPIO_PIN_9
        #define PANEL_USART_TX_PORT GPIOA

        #define PANEL_USART_GPIO_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE()
        #define PANEL_USART_USART_CLK_ENABLE() __HAL_RCC_USART1_CLK_ENABLE()
        #define PANEL_USART_IRQ USART1_IRQn
    #endif

    // J18 has the SPI3 pins, as we dont use SPI3, we recycle them for I2C Bitbanging (for our Pololu ALtIMU-10v5)
    #ifdef SOFT_I2C_ENABLED
        #define SOFT_I2C_SCL_PIN GPIO_PIN_3
        #define SOFT_I2C_SCL_PORT GPIOB
        #define SOFT_I2C_SDA_PIN GPIO_PIN_4
        #define SOFT_I2C_SDA_PORT GPIOB

        #define SOFT_I2C_GPIO_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE();
    #endif

#endif // BOARD_YARDFORCE500


// ====================================================================================================================================================
//  BAGHEERA CONFIG 
// ====================================================================================================================================================

/********************************************************************************
* YARDFORCE 500 MAINBOARD / BAGHEERA (NO IMU, NO BLADE MOTOR)
********************************************************************************/
#ifdef BOARD_YARDFORCE500_BAGHEERA            
    #define PANEL_TYPE_YARDFORCE_500_CLASSIC    1
    // #define PANEL_TYPE_YARDFORCE_900_ECO   1

    // define to support IMU Calibration (Mag) via https://github.com/pcdangio/ros-calibration_imu
    #define SUPPORT_ROS_CALIBRATION_IMU           1     


    // #define HAS_EXT_IMU                         1       // set this if you have a external IMU

    #define I_DONT_NEED_MY_FINGERS              1       // disables EmergencyController() (no wheel lift, or tilt sensing and stopping the blade anymore)

    // #define HAS_ULTRASONIC_SENSOR               1

    /// nominal max charge current is 1 Amp
    #define MAX_CHARGE_CURRENT                  1.0
    // if voltage is greater than this assume we are docked
    #define MIN_CHARGE_VOLTAGE                  5.0
    // must provide at least MIN_CHARGE_VOLTAGE when docked
    #define MIN_CHARGE_PWM                      500
    // if current is greater than this assume the battery is charging
    #define MIN_CHARGE_CURRENT                  0.2
    #define LOW_BAT_THRESHOLD                   23.5

    // when the battery voltage reaches this we stop charging
    #define BAT_CHARGE_CUTOFF_VOLTAGE           28.80
    // maximum voltage that we will ever supply to the battery
    #define MAX_CHARGE_VOLTAGE                  29.4

    // Emergency sensor timeouts
    #define WHEEL_LIFT_EMERGENCY_MILLIS         500
    #define TILT_EMERGENCY_MILLIS               500      // used for both the mechanical and accelerometer based detection
    #define STOP_BUTTON_EMERGENCY_MILLIS        20
    #define PLAY_BUTTON_CLEAR_EMERGENCY_MILLIS  2000
    #define IMU_ONBOARD_INCLINATION_THRESHOLD   0x38     // stock firmware uses 0x2C (way more allowed inclination)

    // IMU configuration options
    //#define IMU_ONBOARD_ACCELERATION            1
    //#define IMU_ONBOARD_TEMP                    1
    #define IMU_ACCELERATION                    1       // external IMU
    #define IMU_ANGULAR                         1       // external IMU
    
    // we use J18 (Red 9 pin connector as Master Serial Port)
    #define MASTER_J18 1

    // enable Drive and Blade Motor UARTS
    #define DRIVEMOTORS_USART_ENABLED 1
    // #define BLADEMOTOR_USART_ENABLED 1
    #define PANEL_USART_ENABLED 1

    // our IMU hangs of a bigbanged I2C bus on J18
    #define SOFT_I2C_ENABLED 1

    #define LED_PIN GPIO_PIN_2
    #define LED_GPIO_PORT GPIOB
    #define LED_GPIO_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE()

    /* 24V Supply */
    #define TF4_PIN GPIO_PIN_5
    #define TF4_GPIO_PORT GPIOC
    #define TF4_GPIO_CLK_ENABLE() __HAL_RCC_GPIOC_CLK_ENABLE()

    /* Blade Motor nRESET - (HIGH for no RESET) */
    #define PAC5223RESET_PIN GPIO_PIN_14
    #define PAC5223RESET_GPIO_PORT GPIOE
    #define PAC5223RESET_GPIO_CLK_ENABLE() __HAL_RCC_GPIOE_CLK_ENABLE()

    /* Drive Motors - HC366 OE Pins (LOW to enable) */
    #define PAC5210RESET_PIN GPIO_PIN_15
    #define PAC5210RESET_GPIO_PORT GPIOE
    #define PAC5210RESET_GPIO_CLK_ENABLE() __HAL_RCC_GPIOE_CLK_ENABLE()

    /* Charge Control Pins - HighSide/LowSide MosFET */    
    #define CHARGE_LOWSIDE_PIN GPIO_PIN_8
    #define CHARGE_HIGHSIDE_PIN GPIO_PIN_9
    #define CHARGE_GPIO_PORT GPIOE
    #define CHARGE_GPIO_CLK_ENABLE() __HAL_RCC_GPIOE_CLK_ENABLE();

    /* Stop button - (HIGH when pressed) */
    #define STOP_BUTTON_YELLOW_PIN GPIO_PIN_0
    #define STOP_BUTTON_YELLOW_PORT GPIOC
    #define STOP_BUTTON_GPIO_CLK_ENABLE() __HAL_RCC_GPIOC_CLK_ENABLE()
    #define STOP_BUTTON_WHITE_PIN GPIO_PIN_8
    #define STOP_BUTTON_WHITE_PORT GPIOC

    /* Mechanical tilt - (HIGH when set) */
    #define TILT_PIN GPIO_PIN_8
    #define TILT_PORT GPIOA
    #define TILT_GPIO_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE()

    /* SPI3 Flash */
    #define FLASH_CLK_PIN GPIO_PIN_3 // GPIO B
    #define FLASH_MISO_PIN GPIO_PIN_4  // GPIO B
    #define FLASH_MOSI_PIN GPIO_PIN_5  // GPIO B
    #define FLASH_SPI_PORT GPIOB
    #define FLASH_SPI_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE()
    #define FLASH_nCS_PIN GPIO_PIN_15 // GPIO A
    #define FLASH_SPICS_PORT GPIOA
    #define FLASH_SPICS_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE()

    /* Wheel lift - (HIGH when set) */
    #define WHEEL_LIFT_BLUE_PIN GPIO_PIN_0
    #define WHEEL_LIFT_BLUE_PORT GPIOD
    #define WHEEL_LIFT_GPIO_CLK_ENABLE() __HAL_RCC_GPIOD_CLK_ENABLE()
    #define WHEEL_LIFT_RED_PIN GPIO_PIN_1
    #define WHEEL_LIFT_RED_PORT GPIOD

    /* Play button - (LOW when pressed) */
    #define PLAY_BUTTON_PIN GPIO_PIN_7
    #define PLAY_BUTTON_PORT GPIOC
    #define PLAY_BUTTON_GPIO_CLK_ENABLE() __HAL_RCC_GPIOC_CLK_ENABLE()

    /* Panel Buttons published in /button_state rostopic via Serial */
    #define PANEL_BUTTON_BYTES 12
    /* Byte Mapping of Bytes 5-16
      0     1     2     3     4     5     6     7     8     9     10    11    12    13    14    15    16
      
      0x55  0xaa  0x02  0x50  0x00  0x02  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00
      0x55  0xaa  0x02  0x50  0x00  0x00  0x02  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00
      0x55  0xaa  0x02  0x50  0x00  0x00  0x00  0x02  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00
      0x55  0xaa  0x02  0x50  0x00  0x00  0x00  0x00  0x02  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00
      0x55  0xaa  0x02  0x50  0x00  0x00  0x00  0x00  0x00  0x02  0x00  0x00  0x00  0x00  0x00  0x00  0x00
      0x55  0xaa  0x02  0x50  0x00  0x00  0x00  0x00  0x00  0x00  0x02  0x00  0x00  0x00  0x00  0x00  0x00
      0x55  0xaa  0x02  0x50  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x02  0x00  0x00  0x00  0x00  0x00
      0x55  0xaa  0x02  0x50  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x02  0x00  0x00  0x00  0x00
      0x55  0xaa  0x02  0x50  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x02  0x00  0x00  0x00
      0x55  0xaa  0x02  0x50  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x02  0x00  0x00
      0x55  0xaa  0x02  0x50  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x02  0x00
      0x55  0xaa  0x02  0x50  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x00  0x02
      
      55    aa    02    50    00    timer S1    S2    Lock  OK	  MON   TUE   WED   THU   FRI   SAT   SUN
    */      
    /* Rain Sensor - (LOW when pressed) */
    #define RAIN_SENSOR_PIN GPIO_PIN_2
    #define RAIN_SENSOR_PORT GPIOE
    #define RAIN_SENSOR_GPIO_CLK_ENABLE() __HAL_RCC_GPIOE_CLK_ENABLE()

    /* either J6 or J18 can be the master USART port */
#ifdef MASTER_J6    
    /* USART1 (J6 Pin 1 (TX) Pin 2 (RX)) */    
    #define MASTER_USART_INSTANCE USART1
    #define MASTER_USART_RX_PIN GPIO_PIN_10
    #define MASTER_USART_RX_PORT GPIOA
    #define MASTER_USART_TX_PIN GPIO_PIN_9
    #define MASTER_USART_TX_PORT GPIOA
    #define MASTER_USART_GPIO_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE()
    #define MASTER_USART_USART_CLK_ENABLE() __HAL_RCC_USART1_CLK_ENABLE()
    #define MASTER_USART_IRQ USART1_IRQn
#endif
#ifdef MASTER_J18
    /* UART4 (J18 Pin 7 (TX) Pin 8 (RX)) */
    #define MASTER_USART_INSTANCE UART4
    #define MASTER_USART_RX_PIN GPIO_PIN_11
    #define MASTER_USART_RX_PORT GPIOC
    #define MASTER_USART_TX_PIN GPIO_PIN_10
    #define MASTER_USART_TX_PORT GPIOC
    #define MASTER_USART_GPIO_CLK_ENABLE() __HAL_RCC_GPIOC_CLK_ENABLE()
    #define MASTER_USART_USART_CLK_ENABLE() __HAL_RCC_UART4_CLK_ENABLE()
    #define MASTER_USART_IRQ UART4_IRQn
#endif

    #ifdef DRIVEMOTORS_USART_ENABLED
        /* drive motors PAC 5210 (USART2) */
        #define DRIVEMOTORS_USART_INSTANCE USART2
        
        #define DRIVEMOTORS_USART_RX_PIN GPIO_PIN_6
        #define DRIVEMOTORS_USART_RX_PORT GPIOD

        #define DRIVEMOTORS_USART_TX_PIN GPIO_PIN_5
        #define DRIVEMOTORS_USART_TX_PORT GPIOD

        #define DRIVEMOTORS_USART_GPIO_CLK_ENABLE() __HAL_RCC_GPIOD_CLK_ENABLE()
        #define DRIVEMOTORS_USART_USART_CLK_ENABLE() __HAL_RCC_USART2_CLK_ENABLE()

        #define DRIVEMOTORS_USART_IRQ USART2_IRQn
        #define DRIVEMOTORS_MSG_LEN 12
    #endif 

    
        /* blade motor PAC 5223 (USART3) */
        #define BLADEMOTOR_USART_INSTANCE USART3
        
        #define BLADEMOTOR_USART_RX_PIN GPIO_PIN_11
        #define BLADEMOTOR_USART_RX_PORT GPIOB

        #define BLADEMOTOR_USART_TX_PIN GPIO_PIN_10
        #define BLADEMOTOR_USART_TX_PORT GPIOB

        #define BLADEMOTOR_USART_GPIO_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE()
        #define BLADEMOTOR_USART_USART_CLK_ENABLE() __HAL_RCC_USART3_CLK_ENABLE()
    

    #ifdef PANEL_USART_ENABLED    
        #define PANEL_USART_INSTANCE USART1

        #define PANEL_USART_RX_PIN GPIO_PIN_10
        #define PANEL_USART_RX_PORT GPIOA

        #define PANEL_USART_TX_PIN GPIO_PIN_9
        #define PANEL_USART_TX_PORT GPIOA

        #define PANEL_USART_GPIO_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE()
        #define PANEL_USART_USART_CLK_ENABLE() __HAL_RCC_USART1_CLK_ENABLE()
        #define PANEL_USART_IRQ USART1_IRQn
    #endif

    // J18 has the SPI3 pins, as we dont use SPI3, we recycle them for I2C Bitbanging (for our Pololu ALtIMU-10v5)
    #ifdef SOFT_I2C_ENABLED
        #define SOFT_I2C_SCL_PIN GPIO_PIN_3
        #define SOFT_I2C_SCL_PORT GPIOB
        #define SOFT_I2C_SDA_PIN GPIO_PIN_4
        #define SOFT_I2C_SDA_PORT GPIOB

        #define SOFT_I2C_GPIO_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE();
    #endif

#endif // BOARD_YARDFORCE500_BAGHEERA


#ifdef __cplusplus
}
#endif

#endif /* __BOARD_H */
