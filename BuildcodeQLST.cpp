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
//  SAN PHAM
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
    NodeProduct* mergeSort(NodeProduct* head, int input);
    NodeProduct* sortedMergeIn(NodeProduct* a, NodeProduct* b);
    NodeProduct* sortedMergeDe(NodeProduct* a, NodeProduct* b);
    void splitList(NodeProduct* source, NodeProduct** frontRef, NodeProduct** backRef);

public:
    ProductManager() : S(NULL), sizeItem(0) {}
    void addProduct();
    void addProduct(int id, string name, double purchasePrice, double salePrice, int quantity);
    int getSizeItem() const { return sizeItem; }
    NodeProduct* findProductById(int id);
    void updateProduct();
    void deleteProduct();
    void displayProducts() const;
    void sortProductsBySalePrice(int input);
    void displayProductsInvoice() const;
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
// Hàm thêm sản phẩm vào kho
void ProductManager::addProduct() {
    bool check;
    char c;
    do {
        NodeProduct* P = new NodeProduct;
        cout << "\nMoi ban nhap san pham \n";
        cout << "Nhap ID san pham: ";
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
    system("cls");
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
    system("cls");
}
// Hàm xóa sản phẩm 
void ProductManager::deleteProduct() {
    char check;
	do{
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
    cout << "\n\nBan co muon xoa tiep khong (y/n) : " ;
    cin >> check;
	}while(check == 'y' );
	system("cls");
}
// Hàm hiển thị tất cả sản phẩm hiện có
void ProductManager::displayProducts() const {
    NodeProduct* P = S;
    cout << left << setw(10) << "ID" << setw(25) << "Ten san pham" << setw(10) << "Gia nhap" << setw(10) << "Gia ban" << setw(10) << "So luong" << endl;
    cout << left << setw(10) << "--------" << setw(25) << "-----------------------" << setw(10) << "--------" << setw(10) << "--------" << setw(10) << "--------" << endl;
    while(P!=NULL) {
        cout << left << setw(10) << P->product.id << setw(25) << P->product.name << setw(10) << P->product.purchasePrice << setw(10) << P->product.salePrice << setw(10) << P->product.quantity << endl;
        P = P->next;
    }
    cout << endl;
    //getch();
    //system("cls");
}
// Hàm hiển thị sản phẩm hóa đơn đưa cho người mua 
void ProductManager::displayProductsInvoice() const {
    NodeProduct* P = S;
    cout << left << setw(10) << "ID" << setw(25) << "Ten san pham" << setw(10) << setw(10) << "Gia ban" << setw(10) << "So luong" << endl;
    cout << left << setw(10) << "--------" << setw(25) << "-----------------------" << setw(10) << setw(10) << "--------" << setw(10) << "--------" << endl;
    while(P!=NULL) {
        cout << left << setw(10) << P->product.id << setw(25) << P->product.name << setw(10) << setw(10) << P->product.salePrice << setw(10) << P->product.quantity << endl;
        P = P->next;
    }
}
// Hàm lọc sản phẩm theo ID, tên, khoảng giá
void ProductManager::filter() {
    cout << "\nTim kiem theo: \n";
	cout << "1. ID\n2. Ten san pham\n3. Khoang gia\n4. Quay lai\n";
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
    case 4:
        return;

    default:
        cout << "Khong hop le, vui long thu lai!";
        break;
    }
}
// Tổng tiền bán 
int ProductManager::totalAmount() {
	NodeProduct* P = S;
	int sum = 0;
	while(P != NULL) {
		sum += P->product.quantity * P->product.salePrice;
		P = P->next;
	}
	return sum;
}
// Tổng tiền nhập hàng
int ProductManager::totalAmountGoc() {
	NodeProduct* P = S;
	int sum = 0;
	while(P != NULL) {
		sum += P->product.quantity * P->product.purchasePrice;
		P = P->next;
	}
	return sum;
}
// Hàm thực hiện chức năng bán hàng
void ProductManager::Buy(int id, int Quatity) {
	NodeProduct* Q = findProductById(id);
	Q->product.quantity -= Quatity;
}
// Hàm kết hợp hai danh sách đã được sắp xếp thành một danh sách duy nhất theo thứ tự tăng dần, giảm dần của giá bán.
NodeProduct* ProductManager::sortedMergeIn(NodeProduct* P, NodeProduct* Q) {
    NodeProduct* result = NULL;
    if (P == NULL)
        return Q;
    else if (Q == NULL)
        return P;
    if (P->product.salePrice <= Q->product.salePrice) {
        result = P;
        result->next = sortedMergeIn(P->next, Q);
    } else {
        result = Q;
        result->next = sortedMergeIn(P, Q->next);
    }
    return result;
}
NodeProduct* ProductManager::sortedMergeDe(NodeProduct* P, NodeProduct* Q) {
    NodeProduct* result = NULL;
    if (P == NULL)
        return Q;
    else if (Q == NULL)
        return P;
    if (P->product.salePrice >= Q->product.salePrice) {
        result = P;
        result->next = sortedMergeDe(P->next, Q);
    } else {
        result = Q;
        result->next = sortedMergeDe(P, Q->next);
    }
    return result;
}
// Hàm chia một danh sách thành hai nửa.
void ProductManager::splitList(NodeProduct* source, NodeProduct** frontRef, NodeProduct** backRef) {
    NodeProduct* fast;
    NodeProduct* slow;
    slow = source;
    fast = source->next;

    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
}
// Hàm thực hiện chia và kết hợp danh sách để sắp xếp.
NodeProduct* ProductManager::mergeSort(NodeProduct* head, int input) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    NodeProduct* a;
    NodeProduct* b;

    splitList(head, &a, &b);

    a = mergeSort(a, input);
    b = mergeSort(b, input);
    switch (input)
    {
    case 1:
        return sortedMergeIn(a, b);
        break;
    case 2:
        return sortedMergeDe(a, b);
        break;
    default:
        return NULL;
        break;
    }
}
// Hàm sắp xếp sản phẩm theo giá bán
void ProductManager::sortProductsBySalePrice(int input) {
    S = mergeSort(S, input);
}
//  KHACH HANG
struct Customer {
    string phone;
    string name;
    long point;
};
// Tạo danh sách liên kết đơn cho tập khách hàng
struct NodeCustomer {
    Customer customer;
    NodeCustomer* next;
};
// Tạo đối tượng Quản lý khách hàng, khai báo các thuộc tính và phương thức hàm(thêm, tìm kiếm, cập nhật, xóa, lọc) và khởi tạo danh sách liên kết rỗng
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
    void filterCustomer(string phone);
    void UpdatePoint(const string& phone, int point, int status);
};
// Thêm khách hàng
NodeCustomer* CustomerManager::addCustomer() {  
	    NodeCustomer* P = new NodeCustomer;
        cout << "Moi ban nhap thong tin khach hang: \n\n";
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
// Tìm khách hàng bằng số điện thoại và trả về địa chỉ node đó
NodeCustomer* CustomerManager::findCustomerByPhone(const string& phone) {
    NodeCustomer* P = C;
    while (P != NULL) {
        if (P->customer.phone == phone) return P;
        else P = P->next;
    }
    return NULL;
}

// Hàm lọc khách hàng theo số điện thoại
void CustomerManager::filterCustomer (string phone) {
    NodeCustomer* P = findCustomerByPhone(phone);
    if (P == NULL) {
        cout << "Khong tim thay khach hang!" << endl;
        } else {
            cout << left << setw(15) << "So dien thoai" << setw(30) << "Ten khach hang" << setw(10) << "Diem tich luy" << endl;
            cout << left << setw(15) << "--------------" << setw(30) << "----------------------------" << setw(10) << "--------" << endl;
            cout << left << setw(15) << P->customer.phone << setw(30) << P->customer.name << setw(10) << P->customer.point << endl;
        }
}

// Hàm cập nhật thông tin khách hàng
void CustomerManager::updateCustomer(const string& phone) {
    cin.ignore();
    NodeCustomer* Q = findCustomerByPhone(phone);
    if (Q == NULL) {
        cout << "Khong tim thay khach hang!" << endl;
    }
    else {
        cout << "So dien thoai: ";
        getline(cin, Q->customer.phone);
        cout << "Ten khach hang: ";
        getline(cin, Q->customer.name);
       // cout << "Enter Customer Points: ";
       // cin >> Q->customer.point;
    }
}

// Hàm xóa khách hàng khỏi danh sách
void CustomerManager::deleteCustomer(const string& phone) {
    if (C == NULL) return;

    NodeCustomer* P = C;
    NodeCustomer* prev = NULL;

    // Tìm kiếm khách hàng bằng sđt
    while (P != NULL && P->customer.phone != phone) {
        prev = P;
        P = P->next;
    }
    if (P == NULL) {
        cout << "Khong tim thay khach hang!" << endl;
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
    cout << "Da xoa khach hang!  " << P->customer.name << endl;
}
// Hàm hiển thị thông tin khách hàng
void CustomerManager::displayCustomers() const {
    cout << "               ==== KHACH HANG ====\n" << endl;
    NodeCustomer* P = C;
    cout << left << setw(15) << "So dien thoai" << setw(30) << "Ten khach hang" << setw(10) << "Diem tich luy" << endl;
    cout << left << setw(15) << "--------------" << setw(30) << "----------------------------" << setw(10) << "--------" << endl;
    while(P!=NULL) {
        cout << left << setw(15) << P->customer.phone << setw(30) << P->customer.name << setw(10) << P->customer.point << endl;
        P = P->next;
    }
    cout << "\nSo luong:  " << getSizeList() << endl;
}
// Hàm cập nhật số điểm tích lũy hiện tại của khách
void CustomerManager::UpdatePoint(const string& phone, int point, int status) {
    NodeCustomer* Q = findCustomerByPhone(phone);
    if (Q == NULL) {
        cout << "Khong tim thay khach hang!" << endl;
        return;
    }
    Q->customer.point += status * point;
}
//  HOA DON
struct Invoice {
	Date date;
	int ID;
	string Name;
	ProductManager List;
	int totalRev;
	int totalCap;
};
// Tạo danh sách liên kết đơn cho hóa đơn
struct NodeInvoice {
	Invoice info;
	NodeInvoice* next;
};
// Tạo đối tượng Quản lý hóa đơn bao gồm các thuộc tính và phương thức
class InvoiceManager {
	private :
		NodeInvoice* listInvoice;
	public:
		InvoiceManager() : listInvoice(NULL) {}
		void DisPlayInvoice();
		void XuatManHinh(NodeInvoice* P) {
			cout << "Ngay:\t" << P->info.date << "\n";
			P->info.List.displayProductsInvoice();
		}
		NodeInvoice* addInvoice(Date date, int id, string name, ProductManager list);
		NodeInvoice* findInvoice(int id);
		void filterInvoice();
		void Sale(CustomerManager& khach, ProductManager& kho);
		void exportInvoice(int id, ProductManager list, Date date, long long Money, long long Discount);
		void Revenue_Profit();
		void CP_History(CustomerManager list);
        int SoBatKy() {
			while(1) {
				int r = random(100000, 999999);
				if (findInvoice(r) == NULL) {
					return r;
				}
			}
		}
};
// Hiển thị danh sách tất cả các hóa đơn
void InvoiceManager::DisPlayInvoice() {
	cout << "                  ==== HOA DON ====\n" << endl;
	NodeInvoice* P = listInvoice;
	while(P != NULL) {
		cout << "ID hoa don: " << P->info.ID << "   \t\tDate: " << P->info.date << endl;
		ProductManager Q = P->info.List;
		Q.displayProductsInvoice();
		P = P->next;					
	}
	getch();
}
// Thêm hóa đơn mới vào danh sách hóa đơn
NodeInvoice* InvoiceManager::addInvoice(Date date, int id, string name, ProductManager list) {
	NodeInvoice* P = new NodeInvoice;
	P->next = NULL;
	P->info.date = date;
	P->info.ID = id;
	P->info.List = list;
    P->info.Name = name;
	P->info.totalRev = list.totalAmount();
	P->info.totalCap = list.totalAmountGoc();
	if (listInvoice == NULL) {
		listInvoice = P;
		return P;
	}
	NodeInvoice* R = listInvoice;
    while (R->next != NULL) R = R->next;
    R->next = P;
    return P;
}
NodeInvoice* InvoiceManager::findInvoice(int id) {
	NodeInvoice* P = listInvoice;
	while(P != NULL) {
		if (P->info.ID == id) {
			return P;
		}
		P = P->next;
	}
	return NULL;
}
// Tìm kiếm hóa đơn theo id - id là cố định mỗi hóa đơn và được tạo ngẫu nhiên
void InvoiceManager::filterInvoice() {
	int id;
	cout << "Nhap ID hoa don can tim kiem: ";
	cin >> id;
	NodeInvoice* P = findInvoice(id);
	if(P == NULL) {
		cout << "Khong ton tai hoa don!" << endl;
		return;
	}
	cout << "ID: " << P->info.ID << "\t\t\tDate: " << P->info.date ;
	ProductManager Q = P->info.List;
	cout << "\n";
	Q.displayProductsInvoice();
	getch();
    system("cls");
}

// Xuất hóa đơn cho khách hàng
void InvoiceManager::exportInvoice(int id, ProductManager list , Date date, long long money, long long discount) {
system("cls");
cout << "Ma hoa don :" << id << "                 " << date << endl;
list.displayProductsInvoice();
cout << "Giam gia : - " <<  discount << endl;
cout << "Thanh tien : " << money;
getch();
system("cls");
}
// Thủ tục bán hàng
void InvoiceManager::Sale(CustomerManager& khach, ProductManager& kho) {
	Date date;
	int point = 0;
	cout << "Nhap ngay mua: ";
	cin >> date;
	ProductManager listBuy;
	char check;
	string sdt = "";
	NodeCustomer* P = NULL;
    char cc;
    long long discount;
    do {
        NodeProduct* Z = new NodeProduct;
        cout << "ID san pham: ";
        cin >> Z->product.id;
        NodeProduct* Q = kho.findProductById(Z->product.id);
        if (Q == NULL) {
        	cout << "Khong tim thay san pham!" << endl;
        	goto a;
		}
		b:
		cout << "So luong can mua: " ;
		cin >> Z->product.quantity;
		if (Z->product.quantity > Q->product.quantity) {
			cout << "Vuot qua so san pham hien co!" << endl;
			cout << "Tiep tuc mua san pham? (y/n):";
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
		listBuy.addProduct(Z->product.id, Z->product.name, Z->product.purchasePrice, Z->product.salePrice, Z->product.quantity);
		kho.Buy(Z->product.id, Z->product.quantity);
        a:
        cout << "Tiep tuc mua san pham? (y/n): ";
        cin >> cc;
        if (cc == 'y') check = true; 
        else check = false;
        cin.ignore();
    } while (check);
	cout << "Su dung tich diem? (y/n): ";
	cin >> check;
	if (check == 'y') {
		cout << "So dien thoai khach hang: ";
		cin >> sdt;
		P = khach.findCustomerByPhone(sdt);
		if (P == NULL) {
            cout << "Khach hang chua co mat tren he thong, tien hanh them moi.\n";
			P = khach.addCustomer();
		}
		khach.UpdatePoint(P->customer.phone, listBuy.totalAmount() / TyLeDoiRaDiem, 1);  
		khach.filterCustomer(sdt);	
		c:
		cout << "Ban co muon su dung diem (y/n): "; cin >> check;
		if (check == 'y') {
			cout << "So diem muon doi (x1000vnd): ";
			cin >> point;
			if (point > P->customer.point) {
				cout << "Vuot qua so diem hien co!" << endl;
				goto c;
			}
			khach.UpdatePoint(P->customer.phone, point, -1);
			cout << "So diem con lai : " << P->customer.point << endl;
			
		}     
	}
    int s = SoBatKy();
	
	NodeInvoice* A = addInvoice(date, s, sdt, listBuy);
	A->info.totalRev = A->info.totalRev - TyLeDoiRaTien * point;
    discount = TyLeDoiRaTien * point;
	cout << "So tien phai thanh toan: " << A->info.totalRev << endl;
	exportInvoice(s, listBuy, date, A->info.totalRev, discount);
	return;
}
// Hàm xuất doanh thu, lợi nhuận theo ngày, tháng, năm
void InvoiceManager::Revenue_Profit() {
	Date d;
	int DoanhThu = 0;
	int Goc = 0;
	cout << "Nhap thoi gian can tim: "; cin >> d;
	NodeInvoice* P = listInvoice;
	while(P != NULL) {
		if ((P->info.date.day== d.day || d.day == 0) && (P->info.date.month== d.month || d.month == 0) && P->info.date.year == d.year) {
			XuatManHinh(P);
			DoanhThu += P->info.totalRev;
			Goc += P->info.totalCap;
		}
		P = P->next;
	}
	cout << "Doanh thu ";
	if (d.day != 0 ) cout << "ngay " << d.day << " ";
	if (d.month != 0) cout << "thang " << d.month << " ";
	cout << "nam " << d.year << " : " << DoanhThu << "\nLoi nhuan: " << DoanhThu - Goc << endl;
	getch();
    system("cls");
}
// Tìm kiếm các mặt hàng mà khách đã mua
void InvoiceManager::CP_History(CustomerManager list) {
	string id;
	char c;
	a:
	cout << "Nhap ten id khach hang: "; cin >> id;
	if (list.findCustomerByPhone(id) == NULL) {
		cout << "Khong co trong danh sach khach hang!" << endl;
		cout << "Ban muon tiep tuc tim: (y/n) "; cin >> c;
		if (c == 'y') goto a; else return;
		
	}
	NodeInvoice* P = listInvoice;
	while(P != NULL) {
		if (!id.compare(P->info.Name)) {
			XuatManHinh(P);
		}
        P = P->next;
	}
	getch();
    system("cls");
}


void quanlisanpham()
{
        cout << endl;
        cout << "\t\t\t_________________________________________________________________________________\n";
        cout << "\t\t\t|                                                                                |\n";
        cout << "\t\t\t|                               Quan li san pham                                 |\n";
        cout << "\t\t\t|                                                                                |\n";
        cout << "\t\t\t|________________________________________________________________________________|\n";
        cout << "\n\t\t\t|______________________      1) Them san pham               _____________________|";
        cout << "\n\t\t\t|                                                                                |";
        cout << "\n\t\t\t|______________________      2) Cap nhat san pham           _____________________|";
        cout << "\n\t\t\t|                                                                                |";
        cout << "\n\t\t\t|______________________      3) Xoa san pham                _____________________|";
        cout << "\n\t\t\t|                                                                                |";
        cout << "\n\t\t\t|______________________      4) Hien thi san pham           _____________________|";
        cout << "\n\t\t\t|                                                                                |";
        cout << "\n\t\t\t|______________________      5) Loc san pham                _____________________|";
        cout << "\n\t\t\t|                                                                                |";
        cout << "\n\t\t\t|______________________      0) Quay lai menu               _____________________|";
        cout << endl;
        
}
void quanlikhachhang()
	{
        cout << endl;
        cout << "\t\t\t_________________________________________________________________________________\n";
        cout << "\t\t\t|                                                                                |\n";
        cout << "\t\t\t|                               Quan li khach hang                               |\n";
        cout << "\t\t\t|                                                                                |\n";
        cout << "\t\t\t|________________________________________________________________________________|\n";
        cout << "\n\t\t\t|______________________      1. Them khach hang             _____________________|";
        cout << "\n\t\t\t|                                                                                |";
        cout << "\n\t\t\t|______________________      2. Xoa khach hang              _____________________|";
        cout << "\n\t\t\t|                                                                                |";
        cout << "\n\t\t\t|______________________      3. Cap nhat khach hang         _____________________|";
        cout << "\n\t\t\t|                                                                                |";
        cout << "\n\t\t\t|______________________      4. Hien thi khach hang         _____________________|";
        cout << "\n\t\t\t|                                                                                |";
        cout << "\n\t\t\t|______________________      0. Quay lai menu               _____________________|";
        cout << endl;
      
}

void quanlihoadon()
{
    cout << endl;
    cout << "\t\t\t_________________________________________________________________________________\n";
    cout << "\t\t\t|                                                                                |\n";
    cout << "\t\t\t|                                Quan li hoa don                                 |\n";
    cout << "\t\t\t|                                                                                |\n";
    cout << "\t\t\t|________________________________________________________________________________|\n";
    cout << "\n\t\t\t|______________________    1. Hien thi tat ca hoa don       _____________________|";
    cout << "\n\t\t\t|                                                                                |";
    cout << "\n\t\t\t|______________________    2. Tim hoa don theo ID           _____________________|";
    cout << "\n\t\t\t|                                                                                |";
    cout << "\n\t\t\t|______________________    3. Lich su mua hang cua khach    _____________________|";
    cout << "\n\t\t\t|                                                                                |";
    cout << "\n\t\t\t|______________________    4. Xuat doanh thu loi nhuan      _____________________|";
    cout << "\n\t\t\t|                                                                                |";
    cout << "\n\t\t\t|______________________    0. Quay lai menu                 _____________________|";
    cout << endl;
}


void menu()
{
    cout << endl;
    cout << "\t\t\t_________________________________________________________________________________\n";
    cout << "\t\t\t|                                                                                |\n";
    cout << "\t\t\t|                                      Menu                                      |\n";
    cout << "\t\t\t|                                                                                |\n";
    cout << "\t\t\t|________________________________________________________________________________|\n";
    cout << "\n\t\t\t|________________________        1.Quan li san pham       _______________________|";
    cout << "\n\t\t\t|                                                                                |";
    cout << "\n\t\t\t|________________________        2.Quan li khach hang     _______________________|";
    cout << "\n\t\t\t|                                                                                |";
    cout << "\n\t\t\t|________________________        3.Quan li hoa don        _______________________|";
    cout << "\n\t\t\t|                                                                                |";
    cout << "\n\t\t\t|________________________        4.Ban hang               _______________________|";
    cout << "\n\t\t\t|                                                                                |";
    cout << "\n\t\t\t|________________________        0.Exit                   _______________________|";
    cout << endl;

}
int main()
{
    InvoiceManager ivh;
    ProductManager manager;
    manager.addProduct(1, "Bot giat Omo", 30000, 35000, 100);
    manager.addProduct(2, "Kem danh rang Closeup", 25000, 30000, 150);
    manager.addProduct(3, "Sua rua mat Crave", 350000, 400000, 120);
    CustomerManager customer;
    int choice;srand((int)time(0));
    do 
    {
        menu();
        cout << "Nhap lua chon:";
        cin >> choice;
        cin.ignore();
        char check;
        int in;
        switch (choice)
        {
        case 1:
        {
        	system("cls");
            int productChoice;
            do {
                quanlisanpham();
                cout << "Nhap lua chon: ";
                cin >> productChoice;
                switch (productChoice) {
                case 1:
                	system("cls");
                    manager.addProduct();
                    break;
                case 2:
                	system("cls");
                	manager.displayProducts();
                	cout << "\nChon san pham muon update \n";
                    manager.updateProduct();
                    break;
                case 3:
                	system("cls");
                	manager.displayProducts();
                	cout << "\nChon san pham muon xoa \n";
                    manager.deleteProduct();
                    break;
                case 4:
                	system("cls");
                    cout << "                       ==== SAN PHAM ====\n" << endl;
                    manager.displayProducts();
                    cout << "So loai mat hang:  " << manager.getSizeItem() << endl;
                    getch();
                    cout << "Sap xep theo gia ban? (y/n): ";
                    cin >> check;
                    system("cls");
                    if ( check == 'y') {
                        cout << "1. Tang dan\n2. Giam dan\n";
                        cout << "Ban chon: ";
                        cin >> in;
                        cout << "                       ==== SAN PHAM ====\n" << endl;
                        manager.sortProductsBySalePrice(in);
                        manager.displayProducts();
                        cout << "So loai mat hang:  " << manager.getSizeItem() << endl;
                        }
                    getch();
                    system("cls");
                    break;
                case 5:
    				system("cls");
                    manager.filter();
                    cout << endl;
                    system("pause");
                    system("cls");
                    break;
                default:
                	system("cls");
                    cout << "  ";
                    break;
                }
            }while (productChoice != 0);
            system("cls");
            
        }break;
        case 2:
        	system("cls");
        {   int customerchoice;
            
        do {
            string sdt;
            quanlikhachhang();
            cout << "Ban chon: ";
            cin >> customerchoice;
            switch (customerchoice) {
            case 1:
            	system("cls");
                customer.addCustomer();
                system("cls");
                break;
            case 2:
            	system("cls");
            	customer.displayCustomers();
                cout << "\nNhap so dien thoai ban muon xoa: ";
                cin >> sdt;
                customer.deleteCustomer(sdt);
                system("cls");
                break; 
            case 3:
            	system("cls");
                cout << "\nNhap so dien thoai cua khach hang: ";
                cin >> sdt;
                customer.updateCustomer(sdt);
                system("cls");
                break;
            case 4:
            	system("cls");
                customer.displayCustomers();
                system("pause");
                system("cls");
                break;
            default:
            	system("cls");
                cout << "   ";
                break;
            }
        }while (customerchoice != 0);
        system("cls");

        }break;
        case 3: {
        	system("cls");
            int historychoice;
            do {
                quanlihoadon();
                cout << "Nhap lua chon: ";
                cin >> historychoice;
                switch (historychoice) {
                case 1:
                	system("cls");
                    ivh.DisPlayInvoice();
                    break;
                case 2:
                	system("cls");
                	ivh.DisPlayInvoice();
                    cout << endl;
                    ivh.filterInvoice();
                    break;
                case 3:
                	system("cls");
                    ivh.CP_History(customer);
                    break;
                case 4:
                	system("cls");
                    ivh.Revenue_Profit();
                    break;
                
                default:
                	system("cls");
                    cout << "    ";
                    break;
                }
            } while (historychoice != 0);
            system("cls");
        }break;
        case 4:
        	system("cls");
        	manager.displayProducts();
            cout << "Loc san pham? (y/n):";
            cin >> check;
            cout << endl;
            if (check == 'y') manager.filter();
            ivh.Sale(customer, manager);
            break;
        case 0:
            cout << "Thoat chuong trinh";
            break;
        default:
            cout << "Lua chon khong hop le, vui long chon lai!" << endl;
        }
    }while (choice != 0);
    
    return 0;
}

