


#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Exception : public exception {

	string text;
	int line;
public:

	Exception(string text, int line) {
		this->text = text;
		this->line = line;

	}

	void Message() const {
		cout << text << endl << line << endl;
	}

};
class ContactException :public Exception {
public:
	ContactException(string text, int line) : Exception(text, line) {

	}
};



class Contact {
public:
	static int id;
	int Id;
	string name;
	string phoneNumber;
	Contact() = default;
	Contact(string n, string pn) {
		Id = ++id;
		name = n;
		phoneNumber = pn;
	}

};

int Contact::id = 0;

class DataBase {
public:
	vector<Contact> contact;

	int size = 0;



	void AddContact(Contact& c) {
		contact.push_back(c);

		fstream file("contact.txt", ios::app);
		if (!file.is_open()) {
			file.open("contact.txt", ios::app);
		}

		file << c.name << "\t";
		file << c.Id << "\t";
		file << c.phoneNumber << endl;
		file.close();

	}



	void DeleteByName(string name) {

		if (SearchByName(name)) {

			for (int i = 0; i < contact.size(); i++)
			{
				if (contact[i].name == name) {
					contact.erase(contact.begin() + i);
					break;
				}
			}
		}
		else throw ContactException("Bele Ad yoxdur", __LINE__);
	}

	bool SearchByName(string name) {
		string temp;
		fstream file("contact.txt", ios::in);
		if (file.is_open()) {
			while (!file.eof()) {
				file >> temp;
				for (int i = 0; i < temp.size(); i++)
				{
					if (temp == name) {
						file.close();
						return true;
					}
					else {
						file.close();
						return false;
					}
				}

			}
		}
	}

};







int main() {

	try
	{
		DataBase db;
		Contact c("huseyn", "0000000000000");
		Contact c1("sarxan", "1111111111111");
		db.AddContact(c);
		db.AddContact(c1);
		cout << db.SearchByName("huseyn") << endl;

		db.DeleteByName("huseyn");
		//cout << db.SearchByName("huseyn") << endl;

	}
	catch (Exception ex)
	{
		ex.Message();
	}
}