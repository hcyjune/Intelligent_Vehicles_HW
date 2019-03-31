#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
int main(){
	int n;
	float tau;
	cin>>n>>tau;
	int p[n],t[n];
	float c[n];
	for (int i=0;i<n;i++){
		cin>>p[i]>>c[i]>>t[i];
	}
	float max=0.0;
	float b[n];//longest blocking time
	for (int i=n-1;i>=0;i--){
		if (c[i]>max)
			max=c[i];
		b[i]=max;
	}
	float q,rhs,r;
	int ceiling;
	float error=0;
	for (int i=0;i<n;i++){
		q=b[i];
		while(1){
			rhs=b[i];
			for (int j=0;j<i;j++){
				ceiling=ceil((q+tau)/t[j]);
				rhs+=ceiling*c[j];
			}
			if (rhs+c[i]>t[i]){
				break;//not schedulable
			} 
			else if (abs(q-rhs)<=error){
				r=q+c[i];
				cout<<r<<endl;
				break;	
			}
			else{
				q=rhs;
			}
		}
	}
	return 0;
} 
