#include <iomanip>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <unordered_set>

using namespace std;

bool createDirectory(const std::string & dirname){
    if(!std::filesystem::create_directories(dirname)){
        if(std::filesystem::exists(dirname)){
            return true; //the directory already exists
        }
    
    printf("ERROR: Failure creating directory!\n");
    return false;
    }
    return true;
}
bool containsUpper(string pass, int len){
    unordered_set <char> set;

    for(int i = 0 ;i < len; i++){
        if(isupper(pass[i])){
            set.insert(pass[i]);
        }
    }
    if(set.empty()){
        return false;
    }
    return true;
}

bool containsDigit(string pass,int len){
    unordered_set <int> set;
    for(int i = 0; i < len; i++){
        if(isdigit(pass[i])){
            set.insert(pass[i]);
        }
    }
    if(set.empty()){
        return false;
    }
    return true;

}
bool meetsCriteria(string pass){
    int checkmark = 0;
    int len = pass.length();
    
    if(len < 8 || len > 21){
        return false;
    }

    if(containsUpper(pass, len)){
        checkmark++;
    }
    if(containsDigit(pass,len)){
        checkmark++;
    }

    if(checkmark != 2){
    return false;
    }

    return true;

}
bool userExists(const string& user){
    ifstream infile("~/.userinfo/" + user);
    return infile.good();   
}

void registerUser(){
    ofstream newUser;
    string user;
    string pass;
    cout << "Welcome to Registration!" << endl;
    cout <<"\nPlease create a unique username: ";
    cin >> user;
    if((userExists(user))){
        while((userExists(user))){
            cout << "\033[31m" << "ERROR!! That username already exists, please input a new one" << "\033[0m" << endl;
            cout << "Username: ";
            cin >> user;
            if(!(userExists(user))){
                newUser.open(".userinfo/" + user);
            }
        }
    }
    else{
    newUser.open("~/.userinfo/" + user);
    }
    cout << endl;

    cout << "\nPlease create a unique password that meets the following criteria:"  << endl;
    cout << " 1) Must be longer from 8 - 20 characters\n";
    cout << " 2) Must have atleast one Uppercase character\n";
    cout << " 3) Must have atleast one number\n";
    cout << endl;
    cout << "Password: ";
    cin >> pass;
    while(!meetsCriteria(pass)){
        cout << "\033[31m" << "ERROR!! Your input does not meet any of the criteria try again" << "\033[0m" << endl;
        cout <<"Password: ";
        cin >> pass;
        if(meetsCriteria(pass)){
            break;
        }
    }
    cout << endl;
    newUser << pass << endl;

    newUser.close();

    cout << "\033[32m" << "You have been successfully registered!" << "\033[0m" << endl;
    cout << endl;
}

bool passwordAuthenticator(string user, string pass){
    ifstream userFile;
    string line;
    userFile.open("~/.userinfo/" + user);
    while(getline(userFile,line)){
        if(line != pass){
            return false;
        }
    }
    return true;
}

int main(){
    string user;
    string pass;
    string line;
    string choice;
    int counter = 3;
    string dirname = "~/.userinfo";
    createDirectory(dirname);
    ifstream userFile;
    cout << endl;
    cout << "New User? (y/n):";
    cin >> choice;
    if(choice == "y"){
        registerUser();
    }
    if(choice == "n"){
        cout << endl;
        cout << setw(30);
        cout << "Username: ";
        cin >> user;
        cin.clear();
        cout << setw(30);
        cout << "Password: ";
        cin >> pass;
        cout << endl;
        if(!userExists(user)){
            while(!userExists(user)){
                cout << "\033[31m" << "Error: That username does not exist in our files, please try again." << "\033[0m" << endl;
                cout << setw(30);
                cout << "Username: ";
                cin >> user;
                cout << setw(30);
                cout << "Password: ";
                cin >> pass;
                if(userExists(user)){
                    break;
                }
            }
        }
        while(!(passwordAuthenticator(user,pass))){
            if(counter == 0){
                cout << endl;
                cout << "You have entered an incorrect password multiple times, the system will now log you off.\n";
                cerr << "Goodbye." << endl;
                return 1;
            }
            cout << "\033[31m" << "Error: Password incorrect, please try again. \n";
            cout << "(Attempts left: " << counter << ")"  << "\033[0m" << endl;
            counter--;
            cout << setw(30);
            cout << "Password: ";
            cin >> pass;
            if(passwordAuthenticator(user, pass) && counter > 0){
                break;
            }
        }
    }
    
    cout << "\nWelcome you are now in the System!" << endl;



    
    
    


}