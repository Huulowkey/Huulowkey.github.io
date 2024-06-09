#include<iostream>
#include<fstream>
#include<vector>
#include<iomanip>
#include <string>
using namespace std;

struct product
{
	string id;
	string name;
	string originprice;
	string saleprice;
	string quantity;
};

typedef struct product Product;

void Doc_file_product(ifstream& filein, Product& pr)
{
	getline(filein, pr.id, ',');
	getline(filein, pr.name, ',');
	getline(filein, pr.originprice, ',');
	getline(filein, pr.saleprice, ',');
	getline(filein, pr.quantity);
}

void Doc_het_file(ifstream& filein, vector<Product>& ds_product)
{
	while (filein.eof() == false)
	{
		Product pr;
		Doc_file_product(filein, pr);
		ds_product.push_back(pr);
	}
}

void xuat_product(Product pr,int index)
{
	if (index == 0)
	{
		cout << setw(5) << left << "ID";// setw  cho id rong 5 khoang trong can trai
		cout << setw(50) << left << "NAME";
		cout << setw(20) << left << "GIA GOC";
		cout << setw(20) << left << "GIA GOC";
		cout << setw(10) << left << "SO LUONG";
		cout << setfill('-');
		cout << setw(125) << "-" << endl;
	}
	cout << setfill(' ');
	cout << setw(5) << left << pr.id;
	cout << setw(50) << left << pr.name;
	cout << setw(20) << left << pr.originprice;
	cout << setw(20) << left << pr.saleprice;
	cout << setw(10) << left << pr.quantity << endl;
}

void test(vector<Product> ds)
{
	for (int i = 0; i < ds.size(); i++)
	{
		xuat_product(ds[i],i);
	}
}

int main()
{
	ifstream filein;
	filein.open("Text.txt", ios_base::in);
	vector<Product>ds;
	Doc_het_file(filein, ds);
	test(ds);
	filein.close();
	system("pause");
	return 0;
}