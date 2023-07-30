#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <ctime>

using namespace std;
using namespace std::chrono;

// Structure to represent a user
struct User {
    string id;
    string username;
    string password;
    bool isLoggedIn;
    User* next;
};

// Structure to represent a university
struct University {
    string rank;
    string institution;
    string locationCode;
    string location;
    double arScore;
    string arRank;
    double fsrScore;
    string fsrRank;
    double ifrScore;
    string ifrRank;
};

struct Feedbacks {
    string universityName;
    string feedbackMessage;
    string dateTime;
};

struct Universitys {
    std::string Rank;
    std::string Institution;
    std::string LocationCode;
    std::string Location;
    std::string ArScore;
    std::string ArRank;
    std::string ErScore;
    std::string ErRank;
    std::string FsrScore;
    std::string FsrRank;
    std::string CpfScore;
    std::string CpfRank;
    std::string IfrScore;
    std::string IfrRank;
    std::string IsrScore;
    std::string IsrRank;
    std::string IrnScore;
    std::string IrnRank;
    std::string GerScore;
    std::string GerRank;
    std::string ScoreScaled;
};

// Structure to represent a university
struct UniversityNode {
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
    UniversityNode* prev;
    UniversityNode* next;
}* UniHead, * UniTail;

class UserManage {
public:
    void SearchPage();
    void Filter();
};



const int MAX_TOKENS = 3; // Maximum number of tokens in a line

void split(const std::string& line, char delimiter, std::string tokens[], int& tokenCount, int maxTokens) {
    std::string token;
    std::istringstream tokenStream(line);

    tokenCount = 0; // Initialize token count

    while (std::getline(tokenStream, token, delimiter)) {
        if (tokenCount >= maxTokens) {
            break; // Maximum number of tokens reached
        }

        tokens[tokenCount] = token;
        tokenCount++;
    }
}

class Guests {
private:
    struct Favo {
        string Institution;
        int click;
    };

    Favo* favorites; // Dynamic to store favorite universities
    int numFavorites; // Number of favorite universities

public:
    Guests() {
        favorites = nullptr;
        numFavorites = 0;
    }

    UniversityNode* UnicreateNewNode(string Rank, string Institution, string LocationCode,
        string Location, string ArScore, string ArRank, string ErScore,
        string ErRank, string FsrScore, string FsrRank, string CpfScore,
        string CpfRank, string IfrScore, string IfrRank, string IsrScore,
        string IsrRank, string IrnScore, string IrnRank, string GerScore,
        string GerRank, string ScoreScaled)
    {
        UniversityNode* UninewNode = new UniversityNode;
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

    void UniInsert(string Rank, string Institution, string LocationCode,
        string Location, string ArScore, string ArRank, string ErScore,
        string ErRank, string FsrScore, string FsrRank, string CpfScore,
        string CpfRank, string IfrScore, string IfrRank, string IsrScore,
        string IsrRank, string IrnScore, string IrnRank, string GerScore,
        string GerRank, string ScoreScaled)
    {
        UniversityNode* UninewNode = UnicreateNewNode(Rank, Institution, LocationCode, Location, ArScore, ArRank, ErScore,
            ErRank, FsrScore, FsrRank, CpfScore, CpfRank, IfrScore, IfrRank, IsrScore, IsrRank, IrnScore,
            IrnRank, GerScore, GerRank, ScoreScaled);
        if (UniHead == nullptr) {
            UniHead = UniTail = UninewNode;
        }
        else {
            UniTail->next = UninewNode;
            UninewNode->prev = UniTail;
            UniTail = UninewNode;
        }
    }

    void DisplayUniversities() {
        UniversityNode* current = UniHead;
        while (current != nullptr) {
            cout << "Rank: " << current->Rank << endl;
            cout << "Institution: " << current->Institution << endl;
            cout << endl;
            current = current->next;
        }
        cout << "End and Success" << endl;
    }

    UniversityNode* UniHead = nullptr;
    UniversityNode* UniTail = nullptr;

    void SaveFavorite(const string& institutionName) {
        bool exists = false;
        for (int i = 0; i < numFavorites; i++) {
            if (favorites[i].Institution == institutionName) {
                favorites[i].click++;
                exists = true;
                break;
            }
        }

        if (!exists) {
            Favo* newFavorites = new Favo[numFavorites + 1];
            for (int i = 0; i < numFavorites; i++) {
                newFavorites[i] = favorites[i];
            }
            newFavorites[numFavorites].Institution = institutionName;
            newFavorites[numFavorites].click = 1;

            delete[] favorites;
            favorites = newFavorites;
            numFavorites++;
        }
    }

    void SaveFavoritesToFile() {
        ofstream file("favo.csv");
        if (!file.is_open()) {
            cout << "Failed to open the file." << endl;
            return;
        }
        file << "Institution,Click" << endl;
        for (int i = 0; i < numFavorites; i++) {
            file << favorites[i].Institution << "," << favorites[i].click << endl;
        }
        file.close();
        cout << "Favorites saved successfully to favo.csv." << endl;
    }

    ~Guests() {
        delete[] favorites;
    }
};

void ReadUniData() {
    Guests Guests;
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
        Guests.UniInsert(Rank, Institution, LocationCode, Location, ArScore, ArRank, ErScore, ErRank, FsrScore, FsrRank,
            CpfScore, CpfRank, IfrScore, IfrRank, IsrScore, IsrRank, IrnScore, IrnRank, GerScore, GerRank, ScoreScaled);
    }
    file.close();
}

string getCurrentDateTime() {
    time_t now = time(0);
    tm* timeInfo = localtime(&now);
    stringstream ss;
    ss << (timeInfo->tm_year + 1900) << "-"
       << setw(2) << setfill('0') << (timeInfo->tm_mon + 1) << "-"
       << setw(2) << setfill('0') << timeInfo->tm_mday << " "
       << setw(2) << setfill('0') << timeInfo->tm_hour << ":"
       << setw(2) << setfill('0') << timeInfo->tm_min << ":"
       << setw(2) << setfill('0') << timeInfo->tm_sec;
    return ss.str();
}

void Favourite(){
    Guests Guests;
    string option;

    ReadUniData();

    Guests.DisplayUniversities();

    while (true) {
        cout << "Enter name to save as favorite (or 'ex' to exit): ";
        getline(cin, option);
        if (option == "ex") {
            break;
        }
        Guests.SaveFavorite(option);
    }

    Guests.SaveFavoritesToFile();

}

void SendFeedback(const string& universityName, const string& feedbackMessage) {
    ofstream file("feedbacks.csv", ios::app);
    if (!file) {
        cout << "Error opening file." << endl;
        return;
    }

    file << universityName << "," << feedbackMessage << "," << getCurrentDateTime() << endl;
    file.close();

    cout << "Feedback sent successfully!" << endl;
}

void ReadFeedbackReply() {
    const int MAX_FEEDBACKS = 100; // Maximum number of feedbacks

    Feedbacks feedbacks[MAX_FEEDBACKS];
    int feedbackCount = 0;

    std::ifstream file("feedbacks.csv");
    if (!file) {
        std::cout << "Error opening file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::string tokens[MAX_TOKENS];
        int tokenCount = 0;

        split(line, ',', tokens, tokenCount, MAX_TOKENS);

        if (tokenCount != MAX_TOKENS) {
            continue;
        }

        if (feedbackCount >= MAX_FEEDBACKS) {
            std::cout << "Maximum number of feedbacks reached. Ignoring remaining data." << std::endl;
            break;
        }

        Feedbacks feedback;
        feedback.universityName = tokens[0];
        feedback.feedbackMessage = tokens[1];
        feedback.dateTime = tokens[2];

        feedbacks[feedbackCount] = feedback;
        feedbackCount++;
    }

    file.close();

    if (feedbackCount == 0) {
        std::cout << "No feedbacks found." << std::endl;
        return;
    }

    // Sort feedbacks by date/time in descending order
    std::sort(feedbacks, feedbacks + feedbackCount, [](const Feedbacks& f1, const Feedbacks& f2) {
        return f1.dateTime > f2.dateTime;
    });

    std::cout << "Latest Feedback Reply:" << std::endl;
    std::cout << "University Name: " << feedbacks[0].universityName << std::endl;
    std::cout << "Feedback Message: " << feedbacks[0].feedbackMessage << std::endl;
    std::cout << "Date/Time: " << feedbacks[0].dateTime << std::endl;
}


// Class to manage user registration, login, and data storage
class UserManager {
private:
    User* userList;
    User* currentUser;

public:
    UserManager() : userList(nullptr), currentUser(nullptr) {
        // Read user data from CSV file
        std::ifstream file("data.csv");
        if (!file.is_open()) {
            std::cout << "Failed to open data file." << std::endl;
            return;
        }
        std::string line;
        while (getline(file, line)) {
            std::stringstream ss(line);
            std::string id, username, password, isLoggedInStr;
            getline(ss, id, ',');
            getline(ss, username, ',');
            getline(ss, password, ',');
            getline(ss, isLoggedInStr, ',');
            bool isLoggedIn = (isLoggedInStr == "1");
            registerUser( username, password, isLoggedIn);
        }
        file.close();
    }

    // Register a new user
    void registerUser(const std::string& username, const std::string& password, bool isLoggedIn = false) {
        User* newUser = new User;
        newUser->id = generateID();
        newUser->username = username;
        newUser->password = password;
        newUser->isLoggedIn = isLoggedIn;
        newUser->next = nullptr;
        if (userList == nullptr) {
            userList = newUser;
        } else {
            User* temp = userList;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newUser;
        }
    }

    // Log in a user
    void login(const std::string& username, const std::string& password) {
        User* temp = userList;
        while (temp != nullptr) {
            if (temp->username == username && temp->password == password) {
                if (temp->isLoggedIn) {
                    std::cout << "User is already logged in." << std::endl;
                    return;
                }
                temp->isLoggedIn = true;
                currentUser = temp;
                std::cout << "User logged in successfully!" << std::endl;
                CustomerPage(); // Navigate to the Customer Page
                return;
            }
            temp = temp->next;
        }
        std::cout << "Invalid username or password. Login failed." << std::endl;
    }

    // Store user data to a CSV file and exit the program
    void storeUserDataAndExit() {
        std::ofstream file("data.csv");
        if (!file.is_open()) {
            std::cout << "Failed to open data file." << std::endl;
            return;
        }
        User* temp = userList;
        while (temp != nullptr) {
            file << temp->id << "," << temp->username << "," << temp->password << "," << (temp->isLoggedIn ? "1" : "0") << "\n";
            temp = temp->next;
        }
        file.close();
        std::cout << "User data stored successfully!" << std::endl;
        exit(0);
    }

    // Free the memory allocated for the linked list
    ~UserManager() {
        User* temp;
        while (userList != nullptr) {
            temp = userList;
            userList = userList->next;
            delete temp;
        }
    }

    // Check if a user is logged in
    bool isLoggedIn() {
        return currentUser != nullptr && currentUser->isLoggedIn;
    }

    // Get the username of the currently logged-in user
    std::string getCurrentUsername() {
        return isLoggedIn() ? currentUser->username : "";
    }

    // Generate a unique ID for each user
    std::string generateID() {
        auto timestamp = std::chrono::system_clock::now();
        auto time = std::chrono::duration_cast<std::chrono::milliseconds>(timestamp.time_since_epoch()).count();
        static int counter = 0;
        return "ID_" + std::to_string(time) + "_" + std::to_string(counter++);
    }

    // Function to perform a linear search on the UniRank CSV file
void linearSearchCSV(const string& filePath, const string& rank) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cout << "Failed to open the file." << endl;
        return;
    }

    string line;
    getline(file, line); // Skip the header line

    while (getline(file, line)) {
        stringstream ss(line);
        string r, inst, locCode, loc, arScore, arRank, erScore, erRank, fsrScore, fsrRank,
            cpfScore, cpfRank, ifrScore, ifrRank, isrScore, isrRank, irnScore, irnRank, gerScore, gerRank, scoreScaled;
        
        getline(ss, r, ',');
        getline(ss, inst, ',');
        getline(ss, locCode, ',');
        getline(ss, loc, ',');
        getline(ss, arScore, ',');
        getline(ss, arRank, ',');
        getline(ss, erScore, ',');
        getline(ss, erRank, ',');
        getline(ss, fsrScore, ',');
        getline(ss, fsrRank, ',');
        getline(ss, cpfScore, ',');
        getline(ss, cpfRank, ',');
        getline(ss, ifrScore, ',');
        getline(ss, ifrRank, ',');
        getline(ss, isrScore, ',');
        getline(ss, isrRank, ',');
        getline(ss, irnScore, ',');
        getline(ss, irnRank, ',');
        getline(ss, gerScore, ',');
        getline(ss, gerRank, ',');
        getline(ss, scoreScaled, ',');

        if (r == rank) {
            cout << "Rank: " << r << endl;
            cout << "Institution: " << inst << endl;
            cout << "Location Code: " << locCode << endl;
            cout << "Location: " << loc << endl;
            cout << "Academic Reputation Score: " << arScore << endl;
            cout << "Academic Reputation Rank: " << arRank << endl;
            cout << "Employer Reputation Score: " << erScore << endl;
            cout << "Employer Reputation Rank: " << erRank << endl;
            cout << "Faculty/Student Ratio Score: " << fsrScore << endl;
            cout << "Faculty/Student Ratio Rank: " << fsrRank << endl;
            cout << "Citations Per Faculty Score: " << cpfScore << endl;
            cout << "Citations Per Faculty Rank: " << cpfRank << endl;
            cout << "International Faculty Ratio Score: " << ifrScore << endl;
            cout << "International Faculty Ratio Rank: " << ifrRank << endl;
            cout << "International Student Ratio Score: " << isrScore << endl;
            cout << "International Student Ratio Rank: " << isrRank << endl;
            cout << "International Research Network Score: " << irnScore << endl;
            cout << "International Research Network Rank: " << irnRank << endl;
            cout << "Employment Outcome Score: " << gerScore << endl;
            cout << "Employment Outcome Rank: " << gerRank << endl;
            cout << "Score Scaled: " << scoreScaled << endl;
            return; // Found the rank, exit the function
        }
    }

    cout << "Rank not found." << endl;
    file.close();
}

    void SearchPage() {
    string filterChoice;
    cout << "________________________________________________________________________________" << endl;
    cout << "Filter by:" << endl;
    cout << "1. Ranking" << endl;
    cout << "2. Location Code" << endl;
    cout << "Enter your filter choice: ";
    cin >> filterChoice;

    ifstream file("UniRank.csv");
    if (!file.is_open()) {
        cout << "Failed to open university data file." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string rank, institution, locationCode, location, arRank, fsrRank, ifrRank;
        double arScore, fsrScore, ifrScore;
        getline(ss, rank, ',');
        getline(ss, institution, ',');
        getline(ss, locationCode, ',');
        getline(ss, location, ',');
        ss >> arScore;
        getline(ss, arRank, ',');
        ss >> fsrScore;
        getline(ss, fsrRank, ',');
        ss >> ifrScore;
        getline(ss, ifrRank, ',');

    if (filterChoice == "2") {
    string searchLocationCode;
    cout << "Enter the location code: ";
    cin >> searchLocationCode;
    cin.ignore(); // Ignore the remaining newline character

    bool found = false; // Flag to track if any match is found

    while (getline(file, line)) {
        stringstream ss(line);
        string rank, institution, locationCode, location, arRank, fsrRank, ifrRank;
        double arScore, fsrScore, ifrScore;
        getline(ss, rank, ',');
        getline(ss, institution, ',');
        getline(ss, locationCode, ',');
        getline(ss, location, ',');
        ss >> arScore;
        getline(ss, arRank, ',');
        ss >> fsrScore;
        getline(ss, fsrRank, ',');
        ss >> ifrScore;
        getline(ss, ifrRank, ',');

        if (locationCode == searchLocationCode) {
            found = true;
            cout << "University found!" << endl;
            cout << "Rank: " << rank << endl;
            cout << "Institution: " << institution << endl;
            cout << "Location Code: " << locationCode << endl;
            cout << "Location: " << location << endl;
            cout << "AR Score: " << arScore << endl;
            cout << "AR Rank: " << arRank << endl;
            cout << "FSR Score: " << fsrScore << endl;
            cout << "FSR Rank: " << fsrRank << endl;
            cout << "IFR Score: " << ifrScore << endl;
            cout << "IFR Rank: " << ifrRank << endl;
            cout << endl;
        }
    }

    if (found) {
        CustomerPage();
        return;
    }
}

    }

    file.close();

    if (filterChoice == "1") {
        string filePath = "UniRank.csv";
        string rank;

        cout << "Enter the rank to search: ";
        cin >> rank;

        linearSearchCSV(filePath, rank);
        CustomerPage();
    } else {
        cout << "No universities found for the given criteria." << endl;
        CustomerPage();
    }
}

    
    
    // Customer Page
    void CustomerPage() {

        string universityName, feedbackMessage;
        cout << "________________________________________________________________________________" << endl;
        cout << "Welcome to the Customer Page, " << getCurrentUsername() << "!" << endl;

        int choice;
        do {
            cout << "1. Sort university information based on ArScore" << endl;
            cout << "2. Sort university information based on FsrScore" << endl;
            cout << "3. Sort university information based on IfrScore" << endl;
            cout << "4. Send Feedback" << endl;
            cout << "5. View Latest Feedback Reply" << endl;
            cout << "6. Search By Filter" << endl;
            cout << "7. Favorite an University" << endl;
            cout << "8. Logout and Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    sortUniversities("ArScore");
                    break;
                case 2:
                    sortUniversities("FsrScore");
                    break;
                case 3:
                    sortUniversities("IfrScore");
                    break;
                case 4:  
                    cout << "Enter the university name: ";
                    cin.ignore();
                    getline(cin, universityName);
                    cout << "Enter your feedback message: ";
                    getline(cin, feedbackMessage);
                    SendFeedback(universityName, feedbackMessage);
                    break;
                case 5:
                    ReadFeedbackReply();
                    break;
                case 6:
                    SearchPage();
                case 7:
                    Favourite();
                case 8:
                    logout();
                    storeUserDataAndExit();
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        } while (true);
    }



    // Logout the user and exit the program
    void logout() {
        if (isLoggedIn()) {
            currentUser->isLoggedIn = false;
            currentUser = nullptr;
            cout << "User logged out successfully!" << endl;
        }
        storeUserDataAndExit();
    }

    // Sort universities based on the specified score field
    struct UniversityNode {
    University data;
    UniversityNode* next;

    UniversityNode(const University& university) : data(university), next(nullptr) {}
};

UniversityNode* merge(UniversityNode* head1, UniversityNode* head2, const string& scoreField) {
    if (head1 == nullptr)
        return head2;
    if (head2 == nullptr)
        return head1;

    if (scoreField == "ArScore") {
        if (head1->data.arScore >= head2->data.arScore) {
            head1->next = merge(head1->next, head2, scoreField);
            return head1;
        } else {
            head2->next = merge(head1, head2->next, scoreField);
            return head2;
        }
    } else if (scoreField == "FsrScore") {
        if (head1->data.fsrScore >= head2->data.fsrScore) {
            head1->next = merge(head1->next, head2, scoreField);
            return head1;
        } else {
            head2->next = merge(head1, head2->next, scoreField);
            return head2;
        }
    } else if (scoreField == "IfrScore") {
        if (head1->data.ifrScore >= head2->data.ifrScore) {
            head1->next = merge(head1->next, head2, scoreField);
            return head1;
        } else {
            head2->next = merge(head1, head2->next, scoreField);
            return head2;
        }
    } else {
        return nullptr;  // Invalid score field
    }
}

UniversityNode* mergeSort(UniversityNode* head, const string& scoreField) {
    if (head == nullptr || head->next == nullptr)
        return head;

    UniversityNode* slow = head;
    UniversityNode* fast = head->next;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    UniversityNode* secondHalf = slow->next;
    slow->next = nullptr;

    UniversityNode* sortedFirstHalf = mergeSort(head, scoreField);
    UniversityNode* sortedSecondHalf = mergeSort(secondHalf, scoreField);

    return merge(sortedFirstHalf, sortedSecondHalf, scoreField);
}

//sort university score base on merge sort algorithm
void sortUniversities(const string& scoreField) {
    ifstream file("UniRank.csv");
    if (!file.is_open()) {
        cout << "Failed to open university data file." << endl;
        return;
    }

    string line;
    UniversityNode* head = nullptr;
    UniversityNode* tail = nullptr;
    const int MAX_UNIVERSITIES = 100; // Maximum number of universities
    int universityCount = 0;

    while (getline(file, line)) {
        stringstream ss(line);
        string rank, institution, locationCode, location, arRank, fsrRank, ifrRank;
        double arScore, fsrScore, ifrScore;
        getline(ss, rank, ',');
        getline(ss, institution, ',');
        getline(ss, locationCode, ',');
        getline(ss, location, ',');
        ss >> arScore;
        getline(ss, arRank, ',');
        ss >> fsrScore;
        getline(ss, fsrRank, ',');
        ss >> ifrScore;
        getline(ss, ifrRank, ',');

        University university;
        university.rank = rank;
        university.institution = institution;
        university.locationCode = locationCode;
        university.location = location;
        university.arScore = arScore;
        university.arRank = arRank;
        university.fsrScore = fsrScore;
        university.fsrRank = fsrRank;
        university.ifrScore = ifrScore;
        university.ifrRank = ifrRank;

        UniversityNode* newNode = new UniversityNode(university);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }

        universityCount++;

        if (universityCount >= MAX_UNIVERSITIES) {
            cout << "Maximum number of universities reached. Ignoring remaining data." << endl;
            break;
        }
    }

    file.close();

    UniversityNode* sortedHead = mergeSort(head, scoreField);

    while (sortedHead != nullptr) {
        const University& university = sortedHead->data;
        cout << "Rank: " << university.rank << endl;
        cout << "Institution: " << university.institution << endl;
        cout << "Location Code: " << university.locationCode << endl;
        cout << "Location: " << university.location << endl;
        cout << "ArScore: " << university.arScore << endl;
        cout << "ArRank: " << university.arRank << endl;
        cout << "FsrScore: " << university.fsrScore << endl;
        cout << "FsrRank: " << university.fsrRank << endl;
        cout << "IfrScore: " << university.ifrScore << endl;
        cout << "IfrRank: " << university.ifrRank << endl;
        cout << "--------------------------" << endl;

        UniversityNode* current = sortedHead;
        sortedHead = sortedHead->next;
        delete current;
    }
}


};

void UserMain() {
    UserManager userManager;
    string username, password;
    cout << "________________________________________________________________________________" << endl;
    cout << "Welcome to the University Ranking System!" << endl;
    cout << "Please log in or register." << endl;

    while (true) {
        cout << "1. Register" << endl;
        cout << "2. Log in" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter a username: ";
                cin >> username;
                cout << "Enter a password: ";
                cin >> password;
                userManager.registerUser(username, password);
                break;
            case 2:
                cout << "Enter your username: ";
                cin >> username;
                cout << "Enter your password: ";
                cin >> password;
                userManager.login(username, password);
                break;
            case 3:
                userManager.storeUserDataAndExit();
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}
