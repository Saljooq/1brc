#include <iostream>
#include <fstream>
#include <string.h>
#include <map>

class temps {
public:
    float min;
    float max;
    float total;
    int count;
    temps(float initial) : min{initial}, max{initial}, total{initial}, count{1} {};
    void add(float newTemp){
        total += newTemp;
        count += 1;
        if (newTemp < min){ min = newTemp; }
        if (newTemp > max){ max = newTemp; }
    };
};

int main(){
    // Create a text string, which is used to output the text file
    std::string myText;

    // Read from the text file
    std::ifstream MyReadFile("../measurements.txt");

    auto max = 100;
    auto counter = 0;

    float f;
    std::string s;

    auto delimiter = ";";

    std::map<std::string, temps> store{};

    while (getline (MyReadFile, myText)) {

        int delimeter_pos =  myText.find_first_of(";");
        s = myText.substr(0, delimeter_pos);
        f = std::atof(myText.substr(delimeter_pos + 1, -1).data());


        std::cout << "pased info. string:" << s << "   parse float: " << f << std::endl;
        auto res = store.find(s);
        if (res == store.end()){
            store.insert(std::pair<std::string, temps>(s, temps{f}));
        } else {
            res->second.add(f);
        }
        // counter += 1;
        // if (counter > max){ break; }
    }

    // Close the file
    MyReadFile.close(); 

    for (auto reading : store){
        std::cout << reading.first << "  min: " << reading.second.min << "  max: " << reading.second.max
         << "  avg: " << reading.second.total/reading.second.count << std::endl;
    }


}