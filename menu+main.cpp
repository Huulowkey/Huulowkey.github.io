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
