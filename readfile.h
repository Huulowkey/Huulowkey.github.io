#include<iostream>
#include<fstream>
#include<vector>
#include<iomanip>
#include <string>
#include"Header.h"
using namespace std;

void Doc_file_product(ifstream& filein, Product& pr)
{
	string id_str;
	string purchasePrice_str;
	string salePrice_str;
	string quantity_str;
	getline(filein, id_str, ',');
	getline(filein, pr.name, ',');
	getline(filein, purchasePrice_str, ',');
	getline(filein, salePrice_str, ',');
	getline(filein, quantity_str);
	pr.id = stoi(id_str);
	pr.purchasePrice = stoi(purchasePrice_str);
	pr.salePrice = stoi(salePrice_str);
	pr.quantity = stoi(quantity_str);
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

void xuat_product(Product pr, int index)
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
	cout << setw(20) << left << pr.purchasePrice;
	cout << setw(20) << left << pr.salePrice;
	cout << setw(10) << left << pr.quantity << endl;
}

void test(vector<Product> ds)
{
	for (int i = 0; i < ds.size(); i++)
	{
		xuat_product(ds[i], i);
	}
}

void main1()
{
	ifstream filein;
	filein.open("Text.txt", ios_base::in);
	vector<Product>ds;
	Doc_het_file(filein, ds);
	test(ds);
	filein.close();
	system("pause");
}