#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<bits/stdc++.h>
void readData(std::ifstream& file){
    std::vector<std::string> vector = {};
    std::string line;
    std::cout << "opening" << std::endl;
    if(file.is_open()){
        int i =0;
        const char del = ' ';
        std::cout << "begin" << std::endl;
        while(getline(file, line)&& i<10){
            //std::cout << line << std::endl; 
            std::stringstream ss(line);
            std::string t;
            while(getline(ss, t, del)){
                std::cout << t << "\n" << std::endl;
                vector.push_back(t);
            }
            
            i++;
        }
        file.close();
    }else{
        std::cout << "file is not opened" << std::endl;
    }
    std::cout << "vector size is: " << vector.size() <<  std::endl;

}
void writer(std::string s){
    std::cout << s << std::endl;

}
int main(int argc, char** argv){
    std::string s;
    int coutn = 0;
    unsigned int commonLength = 0;
    while(std::cin){
        std::cin >> s;
        coutn++;
        commonLength+=s.length();
    }
    writer(std::to_string(commonLength/coutn));

    return 0;
}
