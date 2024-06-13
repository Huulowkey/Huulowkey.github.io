

#include"Header.h"
#include"Costumer.h"
#include"Header1.h"
void manager() 
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
    /*case 10:
        manager.saveToFile("Text.txt");
        break;
    */
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
        cout << "\t\t\t|                                Buyer Menu                                    |\n";
        cout << "\t\t\t|                                                                                |\n";
        cout << "\t\t\t|________________________________________________________________________________|\n";
        cout << "\n\t\t\t\t|______________________   1) Add costumer   _____________________|";
        cout << "\n\t\t\t\t|                                                                |";
        cout << "\n\t\t\t\t|______________________   2) Ban hang       _____________________|";
        cout << "\n\t\t\t\t|                                                                |";
        cout << "\n\t\t\t\t|______________________     3) Filter       _____________________|";
        cout << "\n\t\t\t\t|                                                                |";
        cout << "\n\t\t\t\t|______________________4) update khách hàng _____________________|";
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
void menu()
{
    int choice;
    do {
        cout << endl;
        cout << "\t\t\t_________________________________________________________________________________\n";
        cout << "\t\t\t|                                                                                |\n";
        cout << "\t\t\t|                                      Menu                                      |\n";
        cout << "\t\t\t|                                                                                |\n";
        cout << "\t\t\t|________________________________________________________________________________|\n";
        cout << "\n\t\t\t\t|________________________  1) Manager  _______________________|";
        cout << "\n\t\t\t\t|                                                             |";
        cout << "\n\t\t\t\t|________________________   2) Buyer   _______________________|";
        cout << "\n\t\t\t\t|                                                             |";
        cout << "\n\t\t\t\t|________________________   3) Exit    _______________________|";
       
        cout << endl;
        cout << "Lua chon cua ban :";
        cin >> choice;

        switch (choice) {
        case 1:
            manager();
            break;
        case 2:
            buyer();
            break;
        case 3:
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

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
