#include"Thuvien.h"

using namespace std;
int TyLeDoiRaDiem = 10000;
int TyLeDoiRaTien = 1000;
struct Date {
	int day;
	int month;
	int year;
	friend istream& operator >> (istream& is, Date& d) {
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
int random(int minN, int maxN) 
{
	return minN + rand() % (maxN + 1 - minN);
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
private:
	NodeBill* DsBill;
public:
	InvoiceHistory() : DsBill(NULL) {}
	void DisPlayBill();
	void XuatManHinh(NodeBill* P) {
		cout << P->info.date;
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
		while (1) {
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
	while (P != NULL) {
		cout << "ID: " << P->info.ID << "\tDate: " << P->info.date << "\tKhach hang: " << P->info.Name << endl;
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
	while (P != NULL) {
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
	if (P == NULL) {
		cout << "Khong ton tai hoa don!" << endl;
		return;
	}
	cout << "ID: " << P->info.ID << "\tDate: " << P->info.date << "\tKhach hang: " << P->info.Name;
	ProductManager Q = P->info.List;
	Q.displayProducts();
}

// Can viet tiep phan xuat hoa don
void InvoiceHistory::XuatHoaDon(int id, ProductManager list, Date date, int money) {
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
			cout << "ID: " << Q->product.id << " Name: " << Q->product.name << " Gia: " << Q->product.salePrice << " So luong: " << Q->product.quantity << endl;
		}
	b:
		cout << "So luong can mua: ";
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
	while (P != NULL) {
		if ((P->info.date.day == d.day || d.day == 0) && (P->info.date.month == d.month || d.month == 0) && P->info.date.year == d.year) {
			XuatManHinh(P);
			DoanhThu += P->info.Sum;
			Goc += P->info.TongTienGoc;
		}
		P = P->next;
	}
	cout << "Doanh thu ";
	if (d.day != 0) cout << "ngay " << d.day << " ";
	if (d.month != 0) cout << "thang " << d.month << " ";
	cout << "nam " << d.year << " : " << DoanhThu << ", Loi nhuan: " << DoanhThu - Goc << endl;
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
	while (P != NULL) {
		if (!id.compare(P->info.Name)) {
			XuatManHinh(P);
			P = P->next;
		}
	}
}
