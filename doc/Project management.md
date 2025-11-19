## How to create a new STM32CubeIDE project

Here are the steps to create a new STM32CubeIDE project based on an existing one. 

- Copy/paste and rename the root directory of the project to copy.
- Inside the new directory :
    - Rename the .ioc file under the root folder
    - Open the **.project** file under **STM32CubeIDE** with a text editor (Ctrl + H to show hidden files)
    - Change the project name and the .ioc filename accordingly.
    - Open the **.project** file under **STM32CubeIDE/FSBL** with a text editor
    - Rename the project and add `_FSBL` at the end (two projects can't have the same name)
    - Save all files 
- Import the new project as described in the Quick Launch.

## How to use file linking

The linking feature can be used to link to files or folders without copying them into the project folder.

Steps to import a linked file : 
- Right click in the project explorer.
- New $\rightarrow$ File
- Select the parent folder.
- Click `Advanced >>`
- Check **Link to file in the file system**
- Browse to select the desired file
- Click Finish

The file is now linked with an absolute path. The path variable `PROJECT_LOC` refers to the folder <path_to_project_root_folder>/STM32CubeIDE/FSBL/. This variable can be used to link with a relative path :
- On the new linked file, right click $\rightarrow$ properties
- Edit the location by using `PROJECT_LOC/`. For example, the project root folder can be referenced with `PROJECT_LOC/../../` 
- You can check that the resolved location is correct.

## How to create a new pair of .c/.h file

This new file will be located in a folder tree as shown :

```
Project-Root/
│
├── Appli/                    # Source Folder
│   ├── Inc/                  # User Header files
│   └── Src/                  # User Source files
```

- Create a new source folder.
    - Right-click in the project explorer.
    - New $\rightarrow$ Source Folder
    - Select its location, name it and click Finish.
- Or alternatively link to a folder and defined it as source folder.
    - Right-click in the project explorer.
    - New $\rightarrow$ Folder
    - Advanced >> $\rightarrow$ Link to alternate location (Linked Folder).
    - Browse to select your folder and click Finish.
    - Right-click on the project $\rightarrow$ Properties
    - C/C++ General $\rightarrow$ Paths and symbols $\rightarrow$ Source Location
    - Click Add Folder and select the Linked Folder.
- Create 2 new folders Src and Inc.
- Right-click on the Inc folder $\rightarrow$ Add/remove Include Path...
- Make sure that all configurations are selected.
- Create your new files.


## How to use the ARM CMSIS DSP Library for STM32N6 in a CubeIDE Project

The CMSIS library is not distributed with precompiled binaries anymore,
you have to build the necessary source files with the project.

1) Download the STM32CubeN6 software package, it contains the library's source files. 
    - The repository uses linked submodule. Option `--recursive` has to be specified in the git clone command, more details are provided in the repository's README.md.
```
git clone --recursive https://github.com/STMicroelectronics/STM32CubeN6.git
```
  
2) Add the necessary files to the project
    - Create a new folder in the CubeIDE project to copy the library files into (e.g. /Driver/CMSIS/DSP/)
    - Copy the Include/, PrivateInclude/ and Source/ folder located in `STM32CubeN6-Master/Drivers/CMSIS/DSP` into the new project directory (e.g. /Driver/CMSIS/DSP/)
    - Refresh the project explorer view (F5)
    
3) Add the `Include` and the `PrivateInclude` folder paths to the project include paths
    - Right-click the project $\rightarrow$ properties
    - C/C++ Build $\rightarrow$ settings
    - In the **Tools Settings** tab, go to : MCC GCC compiler $\rightarrow$ Include Paths
    - Click on Add to include new paths.
    - Add the paths to `Include/` and `PrivateInclude/`, make sure that the path uses workspace variables or a relative path. 
    - Click `Ok` and `Apply`

4) Clean the `Source/` folder
    - Delete all unused folders (The CubeIDE's project explorer view can be refreshed with F5)
    - For each folder kept :
      - Open the file with the same name of the folder and its f16 version
      - Comment all the file (Ctrl+Shift+C to comment selection on CubeIDE)
      - Save files
      - The folder `CommonTables/` can be required by other component of the library (e.g. `TransfomFunction/`)

5) Add the following flag `-flax-vector-conversions`
    - Right-click the project $\rightarrow$ properties
    - C/C++ Build $\rightarrow$ settings
    - In the **Tools Settings** tab, go to : MCC GCC compiler $\rightarrow$ Miscellaneous
    - In `Other flags`, click on Add to add the flag.
    - Copy the following flag `-flax-vector-conversions`, click `Ok` and `Apply`

The DSP library can now be used in the project by including `arm_math.h`
 
### Resources 

- The ARM CMSIS-DSP library can be found here : https://arm-software.github.io/CMSIS_5/latest/DSP/html/

- A guide to integrate the library made by ST : https://community.st.com/t5/stm32-mcus/how-to-integrate-cmsis-dsp-libraries-on-a-stm32-project/ta-p/666790

## Clock configuration

Configure the clock according to the maximum supported frequencies (overdrive mode). This mode needs the **EXT_SMPS_MODE** pin to be configured. 
Therefore, the corresponding pin PF4 must be configured as **GPIO_OutPut** and assigned the **FSBL Pin Context**. This can be done under System Core $\rightarrow$ GPIO 

### RCC configuration

In the pinout & Configuration tab, under System Core $\rightarrow$ RCC:

In the Mode menu :
- Disable everything.
- High speed clock : Crystal/Ceramic Resonator.

In Configuration menu :
- Power Regulator Voltage Scale : Power Regulator Voltage Scale 0
- Other parameters stay with their default value

### Clock configuration menu

#### PLL configuration
- PLL1: 
    - Source Mux: HSI 
    - div: /2, *25, /1, /1 
    - freq: 800 MHz
- PLL2: 
    - Source Mux: HSI 
    - div: /8, *125, /1, /1
    - freq: 1000 MHz
- PLL3: 
    - Source Mux: HSI 
    - div: /8, *172, /7, /4 
    - freq: 49.142857 MHz
- PLL3: 
    - Source Mux: HSI 
    - div: /1, *25, /1, /1
    - freq: 1600 MHz

#### IC clock source

- IC1 (To CPU CLOCK Mux)
    - Source : PLL1
    - div : /1
    - freq : 800 MHz
- IC2 (To System Clock Mux)
    - Source : PLL1
    - div : /2
    - freq : 400 MHz
- IC3 (To XSPI2)
    - Source : PLL4
    - div : /1
    - freq : 49.142857 MHz
- IC5 (To CKPER CLOCK Mux)
  - Unused
- IC6 (To System Clock Mux)
    - Source : PLL2
    - div : /1
    - freq : 1000 MHz
- IC7 (To SAI)
    - Source : PLL3
    - div : /1
    - freq : 49.142857 MHz
- IC8 (To MDF)
    - Source : PLL3
    - div : /1
    - freq : 49.142857 MHz
- IC9 (To USART1)
  - Unused
- IC10 (To CKPER CLOCK Mux)
  - Unused
- IC11 (To System Clock Mux)
    - Source : PLL3
    - div : /1
    - freq : 800 MHz
- IC14 (To USART1)
    - Unused
- IC15 (To CKPER CLOCK Mux)
    - Unused 
- IC19 (To CKPER CLOCK Mux)
    - Unused 
- IC20 (To CKPER CLOCK Mux)
    - Unused 

#### Clock Mux

- CPU Clock Mux
    - IC1 : 800 MHz
- System Clock Mux
  - SYSB 
    - IC2 : 400 MHz
    - HPRE : /4
    - TIMPRE : /1
  - SYSC 
    - IC6 : 1000 MHz
  - SYSD
    - IC11 : 800 MHz
- CKPER Source Mux
  - HSI : 64 MHz
- USART1 Source Mux 
  - PCLK2 : 100 MHz
- MDF1 Source Mux 
  - IC8 : 49.142857 MHz
- SAI1 Source Mux
  - IC7 : 49.142857 MHz

### Resources 

- How to build an AI application from scratch : https://community.st.com/t5/stm32-mcus/how-to-build-an-ai-application-from-scratch-on-the-stm32n6570-dk/ta-p/825591#toc-hId--1516025603