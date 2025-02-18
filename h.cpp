#include <iostream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

class Room {
public:
    int roomNumber;
    string roomType;
    double price;
    bool isBooked;

    Room(int number, string type, double price) : roomNumber(number), roomType(type), price(price), isBooked(false) {}
};

class Payment {
public:
    int roomNumber;
    double amount;
    string paymentMethod;

    Payment(int number, double amt, string method) : roomNumber(number), amount(amt), paymentMethod(method) {}
};

class FoodItem {
public:
    string name;
    double price;
    int quantity;

    FoodItem(string name, double price, int quantity) : name(name), price(price), quantity(quantity) {}
};

class Hotel {
private:
    vector<Room> rooms;
    vector<Payment> payments;
    vector<FoodItem> foodItems;
    string adminUsername;
    string adminPassword;

public:
    Hotel() {
        adminUsername = "admin";
        adminPassword = "password";
    }

    void addRoom(int number, string type, double price) {
        rooms.push_back(Room(number, type, price));
    }

    void displayRooms() {
        cout << "Available Rooms:\n";
        for (const auto& room : rooms) {
            cout << "Room Number: " << room.roomNumber 
                 << ", Type: " << room.roomType 
                 << ", Price: " << room.price 
                 << ", Booked: " << (room.isBooked ? "Yes" : "No") << endl;
        }
    }

    void bookRoom(int number) {
        for (auto& room : rooms) {
            if (room.roomNumber == number) {
                if (!room.isBooked) {
                    double advanceAmount = 0;
                    if (room.roomType == "Single") {
                        advanceAmount = 375;
                    } else if (room.roomType == "Double") {
                        advanceAmount = 1125;
                    } else if (room.roomType == "Suite") {
                        advanceAmount = 3375;
                    } else if (room.roomType == "Presidential Suite") {
                        advanceAmount = 6375;
                    } else if (room.roomType == "Executive Suite") {
                        advanceAmount = 9375;
                    }

                    cout << "Room price is: " << room.price << endl;
                    cout << "Advance amount is: " << advanceAmount << endl;

                    string method;
                    cout << "Enter payment method: ";
                    cin >> method;

                    // Validate payment method
                    if (method.empty()) {
                        cout << "Payment method cannot be empty." << endl;
                        return;
                    }

                    payments.push_back(Payment(number, advanceAmount, method));
                    room.isBooked = true;
                    cout << "Room " << number << " has been booked successfully." << endl;
                    cout << "Balance amount to be paid: " << (room.price - advanceAmount) << endl;
                } else {
                    cout << "Room " << number << " is already booked." << endl;
                }
                return;
            }
        }
        cout << "Room " << number << " not found." << endl;
    }

    void addFoodItem(string name, double price, int quantity) {
        foodItems.push_back(FoodItem(name, price, quantity));
    }

    void displayFoodItems() {
        cout << "Available Food Items:\n";
        for (const auto& item : foodItems) {
            cout << "Name: " << item.name << ", Price: " << item.price << ", Quantity: " << item.quantity << endl;
        }
    }

    void orderFoodItem(string name) {
        for (auto& item : foodItems) {
            if (item.name == name) {
                if (item.quantity > 0) {
                    item.quantity--;
                    cout << "Food item " << name << " ordered successfully. Price: " << item.price << endl;
                } else {
                    cout << "Food item " << name << " is out of stock." << endl;
                }
                return;
            }
        }
        cout << "Food item " << name << " not found." << endl;
    }

    bool adminLogin(string username, string password) {
        return username == adminUsername && password == adminPassword;
    }
};

int main() {
    Hotel hotel;
    hotel.addRoom(101, "Single", 500);
    hotel.addRoom(102, "Single", 500);
    hotel.addRoom(103, "Single", 500);
    hotel.addRoom(104, "Single", 500);
    hotel.addRoom(105, "Single", 500);
    hotel.addRoom(106, "Single", 500);
    hotel.addRoom(107, "Single", 500);

    hotel.addRoom(201, "Double", 1500);
    hotel.addRoom(202, "Double", 1500);
    hotel.addRoom(203, "Double", 1500);
    hotel.addRoom(204, "Double", 1500);
    hotel.addRoom(205, "Double", 1500);
    hotel.addRoom(206, "Double", 1500);
    hotel.addRoom(207, "Double", 1500);
    
    hotel.addRoom(301, "Suite", 4500);
    hotel.addRoom(302, "Suite", 4500);
    hotel.addRoom(303, "Suite", 4500);
    hotel.addRoom(304, "Suite", 4500);
    
    hotel.addRoom(401, "Presidential Suite", 8500);
    hotel.addRoom(402, "Presidential Suite", 8500);
    hotel.addRoom(403, "Presidential Suite", 8500);

    hotel.addRoom(501, "Executive Suite", 12500);
    hotel.addRoom(502, "Executive Suite", 12500);

    // Add food items
    hotel.addFoodItem("Dosai", 80, 200);
    hotel.addFoodItem("Parotta", 50, 180);
    hotel.addFoodItem("Noodles", 100, 150);
    hotel.addFoodItem("Pasta", 90, 100);

    hotel.addFoodItem("Biriyani", 120, 250);
    hotel.addFoodItem("Mushroom Rice", 85, 250);
    hotel.addFoodItem("Chicken Rice", 85, 300);
    hotel.addFoodItem("Veg Rice", 70, 200);

    hotel.addFoodItem("Ice Cream", 40, 350);
    hotel.addFoodItem("Cake", 60, 340);
    hotel.addFoodItem("Pastry", 30, 300);
    hotel.addFoodItem("Milkshake", 70, 180);

    hotel.addFoodItem("Coffee", 20, 500);
    hotel.addFoodItem("Tea", 15, 500); 
    hotel.addFoodItem("Coke", 25, 350);  
    hotel.addFoodItem("Pepsi", 25, 350);

    int choice;
    do {
        cout << "\n1. Display Rooms\n2. Book Room\n3. Add Food Item\n4. Display Food Items\n5. Order Food Item\n6. Exit\nEnter your choice: ";
        cin >> choice;

        // Validate choice input
        if (cin.fail() || choice < 1 || choice > 6) {
            cin.clear(); // clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Invalid choice. Please try again." << endl;
            continue;
        }

        switch (choice) {
            case 1:
                hotel.displayRooms();
                break;
            case 2:
                int roomNumber;
                cout << "Enter room number to book: ";
                cin >> roomNumber;

                // Validate room number input
                if (cin.fail() || roomNumber <= 0) {
                    cin.clear(); 
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                    cout << "Invalid room number. Please try again." << endl;
                    continue;
                }

                hotel.bookRoom(roomNumber);
                break;
            case 3:
                {
                    string foodName;
                    double foodPrice;
                    int foodQuantity;
                    cout << "Enter food item name: ";
                    cin.ignore();
                    getline(cin, foodName);
                    cout << "Enter food item price: ";
                    cin >> foodPrice;
                    cout << "Enter food item quantity: ";
                    cin >> foodQuantity;

                    // Validate food price and quantity input
                    if (cin.fail() || foodPrice <= 0 || foodQuantity <= 0) {
                        cin.clear(); 
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                        cout << "Invalid food price or quantity. Please try again." << endl;
                        continue;
                    }

                    hotel.addFoodItem(foodName, foodPrice, foodQuantity);
                    cout << "Food item added successfully." << endl;
                }
                break;
            case 4:
                hotel.displayFoodItems();
                break;
            case 5:
                {
                    string foodName;
                    cout << "Enter food item name: ";
                    cin.ignore();
                    getline(cin, foodName);

                    hotel.orderFoodItem(foodName);
                }
                break;
            case 6:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);

    return 0;
}