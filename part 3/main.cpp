#include <Arduino.h>
#include <EloquentTinyML.h>
#include "digits_model.h"


#define NUM_INPUTS 64
#define NUM_OUTPUTS 10
#define TENSOR_ARENA_SIZE 3500
Eloquent::TinyML::TfLite<NUM_INPUTS, NUM_OUTPUTS, TENSOR_ARENA_SIZE> ml;



void setup() {
    Serial.begin(115200);
    ml.begin(digits_model);
}

void loop() {
    float inp[64] = {    0.    , 0.    , 0.    , 0.875 , 0.9   , 0.875 , 0.    , 0.    ,
                         0.    , 0.    , 1.    , 0.075 , 0.0375, 0.625 , 0.    , 0.    ,
                         0.    , 0.    , 0.    , 0.    , 0.    , 0.9375, 0.    , 0.    ,
                         0.    , 0.    , 0.    , 0.    , 0.    , 0.975 , 0.    , 0.    ,
                         0.    , 0.    , 0.    , 0.1   , 0.9375, 0.2   , 0.    , 0.    ,
                         0.    , 0.    , 0.    , 1.    , 0.    , 0.    , 0.    , 0.    ,
                         0.    , 0.    , 1.    , 0.    , 0.    , 0.    , 0.    , 0.    ,
                         0.    , 1.    , 1.   , 0.875  , 0.875 , 0.75  , 0.    , 0.    };
    
    float predicted[10] = {0};
    int expected = 2;
    uint32_t start = micros();
    ml.predict(inp, predicted);
    uint32_t timetaken = micros() - start;
    Serial.print("It took ");
    Serial.print(timetaken);
    Serial.println(" microseconds.");
    Serial.print("Output should be ");
    Serial.println(expected);
    Serial.print("and predicted values are ");
    Serial.print(predicted[0]);
    for (int i = 1; i < 10; i++) {
        Serial.print(", ");
        Serial.print(predicted[i]);
    }
    Serial.print("\n");
    delay(1000);
}