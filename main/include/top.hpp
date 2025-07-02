#ifndef SAMPLE_TOP_HPP
#define SAMPLE_TOP_HPP

#include "cadmium/modeling/devs/coupled.hpp"
#include "atomic.hpp"
#include "Digitalout.hpp"
#include "stm32h7xx_hal_rcc.h"
#include "stm32h7xx_hal_dma.h"
#include "stm32h7xx_hal_uart.h"


using namespace cadmium;

struct top_coupled : public Coupled {
    top_coupled(const std::string& id) : Coupled(id) {
         __HAL_RCC_GPIOB_CLK_ENABLE();
         __HAL_RCC_GPIOE_CLK_ENABLE();

        auto atomique = addComponent<atomic_model>("atomique");

        // Configuration manuelle du GPIO
        static GPIO_InitTypeDef led_config1 = {
            .Pin = GPIO_PIN_0,
            .Mode = GPIO_MODE_OUTPUT_PP,
            .Pull = GPIO_NOPULL,
            .Speed = GPIO_SPEED_FREQ_LOW,
            .Alternate = 0
        };
        static GPIO_InitTypeDef led_config2 = {
            .Pin = GPIO_PIN_1,
            .Mode = GPIO_MODE_OUTPUT_PP,
            .Pull = GPIO_NOPULL,
            .Speed = GPIO_SPEED_FREQ_LOW,
            .Alternate = 0
        };
        static GPIO_InitTypeDef led_config3 = {
            .Pin = GPIO_PIN_14,
            .Mode = GPIO_MODE_OUTPUT_PP,
            .Pull = GPIO_NOPULL,
            .Speed = GPIO_SPEED_FREQ_LOW,
            .Alternate = 0
        };

        GPIO_TypeDef* led_port = GPIOB;
        GPIO_TypeDef* led_port2 = GPIOE;
        

        // Ajout du composant DigitalOutput avec paramètres
        auto digitaloutput = addComponent<DigitalOutput>(
            "digitaloutput",
            led_port,
            led_port2,
            &led_config1,
            &led_config2,
            &led_config3
        );

        addCoupling(atomique->out, digitaloutput->in);
    }
};

#endif  // SAMPLE_TOP_HPP
