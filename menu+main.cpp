
void quanlisanpham()
{
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
        cout << "\n\t\t\t\t|                                                                |";
        cout << "\n\t\t\t\t|______________________ 2) Cap nhat san pham _____________________|";
        cout << "\n\t\t\t\t|                                                                |";
        cout << "\n\t\t\t\t|______________________ 3) Xoa san pham      _____________________|";
        cout << "\n\t\t\t\t|                                                                |";
        cout << "\n\t\t\t\t|______________________ 4) Hien thi san pham _____________________|";
        cout << "\n\t\t\t\t|                                                                |";
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
void quanlikhachhang()
{
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

void quanlihoadon()
{
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

void menu()
{
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
int main()
{
    srand((int)time(0));
    menu();
    return 0;
}
