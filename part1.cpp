#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

double fcfs(map<string, int> processMap){
  int count=0;
  int sum=0;
  int burst=0;
  double totalWaitTime=0;
  for(auto element : processMap){
    if(count<processMap.size()-1){
      sum+=element.second;
      totalWaitTime+=sum;
      count++;
    }
  }
  return totalWaitTime/processMap.size();
}

double sjf(vector<int> burstTimes){
  int sum=0;
  double totalWaitTime=0;
  sort(burstTimes.begin(), burstTimes.end());
  for(int i=0; i<burstTimes.size()-1; i++){
    sum+=burstTimes[i];
    totalWaitTime+=sum;
  }
  return totalWaitTime/burstTimes.size();
}

double rr(vector<int> times, int timeQuantum){
  int size=times.size();
  double avg;
  double sum=0;
  double totalWaitTime=0;
  while(times.size()!=0){
    for(int i=0; i<times.size(); i++){
      if(times[i]<=timeQuantum){
        totalWaitTime+=((times.size()-1)*times[i]);
        times.erase(times.begin()+i);
        i-=1;
      }
      else{
        totalWaitTime+=(timeQuantum*(times.size()-1));
        times[i]-=timeQuantum;
      }
    }
  }
  return totalWaitTime/size;
}

int main(){
  string str, processID;
  int count=0;
  int timeQuantum=10;
  ifstream inputFile;
  map<string, int> process;
  vector<int> times;
  inputFile.open("processes.txt");
  while(inputFile >> str){
    if(count==0){
      processID=str;;
      process[processID]=0;
      count=1;
    }
    else if(count==1){
      process[processID]=stoi(str);
      times.push_back(stoi(str));
      count=0;
    }
  }
  double avgFcfs=fcfs(process);
  double avgSjf=sjf(times);
  double avgRr=rr(times, timeQuantum);
  cout << "Average wait time for FCFS: " << avgFcfs << endl;
  cout << "Average wait time for SJF: " << avgSjf << endl;
  cout << "Average wait time for RR: " << avgRr << endl;
  if(avgFcfs<avgSjf){
    if(avgFcfs<avgRr)
      cout << "FCFS was the most efficient." <<  endl;
    else{
      cout << "Rr was the most efficient." << endl;
    }
  }
  else if(avgSjf<avgRr){
    cout << "Sjf was the most efficient." << endl;
  }
  else
    cout << "Rr was the most efficient." << endl;
  inputFile.close();
  return 0;
}
