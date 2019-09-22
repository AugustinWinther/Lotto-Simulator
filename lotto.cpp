#include <iostream>     //std::cout and std::cin
#include <ctime>        //std::time
#include <cstdlib>      //std::srand and std::rand
#include <algorithm>    //std::sort and std::find
#include <array>        //std::array
#include <vector>       //std::vector

//Im not "using namespace std" here just for learning good practice

//Global declearation of data types
//N/A

//Global declearations of functions
std::vector<std::array<int, 7>> AutoGenLottoNumbers (int lottoType, int amountOfNumbers, std::vector<std::array<int, 7>>& vector);  //Auto generates arrays representing lotto numbers/rows
std::vector<std::array<int, 7>> UserGenLottoNumbers (int lottoType, std::vector<std::array<int, 7>>& vector);                       //User generates arrays representing lotto numbers/rows
void CheckIfWin (int lottoType, std::vector<std::array<int, 7>> user, std::vector<std::array<int, 7>> win);                         //Checks if user passed vector contains the first array from win vector, if not, it generates new win array (lotto numbers)
void PrintLottoNumbers(std::vector<std::array<int, 7>> vector, int printAmount);                                                    //Prints all arrays in a vector vertically
void PrintLottoArray (std::array<int, 7> array);                                                                                    //Prints array                 
std::string NumToString(unsigned long num);                                                                                         //Converts number to string with spaces added after every 3rd digit for easy reading
void menu();

int main(){
    std::srand(std::time(0)); //Uses time as random seed for the random generators (std::rand())

    //Welcome message
    std::cout << "                         Welcome to Lotto Simulations!... lol                       " << std::endl;
    std::cout << "------------------------------------------------------------------------------------" << std::endl;
    
    menu();
    
    //Press key to quit, so that the program dosent quit instantly
    std::cout << "Press enter to yeet away" << std::endl;
    std::getchar();
}

void menu(){
    //Declearing variables for this function
    int lottoType = 0;              //1=Regualr, 2=Viking, 3=Euro. Defined to 0 for resetting purposes
    int lottoPrice = 0;             //Price of specified lotto. Gets defined depending on what lottoType is selected. Defined to 0 for resetting purposes
    int amountOfNumbers = 0;        //Amount of different lotto numbers. Defined to 0 for resetting purposes
    std::string lottoTypeString;    //String represenmting the lottoType variable. Used for console ouptut
    std::vector<std::array<int, 7>> userNumbers; //User vector numbers

    //Prints out menu
    std::cout << "Please choose one of the lotteries you want to simulate:"                             << std::endl;
    std::cout << "[1] - Regular Lotto (Based of the Nowegian lottery ""Lotto"")"                        << std::endl;
    std::cout << "      7 unique and random numbers between 1-34"                                       << std::endl;
    std::cout << "[2] - Viking Lotto (Based on the multinational lottery ""VikingLotto"")"              << std::endl;
    std::cout << "      7 unique random numbers. 6 numbers between 1-48 + 1 random number between 1-8"  << std::endl;
    std::cout << "[3] - Euro Lotto (Based on the european lottery ""Eurojackpot"")"                     << std::endl;
    std::cout << "      7 unique random numbers. 5 numbers between 1-50 + 2 random number between 1-10" << std::endl << std::endl;

    //lottoType choice loop
    while (lottoType < 1 || lottoType > 3){ //Loops the question of input number until the user types a valid number
        std::cout << "Type desired lotto and press ENTER: ";
        std::cin >> lottoType;
        if (lottoType < 1 || lottoType > 3 || std::cin.fail() || std::cin.peek()!='\n' ){ //std::cin.fail() checks wether the input fits the variable. std::cin.peek will in this case check that the next character in isteam is a "new line", "ENTER" key input basically, and not something else
            std::cout << "ERROR! Invalid input, please try again" << std::endl << std::endl; //Warns the user if they typed a inavlid number
            std::cin.clear(); //Clears error flags in cin
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Ignores rest of the line inputet to lottoType
            lottoType = 0; //Reset lotto type incase wrong inputs were saved to the varible (eg. whole numbers from floats og double inputs)
        } else if (lottoType == 1){
            lottoTypeString = "Regular Lotto";
            lottoPrice = 5;
            break;
        } else if (lottoType == 2){
            lottoTypeString = "Viking Lotto";
            lottoPrice = 6;
            break;
        } else if (lottoType == 3){
            lottoTypeString = "Euro Lotto";
            lottoPrice = 25;
            break;
        }
    }
    std::cout << lottoTypeString << " chosen..." << std::endl << std::endl;
    
    //Generating winning numbers
    std::vector<std::array<int, 7>> winningNumbers; 
    AutoGenLottoNumbers(lottoType, 1, winningNumbers); 
 
    //UserGenerated or Autogenerated coice loop
    std::cout << "[1] - Create your own lotto numbers"              << std::endl;
    std::cout << "[2] - Automatically generate random lotto numbers"<< std::endl << std::endl;
    int choice = 0;
    while (choice < 1 || choice > 2){ //Loops the question of input number until the user types a valid number
        std::cout << "Type desired choice and press ENTER: ";
        std::cin >> choice;
        if (choice < 1 || choice > 2 || std::cin.fail() || std::cin.peek()!='\n' ){ //std::cin.fail() checks wether the input fits the variable. std::cin.peek will in this case check that the next character in isteam is a "new line", "ENTER" key input basically, and not something else
            std::cout << "ERROR! Invalid input, please try again" << std::endl << std::endl; //Warns the user if they typed a inavlid number
            std::cin.clear(); //Clears error flags in cin
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Ignores rest of the line inputet to lottoType
            choice = 0; //Reset choice incase wrong inputs were saved to the varible (eg. whole numbers from floats og double inputs)
        } else if (choice == 1){
            bool doneGen = 1;
            while (doneGen){
                std::cout << std::endl;
                UserGenLottoNumbers(lottoType, userNumbers);
                std::cout << "Here are your current numbers:" << std::endl;
                PrintLottoNumbers(userNumbers, 10000);
                std::cout << std::endl << std::endl;
                std::cout << "[1] - Continue to simulation"   << std::endl;
                std::cout << "[2] - Create more numbers"      << std::endl;
                int choice = 0;
                while (choice < 1 || choice > 2){ //Loops the question of input number until the user types a valid number
                    std::cout << "Type desired choice and press ENTER: ";
                    std::cin >> choice;
                    if (choice < 1 || choice > 2 || std::cin.fail() || std::cin.peek()!='\n' ){ //std::cin.fail() checks wether the input fits the variable. std::cin.peek will in this case check that the next character in isteam is a "new line", "ENTER" key input basically, and not something else
                        std::cout << "ERROR! Invalid input, please try again" << std::endl << std::endl; //Warns the user if they typed a inavlid number
                        std::cin.clear(); //Clears error flags in cin
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Ignores rest of the line inputet to lottoType
                        choice = 0; //Reset choice incase wrong inputs were saved to the varible (eg. whole numbers from floats og double inputs)
                    } else if (choice == 1){
                        doneGen = 0;
                        std::cout << std::endl;
                        break;
                    }
                }
            }   
        } else if (choice == 2){
            //amountOfNumbers choice loop
            while (amountOfNumbers < 1 || amountOfNumbers > 10000){ //Loops the question of input number until the user types a valid number
                std::cout << "Please type amount of random lotto numbers you want [1 - 10 000]: ";
                std::cin >> amountOfNumbers;
                if (amountOfNumbers < 1 || amountOfNumbers > 10000 || std::cin.fail() || std::cin.peek()!='\n'){ 
                    std::cout << "ERROR! Invalid input, please try again" << std::endl << std::endl; //Warns the user if they typed a inavlid number
                    std::cin.clear(); //Clears error flags in cin
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Ignores rest of the line inputet to amountOfNumbers
                    amountOfNumbers = 0; //Reset lotto type incase wrong inputs were saved to the varible (eg. whole numbers from floats og double inputs)
                } else {
                    std::cout << std::endl; //New line for formatting sakes
                    break;
                }
            }
            std::cout << "Generating lotto numbers..." << std::endl;
            AutoGenLottoNumbers(lottoType, amountOfNumbers, userNumbers);
            std::cout << "Finished!" << std::endl << std::endl;
            break;
        }
    }

    std::cout << "Ready to simulate " << NumToString(userNumbers.size()) << " different lotto numbers on " << lottoTypeString <<std::endl;
    std::cout << NumToString(userNumbers.size()) << " " << lottoTypeString << " numbers would cost you: " << NumToString(userNumbers.size() * lottoPrice) << "kr (NOK, Norwegian kroner)" << std::endl;
    std::cout << "Press enter so start simulation. It will run until you win..." << std::endl;
    std::getchar(); 
    std::getchar(); //Press any key to contiue
    CheckIfWin(lottoType, userNumbers, winningNumbers);
}

std::vector<std::array<int, 7>> AutoGenLottoNumbers (int lottoType, int amountOfNumbers, std::vector<std::array<int, 7>>& vector){ 
    vector.clear();
    for (int i=1; i<=amountOfNumbers; i++){ //Loops though array generation until vector has recieved amountOfNumbers arrays    
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

std::vector<std::array<int, 7>> UserGenLottoNumbers (int lottoType, std::vector<std::array<int, 7>>& vector){ 
    std::array<int, 7> array = {0, 0, 0, 0, 0, 0, 0};
    int arrayPlace;
    int num;

    //Regular Lotto Procedure
    if (lottoType == 1){   
        for (arrayPlace=0; arrayPlace<=6; arrayPlace++){
            while (true){
                std::cout << "Please type a number between 1-34: ";
                std::cin >> num;
                if (num < 1 || num > 34 || std::cin.fail() || std::cin.peek()!='\n'){ 
                    std::cout << "ERROR! Invalid input, please try again" << std::endl << std::endl; //Warns the user if they typed a inavlid number
                    std::cin.clear(); //Clears error flags in cin
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Ignores rest of the line inputet to amountOfNumbers
                    num = 0; //Reset number incase wrong inputs were saved to the varible (eg. whole numbers from floats og double inputs)
                } else if (std::find(array.begin(), array.end(), num) != array.end()){ 
                    std::cout << "ERROR! Number already selected, please try again..." << std::endl << std::endl;
                } else {
                    array.at(arrayPlace) = num;     //Adds the number to array.
                    std::sort(array.begin(), array.begin()+arrayPlace+1); //Sorts the array from lowest to highest number
                    break;
                }
            }
            PrintLottoArray(array);
        }
        vector.push_back(array); //Appends array to vector
        return vector;
    }
    
    //Viking Lotto Procedure
    else if (lottoType == 2){   
        for (arrayPlace=0; arrayPlace<=6; arrayPlace++){
            while (true){ 
                //First 6 numbers
                if (arrayPlace < 6){
                    std::cout << "Please type a number between 1-48: ";
                    std::cin >> num;
                    if (num < 1 || num > 48 || std::cin.fail() || std::cin.peek()!='\n'){ 
                        std::cout << "ERROR! Invalid input, please try again" << std::endl << std::endl; //Warns the user if they typed a inavlid number
                        std::cin.clear(); //Clears error flags in cin
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Ignores rest of the line inputet to amountOfNumbers
                        num = 0; //Reset number incase wrong inputs were saved to the varible (eg. whole numbers from floats og double inputs)
                    } else if (std::find(array.begin(), array.end(), num) != array.end()){ 
                        std::cout << "ERROR! Number already selected, please try again..." << std::endl << std::endl;
                    } else {
                        array.at(arrayPlace) = num;     //Adds the number to array.
                        std::sort(array.begin(), array.begin()+arrayPlace+1); //Sorts the array from lowest to highest number
                        break;
                    }
                }
                
                //Last number
                else if (arrayPlace == 6){
                    std::cout << "Please type a number between 1-8: ";
                    std::cin >> num;
                    if (num < 1 || num > 8 || std::cin.fail() || std::cin.peek()!='\n'){ 
                        std::cout << "ERROR! Invalid input, please try again" << std::endl << std::endl; //Warns the user if they typed a inavlid number
                        std::cin.clear(); //Clears error flags in cin
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Ignores rest of the line inputet to amountOfNumbers
                        num = 0; //Reset number incase wrong inputs were saved to the varible (eg. whole numbers from floats og double inputs)
                    } else {
                        array.at(arrayPlace) = num;     //Adds the number to array.
                        break;
                    }
                }  
            }
            PrintLottoArray(array);
        }
        vector.push_back(array); //Appends array to vector
        return vector;
    }

    //Euro Lotto Procedure
    else if (lottoType == 3){   
        for (arrayPlace=0; arrayPlace<=6; arrayPlace++){
            while (true){ 
                //First 5 numbers
                if (arrayPlace < 5){
                    std::cout << "Please type a number between 1-50: ";
                    std::cin >> num;
                    if (num < 1 || num > 50 || std::cin.fail() || std::cin.peek()!='\n'){ 
                        std::cout << "ERROR! Invalid input, please try again" << std::endl << std::endl; //Warns the user if they typed a inavlid number
                        std::cin.clear(); //Clears error flags in cin
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Ignores rest of the line inputet to amountOfNumbers
                        num = 0; //Reset number incase wrong inputs were saved to the varible (eg. whole numbers from floats og double inputs)
                    } else if (std::find(array.begin(), array.end(), num) != array.end()){ 
                        std::cout << "ERROR! Number already selected, please try again..." << std::endl << std::endl;
                    } else {
                        array.at(arrayPlace) = num;     //Adds the number to array.
                        std::sort(array.begin(), array.begin()+arrayPlace+1); //Sorts the array from lowest to highest number
                        break;
                    }
                }
                
                //Last 2 numbers
                else if (arrayPlace > 4){
                    std::cout << "Please type a number between 1-10: ";
                    std::cin >> num;
                    if (num < 1 || num > 10 || std::cin.fail() || std::cin.peek()!='\n'){ 
                        std::cout << "ERROR! Invalid input, please try again" << std::endl << std::endl; //Warns the user if they typed a inavlid number
                        std::cin.clear(); //Clears error flags in cin
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Ignores rest of the line inputet to amountOfNumbers
                        num = 0; //Reset number incase wrong inputs were saved to the varible (eg. whole numbers from floats og double inputs)
                    } else if (std::find(array.begin()+arrayPlace-1, array.end(), num) != array.end()){ 
                        std::cout << "ERROR! Number already selected, please try again..." << std::endl << std::endl;
                    } else {
                        array.at(arrayPlace) = num;     //Adds the number to array.
                        std::sort(array.begin()+5, array.begin()+arrayPlace+1); //Sorts the array from lowest to highest number
                        break;
                    }
                } 
            }
            PrintLottoArray(array);
        }
        vector.push_back(array); //Appends array to vector
        return vector;
    }
    return vector; //This return will return an empty vector if none of the lottoTypes is selected.
}

void PrintLottoNumbers(std::vector<std::array<int, 7>> vector, int printAmount){
    //If the printAmount is bigger than vector size, set print amount to vector size since we cant print out more elements than the vector has
    if (printAmount > vector.size()){
        printAmount = vector.size();
    }

    //Prints out printAmount elements from passed vector
    for (int i=0; i<vector.size() && i <= printAmount - 1 ; i++){ //Loop through for every element in vector but not over 10 (9 since array start at 0) elements. If it were to print more than 10 elements in form big vecotrs, it would look messy on the output and slow the program down.
        std::array<int, 7> array = vector[i]; //Sets "array" to be the array at "i" place in the vector
        for(int x=0; x<array.size(); x++){
            if (array[x] == 0){
                std::cout << " | --"; //If number is 0, represent it my double dashes as this is not a valid lotto number
            } else if (array[x] < 10) {
                std::cout << " |  " << array[x];//If number is above 10, give it two spaces inforn to keep the format consistent on output
            } else {
                std::cout << " | "<< array[x];      
            }
        }
        if (i == printAmount - 1){
            std::cout << " |";  //If the last array has been printed, do not add a new line 
        } else {
            std::cout << " |" << std::endl; 
        }
         
    }
}

void PrintLottoArray (std::array<int, 7> array){
    //PrintsOutArray
    for(int x=0; x<array.size(); x++){
        if (array[x] == 0){
            std::cout << " | --";
        } else if (array[x] < 10) {
            std::cout << " |  " << array[x];
        } else {
            std::cout << " | "<< array[x];      
        }
    }
    std::cout << " |" << std::endl;
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
        if ((w % (10001-user.size())) == 0){ //Prints out every 10000th attemt so the program isn't so dull. Also so it's possbile to see some of the winning numbers which didn't match up
            std::cout << "Your lotto numbers:                       Winning lotto number:" << std::endl;
            PrintLottoNumbers(user, 10);
            std::cout << "    ";
            PrintLottoNumbers(win, 10);
            std::cout << "   Week/Try: " << NumToString(w) << std::endl; //Prints week/try number and adds to new line due to formatting the conole output
            if (user.size() > 10){
                std::cout << "and " << NumToString(user.size() - 10) << " more lotto numbers..." << std::endl << std::endl;
            } else {
                std::cout << std::endl << std::endl;
            }
        }
        w++; //Adds 1 to week/try number
        
        //Genreates new winning array since tha last didnt match any of the user arrays
        AutoGenLottoNumbers(lottoType, 1, win);
    }

    //If you win (winning array is in user vector)
    std::cout << "Yadigg, you won!" << std::endl;
    std::cout << "Your lotto numbers:                       Winning lotto numbers:" << std::endl;
    PrintLottoNumbers(user, 10);
    std::cout << "    ";
    PrintLottoNumbers(win, 10);
    std::cout << "   Week/Try: " << NumToString(w) << std::endl;
    if (user.size() > 10){
        std::cout << "and " << NumToString(user.size() - 10) << " more lotto numbers..." << std::endl << std::endl;
    } else {
        std::cout << std::endl << std::endl;
    }
}