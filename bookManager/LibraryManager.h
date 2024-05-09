

#include "Book.h"
#ifndef _LIBRARYMANAGER_H_
#define _LIBRARYMANAGER_H_

// 어드민 패스워드 
#define ADMIN_PSSWORD 1111

// 책장 크기
#define ROW 3
#define COL 5

using namespace std;

enum UserMenu { BOOK_SEARCH = 1, BOOK_LIST, BOOK_RENTAL, BOOK_RETURN, ADMIN_MODE, EXIT};
enum AdminMenu { BOOK_ADD = 1, BOOK_DELETE, BOOK_CHANGE, GO_MAIN };


class LibraryManager {
	private:		
		int id = 0;
		Book* bookShelf[ROW][COL];
	public:
		// 아이디 생성
		int generateId(){
			return id++;
		}

		// 타이틀 출력
		void showTitle() {
			cout << "***김주희 도서관***\n";
		}

		// 메뉴 출력
		void showMenu() {
			cout << "=====================\n";
			cout << "1. 도서검색\n";
			cout << "2. 도서목록\n";
			cout << "3. 도서대여\n";
			cout << "4. 도서반납\n";
			cout << "5. 관리자모드\n";
			cout << "6. 종료\n";
			cout << "=====================\n";
		}

		// 관리자 메뉴 출력
		void showAdminMenu() {
			cout << "=====================\n";
			cout << "1. 책삽입\n";
			cout << "2. 책삭제\n";
			cout << "3. 책위치변경\n";
			cout << "4. 메인으로\n";
			cout << "=====================\n";
		}

		// 메뉴입력
		int inputMenu() {
			int menuNum = -1;
			cout << "메뉴입력:";
			cin >> menuNum;
			return menuNum;
		}

		// 책 찾기
		void searchBook() {

			bool isEmpty = true;

			for (int i = 0; i < ROW; i++) {
				for (int j = 0; j < COL; j++) {
					if (bookShelf[i][j] != NULL) {
						isEmpty = false;
						goto exit;
					}
				}
			}

			exit:
			if (isEmpty) {
				cout << "출력 현재 삽입된 책이없습니다 관리자에게 문의하여 책을 삽입하세요\n";
			}
			else {
				char name[50];
				cout << "검색할 책 제목 입력 :";
				cin >> name;
				
				for (int i = 0; i < ROW; i++) {
					for (int j = 0; j < COL; j++) {
						if (bookShelf[i][j] != NULL) {
							if (strcmp( bookShelf[i][j]->getName(), name) == 0) {
								cout << "========================책 정 보=======================\n";
								cout << "제목 : " << bookShelf[i][j]->getName() << "\n";
								cout << "장르 : " << bookShelf[i][j]->getGenre() << "\n";
								cout << "저자 : " << bookShelf[i][j]->getAuthor() << "\n";
								cout << "책위치 : " << i << "행 " << j << "열" << "\n";
								cout << "대출상태 : " << bookShelf[i][j]->getRental() << "\n";
								cout << "======================================================\n";
							}
						}
					}
				}

			}
		}

		// 책 목록
		void listBook() {

			cout << "아이디" << "\t\t" << "제목" << "\t\t" << "장르" << "\t\t" << "저자" << "\t\t" << "대출여부" << "\t\t" << "책 위치"  << "\n";
			cout << "====================================================\n";

			for (int i = 0; i < ROW; i++) {
				for (int j = 0; j < COL; j++) {
					if (bookShelf[i][j] != NULL) {						
						cout << bookShelf[i][j]->getId() << "\t\t" << bookShelf[i][j]->getName() << "\t\t" << bookShelf[i][j]->getGenre() 
							<< "\t\t" << bookShelf[i][j]->getAuthor() << "\t\t" << bookShelf[i][j]->getRental() << "\t\t" << i << "행 " << j << "열" << "\n";
					}
				}
			}
			cout << "====================================================\n";
		}

		// 책 대여
		void rentalBook() {
			int id = 0;
			bool isSuccess = false;
			cout << "대여할 책 아이디를 입력:";
			cin >> id;

			for (int i = 0; i < ROW; i++) {
				for (int j = 0; j < COL; j++) {
					if (bookShelf[i][j] != NULL) {
						if (bookShelf[i][j]->getId() == id && bookShelf[i][j]->getRental() == "미대출") {
							 bookShelf[i][j]->setRental(1);
							 isSuccess = true;
						}
					}
				}
			}

			if (isSuccess)  cout << "대여완료\n";
			else cout << "아이디가 없거나 미대출이 아닙니다.\n";
		}

		// 책 반납
		void returnBook() {
			int id = 0;
			bool isSuccess = false;
			cout << "반납 책 아이디를 입력:";
			cin >> id;

			for (int i = 0; i < ROW; i++) {
				for (int j = 0; j < COL; j++) {
					if (bookShelf[i][j] != NULL) {
						if (bookShelf[i][j]->getId() == id && bookShelf[i][j]->getRental() == "대출중") {
							bookShelf[i][j]->setRental(0);		
							isSuccess = true;
						}
					}
				}
			}
			
			if (isSuccess)  cout << "반납완료\n";
			else cout << "아이디가 없거나 대출중이 아닙니다.\n";
		}
		
		// 책 위치 변경
		void changeBook() {

			int id1, id2 = 0;
			Book* bookPtr1 = NULL;
			Book* bookPtr2= NULL;

			cout << "변경 할 책의 아이디(공백구분) :";
			cin >> id1 >> id2;

			for (int i = 0; i < ROW; i++) {
				for (int j = 0; j < COL; j++) {
					if (bookShelf[i][j] != NULL) {
						if (bookShelf[i][j]->getId() == id1) {
							bookPtr1 = bookShelf[i][j];
						}
						if (bookShelf[i][j]->getId() == id2) {
							bookPtr2 = bookShelf[i][j];
						}
					}
				}
			}

			if (bookPtr1 == NULL || bookPtr2 == NULL) {
				cout << "아이디의 입력이 잘못되었습니다.\n";
				return;
			}

			Book tempBook = *bookPtr1;
			*bookPtr1 = *bookPtr2;
			*bookPtr2 = tempBook;

			cout << "변경이 완료되었습니다.\n";

			saveFile();
		}

		// 책 삽입
		void addBook() {
			char name[50];
			char genre[50];
			char author[50];

			cout << "========= 책 추가 =========\n";
			cout << "제목 :";
			cin >> name;
			cout << "장르 :";
			cin >> genre;
			cout << "저자 :";
			cin >> author;

			Book book = Book(generateId(), name, genre, author);
			
			for (int i = 0; i < ROW; i++) {
				for (int j = 0; j < COL; j++) {
					if (bookShelf[i][j] == NULL) {
						bookShelf[i][j] = new Book();
						*bookShelf[i][j] = book;
						goto exit;
					}
				}
			}
			exit: NULL;

			saveFile();

			//cout << "===========================";
		}

		// 파일 저장
		void saveFile() {
			// 파일 입력 (쓰기)
			ofstream outFile("BookShelf.txt", ios_base::out);
			
			for (int i = 0; i < ROW; i++) {
				for (int j = 0; j < COL; j++) {
					if (bookShelf[i][j] == NULL) {
						outFile << "[         " << "]";
					}
					else {
						outFile << "[" << bookShelf[i][j]->getName() << "," << bookShelf[i][j]->getGenre() << "," << bookShelf[i][j]->getAuthor() << "]";
					}
				}

				outFile << "\n";
			}

		}

		// 책 삭제
		void deleteBook() {

			int id = 0;

			cout << "삭제할 책 아이디 입력 :";
			cin >> id;

			for (int i = 0; i < ROW; i++) {
				for (int j = 0; j < COL; j++) {
					if (bookShelf[i][j] != NULL) {
						if (bookShelf[i][j]->getId() == id) {
							bookShelf[i][j] = NULL;
							goto exit;
						}
					}
				}
			}
			exit: NULL;

			saveFile();
		}

		// 관리자 모드
		void changeAdminMode() {
			int password = 0;
			cout << "관리자 암호를 입력 :";
			cin >> password;

			if (password != ADMIN_PSSWORD) {
				cout << "패스워드가 일치하지 않습니다.\n";
				return;
			}

			while (true) {

				showAdminMenu();
				int menuNum = inputMenu();
				switch (menuNum) {
					case BOOK_ADD:
						addBook();
						break;
					case BOOK_DELETE:
						deleteBook();
						break;
					case BOOK_CHANGE:
						changeBook();
						break;
					case GO_MAIN:						
						return; break;					
					default:
						break;
				}
			}

		
		}

		// 종료
		void _exit() {
			exit(0);
		}

		// 초기화
		void initialize() {
			
			// 책장 초기화
			for (int i = 0; i < ROW; i++) {
				for (int j = 0; j < COL; j++) {
					bookShelf[i][j] = NULL;
				}
			}

			// 타이틀 출력
			showTitle();
			// 메뉴출력
			while (true) {
				showMenu();
				// 사용자로 부터 메뉴 번호 입력받음.
				int menuNum = inputMenu();

				// 메뉴에 따른 메소드 실행
				switch (menuNum)
				{
				case BOOK_SEARCH:
					searchBook();
					break;
				case BOOK_LIST:
					listBook();
					break;
				case BOOK_RENTAL:
					rentalBook();
					break;
				case BOOK_RETURN:
					returnBook();
					break;
				case ADMIN_MODE:
					changeAdminMode();
					break;
				case EXIT:
					_exit();
					break;
				default:
					break;
				}
			}
		}

		LibraryManager() {}
};

#endif
