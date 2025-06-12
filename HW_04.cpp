#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std; // namespace std 사용

class Book {
public:
    string title;
    string author;

    Book(const string& title, const string& author)
        : title(title), author(author) {
    }
};

class BookManager {
private:
    vector<Book> books; // 책 목록 저장

public:
    // 책 추가 메서드
    void addBook(const string& title, const string& author) {
        books.push_back(Book(title, author)); // push_back 사용
        cout << "책이 추가되었습니다: " << title << " by " << author << endl;
    }

    // 모든 책 출력 메서드
    void displayAllBooks() const {
        if (books.empty()) {
            cout << "현재 등록된 책이 없습니다." << endl;
            return;
        }

        cout << "현재 도서 목록:" << endl;
        for (size_t i = 0; i < books.size(); i++) { // 일반적인 for문 사용
            cout << "- " << books[i].title << " by " << books[i].author << endl;
        }
    }

    void searchByTitle(const string& title) const{
        for (const auto& book : books) {
            if (book.title == title) {
                cout << "책 제목 : " << book.title << "저자 : " << book.author << "\n";
                return;
            }
        }
        cout << "책 제목 : " << title << "을 찾을 수 없습니다." << "\n";
    }

    void searchByAuthor(string author) {
        bool found = false;
        for (const auto& book : books) {
            if (book.author == author) {
                cout << "책 제목 : " << book.title << "저자 : " << book.author << "\n";
                found = true;
            }
        }
        if (!found) {
            cout << "저자 : " << author << "의 책을 찾을 수 없습니다." << "\n";
        }
    }

    const vector<Book>& getAllBooks() const {
        return books;
    }
};

class BorrowManager {
private:
    unordered_map<string, int> stock;
public:
    void initializeStock(const Book& book, int quantity = 3) {
        stock[book.title] = quantity;
    }

    void borrowBook(const string& title) {
        auto it = stock.find(title);
        if (it != stock.end()) {
            if (it->second > 0) {
                it->second--;
                cout << title << "대여 " << it->second << "권 남음" << "\n";
            }
            else {
                cout << title << " 남은 권수가 없어 대여 불가능" << "\n";
            }
        }
        else {
            cout << title << "은 존재하지 않음" << "\n";
        }
    }
    

    void borrowAuthor(const string& author, const vector<Book>& books) {
        for (const auto& book : books) {
            if (book.author == author && stock[book.title] > 0) {
                stock[book.title]--;
                cout << "대여 책 이름 " << book.title << " 저자 " << book.author << " 남은 권수 " << stock[book.title] << "\n";
                return;
            }
        }
        cout << "저자 " << author << " 의 대여 가능한 책이 없습니다." << "\n";
    }

    void returnBook(string& title) {
        auto it = stock.find(title);
        if (it != stock.end()) {
            it->second++;
            cout << title << "반납 " << it->second << "권 남음" << "\n";
        }
        else {
            cout << title << "은 존재하지 않음" << "\n";
        }
    }

    void displayStock() const {
        cout << "현황" << "\n";
        for (const auto& it : stock) {
            cout << it.first << "는 현재 " << it.second << "권 남음" << "\n";
        }
    }

    void canBorrowStock(const string& title) const {
        auto it = stock.find(title);
        if (it != stock.end()) {
            cout << it->first << "는 현재 " << it->second << "권 남음" << "\n";
        }
        else {
            cout << it->first << "는 현재 대여 불가능" << "\n";
        }
    }
};

int main() {
    BookManager manager;
    BorrowManager borrowManager;

    // 도서관 관리 프로그램의 기본 메뉴를 반복적으로 출력하여 사용자 입력을 처리합니다.
    // 프로그램 종료를 선택하기 전까지 계속 동작합니다.
    while (true) {
        cout << "\n도서관 관리 프로그램" << endl;
        cout << "1. 책 추가" << endl; // 책 정보를 입력받아 책 목록에 추가
        cout << "2. 모든 책 출력" << endl; // 현재 책 목록에 있는 모든 책 출력
        cout << "3. 종료" << endl; // 프로그램 종료
        cout << "4. 책 제목 검색" << "\n";
        cout << "5. 저자 검색" << "\n";
        cout << "6. 책 제목 대여" << "\n";
        cout << "7. 책 제목 반납" << "\n";
        cout << "8. 책 재고 확인" << "\n";
        cout << "9. 대여 가능 여부를 확인" << "\n";
        cout << "10. 책 저자 대여" << "\n";
        cout << "선택: ";

        string title, author;
        int choice; // 사용자의 메뉴 선택을 저장
        cin >> choice;


        if (choice == 1) {
            // 1번 선택: 책 추가
            // 사용자로부터 책 제목과 저자명을 입력받아 BookManager에 추가합니다.
            cout << "책 제목: ";
            cin.ignore(); // 이전 입력의 잔여 버퍼를 제거
            getline(cin, title); // 제목 입력 (공백 포함)
            cout << "책 저자: ";
            getline(cin, author); // 저자명 입력 (공백 포함)
            manager.addBook(title, author); // 입력받은 책 정보를 추가
        }
        else if (choice == 2) {
            // 2번 선택: 모든 책 출력
            // 현재 BookManager에 저장된 책 목록을 출력합니다.
            manager.displayAllBooks();
        }
        else if (choice == 3) {
            // 3번 선택: 종료
            // 프로그램을 종료하고 사용자에게 메시지를 출력합니다.
            cout << "프로그램을 종료합니다." << endl;
            break; // while 루프 종료
        }
        else if (choice == 4) {
            cout << "검색할 책 제목: ";
            getline(cin, title);
            manager.searchByTitle(title);
        }
        else if (choice == 5) {
            cout << "검색할 책 저자: ";
            getline(cin, author);
            manager.searchByAuthor(author);
        }
        else if (choice == 6) {
            cout << "대여할 책 제목: ";
            getline(cin, title);
            borrowManager.borrowBook(title);
        }
        else if (choice == 7) {
            cout << "반납할 책 제목: ";
            getline(cin, title);
            borrowManager.returnBook(title);
        }
        else if (choice == 8) {
            borrowManager.displayStock();
        }
        else if (choice == 9) {
            cout << "대여 가능 여부를 확인할 책 제목: ";
            getline(cin, title);
            borrowManager.canBorrowStock(title);
        }
        else if (choice == 10) {
            cout << "대여할 책 저자: ";
            getline(cin, author);
            borrowManager.borrowAuthor(author, manager.getAllBooks());
        }
        else {
            // 잘못된 입력 처리
            // 메뉴에 없는 번호를 입력했을 경우 경고 메시지를 출력합니다.
            cout << "잘못된 입력입니다. 다시 시도하세요." << endl;
        }
    }

    return 0; // 프로그램 정상 종료
}