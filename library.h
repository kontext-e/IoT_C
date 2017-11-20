#ifndef _H_LIBRARY
#define _H_LIBRARY

#include <unistd.h>

typedef uint8_t byte_t;

typedef void ( *Open_callback_type)(uint8_t Return_Code);
typedef void ( *Close_callback_type)(uint8_t Return_Code);
typedef void ( *GetVersion_callback_type)(uint8_t Return_Code, byte_t* version);
typedef void ( *SetStartGeneration_callback_type)(uint8_t Return_Code);
typedef void ( *CalculateGenerations_callback_type)(uint8_t Return_Code, uint8_t width, uint8_t height, byte_t* living_x, byte_t* living_y);

uint32_t RegOpen(Open_callback_type callback_function);
uint32_t RegClose(Close_callback_type callback_function);
uint32_t RegGetVersion(GetVersion_callback_type callback_function);
uint32_t RegSetStartGeneration(SetStartGeneration_callback_type callback_function);
uint32_t RegCalculateGenerations(CalculateGenerations_callback_type callback_function);

uint32_t Open( void );
uint32_t Close( void );
uint32_t GetVersion( void );
uint32_t SetStartGeneration(uint8_t Width, uint8_t Height, byte_t* Living_x, byte_t* Living_y);
uint32_t CalculateGenerations(uint8_t number_of_generations);

#endif //_H_LIBRARY
