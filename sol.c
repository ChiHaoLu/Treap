/* Reference : 
https://algorithmtutor.com/Data-Structures/Tree/Treaps/

DSA 2021/ 6/ 10
HW 3 PROBLEM 5
BY B08303113 ChiHaoLu
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define true 1
#define false 0
#define size 10000000


/*----- Construct the Data Structure -----*/

typedef struct node{
	int key;
	int priority;
	int left;
	int right;
	
}Node;

Node *Forest;
int s = 0;
int total = 0;

/*----- Construct the based function Split and Merge -----*/

void SPLIT(int root, int k, int *l_root, int *r_root){
	if(root == 0){
		*l_root = 0;
		*r_root = 0;
	}
	else{
		if(Forest[root].key <= k){
			*l_root = root;
			SPLIT(Forest[root].right, k, &Forest[root].right, r_root);
		}
		else{
			*r_root = root;
			SPLIT(Forest[root].left, k, l_root, &Forest[root].left);		
		}		
	}
}

int MERGE(int a, int b){
	if(a == 0){
		return b;
	}
	if(b == 0){
		return a; 
	}

	if(Forest[a].priority > Forest[b].priority){
		Forest[a].right = MERGE(Forest[a].right, b);
		return a;
	}
	else if(Forest[a].priority == Forest[b].priority){
		if(Forest[a].key < Forest[b].key){
			Forest[a].right = MERGE(Forest[a].right, b);
			return a;
		} 
		else{
			Forest[b].left = MERGE(a, Forest[b].left);
			return b;			
		}
	}
	else{
		Forest[b].left = MERGE(a, Forest[b].left);
		return b;
	}
}

/*----- Construct the Insert Function -----*/

int NewNode(int p, int k){
	
	total++;
	int root = total; 
	Forest[root].key = k;
	Forest[root].priority = p;
	Forest[root].left = 0;
	Forest[root].right = 0;
	
	return root;
}

void INSERTION(int *root, int p, int k){
	
	int a = 0;
	int b = 0;
	
	SPLIT(*root, k, &a, &b);
	*root = MERGE(MERGE(a, NewNode(p, k)), b);
}

void inorderTravel_insertion(int root, int k){
	
	if(root == 0){
		return;
	} 
	
	if(Forest[root].key > k){
		Forest[root].key++;
	}
	
	inorderTravel_insertion(Forest[root].left, k);
	inorderTravel_insertion(Forest[root].right, k);
}

/*----- Construct the Delete Function -----*/

void DELETION(int k){
	
	int a = 0;
	int b = 0;
	int c = 0;
	
	SPLIT(s, k, &a, &c);
	SPLIT(a, k - 1, &a, &b);
	b = MERGE(Forest[b].left, Forest[b].right);
	s = MERGE(MERGE(a, b), c);
	
}

void inorderTravel_deletion(int root, int k){
	
	if(root == 0){
		return;
	}

	if(Forest[root].key > k){
		Forest[root].key -= 1;
	}
	
	inorderTravel_deletion(Forest[root].left, k);
	inorderTravel_deletion(Forest[root].right, k);
}

/*----- Construct the Reverse Function -----*/

void REVERSE(int l, int r){
	
	int a = 0;
	int b = 0;
	int c = 0;
	int temp = 0;
	
	SPLIT(s, l - 1, &a, &c);
	SPLIT(c, r, &b, &c);
	
	inorderTravel_reverse(b, &temp, l, r);
	
	s = MERGE(MERGE(a, temp), c);
}

void inorderTravel_reverse(int root, int* final, int l, int r){

	if(root == 0){
		return;
	}
	
	Forest[root].key = r - (Forest[root].key - l);
	INSERTION(final, Forest[root].priority, Forest[root].key);
	
	inorderTravel_reverse(Forest[root].left, final, l, r);
	inorderTravel_reverse(Forest[root].right, final, l, r);
	
}

/*----- Construct the Increase Function -----*/

void INCREASE(int l, int r, int p){
	
	int a = 0;
	int b = 0;
	int c = 0;
	int temp = 0;
	
	SPLIT(s, l - 1, &a, &c);
	SPLIT(c, r, &b, &c);
	
	inorderTravel_increase(b, &temp, p);
	
	s = MERGE(MERGE(a, temp), c);
}

void inorderTravel_increase(int root, int* final, int p){
	
	if(root == 0){
		return;
	}
	
	Forest[root].priority += p;
	INSERTION(final, Forest[root].priority, Forest[root].key);
		
	inorderTravel_increase(Forest[root].left, final, p);
	inorderTravel_increase(Forest[root].right, final, p);
}

/*----- Construct the Query and Testing Print Function -----*/

void QUERY(int l, int r){

	int looker = s;
	
	while(1){
		if(Forest[looker].key < l){
			if(Forest[looker].right == 0){
				break;
			}
			looker = Forest[looker].right;
		}
		else if(Forest[looker].key > r){
			if(Forest[looker].left == 0){
				break;
			} 
			looker = Forest[looker].left;
		}
		else{
			printf("%d", Forest[looker].priority);
			break;
		}
	}	
}

void inorder(int root){
    if (root){
        inorder(Forest[root].left);
        int temp;
        printf("key: %d  | priority: %d ", Forest[root].key, Forest[root].priority);
        if (Forest[root].left){
        	temp = Forest[root].left;
        	printf(" | left child: %d", Forest[temp].key);
		}
        	
        if (Forest[root].right){
        	temp = Forest[root].right;
            printf(" | right child: %d", Forest[temp].key);
		}

        printf("\n");
        inorder(Forest[root].right);
    }
}

/*----- Construct the Main Function -----*/

int main(){
	
	int N = 0;
	int Q = 0;
	int operation = 0;
	int i;
	int l, r, p, k;
	Forest = (Node*)malloc(size * sizeof(Node));
	
	scanf("%d", &N);
	scanf("%d", &Q);
	
	for(i = 0; i < N; i++){
		scanf("%d", &p);
		INSERTION(&s, p, i + 1);
	}
//	inorder(s);
	
	while(Q--){
		scanf("%d", &operation);
		if(operation == 1){
			scanf("%d", &p);
			scanf("%d", &k);
			inorderTravel_insertion(s, k);
			INSERTION(&s, p, k + 1);
			
//			printf("SUCCESSFULLY INSERTION\n");
		}
		else if(operation == 2){
			scanf("%d", &k);
			DELETION(k);
			inorderTravel_deletion(s, k);
//			printf("SUCCESSFULLY DELETE\n");
		}
		else if(operation == 3){
			scanf("%d", &l);
			scanf("%d", &r);
			scanf("%d", &p);
			INCREASE(l ,r, p);
//			printf("SUCCESSFULLY INCREASE\n");
		}		
		else if(operation == 4){
			scanf("%d", &l);
			scanf("%d", &r);
			QUERY(l, r);
				if(Q != 0){
					printf("\n");
				}
//			printf("SUCCESSFULLY QUERY\n");
		}
		else if(operation == 5){
			scanf("%d", &l);
			scanf("%d", &r);
			REVERSE(l, r);
//			printf("SUCCESSFULLY REVERSE\n");	
		}
		else{
			int old_key = Forest[s].key;
			DELETION(old_key);
			inorderTravel_deletion(s, old_key);
//			printf("SUCCESSFULLY DELETE\n");
		}
		
//		if(s == 0){
//			printf("tree is nothing\n");
//		}
//		else{
//			printf("the root key: %d, priority: %d\n", Forest[s].key, Forest[s].priority);
//		}
//		inorder(s);


	}
	
	
	return 0;
}
