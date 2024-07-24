#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>

using namespace std;

#define VERSION "1.0.0"

bool is_even(int n){
	return n%2==0;
}
bool is_prime(int n){
	if(n<=1){return false;}
	if(n<=3){return true;}
	if(n%2==0||n%3==0){return false;}
	for(int i=5;i*i<=n;i+=6){
		if(n%i==0||n%(i+2)==0){return false;}
	}
	return true;
}
vector<int> get_primes(int n){
	vector<int> primes;
	for(int i=2;i<=n;i++){
		if(is_prime(i)){primes.push_back(i);}
	}
	return primes;
}
int sci_to_int(string s){
	if(s.find('e')==string::npos){return stoi(s);}
	int n=0;
	int e=0;
	int i=0;
	while(s[i]!='e'){
		n=n*10+(s[i]-'0');
		i++;
	}
	i++;
	while(i<s.size()){
		e=e*10+(s[i]-'0');
		i++;
	}
	return n*pow(10,e);
}
int get_random(int min,int max){
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(min,max);
	return dis(gen);
}
string get_num_fmt(const string str){
	string ans="";
	int count=0;
	for(int a=str.length()-1;a>=0;a--){
		if(count==3){
			ans=","+ans;
			count=0;
		}
		ans=str[a]+ans;
		count++;
	}
	return ans;
}

int main(int argc,char** argv){
	int n=get_random(4,1000);
	for(int i=1;i<argc;i++){
		if((string)argv[i]=="-h"||(string)argv[i]=="--help"){
			cout<<"Goldbach's Conjecture: Every positive even integer greater than 2 can be written as the sum of two primes."<<endl;
			cout<<endl;
			cout<<"Usage: "<<argv[0]<<" [options]"<<endl;
			cout<<"Options:"<<endl;
			cout<<"-h, --help:\t\tDisplays the help menu."<<endl;
			cout<<"--version:\t\tDisplays the version number."<<endl;
			cout<<"-n <number>:\t\tEnter the number to be checked."<<endl;
			cout<<endl<<"NOTE: The number can be written in scientific notation."<<endl;
			cout<<"\tExample: ./a.out -n 1e3"<<endl;
			cout<<"\tFun fact: The conjecture has been shown to hold for all integers less than 4e18"<<endl;
			return 0;
		}
		else if((string)argv[i]=="--version"){
			cout<<VERSION<<endl;
			return 0;
		}
		else if((string)argv[i]=="-n"){
			i++;
			if(i>argc){
				cout<<"Error: Missing number"<<endl;
				return 1;
			}
			n=sci_to_int(argv[i]);
			if(n<4||!is_even(n)){
				cout<<"Error: Invalid number"<<endl;
				cout<<"The number must be an even integer greater than 2 so n≥4."<<endl;
				return 1;
			}
		}
	}
	vector<int> primes=get_primes(n);
	for(int i=0;i<primes.size();i++){
		int first_num=primes[i];
		for(int j=0;j<primes.size();j++){
			int second_num=primes[j];
			if(first_num+second_num==n){
				cout<<get_num_fmt(to_string(n))<<" = "<<get_num_fmt(to_string(first_num))<<" + "<<get_num_fmt(to_string(second_num))<<endl;
				return 0;
			}
		}
	}
	return 0;
}