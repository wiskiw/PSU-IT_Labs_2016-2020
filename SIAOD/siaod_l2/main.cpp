#include <iostream>

// ВАРИАНТ 5

using namespace std;

// структура для представления узлов дерева
struct tree {
    double info;
    unsigned char height;
    tree *left = nullptr;
    tree *right = nullptr;
};

tree *root; /* начальная вершина дерева */
int amount = 0;

int max(int a, int b) {
    if (a > b) return a;
    else return b;
}

unsigned char height(tree *p) {
    return p ? p->height : 0;
}

//разница высот
int bfactor(tree *p) {
    return height(p->right) - height(p->left);
}

//исправление высот
void fixheight(tree *p) {
    unsigned char hl = height(p->left);
    unsigned char hr = height(p->right);
    p->height = (hl > hr ? hl : hr) + 1;
}

// правый поворот вокруг p
tree *rotateright(tree *p) {
    tree *q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}

// левый поворот вокруг q
tree *rotateleft(tree *q) {
    tree *p = q->right;
    q->right = p->left;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
}

// балансировка узла p
tree *balance(tree *p) {
    fixheight(p);
    if (bfactor(p) == 2) {
        cout << "------------------------" << endl;
        cout << "Tree has been balanced" << endl;
        cout << "------------------------" << endl;
        if (bfactor(p->right) < 0)
            p->right = rotateright(p->right);
        return rotateleft(p);
    }
    if (bfactor(p) == -2) {
        cout << "------------------------" << endl;
        cout << "Tree has been balanced" << endl;
        cout << "------------------------" << endl;
        if (bfactor(p->left) > 0)
            p->left = rotateleft(p->left);
        return rotateright(p);
    }
    return p; // балансировка не нужна
}

// поиск узла с минимальным ключом в дереве p
tree *findmax(tree *p) {
    return p->right ? findmax(p->right) : p;
}

// удаление узла с минимальным ключом из дерева p
tree *removemax(tree *p) {
    if (!p->right) {

        return p->left;
    }

    p->right = removemax(p->right);
    return balance(p);
}

// удаление ключа k из дерева p
tree *remove(tree *p, double info) {
    if (!p) return 0;
    if (info < p->info)
        p->left = remove(p->left, info);
    else if (info > p->info)
        p->right = remove(p->right, info);
    else //  k == p->key
    {
        tree *l = p->left;
        tree *r = p->right;

        amount--;
        free(p);
        if (!l) return r;

        tree *max = findmax(l);

        // левый главенствующий
        max->left = removemax(l);
        max->right = r;


        return balance(max);
    }
    return balance(p);
}

// вставка ключа k в дерево с корнем p
tree *insert(tree *p, double info) {
    if (!p) {
        amount++;
        tree *temp = (tree *) malloc(sizeof(tree));
        temp->height = 1;
        temp->info = info;
        temp->left = nullptr;
        temp->right = nullptr;
        return temp;
    }
    if (info < p->info)
        p->left = insert(p->left, info);
    else
        p->right = insert(p->right, info);
    return balance(p);
}

void preOrderTravers(tree *root) {
    if (root) {
        // " height = " << (int) root->height <<
        cout << "value = " << root->info << endl;
        preOrderTravers(root->left);
        preOrderTravers(root->right);
    }
}

int cleanbuf() {
    char one;
    int loop = 0;
    while ((one = getchar()) != '\n') {
        loop++;
        continue;
    }
    if (loop > 0) return loop;
    return 0;
}

double inputd(double *s) {
    while (1) {
        if (!(scanf("%lf", &(*s)))) {
            cleanbuf();
            continue;
        }
        if (cleanbuf()) {
            continue;
        }
        if (-9223372036854775807.0 > *s || *s > 9223372036854775807.0) {
            continue;
        }
        return 1;
    }
}

int inputi(int *s) {
    while (1) {
        if (!(scanf("%d", s))) {
            cleanbuf();
            continue;
        }
        if (cleanbuf()) {
            continue;
        }
        if ((int) (-2147483648) > (*s) || (2147483647) < (*s)) {
            continue;
        }
        return 1;
    }
}

int check_for_empting() {
    if (amount == 0) {
        cout << "------------------" << endl;
        cout << "Tree is empty!" << endl;
        cout << "------------------" << endl;
        return 1;
    }
    return 0;
}

void destree(tree *root) {
    if (root != nullptr) {
        destree(root->left);
        destree(root->right);
        free(root);
    }
}

int getWidth(tree *root, int level) {
    if (!root) return 0;
    if (level == 1) return 1;
    else if (level > 1) return getWidth(root->left, level - 1) + getWidth(root->right, level - 1);

}

int getMaxWidth(tree *root) {
    int maxWdth = 0;
    int i;
    int width = 0;
    int h = height(root);
    for (i = 1; i <= h; i++) {
        width = getWidth(root, i);
        if (width > maxWdth)
            maxWdth = width;
    }
    return maxWdth;
}

int main() {
    bool created = false;
    double s = 0;
    int c = 0;
    double el = 0;
    int o = 0;
    while (1) {
        cout << endl;
        cout << "--------------------------------" << endl;
        cout << "1. Creating a tree" << endl;
        cout << "2. Adding element" << endl;
        cout << "3. Removing element" << endl;
        cout << "4. Destruction of the tree" << endl;
        cout << "5. Check for emptiness" << endl;
        cout << "6. Output of elements" << endl;
        cout << "7. Depth of the right subtree" << endl;
        cout << "0. Exit" << endl;

        cout << endl << "Select option: " << endl;
        inputi(&o);
        system("cls");
        switch (o) {
            case 1: {
                if (created) {
                    cout << "Tree already created!" << endl;
                    break;
                }
                root = nullptr;
                //root->left = nullptr;
                //root->right = nullptr;
                created = true;
                cout << "Tree created!" << endl;
                break;
            }
            case 2: {
                if (!created) {
                    cout << "------------------" << endl;
                    cout << "Tree not created!" << endl;
                    cout << "------------------" << endl;
                    break;
                }
                /*
                cout << "Enter amount of numbers: ";
                inputi(&c);
                while (c--) {
                 */
                cout << "Enter number: ";
                inputd(&s);
                root = insert(root, s);
                //}
                break;
            }
            case 3: {
                if (check_for_empting()) break;
                cout << "Enter value of element: ";
                inputd(&el);
                int am = amount;
                root = remove(root, el);
                if (am == amount) {
                    cout << "------------------" << endl;
                    cout << "Element is not found!" << endl;
                    cout << "------------------" << endl;
                }
                break;
            }
            case 4: {
                if (!created) {
                    cout << "------------------" << endl;
                    cout << "Tree not created!" << endl;
                    cout << "------------------" << endl;
                    break;
                }
                created = false;
                destree(root);
                amount = 0;
                cout << "------------------" << endl;
                cout << "Tree destroyed!" << endl;
                cout << "------------------" << endl;
                break;
            }
            case 5: {
                if (created) {
                    cout << "----------------------------" << endl;
                    cout << "Tree created!" << endl;
                    if (!amount) cout << "Tree does not have elements." << endl;
                    else cout << "Tree has " << amount << " element(s)." << endl;
                    cout << "----------------------------" << endl;
                } else {
                    cout << "------------------" << endl;
                    cout << "Tree not created!" << endl;
                    cout << "------------------" << endl;
                }
                break;
            }
            case 6: {
                if (!created) {
                    cout << "------------------" << endl;
                    cout << "Tree not created!" << endl;
                    cout << "------------------" << endl;
                    break;
                }
                if (check_for_empting()) break;
                cout << "------------------" << endl;
                preOrderTravers(root);
                cout << "------------------" << endl;
                break;
            }
            case 7: {
                if (!created) {
                    cout << "------------------" << endl;
                    cout << "Tree not created!" << endl;
                    cout << "------------------" << endl;
                    break;
                }
                if (check_for_empting()) break;
                int depth = 0;
                tree *branchToCheck = root;
                for (; branchToCheck->right != nullptr; ++depth){
                    branchToCheck = branchToCheck->right;
                }
                cout << "------------------" << endl;
                cout << "Depth of the right subtree: " << depth << endl;
                cout << "------------------" << endl;
                break;
            }
            case 8:
                cout << "! = " << height(root) << endl;
                break;
            case 0:
                exit(0);
                break;
        }
    }

    return 0;
}