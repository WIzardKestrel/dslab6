#include <stdlib.h>
#include <stdio.h>

#define null NULL
typedef struct tree_node{
    int id;
    int grade;
    struct tree_node * right;
    struct tree_node * left;
    struct tree_node * parent;
}node;
struct tree_node * parent = null;
int calc_tree(node *);
void find_parent(node *, node *);
void disp_tree(node *, node *);
void disp_inorder(node*);
node * create_node(int, int);
node * insert(node *, int, int);
void prt_lvl(node *, node *, int);


int main(){
    int id, grade;
    scanf("%d", &id);
    node * my_root = null;
    while(id != -1){
        scanf("%d", &grade);
        //TODO: save the grades and ids in a bst
        my_root = insert(my_root, id, grade);
        scanf("%d", &id);
    }
    disp_inorder(my_root);
    node * test = my_root -> left -> left;
    find_parent(test, my_root);
    printf("\n");
    disp_tree(my_root, my_root);
    return 0;
}

node * create_node(int id, int grade){
    node * temp = (node*)malloc(sizeof(struct tree_node));
    temp -> id = id;
    temp -> grade = grade;
    temp -> left = null;
    temp -> right = null;
    return temp;
}

node * insert(node * root, int id, int grade){
    if(root == null){
        return create_node(id , grade);
    }
    if(grade > root -> grade)
        root -> right = insert(root -> right, id, grade);
    else if(grade < root -> grade){
        root -> left = insert(root -> left, id, grade);
    }
    return root;
}
void find_parent(node * child, node * root){
    if(child == root){
        parent = null;
        return;
    }
    if(root != null){
        if(root -> left == child || root -> right == child) {
            //printf("parent is: %d", root -> grade);
            parent = root;
            return;
        }else{
            find_parent(child, root->left);
            find_parent(child, root->right);
        }
    }
}

void disp_inorder(node * root){
    if(root != null){
        disp_inorder(root -> left);
        printf("%d %d\n", root -> id, root -> grade);
        disp_inorder(root -> right);
    }
}

void disp_tree(node * org, node * root){
    int height = calc_tree(root);
    for (int i = 1; i <= height; ++i) {
        prt_lvl(root, org, i);
        if(i != height)
            printf("\n");
    }
}

void prt_lvl(node * root, node * org, int h){
    if(root == null)
        return;
    if(h == 1) {
        printf("%d %d ", root->id, root->grade);
        find_parent(root, org);
        if (parent != null) {
            if (parent == root) {
                //debug
                find_parent(root, org);
            }
            if (parent->grade > root->grade)
                printf("(%d L) ", parent->grade);
            else if (parent->grade < root->grade) {
                printf("(%d R) ", parent->grade);
            } else
                printf("(null) ");
        }
    }else if(h > 1){
        prt_lvl(root -> left, org, h - 1);
        prt_lvl(root -> right, org, h - 1);
    }
}

int calc_tree(node * root){
    if(root == null)
        return 0;
    int left_height = calc_tree(root -> left);
    int right_height = calc_tree(root -> right);
    return (right_height > left_height)? right_height + 1 : left_height + 1;
}



