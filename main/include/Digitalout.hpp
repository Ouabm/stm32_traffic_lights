#ifndef __DIGITAL_OUTPUT_HPP__
#define __DIGITAL_OUTPUT_HPP__
#include <iostream>
#include "cadmium/modeling/devs/atomic.hpp"
#include "stm32h7xx_hal_gpio.h" 
#include "stm32h7xx_hal_rcc.h"
#include "stm32h743xx.h"
#include "RGB.hpp"

namespace cadmium {

    struct DigitalOutputState {
        RGB output;
        double sigma;
       explicit DigitalOutputState() : output(0,0,0),sigma(std::numeric_limits<double>::infinity()) {}
    };


    std::ostream& operator<<(std::ostream &out, const DigitalOutputState& state) {
        
        return out;
    }


    class DigitalOutput : public Atomic<DigitalOutputState> {
    private :
    const RGB R;
    const RGB Y;
    const RGB G;
    public:
        
        Port <RGB> in;

        // Hardware references
        GPIO_TypeDef* port;
        GPIO_TypeDef* port2;
        GPIO_InitTypeDef pin1;
        GPIO_InitTypeDef pin2;
        GPIO_InitTypeDef pin3;

        DigitalOutput(const std::string& id, GPIO_TypeDef* selectedPort,GPIO_TypeDef* selectedPort2, GPIO_InitTypeDef* selectedPin1, GPIO_InitTypeDef* selectedPin2, GPIO_InitTypeDef* selectedPin3) : 
         Atomic<DigitalOutputState>(id, DigitalOutputState()), port(selectedPort),port2(selectedPort2), pin1(*selectedPin1), pin2(*selectedPin2), pin3(*selectedPin3),R(32,0,0),Y(30,16,0),G(0,32,0)
        {
            in =addInPort <RGB> ("in");
            HAL_GPIO_Init(port, &pin1);
            HAL_GPIO_Init(port2, &pin2);
            HAL_GPIO_Init(port, &pin3);
        }

        void internalTransition(DigitalOutputState& state) const override {
            
              state.sigma = std::numeric_limits<double>::infinity();
        }

        void externalTransition(DigitalOutputState& state, double /*e*/) const override {
            if (!in->empty()) {
                for (const auto value : in->getBag()) {
                    state.output = value;
                }
           
               state.sigma = 0; 
            }
        }

        void output(const DigitalOutputState& state) const override {
         
             if(state.output==G){
                HAL_GPIO_WritePin(port, pin1.Pin, GPIO_PIN_SET);// Nothing internally changes on its own
                HAL_GPIO_WritePin(port2, pin2.Pin, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(port, pin3.Pin, GPIO_PIN_RESET);
            }
            else if(state.output==Y){
                HAL_GPIO_WritePin(port, pin1.Pin, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(port2, pin2.Pin, GPIO_PIN_SET);
                HAL_GPIO_WritePin(port, pin3.Pin, GPIO_PIN_RESET);
                }
            else if( state.output==R){
                HAL_GPIO_WritePin(port, pin1.Pin, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(port2, pin2.Pin, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(port, pin3.Pin, GPIO_PIN_SET);
                }

           
    }

        [[nodiscard]] double timeAdvance(const DigitalOutputState& /*state*/) const override {
            return state.sigma;
        }
    };

} // namespace cadmium

#endif // __DIGITAL_OUTPUT_HPP__
