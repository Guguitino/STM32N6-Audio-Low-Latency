#!/bin/bash

pathCubeIde="/home/adamg/STM32Cube/stm32cubeide-1.19.0/"
project="file:///home/adamg/STApps/GS_Audio_N6/STM32N6-Audio-Low-Latency/Projects/GS/STM32CubeIDE"

conf="BM" # BM or BM_LP or FREERTOS or FREERTOS_LP

buildconf="GS_Audio_N6/"$conf
cubeIDE=$pathCubeIde/stm32cubeide
app="org.eclipse.cdt.managedbuilder.core.headlessbuild"
tmpDir="/C/ST/Temp/cubeIDE_WS"
rm -Rf $tmpDir

if [ "$#" -lt 1 ]; then
  echo "You need to provide 1 argument:"
  echo "the build config [BM/BM_LP/FREERTOS/FREERTOS_LP]"
fi

$cubeIDE --launcher.suppressErrors -nosplash -application $app -import $project -data $tmpDir -cleanBuild $buildconf
