#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct _p{
	char name;
	//double given;
	double num;
	double separated;
	int tonum;
	//struct _p *from;

} _p;


int main(void){
	
	FILE *fp;
	char *fname = "small_data.txt";
	int pagenum, linknum;
	char from, to;

	int i,j,k;

	fp = fopen(fname, "r");
	if(fp == NULL){
		printf("cannnot open %s\n", fname);
		return -1;
	}

	fscanf(fp, "%d\n", &pagenum);
//	printf("found num!\n");
	struct _p page[pagenum];
	int link[pagenum][pagenum];
	for(i=0; i<pagenum; i++){
		for(j=0; j<pagenum; j++){
			link[i][j]=0;
		}
		page[i].tonum = 0;
	}

	for(i=0; i<pagenum; i++){
		fscanf(fp, "%c\n", &page[i].name);
		page[i].num=100;
//		printf("%d %f\n",i, page[i].num);
	}

	fscanf(fp,"%d\n", &linknum);
	for(i=0; i<linknum; i++){
		fscanf(fp, "%c %c\n", &from, &to);
	//	printf("%c %c\n",from, to);

		for(j=0; j<pagenum; j++){
			if(page[j].name == from){
		//		printf("found!from\n");
				page[j].tonum ++;
				for(k=0; k<pagenum; k++){
					if(page[k].name == to){
						link[j][k]=1;
						break;
					}
				}
				break;
			}
		}

	}
/*ここから動作確認用表示
	for(i=0; i<pagenum; i++){
		for(j=0; j<pagenum; j++){
			printf("%d %d %d\n", i, j, link[i][j]);
		}
	}
	for(i=0; i<pagenum; i++){
		printf("%d %d\n", i, page[i].tonum);
	}
*///ここまで

	//計算処理
	//k回分配の計算をする
	for(k=0; k<20; k++){

	for(i=0; i<pagenum; i++){
		page[i].separated = page[i].num / page[i].tonum;
		page[i].num = 0;
	}

	for(i=0; i<pagenum; i++){
		for(j=0; j<pagenum; j++){
			if(link[j][i] == 1){
				page[i].num += page[j].separated;
			}
		}
	}

	for(i=0; i<pagenum; i++){
		printf("%f\t",page[i].num);
	}
	printf("\n");
	}

	printf("end\n");

	double sum=0;
	for(i=0; i<pagenum; i++){
		sum += page[i].num;
	}

	printf("average is %f\n", sum / pagenum);
	fclose(fp);
	return 0;
}
