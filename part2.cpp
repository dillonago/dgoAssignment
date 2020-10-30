#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <math.h>
#include <iomanip>
#include <algorithm>

using namespace std;

void fcfs(vector<int> cylinders, int start){
  int difference=0;
  int total=0;
  double sdTotal=0;
  double sdNum, avg, sd;
  vector<int> cylindersMoved;
  for(int i=0; i<cylinders.size(); i++){
    difference=start-cylinders[i];
    cylindersMoved.push_back(abs(difference));
    total+=abs(difference);
    start=cylinders[i];
  }
  avg=((double)total/(double)cylindersMoved.size());
  for(int y=0; y<cylindersMoved.size(); y++){
    sdNum=cylindersMoved[y]-avg;
    sdTotal+=pow(sdNum, 2);
  }
  sd=sdTotal/((double)cylindersMoved.size()-1);
  sd=sqrt(sd);
  for(int p=0; p<cylindersMoved.size(); p++){
    cout << cylindersMoved[p] << endl;
  }
  cout << "total: " << total << endl;
  cout << "average: " << setprecision(4) << avg << endl;
  cout << "stdev: " << setprecision(4) << sd << endl;
}

void sstf(vector<int> cylinders, int start){
  int total=0;
  double sdTotal=0;
  double sdNum, avg, sd;
  int closestAdd=0;
  int closestDiff=abs(start-cylinders[0]);
  vector<int> cylindersMoved;
  while(cylinders.size()!=0){
    for(int i=0; i<cylinders.size(); i++){
      if(abs(start-cylinders[i])<closestDiff){
        closestAdd=i;
        closestDiff=abs(start-cylinders[i]);
      }
    }
    start=cylinders[closestAdd];
    cylinders.erase(cylinders.begin()+closestAdd);
    cylindersMoved.push_back(closestDiff);
    total+=closestDiff;
    closestDiff=abs(start-cylinders[0]);
    closestAdd=0;
  }
  avg=((double)total/(double)cylindersMoved.size());
  for(int y=0; y<cylindersMoved.size(); y++){
    sdNum=cylindersMoved[y]-avg;
    sdTotal+=pow(sdNum, 2);
  }
  sd=sdTotal/((double)cylindersMoved.size()-1);
  sd=sqrt(sd);
  for(int p=0; p<cylindersMoved.size(); p++){
    cout << cylindersMoved[p] << endl;
  }
  cout << "total: " << total << endl;
  cout << "average: " << setprecision(4) << avg << endl;
  cout << "stdev: " << setprecision(4) << sd << endl;
}

void scan(vector<int> cylinders, int start){
  int address;
  int total=0;
  int difference=0;
  double avg, sd, sdNum;
  double sdTotal=0;
  vector<int> cylindersMoved;
  sort(cylinders.begin(), cylinders.end());
  for(int i=0; i<cylinders.size(); i++){
    if(start<=cylinders[i]){
      address=i;
      break;
    }
  }
  for(int x=address; x<cylinders.size(); x++){
    difference=abs(start-cylinders[x]);
    total+=difference;
    cylindersMoved.push_back(difference);
    start=cylinders[x];
  }
  for(int y=address-1; y>=0; y--){
    difference=abs(start-cylinders[y]);
    total+=difference;
    cylindersMoved.push_back(difference);
    start=cylinders[y];
  }
  avg=((double)total/(double)cylindersMoved.size());
  for(int z=0; z<cylindersMoved.size(); z++){
    sdNum=cylindersMoved[z]-avg;
    sdTotal+=pow(sdNum, 2);
  }
  sd=sdTotal/((double)cylindersMoved.size()-1);
  sd=sqrt(sd);
  for(int q=0; q<cylindersMoved.size(); q++){
    cout << cylindersMoved[q] << endl;
  }
  cout << "total: " << total << endl;
  cout << "average: " << setprecision(4) << avg << endl;
  cout << "stdev: " << setprecision(4) << sd << endl;


}

int main(){
  string str, newStr;
  int headStart;
  vector<int> cylinders;
  ifstream inputFile;
  inputFile.open("nums.txt");
  getline(inputFile, str, '\n');
  istringstream ss(str);
  while(getline(ss, newStr, ',')){
    cylinders.push_back(stoi(newStr));
  }
  cout << "Enter the head start: ";
  cin >> headStart;
  cout << "FCFS: " << endl;
  fcfs(cylinders, headStart);
  cout << "SSTF: " << endl;
  sstf(cylinders, headStart);
  cout << "SCAN: " << endl;
  scan(cylinders, headStart);
  inputFile.close();
  return 0;
}
