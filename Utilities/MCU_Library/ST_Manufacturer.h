/*This Files define for ALL MCU Of ST Electronics Productions*/


/*Define Main Series for ST Manu chip 32 bits*/
#define ST7                     1
#define ST6                     2       
#define ST10                    3
#define ARM7                    4
#define ARM9                    5
#define ARM_CORTEX_M0           6
#define ARM_CORTEX_M3           7
#define ARM_CORTEX_M4           8

/*Define SUB Series for ST Manu, Cortex-M3*/
typedef enum {
    /*L Series, Ultra Low Power*/
    STM32L100Cx=0,
    STM32L100Rx,
    
    STM32L151Cx,
    STM32L151Rx,
    STM32L151Vx,
    STM32L151Qx,
    STM32L151Zx,
    STM32L151Ux,
    
    STM32L152Cx,
    STM32L152Rx,
    STM32L152Vx,
    STM32L152Qx,
    STM32L152Zx,
    
    STM32L162Rx,
    STM32L162Vx,
    STM32L162Qx,
    STM32L162Zx,
    /*End LowPower Series*/
    
    /* W Series, Wireless MCU*/
    STM32W108Hx,
    STM32W108Cx,
    
    /*T Series, Touch sensing MCU*/
    STM32TS60,
    
    /*STM100 Value Line, 24Mhz*/
    STM32F100Cx,
    STM32F100Rx,
    STM32F100Vx,
    STM32F100Zx,    
    
    /*STM101, 36Mhz*/
    STM32F101Tx,
    STM32F101Cx,
    STM32F101Rx,
    STM32F101Vx,
    STM32F101Zx,    
    
    /*STM102, 48Mhz*/
    STM32F102Cx,
    STM32F102Rx,
    
    /*STM103, 72Mhz*/
    STM32F103Tx,
    STM32F103Cx,
    STM32F103Rx,
    STM32F103Vx,
    STM32F103Zx,
    
    /*STM105/107, 72Mhz*/
    STM32F105Rx,
    STM32F107Rx,
    STM32F105Vx,
    STM32F107Vx,
    
    UNDEN = 0xFF,
}STCortexM3;
