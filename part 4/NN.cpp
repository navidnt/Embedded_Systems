#include "NN.h"
#include "mdata.h"
#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"
//#include "tensorflow/lite/version.h"
#include <Arduino.h>


const int total_alloc = 500000;
NN::NN()
{
    model = tflite::GetModel(converted_model_tflite);
    errorReport = new tflite::MicroErrorReporter();

    res = new tflite::MicroMutableOpResolver<10>();
    

    res->AddQuantize();
    res->AddDequantize();
    res->AddReshape();
    res->AddMul();
    res->AddAdd();
    res->AddLogistic();
    res->AddFullyConnected();

    psramInit();
    total_space = (uint8_t *)ps_malloc(total_alloc);
    interpreter = new tflite::MicroInterpreter(model, *res, total_space, total_alloc, errorReport);
    TfLiteStatus allocated_or_not = interpreter->AllocateTensors();
    size_t used_bytes = interpreter->arena_used_bytes();
    input = interpreter->input(0);
    output = interpreter->output(0);
}

float *NN::getInput()
{
    return input->data.f;
}

float NN::giveOutput()
{
    interpreter->Invoke();
    return output->data.f[0];
}
