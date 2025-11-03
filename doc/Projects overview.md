# STM32CubeIDE projects overview

The real file tree is different from the one seen in CubeIDE, this comes from the linked files feature. Paths described here are from the CubeIDE file tree. 

The file tree seen in STM32CubeIDE as the same structure as the file tree under the **STM32CubeIDE** folder. Only CubeMX generated files are linked.

## Debug tools

The printf() function has been redirected to the Serial Wire Viewer (SWV) console. 
The console can be opened in the IDE in debug mode :
- Launch debug session
- Window $\rightarrow$ Show View $\rightarrow$ SWV $\rightarrow$ SWV ITM Data Console

## STM32N6_Audio_Direct_Streaming

This is a simple application based on the example MDF_AudioRecorder to stream audio using double buffering.
The capture is made with the MDF configured with CubeMX and the playback uses the HAL driver to send audio to the audio output with the SAI. Audio is processed with a very simple low-pass filter.

### Project structure

Project structure as seen in STM32CubeIDE

```
STM32N6-Audio-Low-Latency/
│
├── Application/
│   ├── Inc/                  # User Header files
│   ├── Src/                  # User Header files
│   ├── Startup/              # CubeMX Generated files
│   └── User/                 # CubeMX Generated files
│
├── Debug/                    # Compilation output
│
├── Docs/
│
├── Drivers/
│   ├── BSP/                  # Board suport packages
│   ├── CMSIS/                # arm's CMSIS library
│   └── STM32N6xx_HAL_Driver/ # HAL Drivers
│
└── .ioc                    # CubeMX configuration file
```

CubeMX is generating the main.c file with initialization code in **application/User**. The only user implementation in this file is the call to `AudioMainInit()` and `AudioMain()`, respectively the user initialization and main loop. User files are in **application/Src** or **application/Inc**.

## STM32N6_Audio_Model_Zoo

This project aims to reproduce and extend the **ST Model Zoo Speech Enhancement** application. It includes the X-Cube-AI firmware package, the CMSIS-DSP library and other middlewares coming from the original ST's GS_Audio_N6 project. 

The project won't compile as its memory footprint seems to exceed the target device's available ROM. 

### Objectives

- Reproduce the original Model Zoo Speech Enhancement demo  
- Provide a clean and modular STM32CubeIDE project structure

## STM32N6 Audio_LRUN

This project aim to be a load and run template for audio processing
