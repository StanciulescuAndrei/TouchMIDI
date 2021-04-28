#include "mbed.h"
#include "USBMIDI.h"

USBMIDI midi; // Obiect pentru comunicatia MIDI prin USB
BusIn keys(PTC11, PTC10, PTC6, PTC4, PTC5, PTC3, PTC9, PTC8, PTA5, PTA4, PTA12, PTD4); // Bus pentru cei 12 pini digitali de intrare

Timer timer;

int variation[12] = {0}; // Numarul de variatii al fiecarui pin 
int oldstate = 0; // Starea precedenta pentru detectia tranzitiilor 
int newState = 0; // Starea curenta pentru detectia tranzitiilor

int noteStatus[12] = {0}; // Starea curenta a fiecarei taste
int old_noteStatus[12] = {0}; // Starea fiecarei taste din interatia precedenta
int octave = 3; // Octava in care ne aflam

int main()
{
    keys.mode(PullNone); // Avem pull-up fizic in circuitul de detectie
    
    while (1) {
        // Reinitializam numarul de tranzitii cu 0
        for(int i=0;i<12;i++) {
            variation[i] = 0;
        }
        
        oldstate = 0;
        timer.start();
        while(timer.read_us() < 100 * 1000) // Masuram pentru 100 ms
        {
            newState = keys.read();
            for(int i=0;i<12;i++){
                if((newState >> i)%2 != (oldstate >> i)%2){ // Fiecare bit corespunde unui pin digital
                    //Daca noua stare difera de cea veche, incrementam numarul de tranzitii
                    variation[i]++;
                }
            }
            oldstate = newState;
        }
        timer.stop();
        timer.reset();
        
        for(int i=0; i < 12; i++){
            // Verificam numarul de tranzitii al fiecarei taste
            if(variation[i] < 5){
                noteStatus[i] = 0;
            }
            else{
                noteStatus[i] = 1;
            }
            // Verificam daca a aparut vreo schimbare in tastele apasate
            if(noteStatus[i] != old_noteStatus[i]){
                if(noteStatus[i] == 1){
                    midi.write(MIDIMessage::NoteOn(i + octave * 12));
                }
                else{
                    midi.write(MIDIMessage::NoteOff(i + octave * 12));
                }
            }
        }
        // Update starii vechi a tastelor
        for(int i=0;i<12;i++){
            old_noteStatus[i] = noteStatus[i];
        }
    }
}
