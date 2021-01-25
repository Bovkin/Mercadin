/* 

AUTHOR: ELTON IGOR CUNHA PEREIRA
GOAL: LEARNING

Header about products

*/

#define MAX_DESCR 50
#define MAX 200

typedef struct{
    int id;
    char product[MAX_DESCR + 1];
    double price;
    int quantity;
} product;

typedef struct products{

    product prd;
    struct products *nextProduct;

} products;

void readsFile(products *list);
products *allocatesNewProduct(product component);
void editProductId(product component, products *list, int id);
void editProductName(product component, products *list, char *name);
void registerProduct(product component, products *list);
void printList(products *list);
void printProductsById(products *list, int id);
void printProductsByName(products *list, char *prod);
void saveProductsToFile(products *list);