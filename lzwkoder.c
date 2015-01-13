
#include <stdio.h>
#include <stdlib.h>
#define ALPH_SIZE 256

FILE *writer;
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
	for (int i=0; i<ALPH_SIZE; i++) {
		struct trie_node *q = create_node();
		q->index = counter;
		q->value = (char) i;
        trie_root->link[counter] = q;
        counter++;
    }
}


void get_input(const char * argv[])
{
	char character;
    
	struct node *walker, *new;
	walker = root;
    
	FILE *f;
	f = fopen(argv[1], "r");
	
	if( f == NULL ) {
    	perror("Error while opening the file.\n");
     	exit(EXIT_FAILURE);
   	}
   	else {
   		while ((character = fgetc(f)) != EOF) {
   			new = (struct node *) malloc( sizeof(struct node) );
   			new->next = NULL;
   			walker->character = character;
   			walker->next = new;
   			walker = walker->next;   		}
   	}
    walker = NULL;
   	fclose(f);
}


void add_word(struct trie_node *monkey, struct node *walker, int i)
{
    monkey->link[i] = create_node();
    monkey->link[i]->value = walker->character;
    monkey->link[i]->index = counter;
    counter++;
    fwrite(&monkey->index, sizeof(unsigned short), 1, writer);
    //printf("%hu ", monkey->index);
}


void code()
{
    //get_input();
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
					fwrite(&monkey->link[i]->index, sizeof(unsigned short), 1, writer);
					//printf("%hu ", monkey->link[i]->index);
					return;
				}
			}
			else
                i++;
		}
        add_word(monkey, walker, i);
		monkey = trie_root;
	} while (walker->next != NULL && walker->next->character != '\0');
	for (int i = 0 ; i < ALPH_SIZE; i++){
		if (monkey->link[i]->value == walker->character) {
			fwrite(&monkey->link[i]->index, sizeof(unsigned short), 1, writer);
			//printf("%hu ", monkey->link[i]->index);
			return;
		}
	}
}


int main(int argc, const char * argv[])
{
    root = (struct node *) malloc( sizeof(struct node) );
    root->next = NULL;
    get_input(argv);
    
    writer = fopen(argv[2], "wb");
    
    code();
    
    fclose(writer);
    
    return 0;
}