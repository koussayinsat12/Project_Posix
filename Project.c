#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define NBRE_METROS 10
#define NBRE_SEGMENTS 5
#define MR1_SIZE (sizeof(MR1) / sizeof(MR1[0]))
#define MR2_SIZE (sizeof(MR2) / sizeof(MR2[0]))
#define MR3_SIZE (sizeof(MR3) / sizeof(MR3[0]))

/* Dictionnaire contenant tous les segments en exclusion mutuelle avec leur sémaphore correspondant */
typedef struct KeyValuePair {
    const char *key;
    int value;
} KeyValuePair;

struct KeyValuePair MR1[] = {
    {"A --- B", 0},
    {"B --- C", 1},
    {"C --- D", 2}
};

struct KeyValuePair MR2[] = {
    {"F --- B", 3},
    {"B --- A", 0}
};

struct KeyValuePair MR3[] = {
    {"E --- C", 0},
    {"C --- B", 1}
};

typedef struct Donnees_Metro {
    int ID;
    KeyValuePair *keyValuePairs;
    int size;
} Donnees_Metro;

sem_t sem_segments[NBRE_SEGMENTS];

void acceder_au_segment(int segment, const char *currentKey, int ID_metro) {
    sem_wait(&sem_segments[segment]);
    printf("Le metro no %d entre dans le segment %s\n", ID_metro, currentKey);
}

void quitter_le_segment(int segment, const char *currentKey, int ID_metro) {
    printf("Le metro no %d quitte le segment %s\n", ID_metro, currentKey);
    sem_post(&sem_segments[segment]);
}

void* metro(void* infos_metro) {

    int ID = ((Donnees_Metro*)infos_metro)->ID;
    KeyValuePair* currentPair = ((Donnees_Metro*)infos_metro)->keyValuePairs;
    int currentSize = ((Donnees_Metro*)infos_metro)->size;
printf("Le metro no %d va commence son trajet %c --- %c. Bon voyage ! :)\n", ID,currentPair[0].key[0],currentPair[currentSize-1].key[6]);
    for (int i = 0; i < currentSize; i++) {
        const char *currentKey = currentPair[i].key;
        int currentValue = currentPair[i].value;
        acceder_au_segment(currentValue, currentKey, ID);
        usleep(6000000); // 6 secondes -> 6 minutes
        quitter_le_segment(currentValue, currentKey, ID);
    }
printf("Le metro no %d a termine son trajet. Bonne journee ! :)\n", ID);
    return NULL;
}

int main() {
    pthread_t metros[NBRE_METROS];

    for (int i = 0; i < NBRE_SEGMENTS; i++)
        sem_init(&sem_segments[i], 0, 1);

    for (int i = 0; i < NBRE_METROS; i++) {
        Donnees_Metro* infos_metro = (Donnees_Metro*)malloc(sizeof(Donnees_Metro));
        infos_metro->ID = i + 1;

        if (i < NBRE_METROS / 3) {
            infos_metro->keyValuePairs = MR1; /* Les métros 1, 2, 3 utiliseront la ligne de métro MR1 (A ---> D) */
            infos_metro->size = MR1_SIZE;
        } else if (i < 2 * NBRE_METROS / 3) {
            infos_metro->keyValuePairs = MR2; /* Les métros 4, 5, 6 utiliseront la ligne de métro MR2 (F ---> A) */
            infos_metro->size = MR2_SIZE;
        } else {
            infos_metro->keyValuePairs = MR3; /* Les métros 7, 8, 9, 10 utiliseront la ligne de métro MR3 (E ---> C) */
            infos_metro->size = MR3_SIZE;
        }

        pthread_create(&metros[i], NULL, metro, (void*)infos_metro);
    }

    for (int i = 0; i < NBRE_METROS; i++)
        pthread_join(metros[i], NULL);

    return 0;
}
