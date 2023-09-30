#include <iostream>
#include <string>
#include <fstream>
using namespace std;
struct Node {
	int data_of_release;
	string title;
	string author;
	int number_of_pages;
	string short_abstract;
	string main_characterts;
	Node* left;
	Node* right;
	bool isEmpty;
	Node(int data_of_release, string title,string author,int number_of_pages,string short_abstract, string main_characterts) {
		this->data_of_release = data_of_release;
		this->title = title;
		this->author = author;
		this->number_of_pages = number_of_pages;
		this->short_abstract = short_abstract;
		this->main_characterts = main_characterts;
		this->left = NULL;
		this->right = NULL;
		this->isEmpty = false;

	}
};
class Binary_tree {
public:
	Node* root = NULL;
	void insert(int data_of_release, string title, string author, int number_of_pages, string short_abstract, string main_characterts) {
		root = create_new_Node(root, data_of_release, title, author, number_of_pages, short_abstract, main_characterts);
	}
	void search_title(string title) {
		search_recursive(root, title);
	}
	void search_series_of_books(string main_characters) {
		search_series_recursive(root, main_characters);
	}
	void print_books(Node* current) {
		if (current == NULL || current->isEmpty==true) {
			return;
		}

		print_books(current->left);
		cout << current->title << current->author << "Publication Date: " << current->data_of_release << endl << "Number of Pages: Approximately " << current->number_of_pages << endl << current->main_characterts << current->short_abstract << endl << endl;
		print_books(current->right);
	}
	void delete_node(string title) {
		root = deleteNode(root, title);
	}
private:
	Node* create_new_Node(Node* current, int data_of_release, string title, string author, int number_of_pages, string short_abstract, string main_characterts) {

		if (current == NULL) {
			return new Node(data_of_release, title, author, number_of_pages, short_abstract, main_characterts);
		}

		if (data_of_release < current->data_of_release) {
			current->left = create_new_Node(current->left, data_of_release, title, author, number_of_pages, short_abstract, main_characterts);
		}
		if (data_of_release > current->data_of_release) {
			current->right = create_new_Node(current->right, data_of_release, title, author, number_of_pages, short_abstract, main_characterts);
		}

		return current;
	}
	void search_recursive(Node* current, string title) {
		if (current == NULL) {
			return;
		}

		search_recursive(current->left, title);
		if (current->title.find(title) != string::npos) {
			cout << current->title << current->author << "Publication Date: " << current->data_of_release << endl << "Number of Pages: Approximately " << current->number_of_pages << endl << current->main_characterts << current->short_abstract << endl << endl;
		}
		search_recursive(current->right, title);

	}
	void search_series_recursive(Node* current, string main_characters) {
		if (current == NULL) {
			return;
		}

		search_recursive(current->left, main_characters);
		if (current->main_characterts.find(main_characters) != string::npos) {
			cout << current->title << current->author << "Publication Date: " << current->data_of_release << endl << "Number of Pages: Approximately " << current->number_of_pages << endl << current->main_characterts << current->short_abstract << endl << endl;
		}
		search_recursive(current->right, main_characters);

	}
	Node* deleteNode(Node* current, string title) {
		if (current == NULL) {
			return current;
		}

		deleteNode(current->left, title);
		if (current->title.find(title) != string::npos) {
			if (current->left == NULL && current->right == NULL) {
				current->isEmpty = true;
				return current;
			}
			if (current->left == NULL && current->right != NULL) {
				Node* temp = current->right;
				delete current;
				return temp;
			}
			if (current->right == NULL && current->left == NULL) {
				Node* temp = root->left;
				delete current;
				return temp; 
			}
			if (current->right != NULL && current->left != NULL) {
				Node* temp = minValueNode(current->right);
				current->title = temp->title;
				current->right = deleteNode(current->right, temp->title);
			}


		}
		deleteNode(current->right, title);
		return current;
	}
	Node* minValueNode(Node* current) {
		Node* temp = current;
		while (temp->left != nullptr) {
			temp = temp->left;
		}
		return temp;
	}
};
struct book {
	string title;
	string author;
	int data_of_release;
	int number_of_pages;
	string short_abstract;
	string list_of_book_dublicate;
	string main_characters;

};
book take_book(string list_of_books) {
	book take_book;
	string data;
	string pages;
	string data_only_number;
	string pages_only_number;
	for (int i = list_of_books.find("Title"); i < list_of_books.find("Author"); i++) {
		take_book.title += list_of_books[i];
	}
	list_of_books.erase(list_of_books.find("Title"), list_of_books.find("Author"));
	for (int i = list_of_books.find("Author"); i < list_of_books.find("Publication"); i++) {
		take_book.author += list_of_books[i];
	}
	list_of_books.erase(list_of_books.find("Author"), list_of_books.find("Publication"));
	for (int i = list_of_books.find("Publication"); i < list_of_books.find("Number"); i++) {
		data += list_of_books[i];
	}
	list_of_books.erase(list_of_books.find("Publication"), list_of_books.find("Number"));
	for (int i = list_of_books.find("Number"); i < list_of_books.find("Main"); i++) {
		pages += list_of_books[i];
	}
	list_of_books.erase(list_of_books.find("Number"), list_of_books.find("Main"));
	for (int i = list_of_books.find("Main"); i < list_of_books.find("Synopsis"); i++) {
		take_book.main_characters += list_of_books[i];
	}
	list_of_books.erase(list_of_books.find("Main"), list_of_books.find("Synopsis"));
	if (take_book.title != "Title: \"Pride and Prejudice\"\n") {
		for (int i = list_of_books.find("Synopsis"); i < list_of_books.find("Title"); i++) {
			take_book.short_abstract += list_of_books[i];
		}
		list_of_books.erase(list_of_books.find("Synopsis"), list_of_books.find("Title"));
	}
	if (take_book.title == "Title: \"Pride and Prejudice\"\n") {
		for (int i = list_of_books.find("Synopsis"); i < list_of_books.find("d.")+2; i++) {
			take_book.short_abstract += list_of_books[i];
		}
	}
	for (int i = data.find('1'); i < data.find('1') + 4; i++) {
		data_only_number +=data[i];
	}
	for (int i = pages.find("y ") + 2; i < pages.find("y ") + 5; i++) {
		pages_only_number += pages[i];
	}
	int publication_data = stoi(data_only_number);
	int number_of_pages = stoi(pages_only_number);
	take_book.data_of_release = publication_data;
	take_book.number_of_pages = number_of_pages;
	take_book.list_of_book_dublicate = list_of_books;
	return take_book;
}
int main()
{
	string list_of_books;
	ifstream take;
	string data;
	string pages;
	Binary_tree tree_of_book;
	book my_book;
	take.open("books.txt");
	if (take.is_open()) {
		cout << "File is open" << endl;
	}
	else {
		cout << "File doesnt open" << endl;
	}
	char ch;
	while (take.get(ch)) {
		list_of_books += ch;
	}
	my_book.list_of_book_dublicate = list_of_books;
	while (my_book.list_of_book_dublicate.find("Title") == 0) {
		my_book = take_book(my_book.list_of_book_dublicate);
		
		tree_of_book.insert(my_book.data_of_release, my_book.title, my_book.author, my_book.number_of_pages, my_book.short_abstract,my_book.main_characters);
	}
	int number;
	int your_choice;
	string add_book;
	string book_what_is_searching;
	string book_delete;
	string characters__what_is_searching;
	while (1 != 0) {
		cout << "1. Print library" << endl << "2. Search book what u want" << endl << "3. Delete book from library" << endl << "4. Search a series of books" << endl << "5. Add book to the library"<<endl<<"6. Leave library"<<endl;
		cin >> your_choice;
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		switch (your_choice) {
		case 1:
			tree_of_book.print_books(tree_of_book.root);
			break;
		case 2:
			cout << endl << "Print book what do u search: ";
			getline(cin, book_what_is_searching);
			cout << endl;
			tree_of_book.search_title(book_what_is_searching);
			break;
		case 3:
			cout << endl << "Print book what do u want to delete: ";
			getline(cin, book_delete);
			
			cout << endl;
			tree_of_book.delete_node(book_delete);
			break;
		case 4:
			cout << endl << "Print characters what do u search: ";
			getline(cin, characters__what_is_searching);
			cout << endl;
			tree_of_book.search_series_of_books(characters__what_is_searching);
			break;
		case 5:
			cout << "Title:";
			getline(cin, add_book);
			my_book.title ="Title: "+ add_book+"\n";
			cout << endl << "Author:";
			getline(cin, add_book);
			my_book.author = "Author: " + add_book+"\n";
			cout << endl << "Publication Date:";
			cin >> number;
			my_book.data_of_release = number;
			cout << endl << "Number of Pages:";
			cin >> number;
			my_book.number_of_pages = number;
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << endl << "Main characters:";
			getline(cin, add_book);
			my_book.main_characters = "Main characters: " + add_book + "\n";
			cout << endl << "Synopsis:";
			getline(cin, add_book);
			my_book.short_abstract = "Synopsis: " + add_book;
			tree_of_book.insert(my_book.data_of_release, my_book.title, my_book.author, my_book.number_of_pages, my_book.short_abstract, my_book.main_characters);
			break;
		case 6:
			return 0;
		}
	}
}


