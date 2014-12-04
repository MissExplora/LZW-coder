
#include <stdio.h>
#include <stdlib.h>
#define ALPH_SIZE 256


unsigned short int counter = 0;

struct node {
	char character;
	struct node *next;
};

struct node *root;

struct trie_node {
	unsigned short int index;
	char value;
	struct trie_node *link[ALPH_SIZE];
};

struct trie_node *trie_root = NULL;


struct trie_node *create_node() {
    struct trie_node *q = (struct trie_node*) malloc( sizeof(struct trie_node) );
    for(int x=0 ; x < ALPH_SIZE ; x++)
    q->link[x] = NULL;
    q->index = q->value = -1;
    return q;
}


void start_dictionary()
{
	trie_root = create_node();
    //char bla[5] = {'a', 'b', 'c', 'd'};
	for (int i=32; i<127; i++) {
		struct trie_node *q = create_node();
		q->index = counter;
		q->value = (char) i;
        trie_root->link[counter] = q;
        //printf("%c\n", trie_root->link[counter]->value );
        counter++;
    }
    /*for (int i=0; i<4; i++) {
		struct trie_node *q = create_node();
		q->index = counter;
		q->value = bla[i];
        trie_root->link[counter] = q;
        //printf("%c\n", trie_root->link[counter]->value );
        counter++;
    }*/
    
}


void get_input()
{
	char character;
    
	struct node *walker, *new;
	walker = root;
    
	FILE *f;
	f = fopen("/Users/Dora/Desktop/TINF labos/ulazna", "r");
	
	if( f == NULL ) {
    	perror("Error while opening the file.\n");
     	exit(EXIT_FAILURE);
   	}
   	else {
   		while ((character = fgetc(f)) != EOF) {
   			new = (struct node *) malloc( sizeof(struct node) );
   			new->next = NULL;
   			walker->character = character;
   			//printf("%c ", walker->character);
   			walker->next = new;
   			walker = walker->next;   		}
   	}
     walker = NULL;
    //if (walker->character == '\0')
    //printf("%s", " nooooo ");
    
   	fclose(f);
}

/*void printer()
{
    get_input();
    struct node *walker;
	walker = (struct node *) malloc( sizeof(struct node) );
    for (walker = root; walker->next != NULL; walker=walker->next){
        printf("%c ", walker->character);
        if (walker->character == '\0') {
            printf("%s\n", "krivo");
        }
    }
}
*/

void code()
{
    get_input();
	struct node *walker;
	struct trie_node *monkey;
    
	start_dictionary();
	walker = root;
    monkey = trie_root;
	do {
		int i = 0;
		while ((monkey->link[i] != NULL) && (i < ALPH_SIZE)){
			if (monkey->link[i]->value == walker->character) {
				if (walker->next != NULL && walker->next->character != '\0') {
					walker = walker->next;
					monkey = monkey->link[i];
					i=0;
				}
				else {
					printf("%hu ", monkey->link[i]->index);
					return;
				}
			}
			else
            i++;
		}
		monkey->link[i] = create_node();
		monkey->link[i]->value = walker->character;
		monkey->link[i]->index = counter;
		counter++;
		printf("%hu ", monkey->index);
		monkey = trie_root;
	} while (walker->next != NULL && walker->next->character != '\0');
	for (int i = 0 ; i < ALPH_SIZE; i++){
		if (monkey->link[i]->value == walker->character) {
			printf("%hu ", monkey->link[i]->index);
			return;
		}
	}
    
    
}


int main(int argc, const char * argv[])
{
    root = (struct node *) malloc( sizeof(struct node) );
    root->next = NULL;
    //get_input();
    code();
    //printer();
    
    
    return 0;
}