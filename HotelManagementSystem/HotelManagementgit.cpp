#include<iostream>
#include<vector>
#include<string>
using namespace std ;

class Customer {

	string name ;
	string id ;
	string mobileNumber ;
	string gender ;
	int age ;

public:
	Customer(string name, string id, string mobileNumber, string gender, int age ) {
		this->name = name ;
		this->id = id ;
		this->mobileNumber = mobileNumber ;
		this->gender = gender ;
		this->age = age ;
	}
	string getName() {
		return name;
	}

	string getID() {
		return id;
	}

	string getMobileNumber() {
		return mobileNumber;
	}

	string getGender() {
		return gender;
	}

	int getAge() {
		return age;
	}

	void display() {
		cout<<"Customer Details :"<<endl<<"Name : "<< name<<endl <<"Mobile Number : "<<mobileNumber<<endl<<"Age : "<<age<<endl<<"Gender :"<<gender<<endl<<"ID : "<<id<<endl ;

	}




};

class Room {

	int RoomNumber ;
	string Type ;
	int price ;
	bool isAvailable ;

public :

	int getRoomNumber() {
		return RoomNumber;
	}

	string getType() {
		return Type;
	}

	int getPrice() {
		return price;
	}

	bool getAvailability() {
		return isAvailable;
	}

	void setAvailability(bool status) {
		isAvailable = status ;
	}
	Room(int RoomNumber, string Type, int price) {
		this->RoomNumber = RoomNumber ;
		this->Type = Type ;
		this->price = price ;
		this->isAvailable = true;
	}

	void RoomDetails() {
		cout<<"Room Number :"<<RoomNumber<<endl <<"Room Type :"<<Type <<endl<<"Price :"<<price<<endl << "Availability : "
		    << (isAvailable ? "Available" : "Booked") << endl;
	}
};

class Booking {

	string BookingID ;
	string CustomerID ;
	int RoomNumber ;
	string CheckInDate ;
	string CheckOutDate ;

public :
	string getBookingID() {
		return BookingID;
	}

	string getCustomerID() {
		return CustomerID;
	}

	int getRoomNumber() {
		return RoomNumber;
	}

	string getCheckInDate() {
		return CheckInDate;
	}

	string getCheckOutDate() {
		return CheckOutDate;
	}

	Booking(string BookingID, string CustomerID, int RoomNumber, string CheckInDate,string CheckOutDate) {
		this->BookingID = BookingID ;
		this->CustomerID = CustomerID;
		this->RoomNumber = RoomNumber ;
		this->CheckInDate = CheckInDate ;
		this->CheckOutDate = CheckOutDate ;
	}

	void BookingDetails() {
		cout<<"Booking ID : "<<BookingID <<endl<<"Customer ID : "<<CustomerID<<endl<<"Room Number :"<<RoomNumber<<endl<<"Check In Date : "<<CheckInDate<<endl<<"Check Out Date : "<<CheckOutDate<<endl ;
	}

};

class Hotel {
private:
	int totalRooms;
	vector<Customer> customers;
	vector<Room> rooms;
	vector<Booking> bookings ;
	int bookingCounter = 1 ;

public:
	Hotel(int totalRooms) {
		this->totalRooms = totalRooms;
	}

	void addCustomer(Customer c) {
		customers.push_back(c);
	}

	void addRoom(Room r) {
		rooms.push_back(r);
	}

	void addBooking(Booking b) {
		bookings.push_back(b) ;
	}

	void displayCustomers() {
		for (Customer &c : customers) {
			c.display();
			cout << "----------------------\n";
		}
	}

	void displayRooms() {
		cout << "\n===== Rooms =====\n";
		for (Room &r : rooms) {
			r.RoomDetails();
			cout << "----------------------\n";
		}
	}

	void displayBookings() {
		cout << "\n===== Bookings =====\n";
		for (Booking &r : bookings) {
			r.BookingDetails();
			cout << "----------------------\n";
		}
	}

	void bookroom(string CustomerID,int RoomNumber) {
		bool customerFound = false ;

		for (Customer &c : customers) {
			if(c.getID() == CustomerID) {
				customerFound = true ;
				break ;
			}

		}
		if(customerFound) {
			cout<<"Customer Found"<<endl<<"Room Number : "<<RoomNumber ;
		}
		else {
			cout<<"Customer Not Found"<<endl ;
			return ;
		}

		bool RoomFound = false ;
		Room *selectedRoom = NULL ;
		for(Room &r : rooms) {
			if(r.getRoomNumber() == RoomNumber) {
				RoomFound = true ;
				selectedRoom = &r ;
				break ;
			}
		}

		if(RoomFound) {

			if(selectedRoom->getAvailability() ) {
				cout<<"Room Available"<<endl ;
			}
			else {
				cout<<"Sorry! Room already Booked."<<endl ;
				return ;
			}
		}
		else {
			cout<<"Room Number Not Found"<<endl ;
			return ;
		}

		string CheckInDate ;
		string CheckOutDate ;

		cout<<"Enter Check In Date : " ;
		cin>> CheckInDate ;
		cout<<"Ënter Check Out Date : " ;
		cin>>CheckOutDate ;

		string bookingID = "B" + to_string(bookingCounter++);
		selectedRoom->setAvailability(false) ;

		Booking b(bookingID,CustomerID,RoomNumber,CheckInDate,CheckOutDate) ;
		bookings.push_back(b) ;

		cout<<endl<<"Room Booked Successfully!"<<endl ;


	}

	void CheckOutRoom(int RoomNumber) {
		bool RoomFound = false ;
		Room *selectedRoom = NULL ;
		for(Room &r : rooms) {
			if(r.getRoomNumber() == RoomNumber) {
				RoomFound = true ;
				selectedRoom = &r ;
				break ;
			}
		}

		if(RoomFound) {
			if(!selectedRoom->getAvailability()) {
				Booking *selectedBooking = NULL;

				for (Booking &b : bookings) {
					if (b.getRoomNumber() == RoomNumber) {
						selectedBooking = &b;
						break;
					}
				}

				if (selectedBooking == NULL) {
					cout << "Booking Not Found!" << endl;
					return;
				}

				generateBill(selectedBooking->getBookingID());

				char ch;
				cout << "\nConfirm Checkout? (Y/N): ";
				cin >> ch;

				if (ch != 'Y' && ch != 'y') {
					cout << "Checkout Cancelled!" << endl;
					return;
				}
				for (auto it = bookings.begin(); it != bookings.end(); it++) {
					if (it->getRoomNumber() == RoomNumber) {
						bookings.erase(it);
						break;
					}
				}
				selectedRoom->setAvailability(true) ;
				cout<<"Check Out Successfull!"<<endl ;
			}
			else cout<<"Room is already vacant !" <<endl;
		}
		else {
			cout<<"Room Not Found!"<<endl ;
			return ;
		}
	}

	void HotelReport() {
		int AvailableRooms = 0 ;
		for(Room &r :rooms) {
			if(r.getAvailability()) AvailableRooms++;
		}
		cout<<endl<<"======= HOTEL REPORT ======="<<endl ;
		cout << "Hotel Capacity : " << totalRooms << endl;
		cout << "Rooms Added    : " << rooms.size() << endl;
		cout<<"Total Customers : "<<customers.size() <<endl<<"Total Rooms : "<<rooms.size()<<endl<<"Booked Rooms : "<<rooms.size()-AvailableRooms<<endl<<"Available Rooms : "<<AvailableRooms<<endl<<"Total Bookings : "<<bookings.size()<<endl;
		cout<<endl<<"============================"<<endl ;
	}
	void generateBill(string bookingId) {
		Booking *selectedBooking = NULL;
		int roomNumber =0 ;
		for (Booking &b : bookings) {
			if(b.getBookingID() == bookingId) {
				selectedBooking = &b ;
				break ;
			}
		}
		if(selectedBooking == NULL) {
			cout << "Booking Not Found!" << endl;
			return;
		}
		roomNumber = selectedBooking->getRoomNumber();

		int price ;
		Room *foundRoom = NULL ;
		for(Room &r : rooms) {
			if(r.getRoomNumber() == roomNumber) {
				foundRoom = &r ;
				break;
			}
		}
		if(foundRoom == NULL) {
			cout<<"Room Not Found!"<<endl ;
			return ;
		}
		price = foundRoom->getPrice() ;

		int days ;
		cout<<"Enter Number of Days : " ;
		cin>> days ;

		int totalAmount = price * days ;
		string CustomerID = selectedBooking->getCustomerID() ;
		Customer *FoundCustomer = NULL ;
		for(Customer &c : customers) {
			if(c.getID() == CustomerID) {
				FoundCustomer = &c;
				break ;
			}
		}
		if(FoundCustomer == NULL) {
			cout << "Customer Not Found!" << endl;
			return;
		}


		cout<<"================================="<<endl ;
		cout<<"           HOTEL INVOICE         "<<endl ;
		cout<<"================================="<<endl ;
		cout<<"Customer Name : "<<FoundCustomer->getName()<<endl ;
		cout<<"Customer Mobile Number : "<<FoundCustomer->getMobileNumber()<<endl ;
		cout<<"Customer ID : "<<FoundCustomer->getID()<<endl ;
		cout<<"Booking ID : "<<selectedBooking->getBookingID()<<endl ;
		cout<<"Room Number : "<<selectedBooking->getRoomNumber()<<endl ;
		cout<<"Room Type : "<<foundRoom->getType()<<endl ;
		cout<<"Room Price : "<<foundRoom->getPrice()<<endl ;
		cout<<"Price Per Day : "<<foundRoom->getPrice()<<endl ;
		cout<<"Check In Date : "<<selectedBooking->getCheckInDate()<<endl ;
		cout<<"Check Out Date : "<<selectedBooking->getCheckOutDate()<<endl ;
		cout<<"Days Stayed : "<<days<<endl ;
		cout<<"---------------------------------"<<endl<<endl ;
		cout<<"Total Amount : "<<totalAmount<<endl ;
		cout<<"================================="<<endl ;
		cout<<"     Thank You! Visit Again      "<<endl ;
		cout<<"================================="<<endl ;
	}

};



int main() {



	Hotel H(100) ;
	int choice ;

	while(true) {

		cout<<endl<<"==============================="<<endl ;
		cout<<"     HOTEL MANAGEMENT SYSTEM       "<<endl ;
		cout<<"==============================="<<endl ;
		cout<<"1.Add Customer"<<endl ;
		cout<<"2.Add Room"<<endl ;
		cout<<"3.Display Customers"<<endl ;
		cout<<"4.Display Rooms"<<endl ;
		cout<<"5.Book Room"<<endl ;
		cout<<"6.Checkout Room" << endl ;
		cout<<"7.Display Bookings"<<endl ;
		cout<<"8.Hotel Report"<<endl ;
		cout<<"9.Exit"<<endl ;

		cout<<endl<<"Enter Choice :" ;
		cin>> choice ;

		switch(choice) {

		case 1 : {
			string name, id,mobileNumber, gender ;
			int age ;

			cout<<endl<<"Enter Customer Name :" ;
			cin>>name ;
			cout<<"Enter Customer ID :" ;
			cin>>id ;
			cout<<"Enter Mobile Number :" ;
			cin>>mobileNumber;
			cout<<"Enter Gender :" ;
			cin>> gender ;
			cout<<"Enter Age :" ;
			cin>>age ;

			Customer A(name,id,mobileNumber,gender,age) ;
			H.addCustomer(A) ;
			cout<<endl<<"Customer Added Successfully"<<endl ;
			break ;

		}

		case 2 : {
			int RoomNumber,price ;
			string Type ;

			cout<<endl<<"Enter Room Number :" ;
			cin>>RoomNumber ;
			cout<<endl<<"Enter Price :" ;
			cin>>price ;
			cout<<"Enter Room Type :" ;
			cin>> Type ;

			Room r(RoomNumber,Type,price) ;

			H.addRoom(r) ;
			cout<<endl<<"Room Added Successfully"<<endl ;
			break ;

		}

		case 3: {
			H.displayCustomers();
			break ;
		}

		case 4: {
			H.displayRooms();
			break ;
		}

		case 5: {
			string customerId ;
			int RoomNumber ;
			cout<<endl<<"Enter Customer ID : " ;
			cin>>customerId ;
			cout<<"Enter Room Number : ";
			cin>>RoomNumber ;

			H.bookroom(customerId,RoomNumber) ;
			break ;
		}
		case 6: {
			int roomNumber;

			cout << "Enter Room Number : ";
			cin >> roomNumber;

			H.CheckOutRoom(roomNumber);
			break;
		}
		case 7: {
			H.displayBookings() ;
			break ;
		}
		case 8: {
			H.HotelReport();
			break;
		}
		case 9: {
			cout << endl<<"Thank You For Using Hotel Management System."<<endl;
			return 0;
		}

		default:

			cout << "\nInvalid Choice! Please Try Again.\n";
		}
	}


	return 0 ;

}