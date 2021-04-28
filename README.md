# TouchMIDI
#### Proiect curs SMP - Stanciulescu Andrei, 333AA

## Introducere
In acest proiect voi programa o placa de dezvoltare [FRDM KL25Z](https://www.nxp.com/design/development-boards/freedom-development-boards/mcu-boards/freedom-development-platform-for-kinetis-kl14-kl15-kl24-kl25-mcus:FRDM-KL25Z) sa se comporte precum un dispozitiv MIDI prin USB. Placa dispune de 2 porturi mini USB, unul fiind interfata OpenSDA prin care se incarca programele, se face debugging si se comunica prin portul serial, iar cel de-al doilea poate fi folosit pentru a implementa orice functionalitate din stack-ul USB. In cadrul acestui proiect voi implenta o claviatura MIDI prin USB cu 12 taste.

## Implementare hardware
Implemengtarea hardware este una simpla, singurele periferice atasate placii de dezvoltare fiind tastele claviaturii. In acest caz am ales sa nu folosesc butoane metalice, ci sa detectez atingerea pe niste suprafete metalice ce reprezinta tastele.
