#include<iostream>
#include<string>
using namespace std;

struct Product {
    int id;
    string name;
    double price;
    int quantity;
};

struct Customer {
    string phone;
    string name;
    long point;
};
// Tạo danh sách liên kết cho Sản phẩm
struct NodeProduct {
    Product product;
    NodeProduct* next;
};
typedef NodeProduct* Storage;

// Tạo danh sách liên kết cho Khách hàng
struct NodeCustomer {
    Customer customer;
    NodeCustomer* next;
};
typedef NodeCustomer* CustomerList;

// Tạo đối tượng Quản lý sản phẩm, khai báo các thuộc tính và phương thức hàm(thêm, tìm kiếm, cập nhật, xóa) và khởi tạo danh sách liên kết rỗng
class ProductManager {
private:
    Storage S;
    int sizeItem;
public:
    ProductManager() : S(NULL), sizeItem(0) {}
    void addProduct();
    int getSizeItem() const { return sizeItem; }
    NodeProduct* findProductById(int id);
    void updateProduct();
    void deleteProduct();
    void displayProducts() const;
};
// Hàm thêm sản phẩm vào kho
void ProductManager::addProduct() {
    bool check;
    char c;
    do {
        NodeProduct* P = new NodeProduct;
        cout << "Enter Product ID: ";
        cin >> P->product.id;
        cin.ignore(); 
        cout << "Enter Product Name: ";
        getline(cin, P->product.name);
        cout << "Enter Product Price: ";
        cin >> P->product.price;
        cout << "Enter Product Quantity: ";
        cin >> P->product.quantity;
        P->next = NULL;

        if (S == NULL) {
            S = P;
        } else {
            NodeProduct* R = S;
            while (R->next != NULL) R = R->next;
            R->next = P;
        }
        sizeItem++;

        cout << "Add more products to the storage? (y/n): ";
        cin >> c;
        if (c == 'y') check = true; 
        else check = false;
        cin.ignore();
    } while (check);
}
/* Chạy thử OK
    int main() {
    ProductManager productManager;
    productManager.addProduct();
    cout << "Total Items: " << productManager.getSizeItem() << endl;
    return 0;
}*/

// Hàm tìm kiếm sản phẩm bằng ID và trả về địa chỉ sản phẩm đó
NodeProduct* ProductManager::findProductById(int id) {
    NodeProduct* P;
    P = S;
    while(P!=NULL) {
        if (P->product.id==id) return P;
        else P = P->next;
    }
    return NULL;
}
// Hàm cập nhật các sản phẩm muốn thay đổi(tên, giá, số lượng)_ID không cố định 
void ProductManager::updateProduct() {
    char check;
    do {
        int id;
        cout << "Enter the product ID to update: ";
        cin >> id;
        cin.ignore();
        NodeProduct* Q;
        Q = findProductById(id);
        if (Q==NULL) {
            cout << "This product is not available!" << endl;
        } else {
            cout << "Enter Product Name: ";
            getline(cin, Q->product.name);
            cout << "Enter Product Price: ";
            cin >> Q->product.price;
            cout << "Enter Product Quantity: ";
            cin >> Q->product.quantity;
        }
        cout << "Update more products in the storage? (y/n): ";
        cin >> check;
    } while (check =='y');
}
// Hàm hiển thị tất cả sản phẩm trong kho
void ProductManager::displayProducts() const {
    NodeProduct* P = S;
    while(P!=NULL) {
        cout << "ID: " << P->product.id << ", Name: " << P->product.name << ", Price: " << P->product.price << ", Quantity: " << P->product.quantity << endl;
        P = P->next;
    }
};


class CustomerManager {
private:
    CustomerList C;
    int sizeList;
public:
    CustomerManager() : C(NULL), sizeList(0) {}
    void addCustomer();
    int getSizeList() const { return sizeList; }
    void updateCustomer(const string& phone, const string& name, long point);
    void deleteCustomer(int id);
    Customer* findCustomerById(int id);
    void displayCustomers() const;
};




class InvoiceManager {
private:
    vector<Invoice> invoices;
    ProductManager& productManager;
    CustomerManager& customerManager;
public:
    InvoiceManager(ProductManager& pm, CustomerManager& cm) : productManager(pm), customerManager(cm) {}
    void createInvoice(int invoiceId, int customerId, const vector<InvoiceDetail>& details);
    void displayInvoices() const;
};
int main(){
	return 0;
    cout << "hello";
}
