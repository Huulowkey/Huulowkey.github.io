#include"Thuvien.h"
#include<fstream>
using namespace std;
struct Product {
    int id;
    string name;
    double purchasePrice;
    double salePrice;
    int quantity;
};

// Tạo danh sách liên kết cho Sản phẩm
struct NodeProduct {
    Product product;
    NodeProduct* next;
};
typedef NodeProduct* Storage;

// Tạo đối tượng Quản lý sản phẩm, khai báo các thuộc tính và phương thức hàm(thêm, tìm kiếm, cập nhật, xóa, lọc) và khởi tạo danh sách liên kết rỗng
class ProductManager {
private:
    Storage S;
    int sizeItem;
public:
    ProductManager() : S(NULL), sizeItem(0) {}
    void addProduct();
    void addProduct(int id, string name, double purchasePrice, double salePrice, int quantity);
    int getSizeItem() const { return sizeItem; }
    NodeProduct* findProductById(int id);
    void updateProduct();
    void deleteProduct();
    void displayProducts() const;
    void filter();
    int totalAmount();
    int totalAmountGoc();
    void Buy(int id, int Quatity);
    void loadFromFile(const string& filename);
    void saveToFile(const string& filename);
    
};
void ProductManager::addProduct(int id, string name, double purchasePrice, double salePrice, int quantity) {
    NodeProduct* P = new NodeProduct;
    P->product.id = id;
    P->product.name = name;
    P->product.purchasePrice = purchasePrice;
    P->product.salePrice = salePrice;
    P->product.quantity = quantity;
    P->next = NULL;
    if (S == NULL) {
        S = P;
    }
    else {
        NodeProduct* R = S;
        while (R->next != NULL) R = R->next;
        R->next = P;
    }
    sizeItem++;
}
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
        cout << "Gia nhap: ";
        cin >> P->product.purchasePrice;
        cout << "Gia ban: ";
        cin >> P->product.salePrice;
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
// Hàm cập nhật các sản phẩm muốn thay đổi(tên, giá, số lượng) - ID là cố định với mỗi loại sản phẩm
void ProductManager::updateProduct() {
    char check;
    do {
        int id;
        cout << "Nhap ID san pham can cap nhat: ";
        cin >> id;
        NodeProduct* Q;
        Q = findProductById(id);
        if (Q==NULL) {
            cout << "Khong tim thay san pham!" << endl;
        } else {
            cout << "Ten san pham: ";
            getline(cin, Q->product.name);
            cout << "Gia nhap: ";
            cin >> Q->product.purchasePrice;
            cout << "Gia ban: ";
            cin >> Q->product.salePrice;
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
    cout << left << setw(10) << "ID" << setw(25) << "Ten san pham" << setw(10) << "Gia nhap" << setw(10) << "Gia ban" << setw(10) << "So luong" << endl;
    cout << left << setw(10) << "--------" << setw(25) << "-----------------------" << setw(10) << "--------" << setw(10) << "--------" << setw(10) << "--------" << endl;
    while(P!=NULL) {
        cout << left << setw(10) << P->product.id << setw(25) << P->product.name << setw(10) << P->product.purchasePrice << setw(10) << P->product.salePrice << setw(10) << P->product.quantity << endl;
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
    case 1:
        do {
            cout << "Nhap ID: ";
            cin >> id;
            cin.ignore();
            P = findProductById(id);
            if (P == NULL) {
                cout << "Khong tim thay san pham!" << endl;
            } else {
                cout << left << setw(10) << "ID" << setw(25) << "Ten san pham" << setw(10) << "Gia nhap" << setw(10) << "Gia ban" << setw(10) << "So luong" << endl;
                cout << left << setw(10) << "--------" << setw(25) << "-----------------------" << setw(10) << "--------" << setw(10) << "--------" << setw(10) << "--------" << endl;
                cout << left << setw(10) << P->product.id << setw(25) << P->product.name << setw(10) << P->product.purchasePrice << setw(10) << P->product.salePrice << setw(10) << P->product.quantity << endl; }
            cout << "Tiep tuc tim kiem? (y/n): ";
            cin >> check;
        } while (check == 'y');
        break;

    case 2:
        cout << "Nhap ten san pham: ";
        cin.ignore();
        getline(cin, tensp);
        P = S;
        cout << left << setw(10) << "ID" << setw(25) << "Ten san pham" << setw(10) << "Gia nhap" << setw(10) << "Gia ban" << setw(10) << "So luong" << endl;
        cout << left << setw(10) << "--------" << setw(25) << "-----------------------" << setw(10) << "--------" << setw(10) << "--------" << setw(10) << "--------" << endl;
        while (P != NULL) {
            if (P->product.name.find(tensp) != string::npos) {
                cout << left << setw(10) << P->product.id << setw(25) << P->product.name << setw(10) << P->product.purchasePrice << setw(10) << P->product.salePrice << setw(10) << P->product.quantity << endl;
            }
            P = P->next;
        }
        break;

    case 3:
        cout << "Toi thieu: ";
        cin >> min;
        cout << "Toi da: ";
        cin >> max;
        if (min > max) {
            cout << "Khoang gia khong hop le!" << endl;
            break;
        }
        P = S;
        cout << left << setw(10) << "ID" << setw(25) << "Ten san pham" << setw(10) << "Gia nhap" << setw(10) << "Gia ban" << setw(10) << "So luong" << endl;
        cout << left << setw(10) << "--------" << setw(25) << "-----------------------" << setw(10) << "--------" << setw(10) << "--------" << setw(10) << "--------" << endl;
        while (P != NULL) {
            if ((P->product.salePrice >= min) && (P->product.salePrice <= max)) {
                cout << left << setw(10) << P->product.id << setw(25) << P->product.name << setw(10) << P->product.purchasePrice << setw(10) << P->product.salePrice << setw(10) << P->product.quantity << endl;
            }
            P = P->next;
        }
        break;
    default:
        cout << "Khong hop le, vui long thu lai!";
        break;
    }
}

int ProductManager::totalAmount() {
    NodeProduct* P = S;
    int sum = 0;
    while (P != NULL) {
        sum += P->product.quantity * P->product.salePrice;
        P = P->next;
    }
    return sum;
}
int ProductManager::totalAmountGoc() {
    NodeProduct* P = S;
    int sum = 0;
    while (P != NULL) {
        sum += P->product.quantity * P->product.purchasePrice;
        P = P->next;
    }
    return sum;
}
void ProductManager::Buy(int id, int Quatity) {
    NodeProduct* Q = findProductById(id);
    Q->product.quantity -= Quatity;
}

void ProductManager::loadFromFile(const string& filename) {
    ifstream filein("Text.txt");
    if (!filein.is_open()) {
        cerr << "Failed to open the file." << endl;
        return;
    }

    while (!filein.eof()) {
        Product pr;
        string id_str, purchasePrice_str, salePrice_str, quantity_str;

        if (!getline(filein, id_str, ',')) break;
        getline(filein, pr.name, ',');
        getline(filein, purchasePrice_str, ',');
        getline(filein, salePrice_str, ',');
        getline(filein, quantity_str);

        pr.id = stoi(id_str);
        pr.purchasePrice = stod(purchasePrice_str);
        pr.salePrice = stod(salePrice_str);
        pr.quantity = stoi(quantity_str);

        addProduct();
    }

    filein.close();
}

void ProductManager::saveToFile(const string& filename) {
    ofstream fileout("Text.txt");
    if (!fileout.is_open()) {
        cerr << "Failed to open the file." << endl;
        return;
    }

    NodeProduct* P = S;
    while (P != NULL) {
        fileout << P->product.id << ","
            << P->product.name << ","
            << P->product.purchasePrice << ","
            << P->product.salePrice << ","
            << P->product.quantity << endl;
        P = P->next;
    }

    fileout.close();
}