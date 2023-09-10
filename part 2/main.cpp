#include <Arduino.h>
#include "NN.h"

NN *nn;

void setup()
{
    Serial.begin(115200);
    nn = new NN();
}
void loop()
{
    float inp1 = random(1000) / 1000.0;
    float inp2 = random(1000) / 1000.0;
    char *should_be;
    if(inp2 > inp1){
        should_be = "true";
    }
    else{
        should_be = "false";
    }
    nn->getInput()[0] = inp1;
    nn->getInput()[1] = inp2;
    float assigned_val = nn->giveOutput();
    char *decided;
    if(assigned_val > 0.5){
        decided = "true";
    }
    else{
        decided = "false";
    }

    Serial.printf("input 1 = %.2f input2 = %.2f   answer should be %s, and it is: %s\n", inp1, inp2, should_be, decided);
    delay(1000);
}