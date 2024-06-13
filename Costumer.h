#include"Thuvien.h"
using namespace std;
struct Customer 
{
    string phone;
    string name;
    long point;
};
struct NodeCustomer 
{
    Customer customer;
    NodeCustomer* next;
};

typedef NodeCustomer* CustomerList;
class CustomerManager {
private:
    CustomerList C;
    int sizeList;
public:
    CustomerManager() : C(NULL), sizeList(0) {}
    NodeCustomer* addCustomer();
    int getSizeList() const { return sizeList; }
    void updateCustomer(const string& phone);
    void deleteCustomer(const string& phone);
    NodeCustomer* findCustomerByPhone(const string& phone);
    void displayCustomers() const;
    NodeCustomer* lastCustomer();
    void UpdatePoint(const string& phone, int point, int TrangThai);
};
NodeCustomer* CustomerManager::addCustomer() {
    NodeCustomer* P = new NodeCustomer;
    cout << "So dien thoai: ";
    cin >> P->customer.phone;
    cin.ignore();
    cout << "Ten khach hang: ";
    getline(cin, P->customer.name);
    P->customer.point = 0;
    P->next = NULL;
    if (C == NULL) {
        C = P;
    }
    else {
        NodeCustomer* R = C;
        while (R->next != NULL) R = R->next;
        R->next = P;
    }
    sizeList++;
    return P;
}
NodeCustomer* CustomerManager::findCustomerByPhone(const string& phone) {
    NodeCustomer* P = C;
    while (P != NULL) {
        if (P->customer.phone == phone) return P;
        else P = P->next;
    }
    return NULL;
}
void CustomerManager::updateCustomer(const string& phone) {
    NodeCustomer* Q = findCustomerByPhone(phone);
    if (Q == NULL) {
        cout << "This customer is not available!" << endl;
    }
    else {
        cout << "Enter Customer phone: ";
        getline(cin, Q->customer.phone);
        cout << "Enter Customer Name: ";
        getline(cin, Q->customer.name);
        cout << "Enter Customer Points: ";
        cin >> Q->customer.point;
    }
}

// Hàm xóa khách hàng khỏi danh sách
void CustomerManager::deleteCustomer(const string& phone) {
    if (C == NULL) return;

    NodeCustomer* P = C;
    NodeCustomer* prev = NULL;

    // Tìm kiếm khách hàng
    while (P != NULL && P->customer.phone != phone) {
        prev = P;
        P = P->next;
    }

    if (P == NULL) {
        cout << "Customer not found!" << endl;
        return;
    }

    // Nếu khách hàng là đầu danh sách
    if (prev == NULL) {
        C = P->next;
    }
    else {
        prev->next = P->next;
    }

    delete P;
    sizeList--;
}
void CustomerManager::displayCustomers() const {
    NodeCustomer* P = C;
    while (P != NULL) {
        cout << "Phone: " << P->customer.phone << ", Name: " << P->customer.name << ", Points: " << P->customer.point << endl;
        P = P->next;
    }
}
void CustomerManager::UpdatePoint(const string& phone, int point, int TrangThai) {
    NodeCustomer* Q = findCustomerByPhone(phone);
    if (Q == NULL) {
        cout << "This customer is not available!" << endl;
        return;
    }
    Q->customer.point += TrangThai * point;
}
