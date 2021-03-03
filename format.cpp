#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char *argv[]){

	std::string input(argv[1]);
	std::string output(argv[2]);

	std::fstream fin;
	fin.open(input);

	std::fstream fout;
	fout.open(output, std::ios::out);

	std::string temp;

	for(int i = 0;i < 7;++i)
		std::getline(fin,temp);
	while(fin >> temp){
		fin >> temp;
		fout << temp << " ";
		fin >> temp;
		fout << temp << "\n";
	}

}
