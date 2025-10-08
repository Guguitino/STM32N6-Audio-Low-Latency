## Réduction de la latence

WIP

Les modifications apportées portent sur le mode bypass et consistent principalement à utiliser une nouvelle fonction de traitement audio `audio_process_low_latency()` pour directement copier les échantillons d'un buffer circulaire à l'autre.
Le buffer de sortie utilisé est un buffer circulaire de petite taille `LLPLAYBACK_BUFFER_SIZE`. La fréquence de transfert des échantillons est augmenté et référencé à la taille du nouveau buffer.

Pour pouvoir changer le buffer de sortie utilisé, le flux audio de sortie est arrêté avec la fonction `BSP_AUDIO_OUT_Stop()` puis redémarré avec la prochaine itération.



