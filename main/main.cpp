#include "include/top.hpp"
#include "cadmium/simulation/root_coordinator.hpp"
#include "cadmium/simulation/rt_root_coordinator.hpp"
#include "cadmium/simulation/logger/stdout.hpp"
#include "cadmium/simulation/rt_clock/stm32_rt_clock.hpp"


extern "C" {
  #include "stm32h7xx_hal.h"
  #include "tim.h"
  #include "usart.h"
  #include "main.h"
  #include "usb_device.h"
  #include "usbd_cdc_if.h"
  int __io_putchar(int ch) {
        uint8_t c = ch;
        CDC_Transmit_FS(&c, 1);  // Transmet un caractère via USB CDC
        return ch;
}

}

int main() {
    MX_USART2_UART_Init();
    MX_TIM2_Init();           //  TIM2 configuré dans CubeMX
    HAL_TIM_Base_Start(&htim2);  // Démarrage du timer pour l’horloge
    // 2) Simulation Cadmium
    printf("HELO");
    HAL_Delay(1000);
   
    auto model = std::make_shared<top_coupled>("top_coupled");
    STM32Clock<double> clock; 
    auto rootCoordinator=cadmium::RealTimeRootCoordinator<STM32Clock<double>>(model,clock);
    rootCoordinator.setLogger<cadmium::STDOUTLogger>(";");
    
    rootCoordinator.start();
    rootCoordinator.simulate(10000.0);
    rootCoordinator.stop();
}
