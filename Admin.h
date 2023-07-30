#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm> // For std::transform
#include <cctype>    // For std::tolower
#include <regex>     // For email and phone number validation
#include <chrono>    // For date and time operations
#include <ctime>     // For date and time functions
#include <iomanip>   // For std::put_time
using namespace std;
 
// Struct to hold customer details
struct Customer {
    string userid;
    string username;
    string email;
    string password;
    string lastLoginTime;
    string userRole;
};
 
struct Reply {
    int id;
    string username;
    string content;
    string dateTime;
    Reply* next;
};

struct Feedback {
    int id;
    string username;
    string content;
    string dateTime;
    Reply* reply; // Linked list of reply
};

struct FeedbackNode {
    Feedback data;
    FeedbackNode* next;
};

// Doubly Linked List Node
struct Node {
    Customer customer;
    Node* prev;
    Node* next;
 
    Node(const Customer& c) : customer(c), prev(nullptr), next(nullptr) {}
};
 
// Function to read customer details from a CSV file and create linked list
Node* readCustomersFromCSV(const string& filename) {
    Node* head = nullptr;
    Node* tail = nullptr;
 
    ifstream file(filename);
    string line;
    getline(file,line);
    if (!file) {
        cerr << "Failed to open the file: " << filename << endl;
        return nullptr;
    }

    while (getline(file, line)) {
        istringstream iss(line);
        string userid, username, email, password, lastLoginTime, userRole;
        if (getline(iss, userid, ',') && getline(iss, username, ',') && getline(iss, email, ',') && getline(iss, password, ',') &&
            getline(iss, lastLoginTime, ',') && getline(iss, userRole)) {
            Customer customer = { userid, username, email, password, lastLoginTime, userRole };
            Node* newNode = new Node(customer);
            if (head == nullptr) {
                head = newNode;
                tail = newNode;
            } else {
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            }
        } else {
            cerr << "Error parsing line: " << line << endl;
        }
    }
 
    file.close();
    return head;
}

void writeCustomersToCSV(string filename, Node* head) {
    // Read the existing data from the file
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open the file: " << filename << endl;
        return;
    }
 
    // Read the first line (header line) and store it
    string firstLine;
    getline(file, firstLine);
    file.close();
 
    // Write the customer data to the file, preserving the header line
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Failed to open the file: " << filename << endl;
        return;
    }
 
    // Write the first line back to the file
    outFile << firstLine << '\n';
 
    // Append the new customer data to the file
    Node* currentNode = head;
    while (currentNode != nullptr) {
        const Customer& customer = currentNode->customer;
        outFile << customer.userid << ',' << customer.username << ',' << customer.email << ',' << customer.password << ','
                << customer.lastLoginTime << ',' << customer.userRole << '\n';
        currentNode = currentNode->next;
    }
 
    outFile.close();
}

 
// Function to display customer details
void displayCustomer(const Customer& customer) {
    cout << "User ID: " << customer.userid << endl;
    cout << "Username: " << customer.username << endl;
    cout << "Email: " << customer.email << endl;
    cout << "Password: " << customer.password << endl;
    cout << "Last Login Time: " << customer.lastLoginTime << endl;
    cout << "User Role: " << customer.userRole << endl;
}
 
// Function to perform linear search for a customer by username
Node* linearSearchCustomer(Node* head, const string& username) {
    Node* currentNode = head;
    while (currentNode != nullptr) {
        if (currentNode->customer.username == username) {
            return currentNode; // Found the user
        }
        currentNode = currentNode->next;
    }
    return nullptr; // User not found
}
 
// Function to validate email format
bool validateEmailFormat(const string& email) {
    static const regex pattern(R"(^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}$)");
    return regex_match(email, pattern);
}
 
// Function to modify user details
void modifyUserDetails(Customer& customer) {
    cout << "Enter the new username: ";
    getline(cin, customer.username);
 
    cout << "Enter the new email: ";
    getline(cin, customer.email);
    while (!validateEmailFormat(customer.email)) {
        cout << "Invalid email format. Please enter a valid email: ";
        getline(cin, customer.email);
    }
 
    cout << "Enter the new password: ";
    getline(cin, customer.password);
 
    cout << "Enter the new user role: ";
    getline(cin, customer.userRole);
}
 
// Function to delete customer
void deleteCustomer(Node*& head, Node* targetNode) {
    if (targetNode == nullptr) {
        return;
    }
 
    if (targetNode == head) {
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        }
    } else {
        Node* prevNode = targetNode->prev;
        prevNode->next = targetNode->next;
        if (prevNode->next != nullptr) {
            prevNode->next->prev = prevNode;
        }
    }
 
    delete targetNode;
}
 
// Function to check if a date is 3 months older than the current date
bool isDateOlderThanThreeMonths(const string& date, const string& format) {
    tm currentDateTm = {};
    istringstream iss(date);
    iss >> get_time(&currentDateTm, format.c_str());
    if (iss.fail()) {
        cout << "Invalid date format: " << format << endl;
        return false;
    }
 
    time_t currentDate = mktime(&currentDateTm);
 
    // Get the current date/time
    time_t now = time(nullptr);
    tm* nowTm = localtime(&now);
 
    // Calculate the date three months ago
    tm threeMonthsAgoTm = *nowTm;
    threeMonthsAgoTm.tm_mon -= 3;
    if (threeMonthsAgoTm.tm_mon < 0) {
        threeMonthsAgoTm.tm_year--;
        threeMonthsAgoTm.tm_mon += 12;
    }
 
    time_t threeMonthsAgo = mktime(&threeMonthsAgoTm);
 
    return (currentDate < threeMonthsAgo);
}
 
// Function to display user details
void displayUserDelete(Node* head) {
    string opt = "Y";
    string dlt_opt;
 
    while (opt == "Y" || opt == "y") {
        cout << "Enter the username: ";
        string username;
        cin.ignore(); // Ignore the newline character in the input buffer
        getline(cin, username);
        Node* targetNode = linearSearchCustomer(head, username);
 
        if (targetNode != nullptr) {
            cout << "Displaying registered User details:" << endl;
            cout << "-----------------------------------" << endl;
            displayCustomer(targetNode->customer);
            cout << "-----------------------------------" << endl;
 
            if (isDateOlderThanThreeMonths(targetNode->customer.lastLoginTime, "%Y-%m-%d %H:%M:%S")) {
                cout << "The customer's last login time is 3 months before the current date." << endl;
                cout << "Since he/she has been inactive for more than 3 months, do you want to delete the customer: (Y/N)" << endl;
                cin >> dlt_opt;
                if (dlt_opt == "y" || dlt_opt == "Y") {
                    cout << "Deleting customer details..." << endl;
                    deleteCustomer(head, targetNode);
                    cout << "Customer details deleted successfully." << endl;
                } else {
                    cout << "Do you want to search for another user? (Y/N): ";
                    cin >> opt;
                }
 
            } else {
                cout << "The customer's last login time is within the past 3 months." << endl;
                cout << "Customer details will not be deleted." << endl;
            }
        } else {
            cout << "User not found." << endl;
        }
    }
}
 
string toLowerCase(const string& str) {
    string result;
    for (char c : str) {
        result += tolower(c);
    }
    return result;
}
 
// Function to display user details
void displayUser(Node* head) {
    string opt = "Y";
 
    while (opt == "Y" || opt == "y") {
        cout << "Enter the username: ";
        string username;
        cin.ignore(); // Ignore the newline character in the input buffer
        getline(cin, username);
        Node* targetNode = linearSearchCustomer(head, username);
        if (targetNode != nullptr && toLowerCase(targetNode->customer.username) == toLowerCase(username)) {
            cout << "Displaying registered User details:" << endl;
            cout << endl;
            cout << "-----------------------------------" << endl;
            displayCustomer(targetNode->customer);
            cout << "-----------------------------------" << endl;
 
            cout << "Do you want to modify user details? (Y/N)" << endl;
            cin >> opt;
            cin.ignore(); // Ignore the newline character in the input buffer
 
            if (opt == "Y" || opt == "y") {
                modifyUserDetails(targetNode->customer);
            }
        } else {
            cout << "User not found." << endl;
        }
 
        cout << endl;
        cout << "Do you want to search another user? (Y/N)" << endl;
        cin >> opt;
    }
}

void addReply(Feedback& feedbackData, const string& username, const string& content, const string& dateTime) {
    // Create a new reply
    Reply* newReply = new Reply;
    newReply->username = username;
    newReply->content = content;
    newReply->dateTime = dateTime;
    newReply->next = nullptr;

    // If there are no existing reply, make the new reply the first reply
    if (feedbackData.reply == nullptr) {
        feedbackData.reply = newReply;
    } else {
        // Find the last reply and append the new reply
        Reply* currentReply = feedbackData.reply;
        while (currentReply->next != nullptr) {
            currentReply = currentReply->next;
        }
        currentReply->next = newReply;
    }
}

void clearReplies(Reply* reply) {
    Reply* currentReply = reply;
    while (currentReply != nullptr) {
        Reply* nextReply = currentReply->next;
        delete currentReply;
        currentReply = nextReply;
    }
}

 
// Function to read feedback data from a CSV file
void readFeedbackFromCSV(const string& filename, Feedback& feedbackData, int feedbackIndex) {
    int switch_choice;    
    string reply_opt;
    int currentFeedbackIndex = 0; // Current index of the displayed feedback
    bool displayFeedback = false; // Variable to control displaying feedback or main menu

    ifstream file(filename);
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    int index = 0;
    while (getline(file, line)) {
        if (index == feedbackIndex) {
            istringstream iss(line);
            string token;

            // Read the comma-separated values
            getline(iss, token, ',');
            feedbackData.id = stoi(token);

            getline(iss, token, ',');
            feedbackData.username = token;

            getline(iss, token, ',');
            feedbackData.content = token;

            getline(iss, token, ',');
            string replyContent = token;

            getline(iss, token, ',');
            feedbackData.dateTime = token;

            // Display the feedback
            cout << endl;
            cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
            cout << "| Username            | Content                                                                         | Reply                                 | Date & Time      |" << endl;
            cout << endl;
            cout << "|" << setw(21) << left << feedbackData.username << "| " << setw(80) << left << feedbackData.content << "| " << setw(38) << left << replyContent << "| " << feedbackData.dateTime << " |" << endl;
            cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
            cout << endl;

            // Check if there is a reply and prompt user to enter one if it is empty
            if (replyContent.empty()) {
                cout << "Do you want to provide a reply? (Y/N)" << endl;
                cin >> reply_opt;

                if (reply_opt == "y" || reply_opt == "Y") {
                    string reply;
                    cout << "Enter your reply: ";
                    cin >> reply;
                    getline(cin, reply);

                    // Get current date and time
                    time_t now = time(0);
                    tm* localTime = localtime(&now);
                    stringstream ss;
                    ss << put_time(localTime, "%Y-%m-%d %H:%M:%S");
                    string dateTime = ss.str();

                    // Update the reply in the feedbackData object
                    feedbackData.reply = new Reply;
                    feedbackData.reply->username = "admin";
                    feedbackData.reply->content = reply;
                    feedbackData.reply->dateTime = dateTime;
                    feedbackData.reply->next = nullptr;

                    // Update the reply in the feedback.csv file
                    ifstream inFile(filename);
                    if (!inFile) {
                        cerr << "Error opening file: " << filename << endl;
                        return;
                    }

                    string tempFile = "feedback_reply.csv"; // Temporary file to store updated content
                    ofstream outFile(tempFile);
                    if (!outFile) {
                        cerr << "Error opening file: " << tempFile << endl;
                        return;
                    }

                    string line;
                    int lineIndex = 0;
                    while (getline(inFile, line)) {
                        if (lineIndex == feedbackIndex) {
                            // Modify the line with the updated reply
                            size_t lastCommaPos = line.find_last_of(",");
                            if (lastCommaPos != string::npos) {
                                line = line.substr(0, lastCommaPos + 1) + reply + "," + dateTime;
                            }
                        }
                        outFile << line << endl;
                        lineIndex++;
                    }

                    inFile.close();
                    outFile.close();

                    // Replace the original file with the updated content
                    if (remove(filename.c_str()) != 0) {
                        cerr << "Error deleting file: " << filename << endl;
                        return;
                    }
                    if (rename(tempFile.c_str(), filename.c_str()) != 0) {
                        cerr << "Error renaming file: " << tempFile << " to " << filename << endl;
                        return;
                    }
                } else {
                    cout << "Choose an option:" << endl;
                    cout << "1. Go to previous feedback" << endl;
                    cout << "2. Go to next feedback" << endl;
                    cout << "0. Back to main menu" << endl;
                    cout << "Enter your choice: ";
                    cin >> switch_choice;
        
                    switch (switch_choice) {
                        case 1:
                            // Move to the previous feedback
                            if (currentFeedbackIndex > 0) {
                                currentFeedbackIndex--;
                            }
                            readFeedbackFromCSV(filename, feedbackData, currentFeedbackIndex);
                            break;
                        case 2:
                            // Move to the next feedback
                            currentFeedbackIndex++;
                            readFeedbackFromCSV(filename, feedbackData, currentFeedbackIndex);
                            break;
                        case 0:
                            displayFeedback = false;
                            break;
                        default:
                            cout << "Invalid selection.\n" << endl;
                    }
                }
                break;

            } else {

                cout << "Choose an option:" << endl;
                cout << "1. Go to previous feedback" << endl;
                cout << "2. Go to next feedback" << endl;
                cout << "0. Back to main menu" << endl;
                cout << "Enter your choice: ";
                cin >> switch_choice;
    
                switch (switch_choice) {
                    case 1:
                        // Move to the previous feedback
                        if (currentFeedbackIndex > 0) {
                            currentFeedbackIndex--;
                        }
                        readFeedbackFromCSV(filename, feedbackData, currentFeedbackIndex);
                        break;
                    case 2:
                        // Move to the next feedback
                        currentFeedbackIndex++;
                        readFeedbackFromCSV(filename, feedbackData, currentFeedbackIndex);
                        break;
                    case 0:
                        displayFeedback = false;
                        break;
                    default:
                        cout << "Invalid selection.\n" << endl;
                }
            }
            break;
        }
        index++;
    }
}
 
void AdminInterface(string username) {
    string user = username;
    int choice;
    int switch_choice;    
    bool continueExecution = true; // Flag variable to control program execution
 
    // Read customer details from CSV file and create linked list
    Node* head = nullptr; // Define and initialize the head of the linked list
 
    // Read customer details from CSV file and create linked list
    head = readCustomersFromCSV("user.csv");
 
    // Read feedback data from CSV file
    const string filename = "feedback.csv";
    Feedback feedbackData;

    feedbackData.reply = nullptr;

    int currentFeedbackIndex = 0; // Current index of the displayed feedback
 
    bool displayFeedback = false; // Variable to control displaying feedback or main menu
 
    do {
        cout << endl;
        cout << "Welcome: " << user << endl;
        cout << "*** Administrative Functionalities ***" << endl;
        cout << "To perform an action, enter " << endl;
        cout << "1 Display registered User details" << endl;
        cout << "2 Delete User Account" << endl;
        cout << "3 View Feedback" << endl;
        cout << "4 Summarize Top 10 Universities" << endl;
        cout << "5 Exit System" << endl;
        cout << endl;
        cout << "Please Enter Your Option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayUser(head);
                break;
            case 2:
                displayUserDelete(head);
                break;
            case 3:
                displayFeedback = true;
                readFeedbackFromCSV(filename, feedbackData, currentFeedbackIndex);
                break;

            case 4:
                cout << "Function 6 has been selected" << endl;
                // summarizeUni();
                break;
            case 5:
                cout << "Exiting the program..." << endl;
                writeCustomersToCSV("user.csv", head);
                continueExecution = false; // Set flag to exit program

                exit(0);
                break;
            
            default:
                cout << "Invalid selection.\n" << endl;
            }
        } while (choice != 5);
 
    // Write updated customer details back to CSV file
    writeCustomersToCSV("user.csv", head);
}