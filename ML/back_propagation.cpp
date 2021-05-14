#include <iostream>
#define MAX2(a,b) (a) > (b) ? (a) : (b)
#define endl '\n'

class Neuron {
    public: 
        Neuron()
            : w_(2.0), b_(1.0)
        {}

        Neuron(const double& w_input, const double& b_input)
            : w_(w_input), b_(b_input)
        {}

    public: // attribute
        double w_; // weight of an input
        double b_; // bias

        double input_, output_; // saved for back-prop

    public:
        double feedForward(const double& _input) {

            input_ = _input;

            const double sigma = w_ * input_ + b_;

            output_ = getAct(sigma);

            return output_;
        }

        void propBackward(const double& target) {
            const double alpha = 0.1; // learing rate

            const double grad = (output_ - target) * getActGrad(output_);

            w_ -= alpha * grad * input_; // last input_ came from d(wx+b)/dw = x
            b_ -= alpha * grad * 1.0; // last 1.0 came from d(wx+b)/db=1

        }

        double getAct(const double& x) {
            // linear or ideneity activation function
            return x;

            // ReLU max(0,x)
            // return MAX2(0,x);
        }

        double getActGrad(const double& x) {
            // linear or ideneity activation function
            return 1.0;

            // ReLU if(x > 0.0) return 1.0; else 0.0;
            // return MAX2(0,x);
        }

        void feedForwardAndPrint(const double& input) {
            std::cout<<input<<' '<<feedForward(input)<<' '<<endl;
        }
};

int main() {
    
    // initialize my_neuron
    Neuron my_neuron(2.0,1.0);

    // Training
    for(int r=0;r<100;r++) {
        std::cout<<"Training "<<r<<endl;
        my_neuron.feedForwardAndPrint(1.0);
        my_neuron.propBackward(4.0);
        std::cout<<"w = "<<my_neuron.w_<<" b = "<<my_neuron.b_<<endl;
    }

    return 0;
}