#include <iostream>
#include <cstdlib>  // untuk malloc dan free
using namespace std;

int main() {
    int *a, *b, *c, **d, *e, *f;

    e = (int*) malloc(3 * sizeof(int));
    f = (int*) malloc(sizeof(int));

    e[0] = 10;
    e[1] = 20;
    e[2] = 30;
    *f = 40;

    // Perhatikan urutan assignment!
    a = &e[1];     // a → e[1] = 20
    c = a;         // c → e[1]
    *a = *f;       // e[1] = 40
    d = &a;        // d → a
    b = e;         // b → e[0]
    a = b;         // a → e[0]
    e[0] = *(b + 1);   // e[0] = e[1] = 40
    *(b + 2) = **d;    // e[2] = *a = e[0] = 40

    // OUTPUT
    cout << e[0] << " " << e[1] << " " << e[2] << " "
         << *a << " " << *b << " " << *c << " "
         << **d << " " << *f << endl;

    // DEALLOC
    free(e);
    free(f);

    return 0;
}

