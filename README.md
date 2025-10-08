# STM32N6-Audio-Low-Latency

Ce projet est basé sur le dépôt [STM32N6-GettingStarted-Audio](https://github.com/STMicroelectronics/STM32N6-GettingStarted-Audio) fourni pat STMicroelectronics.

Les modifications sont portées sur la configuration BM (Bare Metal) fonctionnant avec le modèle de speech enhancement.

## Structure générale

La configuration bare metal est composé de 2 fonctions principales : `init_bm()` et `exec_bm()`.
Elles sont responsables respectivement de l'initialisation des périphériques et de la boucle d'exécution.

Lors de l'exécution de `init_bm()`, plusieurs périphériques doivent être initialisés : les clocks, les mémoires, le NPU, les drivers HAL et BSP.

Ensuite, la fonction `exec_bm()` est appelée. La capture et le streaming audio sont initialisés et démarrés. Puis, le programme entre dans la boucle d'exécution.
Cette dernière comporte une unique tache : attendre que le nombre d'échantillons soit suffisant pour pouvoir ensuite les traiter en un bloc avec la fonction `audio_process()`. Avec la configuration par défaut, le programme attend 160*96 échantillons avant d'appeler la fonction. Le signal étant échantillonné à 16000 Hz, cela représente une latence algorithmique de 960 ms.

Pendant le traitement de l'audio, deux fonctions sont appelées successivement : `PreProc_DPU()` et `AiDPUProcess()`.
Elles sont chargées respectivement de créer le spectrogramme puis de le traiter avec le NPU.

## Flux audio

Deux buffers circulaires sont utilisées pour récupérer et fournir du flux audio aux périphériques d'entrées et de sorties de la carte. Ils sont respectivement dans les variables global de contexte `audio_acq_ctx` et `audio_proc_ctx`.
Les fonctions de callback du BSP sont utilisées pour garder le suivi de l'index de l'échantillon en cours de lecture et de celui en cours d'écriture par les DMA. La mise à jour de cette information est effectué avec une période de la moitié de la taille des buffers.

Les fonctions `AudioCapture_ring_buff_feed()` et `AudioCapture_ring_buff_consume()` permettent de récupérer les échantillons des buffers circulaires pour les traiter.

## Bypass

L'application comporte une fonctionnalité lui permettant de faire un bypass du traitement sonore grâce au bouton USER1. Une fois l'appui sur le bouton détecté, la fonction `BSP_PB_Callback()` est appelé et change l'état de la variable `AudioProcIsOn`. La variable à pour effet de décider quel paquet est utilisé pour alimenter le buffer circulaire de sortie. 

```c
//Fichier Projects/GS/Src/audio_bm.c, Fonction audio_process()
int16_t * audioPtr = (AudioProcIsOn) ?
      &proc_ctx_ptr->audio_out[AUDIO_OUT_FIRST] : (int16_t *)acq_buf ;
```

Le premier pointeur correspond aux échantillons traités et le second aux échantillons bruts.

## CubeIDE

Pour debuger avec CubeIDE :

- ouvrir un workspace
- Project->Build Configurations->Set Active->BM
- Lancer en mode debug ou run en sélectionnant la configuration "BM"