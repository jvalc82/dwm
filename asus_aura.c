/* Module to control keyboard lighting for Asus laptops within DWM using
 * asusctl's Aura control module.
 */
#ifdef __ASUS_AURA__


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>


/* Asus Aura keyboard light modes */
typedef enum {
    OFF,
    LOW,
    MED,
    HIGH
} KBLight;


static int get_kblight();
static void set_kblight(const KBLight *);
static void decrease_kblight(const Arg *);
static void increase_kblight(const Arg *);


const char* KBDL_STR[4] = { "OFF", "LOW", "MED", "HIGH" };

int
get_kblight() {
    int s;
    FILE *kb_p;
    KBLight kb_light;


    /* Retrieve current keyboard lighting mode */
    kb_p = popen("/usr/bin/asusctl -k", "r");

    if(kb_p == NULL)
        return -1;


    char *kb_buf = (char *) malloc(_POSIX_PIPE_BUF);

    if(kb_buf == NULL)
        return -1;

    
    if(fgets(kb_buf, _POSIX_PIPE_BUF, kb_p) == NULL)
        return -1;

    s = sscanf(kb_buf, "Current keyboard led brightness: %d", (int *) &kb_light);

    if(!s)
        return -1;
        
    pclose(kb_p);
    free(kb_buf);

    return kb_light;
}


void
set_kblight(const KBLight *kblight) {
    /* Set changed keyboard light */
    char *kbdcmd[]  = { "/usr/bin/asusctl", "-k", KBDL_STR[*kblight], NULL};

    if(fork() == 0) {
        setsid();
        execvp(kbdcmd[0], (char **) kbdcmd);
    }
}


void
decrease_kblight() {
    KBLight curr_kblight = get_kblight();

    if(curr_kblight != OFF) {
        curr_kblight -= 1;
        set_kblight( (const KBLight *) &curr_kblight);
    }
}


void
increase_kblight() {
    KBLight curr_kblight = get_kblight();

    if(curr_kblight != HIGH) {
        curr_kblight += 1;
        set_kblight( (const KBLight *) &curr_kblight);
    } 
}


#endif
