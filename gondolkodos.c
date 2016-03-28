// Copyright (C) 2016, Faragó Tamás, ocsi0520@gmail.com
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// Ez a program szabad szoftver; terjeszthetõ illetve módosítható a
// Free Software Foundation által kiadott GNU General Public License
// dokumentumában leírtak; akár a licenc 3-as, akár (tetszõleges) késõbbi
// változata szerint.
//
// Ez a program abban a reményben kerül közreadásra, hogy hasznos lesz,
// de minden egyéb GARANCIA NÉLKÜL, az ELADHATÓSÁGRA vagy VALAMELY CÉLRA
// VALÓ ALKALMAZHATÓSÁGRA való származtatott garanciát is beleértve.
// További részleteket a GNU General Public License tartalmaz.
//
// A felhasználónak a programmal együtt meg kell kapnia a GNU General
// Public License egy példányát; ha mégsem kapta meg, akkor
// tekintse meg a <http://www.gnu.org/licenses/> oldalon.

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int _KULCSSZAM_;
void kereses(const char*);
void kiiratas();
void kulcs_kiiratas();
int bennevan(char a);
int joakulcs(char b);
char lehetsegeskulcs[300];
int lehetmax;
void tores();
void valtoztatas();
char beolvasott[63000];
char elvilegtort[63000];
char kulcs[100]; //max kulcshossz 99
int db;
int main(int argc, char** argv) //első a fájl
{
	if(argc!=3)
	{
		printf("./gondolkodos fajlnev kulcshossz\n");
		return -1;
	}
		FILE*fp;
		_KULCSSZAM_=atoi(argv[2]);
		fp=fopen(argv[1],"r");
		int i;
			if(!fp)
			{
				printf("fajlgaz\n"); return -2;
			}
			for (i = 0; i < 300; ++i)
			{
				lehetsegeskulcs[i]=i;
			}
			for (i = 0;!feof(fp) && i<63000 ; ++i)
			{
				fscanf(fp,"%c",&beolvasott[i]);
			}
			fclose(fp);
			//printf("lehetseges kulcsok (max 99):\t");
			//scanf("%s",lehetsegeskulcs); lehetmax=strlen(lehetsegeskulcs);
			lehetmax=299;
		db=i-1;
		tores();
		printf("\nkiiras:\n");
		kiiratas();
		valtoztatas();
			return 0;
}

void kiiratas()
{
	int i;
		for (i = 0; i < db; ++i)
		{
			printf("%c",elvilegtort[i]);
		}
}

void kulcs_kiiratas()
{
	int i;
	printf("kulcs:\t");
		for (i = 0; i < _KULCSSZAM_; ++i)
		{
			printf("%c",kulcs[i]);
		}
		printf("\n");
}
void tores()
{
	//printf("-------------------\n%s\n--------------------\n",lehetsegeskulcs);
	int i,j;
	int lehetseged;
	int HATAR=db/_KULCSSZAM_*0.1;
	int rossz=0;
	for(i=0;i<_KULCSSZAM_;i++)
	kulcs[i]=lehetsegeskulcs[0];
	for (i = 0; i < _KULCSSZAM_; ++i) //kulcsokon végigmegyünk
	{
		lehetseged=0;rossz=0;
		for (j = i; j < db; j+=_KULCSSZAM_) //az ehhez a kulcshoz tartozó karaktereken végigmegyünk
		{
			elvilegtort[j]=beolvasott[j]^kulcs[i];
			if(!joakulcs(elvilegtort[j]))
				{rossz++;printf("i:%d j:%d elvilegtort:%c\n",i,j,elvilegtort[j]);}
			if(rossz > HATAR) //ha a határon túl vagyunk, léptetjük a kulcsot
			{
				printf("lehetseged: %d\n",lehetseged);
				rossz=0;j=i-_KULCSSZAM_;lehetseged++;
				if(lehetseged>lehetmax)
				{
					lehetseged=0;
					printf("\n_GAZ_kulcsszam: %d\n",i); exit(-1); //break; ha majd nem lesz exit
				}
				kulcs[i]=lehetsegeskulcs[lehetseged];
			}
		}
	}
	printf("\n//vege\\\\\n");
}

int joakulcs(char b)
{
	if(	isalnum(b) || isspace(b) || bennevan(b))
		return 1;
	return 0;
}

int bennevan(char a)
{
	int i;
	//char asd[]="?:_,.-$éáűúőöüóí\'\"+!%/=()[]&|*<>#{}^@~;\\";
	//char asd[]="?:_,.-éáűúőöüóí()";
	char asd[]="?:,.!-éáűúőöüóí";
	//char asd[]="";
	for(i=0;i<strlen(asd);i++) //azert +1 hogy a \0 is benne legyen
	{
		if(a==asd[i])
			return 1;
	}
	return 0;
}

void valtoztatas()	
{
	int i=0,j;char c[100];
	kulcs_kiiratas();
	for(;;)
	{
		printf("Index betu (-1-es index a kereseshez, tobbi negativnal kilepes)\n");
		scanf("%d %[^\n]s",&i,c);
		if(i==-1)
		{
			kereses(c);
			continue;
		}
		else if(i<-1)
			return;
		printf("ellenorzes i: %d\tc:%s\n",i,c);
		kulcs[i%_KULCSSZAM_]=beolvasott[i]^c[0];
		for(j=i%_KULCSSZAM_;j<db;j+=_KULCSSZAM_)
		{
			elvilegtort[j]=beolvasott[j]^kulcs[i];
		}
		kiiratas();
		kulcs_kiiratas();
	}
}

void kereses(const char* c)
{
	int i;
	for(i=0;i<db;i++)
	{
		if(egyezes(c,&elvilegtort[i])) // megtalálta
		{
			printf("kezdoindex: %d (%c)\n",i,elvilegtort[i]);
			return;
		}
	}
	printf("nem talaltam a szoveget :( \n");
		return;
}

int egyezes(const char*c,const char*szoveg)
{
	int i;
	for (i = 0; i < strlen(c)-1; ++i)
	{
		//printf("%c:%c ",c[i],szoveg[i]);
		if(c[i]!=szoveg[i])
			return 0;
	}
	printf("\n");
	return 1;
}