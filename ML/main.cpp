#include <iostream>
#include "NeuralNetwork.h"

// 컴파일 명령어
// clang++ -std=c++11 -g /Users/{Username}/Documents/codingTest/ML/main.cpp /Users/{Username}/Documents/codingTest/ML/NeuralNetwork.cpp -o /Users/minseongkim/Documents/codingTest/ML/main

int main() {
    VectorND<D> x(2);
    x[0] = 0.0; x[1] = 0.0;

    VectorND<D> y_target(2);
    y_target[0] = 0.3f; // 타겟

    VectorND<D> y_temp(2); // ForwardProp시켰을 때, 나오는 값을 임시로 저장하는 메모리

    NeuralNetwork nn_;
    nn_.initialize(2, 1, 1); // input, output, hidden layer 수
    nn_.alpha_ = 0.1;

    for(int i=0;i<100;i++) { // 학습 반복
        nn_.setInputVector(x);
        nn_.propForward();

        nn_.copyOutputVector(y_temp);
        std::cout<<y_temp<<endl;

        nn_.propBackward(y_target);
    }

    // 100번 훈련으로 타겟 0.3 -> 결과값 : 0.299994

    return 0;
}