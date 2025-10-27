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

