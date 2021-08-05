#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 20

typedef struct Words
{
    char* slova;
    int *numb;
} Struct_1;

typedef struct Bin_tree
{
    Struct_1 info;
    struct Bin_tree* left, * right;   // pointers on right and left treess
} Struct_2;

Struct_2* tree_head;

char end[] = "#", * p = end;
char alph[] = "abcdefghijklmnopqrstuvwxyz", * p_alph = alph;

int left, right;

char* Input(Struct_1* numb_line, int& counter, int n);                          // for inputing
void New_Vuzol(Struct_1 numb_line, int n);                                      // dyn memory in a tree
void Add(Struct_2* new_elem);                                                   // adding in a tree
void Add_numbers(Struct_2* new_elem);                                           // adding in a tree
void Print(Struct_2* head,int n);                                               // printing of elements (direct bypass)
int Height(Struct_2* head);                                                     // height of the tree
void Clear(Struct_2* head,int n);                                               // clearing the tree

int counting;

int main()
{
    system("chcp 1251");
    system("cls");

    Struct_1 info_1;
    int counter = 1, height, type;

    printf("\n\t--------------------------\n\t|      Binary tree       |\n\t--------------------------\n\t");
    printf("\n\tEnter your type of data ( 0 - numbers, 1 - words ) : ");
    scanf_s("%d", &type);
    printf("\tEnter your data - ( # - end of entering for words, 0 - for numbers)");

        printf("\n\n");
        if(type==1)
        {
            while (1)
            {
                p = Input(&info_1, counter, type);
                if (strcmp(p, end) == 0)
                    break;
                
                New_Vuzol(info_1,type);
            }
        }
        else
        {
            while (1)
            {
                p = Input(&info_1, counter, type);
                if (counting == 0)
                    break;

                New_Vuzol(info_1, type);
            }
        }

        printf("\nDirect bypass of the tree (printing) : - ");
        Print(tree_head,type);
        printf("\n\n");

        height = Height(tree_head);
        printf("Tree height : %d\n\n", height);

        right += 1;         // right part of tree
        left += 1;          // left part of tree

        printf("Height of the left part of tree : %d\nHeight of the right part of tree : %d\n\n", left, right);

        if (left - right >= -1 && left - right <= 1)
            printf("Balanced tree\n");
        else
            printf("NOT Balanced tree\n");

        Clear(tree_head,type);

    return 0;
}

char* Input(Struct_1* numb_line, int& counter, int n)
{
    char temp[LEN];
    int a;
    if(n==1)
    {
        printf("\tWord №%d - ", counter);
        gets_s(temp);
        if (strcmp(temp, end) != 0)
        {
            numb_line->slova = (char*)malloc(strlen(temp) + 1);      //виділення ДП для рядка
            strcpy(numb_line->slova, temp);
            counter++;
            rewind(stdin);                  //очищення буферу
        }
        return temp;
    }
    else
    {
        printf("\tElement №%d - ", counter);
        scanf_s("%d", &a);
        if (a != 0)
        {
            numb_line->numb = (int*)malloc(sizeof(a));      //виділення ДП для рядка
            numb_line->numb = (int*)a;
            counter++;
            rewind(stdin);                  //очищення буферу
        }
        counting = a;
    }
}

void New_Vuzol(Struct_1 numb_line, int n)
{
    Struct_2* elem;
    elem = (Struct_2*)malloc(sizeof(Struct_2));
    elem->info = numb_line;
    elem->left = NULL;
    elem->right = NULL;

    if(n==1)
        Add(elem);
    else
        Add_numbers(elem);
}

void Add(Struct_2* new_elem)
{
    if (tree_head == NULL)
    {
        tree_head = new_elem;
        return;
    }

    Struct_2* temp_head = tree_head;
    int i = 1, l = 1;

    char* p1 = temp_head->info.slova;
    char* p2 = new_elem->info.slova;

    do
    {
        while (1)
        {
            if (*p1 == *p_alph)
                break;
            p_alph++;
            i++;
        }

        p_alph = alph;

        while (1)
        {
            if (*p2 == *p_alph)
                break;
            p_alph++;
            l++;
        }

        p_alph = alph;

        if (l > i)
        {
            if (temp_head->right == NULL) {
                temp_head->right = new_elem;
                return;
            }
            else
                temp_head = temp_head->right;
        }

        else
        {
            if (temp_head->left == NULL) {
                temp_head->left = new_elem;
                return;
            }
            else
                temp_head = temp_head->left;
        }

        p1 = temp_head->info.slova;
        l = i = 1;

    } while (1);
}

void Add_numbers(Struct_2* new_elem)
{
    if (tree_head == NULL)
    {
        tree_head = new_elem;
        return;
    }
    Struct_2* temp_head = tree_head;

    do {
        
        if (new_elem->info.numb < 0)                // new left elem
            if (temp_head->left == NULL) {
                temp_head->left = new_elem;         // left leaf
                return;
            }
            else
                temp_head = temp_head->left;
        else                                        // new right elem
            if (temp_head->right == NULL) {
                temp_head->right = new_elem;        // right leaf
                return;
            }
            else
                temp_head = temp_head->right;
    } while (1);
}

void Print(Struct_2* head, int n)
{
    if(n==1)
    {
        if (head)
        {
            printf("%s - ", head->info.slova);
            Print(head->left,n);
            Print(head->right,n);
        }
    }
    else
    {
        if (head)
        {
            printf("%d - ", head->info.numb);
            Print(head->left,n);
            Print(head->right,n);
        }
    }
}

int Height(Struct_2* head)
{
    if (head == NULL)
        return 0;
    left = Height(head->left);
    right = Height(head->right);
    return left > right ? left + 1 : right + 1;
}

void Clear(Struct_2* head, int n)
{
    if(n==0)
    {
        if (head) {
            Clear(head->left,n);
            Clear(head->right,n);
            free(head);
            head = NULL;
        }
        else
            return;
    }
    else
    {
        if (head) {
            Clear(head->left,n);
            Clear(head->right,n);
            free(head->info.slova);
            free(head);
            head->info.slova = NULL;
            head = NULL;
        }
        else
            return;
    }
}