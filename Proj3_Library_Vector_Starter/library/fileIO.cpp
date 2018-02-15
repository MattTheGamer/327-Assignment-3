#include "../includes_usr/fileIO.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
/* clears, then loads books from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries in books
 * 			SUCCESS if all data is loaded
 * */
int loadBooks(std::vector<book> &books, const char* filename) {
	ifstream inFile;
	string line;
	string token;
	stringstream ss;
	const char CHAR_TO_SEARCH_FOR = ',';
	book book;

	inFile.open(filename);

	if (!inFile.is_open()) {
		return COULD_NOT_OPEN_FILE;
	} else {
		if (inFile.peek() == std::ifstream::traits_type::eof()) {
			return NO_BOOKS_IN_LIBRARY;
		} else {

			while (!inFile.eof()) {
				getline(inFile, line);
				ss.str(line);

				getline(ss, token, CHAR_TO_SEARCH_FOR);
				book.book_id = atoi(token.c_str());

				getline(ss, book.title, CHAR_TO_SEARCH_FOR);

				getline(ss, book.author, CHAR_TO_SEARCH_FOR);

				getline(ss, token, CHAR_TO_SEARCH_FOR);
				int temp = atoi(token.c_str());

				switch (temp) {

				case 0:
					book.state = UNKNOWN;
					break;
				case 1:
					book.state = IN;
					break;
				case 2:
					book.state = OUT;
					break;
				}
				getline(ss, token, CHAR_TO_SEARCH_FOR);
				book.loaned_to_patron_id = atoi(token.c_str());

				books.push_back(book);

				ss.clear();
			}
			inFile.close();
			return SUCCESS;
		}
	}

}

/* serializes books to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries books (do not create file)
 * 			SUCCESS if all data is saved
 * */
int saveBooks(std::vector<book> &books, const char* filename) {
	ofstream outFile;
	outFile.open(filename);

	if (!outFile.is_open()) {
		return COULD_NOT_OPEN_FILE;
	} else {
		if (books.size() <= 0) {
			return NO_BOOKS_IN_LIBRARY;
		} else {

			//TODO sort array by ID number
			string data;

			for (unsigned int i = 0; i < books.size() - 1; i++) {

				data = std::to_string(books[i].book_id) + "," + books[i].title
						+ "," + books[i].author + ","
						+ std::to_string(books[i].state) + ","
						+ std::to_string(books[i].loaned_to_patron_id);
				outFile << data << std::endl;
			}

			outFile.close();
			return SUCCESS;
		}
	}

}

/* clears, then loads patrons from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons
 * 			SUCCESS if all data is loaded
 * */
int loadPatrons(std::vector<patron> &patrons, const char* filename) {
	ifstream inFile;
	string line;
	string token;
	stringstream ss;
	const char CHAR_TO_SEARCH_FOR = ',';
	patron patron;

	inFile.open(filename);

	if (!inFile.is_open()) {
		return COULD_NOT_OPEN_FILE;
	} else {
		if (inFile.peek() == std::ifstream::traits_type::eof()) {
			return NO_PATRONS_IN_LIBRARY;
		} else {

			while (!inFile.eof()) {
				getline(inFile, line);
				ss.str(line);

				getline(ss, token, CHAR_TO_SEARCH_FOR);
				patron.patron_id = atoi(token.c_str());

				getline(ss, patron.name, CHAR_TO_SEARCH_FOR);

				getline(ss, token, CHAR_TO_SEARCH_FOR);
				patron.number_books_checked_out = atoi(token.c_str());

				patrons.push_back(patron);

				ss.clear();
			}
			inFile.close();
			return SUCCESS;
		}
	}

}

/* serializes patrons to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons  (do not create file)
 * 			SUCCESS if all data is saved
 * */
int savePatrons(std::vector<patron> &patrons, const char* filename) {
	ofstream outFile;
	outFile.open(filename);

	if (!outFile.is_open()) {
		return COULD_NOT_OPEN_FILE;
	} else {
		if (patrons.size() <= 0) {
			return NO_PATRONS_IN_LIBRARY;
		} else {

			//TODO sort array by ID number
			string data;

			for (unsigned int i = 0; i < patrons.size() - 1; i++) {

				data = std::to_string(patrons[i].patron_id) + ","
						+ patrons[i].name + ","
						+ std::to_string(patrons[i].number_books_checked_out);
				outFile << data << std::endl;
			}

			outFile.close();
			return SUCCESS;
		}
	}
}
