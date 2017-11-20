#include <memory.h>
#include "library.h"

/* OS dependent implementation skipped because if license issues */
/* only some demo code here */

void (*OpenCallback)(uint8_t);
void (*CloseCallback)(uint8_t);
void (*GetVersionCallback)(uint8_t, byte_t*);
void (*SetStartGenerationCallback)(uint8_t);
void (*CalculateGenerationsCallback)(uint8_t, uint8_t, uint8_t, byte_t*, byte_t*);

uint32_t RegOpen(Open_callback_type callback) {
    OpenCallback = callback;
    return 0;
}
uint32_t RegClose(Close_callback_type callback) {
    CloseCallback = callback;
    return 0;
}
uint32_t RegGetVersion(GetVersion_callback_type callback) {
    GetVersionCallback = callback;
    return 0;
}
uint32_t RegSetStartGeneration(SetStartGeneration_callback_type callback) {
    SetStartGenerationCallback = callback;
    return 0;
}
uint32_t RegCalculateGenerations(CalculateGenerations_callback_type callback) {
    CalculateGenerationsCallback = callback;
    return 0;
}

uint32_t Open() {
    OpenCallback(0);
    return 0;
}

uint32_t Close() {
    CloseCallback(0);
    return 0;
}

uint32_t GetVersion() {
    // call the callback with some version information fitting into 14 characters
    const char * version = "1.0.0-SNAPSHOT";
    GetVersionCallback(0, (byte_t *) version);

    return 0;
}
uint32_t SetStartGeneration(byte_t width, byte_t height, byte_t* living_x, byte_t* living_y) {
    SetStartGenerationCallback(0);

    // just for showing that the call went until here
    return width;
}
uint32_t CalculateGenerations(byte_t number_of_generations) {
    // just for showing that the call went until here
    return number_of_generations;
}
