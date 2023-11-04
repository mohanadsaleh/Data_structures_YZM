#include <stdio.h>
#include <stdlib.h>
#define stack_size 20

// YZM LAB HAFTA 5 

/*-----------------------------------------------------------------------------------------------
Bir txt dosya i�erisindeki kodda var olan parantez hatalarini tespit edecek programi stack 
array implementation ile yaziniz.
Metin dosyasinda yazili kodu a�ilacak, dosya g�stericisi tek tek okuyacak ve bir staga 
aktaracaktir yalnizca parantez hata kontrol� yapilacaktir.
--------------------------------------------------------------------------------------------------- */
typedef struct{
	
	char parantez[stack_size]; //Stack yapisi
	int top;
}stack;

void resting( stack *stk){ //initialize  fonksiyonu
	stk->top=-1;
}

void push(stack *stk , char pa){  // stack�e ekleme yapan fonksiyon
	
	if(stk->top==stack_size-1){ //Eger top de�i�keni dizinin son indisini g�steriyorsa, o zaman dizi doludur.
		printf("stack full !\n");
		return 0;
	
	} else{
		stk->parantez[++stk->top]=pa;
		
	}

}

char pop(stack *stk){//Stack�lerden Eleman �ikarma Islemi 
	
	if(stk->top==-1){// stack bos kontrolu
		printf("Stack empty !\n");
	return -1;
	}
	
	else{
		return stk->parantez[stk->top--];
	}
}

int main(){
	char key;// parantez tutmak icin
	stack stk;
	resting(&stk);
	FILE *fptr; //file ponter
	if((fptr = fopen("C:\\Users\\Mohannad\\Desktop\\parantez.txt","r")) == NULL){//Dosyanin yolu ve adi "r" okumak icin
		printf("dosya bulunmaz !\n");
		return NULL;
	}
	else{
		while(!feof(fptr)){ //Dosya isaret�isi dosyanin sonunda olup olmadigi kontrol etmek i�in 
			key=getc(fptr);
			
			switch(key){
				
				case '(':
					push(&stk,key);
					break;
					
				case ')' : /*Se�im islemi ')' karakterine geldiginde,
				 yigindaki en �stteki parantez karakterinin '(' olmasi gerekir; aksi halde yanlis bir parantez olacak."*/
					if(pop(&stk)=='(')
					continue;
					else{
						printf("\n\n Error for () parentheses !!\n");
						exit(1);
					}
					break;
				
				case '{':
					push(&stk,key);
					break;
				case '}':
					if(pop(&stk)=='{ ')
					continue ;
					else{
						printf("\n\n Error for {} parentheses !!\n");
						exit(1);
					}
					break;
				case '[' : 
						push(&stk , key);
						break;
				case ']': 
				if(pop(&stk)=='[')
				continue;
				else{
						printf("\n\n Error for [] parentheses !!\n");
						exit(1);
				}
				break;
				default : 
				break;
			}
			
		}
	}
	
	
	return 0;
}
