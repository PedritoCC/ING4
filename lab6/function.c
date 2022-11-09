#ifndef __MMU__H__
#define __MMU__H__

#define SIZE 65536

typedef short byte_t;
typedef int address_t;

typedef struct hole {
    address_t adr;
    int size;
    struct hole *next;
    struct hole *prev;
} hole_t;

typedef struct {
    byte_t mem[SIZE];
    hole_t root; // holes list
} mem_t;

// dynamically allocates a mem_t structure and initializes its content
mem_t *initMem(){
    mem_t* memo = (mem_t*) malloc(sizeof(mem_t));
    hole_t* initBlock = (hole_t*) malloc(sizeof(hole_t));

    initBlock->adr = 1;
    initBlock->size = 0;
    initBlock->next = NULL;
    initBlock->prev = NULL;
    
    memo->root = initBlock;
    memo->last = NULL;
    memo->size = initBlock->size;

    return memo;
}; 

// allocates space in bytes (byte_t) using First-Fit, Best-Fit or Worst-Fit
address_t myAlloc(mem_t *mp, int size){

    bool isAllocated = false, get = false;
    address_t res = -1;
    memoBlock_t* tmp = mp->root;
    memoBlock_t* block = (memoBlock_t*) malloc(sizeof(memoBlock_t));
    while(!get){
        if(!mp->root->next){
            if ((mp->size + size) <= SIZE){
                //Create a new block
               
                block->adr = mp->size + 1;
                mp->root->next = block;
                block->prev = mp->root;

                block->size = size;
                block->next = NULL;
                mp->size += size;

                res = block->adr;
                printf("[myAlloc] Size : %d\n", block->adr);
            }
            else{
                res = -1;
                printf("[myAlloc] Memory is full\n");
            }
            get = true;
        } else{
            if(mp->root->next != NULL ){
                mp->root = mp->root->next;
            } else {
                get = true; // Juste pour sortir du while au cas ou il ne trouve pas de block
            }
        }
    }

    return res;
};

// release memory that has already been allocated previously
void myFree(mem_t *mp, address_t p, int sz){
    bool prev = false, next = false, state = false, get = false;
    
    while(!get){
        if(p == mp->root->adr) {
            if(sz >= mp->root->size){
                printf("[myFree] Taille saisie plus grande que l'objet.\n[myFree] Suppression de tout l'élément...\n");
                if(mp->root->prev){ //Vérification qu'un block précédent existe
                    if(mp->root->next){
                        mp->root->next->prev = NULL;
                    }
                    prev = true;
                }
                
                if(!mp->root->next){ //Vérification qu'un block suivant existe
                    if(mp->root->prev){
                        mp->root->prev->next = NULL;
                    }
                    next = true;
                }
                
                if(prev && next){
                    memoBlock_t *temp;
                    temp= mp->root->next->prev;
                    mp->root->next->prev = mp->root->prev->next;
                    mp->root->prev->next = temp;
                }
                
                
                memoBlock_t* block_temp = (memoBlock_t*) malloc(sizeof(memoBlock_t));
                
                block_temp = mp->root->next;
                
                if(mp->root->next){
                    state = true;
                }
                
                if(state) {
                    get = true;
                    free(block_temp);
                    printf("[myFree] La suppression est un succès!\n\n");
                } else {
                    printf("[myFree] La suppression est un échec.\n\n");
                }
            }
            if(sz < mp->root->size){
                printf("[myFree] Rétrécissement de la mémoire allouée...\n");
                get = true;
                mp->root->size = mp->root->size - sz;
                printf("[myFree] La suppression est un succès!\n\n");
            }
        } else {
            if(mp->root->next != NULL){
                mp->root = mp->root->next;
            }
            else{
                get =  true; // Juste pour sortir du while au cas ou il ne trouve pas de block
            }
        }
    }
};

// assign a value to a byte
void myWrite(mem_t *mp, address_t p, byte_t val){
    bool get = false;
    if(exist(mp, p, 1) == 1){
        while(!get){
             if(mp->root->adr == p){
                 printf("[myWrite] ");
                 for(int i = 0; i < mp->root->size; i++){
                     mp->mem[p + i] = val;
                 }
                 get = true;
             } else {
                 if(mp->root->next != NULL ){
                     mp->root = mp->root->next;
                 } else {
                     get = true; // Juste pour sortir du while au cas ou il ne trouve pas de block
                 }
             }
         }
     }
}

// read memory from a byte
byte_t myRead(mem_t *mp, address_t p){
    bool get = false;
    if(exist(mp, p, 1) == 1){
        while(!get){
            if(mp->root->adr == p){
                printf("[myRead] ");
                for(int i = 0 ; i < mp->root->size; i++){
                    printf("%d", mp->mem[p+ i]);
                }
                get = true;
            } else {
                if(mp->root->next){
                    mp->root = mp->root->next;
                } else {
                    get = true; // Juste pour sortir du while au cas ou il ne trouve pas de block
                }
            }
        }
    }
}

#endif 