#include <iostream> //cout and stuff
#include <ctime> //time()
#include <cstdlib> //srand() and rand()
#include <algorithm> //sort() and find()
#include <array> //std array library lol
#include <vector> //vector library... duh

//Im not "using namespace std" here just for learning good practice

//Global declearation of data types
//N/A

//Global declearations of functions
std::vector<std::array<int, 7>> GenLottoArrays (int lottoType, int numberOfArrays, std::vector<std::array<int, 7>>& vector); //Generates arrays representing lotto numbers/rows
void CheckIfWin (int lottoType, std::vector<std::array<int, 7>> user, std::vector<std::array<int, 7>> win); //Checks if user passed vector contains the first array from win vector, if not, it generates new win array (lotto numbers)
void PrintVectorArrays(std::vector<std::array<int, 7>> vector); //Prints all arrays in a vector vertically
std::string NumToString(unsigned long num); //Converts number to string with spaces added after every 3rd digit for easy reading
void menu();

int main(){
    std::srand(std::time(0)); //Uses time as random seed for the random generators (std::rand())
    menu();
}

void menu(){
    std::srand(std::time(0)); //Uses time as random seed for the random generators (std::rand())
    std::cout << "                         Welcome to Lotto Simulations!... lol                       " << std::endl;
    std::cout << "------------------------------------------------------------------------------------" << std::endl;
    std::cout << "Please choose one of the lotteries you want to simulate:"                             << std::endl;
    std::cout << "[1] - Regular Lotto (Based of the Nowegian lottery ""Lotto"")"                        << std::endl;
    std::cout << "      7 unique and random numbers between 1-34"                                       << std::endl;
    std::cout << "[2] - Viking Lotto (Based on the multinational lottery ""VikingLotto"")"              << std::endl;
    std::cout << "      7 unique random numbers. 6 numbers between 1-48 + 1 random number between 1-8"  << std::endl;
    std::cout << "[3] - Euro Lotto (Based on the european lottery ""Eurojackpot"")"                     << std::endl;
    std::cout << "      7 unique random numbers. 5 numbers between 1-50 + 2 random number between 1-10" << std::endl;
    std::cout << std::endl;
    int lottoType = 0;
    while (lottoType < 1 || lottoType > 3){ //Loops the question of input number until the user types a valid number
        std::cout << "Type desired lotto and press ENTER: ";
        std::cin >> lottoType;
        if (lottoType < 1 || lottoType > 3 || !std::cin){
            std::cout << "ERROR! Invalid input, please try again" << std::endl; //Warns the user if they typed a inavlid number
            std::cin.clear(); //Clears error flags in cin
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Ignores rest of the line inputet to lottoType
        } else {
            std::cout << std::endl; //New line for formatting sakes
            break;
        }
    }
    int numberOfArrays; //Amopunt of different lotto numbers
    while (numberOfArrays < 1 || numberOfArrays > 10000){
        std::cout << "Please type amount of lotto numbers you want [0 - 10 000]: ";
        std::cin >> numberOfArrays;
        if (numberOfArrays < 1 || numberOfArrays > 10000){ //Warns the user if they typed a inavlid number
            std::cout << "ERROR! Invalid input, please try again" << std::endl;
            std::cin.clear(); //Clears error flags in cin
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Ignores rest of the line inputet to numberOfArrays
        } else {
            std::cout << std::endl; //New line for formatting sakes
            break;
        }
    }
    std::vector<std::array<int, 7>> userArrays;     //Vector containing a dymanic amount of 7 int element arrays
    GenLottoArrays(lottoType, numberOfArrays, userArrays);
    
    std::vector<std::array<int, 7>> winningArray;   //Vector which should only contain one 7 int element array
    GenLottoArrays(lottoType, 1, winningArray);

    std::cout << "Ready to simulate " << NumToString(numberOfArrays) << " different lotto numbers" << std::endl;
    std::cout << "Press enter so start simulation. It will run until you win..." << std::endl;
    std::getchar(); 
    std::getchar(); //Press any key to contiue
    CheckIfWin(lottoType, userArrays, winningArray);
}

std::vector<std::array<int, 7>> GenLottoArrays (int lottoType, int numberOfArrays, std::vector<std::array<int, 7>>& vector){ 
    vector.clear();
    for (int i=1; i<=numberOfArrays; i++){ //Loops though array generation until vector has recieved numberOfArrays arrays    
        std::array<int, 7> array;
        int randNum;
        int arrayPlace;
        while (true){ //Used so that if the generated array is already in the vector, it will loop and create a new array
            if (lottoType == 1){ //Generates 7 unike numbers from 1-34 (Regular Lotto)    
                for (arrayPlace=0; arrayPlace<=6; arrayPlace++){
                randNum = (std::rand() % 34) + 1; //Rand generates number between 0 and RAND_MAX (Typ. 32767). % 34 assures that it dossent exeed 33. We have to add 1 to make it be bewteen 1 and 34 instead of 0 and 33
                    while  (std::find(array.begin(), array.end(), randNum) != array.end()){ //If random alrady is in array, create a new randNum until it's uniqe
                    randNum = (std::rand() % 34) + 1;
                    }
                    array.at(arrayPlace) = randNum; //Adds the random number to array.
                }
                std::sort(array.begin(), array.begin()+arrayPlace); //Sorts the array from lowest to highest number
                
                if (std::find(vector.begin(), vector.end(), array) == vector.end()){ //If the array is not in the vecotr already, it wil break the while loop and continue
                    break;
                }
            } else if (lottoType == 2){ //Generates 7 unique numbers. 6 from 1-48, + 1 from 1-8 (VikingLotto)
                for (arrayPlace=0; arrayPlace<=5; arrayPlace++){
                    randNum = (std::rand() % 48) + 1;
                    while  (std::find(array.begin(), array.end(), randNum) != array.end()){
                        randNum = (std::rand() % 48) + 1;
                    }
                    array.at(arrayPlace) = randNum;
                }
                std::sort(array.begin(), array.begin()+arrayPlace);
            
                //Dont take the last random into the sorting as this digit is supposed to be at the end of the array.
                randNum = (std::rand() % 8) + 1; //Generates the last number in the array which has to be between 1 an 8
                array[6] = randNum; //Adds the last number to the array. This number is suppoes to be at the end, so it is not sorted with the others
                
                if (std::find(vector.begin(), vector.end(), array) == vector.end()){ //If the array is not in the vector alreayd, it wil break the while loop and continue
                    break;
                }
            } else if (lottoType == 3){ //Generates 7 unike numbers. 5 from 1-50, + 2 from 1-10 (Eurojackpot)
                for (arrayPlace=0; arrayPlace<=4; arrayPlace++){ 
                    randNum = (std::rand() % 50) + 1;
                    while  (std::find(array.begin(), array.end(), randNum) != array.end()){
                        randNum = (std::rand() % 50) + 1;
                    }
                    array.at(arrayPlace) = randNum;
                }   
                std::sort(array.begin(), array.begin()+arrayPlace);
            
                for (arrayPlace=5; arrayPlace<=6; arrayPlace++){ //Generates the last 2 numbers (1-10)
                    randNum = (std::rand() % 10) + 1;
                    while  (arrayPlace == 6 && randNum == array[5] ){
                        randNum = (std::rand() % 10) + 1;
                    }
                    array.at(arrayPlace) = randNum;
                }
                std::sort(array.begin()+5, array.begin()+arrayPlace); //Sorts the last two digits for themselves as this two are supposed to be at the end of the array
                
                if (std::find(vector.begin(), vector.end(), array) == vector.end()){ //If the array is not in the vector already, it wil break the while loop and continue
                    break;
                }
            }
        }
        vector.push_back(array); //Appends array to vector
    }
    return vector; //This return will return an empty vector if none of the lottoTypes is selected.
}

void PrintVectorArrays(std::vector<std::array<int, 7>> vector){
    for (int i=0; i<vector.size() && i <= 9; i++){ //Loop through for every element in vector but not over 10 (9 since array start at 0) elements. If it were to print more than 10 elements in form big vecotrs, it would look messy on the output and slow the program down.
        std::array<int, 7> array = vector[i]; //Sets "array" to be the array an "i" place in the vector
        for(int x=0; x<array.size(); x++){
            if (array.at(x) < 10){
                std::cout << ' ' << ' ' << array.at(x); //Adds double spaced infront of number if its lower than 10
            } else {
                std::cout << ' ' << array.at(x); //If number is higher than 10, it gets added one space infront
            }
        }
        if (i < vector.size()-1 && vector.size() > 1 && i < 9){ //If "i"(element in vector) is not the last element and there is more than just one element, and the i is not grater than 10, add a new line after the print
            std::cout << std::endl;
        } else if (vector.size() > 10) { //If the vector has more than 10 elements, the last line printed shoud tell how many arrays which weren't printed
            std::cout << std::endl;
            std::cout << "and " << NumToString(vector.size() - 10) << " more arrays..";
        }   
    }
}

std::string NumToString(unsigned long num){
    std::string numString = std::to_string(num); //Converts to string
    for (int i=numString.length()-3; i>0; i-=3){ //Adds space after every 3rd digit
        numString.insert(i, " ");
    }
    return numString;
}

void CheckIfWin (int lottoType, std::vector<std::array<int, 7>> user, std::vector<std::array<int, 7>> win) {
    unsigned long w = 1; //Week/Try number
    while (std::find(user.begin(), user.end(), win[0]) == user.end()){ //Checks whether the first element in the winning vector is in the user vector, and loops until it is
        if ((w % 100000) == 0){ //Prints out every 100,000th attemt so the program isn't so dull. Also so it's possbile to see some of the winning numbers which didn't match up
            PrintVectorArrays(user);
            std::cout << "  -";
            PrintVectorArrays(win);
            std::cout << " | Week/Try: " << NumToString(w) << std::endl << std::endl; //Prints week/try number and adds to new line due to formatting the conole output
        }
        w++; //Adds 1 to week/try number
        
        //Genreates new winning array since tha last didnt match any of the user arrays
        GenLottoArrays(lottoType, 1, win);
    }

    //If you win (winning array is in user vector)
    std::cout << "Yadigg, you won!" << std::endl;
    PrintVectorArrays(user);
    std::cout << "  -";
    PrintVectorArrays(win);
    std::cout << " | Week/Try: " << NumToString(w) << std::endl;

    std::cout << "Press enter to yeet away" << std::endl;
    std::getchar(); //Press key to quit, so that the program dosent quit instantly
}