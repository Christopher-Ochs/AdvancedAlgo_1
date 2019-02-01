#include <iostream>
#include <string>
#include <iterator>
#include <map>
#include <vector>
#include <tgmath.h>

using namespace std;

// Global variable of Bearcatii map.  Used to convert form
std::map<string, int> BEARCATII;

// Init map values
void initializeMap()
{
    BEARCATII.insert(pair<string, int>("a", 1));
    BEARCATII.insert(pair<string, int>("b", 2));
    BEARCATII.insert(pair<string, int>("c", 3));
    BEARCATII.insert(pair<string, int>("d", 4));
    BEARCATII.insert(pair<string, int>("e", 5));
    BEARCATII.insert(pair<string, int>("f", 6));
    BEARCATII.insert(pair<string, int>("g", 7));
    BEARCATII.insert(pair<string, int>("h", 8));
    BEARCATII.insert(pair<string, int>("i", 9));
    BEARCATII.insert(pair<string, int>("j", 10));
    BEARCATII.insert(pair<string, int>("k", 11));
    BEARCATII.insert(pair<string, int>("l", 12));
    BEARCATII.insert(pair<string, int>("m", 13));
    BEARCATII.insert(pair<string, int>("n", 14));
    BEARCATII.insert(pair<string, int>("o", 15));
    BEARCATII.insert(pair<string, int>("p", 16));
    BEARCATII.insert(pair<string, int>("q", 17));
    BEARCATII.insert(pair<string, int>("r", 18));
    BEARCATII.insert(pair<string, int>("s", 19));
    BEARCATII.insert(pair<string, int>("t", 20));
    BEARCATII.insert(pair<string, int>("u", 21));
    BEARCATII.insert(pair<string, int>("v", 22));
    BEARCATII.insert(pair<string, int>("w", 23));
    BEARCATII.insert(pair<string, int>("x", 24));
    BEARCATII.insert(pair<string, int>("y", 25));
    BEARCATII.insert(pair<string, int>("z", 26));
    BEARCATII.insert(pair<string, int>(" ", 0));
}

// Implement Euclid GCD
unsigned long long int GCD(unsigned long long int num1, unsigned long long int num2)
{
    return 0;
}

// Implement Miller-Rabin Algorithm to test for composite
bool millerRabin(unsigned long long int num)
{
    // return true if proved to composite

    // return false if otherewise
    return false;
}

bool isValidKey(unsigned long long int key)
{
    return true;
}

unsigned long long int requestPublicKey()
{
    unsigned long long int tempPublicKey;
    cout << "Please enter a positive integer for the public key: ";
    cin >> tempPublicKey;
    while (!isValidKey(tempPublicKey))
    {
        requestPublicKey();
    }
    return tempPublicKey;
}

string getUserMessage()
{
    string tempString;
    cout << "Please enter a valid message: ";
    cin.ignore(1000, '\n');
    getline(cin, tempString);
    return tempString;
}

// converts string to vector of bearcatii values
vector<int> stringToBearcatii(string input)
{
    vector<int> output;
    for (int i = 0; i <= input.size()-1; i++)
    {
        string s(1, input[i]);
        int temp = BEARCATII.find(s)->second;
        output.push_back(temp);
    }
    return output;
}

unsigned long long int base27todecimal(vector<int> base27)
{
    unsigned long long int sum = 0;
    int beginingSize = base27.size();
    for (int i = 0; i < beginingSize; i++)
    {
        int x = base27.back();
        int y = pow(27, i);
        sum += x*y;
        base27.pop_back();
    }
    return sum;
}

//converts bearcatii to string
string bearcatiiToString(vector<int> input)
{
    string temp = "";
    for (int i = 0; i <= input.size(); i++)
    {
        for (auto it = BEARCATII.begin(); it != BEARCATII.end(); ++it )
            if (it->second == input[i])
                temp.append(it->first);
    }
    return temp;
}

vector<int> decimalToBase27 (int number)
{
    vector<int> output;
    int base = 27;
    int num = number;
    while (num >= base)
    {
        output.insert(output.begin(), num % base);
        num = num / 27;
    }
    output.insert(output.begin(), num);
    return output;
}

vector<int> encrypt (string messageToEncrypt)
{
    vector<int> input = stringToBearcatii(messageToEncrypt);
    vector<int> output;
    return output;
}

string decrypt (vector<int> messageToDecrypt)
{
    vector<int> decryptedBearcatii;
    string decrytpetdMessage = bearcatiiToString(decryptedBearcatii);
    return decrytpetdMessage;
}

int main()
{
    // initialize the bearcatii map
    initializeMap();
    // request the public key from user
    unsigned long long int key = requestPublicKey();
    // request the message to be encrypted
    string message = getUserMessage();
    // convert to bearcatti
    vector<int> bearcatiiMessage = stringToBearcatii(message);

    // convert to base27 long long int
    unsigned long long int messageB27 =  base27todecimal(bearcatiiMessage);

    // encrypt using bearcatiiMessage

    //decrypt the message

    // display needed output

    return 0;
}