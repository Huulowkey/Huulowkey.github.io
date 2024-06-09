#include <iostream>
#include <string>
#include <iomanip>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

// Ngày - Định dạng dd/mm/yyyy
struct Date {
	int day;
	int month;
	int year;
	friend istream& operator >> (istream& is, Date &d) {
		string s;
		while (true) {
            cin >> s;
            if (s.size() == 10 && s[2] == '/' && s[5] == '/') break;
            cout << "Nhap sai dinh dang, vui long nhap lai (dd/mm/yyyy): ";
        }
		d.day = (s[0] - 48) * 10 + (s[1] - 48);
		d.month = (s[3] - 48) * 10 + (s[4] - 48);
		d.year = (s[6] - 48) * 1000 + (s[7] - 48) * 100 + (s[8] - 48) * 10 + (s[9] - 48);  
		return is;
	}

	friend ostream& operator << (ostream& os, Date d) {
		cout << d.day << " / " << d.month << " / " << d.year;
		return os;
	}
};

struct Product {
    int id;
    string name;
    double purchasePrice;
    double salePrice;
    int quantity;
};

struct Customer {
    string phone;
    string name;
    long point;
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
    int totalAmount();
    void Buy(int id, int Quatity);
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

/*void ProductManager::sortProduct() {
    cout << "1. Sap xep theo gia ban\n2. Sap xep theo so luong  "
    switch (s)
    {
    case :
        break;
    
    default:
        break;
    }
} 
*/
// Loc tim kiem (id, ten, khoang gia)
//id: chi 1 
//ten: tu goi y
//khoang gia: min - max
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
        cin.ignore();
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
// Tổng tiền
int ProductManager::totalAmount() {
	NodeProduct* P = S;
	int sum = 0;
	while(P != NULL) {
		sum += P->product.quantity * P->product.salePrice;
		P = P->next;
	}
	return sum;
}

void ProductManager::Buy(int id, int Quatity) {
	NodeProduct* Q = findProductById(id);
	Q->product.quantity -= Quatity;
}


class CustomerManager {
private:
    CustomerList C;
    int sizeList;
public:
    CustomerManager() : C(NULL), sizeList(0) {}
    void addCustomer();
    int getSizeList() const { return sizeList; }
    void updateCustomer(const string& phone);
    void deleteCustomer(const string& phone);
    NodeCustomer* findCustomerByPhone(const string& phone);
    void displayCustomers() const;
    NodeCustomer* lastCustomer();
};

// Hàm thêm khách hàng vào danh sách
void CustomerManager::addCustomer() {
    bool check;
    char c;
    do {
        NodeCustomer* P = new NodeCustomer;
        cout << "So dien thoai: ";
        cin >> P->customer.phone;
        cin.ignore();
        cout << "Ten khach hang: ";
        getline(cin, P->customer.name);
        cout << "Diem: ";
        cin >> P->customer.point;
        P->next = NULL;

        if (C == NULL) {
            C = P;
        } else {
            NodeCustomer* R = C;
            while (R->next != NULL) R = R->next;
            R->next = P;
        }
        sizeList++;

        cout << "Add more customers to the list? (y/n): ";
        cin >> c;
        if (c == 'y') check = true;
        else check = false;
        cin.ignore();
    } while (check);
}

// Hàm tìm kiếm khách hàng bằng số điện thoại và trả về địa chỉ NodeCustomer chứa khách hàng đó
NodeCustomer* CustomerManager::findCustomerByPhone(const string& phone) {
    NodeCustomer* P = C;
    while (P != NULL) {
        if (P->customer.phone == phone) return P;
        else P = P->next;
    }
    return NULL;
}

// Hàm cập nhật các thông tin khách hàng (tên, điểm)
void CustomerManager::updateCustomer(const string& phone) {
    NodeCustomer* Q = findCustomerByPhone(phone);
    if (Q == NULL) {
        cout << "This customer is not available!" << endl;
    } else {
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
    } else {
        prev->next = P->next;
    }

    delete P;
    sizeList--;
}

// Hàm hiển thị tất cả khách hàng trong danh sách
void CustomerManager::displayCustomers() const {
    NodeCustomer* P = C;
    while (P != NULL) {
        cout << "Phone: " << P->customer.phone << ", Name: " << P->customer.name << ", Points: " << P->customer.point << endl;
        P = P->next;
    }
}

NodeCustomer* CustomerManager::lastCustomer() {
    NodeCustomer* P = new NodeCustomer;
    if (C == NULL) {
        C = P;
    } else {
        NodeCustomer* R = C;
        while (R->next != NULL) R = R->next;
        R->next = P;
        return P;
    }
}

// Lịch sử bán hàng và doanh thu, lợi nhuận
struct Bill {
	Date date;
	int ID;
	string Name;
	ProductManager List;
	int Sum;
};
struct NodeBill {
	Bill info;
	NodeBill* next;
};
class InvoiceHistory {
	private :
		NodeBill* DsBill;
	public:
		InvoiceHistory() : DsBill(NULL) {}
		void DisPlayBill();
		void XuatManHinh(NodeBill* P) {
			cout << P->info.date;
			P->info.List.displayProducts();
		}
		void addBill(Date date, int id, string name, ProductManager list);
		NodeBill* FindBill(int id);
		void FindInvoice();
		void BanHang(CustomerManager& khach, ProductManager& kho);
		void XuatHoaDon(int id, ProductManager list);
		void XuatDoanhThuTheo();
		void LichSuMuaHangCuaKhach(CustomerManager list);
};
void InvoiceHistory::DisPlayBill() {
	cout << ">> Toan bo lich su hoa don <<" << endl;
	NodeBill* P = DsBill;
	while(P != NULL) {
		cout << "ID: " << P->info.ID << "\tDate: " << P->info.date << "\tKhach hang: " << P->info.Name << endl;
		ProductManager Q = P->info.List;
		Q.displayProducts();
		P = P->next;					
	}
}
void InvoiceHistory::addBill(Date date, int id, string name, ProductManager list) {
	NodeBill* P = new NodeBill;
	P->next = NULL;
	P->info.date = date;
	P->info.ID = id;
	P->info.List = list;
	P->info.Sum = list.totalAmount();
	if (DsBill == NULL) {
		DsBill = P;
		return;
	}
	NodeBill* R = DsBill;
    while (R->next != NULL) R = R->next;
    R->next = P;
}
NodeBill* InvoiceHistory::FindBill(int id) {
	NodeBill* P = DsBill;
	while(P != NULL) {
		if (P->info.ID == id) {
			return P;
		}
		P = P->next;
	}
	return NULL;
}
void InvoiceHistory::FindInvoice() {
	int id;
	cout << "Nhap hoa don can tim kiem: ";
	cin >> id;
	NodeBill* P = FindBill(id);
	if(P == NULL) {
		cout << "Khong ton tai hoa don!" << endl;
		return;
	}
	cout << "ID: " << P->info.ID << "\tDate: " << P->info.date << "\tKhach hang: " << P->info.Name;
	ProductManager Q = P->info.List;
	Q.displayProducts();
}


void InvoiceHistory::XuatHoaDon(int id, ProductManager list) {
cout << id << endl;
list.displayProducts();
}



void InvoiceHistory::BanHang(CustomerManager& khach, ProductManager& kho) {
	Date date;
	cout << "Nhap ngay mua: ";
	cin >> date;
	ProductManager DsMua;
	char check;
	string sdt;
	NodeCustomer* P;
	bool checkk;
    char cc;
    char muatiep;
    do {
        NodeProduct* Z = new NodeProduct;
        cout << "ID: ";
        cin >> Z->product.id;
        NodeProduct* Q = kho.findProductById(Z->product.id);
        if (Q == NULL) {
        	cout << "Khong tim thay san pham!" << endl;
        	goto a;
		}
        else {
        	cout << "ID: " << Q->product.id << " Name: " << Q->product.name << " Gia: " << Q->product.salePrice << " So luong: " << Q->product.quantity << endl;
		}
		b:
		cout << "So luong can mua: " ;
		cin >> Z->product.quantity;
		if (Z->product.quantity > Q->product.quantity) {
			cout << "Vuot qua so san pham hien co!" << endl;
			cout << "Ban tiep tuc mua san pham nay?: (y/n)";
			cin >> muatiep;
			if (muatiep == 'y') {
				goto b;
			}
			delete Z;
			goto a;
		}
		Z->product.salePrice = Q->product.salePrice;
		Z->product.name = Q->product.name;
		DsMua.addProduct();
		kho.Buy(Z->product.id, Z->product.quantity);
        a:
        cout << "Tiep tuc mua san pham? (y/n): ";
        cin >> cc;
        if (cc == 'y') checkk = true; 
        else checkk = false;
        cin.ignore();
    } while (checkk);
	cout << "Ban co muon tich diem khong? (y/n): ";
	cin >> check;
	if (check == 'y') {
		cout << "Nhap so dien thoai cua bn: ";
		cin >> sdt;
		P = khach.findCustomerByPhone(sdt);
		if (P == NULL) {
			khach.addCustomer();
            P = khach.lastCustomer();
            cin.ignore();
            cout << P->customer.point;
		} else {khach.lastCustomer();}         
	}
}
void InvoiceHistory::XuatDoanhThuTheo() {
	Date d;
	int sum = 0;
	cout << "Nhap thoi gian can tim: "; cin >> d;
	NodeBill* P = DsBill;
	while(P != NULL) {
		if ((P->info.date.day== d.day || d.day == 0) && (P->info.date.month== d.month || d.month == 0) && P->info.date.year == d.year) {
			XuatManHinh(P);
			sum += P->info.Sum;
		}
		P = P->next;
	}
	cout << "Doanh thu ";
	if (d.day != 0 ) cout << "ngay " << d.day << " ";
	if (d.month != 0) cout << "thang " << d.month << " ";
	cout << "nam " << d.year << " : " << sum;
}
void InvoiceHistory::LichSuMuaHangCuaKhach(CustomerManager list) {
	string id;
	char c;
	a:
	cout << "Nhap ten id khach hang: "; cin >> id;
	if (list.findCustomerByPhone(id) == NULL) {
		cout << "Khong co trong danh sach khach hang!" << endl;
		cout << "Ban muon tiep tuc tim: (y/n) "; cin >> c;
		if (c == 'y') goto a; else return;
		
	}
	cout << "Hello";
	NodeBill* P = DsBill;
	while(P != NULL) {
		if (!id.compare(P->info.Name)) {
			XuatManHinh(P);
			P = P->next;
		}
	}
}
int main() {
    ProductManager productManager;
    CustomerManager customerManager;
    InvoiceHistory invoiceHistory;
    productManager.addProduct();
    //productManager.updateProduct();
    //productManager.deleteProduct();
    productManager.displayProducts();
    productManager.filter();
    invoiceHistory.BanHang(customerManager, productManager);
    invoiceHistory.DisPlayBill();
    getch();
    productManager.displayProducts();
    getch();
    invoiceHistory.XuatDoanhThuTheo();
    getch();
    invoiceHistory.LichSuMuaHangCuaKhach(customerManager);
    return 0;
}
