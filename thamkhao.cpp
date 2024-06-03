#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>

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
    long points;
};

struct NodeProduct {
    Product product;
    NodeProduct* next;
};

typedef NodeProduct* Storage;

struct NodeCustomer {
    Customer customer;
    NodeCustomer* next;
};

typedef NodeCustomer* CustomerList;

struct InvoiceItem {
    Product product;
    int quantity;
};

class Invoice {
public:
    vector<InvoiceItem> items;
    double totalAmount;

    Invoice() : totalAmount(0) {}

    void addItem(Product product, int quantity) {
        InvoiceItem newItem = {product, quantity};
        items.push_back(newItem);
        totalAmount += product.price * quantity;
    }

    void displayInvoice() {
        cout << left << setw(10) << "ID" << setw(25) << "Ten san pham" << setw(10) << "Gia ban" << setw(10) << "So luong" << setw(10) << "Thanh tien" << endl;
        cout << left << setw(10) << "--------" << setw(25) << "-----------------------" << setw(10) << "--------" << setw(10) << "--------" << setw(10) << "--------" << endl;
        for (const auto& item : items) {
            cout << left << setw(10) << item.product.id << setw(25) << item.product.name << setw(10) << item.product.price << setw(10) << item.quantity << setw(10) << item.product.price * item.quantity << endl;
        }
        cout << "Tong tien: " << totalAmount << endl;
    }

    void exportInvoiceToFile(const string& filename) {
        ofstream outFile(filename);
        if (!outFile) {
            cerr << "Khong the mo file de ghi!" << endl;
            return;
        }
        outFile << left << setw(10) << "ID" << setw(25) << "Ten san pham" << setw(10) << "Gia ban" << setw(10) << "So luong" << setw(10) << "Thanh tien" << endl;
        outFile << left << setw(10) << "--------" << setw(25) << "-----------------------" << setw(10) << "--------" << setw(10) << "--------" << setw(10) << "--------" << endl;
        for (const auto& item : items) {
            outFile << left << setw(10) << item.product.id << setw(25) << item.product.name << setw(10) << item.product.price << setw(10) << item.quantity << setw(10) << item.product.price * item.quantity << endl;
        }
        outFile << "Tong tien: " << totalAmount << endl;
        outFile.close();
        cout << "Hoa don da duoc luu vao file " << filename << endl;
    }
};

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
    void checkLowStock(int threshold) const;
};

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

NodeProduct* ProductManager::findProductById(int id) {
    NodeProduct* P;
    P = S;
    while(P!=NULL) {
        if (P->product.id==id) return P;
        else P = P->next;
    }
    return NULL;
}

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
        cin.ignore();
    } while (check =='y');
}

void ProductManager::deleteProduct() {
    cout << "Nhap ID san pham can xoa: ";
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

void ProductManager::displayProducts() const {
    cout << "So loai mat hang:  " << getSizeItem() << endl;
    NodeProduct* P = S;
    cout << left << setw(10) << "ID" << setw(25) << "Ten san pham" << setw(10) << "Gia ban" << setw(10) << "So luong" << endl;
    cout << left << setw(10) << "--------" << setw(25) << "-----------------------" << setw(10) << "--------" << setw(10) << "--------" << endl;
    while(P!=NULL) {
        cout << left << setw(10) << P->product.id << setw(25) << P->product.name << setw(10) << P->product.price << setw(10) << P->product.quantity << endl;
        P = P->next;
    }
}

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
                cout << left << setw(10) << "ID" << setw(25) << "Ten san pham" << setw(10) << "Gia ban" << setw(10) << "So luong" << endl;
                cout << left << setw(10) << "--------" << setw(25) << "-----------------------" << setw(10) << "--------" << setw(10) << "--------" << endl;
                cout << left << setw(10) << P->product.id << setw(25) << P->product.name << setw(10) << P->product.price << setw(10) << P->product.quantity << endl;
            }
            cout << "Tiep tuc tim kiem? (y/n): ";
            cin >> check;
        } while (check == 'y');
        break;

    case 2:
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

void ProductManager::checkLowStock(int threshold) const {
    NodeProduct* P = S;
    cout << "San pham co so luong duoi " << threshold << ":" << endl;
    cout << left << setw(10) << "ID" << setw(25) << "Ten san pham" << setw(10) << "Gia ban" << setw(10) << "So luong" << endl;
    cout << left << setw(10) << "--------" << setw(25) << "-----------------------" << setw(10) << "--------" << setw(10) << "--------" << endl;
    while(P != NULL) {
        if (P->product.quantity < threshold) {
            cout << left << setw(10) << P->product.id << setw(25) << P->product.name << setw(10) << P->product.price << setw(10) << P->product.quantity << endl;
        }
        P = P->next;
    }
}

class CustomerManager {
private:
    CustomerList customers;
public:
    CustomerManager() : customers(NULL) {}

    void addCustomer() {
        NodeCustomer* newCustomer = new NodeCustomer;
        cout << "Nhap ten khach hang: ";
        cin.ignore();
        getline(cin, newCustomer->customer.name);
        cout << "Nhap so dien thoai: ";
        getline(cin, newCustomer->customer.phone);
        newCustomer->customer.points = 0;
        newCustomer->next = customers;
        customers = newCustomer;
    }

    NodeCustomer* findCustomerByPhone(const string& phone) {
        NodeCustomer* current = customers;
        while (current != NULL) {
            if (current->customer.phone == phone) {
                return current;
            }
            current = current->next;
        }
        return NULL;
    }

    void displayCustomers() const {
        NodeCustomer* current = customers;
        cout << left << setw(15) << "So dien thoai" << setw(25) << "Ten khach hang" << setw(10) << "Diem tich luy" << endl;
        cout << left << setw(15) << "---------------" << setw(25) << "-----------------------" << setw(10) << "--------" << endl;
        while (current != NULL) {
            cout << left << setw(15) << current->customer.phone << setw(25) << current->customer.name << setw(10) << current->customer.points << endl;
            current = current->next;
        }
    }

    void updateCustomerPoints(const string& phone, long points) {
        NodeCustomer* customer = findCustomerByPhone(phone);
        if (customer != NULL) {
            customer->customer.points += points;
        }
    }
};

class SaleManager {
private:
    ProductManager& productManager;
    CustomerManager& customerManager;
public:
    SaleManager(ProductManager& pm, CustomerManager& cm) : productManager(pm), customerManager(cm) {}

    void createInvoice() {
        Invoice invoice;
        char check;
        do {
            int productId, quantity;
            cout << "Nhap ID san pham: ";
            cin >> productId;
            NodeProduct* productNode = productManager.findProductById(productId);
            if (productNode == NULL) {
                cout << "Khong tim thay san pham!" << endl;
                continue;
            }
            cout << "Nhap so luong: ";
            cin >> quantity;
            if (quantity > productNode->product.quantity) {
                cout << "So luong khong du!" << endl;
                continue;
            }
            productNode->product.quantity -= quantity;
            invoice.addItem(productNode->product, quantity);
            cout << "Tiep tuc them san pham? (y/n): ";
            cin >> check;
        } while (check == 'y');

        string phone;
        cout << "Nhap so dien thoai khach hang: ";
        cin >> phone;
        NodeCustomer* customer = customerManager.findCustomerByPhone(phone);
        if (customer == NULL) {
            cout << "Khong tim thay khach hang, vui long dang ky khach hang moi." << endl;
            cin.ignore();
            customerManager.addCustomer();
            customer = customerManager.findCustomerByPhone(phone);
        }
        customerManager.updateCustomerPoints(phone, static_cast<long>(invoice.totalAmount));
        invoice.displayInvoice();
        invoice.exportInvoiceToFile("invoice.txt");
    }
};

class ReportManager {
private:
    vector<double> dailySales;
public:
    void addSale(double amount) {
        dailySales.push_back(amount);
    }

    void generateReport() {
        double total = 0;
        for (double sale : dailySales) {
            total += sale;
        }
        cout << "Doanh thu trong ngay: " << total << endl;
    }
};

int main() {
    ProductManager productManager;
    CustomerManager customerManager;
    SaleManager saleManager(productManager, customerManager);
    ReportManager reportManager;

    int choice;
    do {
        cout << "1. Quan ly san pham\n2. Quan ly khach hang\n3. Tao hoa don\n4. Bao cao doanh thu\n5. Kiem tra so luong ton kho\n0. Thoat\n";
        cout << "Nhap lua chon: ";
        cin >> choice;
        switch (choice) {
            case 1:
                productManager.addProduct();
                //productManager.displayProducts();
                //productManager.updateProduct();
                //productManager.deleteProduct();
                productManager.displayProducts();
                productManager.filter();
                break;
            case 2:
                customerManager.addCustomer();
                customerManager.displayCustomers();
                break;
            case 3:
                saleManager.createInvoice();
                break;
            case 4:
                reportManager.generateReport();
                break;
            case 5:
                int threshold;
                cout << "Nhap nguong so luong: ";
                cin >> threshold;
                productManager.checkLowStock(threshold);
                break;
            case 0:
                cout << "Thoat chuong trinh.\n";
                break;
            default:
                cout << "Lua chon khong hop le, vui long thu lai!\n";
                break;
        }
    } while (choice != 0);

    return 0;
}
