# Boot from flash

This document describe how to use a first stage bootloader (FSBL) for the boot rom to load the code from the external memory into the internal RAM. 

## The signing process

Every binary must be signed before being uploaded, see **resources** section for more information.

The signed binaries are generated using the STM32 Signing Tool software included as a STM32CubeIDE external plugin `stm32cubide2.0.0/`. Se the following example to sign a binary :
```
% from <project root>/STM32CubeIDE/FSBL/Debug/

~/stm32cubeide_2.0.0/plugins/com.st.stm32cube.ide.mcu.externaltools.cubeprogrammer.linux64_2.2.300.202508131133/tools/bin/STM32_SigningTool_CLI -bin STM32N6_Audio_Direct_Streaming_FSBL.bin -nk -of 0x80000000 -t fsbl -o STM32N6_Audio_Direct_Streaming_FSBL-Trusted.bin -hv 2.3 -dump STM32N6_Audio_Direct_Streaming_FSBL-Trusted.bin -align
```

The signing process can be automated using STM32CubeIDE, see the [tutorial](https://community.st.com/t5/stm32-mcus/how-to-add-the-stm32n6-s-header-signature-as-post-build/ta-p/778436)

## Flashing binaries

Signed images can be flashed into the external memory using STM32CubeProgrammer as described in [this](https://community.st.com/t5/stm32-mcus/how-to-build-an-ai-application-from-scratch-on-the-stm32n6570-dk/ta-p/825591#toc-hId--1283626472) tutorial.

STM32CubePrgrammer also has a command line interface (CLI) include as a STM32CubeIDE external plugin.



## Resources

- How to add the STM32N6's header signature as post build : https://community.st.com/t5/stm32-mcus/how-to-add-the-stm32n6-s-header-signature-as-post-build/ta-p/778436

- How to build an AI application from scratch on the STM32N6570-DK using STM32CubeMX : https://community.st.com/t5/stm32-mcus/how-to-build-an-ai-application-from-scratch-on-the-stm32n6570-dk/ta-p/825591#toc-hId--1283626472

- STM32N6 FSBL explained : https://community.st.com/t5/stm32-mcus/stm32n6-fsbl-explained/ta-p/764307

- How to debug STM32N6 using STM32CubeIDE  : https://community.st.com/t5/stm32-mcus/how-to-debug-stm32n6-using-stm32cubeide/ta-p/800547