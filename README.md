# STM32N6-Audio-Low-Latency

This project provides a real-time environment for audio processing on the STM32N6 Microcontroller. It is a development application to deploy AI audio processing models on the STM32N6570-DK board. 

## Development tools

This application is tested on STM32N6570-DK.

This project was developed using STM32CubeIDE and STM32CubeMX to generate hardware configuration code. More information on the installation of this software can be found in the **docs** directory.

## Quick launch

- Clone the repository
- Start STM32CubeIDE and create or select a workspace
- Import the project :
    * File $\rightarrow$ Import $\rightarrow$ Existing projects into Workspace
    * Select a project root directory (e.g. `/STM32N6_Audio_Direct_Streaming`)
    * Make sure all projects are selected in the import preview
    * Click Finish
- Connect the STM32N6570-DK board via USB and switch in dev mode (BOOT1 = H)
- Select the FSBL project in the file tree
- Click **Run** or **Debug** to launch the project

## How to create a new STM32CubeIDE project

Here are the steps to create a new STM32CubeIDE project based on an existing one. 

- Copy/paste and rename the root directory of the project to copy.
- Inside the new directory :
    - Rename the .ioc file under the root folder
    - Open the **.project** file under **STM32CubeIDE** with a text editor
    - Change the project name and the .ioc filename accordingly.
    - Open the **.project** file under **STM32CubeIDE/FSBL** with a text editor
    - Rename the project and add `_FSBL` at the end (two projects can't have the same name)
    - Save all files 
- Import the new project as described in the Quick Launch.