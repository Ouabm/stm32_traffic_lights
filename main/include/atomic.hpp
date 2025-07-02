#ifndef ATOMIC_MODEL_HPP
#define ATOMIC_MODEL_HPP
#include "cadmium/modeling/devs/atomic.hpp"
#include "RGB.hpp"



using namespace cadmium;

struct atomic_modelState {

    RGB signal;

    atomic_modelState() : signal(0,0,0) {}
};

std::ostream& operator<<(std::ostream& out, const atomic_modelState& state) {
 
    return out;
}

class atomic_model : public Atomic<atomic_modelState> {
private :
    const RGB R;
    const RGB Y;
    const RGB G;
public:
    Port<RGB>out ;
    // Constructeur : initialiser la LED sur la broche LED1
    atomic_model(const std::string& id) :
        Atomic<atomic_modelState>(id, atomic_modelState()),R(32,0,0),Y(30,16,0),G(0,32,0)
    {
        out = addOutPort<RGB>("out");
    }

    void internalTransition(atomic_modelState& state) const override {
       if(state.signal==R){
        state.signal=G;
       }
       else if(state.signal==Y){
        state.signal=R;
        }
        else if(state.signal==G){
            state.signal=Y;
            }
            else {
                state.signal=R;
                }

    }

    void externalTransition(atomic_modelState& state, double e) const override {
        (void)state;
        (void)e;
    }

    void output(const atomic_modelState& state) const override {
        out->addMessage(state.signal);// Pas besoin d’output explicite ici, car l’action se fait dans internalTransition
         
    }

    [[nodiscard]] double timeAdvance(const atomic_modelState& state) const override {
        if(state.signal==R){
            return 2.0;
        }
        
        else if(state.signal==Y ){
            return 10.0;
        }
        else if(state.signal==G){
            return 10.0;
        }

        return 0.1;
        
    }
};
#endif
