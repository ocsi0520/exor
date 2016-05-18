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

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>

int _KULCSSZAM_;
void kereses(const std::string& mit, const std::string& miben);
bool bennevan(char a);
bool joakulcs(char b);
std::string tores(std::string&, const std::string&);
void valtoztatas(std::string& kulcs,std::string& tortszoveg,const std::string& beolvasott);

int main(int argc, char** argv) //első a fájl
{
	std::string beolvasott="",jokulcs,tortszoveg="";
	if(argc!=3)
	{
		std::cout << "./gondolkodos fajlnev kulcshossz" << std::endl;
		return -1;
	}
		std::ifstream fp {argv[1]};
		_KULCSSZAM_=atoi(argv[2]);
		int i;
			if(!fp.is_open())
			{
				std::cout <<"fajlgaz" << std::endl;
				return -2;
			}
			 while (!fp.eof())
			 	beolvasott.push_back(fp.get());
			fp.close();
		jokulcs=tores(tortszoveg,beolvasott);
		std::cout << "kiiras" << std::endl;
		std::cout << tortszoveg << std::endl;
		valtoztatas(jokulcs,tortszoveg,beolvasott);
		std::cout << tortszoveg << std::endl;
		std:: cout << jokulcs << std::endl;
			return 0;
}

std::string tores(std::string& elvilegtort, const std::string& beolvasott)
{
	int i,j;
	std::string lehetsegeskulcs="",kulcs="";
	for (i = 0; i < 256; ++i)
	{
		lehetsegeskulcs.push_back(i);
	}
	elvilegtort=beolvasott;
	int lehetseged;
	int HATAR=beolvasott.length()/_KULCSSZAM_*0.1;
	int rossz=0;
	for(i=0;i<_KULCSSZAM_;i++)
	kulcs.push_back(lehetsegeskulcs[0]);
	for (i = 0; i < _KULCSSZAM_; ++i) //kulcsokon végigmegyünk
	{
		lehetseged=0;rossz=0;
		for (j = i; j < beolvasott.length(); j+=_KULCSSZAM_) //az ehhez a kulcshoz tartozó karaktereken végigmegyünk
		{
			elvilegtort[j]=beolvasott[j]^kulcs[i];
			if(!joakulcs(elvilegtort[j]))
				{
					rossz++;
					//std::cout << "i: " << i << "j: " << j << "elvilegtort: " << elvilegtort[j] << std::endl;
				}
			if(rossz > HATAR) //ha a határon túl vagyunk, léptetjük a kulcsot
			{
				//std::cout << "lehetseged: " << lehetseged << std::endl; 
				rossz=0;j=i-_KULCSSZAM_;lehetseged++;
				if(lehetseged>lehetsegeskulcs.length())
				{
					lehetseged=0;
					std::cout << "\n_GAZ_kulcsszam: " << i;
					exit(-1);
				}
				kulcs[i]=lehetsegeskulcs[lehetseged];
			}
		}
	}
	elvilegtort[elvilegtort.length()-1]=0; // \0 a végére
	return kulcs;
}

bool joakulcs(char b)
{
	if(	isalnum(b) || isspace(b) || bennevan(b))
		return true;
	return false;
}

bool bennevan(char a)
{
	int i;
	//char asd[]="?:_,.-$éáűúőöüóí\'\"+!%/=()[]&|*<>#{}^@~;\\";
	//char asd[]="?:_,.-éáűúőöüóí()";
	std::string asd="?:,.!-éáűúőöüóí";
	//char asd[]="";
	for(i=0;i<asd.length();i++) //azert +1 hogy a \0 is benne legyen
	{
		if(a==asd[i])
			return true;
	}
	return false;
}

void valtoztatas(std::string& kulcs, std::string& elvilegtort, const std::string& beolvasott)	
{
	int i=0,j;
	std::string c;
	//kulcs_kiiratas();
	for(;;)
	{
		//printf("Index betu (-1-es index a kereseshez, tobbi negativnal kilepes)\n");
		std::cout << "index enter betű (-1-es index a kereséshez, többi negatívnal kilépés)" << std::endl;
		std::cin >> i;
		if (i<-1)
			return;
		//std::cin >> c;
		std::cin.ignore(256,'\n');
		std::getline (std::cin,c);
		if(i==-1)
		{
			size_t talalat = elvilegtort.find(c);
			if(talalat!=std::string::npos)
				std::cout << "megtaláltam, ez a kezdőindexe: " << talalat << std::endl;
			else
				std::cout << "nem találtam meg :(" << std::endl;
			continue;
		}
		std::cout << "ellenőrzes i: " << i << '\t' << c << std::endl;
		kulcs[i%_KULCSSZAM_]=beolvasott[i]^c[0];
		for(j=i%_KULCSSZAM_;j<beolvasott.length();j+=_KULCSSZAM_)
		{
			elvilegtort[j]=beolvasott[j]^kulcs[i];
		}
		std::cout << elvilegtort << std::endl;
		//kiiratas();
		//kulcs_kiiratas();
	}
}

/*void kereses(const std::string& c, const std::string& elvilegtort)
{
	int i,egyezes=0;
	for(i=0;i<elvilegtort.length();i++)
	{
		if(egyezes == c.length())
		{
			std::cout << "index: " << i-egyezes << "betű:" << elvilegtort[i-egyezes] << std::endl;
			return;
		}
		if(elvilegtort[i]==c[egyezes])
		{
			egyezes++;
		}
		else
			egyezes=0;
	}
	std::cout << "nem találtam meg a szöveget :(" << std::endl;
		return;
}*/