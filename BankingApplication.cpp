#include <iostream>
#include <stdlib.h>
#include <ctime> //To get current time and date
#include <vector>
using namespace std;
class BankException;
class BankingApplication;
class Bank;
class BankAccount;
class SavingsAccount;
class CurrentAccount;
class User;
class Insurance;
class Loan;
// Class for user defined exception.
class LowBalanceException
{
private:
    string msg;

public:
    // Parameterized constructor used to assign the message when exception is thrown.
    LowBalanceException(string msg)
    {
        this->msg = msg;
    }
    // Method that returns the error message.
    string what()
    {
        return msg;
    }
};
class InvalidUserException
{
private:
    string msg;

public:
    // Parameterized constructor used to assign the message when exception is thrown.
    InvalidUserException(string msg)
    {
        this->msg = msg;
    }
    // Method that returns the error message.
    string what()
    {
        return msg;
    }
};
class WrongPasswordException
{
private:
    string msg;

public:
    // Parameterized constructor used to assign the message when exception is thrown.
    WrongPasswordException(string msg)
    {
        this->msg = msg;
    }
    // Method that returns the error message.
    string what()
    {
        return msg;
    }
};
class User
{
private:
    bool hasLoan, hasInsurance;
    string name, address, username, password;
    double income;
    int age, userId;
    long long adhaar;

public:
    static int userIdIntial;
    friend class BankingApplication;
    User(string name, string address, string username, string password, double income, int age, long long adhaar)
    {
        this->userId = userIdIntial++;
        this->hasLoan = false;
        this->hasInsurance = false;
        this->name = name;
        this->address = address;
        this->username = username;
        this->password = password;
        this->income = income;
        this->age = age;
        this->adhaar = adhaar;
    }
    void printUser()
    {
        cout << "-------------------------------------------------" << endl;
        cout << "User details with " << username << " username -" << endl;
        cout << "User Id: " << userId << endl;
        cout << "Name: " << name << endl;
        cout << "Address: " << address << endl;
        cout << "Username: " << username << endl;
        cout << "Password: " << password << endl;
        cout << "Income: " << income << endl;
        cout << "Age: " << age << endl;
        cout << "Adhaar: " << adhaar << endl;
        cout << "Has Loan: " << hasLoan << endl;
        cout << "Has Insurance: " << hasInsurance << endl;
    }
};
class BankAccount
{
protected:
    int userId;
    int accNo;
    string name;
    double balance;
    string statement, accType;

public:
    static int accNoIntial;
    friend class BankingApplication;
    BankAccount(int userId, string name, double balance)
    {
        this->userId = userId;
        this->name = name;
        this->balance = balance;
        statement = "";
    }
    virtual void creditAmount(double amount) = 0;
    virtual void debitAmount(double amount) = 0;
    virtual void printAccount() = 0;
    // Composite Design Pattern.
    static void printAllBankAccounts(vector<BankAccount *> *bankAccounts)
    {
        for (int i = 0; i < bankAccounts->size(); i++)
        {
            bankAccounts->at(i)->printAccount();
        }
    }
};
class SavingsAccount : public BankAccount
{
private:
    int noOfTransaction, transactionLimit;
    double penaltyAmount;
    float percentageOfInterest;

public:
    SavingsAccount(int userId, string name, double balance) : BankAccount(userId, name, balance)
    {
        noOfTransaction = 0;
        penaltyAmount = 500.00;
        percentageOfInterest = 8.5f;
        transactionLimit = 5;
        accType = "Savings";
        accNo = accNoIntial++;
    }
    void creditAmount(double amount)
    {
        if (noOfTransaction <= transactionLimit)
        {
            balance = balance + amount;
        }
    }
    void debitAmount(double amount)
    {
        if (noOfTransaction <= transactionLimit)
        {
            if ((balance - amount) >= 500)
            {
                balance = balance - amount;
            }
            else
            {
                throw LowBalanceException("Low balance");
            }
        }
    }
    void printAccount()
    {
        cout << "Bank Account details - " << endl;
        cout << "Name: " << name << endl;
        cout << "User ID: " << userId << endl;
        cout << "Account Number: " << accNo << endl;
        cout << "Balance: " << balance << endl;
        cout << "Bank Account type: " << accType << endl;
    }
    void payInterest()
    {
        balance = balance + (balance * percentageOfInterest) / 100;
    }
};

class CurrentAccount : public BankAccount
{

public:
    CurrentAccount(int userId, string name, double balance) : BankAccount(userId, name, balance)
    {
        accType = "Current";
        accNo = accNoIntial++;
    }
    void creditAmount(double amount)
    {
        balance = balance + amount;
    }
    void debitAmount(double amount)
    {

        if ((balance - amount) >= 500)
        {
            balance = balance - amount;
        }
        else
        {
            throw LowBalanceException("Low balance");
        }
    }
    void printAccount()
    {
        cout << "Bank Account details - " << endl;
        cout << "Name: " << name << endl;
        cout << "User ID: " << userId << endl;
        cout << "Account Number: " << accNo << endl;
        cout << "Balance: " << balance << endl;
        cout << "Bank Account type: " << accType << endl;
    }
};

class Loan
{
public:
    double loanAmount, interestRate, duration, totalAmount, monthlyAmount, paid, balance;
    int userId, choice;
    string loanType;
    Loan(int userId)
    {
        this->userId = userId;
    }
    void computeInterest()
    {
        cout << "Enter the choice for the type of loan you want: " << endl;
        /*education = 8;
        home = 12;
        vehicle = 7;*/
        cout
            << "1. Education Loan with 8% interest per annum." << endl;
        cout << "2. Home Loan with 12% interest per annum." << endl;
        cout << "3. Vehicle Loan with 7% interest per annum." << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            interestRate = 8.0;
            loanType = "Education Loan";
            break;
        case 2:
            interestRate = 12.0;
            loanType = "Home Loan";
            break;
        case 3:
            interestRate = 7.0;
            loanType = "Vehicle Loan";
            break;
        default:
            cout << "Invalid choice." << endl;
            break;
        }
    }
    void applyLoan()
    {
        computeInterest();
        cout << "Enter the loan amount: ";
        cin >> loanAmount;
        cout << "Enter the duration: ";
        cin >> duration;

        totalAmount = loanAmount + (duration * loanAmount * (interestRate / 100.00));
        monthlyAmount = totalAmount / (duration * 12);

        cout << "Total amount to be paid: " << totalAmount << endl;
        cout << "Total interest: " << (duration * loanAmount * (interestRate / 100.00)) << endl;
        cout << "Monthly amount to be paid: " << monthlyAmount << endl;
        balance = totalAmount;
        paid = 0.0;
    }
    void payLoan(double amt)
    {
        paid += amt;
        balance -= amt;
    }
    void printLoanDetails()
    {

        cout << "------------------------------------------------" << endl;
        cout << "Loan details of user with userId " << userId << " is -" << endl;
        cout << "Loan Type: " << loanType << endl;
        cout << "Total Loan: " << totalAmount << endl;
        cout << "Interest: " << interestRate << endl;
        cout << "Paid: " << paid << endl;
        cout << "Balance: " << balance << endl;
    }
};

class Insurance
{
public:
    string typeOfInsurance;
    double premium;
    int maturityYear, noy;
    double insuranceAmount;
    int userId;

    Insurance(int userId)
    {
        this->userId = userId;
    }
    void getInsurance()
    {
        setType();
        cout << "Enter the insurance amount: ";
        cin >> insuranceAmount;
        cout << "Enter the number of years: ";
        cin >> noy;
        computePremium();
    }
    void display()
    {
        cout << "Insurance Details: " << endl;
        cout << "User Id: " << userId << endl;
        cout << "Premium: " << premium << endl;
        cout << "Maturity Year: " << maturityYear << endl;
    }
    void computePremium()
    {
        maturityYear = 2022 + noy;
        premium = insuranceAmount / noy;
    }
    void setType()
    {
        int choice;
        cout << "Enter choice for insurance type: " << endl;
        cout << "1. Life Insurance" << endl;
        cout << "2. Vehicle Insurance" << endl;
        cout << "3. Home Insurance" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            typeOfInsurance = "LifeInsurance";
            break;
        case 2:
            typeOfInsurance = "VehicleInsurance";
            break;
        case 3:
            typeOfInsurance = "HomeInsurance";
            break;
        default:
            cout << "Invalid choice" << endl;
            break;
        }
    }
};

class BankingApplication
{
public:
    vector<User> *users;
    vector<Loan> *loans;
    vector<Insurance> *insurances;
    vector<BankAccount *> *bankAccounts;
    string loggedInUsername;
    bool loggedIn;
    int currentUserId;

private:
    static BankingApplication *instance;

    // Parameterized constructor.
    BankingApplication(vector<User> *users, vector<Loan> *loans, vector<Insurance> *insurances, vector<BankAccount *> *bankAccounts)
    {
        this->users = users;
        this->loans = loans;
        this->insurances = insurances;
        this->bankAccounts = bankAccounts;
        loggedIn = false;
    }

public:
    // Singleton pattern.
    static BankingApplication *getInstance(vector<User> *users, vector<Loan> *loans, vector<Insurance> *insurances, vector<BankAccount *> *bankAccounts)
    {
        if (!instance)
            instance = new BankingApplication(users, loans, insurances, bankAccounts);
        return instance;
    }

    // This is the function which is called first. Which displays menu of operations.
    void startApplication()
    {
        // Fornon login users.

        while (1)
        {
            int option;
            cout << endl
                 << "Welcome to Banking Application." << endl;
            cout << "-------------------------------" << endl;
            cout << "Choose one of the options from below to continue -" << endl;
            cout << "1. Login" << endl;
            cout << "2. Display all Users." << endl;
            cout << "3. Print account balance." << endl;
            cout << "4. Print BankAccount statement." << endl;
            cout << "5. Create BankAccount." << endl;
            cout << "6. Send Money." << endl;
            cout << "7. Log Out." << endl;
            cout << "8. Create new user." << endl;
            cout << "9. Apply for loan." << endl;
            cout << "10. Display Loan details." << endl;
            cout << "11. Payloan." << endl;
            cout << "12. Apply for Insurance." << endl;
            cout << "13. Display Insurance details." << endl;
            cout << "14. Display all bank accounts." << endl;
            cout << "15. Exit." << endl;
            cin >> option;
            switch (option)
            {
            case 1:
                try
                {
                    logIn();
                }
                catch (WrongPasswordException e)
                {
                    cout << e.what();
                }
                catch (InvalidUserException iue)
                {
                    cout << iue.what();
                }

                break;
            case 2:
                display();
                break;
            case 3:
                printAccountBalance();
                break;
            case 4:
                printAccountStatement();
                break;
            case 5:
                createAccount();
                break;
            case 6:
                if (loggedIn)
                {
                    try
                    {
                        sendMoney();
                    }
                    catch (LowBalanceException lbe)
                    {
                        cout << lbe.what();
                    }
                }
                else
                {
                    cout << "Login First" << endl;
                }
                break;
            case 7:
                logOut();
                break;
            case 8:
                createUser();
                break;
            case 9:
                if (loggedIn)
                {
                    applyLoan();
                }
                else
                {
                    cout << "Login First" << endl;
                }
                break;
            case 10:
                if (loggedIn)
                {
                    displayLoanDetails();
                }
                else
                {
                    cout << "Login First" << endl;
                }
                break;
            case 11:
                if (loggedIn)
                {
                    payLoan();
                }
                else
                {
                    cout << "Login First" << endl;
                }
                break;
            case 12:
                if (loggedIn)
                {
                    applyInsurance();
                }
                else
                {
                    cout << "Login First" << endl;
                }
                break;
            case 13:
                if (loggedIn)
                {
                    displayInsuranceDetails();
                }
                else
                {
                    cout << "Login First" << endl;
                }
                break;
            case 14:
                BankAccount::printAllBankAccounts(bankAccounts);
                break;
            case 15:
                cout << "Exiting...." << endl;
                exit(1);
                break;
            default:
                cout << "Invalid option." << endl;
                break;
            }
        }
    }
    // This function is used to pay the loan. The money is debitted from bank and loan is paid.
    void payLoan()
    {
        int amount;
        cout << "Enter the amout to be paid for loan: ";
        cin >> amount;
        for (int i = 0; i < bankAccounts->size(); i++)
        {
            if (bankAccounts->at(i)->userId == currentUserId)
            {
                try
                {
                    bankAccounts->at(i)->debitAmount(amount);
                }
                catch (LowBalanceException e)
                {
                    cout << e.what();
                }
            }
        }
        for (int i = 0; i < loans->size(); i++)
        {
            if (loans->at(i).userId == currentUserId)
            {
                loans->at(i).payLoan(amount);
                cout << "Successfully paid " << amount << " to loan." << endl;
            }
        }
    }

    // This function is used to create a new user.
    void createUser()
    {
        string name;
        string address;
        string username;
        string password;
        double income;
        int age;
        long long adhaar;
        cout << "Enter your name: ";
        cin >> name;
        cout << "Enter your address: ";
        cin >> address;
        cout << "Enter your username: ";
        cin >> username;
        cout << "Enter your password: ";
        cin >> password;
        cout << "Enter your income: ";
        cin >> income;
        cout << "Enter your age: ";
        cin >> age;
        cout << "Enter your aadhar number: ";
        cin >> adhaar;
        // string name, string address, string username, string password, double income, int age, long long adhaar
        User newUser(name, address, username, password, income, age, adhaar);
        users->push_back(newUser);
        cout << "User " << username << " successfully created, you can login with your credentials." << endl;
    }

    // This function prints all the users.
    void display()
    {
        for (int i = 0; i < users->size(); i++)
        {
            users->at(i).printUser();
        }
    }
    // This function is used to login into the application.
    void logIn()
    {
        bool userFound = false;
        if (!loggedIn)
        {
            string username, password;
            cout << "Login - " << endl;
            cout << "Enter Username - ";
            cin >> username;
            cout << "Enter Password - ";
            cin >> password;
            for (int i = 0; i < users->size(); i++)
            {
                if (users->at(i).username == username)
                {
                    userFound = true;
                    if (users->at(i).password == password)
                    {
                        loggedInUsername = username;
                        loggedIn = true;
                        cout << "Succesfully logged in " << loggedInUsername << endl;
                        currentUserId = users->at(i).userId;
                        break;
                    }
                    else
                    {
                        throw WrongPasswordException("Wrong user password");
                        break;
                    }
                }
            }
            if (!userFound)
            {
                throw InvalidUserException("User not found");
            }
        }
        else
        {
            cout << "Already Logged In. Logout to login with other username" << endl;
        }
    }

    // This function is used to create a new bank account for the user.
    void createAccount()
    {
        // int userId, string name, double balance
        int userId;
        string name;
        double balance = 0.0;

        // Fetching details of current user for creating Bank Account
        for (int i = 0; i < users->size(); i++)
        {
            if (users->at(i).username == loggedInUsername)
            {
                userId = users->at(i).userId;
                name = users->at(i).name;
            }
        }

        // Checking if the current user already has a Bank Account
        for (int i = 0; i < bankAccounts->size(); i++)
        {
            if (bankAccounts->at(i)->userId == userId)
            {
                cout << "Bank Account for user " << loggedInUsername << " already exists." << endl;
                break;
            }
        }
        int choice;
        BankAccount *bankAcc;
        cout << "To create Savings account press 1." << endl;
        cout << "To create Current account press 2." << endl;
        cin >> choice;
        if (choice == 1)
        {
            bankAcc = new SavingsAccount(userId, name, balance);
        }
        else if (choice == 2)
        {
            bankAcc = new CurrentAccount(userId, name, balance);
        }
        bankAccounts->push_back(bankAcc);
        cout << "Bank Account for user " << loggedInUsername << " created using user's details." << endl;
    }

    // This function is used to get the loan from the bank.
    void applyLoan()
    {
        Loan loan(currentUserId);
        loan.applyLoan();
        for (int i = 0; i < users->size(); i++)
        {
            if (users->at(i).userId == currentUserId)
            {
                users->at(i).hasLoan = true;
            }
        }
        loans->push_back(loan);
    }

    // This funtion displays the loan details of the current user.
    void displayLoanDetails()
    {
        for (int i = 0; i < loans->size(); i++)
        {
            if (loans->at(i).userId == currentUserId)
            {
                loans->at(i).printLoanDetails();
            }
        }
    }

    // This function is used to get the Insurance from the bank.
    void applyInsurance()
    {
        Insurance insu(currentUserId);
        insu.getInsurance();
        for (int i = 0; i < users->size(); i++)
        {
            if (users->at(i).userId == currentUserId)
            {
                users->at(i).hasInsurance = true;
            }
        }
        insurances->push_back(insu);
    }

    // This funtion displays the Insurance details of the current user.
    void displayInsuranceDetails()
    {
        for (int i = 0; i < insurances->size(); i++)
        {
            if (insurances->at(i).userId == currentUserId)
            {
                insurances->at(i).display();
            }
        }
    }

    // This function displays the available balance of user's bank account.
    void printAccountBalance()
    {

        if (loggedIn)
        {

            for (int i = 0; i < users->size(); i++)
            {
                if (users->at(i).username == loggedInUsername)
                {
                    for (int j = 0; j < bankAccounts->size(); j++)
                    {
                        if (users->at(i).userId == bankAccounts->at(j)->userId)
                        {
                            cout << "Account balance of " << users->at(i).username << " is " << bankAccounts->at(j)->balance << endl; // change
                            break;
                        }
                    }
                    // break;
                }
            }
        }
        else
        {
            cout << "First Login." << endl;
        }
    }

    // This function prints the details of user's Bank account.
    void printAccountStatement()
    {
        if (loggedIn)
        {

            for (int i = 0; i < users->size(); i++)
            {
                if (users->at(i).username == loggedInUsername)
                {
                    for (int j = 0; j < bankAccounts->size(); j++)
                    {
                        if (users->at(i).userId == bankAccounts->at(j)->userId)
                        {
                            cout << "Account statement of " << users->at(i).username << " is -" << endl; // << bankAccounts->at(j)->balance << endl; // change
                            bankAccounts->at(j)->printAccount();
                            break;
                        }
                    }
                    // break;
                }
            }
        }
        else
        {
            cout << "First Login." << endl;
        }
    }

    // This function sends money from the current user's bank account to the
    // mentioned user's bank account.
    void sendMoney()
    {
        double amountToSend;
        int accNoOfReceiver;
        bool sent = false;
        cout << "Enter account number to send the money: ";
        cin >> accNoOfReceiver;

        cout << "Enter the amout to send: ";
        cin >> amountToSend;
        if (amountToSend < 0)
        {
            cout << "Negative amount entered." << endl;
            return;
        }
        int accNoOfCurrentUser;
        for (int i = 0; i < bankAccounts->size(); i++)
        {
            if (bankAccounts->at(i)->accNo == accNoOfReceiver)
            {
                for (int j = 0; j < users->size(); j++)
                {
                    if (users->at(j).username == loggedInUsername)
                    {
                        for (int k = 0; k < bankAccounts->size(); k++)
                        {
                            if (users->at(j).userId == bankAccounts->at(k)->userId)
                            {
                                accNoOfCurrentUser = bankAccounts->at(k)->accNo;
                            }
                        }
                    }
                }
                for (int p = 0; p < bankAccounts->size(); p++)
                {
                    if (bankAccounts->at(p)->accNo == accNoOfCurrentUser)
                    {
                        bankAccounts->at(p)->debitAmount(amountToSend);
                    }
                }

                bankAccounts->at(i)->creditAmount(amountToSend);
                cout << "Money " << amountToSend << " successfully sent to account number " << bankAccounts->at(i)->accNo << endl;
                sent = true;
            }
        }
        if (!sent)
        {
            cout << "Incorrect account number" << endl;
        }
    }

    // Function used to logout.
    void logOut()
    {
        if (loggedIn)
        {
            loggedIn = false;
            loggedInUsername = "";
            cout << "Log out successful." << endl;
        }
        else
        {
            cout << "User has not logged in." << endl;
        }
    }
};

// The Bank class which has BankAccounts
class Bank
{
private:
    vector<BankAccount> *bankAccounts;
    string bankName;
    // BankingApplication bankingApplication;

public:
    Bank(vector<BankAccount> *bankAccounts, string bankName)
    {
        this->bankAccounts = bankAccounts;
        this->bankName = bankName;
    }
};
int BankAccount::accNoIntial = 1000;
int User::userIdIntial = 100;
BankingApplication *BankingApplication::instance = 0;
int main()
{
    cout
        << " _" << endl;
    cout << "|_)  _. ._  |  o ._   _     /\\  ._  ._  | o  _  _. _|_ o  _  ._" << endl;
    cout << "|_) (_| | | |< | | | (_|   /--\\ |_) |_) | | (_ (_|  |_ | (_) | |" << endl;
    cout << "                      _|        |   |                            " << endl;
    User u1("Sandeep", "Hubli", "sandeep", "123", 10000, 20, 9988772211),
        u2("Swaroop", "Dharwad", "swaroop", "456", 15000, 20, 7878009876);
    vector<User> users = {u1, u2};
    // int userId, int accNo, string name, double balance
    SavingsAccount s1(100, "Sandeep", 10000.00),
        s2(101, "Swaroop", 20000.00);
    vector<BankAccount *> bankAccounts = {&s1, &s2};
    // vector<User> *users, vector<Loan> *loans, vector<Insurance> *insurances, vector<BankAccount *> *bankAccounts
    vector<Insurance> insurances;
    vector<Loan> loans;
    // Singleton Pattern.
    BankingApplication *bankingApplication = bankingApplication->getInstance(&users, &loans, &insurances, &bankAccounts);
    // Bank bank(bankAccounts, "SBI", bankingApplication);
    //  BankingApplication bankingApplication(&users, &loans, &insurances, &bankAccounts);
    bankingApplication->startApplication();
    return 0;
}