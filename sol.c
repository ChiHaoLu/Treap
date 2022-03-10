/* Reference : 
https://algorithmtutor.com/Data-Structures/Tree/Treaps/
http://sunmoon-template.blogspot.com/2015/01/split-merge-randomized-binary-search.html
B06303131

DSA 2021/ 6/ 10
HW 3 PROBLEM 5
BY B08303113 ChiHaoLu
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define true 1
#define false 0

/*----- Construct the Data Structure -----*/

typedef struct node{
	int size;
	int priority;
	int random;
	int max;
	int reverse_tag;
	int increase_tag;
	struct node* left;
	struct node* right;
	
}Node;


Node* s = NULL;

int Size(Node* root){
	if(root){
		return root->size;
	}
	return 0;
}

int getMAX(Node* root){
	if(root){
		return root->max;
	}
	return -2147483648;
} 

void Down(Node* root);
void Up(Node* root){ // 有可能改變結構的時候
	if(root == NULL){
		return;
	}
	
	root->size = 1;
	root->max = root->priority;
	
	if(root->left){
		Down(root->left);
		if(getMAX(root->left) > getMAX(root)){
			root->max = getMAX(root->left);
		}
		root->size += Size(root->left);
	}
	if(root->right){
		Down(root->right);
		if(getMAX(root->right) > getMAX(root)){
			root->max = getMAX(root->right);
		}
		root->size += Size(root->right);
	}
}

void Down(Node* root){ // 有可能改變max的時候，訪問點的時候 
	if(root == NULL){
		return;
	}
	if(root->reverse_tag == 1){
		
		Node* temp = root->left;
		root->left = root->right;
		root->right = temp;
		
		if(root->left){
			(root->left)->reverse_tag ^= 1;
		}
		if(root->right){
			(root->right)->reverse_tag ^= 1;
		}
		root->reverse_tag = 0;
	}
	
	if(root->increase_tag){
		
		root->priority += root->increase_tag;
		root->max += root->increase_tag;
		
		if(root->left){
			(root->left)->increase_tag += root->increase_tag;
		}
		if(root->right){
			(root->right)->increase_tag += root->increase_tag;
		}
		
		root->increase_tag = 0;
	}
	
}

/*----- Construct the based function Split and Merge -----*/

void SPLIT(Node* root, int k, Node **l_root, Node **r_root){
	if(root == NULL){
		*l_root = NULL;
		*r_root = NULL;
	}
	else{
		Down(root);
		if(Size(root->left) < k){
			*l_root = root;
			SPLIT(root->right, k - Size(root->left) - 1, &((*l_root)->right), &(*r_root));
		}
		else{
			*r_root = root;
			SPLIT(root->left, k, &(*l_root), &((*r_root)->left));		
		}
		Up(root);
	}
}

Node* MERGE(Node* a, Node* b){
	if(a == NULL){
		return b;
	}
	if(b == NULL){
		return a; 
	}
	if(b->random < a->random){
		Down(a);
		a->right = MERGE(a->right, b);
		Up(a);
		return a;
	}
	else{
		Down(b);
		b->left = MERGE(a, b->left);
		Up(b);
		return b;
	}
}

/*----- Construct the Insert Function -----*/

Node* NewNode(int p){
	
	Node* root = (Node*)malloc(sizeof(Node)); 
	root->priority = p;
	root->size = 1;
	root->max = p;
	root->random = rand();
	root->reverse_tag = 0;
	root->increase_tag = 0;
	root->left = NULL;
	root->right = NULL;
	
	return root;
}

void INSERTION(Node **root, int p, int k){
	
	Node* a = NULL;
	Node* b = NULL;
	
	SPLIT(*root, k, &a, &b);
	*root = MERGE(MERGE(a, NewNode(p)), b);
	
}

/*----- Construct the Delete Function -----*/

void DELETION(int k){
	
	Node* a = NULL;
	Node* b = NULL;
	Node* c = NULL;
	
	if(s == NULL){
		return;
	}
	
	SPLIT(s, k, &a, &c);
	SPLIT(a, k - 1, &a, &b);
	Down(b);
	s = MERGE(a , c);
}

/*----- Construct the Reverse Function -----*/

void REVERSE(int l, int r){
	
	if(l == r){
		return;
	}
	
	Node* a = NULL;
	Node* b = NULL;
	Node* c = NULL;
	
	SPLIT(s, l - 1, &a, &c);
	SPLIT(c, r - (l - 1), &b, &c);
	
	b->reverse_tag = 1;
	
	s = MERGE(MERGE(a, b), c);
}

/*----- Construct the Increase Function -----*/

void INCREASE(int l, int r, int p){
	
	Node* a = NULL;
	Node* b = NULL;
	Node* c = NULL;
	
	SPLIT(s, l - 1, &a, &c);
	SPLIT(c, r - (l - 1), &b, &c);
	
	b->increase_tag += p;
	
	s = MERGE(MERGE(a, b), c);	
}

/*----- Construct the Query and Testing Print Function -----*/

void QUERY(int l, int r){

	Node* looker = s;
	
	if(s == NULL){
		return;
	}
	Node* a = NULL;
	Node* b = NULL;
	Node* c = NULL;
	
	SPLIT(s, l - 1, &a, &c);
	SPLIT(c, r - (l - 1), &b, &c);
	
	printf("%d", b->max);

	s = MERGE(MERGE(a, b), c);

}

/* deletion max */

void DELETION_max(){
	
	Down(s);
	int MAX = s->max;
	int pos = 1;
	Node *current = s;
	while(1){
		Down(current->left);
		Down(current->right);
		if(getMAX(current->left) != MAX && current->priority == MAX){
			// find the max
			break;
		}
		else{
			if(getMAX(current->left) == MAX){
				current = current->left;
			}
			else{
				pos += (Size(current->left) + 1);
				current = current->right;
			}
		}
		
	}
	
	// get the final pos
	pos += Size(current->left);
	
	DELETION(pos);
	return;
}
 

/*----- Construct the Main Function -----*/

int main(){
	
	int N = 0;
	int Q = 0;
	int operation = 0;
	int i;
	int l, r, p, k;
	srand(20000102);
	
	scanf("%d", &N);
	scanf("%d", &Q);
	
	for(i = 0; i < N; i++){
		scanf("%d", &p);
		INSERTION(&s, p, i);
	}
	
	while(Q--){
		scanf("%d", &operation);
		if(operation == 1){
			scanf("%d", &p);
			scanf("%d", &k);
			INSERTION(&s, p, k);
		}
		else if(operation == 2){
			scanf("%d", &k);
			DELETION(k);
		}
		else if(operation == 3){
			scanf("%d", &l);
			scanf("%d", &r);
			scanf("%d", &p);
			INCREASE(l ,r, p);
		}		
		else if(operation == 4){
			scanf("%d", &l);
			scanf("%d", &r);
			QUERY(l, r);
			if(Q != 0){
				printf("\n");
			}
		}
		else if(operation == 5){
			scanf("%d", &l);
			scanf("%d", &r);
			REVERSE(l, r);
		}
		else{
			if(s != NULL){
				DELETION_max();				
			}
		}
	}
	
	
	return 0;
}
