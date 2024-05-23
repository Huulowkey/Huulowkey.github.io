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
// Tạo danh sách liên kết cho Customer, Product, Database
struct NodeProduct {
    Product info;
    NodeProduct* next;
};
typedef NodeProduct* Storage;

struct NodeCustomer {
    Customer info;
    NodeCustomer* next;
};
typedef NodeCustomer* CustomerList;

class ProductManager {
private:
    Storage product;
public:
    void addProduct();
    void updateProduct(int id, const string& name, double price, int quantity);
    void deleteProduct(int id);
    Product* findProductById(int id);
    void displayProducts() const;
};

class CustomerManager {
private:
    CustomerList customer;
public:
    void addCustomer(int id, const string& name, const string& phone);
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