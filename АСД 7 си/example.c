typedef	int BaseType;

typedef struct Element {
    BaseType data;
    struct Element *LSon;
    struct Element *RSon;
} element;
typedef element* PtrEl;
typedef PtrEl *Tree;

int main() {
    Tree example_tree;
}