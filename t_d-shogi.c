#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "MH.h"

struct kyokumen
{
	int k_moti_1[4];
	int k_moti_2[4];
	int k_ban[6][5];
	int kaisu;
};

struct bestpv
{
	char sasite[500];
};

struct hash
{
	int h_moti_1[4];
	int h_moti_2[4];
	int h_ban[6][5];
	int deep;
	int low;
	int upp;
	char h_te[4];
};

void input(char *te, int tesu);
void output(int ban[6][5], int moti_1[], int moti_2[]);
int check(int ban[6][5], char *te, int tesu, int moti_1[], int moti_2[]);
int c_check(int ban[6][5], char *te, int tesu, int moti_1[], int moti_2[]);
int sennitite(struct kyokumen banmen[], int ban[6][5], int moti_1[], int moti_2[]);
int move(int ban[6][5], char *te, int tesu, int moti_1[], int moti_2[]);
void back(int ban[6][5], char *te, int tesu, int moti_1[], int moti_2[], int koma);
int result(int ban[10][10]);
void think(int ban[6][5], struct kyokumen banmen[], char *te, int tesu, int moti_1[], int moti_2[], int l);
void think_1(int ban[6][5], char *te, int tesu, int moti_1[], int moti_2[]);
void think_2(int ban[6][5], struct kyokumen banmen[], char *te, int tesu, int moti_1[], int moti_2[], int depth);
void think_3(int ban[6][5], struct kyokumen banmen[], char *te, int tesu, int moti_1[], int moti_2[]);
int NegaMax(int ban[6][5], struct kyokumen banmen[], struct bestpv pv[], struct hash tikan[], char *str, int tesu, int moti_1[], int moti_2[], int deep, int depth, int *node, int al, int be);
int hashti(int ban[6][5], int moti_1[], int moti_2[], int tesu);
void m_m(void);
void m_c(int c);
int c_c(int c_1, int c_2);

int main(void)
{
	int n, i, b, w, c[2];
	double start, end;
	char str[100];

	init_genrand((unsigned)time(NULL));

	do{
		do{
			printf("1. l VS l  2. l VS COM  3. COM VS COM\n");
			printf("”Ô†‚ğ“ü—Í: ");
			scanf("%s", &str);
		}while(strlen(str)!=1||atoi(str)<1||3<atoi(str));
		
		n=atoi(str);
		
		switch(n){
		    case 1:
				m_m();
				break;
			case 2:
				do{
					printf("COM‚ÌƒŒƒxƒ‹(1-9)‚ğ“ü—Í: ");
					scanf("%d", &c[0]);
				}while(c[0]<1||9<c[0]);
				m_c(c[0]);
				break;
			case 3:
				do{
					printf("COM_1‚ÌƒŒƒxƒ‹(1-9)‚ğ“ü—Í: ");
					scanf("%d", &c[0]);
				}while(c[0]<1||9<c[0]);
				do{
					printf("COM_2‚ÌƒŒƒxƒ‹(1-9)‚ğ“ü—Í: ");
					scanf("%d", &c[1]);
				}while(c[1]<1||9<c[1]);
					b=0;
					w=0;
				start=clock();
				for(i=0;i<1;i++){
					n=c_c(c[0], c[1]);
					switch(n){
						case 1:
							b++;
							break;
						case 2:
							w++;
							break;
					}
				}
				for(i=0;i<1;i++){
					n=c_c(c[1], c[0]);
					switch(n){
						case 1:
							w++;
							break;
						case 2:
							b++;
							break;
					}
				}
				end=clock();
				printf("COM_1: %dŸ\n", b);
				printf("COM_2: %dŸ\n", w);
				printf("‘vlŠÔ: %f\n", (end-start)/CLOCKS_PER_SEC);
		}

		do{
			printf("‚à‚¤ˆê“x‚â‚è‚Ü‚·‚©H (y/n): ");
			str[0]=getche();
			printf("\n");
		}while(str[0]!='y'&&str[0]!='n');
	}while(str[0]=='y');

	return 0;
}

void input(char *m_te, int tesu)
{
	if(tesu%2==1){
		printf("æè”Ô(•)Aè‚ğ“ü—Í‚µ‚Ä‰º‚³‚¢B: ");
		scanf("%s", m_te);
		if(m_te[0]=='0'){
			switch(m_te[1]){
				case 'h':
					m_te[1]=1;
					break;
				case 'n':
					m_te[1]=2;
					break;
				case 'z':
					m_te[1]=3;
					break;
				case 'k':
					m_te[1]=4;
					break;
				case 'r':
					m_te[1]=5;
					break;
			}
		}

	}
	else{
		printf("Œãè”Ô(”’)Aè‚ğ“ü—Í‚µ‚Ä‰º‚³‚¢B: ");
		scanf("%s", m_te);
		if(m_te[0]=='0'){
			switch(m_te[1]){
				case 'h':
					m_te[1]=6;
					break;
				case 'n':
					m_te[1]=7;
					break;
				case 'z':
					m_te[1]=8;
					break;
				case 'k':
					m_te[1]=9;
					break;
				case 'r':
					m_te[1]=10;
					break;
			}
		}
	}
}

void output(int ban[6][5], int moti_1[], int moti_2[])
{
	int i, j;

	printf("‚¿‹î: ");
	switch(moti_2[0]){
		case 0:
			break;
		case 1:
			printf("ƒq");
			break;
		case 2:
			printf("ƒqƒq");
			break;
	}
	switch(moti_2[1]){
		case 0:
			break;
		case 1:
			printf("ƒ]");
			break;
		case 2:
			printf("ƒ]ƒ]");
			break;
	}
	switch(moti_2[2]){
		case 0:
			break;
		case 1:
			printf("ƒL");
			break;
		case 2:
			printf("ƒLƒL");
			break;
	}
	printf("\n\n");

	printf("‚‚‚‚ƒ \n");
	for(i=1;i<5;i++){
		for(j=1;j<4;j++){
			switch(ban[i][j]){
			    case 0:
					printf("|");
					break;
				case 1:
					printf("‚Ğ");
					break;
				case 2:
					printf("‚É");
					break;
				case 3:
					printf("‚¼");
					break;
				case 4:
					printf("‚«");
					break;
				case 5:
					printf("‚ç");
					break;
				case 6:
					printf("ƒq");
					break;
				case 7:
					printf("ƒj");
					break;
				case 8:
					printf("ƒ]");
					break;
				case 9:
					printf("ƒL");
					break;
				case 10:
					printf("ƒ‰");
					break;
			}
		}
		printf("%d\n", i);
	}
	printf("\n");

	printf("‚¿‹î: ");
	switch(moti_1[0]){
		case 0:
			break;
		case 1:
			printf("‚Ğ");
			break;
		case 2:
			printf("‚Ğ‚Ğ");
			break;
	}
	switch(moti_1[1]){
		case 0:
			break;
		case 1:
			printf("‚¼");
			break;
		case 2:
			printf("‚¼‚¼");
			break;
	}
	switch(moti_1[2]){
		case 0:
			break;
		case 1:
			printf("‚«");
			break;
		case 2:
			printf("‚«‚«");
			break;
	}
	printf("\n\n");
}

int check(int ban[6][5], char *te, int tesu, int moti_1[], int moti_2[])
{
	int i, j, k=-1, l=-1, m=0, n=-1, koma;
	char x[1000]={""}, y[1000]={""};

	strcpy(te, x);

	tesu=tesu%2;

	if(tesu==0){

		for(i='1';i<'5';i++){
			for(j=1;j<4;j++){
				if(ban[i-'0'][j]/6==1){
					if(ban[i-'0'][j]==6){
						if(ban[i-'0'+1][j]!=-1&&ban[i-'0'+1][j]/6!=1){
							x[m]='a'+j-1;
							x[m+1]=i;
							x[m+2]='a'+j-1;
							x[m+3]=i+1;
							m+=4;
						}
					}
					else{
						if(ban[i-'0'][j]==7){
							if(ban[i-'0'+1][j]!=-1&&ban[i-'0'+1][j]/6!=1){
								x[m]='a'+j-1;
								x[m+1]=i;
								x[m+2]='a'+j-1;
								x[m+3]=i+1;
								m+=4;
							}
							if(ban[i-'0'+1][j-1]!=-1&&ban[i-'0'+1][j-1]/6!=1){
								x[m]='a'+j-1;
								x[m+1]=i;
								x[m+2]='a'+j-2;
								x[m+3]=i+1;
								m+=4;
							}
							if(ban[i-'0'][j-1]!=-1&&ban[i-'0'][j-1]/6!=1){
								x[m]='a'+j-1;
								x[m+1]=i;
								x[m+2]='a'+j-2;
								x[m+3]=i;
								m+=4;
							}
							if(ban[i-'0'-1][j]!=-1&&ban[i-'0'-1][j]/6!=1){
								x[m]='a'+j-1;
								x[m+1]=i;
								x[m+2]='a'+j-1;
								x[m+3]=i-1;
								m+=4;
							}
							if(ban[i-'0'][j+1]!=-1&&ban[i-'0'][j+1]/6!=1){
								x[m]='a'+j-1;
								x[m+1]=i;
								x[m+2]='a'+j;
								x[m+3]=i;
								m+=4;
							}
							if(ban[i-'0'+1][j+1]!=-1&&ban[i-'0'+1][j+1]/6!=1){
								x[m]='a'+j-1;
								x[m+1]=i;
								x[m+2]='a'+j;
								x[m+3]=i+1;
								m+=4;
							}
						}
						else{
							if(ban[i-'0'][j]==8){
								if(ban[i-'0'+1][j-1]!=-1&&ban[i-'0'+1][j-1]/6!=1){
									x[m]='a'+j-1;
									x[m+1]=i;
									x[m+2]='a'+j-2;
									x[m+3]=i+1;
									m+=4;
								}
								if(ban[i-'0'-1][j-1]!=-1&&ban[i-'0'-1][j-1]/6!=1){
									x[m]='a'+j-1;
									x[m+1]=i;
									x[m+2]='a'+j-2;
									x[m+3]=i-1;
									m+=4;
								}
								if(ban[i-'0'-1][j+1]!=-1&&ban[i-'0'-1][j+1]/6!=1){
									x[m]='a'+j-1;
									x[m+1]=i;
									x[m+2]='a'+j;
									x[m+3]=i-1;
									m+=4;
								}
								if(ban[i-'0'+1][j+1]!=-1&&ban[i-'0'+1][j+1]/6!=1){
									x[m]='a'+j-1;
									x[m+1]=i;
									x[m+2]='a'+j;
									x[m+3]=i+1;
									m+=4;
								}
							}
							else{
								if(ban[i-'0'][j]==9){
									if(ban[i-'0'+1][j]!=-1&&ban[i-'0'+1][j]/6!=1){
										x[m]='a'+j-1;
										x[m+1]=i;
										x[m+2]='a'+j-1;
										x[m+3]=i+1;
										m+=4;
									}
									if(ban[i-'0'][j-1]!=-1&&ban[i-'0'][j-1]/6!=1){
										x[m]='a'+j-1;
										x[m+1]=i;
										x[m+2]='a'+j-2;
										x[m+3]=i;
										m+=4;
									}
									if(ban[i-'0'-1][j]!=-1&&ban[i-'0'-1][j]/6!=1){
										x[m]='a'+j-1;
										x[m+1]=i;
										x[m+2]='a'+j-1;
										x[m+3]=i-1;
										m+=4;
									}
									if(ban[i-'0'][j+1]!=-1&&ban[i-'0'][j+1]/6!=1){
										x[m]='a'+j-1;
										x[m+1]=i;
										x[m+2]='a'+j;
										x[m+3]=i;
										m+=4;
									}
								}
								else{
									if(ban[i-'0'][j]==10){
										if(ban[i-'0'+1][j]!=-1&&ban[i-'0'+1][j]/6!=1){
											x[m]='a'+j-1;
											x[m+1]=i;
											x[m+2]='a'+j-1;
											x[m+3]=i+1;
											m+=4;
										}
										if(ban[i-'0'+1][j-1]!=-1&&ban[i-'0'+1][j-1]/6!=1){
											x[m]='a'+j-1;
											x[m+1]=i;
											x[m+2]='a'+j-2;
											x[m+3]=i+1;
											m+=4;
										}
										if(ban[i-'0'][j-1]!=-1&&ban[i-'0'][j-1]/6!=1){
											x[m]='a'+j-1;
											x[m+1]=i;
											x[m+2]='a'+j-2;
											x[m+3]=i;
											m+=4;
										}
										if(ban[i-'0'-1][j-1]!=-1&&ban[i-'0'-1][j-1]/6!=1){
											x[m]='a'+j-1;
											x[m+1]=i;
											x[m+2]='a'+j-2;
											x[m+3]=i-1;
											m+=4;
										}
										if(ban[i-'0'-1][j]!=-1&&ban[i-'0'-1][j]/6!=1){
											x[m]='a'+j-1;
											x[m+1]=i;
											x[m+2]='a'+j-1;
											x[m+3]=i-1;
											m+=4;
										}
										if(ban[i-'0'-1][j+1]!=-1&&ban[i-'0'-1][j+1]/6!=1){
											x[m]='a'+j-1;
											x[m+1]=i;
											x[m+2]='a'+j;
											x[m+3]=i-1;
											m+=4;
										}
										if(ban[i-'0'][j+1]!=-1&&ban[i-'0'][j+1]/6!=1){
											x[m]='a'+j-1;
											x[m+1]=i;
											x[m+2]='a'+j;
								 			x[m+3]=i;
											m+=4;
										}
										if(ban[i-'0'+1][j+1]!=-1&&ban[i-'0'+1][j+1]/6!=1){
											x[m]='a'+j-1;
											x[m+1]=i;
											x[m+2]='a'+j;
											x[m+3]=i+1;
											m+=4;
										}
									}
								}
							}
						}
					}
				}
			}
		}

		for(l=0;l<3;l++){
			if(moti_2[l]>0){
				switch(l){
					case 0:
						koma=6;
						break;
					case 1:
						koma=8;
						break;
					case 2:
						koma=9;
						break;
				}
				for(i='1';i<'5';i++){
					for(j=1;j<4;j++){
						if(ban[i-'0'][j]==0){
							x[m]='0';
							x[m+1]=koma;
							x[m+2]='a'+j-1;
							x[m+3]=i;
							m+=4;
						}
					}
				}
			}
		}
	}

	if(tesu==1){
		for(i='1';i<'5';i++){
			for(j=1;j<4;j++){
				if(ban[i-'0'][j]!=0){
					if(ban[i-'0'][j]/6==0){
						if(ban[i-'0'][j]==1){
							if(ban[i-'0'-1][j]==0||ban[i-'0'-1][j]>5){
								x[m]='a'+j-1;
								x[m+1]=i;
								x[m+2]='a'+j-1;
								x[m+3]=i-1;
								m+=4;
							}
						}
						else{
							if(ban[i-'0'][j]==2){
								if(ban[i-'0'-1][j]==0||ban[i-'0'-1][j]>5){
									x[m]='a'+j-1;
									x[m+1]=i;
									x[m+2]='a'+j-1;
									x[m+3]=i-1;
									m+=4;
								}
								if(ban[i-'0'-1][j+1]==0||ban[i-'0'-1][j+1]>5){
									x[m]='a'+j-1;
									x[m+1]=i;
									x[m+2]='a'+j;
									x[m+3]=i-1;
									m+=4;
								}
								if(ban[i-'0'][j+1]==0||ban[i-'0'][j+1]>5){
									x[m]='a'+j-1;
									x[m+1]=i;
									x[m+2]='a'+j;
									x[m+3]=i;
									m+=4;
								}
								if(ban[i-'0'+1][j]==0||ban[i-'0'+1][j]>5){
									x[m]='a'+j-1;
									x[m+1]=i;
									x[m+2]='a'+j-1;
									x[m+3]=i+1;
									m+=4;
								}
								if(ban[i-'0'][j-1]==0||ban[i-'0'][j-1]>5){
									x[m]='a'+j-1;
									x[m+1]=i;
									x[m+2]='a'+j-2;
									x[m+3]=i;
									m+=4;
								}
								if(ban[i-'0'-1][j-1]==0||ban[i-'0'-1][j-1]>5){
									x[m]='a'+j-1;
									x[m+1]=i;
									x[m+2]='a'+j-2;
									x[m+3]=i-1;
									m+=4;
								}
							}
							else{
								if(ban[i-'0'][j]==3){
									if(ban[i-'0'+1][j-1]==0||ban[i-'0'+1][j-1]>5){
										x[m]='a'+j-1;
										x[m+1]=i;
										x[m+2]='a'+j-2;
										x[m+3]=i+1;
										m+=4;
									}
									if(ban[i-'0'-1][j-1]==0||ban[i-'0'-1][j-1]>5){
										x[m]='a'+j-1;
										x[m+1]=i;
										x[m+2]='a'+j-2;
										x[m+3]=i-1;
										m+=4;
									}
									if(ban[i-'0'-1][j+1]==0||ban[i-'0'-1][j+1]>5){
										x[m]='a'+j-1;
										x[m+1]=i;
										x[m+2]='a'+j;
										x[m+3]=i-1;
										m+=4;
									}
									if(ban[i-'0'+1][j+1]==0||ban[i-'0'+1][j+1]>5){
										x[m]='a'+j-1;
										x[m+1]=i;
										x[m+2]='a'+j;
										x[m+3]=i+1;
										m+=4;
									}
								}
								else{
									if(ban[i-'0'][j]==4){
										if(ban[i-'0'+1][j]==0||ban[i-'0'+1][j]>5){
											x[m]='a'+j-1;
											x[m+1]=i;
											x[m+2]='a'+j-1;
											x[m+3]=i+1;
											m+=4;
										}
										if(ban[i-'0'][j-1]==0||ban[i-'0'][j-1]>5){
											x[m]='a'+j-1;
											x[m+1]=i;
											x[m+2]='a'+j-2;
											x[m+3]=i;
											m+=4;
										}
										if(ban[i-'0'-1][j]==0||ban[i-'0'-1][j]>5){
											x[m]='a'+j-1;
											x[m+1]=i;
											x[m+2]='a'+j-1;
											x[m+3]=i-1;
											m+=4;
										}
										if(ban[i-'0'][j+1]==0||ban[i-'0'][j+1]>5){
											x[m]='a'+j-1;
											x[m+1]=i;
											x[m+2]='a'+j;
											x[m+3]=i;
											m+=4;
										}
									}
									else{
										if(ban[i-'0'][j]==5){
											if(ban[i-'0'+1][j]==0||ban[i-'0'+1][j]>5){
												x[m]='a'+j-1;
												x[m+1]=i;
												x[m+2]='a'+j-1;
												x[m+3]=i+1;
												m+=4;
											}
											if(ban[i-'0'+1][j-1]==0||ban[i-'0'+1][j-1]>5){
												x[m]='a'+j-1;
												x[m+1]=i;
												x[m+2]='a'+j-2;
												x[m+3]=i+1;
												m+=4;
											}
											if(ban[i-'0'][j-1]==0||ban[i-'0'][j-1]>5){
												x[m]='a'+j-1;
												x[m+1]=i;
												x[m+2]='a'+j-2;
												x[m+3]=i;
												m+=4;
											}
											if(ban[i-'0'-1][j-1]==0||ban[i-'0'-1][j-1]>5){
												x[m]='a'+j-1;
												x[m+1]=i;
												x[m+2]='a'+j-2;
												x[m+3]=i-1;
												m+=4;
											}
											if(ban[i-'0'-1][j]==0||ban[i-'0'-1][j]>5){
												x[m]='a'+j-1;
												x[m+1]=i;
												x[m+2]='a'+j-1;
												x[m+3]=i-1;
												m+=4;
											}
											if(ban[i-'0'-1][j+1]==0||ban[i-'0'-1][j+1]>5){
												x[m]='a'+j-1;
												x[m+1]=i;
												x[m+2]='a'+j;
												x[m+3]=i-1;
												m+=4;
											}
											if(ban[i-'0'][j+1]==0||ban[i-'0'][j+1]>5){
												x[m]='a'+j-1;
												x[m+1]=i;
												x[m+2]='a'+j;
									 			x[m+3]=i;
												m+=4;
											}
											if(ban[i-'0'+1][j+1]==0||ban[i-'0'+1][j+1]>5){
												x[m]='a'+j-1;
												x[m+1]=i;
												x[m+2]='a'+j;
												x[m+3]=i+1;
												m+=4;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}

		for(l=0;l<3;l++){
			if(moti_1[l]>0){
				switch(l){
					case 0:
						koma=1;
						break;
					case 1:
						koma=3;
						break;
					case 2:
						koma=4;
						break;
				}
				for(i='1';i<'5';i++){
					for(j=1;j<4;j++){
						if(ban[i-'0'][j]==0){
							x[m]='0';
							x[m+1]=koma;
							x[m+2]='a'+j-1;
							x[m+3]=i;
							m+=4;
						}
					}
				}
			}
		}

	}
	l=-1;
	for(i=1;i<5;i++){
		for(j='a';j<'d';j++){
			if(ban[i][j-'a'+1]==5){
				if(i==1){
					m=2;
					do{
						if(x[m]==j&&(x[m+1]-'0')==i){
							n=0;
						}
						m+=4;
					}while(strlen(x)>m);
					if(n==-1){
						return 1;
					}
				}
				k=0;
			}
			if(ban[i][j-'a'+1]==10){
				if(i==4){
					m=2;
					do{
						if(x[m]==j&&(x[m+1]-'0')==i){
							n=0;
						}
						m+=4;
					}while(strlen(x)>m);
					if(n==-1){
						return 2;
					}
				}
				l=0;
			}
		}
	}
	if(k==-1){
		return 2;
	}
	if(l==-1){
		return 1;
	}
	
	m=1;
	k=0;
	n=0;
	if(tesu==0){
		for(i=0;x[m]!=0;i++){
			if(ban[x[m+2]-'0'][x[m+1]-'a'+1]/5==0&&ban[x[m+2]-'0'][x[m+1]-'a'+1]!=0){
				y[k]=x[m-1];
				y[k+1]=x[m];
				y[k+2]=x[m+1];
				y[k+3]=x[m+2];
				if(ban[x[m+2]-'0'][x[m+1]-'a'+1]==5){
					if(n==0){
						strcpy(te, y);
						n++;
					}
					else{
						strcat(te, y);
					}
				}
				j=m;
				k+=4;
				for(l=j+2;x[j-1]!=0;l++){
					x[j-1]=x[j+3];
					j++;
				}
			}
			m+=4;
		}
	}
	else{
		for(i=0;x[m]!=0;i++){
			if(ban[x[m+2]-'0'][x[m+1]-'a'+1]/6==1){
				y[k]=x[m-1];
				y[k+1]=x[m];
				y[k+2]=x[m+1];
				y[k+3]=x[m+2];
				if(ban[x[m+2]-'0'][x[m+1]-'a'+1]==10){
					if(n==0){
						strcpy(te, y);
						n++;
					}
					else{
						strcat(te, y);
					}
				}
				j=m;
				k+=4;
				for(l=j+2;x[j-1]!=0;l++){
					x[j-1]=x[j+3];
					j++;
				}
			}
			m+=4;
		}
	}
	
	strcat(y, x);
	strcpy(te, y);

	return 0;
}

int c_check(int ban[6][5], char *te, int tesu, int moti_1[], int moti_2[])
{
	int i, j, k=-1, l=-1, m=0, n=-1, i_moti_1[4], i_moti_2[4], koma;
	int t_ban[6][5];
	char x[1000]={""}, y[1000]={""}, t_te[1000]={""};

	strcpy(te, x);

	tesu=tesu%2;

	if(tesu==0){

		for(i='1';i<'5';i++){
			for(j=1;j<4;j++){
				if(ban[i-'0'][j]/6==1){
					if(ban[i-'0'][j]==6){
						if(ban[i-'0'+1][j]!=-1&&ban[i-'0'+1][j]/6!=1){
							x[m]='a'+j-1;
							x[m+1]=i;
							x[m+2]='a'+j-1;
							x[m+3]=i+1;
							m+=4;
						}
					}
					else{
						if(ban[i-'0'][j]==7){
							if(ban[i-'0'+1][j]!=-1&&ban[i-'0'+1][j]/6!=1){
								x[m]='a'+j-1;
								x[m+1]=i;
								x[m+2]='a'+j-1;
								x[m+3]=i+1;
								m+=4;
							}
							if(ban[i-'0'+1][j-1]!=-1&&ban[i-'0'+1][j-1]/6!=1){
								x[m]='a'+j-1;
								x[m+1]=i;
								x[m+2]='a'+j-2;
								x[m+3]=i+1;
								m+=4;
							}
							if(ban[i-'0'][j-1]!=-1&&ban[i-'0'][j-1]/6!=1){
								x[m]='a'+j-1;
								x[m+1]=i;
								x[m+2]='a'+j-2;
								x[m+3]=i;
								m+=4;
							}
							if(ban[i-'0'-1][j]!=-1&&ban[i-'0'-1][j]/6!=1){
								x[m]='a'+j-1;
								x[m+1]=i;
								x[m+2]='a'+j-1;
								x[m+3]=i-1;
								m+=4;
							}
							if(ban[i-'0'][j+1]!=-1&&ban[i-'0'][j+1]/6!=1){
								x[m]='a'+j-1;
								x[m+1]=i;
								x[m+2]='a'+j;
								x[m+3]=i;
								m+=4;
							}
							if(ban[i-'0'+1][j+1]!=-1&&ban[i-'0'+1][j+1]/6!=1){
								x[m]='a'+j-1;
								x[m+1]=i;
								x[m+2]='a'+j;
								x[m+3]=i+1;
								m+=4;
							}
						}
						else{
							if(ban[i-'0'][j]==8){
								if(ban[i-'0'+1][j-1]!=-1&&ban[i-'0'+1][j-1]/6!=1){
									x[m]='a'+j-1;
									x[m+1]=i;
									x[m+2]='a'+j-2;
									x[m+3]=i+1;
									m+=4;
								}
								if(ban[i-'0'-1][j-1]!=-1&&ban[i-'0'-1][j-1]/6!=1){
									x[m]='a'+j-1;
									x[m+1]=i;
									x[m+2]='a'+j-2;
									x[m+3]=i-1;
									m+=4;
								}
								if(ban[i-'0'-1][j+1]!=-1&&ban[i-'0'-1][j+1]/6!=1){
									x[m]='a'+j-1;
									x[m+1]=i;
									x[m+2]='a'+j;
									x[m+3]=i-1;
									m+=4;
								}
								if(ban[i-'0'+1][j+1]!=-1&&ban[i-'0'+1][j+1]/6!=1){
									x[m]='a'+j-1;
									x[m+1]=i;
									x[m+2]='a'+j;
									x[m+3]=i+1;
									m+=4;
								}
							}
							else{
								if(ban[i-'0'][j]==9){
									if(ban[i-'0'+1][j]!=-1&&ban[i-'0'+1][j]/6!=1){
										x[m]='a'+j-1;
										x[m+1]=i;
										x[m+2]='a'+j-1;
										x[m+3]=i+1;
										m+=4;
									}
									if(ban[i-'0'][j-1]!=-1&&ban[i-'0'][j-1]/6!=1){
										x[m]='a'+j-1;
										x[m+1]=i;
										x[m+2]='a'+j-2;
										x[m+3]=i;
										m+=4;
									}
									if(ban[i-'0'-1][j]!=-1&&ban[i-'0'-1][j]/6!=1){
										x[m]='a'+j-1;
										x[m+1]=i;
										x[m+2]='a'+j-1;
										x[m+3]=i-1;
										m+=4;
									}
									if(ban[i-'0'][j+1]!=-1&&ban[i-'0'][j+1]/6!=1){
										x[m]='a'+j-1;
										x[m+1]=i;
										x[m+2]='a'+j;
										x[m+3]=i;
										m+=4;
									}
								}
								else{
									if(ban[i-'0'][j]==10){
										if(ban[i-'0'+1][j]!=-1&&ban[i-'0'+1][j]/6!=1){
											x[m]='a'+j-1;
											x[m+1]=i;
											x[m+2]='a'+j-1;
											x[m+3]=i+1;
											m+=4;
										}
										if(ban[i-'0'+1][j-1]!=-1&&ban[i-'0'+1][j-1]/6!=1){
											x[m]='a'+j-1;
											x[m+1]=i;
											x[m+2]='a'+j-2;
											x[m+3]=i+1;
											m+=4;
										}
										if(ban[i-'0'][j-1]!=-1&&ban[i-'0'][j-1]/6!=1){
											x[m]='a'+j-1;
											x[m+1]=i;
											x[m+2]='a'+j-2;
											x[m+3]=i;
											m+=4;
										}
										if(ban[i-'0'-1][j-1]!=-1&&ban[i-'0'-1][j-1]/6!=1){
											x[m]='a'+j-1;
											x[m+1]=i;
											x[m+2]='a'+j-2;
											x[m+3]=i-1;
											m+=4;
										}
										if(ban[i-'0'-1][j]!=-1&&ban[i-'0'-1][j]/6!=1){
											x[m]='a'+j-1;
											x[m+1]=i;
											x[m+2]='a'+j-1;
											x[m+3]=i-1;
											m+=4;
										}
										if(ban[i-'0'-1][j+1]!=-1&&ban[i-'0'-1][j+1]/6!=1){
											x[m]='a'+j-1;
											x[m+1]=i;
											x[m+2]='a'+j;
											x[m+3]=i-1;
											m+=4;
										}
										if(ban[i-'0'][j+1]!=-1&&ban[i-'0'][j+1]/6!=1){
											x[m]='a'+j-1;
											x[m+1]=i;
											x[m+2]='a'+j;
								 			x[m+3]=i;
											m+=4;
										}
										if(ban[i-'0'+1][j+1]!=-1&&ban[i-'0'+1][j+1]/6!=1){
											x[m]='a'+j-1;
											x[m+1]=i;
											x[m+2]='a'+j;
											x[m+3]=i+1;
											m+=4;
										}
									}
								}
							}
						}
					}
				}
			}
		}

		for(l=0;l<3;l++){
			if(moti_2[l]>0){
				switch(l){
					case 0:
						koma=6;
						break;
					case 1:
						koma=8;
						break;
					case 2:
						koma=9;
						break;
				}
				for(i='1';i<'5';i++){
					for(j=1;j<4;j++){
						if(ban[i-'0'][j]==0){
							x[m]='0';
							x[m+1]=koma;
							x[m+2]='a'+j-1;
							x[m+3]=i;
							m+=4;
						}
					}
				}
			}
		}

	}

	if(tesu==1){
		for(i='1';i<'5';i++){
			for(j=1;j<4;j++){
				if(ban[i-'0'][j]!=0){
					if(ban[i-'0'][j]/6==0){
						if(ban[i-'0'][j]==1){
							if(ban[i-'0'-1][j]==0||ban[i-'0'-1][j]>5){
								x[m]='a'+j-1;
								x[m+1]=i;
								x[m+2]='a'+j-1;
								x[m+3]=i-1;
								m+=4;
							}
						}
						else{
							if(ban[i-'0'][j]==2){
								if(ban[i-'0'-1][j]==0||ban[i-'0'-1][j]>5){
									x[m]='a'+j-1;
									x[m+1]=i;
									x[m+2]='a'+j-1;
									x[m+3]=i-1;
									m+=4;
								}
								if(ban[i-'0'-1][j+1]==0||ban[i-'0'-1][j+1]>5){
									x[m]='a'+j-1;
									x[m+1]=i;
									x[m+2]='a'+j;
									x[m+3]=i-1;
									m+=4;
								}
								if(ban[i-'0'][j+1]==0||ban[i-'0'][j+1]>5){
									x[m]='a'+j-1;
									x[m+1]=i;
									x[m+2]='a'+j;
									x[m+3]=i;
									m+=4;
								}
								if(ban[i-'0'+1][j]==0||ban[i-'0'+1][j]>5){
									x[m]='a'+j-1;
									x[m+1]=i;
									x[m+2]='a'+j-1;
									x[m+3]=i+1;
									m+=4;
								}
								if(ban[i-'0'][j-1]==0||ban[i-'0'][j-1]>5){
									x[m]='a'+j-1;
									x[m+1]=i;
									x[m+2]='a'+j-2;
									x[m+3]=i;
									m+=4;
								}
								if(ban[i-'0'-1][j-1]==0||ban[i-'0'-1][j-1]>5){
									x[m]='a'+j-1;
									x[m+1]=i;
									x[m+2]='a'+j-2;
									x[m+3]=i-1;
									m+=4;
								}
							}
							else{
								if(ban[i-'0'][j]==3){
									if(ban[i-'0'+1][j-1]==0||ban[i-'0'+1][j-1]>5){
										x[m]='a'+j-1;
										x[m+1]=i;
										x[m+2]='a'+j-2;
										x[m+3]=i+1;
										m+=4;
									}
									if(ban[i-'0'-1][j-1]==0||ban[i-'0'-1][j-1]>5){
										x[m]='a'+j-1;
										x[m+1]=i;
										x[m+2]='a'+j-2;
										x[m+3]=i-1;
										m+=4;
									}
									if(ban[i-'0'-1][j+1]==0||ban[i-'0'-1][j+1]>5){
										x[m]='a'+j-1;
										x[m+1]=i;
										x[m+2]='a'+j;
										x[m+3]=i-1;
										m+=4;
									}
									if(ban[i-'0'+1][j+1]==0||ban[i-'0'+1][j+1]>5){
										x[m]='a'+j-1;
										x[m+1]=i;
										x[m+2]='a'+j;
										x[m+3]=i+1;
										m+=4;
									}
								}
								else{
									if(ban[i-'0'][j]==4){
										if(ban[i-'0'+1][j]==0||ban[i-'0'+1][j]>5){
											x[m]='a'+j-1;
											x[m+1]=i;
											x[m+2]='a'+j-1;
											x[m+3]=i+1;
											m+=4;
										}
										if(ban[i-'0'][j-1]==0||ban[i-'0'][j-1]>5){
											x[m]='a'+j-1;
											x[m+1]=i;
											x[m+2]='a'+j-2;
											x[m+3]=i;
											m+=4;
										}
										if(ban[i-'0'-1][j]==0||ban[i-'0'-1][j]>5){
											x[m]='a'+j-1;
											x[m+1]=i;
											x[m+2]='a'+j-1;
											x[m+3]=i-1;
											m+=4;
										}
										if(ban[i-'0'][j+1]==0||ban[i-'0'][j+1]>5){
											x[m]='a'+j-1;
											x[m+1]=i;
											x[m+2]='a'+j;
											x[m+3]=i;
											m+=4;
										}
									}
									else{
										if(ban[i-'0'][j]==5){
											if(ban[i-'0'+1][j]==0||ban[i-'0'+1][j]>5){
												x[m]='a'+j-1;
												x[m+1]=i;
												x[m+2]='a'+j-1;
												x[m+3]=i+1;
												m+=4;
											}
											if(ban[i-'0'+1][j-1]==0||ban[i-'0'+1][j-1]>5){
												x[m]='a'+j-1;
												x[m+1]=i;
												x[m+2]='a'+j-2;
												x[m+3]=i+1;
												m+=4;
											}
											if(ban[i-'0'][j-1]==0||ban[i-'0'][j-1]>5){
												x[m]='a'+j-1;
												x[m+1]=i;
												x[m+2]='a'+j-2;
												x[m+3]=i;
												m+=4;
											}
											if(ban[i-'0'-1][j-1]==0||ban[i-'0'-1][j-1]>5){
												x[m]='a'+j-1;
												x[m+1]=i;
												x[m+2]='a'+j-2;
												x[m+3]=i-1;
												m+=4;
											}
											if(ban[i-'0'-1][j]==0||ban[i-'0'-1][j]>5){
												x[m]='a'+j-1;
												x[m+1]=i;
												x[m+2]='a'+j-1;
												x[m+3]=i-1;
												m+=4;
											}
											if(ban[i-'0'-1][j+1]==0||ban[i-'0'-1][j+1]>5){
												x[m]='a'+j-1;
												x[m+1]=i;
												x[m+2]='a'+j;
												x[m+3]=i-1;
												m+=4;
											}
											if(ban[i-'0'][j+1]==0||ban[i-'0'][j+1]>5){
												x[m]='a'+j-1;
												x[m+1]=i;
												x[m+2]='a'+j;
									 			x[m+3]=i;
												m+=4;
											}
											if(ban[i-'0'+1][j+1]==0||ban[i-'0'+1][j+1]>5){
												x[m]='a'+j-1;
												x[m+1]=i;
												x[m+2]='a'+j;
												x[m+3]=i+1;
												m+=4;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}

		for(l=0;l<3;l++){
			if(moti_1[l]>0){
				switch(l){
					case 0:
						koma=1;
						break;
					case 1:
						koma=3;
						break;
					case 2:
						koma=4;
						break;
				}
				for(i='1';i<'5';i++){
					for(j=1;j<4;j++){
						if(ban[i-'0'][j]==0){
							x[m]='0';
							x[m+1]=koma;
							x[m+2]='a'+j-1;
							x[m+3]=i;
							m+=4;
						}
					}
				}
			}
		}
	}
	l=-1;
	for(i=1;i<5;i++){
		for(j='a';j<'d';j++){
			if(ban[i][j-'a'+1]==5){
				if(i==1){
					m=2;
					do{
						if(x[m]==j&&(x[m+1]-'0')==i){
							n=0;
						}
						m+=4;
					}while(strlen(x)>m);
					if(n==-1){
						return 1;
					}
				}
				k=0;
			}
			if(ban[i][j-'a'+1]==10){
				if(i==4){
					m=2;
					do{
						if(x[m]==j&&(x[m+1]-'0')==i){
							n=0;
						}
						m+=4;
					}while(strlen(x)>m);
					if(n==-1){
						return 2;
					}
				}
				l=0;
			}
		}
	}
	if(k==-1){
		return 2;
	}
	if(l==-1){
		return 1;
	}

	m=1;
	k=0;
	n=0;
	if(tesu==0){
		for(i=0;x[m]!=0;i++){
			if(ban[x[m+2]-'0'][x[m+1]-'a'+1]==5){
				y[0]=x[m-1];
				y[1]=x[m];
				y[2]=x[m+1];
				y[3]=x[m+2];
				y[4]='\0';
				strcpy(te, y);
				return 0;
			}
			if(x[m+2]=='4'&&ban[x[m]-'0'][x[m-1]-'a'+1]==10){
				for(n=0;n<5;n++){
					for(l=0;l<6;l++){
						t_ban[l][n]=ban[l][n];
					}
				}
				for(n=0;n<3;n++){
					i_moti_1[n]=moti_1[n];
					i_moti_2[n]=moti_2[n];
				}
				t_te[0]=x[m-1];
				t_te[1]=x[m];
				t_te[2]=x[m+1];
				t_te[3]=x[m+2];
				move(t_ban, t_te, tesu, i_moti_1, i_moti_2);
				if(check(t_ban, t_te, tesu+1, i_moti_1, i_moti_2)!=0){
					y[0]=x[m-1];
					y[1]=x[m];
					y[2]=x[m+1];
					y[3]=x[m+2];
					y[4]='\0';
					strcpy(te, y);
					return 0;
				}
			}
			if(ban[x[m+2]-'0'][x[m+1]-'a'+1]/6==0&&ban[x[m+2]-'0'][x[m+1]-'a'+1]!=0){
				y[k]=x[m-1];
				y[k+1]=x[m];
				y[k+2]=x[m+1];
				y[k+3]=x[m+2];
				j=m;
				k+=4;
				for(l=j+2;x[j-1]!=0;l++){
					x[j-1]=x[j+3];
					j++;
				}
			}
			m+=4;
		}
	}
	else{
		for(i=0;x[m]!=0;i++){
			if(ban[x[m+2]-'0'][x[m+1]-'a'+1]==10){

				y[0]=x[m-1];
				y[1]=x[m];
				y[2]=x[m+1];
				y[3]=x[m+2];
				y[4]='\0';
				strcpy(te, y);
				return 0;
			}
			if(x[m+2]=='1'&&ban[x[m]-'0'][x[m-1]-'a'+1]==5){
				for(n=0;n<5;n++){
					for(l=0;l<6;l++){
						t_ban[l][n]=ban[l][n];
					}
				}
				for(n=0;n<3;n++){
					i_moti_1[n]=moti_1[n];
					i_moti_2[n]=moti_2[n];
				}
				t_te[0]=x[m-1];
				t_te[1]=x[m];
				t_te[2]=x[m+1];
				t_te[3]=x[m+2];
				move(t_ban, t_te, tesu, i_moti_1, i_moti_2);
				if(check(t_ban, t_te, tesu+1, i_moti_1, i_moti_2)!=0){
					y[0]=x[m-1];
					y[1]=x[m];
					y[2]=x[m+1];
					y[3]=x[m+2];
					y[4]='\0';
					strcpy(te, y);
					return 0;
				}
			}
			if(ban[x[m+2]-'0'][x[m+1]-'a'+1]/6==1){
				y[k]=x[m-1];
				y[k+1]=x[m];
				y[k+2]=x[m+1];
				y[k+3]=x[m+2];
				j=m;
				k+=4;
				for(l=j+2;x[j-1]!=0;l++){
					x[j-1]=x[j+3];
					j++;
				}
			}
			m+=4;
		}
	}
	
	strcat(y, x);
	strcpy(te, y);

	return 0;
}

int sennitite(struct kyokumen banmen[], int ban[6][5], int moti_1[], int moti_2[])
{
	int i, j, k, l, n=-1;

	for(k=0;banmen[k].kaisu>0;k++){
		n=0;
		for(i=1;i<4;i++){
			for(j=1;j<5;j++){
				if(banmen[k].k_ban[j][i]!=ban[j][i]){
					n=-1;
					break;
				}
			}
			if(n==-1){
				break;
			}
		}
		if(n==0){
			for(l=0;l<3;l++){
				if(banmen[k].k_moti_1[l]!=moti_1[l]||banmen[k].k_moti_2[l]!=moti_2[l]){
					n=-1;
					break;
				}
			}
		}
		if(n==0){
			banmen[k].kaisu++;
			break;
		}
	}

	if(n==-1){
		for(i=0;i<5;i++){
			for(j=0;j<6;j++){
				banmen[k].k_ban[j][i]=ban[j][i];
			}
		}
		for(l=0;l<3;l++){
			banmen[k].k_moti_1[l]=moti_1[l];
			banmen[k].k_moti_2[l]=moti_2[l];
		}
		banmen[k].kaisu=1;
	}

	if(banmen[k].kaisu==3){
		return -1;
	}
	else{
		return 0;
	}
}

int move(int ban[6][5], char *te, int tesu, int moti_1[], int moti_2[])
{
	int teban, i, x=-1, temp, koma=0;

	teban=tesu%2;

	if(teban==1){
		if(te[0]=='0'){
			ban[te[3]-'0'][te[2]-'a'+1]=te[1];
			switch(te[1]){
				case 1:
					moti_1[0]--;
					break;
				case 3:
					moti_1[1]--;
					break;
				case 4:
					moti_1[2]--;
					break;
			}
		}
		else{
			if(ban[te[3]-'0'][te[2]-'a'+1]==0){
				ban[te[3]-'0'][te[2]-'a'+1]=ban[te[1]-'0'][te[0]-'a'+1];
				ban[te[1]-'0'][te[0]-'a'+1]=0;
			}
			else{
				koma=ban[te[3]-'0'][te[2]-'a'+1];
				switch(ban[te[3]-'0'][te[2]-'a'+1]){
					case 6:
						moti_1[0]++;
						break;
					case 7:
						moti_1[0]++;
						break;
					case 8:
						moti_1[1]++;
						break;
					case 9:
						moti_1[2]++;
						break;
				}
				ban[te[3]-'0'][te[2]-'a'+1]=ban[te[1]-'0'][te[0]-'a'+1];
				ban[te[1]-'0'][te[0]-'a'+1]=0;
			}
			if(te[3]=='1'&&ban[te[3]-'0'][te[2]-'a'+1]==1){
				ban[te[3]-'0'][te[2]-'a'+1]=2;
				koma+=20;
			}
		}
	}

	if(teban==0){
		if(te[0]=='0'){
			ban[te[3]-'0'][te[2]-'a'+1]=te[1];
			switch(te[1]){
				case 6:
					moti_2[0]--;
					break;
				case 8:
					moti_2[1]--;
					break;
				case 9:
					moti_2[2]--;
					break;
			}
		}
		else{
			if(ban[te[3]-'0'][te[2]-'a'+1]==0){
				ban[te[3]-'0'][te[2]-'a'+1]=ban[te[1]-'0'][te[0]-'a'+1];
				ban[te[1]-'0'][te[0]-'a'+1]=0;
			}
			else{
				koma=ban[te[3]-'0'][te[2]-'a'+1];
				switch(ban[te[3]-'0'][te[2]-'a'+1]){
					case 1:
						moti_2[0]++;
						break;
					case 2:
						moti_2[0]++;
						break;
					case 3:
						moti_2[1]++;
						break;
					case 4:
						moti_2[2]++;
						break;
				}
				ban[te[3]-'0'][te[2]-'a'+1]=ban[te[1]-'0'][te[0]-'a'+1];
				ban[te[1]-'0'][te[0]-'a'+1]=0;
			}
			if(te[3]=='4'&&ban[te[3]-'0'][te[2]-'a'+1]==6){
				ban[te[3]-'0'][te[2]-'a'+1]=7;
				koma+=20;
			}
		}
	}

	return koma;
	
}

void back(int ban[6][5], char *te, int tesu, int moti_1[], int moti_2[], int koma)
{
	int teban, i, x=-1, temp;

	teban=tesu%2;

	if(koma>19){
		koma-=20;
		ban[te[3]-'0'][te[2]-'a'+1]-=1;
	}

	if(teban==1){
		if(te[0]=='0'){
			switch(te[1]){
				case 1:
					moti_1[0]++;
					break;
				case 3:
					moti_1[1]++;
					break;
				case 4:
					moti_1[2]++;
					break;
			}
			ban[te[3]-'0'][te[2]-'a'+1]=0;
			i=0;
		}
		else{
			if(koma==0){
				ban[te[1]-'0'][te[0]-'a'+1]=ban[te[3]-'0'][te[2]-'a'+1];
				ban[te[3]-'0'][te[2]-'a'+1]=0;
			}
			else{
				ban[te[1]-'0'][te[0]-'a'+1]=ban[te[3]-'0'][te[2]-'a'+1];
				ban[te[3]-'0'][te[2]-'a'+1]=koma;
				switch(koma){
					case 6:
						moti_1[0]--;
						break;
					case 7:
						moti_1[0]--;
						break;
					case 8:
						moti_1[1]--;
						break;
					case 9:
						moti_1[2]--;
						break;
				}
			}
		}
	}
	else{
		if(te[0]=='0'){
			switch(te[1]){
				case 6:
					moti_2[0]++;
					break;
				case 8:
					moti_2[1]++;
					break;
				case 9:
					moti_2[2]++;
					break;
			}
			ban[te[3]-'0'][te[2]-'a'+1]=0;
		}
		else{
			if(koma==0){
				ban[te[1]-'0'][te[0]-'a'+1]=ban[te[3]-'0'][te[2]-'a'+1];
				ban[te[3]-'0'][te[2]-'a'+1]=0;
			}
			else{
				ban[te[1]-'0'][te[0]-'a'+1]=ban[te[3]-'0'][te[2]-'a'+1];
				ban[te[3]-'0'][te[2]-'a'+1]=koma;
				switch(koma){
					case 1:
						moti_2[0]--;
						break;
					case 2:
						moti_2[0]--;
						break;
					case 3:
						moti_2[1]--;
						break;
					case 4:
						moti_2[2]--;
						break;
				}
			}
		}
	}
}

void think(int ban[6][5], struct kyokumen banmen[], char *te, int tesu, int moti_1[], int moti_2[], int l)
{
	if(l==1){
		think_1(ban, te, tesu, moti_1, moti_2);
	}
	else{
		if(l!=9){
			l=l-1;
			think_2(ban, &banmen[0], te, tesu, moti_1, moti_2, l);
		}
		else{
			think_3(ban, &banmen[0], te, tesu, moti_1, moti_2);
		}
	}
}

void think_1(int ban[6][5], char *te, int tesu, int moti_1[], int moti_2[])
{
	int x, i, j, n;
	char str[1000]={""};
	
	x=check(ban, str, tesu, moti_1, moti_2);

	n=strlen(str);
	n=n/4;
	n=genrand_int32()%n;
	n=n*4;
	for(i=0;i<4;i++){
		te[i]=str[n+i];
	}

	printf("%s\n", te);
}

void think_2(int ban[6][5], struct kyokumen banmen[], char *te, int tesu, int moti_1[], int moti_2[], int depth)
{
	int best, node[4]={0, -1, 0, 0}, i, k, j, hanpuku=0;
	char str[1000]={""}, c;
	struct bestpv pv[100];
	struct hash *tikan;
	
	for(i=0;i<100;i++){
		pv[i].sasite[0]='\0';
	}
	
	tikan=(struct hash *)malloc(sizeof(struct hash)*1000000);
	if(tikan==NULL){
		printf("ƒƒ‚ƒŠ•s‘«!!\n");
	}
	for(i=0;i<1000000;i++){
		for(k=0;k<5;k++){
			for(j=0;j<6;j++){
				tikan[i].h_ban[j][k]=0;
			}
		}
		for(k=0;k<4;k++){
			tikan[i].h_moti_1[k]=0;
			tikan[i].h_moti_2[k]=0;
		}
		tikan[i].deep=0;
		tikan[i].low=0;
		tikan[i].upp=0;
	}
	
	do{
		/*for(i=0;i<100;i++){
			pv[i].sasite[0]='\0';
		}*/
		hanpuku++;
		node[3]=hanpuku;
		node[2]=0;
		node[0]=0;
		best=NegaMax(ban, &banmen[0], &pv[0], &tikan[0], str, tesu, moti_1, moti_2, 0, hanpuku, node, -9999, 9999);
		if(node[1]==-1){
			node[1]=0;
		}
		strcpy(str, pv[0].sasite);i=0;
		do{
		switch(pv[0].sasite[i]){
			case 1:
				pv[0].sasite[i]='h';
				break;
			case 3:
				pv[0].sasite[i]='z';
				break;
			case 4:
				pv[0].sasite[i]='k';
				break;
			case 6:
				pv[0].sasite[i]='h';
				break;
			case 8:
				pv[0].sasite[i]='z';
				break;
			case 9:
				pv[0].sasite[i]='k';
				break;
		}i++;}while(strlen(pv[0].sasite)>i);
		printf("%s\n", pv[0].sasite);
		if(best>9000||-9000>best){
			break;
		}
		
	}while(hanpuku<depth);

	for(i=0;i<4;i++){
		te[i]=str[i];
	}
	if(te[0]=='0'){
		switch(te[1]){
			case 1:
				c='h';
				break;
			case 3:
				c='z';
				break;
			case 4:
				c='k';
				break;
			case 6:
				c='h';
				break;
			case 8:
				c='z';
				break;
			case 9:
				c='k';
				break;
		}
		printf("Å‘Pè:%c%c%c%c, •]‰¿’l:%d, ’Tõ[‚³:%d, ’Tõ‘‹Ç–Ê:%d\n", te[0], c, te[2], te[3], best, hanpuku, node[0]);
	}
	else{
		printf("Å‘Pè:%s, •]‰¿’l:%d, ’Tõ[‚³:%d, ’Tõ‘‹Ç–Ê:%d\n", te, best, hanpuku, node[0]);
	}k=0;for(i=0;i<1000000;i++){if(tikan[i].deep>0){k++;}}printf("%f\n", (double)k/10000.0);
	free(tikan);
}

void think_3(int ban[6][5], struct kyokumen banmen[], char *te, int tesu, int moti_1[], int moti_2[])
{
	int best, node[4]={0, -1, 0, 0}, depth=0, i, j, k;
	double start, end;
	char str[1000]={""}, c;
	struct bestpv pv[100];
	struct hash *tikan;

	for(i=0;i<100;i++){
		pv[i].sasite[0]='\0';
	}

	tikan=(struct hash *)malloc(sizeof(struct hash)*1000000);
	if(tikan==NULL){
		printf("ƒƒ‚ƒŠ•s‘«!!\n");
	}
	for(i=0;i<1000000;i++){
		for(k=0;k<5;k++){
			for(j=0;j<6;j++){
				tikan[i].h_ban[j][k]=0;
			}
		}
		for(k=0;k<4;k++){
			tikan[i].h_moti_1[k]=0;
			tikan[i].h_moti_2[k]=0;
		}
		tikan[i].deep=0;
		tikan[i].low=0;
		tikan[i].upp=0;
	}
	
	do{
		/*for(i=0;i<100;i++){
			pv[i].sasite[0]='\0';
		}*/
		depth++;
		node[3]=depth;
		node[2]=0;
		node[0]=0;
		start=clock();
		best=NegaMax(ban, &banmen[0], &pv[0], &tikan[0], str, tesu, moti_1, moti_2, 0, depth, node, -9999, 9999);
		end=clock();
		if(node[1]==-1){
			node[1]=0;
		}
		strcpy(str, pv[0].sasite);i=0;
		do{
		switch(pv[0].sasite[i]){
			case 1:
				pv[0].sasite[i]='h';
				break;
			case 3:
				pv[0].sasite[i]='z';
				break;
			case 4:
				pv[0].sasite[i]='k';
				break;
			case 6:
				pv[0].sasite[i]='h';
				break;
			case 8:
				pv[0].sasite[i]='z';
				break;
			case 9:
				pv[0].sasite[i]='k';
				break;
		}i++;}while(strlen(pv[0].sasite)>i);
		printf("%s, %f\n", pv[0].sasite, (end-start)/CLOCKS_PER_SEC);
		if(best>9000||-9000>best){
			break;
		}
	}while(((end-start)/CLOCKS_PER_SEC)<1.0);

	for(i=0;i<4;i++){
		te[i]=str[i];
	}
	if(te[0]=='0'){
		switch(te[1]){
			case 1:
				c='h';
				break;
			case 3:
				c='z';
				break;
			case 4:
				c='k';
				break;
			case 6:
				c='h';
				break;
			case 8:
				c='z';
				break;
			case 9:
				c='k';
				break;
		}
		printf("Å‘Pè:%c%c%c%c, •]‰¿’l:%d, ’Tõ[‚³:%d, ’Tõ‘‹Ç–Ê:%d\n", te[0], c, te[2], te[3], best, depth, node[0]);
	}
	else{
		printf("Å‘Pè:%s, •]‰¿’l:%d, ’Tõ[‚³:%d, ’Tõ‘‹Ç–Ê:%d\n", te, best, depth, node[0]);
	}k=0;for(i=0;i<1000000;i++){if(tikan[i].deep>0){k++;}}printf("%f\n", (double)k/10000.0);
	free(tikan);
	
}

int NegaMax(int ban[6][5], struct kyokumen banmen[], struct bestpv pv[], struct hash tikan[], char *str, int tesu, int moti_1[], int moti_2[], int deep, int depth, int *node, int al, int be)
{
	int i, j=0, k, l, n, x, var=0, best, p, sen,  i_moti_1[4], i_moti_2[4], koma;
	unsigned long long int hash=0;
	int t_ban[6][5];
	char t_te[1000]={""}, i_te[1000]={""}, same[1000]={""};
	struct kyokumen *t_banmen;

	hash=hashti(ban, moti_1, moti_2, tesu);
	//hash=hash%1000000;

	n=0;
	do{
		if(tikan[hash].deep>=depth-deep&&tikan[hash].deep!=0){
			for(i=1;i<4;i++){
				for(j=1;j<5;j++){
					if(tikan[hash].h_ban[j][i]!=ban[j][i]){
						n=-1;
						//output(ban, moti_1, moti_2);
						//output(tikan[hash].h_ban, tikan[hash].h_moti_1, tikan[hash].h_moti_2);
						break;
					}
				}
				if(n==-1){
					break;
				}
			}
			if(n==0){
				for(l=0;l<3;l++){
					if(tikan[hash].h_moti_1[l]!=moti_1[l]||tikan[hash].h_moti_2[l]!=moti_2[l]){
						n=-1;
						break;
					}
				}
			}
			if(n==0){
				if(tikan[hash].low>=be){
					for(i=0;i<4;i++){
						pv[99].sasite[deep*4+i]=tikan[hash].h_te[i];
					}
					pv[99].sasite[deep*4+i]='\0';
					return tikan[hash].low;
				}
				if(tikan[hash].upp>=al){
					for(i=0;i<4;i++){
						pv[99].sasite[deep*4+i]=tikan[hash].h_te[i];
					}
					pv[99].sasite[deep*4+i]='\0';
					return tikan[hash].upp;
				}	
				if(tikan[hash].low>al){
					al=tikan[hash].low;
					break;
				}
				if(tikan[hash].upp<be){
					be=tikan[hash].upp;
					break;
				}
			}
			else{
				hash+=2;
			}
		}
		else{
			break;
		}
	}while(n=0);

	
	x=c_check(ban, t_te, tesu, moti_1, moti_2);

	if(x==1){
		if(tesu%2==0){
			return -9999+deep-1;
		}
		else{
			return 9999-deep+1;
		}
	}
	if(x==2){
		if(tesu%2==0){
			return 9999-deep+1;
		}
		else{
			return -9999+deep-1;
		}
	}
	
	if(str[deep*4]!='\0'&&strlen(t_te)!=4){
		for(i=0;i<strlen(t_te);i+=4){
			if(t_te[i]==str[deep*4]&&t_te[i+1]==str[deep*4+1]&&t_te[i+2]==str[deep*4+2]&&t_te[i+3]==str[deep*4+3]){
				i_te[0]=t_te[0];
				i_te[1]=t_te[1];
				i_te[2]=t_te[2];
				i_te[3]=t_te[3];

				t_te[0]=str[deep*4];
				t_te[1]=str[deep*4+1];
				t_te[2]=str[deep*4+2];
				t_te[3]=str[deep*4+3];

				t_te[i]=i_te[0];
				t_te[i+1]=i_te[1];
				t_te[i+2]=i_te[2];
				t_te[i+3]=i_te[3];
				break;
			}
		}
	}
	
	if(depth==deep){
		var+=moti_1[0]*15;
		var+=moti_1[1]*30;
		var+=moti_1[2]*30;
		var-=moti_2[0]*15;
		var-=moti_2[1]*30;
		var-=moti_2[2]*30;
		
		for(i=1;i<5;i++){
			for(j=1;j<4;j++){
				switch(ban[i][j]){
					case 0:
						break;
					case 1:
						var+=10;
						break;
					case 2:
						var+=25;
						break;
					case 3:
						var+=20;
						break;
					case 4:
						var+=20;
						break;
					case 6:
						var-=10;
						break;
					case 7:
						var-=25;
						break;
					case 8:
						var-=20;
						break;
					case 9:
						var-=20;
						break;
				}
			}
		}

		if(tesu%2==0){
			return -var;
		}
		else{
			return var;
		}
	}
	
	t_banmen=(struct kyokumen *)malloc(sizeof(struct kyokumen)*1000);
	

	for(i=0;i<1000;i++){
		t_banmen[i]=banmen[i];
	}
	if(deep!=0){
		sen=sennitite(&t_banmen[0], ban, moti_1, moti_2);
		if(sen==-1){
			free(t_banmen);
			return 0;
		}
	}

	j=0;
	for(i=0;i<4;i++){
		i_te[i]=t_te[j];
		pv[99].sasite[deep*4+i]=i_te[i];
		j++;
	}
	pv[99].sasite[deep*4+i]='\0';

	koma=move(ban, i_te, tesu, moti_1, moti_2);
	node[0]++;
	var=-NegaMax(ban, &t_banmen[0], &pv[0], &tikan[0], str, tesu+1, moti_1, moti_2, deep+1, depth, node, -be, -al);
	back(ban, i_te, tesu, moti_1, moti_2, koma);

	if(var>al){
		al=var;
		best=al;

		hash=hashti(ban, moti_1, moti_2, tesu);
		//hash=hash%1000000;
		n=0;
		do{
			if(tikan[hash].deep==0){
				for(i=1;i<5;i++){
					for(p=1;p<4;p++){
						tikan[hash].h_ban[i][p]=ban[i][p];
					}
				}
				for(k=0;k<3;k++){
					tikan[hash].h_moti_1[k]=moti_1[k];
					tikan[hash].h_moti_2[k]=moti_2[k];
				}
				tikan[hash].deep=depth-deep-1;
				if(best<=al){
					tikan[hash].upp=best;
				}
				else{
					if(best>=be){
						tikan[hash].low=best;
					}
					else{
						tikan[hash].upp=best;
						tikan[hash].low=best;
					}
				}
				strcpy(tikan[hash].h_te, i_te);
			}
			else{
				for(i=1;i<4;i++){
					for(p=1;p<5;p++){
						if(tikan[hash].h_ban[p][i]!=ban[p][i]){
							n=-1;
							//output(ban, moti_1, moti_2);
							//output(tikan[hash].h_ban, tikan[hash].h_moti_1, tikan[hash].h_moti_2);
							break;
						}
					}
					if(n==-1){
						break;
					}
				}
				if(n==0){
					for(l=0;l<3;l++){
						if(tikan[hash].h_moti_1[l]!=moti_1[l]||tikan[hash].h_moti_2[l]!=moti_2[l]){
							n=-1;
							break;
						}
					}
				}
				if(n==0){
					if(tikan[hash].deep<depth-deep){
						tikan[hash].deep=depth-deep-1;
						if(best<=al){
							tikan[hash].upp=best;
						}
						else{
							if(best>=be){
								tikan[hash].low=best;
							}
							else{
								tikan[hash].upp=best;
								tikan[hash].low=best;
							}
						}
						strcpy(tikan[hash].h_te, i_te);
					}
					break;
				}
				if(n==-1){
					hash=(hash+2)%1000000;
				}
			}
		}while(n=0);

		if(deep+1==depth){
			strcpy(pv[deep].sasite, pv[99].sasite);
		}
		else{
			strcpy(pv[deep].sasite, pv[deep+1].sasite);
		}

	}

	while(t_te[j]!=0&&al<be){
		for(i=0;i<4;i++){
			i_te[i]=t_te[j];
			pv[99].sasite[deep*4+i]=i_te[i];
			j++;
		}
		pv[99].sasite[deep*4+i]='\0';

		koma=move(ban, i_te, tesu, moti_1, moti_2);
		var=-NegaMax(ban, &t_banmen[0], &pv[0], &tikan[0], str, tesu+1, moti_1, moti_2, deep+1, depth, node, -al-1, -al);
		if(var>al){
			al=var;
			var=-NegaMax(ban, &t_banmen[0], &pv[0], &tikan[0], str, tesu+1, moti_1, moti_2, deep+1, depth, node, -be, -al);
		}
		back(ban, i_te, tesu, moti_1, moti_2, koma);

		if(var>al){
			al=var;

			hash=hashti(ban, moti_1, moti_2, tesu);
			//hash=hash%1000000;
			n=0;
			do{
			if(tikan[hash].deep==0){
				for(i=1;i<5;i++){
					for(p=1;p<4;p++){
						tikan[hash].h_ban[i][p]=ban[i][p];
					}
				}
				for(k=0;k<3;k++){
					tikan[hash].h_moti_1[k]=moti_1[k];
					tikan[hash].h_moti_2[k]=moti_2[k];
				}
				tikan[hash].deep=depth-deep-1;
				tikan[hash].low=al;
				tikan[hash].upp=be;
				strcpy(tikan[hash].h_te, i_te);
			}
			else{
				for(i=1;i<4;i++){
					for(p=1;p<5;p++){
						if(tikan[hash].h_ban[p][i]!=ban[p][i]){
							n=-1;
							//output(ban, moti_1, moti_2);
							//output(tikan[hash].h_ban, tikan[hash].h_moti_1, tikan[hash].h_moti_2);
							break;
						}
					}
					if(n==-1){
						break;
					}
				}
				if(n==0){
					for(l=0;l<3;l++){
						if(tikan[hash].h_moti_1[l]!=moti_1[l]||tikan[hash].h_moti_2[l]!=moti_2[l]){
							n=-1;
							break;
						}
					}
				}
				if(n==0){
					if(tikan[hash].deep<depth-deep){
						tikan[hash].deep=depth-deep-1;
						tikan[hash].low=al;
						tikan[hash].upp=be;
						strcpy(tikan[hash].h_te, i_te);
					}
					break;
				}
				if(n==-1){
					hash=(hash+2)%1000000;
				}
			}
		}while(n=0);
			if(deep+1==depth){
				strcpy(pv[deep].sasite, pv[99].sasite);
			}
			else{
				strcpy(pv[deep].sasite, pv[deep+1].sasite);
			}
		}
	}
	free(t_banmen);
	return al;
}

int hashti(int ban[6][5], int moti_1[], int moti_2[], int tesu)
{
	unsigned long long int index[4], hash;
	unsigned long long int a=2305843009213693951, b=12345, c=16807;
	
	index[0]=ban[1][1]*11*11*11+ban[2][1]*11*11+ban[3][1]*11+ban[4][1];
	index[1]=ban[1][2]*11*11*11+ban[2][2]*11*11+ban[3][2]*11+ban[4][2];
	index[2]=ban[1][3]*11*11*11+ban[2][3]*11*11+ban[3][3]*11+ban[4][3];
	index[3]=moti_1[0]*3*3*3*3*3+moti_1[1]*3*3*3*3+moti_1[2]*3*3*3+moti_2[0]*3*3+moti_2[1]*3+moti_2[2];

	hash=index[3]*17*17*17+index[2]*17*17+index[1]*17+index[0];

	hash=(c*hash)%1000001;
	if(tesu%2!=hash%2){
		hash++;
	}
	//init_genrand(hash);
	//hash=genrand_int32();
	//printf("%lld\n", hash);
	return hash;
}

void m_m(void)
{
	int ban[6][5]={
		-1, -1, -1, -1, -1,
		-1,  9, 10,  8, -1,
		-1,  0,  6,  0, -1,
		-1,  0,  1,  0, -1,
		-1,  3,  5,  4, -1,
		-1, -1, -1, -1, -1,
	};
	int tesu=1, i, j, k, x=0, m, sen, moti_1[4]={0}, moti_2[4]={0};
	char te[200]={""}, m_te[10]={""};
	struct kyokumen banmen[1000];
	
	for(i=0;i<1000;i++){
		for(k=0;k<5;k++){
			for(j=0;j<6;j++){
				banmen[i].k_ban[j][k]=0;
			}
		}
		for(k=0;k<4;k++){
			banmen->k_moti_1[k]=0;
			banmen->k_moti_2[k]=0;
		}
		banmen[i].kaisu=-1;
	}
	
	output(ban, moti_1, moti_2);
	
	do{
		do{
			if(x==0){
				sen=sennitite(&banmen[0], ban, moti_1, moti_2);
			}
			x=check(ban, te, tesu, moti_1, moti_2);printf("%s\n", te);
			if(x==1){
				printf("æè‚ÌŸ‚¿!!\n");
				return;
			}
			if(x==2){
				printf("Œãè‚ÌŸ‚¿!!\n");
				return;
			}
			if(sen==-1){
				printf("ç“úè!!ˆø‚«•ª‚¯!!\n");
				return;
			}
			input(m_te, tesu);
			m=0;
			x=-1;
			if(strlen(m_te)==4){
				j=strlen(te)/4;
				for(i=0;i<j;i++){
					if(m_te[0]==te[m]&&m_te[1]==te[m+1]&&m_te[2]==te[m+2]&&m_te[3]==te[m+3]){
						x=0;
						break;
					}
					else{
						m+=4;
					}
				}
			}
		}while(x==-1);
		move(ban, m_te, tesu, moti_1, moti_2);
		tesu++;
		output(ban, moti_1, moti_2);
		x=0;
	}while(x==0);
}

void m_c(int c)
{
	int ban[6][5]={
		-1, -1, -1, -1, -1,
		-1,  9, 10,  8, -1,
		-1,  0,  6,  0, -1,
		-1,  0,  1,  0, -1,
		-1,  3,  5,  4, -1,
		-1, -1, -1, -1, -1,
	};
	int teban, tesu=1, i, j, k, x=0, m, sen,  moti_1[7]={0}, moti_2[7]={0};
	char te[200]={""}, m_te[10]={""};
	struct kyokumen banmen[1000];
	
	for(i=0;i<1000;i++){
		for(k=0;k<5;k++){
			for(j=0;j<6;j++){
				banmen[i].k_ban[j][k]=0;
			}
		}
		for(k=0;k<4;k++){
			banmen->k_moti_1[k]=0;
			banmen->k_moti_2[k]=0;
		}
		banmen[i].kaisu=-1;
	}
	
	teban=genrand_int32()%2;
	if(teban==1){
		printf("‚ ‚È‚½‚Ìæè”Ô(•)‚Å‚·B\n");
	}
	else{
		printf("‚ ‚È‚½‚ÌŒãè”Ô(”’)‚Å‚·B\n");
	}
	
	output(ban, moti_1, moti_2);
	
	do{
		do{
			if(x==0){
				sen=sennitite(&banmen[0], ban, moti_1, moti_2);
			}
			x=check(ban, te, tesu, moti_1, moti_2);
			if(x==1){
				printf("æè‚ÌŸ‚¿\n");
				return;
			}
			if(x==2){
				printf("Œãè‚ÌŸ‚¿\n");
				return;
			}
			if(sen==-1){
				printf("ç“úè!!ˆø‚«•ª‚¯!!\n");
				return;
			}
			if(tesu%2==teban){
				input(m_te, tesu);
			}
			else{
				think(ban, &banmen[0], m_te, tesu, moti_1, moti_2, c);
			}
			m=0;
			x=-1;
			if(strlen(m_te)==4){
				j=strlen(te)/4;
				for(i=0;i<j;i++){
					if(m_te[0]==te[m]&&m_te[1]==te[m+1]&&m_te[2]==te[m+2]&&m_te[3]==te[m+3]){
						x=0;
						break;
					}
					else{
						m+=4;
					}
				}
			}
		}while(x==-1);
		move(ban, m_te, tesu, moti_1, moti_2);
		tesu++;
		output(ban, moti_1, moti_2);
		x=0;
	}while(x==0);
}

int c_c(int c_1, int c_2)
{
	int ban[6][5]={
		-1, -1, -1, -1, -1,
		-1,  9, 10,  8, -1,
		-1,  0,  6,  0, -1,
		-1,  0,  1,  0, -1,
		-1,  3,  5,  4, -1,
		-1, -1, -1, -1, -1,
	};
	int teban, tesu=1, i, j, k, x, m, sen,  moti_1[7]={0}, moti_2[7]={0};
	char te[200]={""}, m_te[10]={""};
	struct kyokumen banmen[1000];
	
	for(i=0;i<1000;i++){
		for(k=0;k<5;k++){
			for(j=0;j<6;j++){
				banmen[i].k_ban[j][k]=0;
			}
		}
		for(k=0;k<4;k++){
			banmen->k_moti_1[k]=0;
			banmen->k_moti_2[k]=0;
		}
		banmen[i].kaisu=-1;
	}

	//output(ban, moti_1, moti_2);

	do{
		do{
			x=check(ban, te, tesu, moti_1, moti_2);
			if(x==1){
				printf("æè‚ÌŸ‚¿\n");
				return 1;
			}
			if(x==2){
				printf("Œãè‚ÌŸ‚¿\n");
				return 2;
			}
			sen=sennitite(&banmen[0], ban, moti_1, moti_2);
			if(sen==-1){
				printf("ç“úè!!ˆø‚«•ª‚¯!!\n");
				return 0;
			}
			if(tesu%2==1){
				think(ban, &banmen[0], m_te, tesu, moti_1, moti_2, c_1);
			}
			else{
				think(ban, &banmen[0], m_te, tesu, moti_1, moti_2, c_2);
			}
			m=0;
			x=-1;
			if(strlen(m_te)==4){
				j=strlen(te)/4;
				for(i=0;i<j;i++){
					if(m_te[0]==te[m]&&m_te[1]==te[m+1]&&m_te[2]==te[m+2]&&m_te[3]==te[m+3]){
						x=0;
						break;
					}
					else{
						m+=4;
					}
				}
			}
		}while(x==-1);
		move(ban, m_te, tesu, moti_1, moti_2);
		tesu++;
		output(ban, moti_1, moti_2);
	}while(x=-1);

	return 0;
}