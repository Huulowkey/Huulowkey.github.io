#include <iostream>
#include <string>
#include <iomanip>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
int TyLeDoiRaDiem = 10000;
int TyLeDoiRaTien = 1000;
using namespace std;
int random(int minN, int maxN){
	return minN + rand() % (maxN + 1 - minN);
}
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
struct NodeProduct {
    Product product;
    NodeProduct* next;
};

typedef NodeProduct* Storage;

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
    } else {
        NodeProduct* R = S;
        while (R->next != NULL) R = R->next;
        R->next = P;
    }
    sizeItem++;
}
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
            cin.ignore();
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
    if (Q==NULL) {
    	cout << "Khong tim thay san pham!";
    	return;
	}
	string NameXoa = Q->product.name;
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
    } 
    sizeItem--;
    cout << "Da xoa san pham:  " << NameXoa << endl;

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
int ProductManager::totalAmountGoc() {
	NodeProduct* P = S;
	int sum = 0;
	while(P != NULL) {
		sum += P->product.quantity * P->product.purchasePrice;
		P = P->next;
	}
	return sum;
}
void ProductManager::Buy(int id, int Quatity) {
	NodeProduct* Q = findProductById(id);
	Q->product.quantity -= Quatity;
}
struct Customer {
    string phone;
    string name;
    long point;
};
struct NodeCustomer {
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
        } else {
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
    } else {
        cout << "Enter Customer Name: ";
        cin.ignore();
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
    cout << "Da xoa khach hang:  " << P->customer.name << endl;
}
void CustomerManager::displayCustomers() const {
    NodeCustomer* P = C;
    
        cout << left << setw(17) << "Phone" << setw(25) << "Ten khach hang" << setw(10) << "Diem" << endl;
        cout << left << setw(17) << "---------------" << setw(25) << "-----------------------" << setw(10) << "--------" << endl;
		
    while (P != NULL) {
        cout << left << setw(17)  << P->customer.phone << setw(25) << P->customer.name << setw(10)  << P->customer.point << endl;
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
struct Bill {
	Date date;
	int ID;
	string Name;
	ProductManager List;
	int Sum;
	int TongTienGoc;
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
			cout << P->info.date << "\n";
			P->info.List.displayProducts();
		}
		NodeBill* addBill(Date date, int id, string name, ProductManager list);
		NodeBill* FindBill(int id);
		void FindInvoice();
		void BanHang(CustomerManager& khach, ProductManager& kho);
		void XuatHoaDon(int id, ProductManager list, Date date, int Money);
		void XuatDoanhThuLoiNhuan();
		void LichSuMuaHangCuaKhach(CustomerManager list);
        int SoBatKy() {
			while(1) {
				int r = random(100000, 999999);
				if (FindBill(r) == NULL) {
					return r;
				}
			}
		}
};
void InvoiceHistory::DisPlayBill() {
	cout << ">>> Toan bo lich su hoa don <<<" << endl;
	NodeBill* P = DsBill;
	while(P != NULL) {
		cout << "ID hoa don: " << P->info.ID << "\tDate: " << P->info.date << "\tKhach hang: " << P->info.Name << endl;
		ProductManager Q = P->info.List;
		Q.displayProducts();
		P = P->next;					
	}
}
NodeBill* InvoiceHistory::addBill(Date date, int id, string name, ProductManager list) {
	NodeBill* P = new NodeBill;
	P->next = NULL;
	P->info.date = date;
	P->info.ID = id;
	P->info.List = list;
    P->info.Name = name;
	P->info.Sum = list.totalAmount();
	P->info.TongTienGoc = list.totalAmountGoc();
	if (DsBill == NULL) {
		DsBill = P;
		return P;
	}
	NodeBill* R = DsBill;
    while (R->next != NULL) R = R->next;
    R->next = P;
    return P;
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

// Can viet tiep phan xuat hoa don
void InvoiceHistory::XuatHoaDon(int id, ProductManager list , Date date, int money) {
system("cls");
cout << "Ma hoa don :" << id << "       " << date << endl;
list.displayProducts();
cout << "Thanh tien : " << money;
}



void InvoiceHistory::BanHang(CustomerManager& khach, ProductManager& kho) {
	Date date;
	int point = 0;
	cout << "Nhap ngay mua: ";
	cin >> date;
	ProductManager DsMua;
	char check;
	string sdt = "";
	NodeCustomer* P = NULL;
    char cc;
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
        	cout << left << setw(10) << "ID" << setw(25) << "Ten san pham" << setw(10) << "Gia nhap" << setw(10) << "Gia ban" << setw(10) << "So luong" << endl;
            cout << left << setw(10) << "--------" << setw(25) << "-----------------------" << setw(10) << "--------" << setw(10) << "--------" << setw(10) << "--------" << endl;
        	cout << left << setw(10) << Q->product.id << setw(25) << Q->product.name << setw(10) << Q->product.purchasePrice << setw(10) << Q->product.salePrice << setw(10) << Q->product.quantity << endl;            
		}
		b:
		cout << "So luong can mua: " ;
		cin >> Z->product.quantity;
		if (Z->product.quantity > Q->product.quantity) {
			cout << "Vuot qua so san pham hien co!" << endl;
			cout << "Ban tiep tuc mua san pham nay?: (y/n)";
			cin >> check;
			if (check == 'y') {
				goto b;
			}
			delete Z;
			goto a;
		}
		Z->product.salePrice = Q->product.salePrice;
		Z->product.name = Q->product.name;
		Z->product.purchasePrice = Q->product.purchasePrice;
		DsMua.addProduct(Z->product.id, Z->product.name, Z->product.purchasePrice, Z->product.salePrice, Z->product.quantity);
		kho.Buy(Z->product.id, Z->product.quantity);
        a:
        cout << "Tiep tuc mua san pham? (y/n): ";
        cin >> cc;
        if (cc == 'y') check = true; 
        else check = false;
        cin.ignore();
    } while (check);
	cout << "Ban co muon su dung tich diem khong? (y/n): ";
	cin >> check;
	if (check == 'y') {
		cout << "Nhap so dien thoai cua bn: ";
		cin >> sdt;
		P = khach.findCustomerByPhone(sdt);
		if (P == NULL) {
			cout << "Chua co mat tai he thong!" << endl;
			 P = khach.addCustomer();
			 sdt = P->customer.phone;
		}
		khach.UpdatePoint(P->customer.phone, DsMua.totalAmount() / TyLeDoiRaDiem, 1);  
		cout << "So diem tich luy hien co: " << P->customer.point << endl;		
		c:
		cout << "Ban co muon su dung diem (y/n): "; cin >> check;
		if (check == 'y') {
			cout << "So diem muon doi (x1000): ";
			cin >> point;
			if (point > P->customer.point) {
				cout << "So diem lon bn co!" << endl;
				goto c;
			}
			khach.UpdatePoint(P->customer.phone, point, -1);
			cout << "So Diem con lai : " << P->customer.point << endl;
			
		}     
	}
    int s = SoBatKy();
	
	NodeBill* A = addBill(date, s, sdt, DsMua);
	A->info.Sum = A->info.Sum - TyLeDoiRaTien * point;
	cout << "So tien phai thanh toan: " << A->info.Sum << endl;
	XuatHoaDon(s, DsMua, date, A->info.Sum);
	return;
}
void InvoiceHistory::XuatDoanhThuLoiNhuan() {
	Date d;
	int DoanhThu = 0;
	int Goc = 0;
	cout << "Nhap thoi gian can tim: "; cin >> d;
	NodeBill* P = DsBill;
	while(P != NULL) {
		if ((P->info.date.day== d.day || d.day == 0) && (P->info.date.month== d.month || d.month == 0) && P->info.date.year == d.year) {
			XuatManHinh(P);
			DoanhThu += P->info.Sum;
			Goc += P->info.TongTienGoc;
		}
		P = P->next;
	}
	cout << "Doanh thu ";
	if (d.day != 0 ) cout << "ngay " << d.day << " ";
	if (d.month != 0) cout << "thang " << d.month << " ";
	cout << "nam " << d.year << " : " << DoanhThu << "\n Loi nhuan: " << DoanhThu - Goc << endl;
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
	NodeBill* P = DsBill;
	while(P != NULL) {
		if (!id.compare(P->info.Name)) {
			XuatManHinh(P);
			P = P->next;
		}
	}
}

//void quanlisanpham()
/*{
    ProductManager manager;
    int choice;
    do
    {
        cout << endl;
        cout << "\t\t\t_________________________________________________________________________________\n";
        cout << "\t\t\t|                                                                                |\n";
        cout << "\t\t\t|                            Quan li san pham                                    |\n";
        cout << "\t\t\t|                                                                                |\n";
        cout << "\t\t\t|________________________________________________________________________________|\n";
        cout << "\n\t\t\t\t|______________________ 1) Them san pham     _____________________|";
        cout << "\n\t\t\t\t|                                                                 |";
        cout << "\n\t\t\t\t|______________________ 2) Cap nhat san pham _____________________|";
        cout << "\n\t\t\t\t|                                                                 |";
        cout << "\n\t\t\t\t|______________________ 3) Xoa san pham      _____________________|";
        cout << "\n\t\t\t\t|                                                                 |";
        cout << "\n\t\t\t\t|______________________ 4) Hien thi san pham _____________________|";
        cout << "\n\t\t\t\t|                                                                 |";
        cout << "\n\t\t\t\t|______________________ 5) Quay lai menu     _____________________|";
        
        cout << endl;
        cout << "Lua chon cua ban: ";
        cin >> choice;

        switch (choice) {
        case 1:
            manager.addProduct();
            break;
        case 2:
            manager.updateProduct();
            break;
        case 3:
            manager.deleteProduct();
            break;
        case 4:
            manager.displayProducts();
            break;
		case 5:
            return;
        default:
            cout << "Lua chon khong hop le !";
            break;
        }

    } while (choice != 0);

}
//void quanlikhachhang()
//{
    CustomerManager costomer;
    string sdt;
    int choice;
    do
    {
        cout << endl;
        cout << "\t\t\t_________________________________________________________________________________\n";
        cout << "\t\t\t|                                                                                |\n";
        cout << "\t\t\t|                            Quan li khach hang                                  |\n";
        cout << "\t\t\t|                                                                                |\n";
        cout << "\t\t\t|________________________________________________________________________________|\n";
        cout << "\n\t\t\t\t|______________________ 1) Them khach hang     _____________________|";
        cout << "\n\t\t\t\t|                                                                   |";
        cout << "\n\t\t\t\t|______________________ 2) Xoa khach hang      _____________________|";
        cout << "\n\t\t\t\t|                                                                   |";
        cout << "\n\t\t\t\t|______________________ 3) Cap nhat khach hang _____________________|";
        cout << "\n\t\t\t\t|                                                                   |";
        cout << "\n\t\t\t\t|______________________ 4) Hien thi khach hang _____________________|";
        cout << "\n\t\t\t\t|                                                                   |";
        cout << "\n\t\t\t\t|______________________ 5) Quay lai menu       _____________________|";
      
        cout << endl;
        cout << "Lua chon cua ban: ";
        cin >> choice;

        switch (choice) {
        case 1:
            costomer.addCustomer();
            break;
        case 2:
            cout << "nhap so dien thoai: ";
            cin >> sdt;
            costomer.deleteCustomer(sdt);
            break;
        case 3:
            cout << "nhap so dien thoai: ";
            cin >> sdt;
            costomer.updateCustomer(sdt);
            break;
        case 4:
            costomer.displayCustomers();
            break;
        case 5:
            return;
        default:
            cout << "Lua chon khong hop le !";
            break;
        }

    } while (choice != 0);
}

//void quanlihoadon()
//{
    InvoiceHistory ivh;
    ProductManager manager;
    CustomerManager costomer;
    string sdt;
    int id;
    int choice;
    do
    {
        cout << endl;
        cout << "\t\t\t_________________________________________________________________________________\n";
        cout << "\t\t\t|                                                                                |\n";
        cout << "\t\t\t|                              Quan li hoa don                                   |\n";
        cout << "\t\t\t|                                                                                |\n";
        cout << "\t\t\t|________________________________________________________________________________|\n";
        cout << "\n\t\t\t\t|______________________ 1) Hien thi tat ca hoa don      _____________________|";
        cout << "\n\t\t\t\t|                                                                            |";
        cout << "\n\t\t\t\t|______________________ 2) Tim kiem mot hoa don theo id _____________________|";
        cout << "\n\t\t\t\t|                                                                            |";
        cout << "\n\t\t\t\t|______________________ 3) Lich su mua hang cua khach   _____________________|";
        cout << "\n\t\t\t\t|                                                                            |";
        cout << "\n\t\t\t\t|______________________ 4) Xuat doanh thu loi nhuan     _____________________|";
        cout << "\n\t\t\t\t|                                                                            |";
        cout << "\n\t\t\t\t|______________________ 5) Quay lai menu                _____________________|";
        cout << endl;
        cout << "Lua chon cua ban: ";
        cin >> choice;

        switch (choice) {
        case 1:
            ivh.DisPlayBill();
            break;
        case 2:
            cout << "Nhap ID hoa don: ";
            cin >> id;
            ivh.FindBill(id);
            break;
        case 3:
            ivh.LichSuMuaHangCuaKhach(costomer);
            break;
        case 4:
            ivh.XuatDoanhThuLoiNhuan();
            break;
        case 5:
            return;
        default:
            cout << "Lua chon khong hop le !";
            break;
        }

    } while (choice != 0);
}

//void menu()
//{
    InvoiceHistory ivh;
    ProductManager manager;
    CustomerManager costomer;
    int choice;
    do {
        cout << endl;
        cout << "\t\t\t_________________________________________________________________________________\n";
        cout << "\t\t\t|                                                                                |\n";
        cout << "\t\t\t|                                      Menu                                      |\n";
        cout << "\t\t\t|                                                                                |\n";
        cout << "\t\t\t|________________________________________________________________________________|\n";
        cout << "\n\t\t\t\t|________________________  1)Quan li san pham  _______________________|";
        cout << "\n\t\t\t\t|                                                                     |";
        cout << "\n\t\t\t\t|________________________  2)Quan li khach hang_______________________|";
        cout << "\n\t\t\t\t|                                                                     |";
        cout << "\n\t\t\t\t|________________________  3)Quan li hoa don   _______________________|";
        cout << "\n\t\t\t\t|                                                                     |";
        cout << "\n\t\t\t\t|________________________  4)Ban hang          _______________________|";
        cout << "\n\t\t\t\t|                                                                     |";
        cout << "\n\t\t\t\t|________________________  0) Exit             _______________________|";
       
        cout << endl;
        cout << "Lua chon cua ban :";
        cin >> choice;

        switch (choice) {
        case 1:
            quanlisanpham();
            break;
        case 2:
            quanlikhachhang();
            break;
        case 3:
            quanlihoadon();
            break;
        case 4:        	
            ivh.BanHang(costomer, manager);
            break;
        case 5:
            cout << "Thoat chuong trinh.\n";
            break;
        default:
            cout << "Lua chon khong hop le. Vui long chon lai.\n";
            break;
        }
    } while (choice != 0);
}
//int main()
//{
    srand((int)time(0));
    menu();
    return 0;
}
*/
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file




void quanlisanpham()
{
        cout << endl;
        cout << "\t\t\t_________________________________________________________________________________\n";
        cout << "\t\t\t|                                                                                |\n";
        cout << "\t\t\t|                            Quan li san pham                                    |\n";
        cout << "\t\t\t|                                                                                |\n";
        cout << "\t\t\t|________________________________________________________________________________|\n";
        cout << "\n\t\t\t\t|______________________ 1) Them san pham     _____________________|";
        cout << "\n\t\t\t\t|                                                                |";
        cout << "\n\t\t\t\t|______________________ 2) Cap nhat san pham _____________________|";
        cout << "\n\t\t\t\t|                                                                |";
        cout << "\n\t\t\t\t|______________________ 3) Xoa san pham      _____________________|";
        cout << "\n\t\t\t\t|                                                                |";
        cout << "\n\t\t\t\t|______________________ 4) Hien thi san pham _____________________|";
        cout << "\n\t\t\t\t|                                                                |";
        cout << "\n\t\t\t\t|______________________ 0) Quay lai menu     _____________________|";
        cout << endl;
        
}
void quanlikhachhang()
{
  
        cout << endl;
        cout << "\t\t\t_________________________________________________________________________________\n";
        cout << "\t\t\t|                                                                                |\n";
        cout << "\t\t\t|                            Quan li khach hang                                  |\n";
        cout << "\t\t\t|                                                                                |\n";
        cout << "\t\t\t|________________________________________________________________________________|\n";
        cout << "\n\t\t\t\t|______________________ 1) Them khach hang     _____________________|";
        cout << "\n\t\t\t\t|                                                                   |";
        cout << "\n\t\t\t\t|______________________ 2) Xoa khach hang      _____________________|";
        cout << "\n\t\t\t\t|                                                                   |";
        cout << "\n\t\t\t\t|______________________ 3) Cap nhat khach hang _____________________|";
        cout << "\n\t\t\t\t|                                                                   |";
        cout << "\n\t\t\t\t|______________________ 4) Hien thi khach hang _____________________|";
        cout << "\n\t\t\t\t|                                                                   |";
        cout << "\n\t\t\t\t|______________________ 0) Quay lai menu       _____________________|";
        cout << endl;
      
}

void quanlihoadon()
{

    cout << endl;
    cout << "\t\t\t_________________________________________________________________________________\n";
    cout << "\t\t\t|                                                                                |\n";
    cout << "\t\t\t|                              Quan li hoa don                                   |\n";
    cout << "\t\t\t|                                                                                |\n";
    cout << "\t\t\t|________________________________________________________________________________|\n";
    cout << "\n\t\t\t\t|______________________ 1) Hien thi tat ca hoa don      _____________________|";
    cout << "\n\t\t\t\t|                                                                            |";
    cout << "\n\t\t\t\t|______________________ 2) Lich su mua hang cua khach   _____________________|";
    cout << "\n\t\t\t\t|                                                                            |";
    cout << "\n\t\t\t\t|______________________ 3) Xuat doanh thu loi nhuan     _____________________|";
    cout << "\n\t\t\t\t|                                                                            |";
    cout << "\n\t\t\t\t|______________________ 0) Quay lai menu                _____________________|";
    cout << endl;
}


/*void manager()
{

    ProductManager manager;
    CustomerManager costomer;
    InvoiceHistory inh;
    //manager.loadFromFile("Text.txt");
    int choice;
do 
{
    cout << endl;
    cout << "\t\t\t_________________________________________________________________________________\n";
    cout << "\t\t\t|                                                                                |\n";
    cout << "\t\t\t|                                Manager Menu                                    |\n";
    cout << "\t\t\t|                                                                                |\n";
    cout << "\t\t\t|________________________________________________________________________________|\n";
    cout << "\n\t\t\t\t|______________________ 1) Add new product  _____________________|";
    cout << "\n\t\t\t\t|                                                                |";
    cout << "\n\t\t\t\t|______________________2) Update the product_____________________|";
    cout << "\n\t\t\t\t|                                                                |";
    cout << "\n\t\t\t\t|______________________   3) Delete product _____________________|";
    cout << "\n\t\t\t\t|                                                                |";
    cout << "\n\t\t\t\t|______________________  4) Display product _____________________|";
    cout << "\n\t\t\t\t|                                                                |";
    cout << "\n\t\t\t\t|______________________     5) Filter       _____________________|";
    cout << "\n\t\t\t\t|                                                                |";
    cout << "\n\t\t\t\t|______________________ 6) Lich su mua hang _____________________|";
    cout << "\n\t\t\t\t|                                                                |";
    cout << "\n\t\t\t\t|______________________   7)Display bill    _____________________|";
    cout << "\n\t\t\t\t|                                                                |";
    cout << "\n\t\t\t\t|______________________8)Doanh thu loi nhuan_____________________|";
    cout << "\n\t\t\t\t|                                                                |";   
    cout << "\n\t\t\t\t|______________________   9)Back to menu    _____________________|";
    cout << "\n\t\t\t\t|                                                                |";
    cout << "\n\t\t\t\t|______________________      0) Exit        _____________________|";
    cout << endl;
    cout << "Lua chon cua ban: ";
    cin >> choice;

    switch (choice) {
    case 1:
        manager.addProduct();
        break;
    case 2:
        manager.updateProduct();
        break;
    case 3:
        manager.deleteProduct();
        break;
    case 4:
        manager.displayProducts();
        break;
    case 5:
        manager.filter();
        break;
    case 6:
        inh.LichSuMuaHangCuaKhach(costomer);
        break;
    case 7:
        inh.DisPlayBill();
        break;
    case 8:
        inh.XuatDoanhThuLoiNhuan();
        break;    
    case 10:
        manager.saveToFile("Text.txt");
        break;
    
    case 9:
        return;
    case 0:
        cout << "Thoat chuong trinh.\n";
        break;
    default:
        cout << "Lua chon khong hop le. Vui long chon lai.\n";
        break;
    }
} while (choice != 0);
}
void buyer()
{
    string sdt;
    ProductManager manager;
    CustomerManager costomer;
    InvoiceHistory inh;
    int choice;

    do {
        cout << endl;
        cout << "\t\t\t_________________________________________________________________________________\n";
        cout << "\t\t\t|                                                                                |\n";
        cout << "\t\t\t|                                  Buyer Menu                                    |\n";
        cout << "\t\t\t|                                                                                |\n";
        cout << "\t\t\t|________________________________________________________________________________|\n";
        cout << "\n\t\t\t\t|______________________   2) Ban hang       _____________________|";
        cout << "\n\t\t\t\t|                                                                |";
        cout << "\n\t\t\t\t|______________________     3) Filter       _____________________|";
        cout << "\n\t\t\t\t|                                                                |";
        cout << "\n\t\t\t\t|______________________4) update kh�ch h�ng _____________________|";
        cout << "\n\t\t\t\t|                                                                |";
        cout << "\n\t\t\t\t|______________________   5) Back to menu   _____________________|";
        cout << "\n\t\t\t\t|                                                                |";
        cout << "\n\t\t\t\t|______________________      0) Exit        _____________________|";
        cout << endl;
        cout << "Lua chon cua ban: ";
        cin >> choice;

        switch (choice) {
        case 1:
            costomer.addCustomer();
            break;
        case 2:
            inh.BanHang(costomer,manager);
            break;       
        case 3:
            manager.filter();
            break;
        case 4: 
            cout << "so dien thoai cua ban la: " ;
            cin.ignore();
            getline(cin, sdt);
            costomer.updateCustomer(sdt);
       
        case 5:
            return;
        case 0:
            cout << "Thoat chuong trinh.\n";
            break;
        default:
            cout << "Lua chon khong hop le. Vui long chon lai.\n";
            break;
        }
    } while (choice != 0);
}
*/
void menu()
{

    cout << endl;
    cout << "\t\t\t_________________________________________________________________________________\n";
    cout << "\t\t\t|                                                                                |\n";
    cout << "\t\t\t|                                      Menu                                      |\n";
    cout << "\t\t\t|                                                                                |\n";
    cout << "\t\t\t|________________________________________________________________________________|\n";
    cout << "\n\t\t\t\t|________________________  1)Quan li san pham  _______________________|";
    cout << "\n\t\t\t\t|                                                                     |";
    cout << "\n\t\t\t\t|________________________  2)Quan li khach hang_______________________|";
    cout << "\n\t\t\t\t|                                                                     |";
    cout << "\n\t\t\t\t|________________________  3)Quan li hoa don   _______________________|";
    cout << "\n\t\t\t\t|                                                                     |";
    cout << "\n\t\t\t\t|________________________  4)Ban hang          _______________________|";
    cout << "\n\t\t\t\t|                                                                     |";
    cout << "\n\t\t\t\t|________________________  0) Exit             _______________________|";
    cout << endl;

}
int main()
{
    InvoiceHistory ivh;
    ProductManager manager;
    CustomerManager costomer;
    int choice;srand((int)time(0));
    do 
    {
        menu();
        cout << "Nhap lua chon :";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int productChoice;
            do {
                quanlisanpham();
                cout << " Nhap lua chon: ";
                cin >> productChoice;
                switch (productChoice) {
                case 1:
                    manager.addProduct();
                    break;
                case 2:
                    manager.updateProduct();
                    break;
                case 3:
                    manager.deleteProduct();
                    break;
                case 4:
                    manager.displayProducts();
                    break;
               
                default:
                	system("cls");
                    cout << "  ";
                    break;
                }
            }while (productChoice != 0);
            
        }break;
        case 2:
        {   int costomerchoice;
            
        do {
            string sdt;
            quanlikhachhang();
            cout << "Nhap lua chon cua ban: ";
            cin >> costomerchoice;
            switch (costomerchoice) {
            case 1:
                costomer.addCustomer();
                break;
            case 2:
                cout << "nhap so dien thoai: ";
                cin >> sdt;
                costomer.updateCustomer(sdt);
                break;
            case 3:
                costomer.displayCustomers();
                break;
           
            default:
            	system("cls");
                cout << "   ";
                break;
            }
        }while (costomerchoice != 0);

        }break;
        case 3: {
            int historychoice;
            do {
                int id;
                quanlihoadon();
                cout << "Nhap lua chon: ";
                cin >> historychoice;
                switch (historychoice) {
                case 1:
                    ivh.DisPlayBill();
                    break;
                case 2:
                    cout << "Nhap ID hoa don: ";
                    cin >> id;
                    ivh.FindBill(id);
                    break;
                case 3:
                    ivh.LichSuMuaHangCuaKhach(costomer);
                    break;
                case 4:
                    ivh.XuatDoanhThuLoiNhuan();
                    break;
                
                default:
                	system("cls");
                    cout << "    ";
                    break;
                }
            } while (historychoice != 0);
        }break;
        case 4:
        	manager.displayProducts();
            ivh.BanHang(costomer, manager);
            break;
        case 0:
            cout << "Thoat chuong trinh";
            break;
        default:
            cout << "Lua chon khong hop le. Vui long chon lai." << endl;
        }
    }while (choice != 0);
    
    
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file


