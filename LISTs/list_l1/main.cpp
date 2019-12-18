#include <iostream>
#include <cstdlib>

using namespace std;

struct tree {
    char info;
    struct tree *left, *right, *parent;
};

struct tree *root;                                                      // начальная вершина дерева
struct tree *createTree(struct tree *root, struct tree *r, char info);  // Create tree
void insertTreeNode(struct tree *node, char ch);                        // Add element
struct tree *deleteElement(struct tree *root, char key);                // Delete element
bool isClean(struct tree *root);                                        // Check for clean
void preorder(struct tree *root);                                       // Print tree

int leftDeep(struct tree *node);                                     // Deep Tree

void postorder(struct tree *root);

int main() {
    char ch;
    root = nullptr;
    do {
        cout << "Enter a character: ";
        cin >> ch;
        if (ch == '.') continue;
        root = createTree(root, root, ch);

    } while (ch != '.');

    int s = 1;
    while (s != 0) {
        cout << "---------------------\n"
             << "1 Add character\n"
             << "2 Delete character\n"
             << "3 Deep of left subtree\n"
             << "4 Is clean\n"
             << "5 Pre-order\n"
             << "6 Post-order\n"
             << "0 Quit\n:";
        cin >> s;
        switch (s) {
            case 1: {
                cout << "Enter character: ";
                char key;
                cin >> key;
                insertTreeNode(root, key);
                preorder(root);
                cout << endl;
                break;
            }
            case 2: {
                cout << "Enter character: ";
                char key;
                cin >> key;
                root = deleteElement(root, key);
                preorder(root);
                cout << endl;
                break;
            }
            case 4: {
                if (isClean(root)) {
                    cout << "Tree is clean!\n";
                } else {
                    cout << "Tree isn't clean!\n";
                }
                break;
            }
            case 3: {
                int deep = leftDeep(root);
                cout << deep << endl;
                break;
            }
            case 5: {
                preorder(root);
                cout << endl;
                break;
            }
            case 6: {
                postorder(root);
                cout << endl;
                break;
            }
            default:
                break;
        }
        cout << endl;
    }
    system("pause");
    return 0;
}

bool isClean(struct tree *root) {
    return root->right == root->left;
}

void insertTreeNode(struct tree *node, char ch) {
    tree *newNode = new tree;
    newNode->info = ch;
    newNode->left = NULL;
    newNode->right = NULL;
    while (node) {
        if (ch <= node->info) {
            if (node->left == NULL) {
                newNode->parent = node;
                node->left = newNode;
                break;
            } else {
                node = node->left;
            }
        } else {
            if (node->right == NULL) {
                newNode->parent = node;
                node->right = newNode;
                break;
            } else {
                node = node->right;
            }
        }
    }
}

struct tree *createTree(struct tree *root, struct tree *r, char info) {
    if (!r) {
        r = (struct tree *) malloc(sizeof(struct tree));
        if (!r) {
            cout << "Not enough memory!" << endl;
            exit(0);
        }
        r->left = NULL;
        r->right = NULL;
        r->info = info;
        if (!root) return r; /* первый вход */
        if (info < root->info) root->left = r;
        else root->right = r;
        return r;
    }
    if (info < r->info) createTree(r, r->left, info);
    else createTree(r, r->right, info);
    return root;
}

struct tree *deleteElement(struct tree *root, char key) {
    struct tree *p, *p2;
    if (!root) return root;
    if (root->info == key) {
        // если есть совпадение
        if (isClean(root)) {
            // это означает пустое дерево
            free(root);
            return NULL;
        } else if (root->left == NULL) {
            // или если одно из поддеревьев пустое
            p = root->right;
            free(root);
            return p;
        } else if (root->right == NULL) {
            p = root->left;
            free(root);
            return p;
        } else {
            // или есть оба поддерева
            p2 = root->right;
            p = root->right;
            while (p->left) p = p->left;
            p->left = root->left;
            free(root);
            return p2;
        }
    }
    if (root->info < key) root->right = deleteElement(root->right, key);
    else root->left = deleteElement(root->left, key);
    return root;
}

void postorder(struct tree *root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    if (root->info) {
        cout << root->info << " -> ";
    }
}

void preorder(struct tree *root) {
    if (!root) return;
    if (root->info) {
        cout << root->info << " -> ";
    }
    preorder(root->left);
    preorder(root->right);
}

int leftDeep(struct tree *node) {
    if (node->left == NULL) {
        return 1;
    } else {
        return 1 + leftDeep(node->left);
    }
}
