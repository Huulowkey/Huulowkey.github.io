#include<iostream>
#include<string>
#include <iomanip>
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
    void filter();
};
// Hàm thêm sản phẩm vào kho
void ProductManager::addProduct() {
    bool check;
    char c;
    do {
        NodeProduct* P = new NodeProduct;
        cout << "ID: ";
        cin >> P->product.id;
        cin.ignore(); 
        cout << "Ten san pham: ";
        getline(cin, P->product.name);
        cout << "Gia ban: ";
        cin >> P->product.price;
        cout << "So luong: ";
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

        cout << "Tiep tuc them san pham? (y/n): ";
        cin >> c;
        if (c == 'y') check = true; 
        else check = false;
        cin.ignore();
    } while (check);
}
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
        cout << "Nhap ID san pham can cap nhat: ";
        cin >> id;
        cin.ignore();
        NodeProduct* Q;
        Q = findProductById(id);
        if (Q==NULL) {
            cout << "Khong tim thay san pham!" << endl;
        } else {
            cout << "Ten san pham: ";
            getline(cin, Q->product.name);
            cout << "Gia ban: ";
            cin >> Q->product.price;
            cout << "So luong: ";
            cin >> Q->product.quantity;
        }
        cout << "Tiep tuc cap nhat? (y/n): ";
        cin >> check;
    } while (check =='y');
}
// Hàm xóa sản phẩm 
void ProductManager::deleteProduct() {
    cout << "Nhan ID san pham can xoa: ";
    int id;
    cin >> id;
    cin.ignore();
    NodeProduct* Q;
    Q = findProductById(id);
    NodeProduct* P = Q;
    if (Q==NULL) cout << "Khong tim thay san pham!";
    if (S==Q && Q->next==NULL) {
        S = NULL;
        delete Q;
    } else {
        if (S==Q) {
            S = Q->next;
            delete Q;
        } else {
            NodeProduct* R = S;
            while (R->next!=Q) R = R->next;
            R->next = Q->next;
            delete Q;
        }
        sizeItem--;
        cout << "Da xoa san pham:  " << P->product.name << endl;
    } 

}
// Hàm hiển thị tất cả sản phẩm hiện có
void ProductManager::displayProducts() const {
    cout << "So loai mat hang:  " << getSizeItem() << endl;
    NodeProduct* P = S;
    cout << left << setw(10) << "ID" << setw(25) << "Ten san pham" << setw(10) << "Gia ban" << setw(10) << "So luong" << endl;
    cout << left << setw(10) << "--------" << setw(25) << "-----------------------" << setw(10) << "--------" << setw(10) << "--------" << endl;
    while(P!=NULL) {
        cout << left << setw(10) << P->product.id << setw(25) << P->product.name << setw(10) << P->product.price << setw(10) << P->product.quantity << endl;
        P = P->next;
    }
};
// Hàm lọc sản phẩm theo ID, tên, khoảng giá
void ProductManager::filter() {
    cout << "1. ID\n2. Ten san pham\n3. Khoang gia\n";
    int a, id;
    cout << "Ban chon: ";
    cin >> a;
    char check;
    double min, max;
    string tensp;
    NodeProduct* P;
    switch (a) {
    case 1: // Lọc theo ID
        do {
            cout << "Nhap ID: ";
            cin >> id;
            cin.ignore();
            P = findProductById(id);
            if (P == NULL) {
                cout << "Khong tim thay san pham!" << endl;
            } else {
                cout << left << setw(10) << "ID" << setw(25) << "Ten san pham" << setw(10) << "Gia ban" << setw(10) << "So luong" << endl;
                cout << left << setw(10) << "--------" << setw(25) << "-----------------------" << setw(10) << "--------" << setw(10) << "--------" << endl;
                cout << left << setw(10) << P->product.id << setw(25) << P->product.name << setw(10) << P->product.price << setw(10) << P->product.quantity << endl;
            }
            cout << "Tiep tuc tim kiem? (y/n): ";
            cin >> check;
        } while (check == 'y');
        break;

    case 2: // Lọc theo tên sản phẩm
        cout << "Nhap ten san pham: ";
        cin.ignore();
        getline(cin, tensp);
        P = S;
        cout << left << setw(10) << "ID" << setw(25) << "Ten san pham" << setw(10) << "Gia ban" << setw(10) << "So luong" << endl;
        cout << left << setw(10) << "--------" << setw(25) << "-----------------------" << setw(10) << "--------" << setw(10) << "--------" << endl;
        while (P != NULL) {
            if (P->product.name.find(tensp) != string::npos) {
                cout << left << setw(10) << P->product.id << setw(25) << P->product.name << setw(10) << P->product.price << setw(10) << P->product.quantity << endl;
            }
            P = P->next;
        }
        break;

    case 3: // Lọc theo khoảng giá 
        cout << "Toi thieu: ";
        cin >> min;
        cout << "Toi da: ";
        cin >> max;
        if (min > max) {
            cout << "Khoang gia khong hop le!" << endl;
            break;
        }
        P = S;
        cout << left << setw(10) << "ID" << setw(25) << "Ten san pham" << setw(10) << "Gia ban" << setw(10) << "So luong" << endl;
        cout << left << setw(10) << "--------" << setw(25) << "-----------------------" << setw(10) << "--------" << setw(10) << "--------" << endl;
        while (P != NULL) {
            if ((P->product.price >= min) && (P->product.price <= max)) {
                cout << left << setw(10) << P->product.id << setw(25) << P->product.name << setw(10) << P->product.price << setw(10) << P->product.quantity << endl;
            }
            P = P->next;
        }
        break;

    default:
        cout << "Khong hop le, vui long thu lai!";
        break;
    }
}



// Thành 
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


int main() {
	return 0;
cout << "OKe";
}
