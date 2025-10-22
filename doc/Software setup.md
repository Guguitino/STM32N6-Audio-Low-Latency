# Software setup

## Installing STM32Cube software products

STM32CubeIDE and STM32CubeProgrammer are the 2 main applications to program on a STM32 board.

- **STM32CubeIDE** – Integrated development environment for code editing, compilation, and debugging.  
- **STM32CubeProgrammer** – Utility for flashing and managing STM32 devices.


### STM32CubeIDE
- Go to the official STM32CubeIDE page: https://www.st.com/en/development-tools/stm32cubeide.html
- Download the installer corresponding to your operating system.
- Extract and execute the installer :
```
% for generic linux distribution
unzip st-stm32cubide(...).sh zip
chmod +x st-stm32cubeide(...).sh
sudo ./st-stm32cubeide(...).sh
```!
- Accept the license agreement.
- Choose an installation path.
- Accept installing STLinkServer.

The main executable (stm32cubeide) will be available under your chosen installation directory.

### STM32CubeProgrammer

- Go to the official STM32CubeIDE page: https://www.st.com/en/development-tools/stm32cubeprog.html
- Download the installer corresponding to your operating system.
- Extract and execute the installer.
```
% for generic linux distribution
unzip stm32cubeprg(...).zip
chmod +x SetupSTM32CubeProgrammer(...).linux
./SetupSTM32CubeProgrammer(...).linux
```
- Accept the license agreement.
- Step 5 : Choose and installation directory.
- Step 6 : Select the following modules :
    - Core File
    - STM32CubeProgrammer
    - STM32TrustedPackageCreator

Binaries are located in the **bin** folder inside your installation directory.