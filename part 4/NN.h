#ifndef __NN__
#define __NeuralNetwork__

#include <stdint.h>

namespace tflite
{
    template <unsigned int tOpCount>
    class MicroMutableOpResolver;
    class ErrorReporter;
    class Model;
    class MicroInterpreter;
} // namespace tflite

struct TfLiteTensor;

class NN
{
private:
    TfLiteTensor *input;
    TfLiteTensor *output;
    const tflite::Model *model;
    tflite::MicroInterpreter *interpreter;
    tflite::MicroMutableOpResolver<10> *res;
    uint8_t *total_space;
    tflite::ErrorReporter *errorReport;


    
public:
    NN();
    float giveOutput();
    float *getInput();
};

#endif