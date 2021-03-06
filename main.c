/*to get very tired of sitting by her sister on the bank, and of having nothing to do*/

/*---------------------- Declaration Space -----------------------*/

#include <stdio.h>
#include <stdlib.h>

/*---------------------- Structures Space ------------------------*/

typedef struct Stock {
	int Letter;
	int Occurence;
	char Binary[8];
	struct Stock* next;
}Stock;

typedef struct Node{
    int data;
	char code[20];
    struct Node* left;
    struct Node* right;
	struct Node* parent;
}Node;

typedef Stock* Library;

typedef Node* Tree;

/*----------------------------------------------------------------*/

/*---------------------- Functions Space -------------------------*/

Library create_Library(int let, int occu, char p_binary[8]) {
	Library new_lib;
	new_lib = (Library)malloc(sizeof(Stock));
	new_lib->Letter = let;
	new_lib->Occurence = occu;
	for (int i = 0 ; i < 8 ; i++) {
    	new_lib->Binary[i] = p_binary[i];
	}
	new_lib->next = NULL;
	return new_lib;
}

Tree create_node(){
    //printf("In Create Node Function\n\n");
    Tree tr = malloc(sizeof(*tr));

	if (tr == NULL) {
		fprintf(stderr, "Erreur allocation memoire.\n");
		exit(EXIT_FAILURE);
	}

	tr->left = NULL;
	tr->right = NULL;
	tr->parent = NULL;

	return tr;
}

/*void change_in_lib(Library* lib, int let, int occu, char p_binary[8]) {
	Library temp = *lib;
	temp->Letter = let;
	temp->Occurence = occu;
	for (int i = 0 ; i <= 7 ; i++)
				temp->Binary[i] = p_binary[i];
}*/

void add_in_Library(Library* currentLib, Library new_el) {

	Library temp = *currentLib;
	if (*currentLib == NULL) {
		*currentLib = new_el;
		return;
	}
	while (temp != NULL) {
		if (temp->Letter == new_el->Letter) {
			temp->Occurence += 1;
			return;
		} 
		if (temp->next == NULL) {
			temp->next = new_el;
			return;
		}
		temp = temp->next;
	}
}

void translate_text_to_binary(Library* currentLib) {

	FILE *fic = fopen("Alice.txt", "r");

	int letter = 0;
	char binary[8];

	if (fic == NULL) 
		exit(1);

	while((letter = fgetc(fic)) != EOF) {

		int find_binary = letter;

		for(int j=7 ; j >= 0 ; j--)
	    {
	    	int power = 1;
	    	for (int i = 1 ; i <= j; i++) {
	    		power *= 2;
	    	}
		    if(find_binary - power >= 0) {
			    binary[7 - j] = '1';
			    find_binary = find_binary - power;
		    } else {
			    binary[7 - j] = '0';
		    }	
	    }

	    add_in_Library(currentLib, create_Library(letter, 1, binary));
	}

	fclose(fic);
}

void nb_charact_in_file(Library* currentLib) {
	FILE *fic = fopen("Alice.txt", "r");
	
	int letter = 0;

	int count_fic = 0;
	int count_out = 0;

	if (fic == NULL) 
		exit(1);

	while((letter = fgetc(fic)) != EOF) {
		count_fic += 1;
	}
	fclose(fic);
}

void min_in_library(Library* currentLib) {

	Library loop = *currentLib;
	int temp_Letter, temp_next_Letter;
	int temp_Occurence, temp_next_Occurence;
	char temp_Binary[8], temp_next_Binary[8];

	if (*currentLib == NULL)
		exit(1);

	while (loop != NULL) {
		Library temp = loop;
		while (temp != NULL) {
			if (temp->Occurence < loop->Occurence) {

				temp_next_Letter = temp->Letter;
				temp_next_Occurence = temp->Occurence;
				for (int i = 0 ; i < 8 ; i++) {
			    	temp_next_Binary[i] = temp->Binary[i];
				}

				temp->Letter = loop->Letter;
				temp->Occurence = loop->Occurence;
				for (int i = 0; i < 8; i++) {
					temp->Binary[i] = loop->Binary[i];
				}

				loop->Letter = temp_next_Letter;
				loop->Occurence = temp_next_Occurence;
				for (int i = 0; i < 8; i++) {
					loop->Binary[i] = temp_next_Binary[i];
				}
			}
			temp = temp->next;
		}
		loop = loop->next;
	}
}

Tree join_node(Tree tr, Library moment) {

	Tree tempTree = NULL;
	Tree tempTree2 = NULL;

	tempTree = create_node();
	tempTree2 = create_node();

	tempTree->data = tr->data + moment->Occurence;
	tr->parent = tempTree;
	tempTree->right = tr;
	tempTree2->data = moment->Letter;
	tempTree2->parent = tempTree;
	tempTree->left = tempTree2;

	return tempTree;
}

Tree huffman_tree(Library* lib) {

	Library temp = *lib;
	Tree tr = NULL;
	Tree tempTree = NULL;

	if (*lib == NULL)
		return tr;

	while (temp != NULL) {
		if (tr == NULL){
			tr = create_node();
			tempTree = create_node();
			tr->data = temp->Occurence;
			tempTree->data = temp->Letter;
			tempTree->parent = tr;
			tr->right = tempTree;
		} else {
			tr = join_node(tr, temp);
		}
		temp = temp->next;
	}
	return tr;
}

void create_dico(Tree tr, FILE *dic) {

	if (tr == NULL) {
		return;
	}

	/*if (tr->left != NULL) {
		COUNT += '0';
		create_dico(tr->left, dic);
	} 

	if (tr->right != NULL) {
		COUNT += '1';
		create_dico(tr->right, dic);
	} /*else if (COUNT%2 == 0) {
		printf("'%c' : %d\n", tr->data, COUNT);
		fprintf(dic, "'%c' : %d\n", tr->data, COUNT);
	} else {
		printf("'%c' : %d\n", tr->data, COUNT);
		fprintf(dic, "'%c' : %d\n", tr->data, COUNT);
	}*/

	/*if (tr->code == 0) {
		printf("No code\n");
	} else {
		int i = 0;
		while (tr->code[i] != 0)
		{
			printf("%c\n", tr->code[i]);
		}
	}*/
	
	if (tr->left != NULL) {
		/*int i = 0;
		while (tr->code[i] != 0){
			tr->left->code[i] = tr->code[i];
			i++;
		}
		tr->left->code[i+1] = '0';*/
		create_dico(tr->left, dic);
	}

	if (tr->right != NULL) {
		/*int i = 0;
		while (tr->code[i] != 0){
			tr->right->code[i] = tr->code[i];
			i++;
		}
		tr->right->code[i+1] = '1';*/
		create_dico(tr->right, dic);
	} else if (tr->parent != NULL) {
		fprintf(dic, "' %c ' : \n", tr->data);
		/*int i = 0;
		while (tr->code[i] != 0)
		{
			fprintf(dic, "%c\n", tr->code[i]);
		}*/
	} else {
		printf("(%d)\n", tr->data);
	}
}

void print_lib(Library* lib){
	
	FILE *dicCheck = fopen("Dictionary_check.txt", "w+");

	Library temp = *lib;

	if (*lib == NULL)
		return;

	while (temp != NULL) {
		fprintf(dicCheck, "%c (%d) : ", temp->Letter, temp->Occurence);

	    for (int i = 0 ; i <= 7 ; i++) {
	    	fprintf(dicCheck, "%c", temp->Binary[i]);
	    }

	    fprintf(dicCheck, "\n");
		temp = temp->next;
	}

	fclose(dicCheck);
}

/*----------------------------------------------------------------*/

/*---------------------------- Main ------------------------------*/

int main() {

	FILE *dic = fopen("Dictionary.txt", "w+");

	Library lib = NULL;
	Tree Huffman = NULL;

	translate_text_to_binary(&lib);

	//nb_charact_in_file(&lib);

	min_in_library(&lib);

	Huffman = huffman_tree(&lib);

	create_dico(Huffman, dic);

	fclose(dic);

	print_lib(&lib);

	return 0;
}
