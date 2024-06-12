#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ele {
	char name[20];
	char cname[20];
	int price;
} ele;

typedef struct node* nptr;
typedef struct node {
	ele data;
	nptr next;
}node;

void insert(nptr* rptr, ele data) {
	nptr newnode = (nptr)malloc(sizeof(node));
	newnode->next = NULL;
	newnode->data = data;

	if (*rptr == NULL) {
		*rptr = newnode;
		return;
	}

	newnode->next = *rptr;
	(*rptr) = newnode;
}

void selectInsert(nptr* rptr, ele data, char* target) {
	nptr newnode = (nptr)malloc(sizeof(node));
	newnode->next = NULL;
	newnode->data = data;
	nptr root = *rptr;

	while (root != NULL) {
		if (strcmp(target, root->data.name) == 0) {
			break;
		}
		root = root->next;
	}
	
	if (root != NULL) {
		newnode->next = root->next;
		root->next = newnode;
	}
	else {
		printf("Ÿ���� �����ϴ�\n");
	}
}

void printlist(nptr* rptr) {
	printf("The ordered list contains:\n");
	nptr root = *rptr;

	
	while (root != NULL) {
		printf("%p (%s, %s, %d, %p) =>", root, root->data.name, root->data.cname, root->data.price, root->next);
		root = root->next;
	}
	printf("\n\n");
}

nptr reverse(nptr* rptr) {
	nptr root = *rptr;
	nptr newroot = NULL;
	nptr tmp;

	while (root != NULL) {
		tmp = root->next;

		if(newroot==NULL){
			newroot = root;
			root->next = NULL;
		}
		else {
			root->next = newroot;
			newroot = root;
		}

		root = tmp;
	}
	return newroot;
}

void search(nptr* rptr, char* cname) {
	nptr root = *rptr;

	int c = 0;
	while (root != NULL) {
		if (strcmp(cname, root->data.cname) == 0) {
			printf("%s, ", root->data.name);
			c = 1;
		}
		root = root->next;
	}
	if (c == 0) printf("����");
	printf("\n\n");
}

void delete(nptr* rptr, char* name) {
	nptr root = *rptr;

	if (root == NULL) {
		return;
	}
	if (strcmp(name, root->data.name) == 0) {
		if (root->next) {
			*rptr = root->next;
		}
		else *rptr = NULL;
	}

	while (root->next != NULL) {
		if (strcmp(name, root->next->data.name) == 0) {
			break;
		}
		root = root->next;
	}
	if (root->next == NULL) {
		return;
	}

	nptr tmp = root->next;
	root->next = root->next->next;
	free(tmp);
}





int cmp(const void* a, const void* b) {
	ele aa = *(ele*)a;
	ele bb = *(ele*)b;

	return aa.price - bb.price;
}

int main() {
	FILE* fp = fopen("input4.txt", "r");
	nptr root = NULL;

	char name[20];
	char cname[20];
	int price;
	while (fscanf(fp, "%s %s %d", name, cname, &price) != EOF) {
		ele tmp;
		strcpy(tmp.name, name);
		strcpy(tmp.cname, cname);
		tmp.price = price;

		insert(&root, tmp);
	}

	printf("������ ���\n");
	printlist(&root);

	printf("�����̸��� �Է��ϼ��� : ");
	scanf("%s", cname);
	search(&root, cname);

	char target[20];
	printf("������ �����ϱ� ���� ������ ��ġ, ������ ��¡ ������ ������ ���� �Է��ϼ��� : \n");
	printf("(���� ���� ������ 600)\n");
	scanf("%s %s %s %d", target, name, cname, &price); //�� �ƺ�ī�� �±� 650
	ele tmp;
	strcpy(tmp.name, name);
	strcpy(tmp.cname, cname);
	tmp.price = price;
	selectInsert(&root, tmp, target);
	printlist(&root);


	printf("������ ���� ������ ������ ���� �Է��ϼ��� : \n");
	printf("(��)\n");
	scanf("%s", target);
	delete(&root, target);
	printlist(&root);

	printf("������ ���\n");
	nptr rvs = reverse(&root); 
	printlist(&rvs);
}