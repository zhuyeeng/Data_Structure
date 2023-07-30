#include "User.h"
#include "Admin.h"
#include <iostream>
#include <chrono>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
using namespace std::chrono;
#include <chrono>
#include <ctime>
#include <iomanip>

// Structure to represent a user
struct Users {
    int userId;
    string username;
    string password;
    string email;
    string loginDate;
    string userRole;

    Users* UserNext;
    Users* UserPrev;
}*UserHead, *UserTail;

// Structure to represent a university
struct UniNode {
    // University attributes
    string Rank;
    string Institution;
    string LocationCode;
    string Location;
    string ArScore;
    string ArRank;
    string ErScore;
    string ErRank;
    string FsrScore;
    string FsrRank;
    string CpfScore;
    string CpfRank;
    string IfrScore;
    string IfrRank;
    string IsrScore;
    string IsrRank;
    string IrnScore;
    string IrnRank;
    string GerScore;
    string GerRank;
    string ScoreScaled;

    // Pointers to previous and next nodes
    UniNode* prev;
    UniNode* next;
}*Uniheads, *Unitails;


class UserFunction {
    Users* UserHead = NULL;
    Users* UserTail = NULL;
    int lastUserId = 0; // Track the last userId from the file

public:
    Users* createNewNode(int userId, string username, string password, string email, string time, string userRole) {
        Users* UserNewNode = new Users;
        UserNewNode->userId = userId;
        UserNewNode->username = username;
        UserNewNode->password = password;
        UserNewNode->email = email;
        UserNewNode->loginDate = time;
        UserNewNode->userRole = userRole;
        UserNewNode->UserNext = NULL;
        return UserNewNode;
    }

    void InsertToEndOfList(int userId, string username, string password, string email, string time, string userRole) {
        Users* UserNewNode = createNewNode(userId, username, password, email, time, userRole);
        if (UserHead == NULL) {
            UserHead = UserTail = UserNewNode;
        }
        else {
            UserNewNode->UserPrev = UserTail;
            UserTail->UserNext = UserNewNode;
            UserTail = UserNewNode;
        }
    }

    void ReadUserData() {
        ifstream file("user.csv");
        string line;
        getline(file, line); // Ignore the first line (header)

        if (file.is_open()) {
            while (getline(file, line)) {
                stringstream ss(line);
                string userId, username, password, email, loginTime, userRole;
                getline(ss, userId, ',');
                getline(ss, username, ',');
                getline(ss, password, ',');
                getline(ss, email, ',');
                getline(ss,loginTime, ',');
                getline(ss, userRole, ',');

                int currentUserId = stoi(userId);
                lastUserId = max(lastUserId, currentUserId);
                InsertToEndOfList(currentUserId, username, password, email, loginTime, userRole);
            }
            file.close();
        }
        else {
            cout << "Failed to open the file." << endl;
        }
    }

    string getCurrentDateTime() {
        // Get the current system time
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

        // Convert the system time to a time_t value
        std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

        // Convert the time_t value to a string representation
        std::stringstream ss;
        ss << std::put_time(std::localtime(&currentTime), "%Y-%m-%d %H:%M:%S");

        return ss.str();
    }

    void RegisterUser(string username, string password, string email, string time, string userRole) {
        int newUserId = lastUserId + 1;
        
        InsertToEndOfList(newUserId, username, password, email, time, userRole);
        lastUserId = newUserId;
        

        cout << "Registration successful! UserId: " << newUserId << endl;
		cout << endl;
    }

	Users* UserLogin(string username, string password) {
        if(UserHead == NULL) {
            return NULL;
        }
        Users* current = UserHead;
        while(current != NULL) {
            if(current->username == username && current->password == password) {
                // Update login time
                current->loginDate = getCurrentDateTime();
                return current;
            }
            current = current->UserNext;
        }
        return NULL;
    }

    void SaveUserData() {
        ofstream file("user.csv");
        if (file.is_open()) {
            file << "userId,username,password,email,loginTime,userRole" << endl;
            Users* curr = UserHead;
            while (curr != NULL) {
                file << curr->userId << "," << curr->username << "," << curr->password << "," << curr->email << "," << curr->loginDate << "," << curr->userRole << endl;
                curr = curr->UserNext;
            }
            file.close();
            cout << "User data saved successfully." << endl;
        }
        else {
            cout << "Failed to open the file for writing." << endl;
        }
    }

    ~UserFunction() {
        SaveUserData();
        Users* curr = UserHead;
        while (curr != NULL) {
            Users* temp = curr;
            curr = curr->UserNext;
            delete temp;
        }
        UserHead = UserTail = NULL;
    }
};

class Guest {
public:
    UniNode* UnicreateNewNode(string Rank, string Institution, string LocationCode,
        string Location, string ArScore, string ArRank, string ErScore,
        string ErRank, string FsrScore, string FsrRank, string CpfScore,
        string CpfRank, string IfrScore, string IfrRank, string IsrScore,
        string IsrRank, string IrnScore, string IrnRank, string GerScore,
        string GerRank, string ScoreScaled)
    {
        UniNode* UninewNode = new UniNode;
        UninewNode->Rank = Rank;
        UninewNode->Institution = Institution;
        UninewNode->LocationCode = LocationCode;
        UninewNode->Location = Location;
        UninewNode->ArScore = ArScore;
        UninewNode->ArRank = ArRank;
        UninewNode->ErScore = ErScore;
        UninewNode->ErRank = ErRank;
        UninewNode->FsrScore = FsrScore;
        UninewNode->FsrRank = FsrRank;
        UninewNode->CpfScore = CpfScore;
        UninewNode->CpfRank = CpfRank;
        UninewNode->IfrScore = IfrScore;
        UninewNode->IfrRank = IfrRank;
        UninewNode->IsrScore = IsrScore;
        UninewNode->IsrRank = IsrRank;
        UninewNode->IrnScore = IrnScore;
        UninewNode->IrnRank = IrnRank;
        UninewNode->GerScore = GerScore;
        UninewNode->GerRank = GerRank;
        UninewNode->ScoreScaled = ScoreScaled;

        UninewNode->prev = nullptr;
        UninewNode->next = nullptr;

        return UninewNode;
    }

    void ReadUniData() {
    Guest list;
    string Rank, Institution, LocationCode, Location, ArScore, ArRank, ErScore, ErRank, FsrScore, FsrRank,
        CpfScore, CpfRank, IfrScore, IfrRank, IsrScore, IsrRank, IrnScore, IrnRank, GerScore, GerRank, ScoreScaled;
    ifstream file;
    file.open("2023 QS World University Rankings.csv");
    getline(file, Rank);
    if (!file.is_open()) {
        cout << "Failed to open the file." << endl;
        return;
    }
    while (file.good()) {
        getline(file, Rank, ',');
        getline(file, Institution, ',');
        getline(file, LocationCode, ',');
        if (LocationCode.length() != 2) {
            Institution += ", ";
            Institution += LocationCode;
            getline(file, LocationCode, ',');
        }
        getline(file, Location, ',');
        getline(file, ArScore, ',');
        getline(file, ArRank, ',');
        getline(file, ErScore, ',');
        getline(file, ErRank, ',');
        getline(file, FsrScore, ',');
        getline(file, FsrRank, ',');
        getline(file, CpfScore, ',');
        getline(file, CpfRank, ',');
        getline(file, IfrScore, ',');
        getline(file, IfrRank, ',');
        getline(file, IsrScore, ',');
        getline(file, IsrRank, ',');
        getline(file, IrnScore, ',');
        getline(file, IrnRank, ',');
        getline(file, GerScore, ',');
        getline(file, GerRank, ',');
        getline(file, ScoreScaled);
        if (Rank == "") {
            break;
        }
        else if (Rank == "Rank") {
            continue;
        }
        list.UniInsert(Rank, Institution, LocationCode, Location, ArScore, ArRank, ErScore, ErRank, FsrScore, FsrRank,
            CpfScore, CpfRank, IfrScore, IfrRank, IsrScore, IsrRank, IrnScore, IrnRank, GerScore, GerRank, ScoreScaled);
    }
    file.close();
}

    void UniInsert(string Rank, string Institution, string LocationCode,
        string Location, string ArScore, string ArRank, string ErScore,
        string ErRank, string FsrScore, string FsrRank, string CpfScore,
        string CpfRank, string IfrScore, string IfrRank, string IsrScore,
        string IsrRank, string IrnScore, string IrnRank, string GerScore,
        string GerRank, string ScoreScaled)
    {
        UniNode* UninewNode = UnicreateNewNode(Rank, Institution, LocationCode, Location, ArScore, ArRank, ErScore,
            ErRank, FsrScore, FsrRank, CpfScore, CpfRank, IfrScore, IfrRank, IsrScore, IsrRank, IrnScore,
            IrnRank, GerScore, GerRank, ScoreScaled);
        if (Uniheads == nullptr) {
            Uniheads = Unitails = UninewNode;
        }
        else {
            Unitails->next = UninewNode;
            UninewNode->prev = Unitails;
            Unitails = UninewNode;
        }
    }

    //merge sort
    UniNode* merge(UniNode* left, UniNode* right) {
        if (left == nullptr)
            return right;
        if (right == nullptr)
            return left;

        UniNode* result = nullptr;
        if (left->Institution <= right->Institution) {
            result = left;
            result->next = merge(left->next, right);
        }
        else {
            result = right;
            result->next = merge(left, right->next);
        }
        return result;
    }

    UniNode* getMiddle(UniNode* Uninode) {
        if (Uninode == nullptr || Uninode->next == nullptr)
            return Uninode;

        UniNode* slow = Uninode;
        UniNode* fast = Uninode->next;

        while (fast != nullptr) {
            fast = fast->next;
            if (fast != nullptr) {
                slow = slow->next;
                fast = fast->next;
            }
        }
        return slow;
    }

    UniNode* mergeSort(UniNode* Uninode) {
        if (Uninode == nullptr || Uninode->next == nullptr)
            return Uninode;

        UniNode* middle = getMiddle(Uninode);
        UniNode* nextToMiddle = middle->next;
        middle->next = nullptr;

        UniNode* left = mergeSort(Uninode);
        UniNode* right = mergeSort(nextToMiddle);

        return merge(left, right);
    }

	//quick sort
    UniNode* partition(UniNode* low, UniNode* high) {
        string pivot = high->Institution;
        UniNode* i = low->prev;

        for (UniNode* j = low; j != high; j = j->next) {
            // Convert the Rank to integer for comparison
            string rank_i = j->Institution;
            string pivot_i = pivot;

            if (rank_i <= pivot_i) {
                i = (i == nullptr) ? low : i->next;
                swap(i->Institution, j->Institution);
                // Swap other attributes if needed
            }
        }
        i = (i == nullptr) ? low : i->next;
        swap(i->Institution, high->Institution);
        // Swap other attributes if needed

        return i;
    }

    void quickSort(UniNode* low, UniNode* high) {
        if (high != nullptr && low != high && low != high->next) {
            UniNode* pivot = partition(low, high);
            quickSort(low, pivot->prev);
            quickSort(pivot->next, high);
        }
    }

    void display() {
        UniNode* current = Uniheads;
        while (current != nullptr) {
            cout << "Rank: " << current->Rank << endl;
            cout << "Institution: " << current->Institution << endl;
            cout << "Location Code: " << current->LocationCode << endl;
            cout << "Location: " << current->Location << endl;
            cout << "Academic Reputation Score: " << current->ArScore << endl;
            cout << "Academic Reputation Rank: " << current->ArRank << endl;
            cout << "Employer Reputation Score: " << current->ErScore << endl;
            cout << "Employer Reputation Rank: " << current->ErRank << endl;
            cout << "Faculty/Student Ratio Score: " << current->FsrScore << endl;
            cout << "Faculty/Student Ratio Rank: " << current->FsrRank << endl;
            cout << "Citations Per Faculty Score: " << current->CpfScore << endl;
            cout << "Citations Per Faculty Rank: " << current->CpfRank << endl;
            cout << "International Faculty Ratio Score: " << current->IfrScore << endl;
            cout << "International Faculty Ratio Rank: " << current->IfrRank << endl;
            cout << "International Student Ratio Score: " << current->IsrScore << endl;
            cout << "International Student Ratio Rank: " << current->IsrRank << endl;
            cout << "International Research Network Score: " << current->IrnScore << endl;
            cout << "International Research Network Rank: " << current->IrnRank << endl;
            cout << "Employment Outcome Score: " << current->GerScore << endl;
            cout << "Employment Outcome Rank: " << current->GerRank << endl;
            cout << "Score Scaled: " << current->ScoreScaled << endl;

            cout << endl;
            current = current->next;
        }
        cout << "End and Success" << endl;
    }

//linear search
UniNode* UniSearch(string name) {
    UniNode* current = Uniheads;
    while (current != nullptr) {
        if (current->Institution == name) {
            return current;
        }
        current = current->next;
    }
    return nullptr; // University not found
}

//BinarySearch
UniNode* binarySearch(UniNode* Uniheads, string target) {
    UniNode* low = Uniheads;
    UniNode* high = nullptr;

    while (low != high) {
        UniNode* mid = low;
        int cmp = target.compare(mid->Institution);

        if (cmp < 0)
            high = mid;
        else if (cmp > 0)
            low = mid->next;
        else
            return mid;
    }

    return nullptr;
}
};


int main() {
	Users users;
	Guest guest;
    UserFunction userFunction;
    int choice;
    string currentDateTime = userFunction.getCurrentDateTime();
    userFunction.ReadUserData();
	guest.ReadUniData();

    do {
        cout << "*** University Finder System ***" << endl;
        cout << "To perform an action, enter: " << endl;
        cout << "1.Display all the University" << endl;
        cout << "2 Login" << endl;
        cout << "3 Register" << endl;
        cout << "4 Select a search algorithm" << endl;
        cout << "5 Select a sort algorithm" << endl;
        cout << "6 Exit System" << endl;
        cout << "*******************************" << endl;
        cout << "Please enter your choice: " << endl;
        
        
        cin >> choice;

        switch (choice) {
        case 1:{
            guest.display();
        }
        break;
        case 2:
            {
                string username, password;
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;
                Users* loggedInUser = userFunction.UserLogin(username, password);
                if (loggedInUser != NULL) {
                    cout << endl;
                    cout << "Login successful!" << endl;
                    cout << "Username: " << loggedInUser->username << endl;
                    cout << "Login Time: " << loggedInUser->loginDate << endl;
                    if(loggedInUser->userRole == "admin"){
                        cout << "Welcome Admin" << endl;
                        AdminInterface(username);
                    }else if(loggedInUser->userRole == "user"){
                        cout << "Welcome to Our System" << endl;
                        UserMain();
                    }
                } else {
                    cout << "Invalid username or password." << endl;
                }
            }
            break;
        case 3:
            {
                string username, password, email;
				string userRole = "user";
                string time = currentDateTime;
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;
                cout << "Enter email: ";
                cin >> email;

                userFunction.RegisterUser(username, password, email, time ,userRole);
            }
            break;
        case 4:{
            string SearchOption;
            
            cout << "-------------------------------------" << endl;
            cout << "1.Linear Search" << endl;
            cout << "2.Binary Search" << endl;
            cout << "-------------------------------------" << endl;
            cin >> SearchOption;

            if(SearchOption == "1"){
                string institution;
                cout << "Enter the institution name: ";
                cin.ignore();
                getline(cin, institution);

                auto startTime = high_resolution_clock::now();

                UniNode* result = guest.UniSearch(institution);
                auto endTime = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(endTime - startTime);
                if (result != nullptr) {
                    cout << "+---------------------------------------------------+" << endl;
                    cout << "University Found:" << endl;
                    cout << "Rank: " << result->Rank << endl;
                    cout << "Institution: " << result->Institution << endl;
                    cout << "+---------------------------------------------------+" << endl;
                    // Display other attributes if needed
                }else{
                    cout << "Error" << endl;
                }
                cout << "Time taken for searching: " << duration.count() << " microseconds" << endl;
            }else if(SearchOption == "2"){
                string searchInstitution;
                cout << "Enter the institution name to search: ";
                cin.ignore();
                getline(cin, searchInstitution);

                auto startTime = high_resolution_clock::now();

                // Perform the binary search
                UniNode* result = guest.binarySearch(Uniheads, searchInstitution);
                auto endTime = high_resolution_clock::now();
                    auto duration = duration_cast<microseconds>(endTime - startTime);
                if (result != nullptr) {
                    cout << "+-----------------------------------------------------+" << endl;
                    cout << "Institution Found:" << endl;
                    cout << "Rank: " << result->Rank << endl;
                    cout << "Institution: " << result->Institution << endl;
                    cout << "+-----------------------------------------------------+" << endl;
                    // Display other attributes if needed
                }
                else {
                    cout << "Institution Not Found." << endl;
                }
                cout << "Time taken for searching: " << duration.count() << " microseconds" << endl;
            }else{
                cout << "Invalid Input" << endl;
            }
            }
            break;
        case 5:
			{
				string option;

                cout << "--------------------------------------------------" << endl;
				cout << "Select one sort:" << endl;
				cout << "1. Merge" << endl;
				cout << "2. Quick" << endl;
                cout << "--------------------------------------------------" << endl;

				cin >> option;

				auto startTime = high_resolution_clock::now();
				if (option == "1") {
					guest.mergeSort(Uniheads);
					cout << "Sorted Data:" << endl;
    				//guest.display();
				} else if (option == "2") {
					guest.quickSort(Uniheads,Unitails);
                    //guest.display();
				}else{
                    cout << "Invalid Input" << endl;
                }
				auto endTime = high_resolution_clock::now();

				// Calculate and display the time taken for sorting
				auto duration = duration_cast<microseconds>(endTime - startTime);
				cout << "Time taken for sorting: " << duration.count() << " microseconds" << endl;

			}
            break;
        case 6:
			userFunction.SaveUserData();
            exit(0);
            break;
        default:
            cout << "Invalid selection.\n" << endl;
        }
    } while (choice != 6);

    return 0;
}
