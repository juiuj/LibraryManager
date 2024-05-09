#ifndef _BOOK_H_
#define _BOOK_H_

class Book {
	int id;
	char name[50];  // 책이름
	char genre[50]; // 장르
	char author[50]; // 저자
	int  rental; // 대출여부 (  0 : 미대출, 1 : 대출중)
public:
	Book(int _id, const char _name[], const char _genre[], const char _author[]) {
		id = _id;
		rental = 0;
		strcpy(name, _name);
		strcpy(genre, _genre);
		strcpy(author, _author);
	}
	Book() {};
	~Book() {};
	char* getName();
	char* getGenre();
	char* getAuthor();
	int getId();
	const char* getRental();
	void setRental(int rental); 
};

int Book::getId() {
	return id;
};

const char* Book::getRental() {
	if (rental == 0) {
		return "미대출";
	}
	else {
		return "대출중";
	}	
};

void Book::setRental(int _rental) {
	rental = _rental;
}

char* Book::getName() {
	return name;
};

char* Book::getGenre() {
	return genre;
};

char* Book::getAuthor() {
	return author;
};

#endif