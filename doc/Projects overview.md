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
│   ├── Src/                  # User Source files
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

## STM32N6 Double Project Template

This project aim to be a load and run template application.
It shows how to set the debug configuration to download 2 different projects and how to jump from one another.

The first project to be executed is the First Stage Boot Loader, it manages clock and system configuration and initialize peripherals. Once done, it jumps to the application. This FSBL do not copy the application, the app binary has to be downloaded in the right place.

- FSBL location : 0x34000000 (SRAM1)
- APP location : 0x34100000 (SRAM2)

### The jump function

The jump function is simple, it calls the Reset Handler from the application project. Its memory address is **app base address + 4**.

```c
#define APP_LOCATION (0x34100000 + 4)

static void JumpToApp(void)
{
	void (*app_reset_handler)(void) = (void *)(*((uint32_t *)(APP_LOCATION)));
	app_reset_handler();
}
```

### Debug configuration

For the first launch :
- Select the Debug build configuration : Project $\rightarrow$ Build Configurations $\rightarrow$ Set Active $\rightarrow$ Debug
- Left-click on the FSBL project inside the Project Explorer to select it.
- Build the project.
- With the project selected, go to Run $\rightarrow$ Debug Configurations ...
- Double Left-click on `STM32 C/C++ Application` to create a new debug configuration for the FSBL project.
- Go to Startup.
- In Load Image and Symbols, click `Add...` and select the Appli project
- Check `Perform build`, `Download` and `Load symbols`.
- Specify the download address (0x34100000), if you can't, click ok to close the window and re-open it by clicking `Edit...`
- Click Apply and Debug to start debugging.



