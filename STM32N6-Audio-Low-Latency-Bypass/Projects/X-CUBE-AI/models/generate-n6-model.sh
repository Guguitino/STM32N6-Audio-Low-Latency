#!/bin/bash
generateCmd="/home/adamg/STM32Cube/Repository/Packs/STMicroelectronics/X-CUBE-AI/10.2.0/Utilities/linux/stedgeai" 

"$generateCmd" -m $1 --target stm32n6 --st-neural-art default@user_neural_art.json
cp ./st_ai_output/network.c .
cp ./st_ai_output/network_analyze_report.txt .
cp ./st_ai_output/network_atonbuf.xSPI2.raw  network_data.bin
rm -rf st_ai_*
