/***
*
* Programme qui reçoit 5 CTRL-C avant de se stopper
*
*
***/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
void Recuperation(int sig)
{
    static int compt = 0;
    switch (sig) {
    case SIGSEGV: printf("Arrrrrgh, il s'en est fallu de peu\n" );
        /* La seule chose que l'on peut faire ici est de terminer le
         * programme puisqu'on ne sais pas reparer l'erreur. Un simple
         * return provoquerait une boucle
         */
        exit(1);
    case SIGINT:  if (++compt == 5) {
            printf("J'en ai assez!!\n" );
            exit(1);
        }
        else
            printf("OK je recupere le signal SIGINT\n" );
    }
}
int main()
{
    char t[1];
    int i=0;
    signal(SIGSEGV, Recuperation);
    signal(SIGINT,  Recuperation);
    printf("Taper 5 ^C pour arreter le programme ou return pour continuer\n" );
    /* On met le programme en attente : attention, sleep() ne conviendrait pas
     * ici (essayez, vous verrez et lisez la page du manuel de sleep (man 3
     * sleep). */
    getchar();
    /* On provoque un SIGSEGV car on sort du tableau t */
    while(1) t[i++] = '!';
}