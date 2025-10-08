# Implémentation streaming audio direct

Cette implémentation utilise les fonctions de callback pour copier directement les échantillons audio du buffer d'entrée vers le buffer de sortie.

Les fonctions de callback utilisés sont les suivantes (`audio_bm.c`) :

- `BSP_AUDIO_IN_TransferComplete_CallBack`
- `BSP_AUDIO_IN_HalfTransfer_CallBack`
- `BSP_AUDIO_OUT_TransferComplete_CallBack`
- `BSP_AUDIO_OUT_HalfTransfer_CallBack`

Les buffers utilisés sont **capture_buffer** pour l'acquisition et **playback_buffer** pour la sortie. Ils ont chacun une taille définie par **CAPTURE_BUFFER_SIZE** dans le fichier **stm32n6570_discovery_conf.h**.

Pour une taille de buffer inférieur à environ 500 ms, aucun son n'est obtenu en sortie. Pour une taille de buffer plus grande, on peut entendre le son capté en entrée. Le son obtenu est très bruité et avec un fort délai.

# TODO

- Supprimer le code non utilisé
- Pourquoi du son pour seulement des petits buffers ? (Double buffering ?)
- Pourquoi le signal est bruité ?
- Vérifier que le délai correspond à la taille de buffer