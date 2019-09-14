#include <iostream> //cout and stuff
#include <ctime> //time()
#include <cstdlib> //srand() and rand()
#include <algorithm> //sort() and find()
#include <array> //std array library lol
#include <vector> //vector library... duh

//Im not "using namespace std" here just for learning good practice

//Global declearation of data types
std::vector<std::array<int, 7>> userArrays;     //userArrays is a vector since the user of the program can choose how many arrays he want sto check up against the winning array
std::vector<std::array<int, 7>> winningArray;   //Creates an winning array in Vikinglotto

//Global declearations of functions
std::vector<std::array<int, 7>> GenLottoArrays (std::string lottoType, int numberOfArrays, std::vector<std::array<int, 7>>& vector); //First parameter is what type of lotto you want. Second parameter will be what array variable you want the random array to be assigned to
void CheckIfWin (std::string lottoType, std::vector<std::array<int, 7>> user, std::vector<std::array<int, 7>> win); //User array, and winning array. Also need to pass lotto Type for the creation of a new lotto array
void PrintVectorArrays(std::vector<std::array<int, 7>> vector);
std::string NumToString(unsigned long num);

int main(){
    std::srand(std::time(0)); //Uses time as random seed. This has to be called only once
    GenLottoArrays("regular", 10, userArrays); //This generates a radnom VikingLotto array, and returns it to "userVikingArrway"
    GenLottoArrays("regular", 1, winningArray);
    CheckIfWin("regular", userArrays, winningArray);
}

std::vector<std::array<int, 7>> GenLottoArrays (std::string lottoType, int numberOfArrays, std::vector<std::array<int, 7>>& vector){ 
    vector.clear();
    if (lottoType == "regular"){ //Generates 7 unike numbers from 1-34 (Regular Lotto)
        for (int i=1; i<=numberOfArrays; i++){    
            std::array<int, 7> array;
            int randNum;
            int arrayPlace;
            while (true){
                for (arrayPlace=0; arrayPlace<=6; arrayPlace++){
                randNum = (std::rand() % 34) + 1; //Rand generates number between 0 and RAND_MAX (Typ. 32767). % 34 assures that it dossent exeed 33. We have to add 1 to make it be bewteen 1 and 34 instead of 0 and 33
                    while  (std::find(array.begin(), array.end(), randNum) != array.end()){ //If randum alrady is in array, create a new randNum until it's uniqe
                    randNum = (std::rand() % 34) + 1;
                    }
                    array.at(arrayPlace) = randNum; //Adds the random number to it's set place in the array. The reasen to replacing instead of adding is becaouse the array already has 7 elemetns which needs to be replace to recieve a new unike array.
                }
                std::sort(array.begin(), array.begin()+arrayPlace); //Sorts the array accending from the start index of the array to the last index in the array where a number was written
                
                if (std::find(vector.begin(), vector.end(), array) == vector.end()){ //If the array is not in the vecotr alreayd, it wil break the while loop and continue
                    break;
                }
            }
            vector.push_back(array); //appends array to vector
        }
        return vector; //Returns the vector to passed vector, basically changing the vector that is passed to the one generated here
    }
    else if (lottoType == "viking"){ //Generates 7 unike numbers. 6 from 1-48, + 1 VikingTall from 1-8 (VikingLotto)
        for (int i=1; i<=numberOfArrays; i++){    
            std::array<int, 7> array;
            int randNum;
            int arrayPlace;         
            while (true){    
                for (arrayPlace=0; arrayPlace<=5; arrayPlace++){
                    randNum = (std::rand() % 48) + 1;
                    while  (std::find(array.begin(), array.end(), randNum) != array.end()){
                        randNum = (std::rand() % 48) + 1;
                    }
                array.at(arrayPlace) = randNum;
                }
                std::sort(array.begin(), array.begin()+arrayPlace);
            
                //Dont take the last random into the sorting as this digit is supposed to be at the end of the array.
                randNum = (std::rand() % 8) + 1; //Generates Vikingtall, the last number in the array which has to be between 1 an 8
                array[6] = randNum; //Adds viking tall to the vikingNum array at the last place. No need to check if the humber already is in the array as this number is different from the others
                
                if (std::find(vector.begin(), vector.end(), array) == vector.end()){ //If the array is not in the vecotr alreayd, it wil break the while loop and continue
                    break;
                }
            }    
            vector.push_back(array); //Retruns array
        }
        return vector; //Returns the vector to passed vector, basically changing the vector that is passed to the one generated here
    }
    else if (lottoType == "euro"){
        for (int i=1; i<=numberOfArrays; i++){    
            std::array<int, 7> array;
            int randNum; 
            int arrayPlace;       
            while (true){
                for (arrayPlace=0; arrayPlace<=4; arrayPlace++){ //Generates 7 unike numbers. 5 from 1-50, + 2 Stjerneatll from 1-10 (Eurojackpot)
                    randNum = (std::rand() % 50) + 1;
                    while  (std::find(array.begin(), array.end(), randNum) != array.end()){
                        randNum = (std::rand() % 50) + 1;
                    }
                array.at(arrayPlace) = randNum;
                }   
                std::sort(array.begin(), array.begin()+arrayPlace);
            
                for (arrayPlace=5; arrayPlace<=6; arrayPlace++){ //Generates the last 2
                    randNum = (std::rand() % 10) + 1;
                    while  (arrayPlace == 6 && randNum == array[5] ){
                        randNum = (std::rand() % 10) + 1;
                    }
                array.at(arrayPlace) = randNum;
                }
                std::sort(array.begin()+5, array.begin()+arrayPlace); //Sorts the last two digits (Stjernetall) for themselves as this two are supposed to be at the end of the array
                
                if (std::find(vector.begin(), vector.end(), array) == vector.end()){ //If the array is not in the vecotr alreayd, it wil break the while loop and continue
                    break;
                }
            }    
            vector.push_back(array); //Retruns array
        }
        return vector; //Returns the vector to passed vector, basically changing the vector that is passed to the one generated here
    }
    return vector; //This return will return an empy vector if no lottoType is selected.
}

void PrintVectorArrays(std::vector<std::array<int, 7>> vector){ //Prints array with space inbewteen to make stuff look nice in command line
    for (int i=0; i<vector.size(); i++){
        std::array<int, 7> array = vector[i]; //Sets array to be one of the arrays from the vector
        for(int x=0; x<array.size(); x++){
            if (array.at(x) < 10){
                std::cout << ' ' << ' ' << array.at(x);
            } else {
                std::cout << ' ' << array.at(x);
            }
        }
        if (i < vector.size()-1 && vector.size() > 1){ //If i(element in vector) is not the last elemt and there is more than just one element, add a new line after the print
            std::cout << std::endl; //new line lol 
        }    
    }
}

std::string NumToString(unsigned long num){ //Function to add spaces after every 3rd digit in a number
    std::string numString = std::to_string(num); //Converts to string
    for (int i=numString.length(); i>0; i-=3){  //Adds space after every 3rd digit
        numString.insert(i, " ");
    }
    return numString;
}

void CheckIfWin (std::string lottoType, std::vector<std::array<int, 7>> user, std::vector<std::array<int, 7>> win) {
    unsigned long w = 1; //Week Number. its long cuz it can pass 4,294,967,295, tho its extreeeeeeeemeley unlikely
    while (std::find(user.begin(), user.end(), win[0]) == user.end()){ //Checks wether the first element in the winning vector is in the user vector, and loops until it is
        if ((w % 100000) == 0){
            PrintVectorArrays(user);
            std::cout << "  -";
            PrintVectorArrays(win);
            std::cout << " | Week/Try: " << NumToString(w) << std::endl << std::endl; //Prints week/try number and adds to new line due to formatting the conole output
        }
        w++;//Adds week number
        
        //Genreates new winning array
        GenLottoArrays(lottoType, 1, win);
    }

    std::cout << "Yadigg, you won!" << std::endl;
    PrintVectorArrays(user);
    std::cout << "  -";
    PrintVectorArrays(win);
    std::cout << " | Week/Try: " << NumToString(w) << std::endl;

    std::cout << "Press enter to yeet away" << std::endl;
    std::getchar(); //Press key to quit
}