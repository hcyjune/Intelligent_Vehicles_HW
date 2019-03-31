#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <ctime>
using namespace std;
struct message{
	int p,t,p_bf,p_af;
	float c;
};
bool comp_p(struct message m1,struct message m2){
	return m1.p < m2.p;
}
bool comp_p_bf(struct message m1,struct message m2){
	return m1.p_bf < m2.p_bf;
}
bool comp_p_af(struct message m1,struct message m2){
	return m1.p_af < m2.p_af;
}
float worstRT(struct message x[],int n,float tau){
	float max=0.0;
	float b[n];//longest blocking time
	for (int i=n-1;i>=0;i--){
		if (x[i].c>max)
			max=x[i].c;
		b[i]=max;
	}
	float q,rhs,r;
	int ceiling,schedulable=0;
	float error=0,sum=0;
	for (int i=0;i<n;i++){
		q=b[i];
		while(1){
			rhs=b[i];
			for (int j=0;j<i;j++){
				ceiling=ceil((q+tau)/x[j].t);
				rhs+=ceiling*x[j].c;
			}
			if (rhs+x[i].c>x[i].t){
				schedulable=1;
				break;//not schedulable
			} 
			else if (abs(q-rhs)<=error){
				r=q+x[i].c;
				sum+=r;
				break;	
			}
			else{
				q=rhs;
			}
		}
		if (schedulable==1){
			sum=-1;
			break;
		}
	}
	return sum;	
}
int main(){
	int n;
	float tau;
	cin>>n>>tau;
	struct message m[n],opt[n];
	for (int i=0;i<n;i++){
		cin>>m[i].p>>m[i].c>>m[i].t;
		m[i].p_bf=m[i].p;
		m[i].p_af=m[i].p;
		opt[i].p=m[i].p;
		opt[i].p_af=m[i].p;
	}
	float cost=worstRT(m,n,tau);
	float cost_min=cost,T=10000;
	int c=3;
	while (T>1){
		sort(m,m+n,comp_p_bf);		
		int a=0;
		for (int i=0;i<ceil(n/(float)c);i++){
			int b=a+c;
			while (b>n){
				b--;
			}
			random_shuffle(m+a,m+b);
			a+=c;
		}
		for (int i=0;i<n;i++){
			m[i].p_af=i;
		}
		float cost_new=worstRT(m,n,tau);
		//cout<<cost_new<<endl;
		if (cost_new!=-1){
			if (cost_new<cost_min){
				cost_min=cost_new;
				for (int i=0;i<n;i++){
					opt[i].p=m[i].p;
					opt[i].p_af=m[i].p_af;
				}
			}
			float delta=cost_new-cost;
			if (delta<=0){
				for (int i=0;i<n;i++){
					m[i].p_bf=m[i].p_af;
					c=4;
				}
			}
			else if (delta>0){
				srand(time(NULL));
				float y=(float)rand()/(RAND_MAX+1.0);
				if (y<exp(-delta/T)){
					for (int i=0;i<n;i++){
						m[i].p_bf=m[i].p_af;
						c=4;
					}
				}
			}
			cost=cost_new;
			T=0.999*T;
		}
	}
	sort(opt,opt+n,comp_p);
	for (int i=0;i<n;i++){
		cout<<opt[i].p_af<<endl;
	}
	cout<<"cost="<<cost_min<<endl;
	return 0;
} 
