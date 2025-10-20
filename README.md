# STM32N6-Audio-Low-Latency

This project is a development application to deploy AI models onto the STM32N6570-DK board.

## STM32CubeIDE projects description

The real file tree is different from the one seen in CubeIDE, this comes from the linked files feature. Paths described here are from the CubeIDE file tree. 

### STM32N6_Audio_Direct_Streaming

This is a simple application based on the example MDF_AudioRecorder to stream audio using double buffering.
The capture is made with the MDF configured with CubeMX and the playback uses the HAL driver to send audio to the audio output. Audio is processed with a very simple low-pass filter.

CubeMX is generating the main.c file with initialization code in *application/User*. The only user implementation in this file is the call to `AudioMainInit()` and `AudioMain()`, respectively the user initialization and main loop. User files are in *application/Src* or *application/Inc*.


## STM32CubeIDE deployment

- Install CubeIDE
- Clone the repository
- Open a workspace
- Import the project :
    * File $\rightarrow$ Import $\rightarrow$ Existing projects into Workspace
    * Select a project root directory (e.g. `/STM32N6_Audio_Direct_Streaming`)
    * Make sure to select all in the projects preview
    * Click Finish
- Select the FSBL IDE project in the file tree
- Click Run or Debug