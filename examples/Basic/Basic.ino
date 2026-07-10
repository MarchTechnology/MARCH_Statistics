#include <Arduino.h>

#include <MARCH_Statistics.h>

void setup() {
    Serial.begin(115200);
    double data[] = { 10, 20, 30, 40, 50 };

    auto result = MARCH::Statistics::calculate(data);

    Serial.printf("Mean : %.2f\n", result.mean);
    Serial.printf("Median : %.2f\n", result.median);
    Serial.printf("Minimum : %.2f\n", result.minimum);
    Serial.printf("Maximum : %.2f\n", result.maximum);
    Serial.printf("Range : %.2f\n", result.range);
    Serial.printf("Variance : %.2f\n", result.variance);
    Serial.printf("StdDev : %.2f\n", result.standardDeviation);
    Serial.printf("CV : %.2f %%\n", result.coefficientOfVariation);
}

void loop() { }