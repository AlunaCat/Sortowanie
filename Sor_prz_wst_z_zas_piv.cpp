#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <sstream> 
#include <fstream>
#include <algorithm>


using namespace std;


template <class T>
void kopiowanie_tablicy(T tablica[], T kopia[], int n){
	for (int i=0;i<n;i++){
		kopia[i]=tablica[i];
	}
}


template <class T>
bool nie_sprawdzanie_poprawnosci(int n, T tablica[]){
	for (int i=0;i<n-1;i++){
		if(tablica[i]>tablica[i+1]){
			return true;
		}
	}
	return false;
}


template <class T>
void pokaz_tablice(int n, T tablica[]){
	for (int i=0;i<n;i++){
		cout<<tablica[i]<<endl;
	}
	cout<<"wychodze"<<endl;
}

template <class T>
void generator_liczb(int n,T tablica[],T temp){
	srand(time(NULL)+temp);	
	for(int i=0;i<n;i++){
		tablica[i]=rand();
	}
}


template <class T>
void sortowanie_wstaw_lewa(int n, T tablica[],int sortowanie[]){
	//rosn¹co
	unsigned long long l_wstawien=0, l_porownan=0;
	int j,temp;
	for(int i=1;i<n;i++){
		temp=tablica[i];
		for(j=i-1; j>=0;j--){ 
			l_porownan++;
			if(tablica[j]>temp){ 
				tablica[j+1]=tablica[j];
				l_wstawien++;
			}else break ;
		}
		tablica[j+1]=temp;
		l_wstawien++;
	}
	sortowanie[0]=l_porownan;
	sortowanie[1]=l_wstawien;
	
}


template <class T>
void babelki(int n, T tablica[], int sortowanie[]){
	int temp;
	unsigned long long l_wstawien=0, l_porownan=0;
	do{
		for(int i=0;i<n-1;i++){
			if(tablica[i]>tablica[i+1]){
				temp=tablica[i];
				tablica[i]=tablica[i+1];
				tablica[i+1]=temp;
				l_wstawien++;
			}
		l_porownan++;	
		}
		n--;
	}while(n>1);
	sortowanie[0]=l_porownan;
	sortowanie[1]=l_wstawien;
}


template <class T>
void SortNew(T tablica[],int n, int sortowanie[]){
	int por=0;
	int przest=0;
	int sr=n/2;
	T x=tablica[sr];
	int l= 0, p=n-1; //i indeks elementu z lewej strony do badania, p z prawej
	int i;
	T temp;
	while(l<p){
		while(l<=p){
				por++;
				if (tablica[l]<=x){
					temp=tablica[l];
					i=l-1;
					//por++;
					for(; i>=0;i--){ 
						por++;
						if(tablica[i]>temp){ 
							tablica[i+1]=tablica[i];
							przest++;
						}else break ;
					}
					tablica[i+1]=temp;
					przest++;
					l++;
				}else break; // trzeba przerzucic
			} 
			while(p>=l){ 
				por++;
				if(tablica[p]>=x){
					temp=tablica[p];
					i=p+1;
					for(; i<n;i++){ 
						por++;
						if(tablica[i]<temp){ 
							tablica[i-1]=tablica[i];
							przest++;
						}else break;
					}
					tablica[i-1]=temp;
					przest++;
					p--;
				}else break; //trzeba przerzucic
			}
		if(l<p){
			swap(tablica[l],tablica[p]);
			przest+=2;
        }
	}
	sortowanie[0]=por;
	sortowanie[1]=przest;
	
}


template <class T>
T wyb_piwot(T max, T min, T x,int &przest,int &por){
por++;
if(min<max){
	por++;
	if(x<max){
		por++;
		if(x<min){
			x=min;
			przest++;
		}else{
			por++;
			if(x>=max){
				x=max;
				przest++;
			}
		}
	}else{
		por++;
		if(x>=max){
			x=max;
			przest++;
		}
	}
}else{
	por++;
	if(x>=min){
		x=min;
		przest++;
	}else{
		por++;
		if(x<=max){
			x=max;
			przest++;
		}
	}
	}
return x;
}


template <class T>
void SortNew_z_wyborem(T tablica[],int n, int sortowanie[]){
	int por=0;
	int przest=0;
	T min,max,x;
	//przy du¿ej liczbie zmiennych do posortowania to wstêpne sortowanie przyœpiesza dzia³anie
	x=wyb_piwot(tablica[0],tablica[n-1],tablica[(n-1)/2],przest,por);
	int l= 0, p=n-1; //i indeks elementu z lewej strony do badania, p z prawej
	int i;
	T temp;
	while(l<p){
		while(l<=p){
				por++;
				if (tablica[l]<=x){
					temp=tablica[l];
					i=l-1;
					//por++;
					for(; i>=0;i--){ 
						por++;
						if(tablica[i]>temp){ 
							tablica[i+1]=tablica[i];
							przest++;
						}else break ;
					}
					tablica[i+1]=temp;
					przest++;
					l++;
				}else break; // trzeba przerzucic
			} 
			while(p>=l){ 
				por++;
				if(tablica[p]>=x){
					temp=tablica[p];
					i=p+1;
					for(; i<n;i++){ 
						por++;
						if(tablica[i]<temp){ 
							tablica[i-1]=tablica[i];
							przest++;
						}else break;
					}
					tablica[i-1]=temp;
					przest++;
					p--;
				}else break; //trzeba przerzucic
			}
    if(l<p){
			swap(tablica[l],tablica[p]);
			przest+=2;
          }
	}
	sortowanie[0]=por;
	sortowanie[1]=przest;

}


int main(){
	long long int suma_pod_wp, suma_wst_wp, suma_pod_bo, suma_wst_bo, suma_pod_ws, suma_wst_ws,suma_pod_wszw,suma_wst_wszw;
	srand(time(NULL));
	int sortowanie[2]={0,0};
	int max_l_elementow, dokladnosc, co_ile, od_czego_zaczac,pop_gen_liczb,temp;
	float dokladnosc_float;
	cout<<"podaj liczbe elementow od ktorej mam zaczac sprawdzanie"<<endl;
	cin>>od_czego_zaczac;
	cout<<"podaj przy jakiej ilosci danych mam skonczyc"<<endl;
	cin>>max_l_elementow;
	cout<<"co ile wartosci mam przeskakiwac"<<endl;
	cin>>co_ile;
	cout<<"ile razy mam powtorzyc test przy danej liczbie danych"<<endl;
	cin>>dokladnosc;
	fstream losowe;
	losowe.open("Wyniki.txt",ios::out);
	dokladnosc_float=dokladnosc*1.0;
	if(losowe.good()==true){
		losowe<<"liczba elementow w tablicy"<<";"<<"liczba porownan sortowanie przez wstawianie"<<";"<<"liczba wstawien sortowanie przez wstawianie"<<";"<<"liczba porownan sortowanie przez wstawianie z pivotem"<<";"<<"liczba wstawien sortowanie przez wstawianie z pivotem"<<";"<<"liczba porownan sortowanie przez wstawianie z pivotem wybieranym z 3"<<";"<<"liczba wstawien sortowanie przez wstawianie z pivotem wybieranym z 3"<<";"<<"liczba porownan sortowanie babelkowe"<<";"<<"liczba wstawien sortowanie babelkowe"<<endl;

		for (int n=od_czego_zaczac;n<=max_l_elementow;n+=co_ile){
			
			suma_pod_wp=0;
			suma_wst_wp=0;
			suma_pod_bo=0;
			suma_wst_bo=0;
			suma_pod_ws=0;
			suma_wst_ws=0;
			suma_pod_wszw=0;
			suma_wst_wszw=0;

			for(int i=0; i<dokladnosc;i++){
				int *tablica;
				pop_gen_liczb=rand()%(n-1);
				tablica=new int[n];
				int *tablica_kopia;
				tablica_kopia=new int[n];
				generator_liczb(n,tablica,temp);
				kopiowanie_tablicy(tablica, tablica_kopia, n);
				
				babelki(n,tablica_kopia,sortowanie);
				if(nie_sprawdzanie_poprawnosci(n,tablica_kopia)){
					cout<<"blad babelki"<<endl;
				}
				suma_pod_bo=suma_pod_bo+sortowanie[0];
				suma_wst_bo=suma_wst_bo+sortowanie[1];
		
	
				kopiowanie_tablicy(tablica, tablica_kopia, n);
				sortowanie_wstaw_lewa(n,tablica_kopia,sortowanie);
				if(nie_sprawdzanie_poprawnosci(n,tablica_kopia)){
					cout<<"blad sortowanie_wstaw_lewa"<<endl;
				}
				suma_pod_ws=suma_pod_ws+sortowanie[0];
				suma_wst_ws=suma_wst_ws+sortowanie[1];
				
				kopiowanie_tablicy(tablica,tablica_kopia, n);
				SortNew(tablica_kopia, n, sortowanie);
				if(nie_sprawdzanie_poprawnosci(n,tablica_kopia)){
					cout<<"blad SortNew"<<endl;
				}
				suma_pod_wp=suma_pod_wp+sortowanie[0];
				suma_wst_wp=suma_wst_wp+sortowanie[1];
				
				
				kopiowanie_tablicy(tablica,tablica_kopia, n);
				SortNew_z_wyborem(tablica_kopia, n, sortowanie);
				if(nie_sprawdzanie_poprawnosci(n,tablica_kopia)){
					cout<<"blad SortNew_z_wyborem"<<endl;
				}
				suma_pod_wszw=suma_pod_wszw+sortowanie[0];
				suma_wst_wszw=suma_wst_wszw+sortowanie[1];
				
				temp=tablica[pop_gen_liczb];
				delete [] tablica;
				delete [] tablica_kopia;
			}
		losowe<<n<<";"<<suma_pod_ws/dokladnosc_float*1.0<<";"<<suma_wst_ws/dokladnosc_float*1.0<<";"<<suma_pod_wp/dokladnosc_float*1.0<<";"<<suma_wst_wp/dokladnosc_float*1.0<<";"<<suma_pod_wszw/dokladnosc_float*1.0<<";"<<suma_wst_wszw/dokladnosc_float*1.0<<";"<<suma_pod_bo/dokladnosc_float*1.0<<";"<<suma_wst_bo/dokladnosc_float*1.0<<";"<<endl;
		}
		losowe.close();
	}	
	return 0;
}


