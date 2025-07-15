#include "include/top.hpp"
#include "cadmium/simulation/root_coordinator.hpp"
#include "cadmium/simulation/rt_root_coordinator.hpp"
#include "cadmium/simulation/logger/stdout.hpp"
#include "cadmium/simulation/rt_clock/stm32_rt_clock.hpp"

extern "C"
{
#include "stm32h7xx_hal.h"
#include "tim.h"
#include "usart.h"
#include "main.h"
}

int main()
{
  MX_TIM2_Init();             
  HAL_TIM_Base_Start(&htim2); 
  auto model = std::make_shared<top_coupled>("top_coupled");
  STM32Clock<double> clock;
  auto rootCoordinator = cadmium::RealTimeRootCoordinator<STM32Clock<double>>(model, clock);
  rootCoordinator.setLogger<cadmium::STDOUTLogger>(";");
  rootCoordinator.start();
  rootCoordinator.simulate(10000.0);
  rootCoordinator.stop();
}
