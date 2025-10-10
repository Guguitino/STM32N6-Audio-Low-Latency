# Implémentation streaming audio direct

Cette implémentation utilise les fonctions de callback pour copier directement les échantillons audio du buffer d'entrée vers le buffer de sortie.

Les fonctions de callback utilisés sont les suivantes (`audio_bm.c`) :

- `BSP_AUDIO_IN_TransferComplete_CallBack`
- `BSP_AUDIO_IN_HalfTransfer_CallBack`
- `BSP_AUDIO_OUT_TransferComplete_CallBack`
- `BSP_AUDIO_OUT_HalfTransfer_CallBack`

Les buffers utilisés sont **capture_buffer** pour l'acquisition et **playback_buffer** pour la sortie. Ils ont chacun une taille définie par **BUFFER_SIZE**. Le codex limite la taille du buffer d'entrée à 128 échantillons.

Le son est cependant dégradé, une solution est d'utiliser le même buffer pour l'acquisition et le playback. Pour cela, il suffit d'appeler 

# TODO
- Pourquoi la fonction SCB_EnableDCache() casse tout ?
- Pourquoi le signal est bruité ?