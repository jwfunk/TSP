#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

double Area(double dX0, double dY0, double dX1, double dY1, double dX2, double dY2) {
	double dArea = ((dX1 - dX0)*(dY2 - dY0) - (dX2 - dX0)*(dY1 - dY0))/2.0;
	return (dArea > 0.0) ? dArea : -dArea;
}

double Length(double dX0, double dY0, double dX1, double dY1) {
	double dLength = std::sqrt((dX1 - dX0) * (dX1 - dX0) + (dY1 - dY0) * (dY1 - dY0));
	return (dLength > 0.0) ? dLength : -dLength;
}

double PathLength(std::vector<int> path, std::vector<double> Xpoints, std::vector<double> Ypoints){
	double length = 0;
	for(long unsigned int i = 0;i < path.size() - 1; ++i){
		length += Length(Xpoints[path[i]],Ypoints[path[i]],Xpoints[path[i + 1]],Ypoints[path[i + 1]]);
	}
	length += Length(Xpoints[path[path.size() - 1]],Ypoints[path[path.size() - 1]],Xpoints[path[0]],Ypoints[path[0]]);
	return length;
}

bool containsFalse(std::vector<bool> inPath){
	for(long unsigned int i = 0; i < inPath.size(); ++i){
		if(inPath[i] == false)
			return true;
	}
	return false;
}

void save(std::vector<int> path, std::vector<double> Xpoints, std::vector<double> Ypoints){
	std::fstream fout;
	fout.open("result.txt" + std::to_string(path.size()), std::ios::out);
	fout << "X,Y\n";
	for(long unsigned int i = 0; i < path.size(); ++i){
		fout << Xpoints[path[i]] << "," << Ypoints[path[i]] << "\n";
	}
}

int main(){
	std::vector<double> Xpoints;
	std::vector<double> Ypoints;

	//Load points

	std::fstream fin;
	fin.open("q.tsp");

	double temp;

	while(fin >> temp){
		Xpoints.push_back(temp);
		fin >> temp;
		Ypoints.push_back(temp);
	}

	std::vector<bool> inPath;

	for(long unsigned int i = 0;i < Xpoints.size(); ++i)
		inPath.push_back(false);

	
	double bestLength = -1;
	std::vector<int> bestPath;

	for(long unsigned int i = 0; i < Xpoints.size(); ++i){
		for(long unsigned int j = i + 1; j < Xpoints.size(); ++j){
			for(long unsigned int k = j + 1; k < Xpoints.size(); ++k){
				if(i != j && j != k && i != k){
					for(long unsigned int i = 0;i < Xpoints.size(); ++i)
						inPath[i] = false;
					std::vector<int> path;

					path.push_back(i);
					inPath[i] = true;
					path.push_back(j);
					inPath[j] = true;
					path.push_back(k);
					inPath[k] = true;

					while(containsFalse(inPath)){

						double max = 0;
						int point;
						int position;
						for(long unsigned int i = 0; i < Xpoints.size(); ++i){
							if(inPath[i] == false){
								double min = -1;
								int pos;
								for(long unsigned int j = 0; j < path.size() - 1; ++j){
									double value = Length(Xpoints[path[j]],Ypoints[path[j]],Xpoints[i],Ypoints[i]) + Length(Xpoints[i],Ypoints[i],Xpoints[path[j + 1]],Ypoints[path[j + 1]]) - Length(Xpoints[path[j]],Ypoints[path[j]],Xpoints[path[j + 1]],Ypoints[path[j + 1]]);
									if(value < min || min == -1){
										min = value;
										pos = j + 1;
									}
								}
								double value = Length(Xpoints[path[path.size() - 1]],Ypoints[path[path.size() - 1]],Xpoints[i],Ypoints[i]) + Length(Xpoints[i],Ypoints[i],Xpoints[path[0]],Ypoints[path[0]]) - Length(Xpoints[path[path.size() - 1]],Ypoints[path[path.size() - 1]],Xpoints[path[0]],Ypoints[path[0]]);
								if(value < min || min == -1){
									min = value;
									pos = path.size();
								}

								if(min > max){
									max = min;
									point = i;
									position = pos;
								}
							}
						}

						path.insert(path.begin() + position, point);
						inPath[point] = true;

					}
					if(PathLength(path,Xpoints,Ypoints) < bestLength || bestLength == -1){
						bestLength = PathLength(path,Xpoints,Ypoints);
						bestPath = path; 
					}	
					std::cout << bestLength << "\n";
				}
			}
		}
	}



	std::cout << bestLength;
	save(bestPath,Xpoints,Ypoints);
}
