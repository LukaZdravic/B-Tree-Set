#include <iostream>
#include <stdio.h>
#include <vector>
#include <stack>
#include <queue>

using namespace std;
int brkorakabin = 0;
int brkorakatern = 0;

class Cvor {
public:
	Cvor(int data, int visina=1) : datavalue(data),visina(visina) {}
	static Cvor* ubaci_vrednost(Cvor*& koren,int value);
	static int getVisina(Cvor* cvor);
	static int getBalans(Cvor* cvor);

	Cvor* levisin;
	Cvor* desnisin;
	int visina;
	int datavalue;
};

void uradi_tabove(int tabs) {
	for (int i = 0; i < tabs; i++) cout << " ";
}
/*
void lepPrint(Cvor* koren) {
	if (koren == nullptr) return;
	queue<Cvor*> red;
	int tmp = koren->visina;
	Cvor* next = koren;
	red.push(next);
	while (red.empty() == false) {
		next = red.front();
		red.pop();
		uradi_tabove(abs(next->visina-tmp));
		cout << next->datavalue<<endl;
		if (next->levisin != nullptr) red.push(next->levisin);
		if (next->desnisin != nullptr) red.push(next->desnisin);
	}


}*/
void lepPrint(Cvor* koren,int dubina) {
	if (koren == nullptr) return;
	uradi_tabove(dubina);
	cout << koren->datavalue << endl;
	lepPrint(koren->levisin, dubina + 1);
	lepPrint(koren->desnisin, dubina + 1);



}

int InOrder_pretragaPR(Cvor* koren, int key) {
	stack<Cvor*> S;
	Cvor* trenutni = koren;
	while (trenutni != nullptr || S.empty() == false) {
		while (trenutni != nullptr) {
			S.push(trenutni);
			trenutni = trenutni->levisin;
		}
		trenutni = S.top();
		S.pop();
		if (trenutni->datavalue == key) return 1;
		trenutni = trenutni->desnisin;
	}
	return 0;

}

void InOrder_pretragaCL(Cvor* koren) {
	stack<Cvor*> S;
	Cvor* trenutni = koren;
	Cvor* tmp;
	while (trenutni != nullptr || !(S.empty())) {
		while (trenutni != nullptr) {
			S.push(trenutni);
			trenutni = trenutni->levisin;
		}
		trenutni = S.top();
		S.pop();
		tmp = trenutni;
		trenutni = trenutni->desnisin;
		free(tmp);
	}

}

void InOrder_pretragaSR(Cvor* koren,vector<int>& v1) {
	stack<Cvor*> S;
	Cvor* trenutni = koren;
	while (trenutni != nullptr || S.empty() == false) {
		while (trenutni != nullptr) {
			S.push(trenutni);
			trenutni = trenutni->levisin;
		}
		trenutni = S.top();
		S.pop();
		v1.push_back(trenutni->datavalue);
		trenutni = trenutni->desnisin;
	}
}

void InOrder_pretraga(Cvor* koren) {
	stack<Cvor*> S;
	Cvor* trenutni = koren;
	while (trenutni != nullptr || S.empty()==false) {
		while (trenutni != nullptr) {
			S.push(trenutni);
			trenutni = trenutni->levisin;
		}
		trenutni = S.top();
		S.pop();
		cout << trenutni->datavalue<<endl;
		trenutni = trenutni->desnisin;
	}

}
int Cvor::getVisina(Cvor* cvor) {
	if (cvor == nullptr) return 0;
	return cvor->visina;
}
void checkHeight(Cvor* cvor) {
	cvor->visina = 1 + max(Cvor::getVisina(cvor->levisin), Cvor::getVisina(cvor->desnisin));
}
int Cvor::getBalans(Cvor* cvor) {
	if (cvor == nullptr) return 0;
	return getVisina(cvor->levisin) - getVisina(cvor->desnisin);
}

Cvor* lrotacija(Cvor* cvor) {
	Cvor* temp = cvor->desnisin;
	Cvor* tempsinoddesnog = temp->levisin;
	temp->levisin = cvor;
	cvor->desnisin = tempsinoddesnog;
	checkHeight(cvor);
	checkHeight(temp);
	return temp;
}

Cvor* drotacija(Cvor* cvor) {
	Cvor* temp = cvor->levisin;
	cvor->levisin = temp->desnisin;
	temp->desnisin = cvor;
	checkHeight(cvor);
	checkHeight(temp);
	return temp;

}



Cvor* Cvor::ubaci_vrednost(Cvor*& koren, int value) {
	if (koren == nullptr) {
		koren = new Cvor(value);
		koren->desnisin = nullptr;
		koren->levisin = nullptr;
		return koren;
	}
	Cvor* trenutni = koren;
	Cvor* prethodni = trenutni;
	stack<Cvor*> put;
	while (trenutni != nullptr) {
		put.push(trenutni);
		prethodni = trenutni;
		if (value > trenutni->datavalue) trenutni = trenutni->desnisin;
		else trenutni = trenutni->levisin;
	}
	if (value < prethodni->datavalue) prethodni->levisin = new Cvor(value);
	else if (value > prethodni->datavalue) prethodni->desnisin = new Cvor(value); 
	
	while (put.empty() == false) {
		trenutni = put.top();
		put.pop();
		checkHeight(trenutni);
		int balans = getBalans(trenutni);
		if (balans > 1 && getBalans(trenutni->levisin) >= 0) {
			int s = 0;
			if (trenutni == koren) s = 1;
			trenutni = drotacija(trenutni);
			if (!s) put.top()->levisin = trenutni;
			if (s) koren = trenutni;
		}
		else if (balans > 1 && getBalans(trenutni->levisin) < 0) {
			int s = 0;
			if (trenutni == koren) s = 1;
			Cvor* tmp2 = trenutni->levisin;
			tmp2 = lrotacija(tmp2);
			trenutni->levisin= tmp2; 





			trenutni = drotacija(trenutni);
			if (!s) put.top()->levisin = trenutni;
			if (s) koren = trenutni;
		}
		if (balans < -1 && getBalans(trenutni->desnisin) <= 0) {
			int s = 0;
			if (trenutni == koren) s = 1;
			trenutni = lrotacija(trenutni);
			if (!s) put.top()->desnisin = trenutni;
			if (s) koren = trenutni;
		}
		else if (balans < -1 && getBalans(trenutni->desnisin) > 0) {
			int s = 0;
			if (trenutni == koren) s = 1;
			Cvor* tmp2 = trenutni->desnisin;
			tmp2 = drotacija(tmp2);
			trenutni->desnisin = tmp2;



			trenutni = lrotacija(trenutni);
			if (!s) put.top()->desnisin = trenutni;
			if (s) koren = trenutni;


		}
		if (trenutni == koren) return trenutni;
	}
	



}



int faktorijel(int broj)  {
	int suma = 1;
	for (int i = 1; i <= broj; i++) suma *= i;
	return suma;
}

int izracunaj_binomni(int brojiznad, int brojispod) {
	int rezultat;
	if (brojiznad == 0 && brojispod==1) return 0;
	rezultat = faktorijel(brojiznad) / (faktorijel(brojispod) * faktorijel(brojiznad - brojispod));
	return rezultat;
}

int binarna_pretraga(vector<int> niz, int key) {
	cout << "Koraci za binarnu pretragu:" << endl;
	brkorakabin = 0;
	int high = ceil(niz.size()/2.0)-1;
	int low = 0;
	while (low <= high) {
		brkorakabin++;

		int mid = (low + high) / 2;
		cout << "Mid je :" << mid <<" Br koraka: "<<brkorakabin<< endl;
		if (niz[mid] == key) return mid;

		else if (key < niz[mid]) high = mid - 1;
		else if (key > niz[mid]) low = mid + 1;
		
	}
	return -1;

}

int ternarna_pretraga(vector<int> niz, int key) {
	cout << "Koraci za ternarnu pretragu:" << endl;
	brkorakatern = 0;
	int high = ceil(niz.size() / 2.0)-1;
	int low = 0;
	while (low <= high) {
		//int prvimid = (low + high) / 3;
		//int drugimid = 2 * prvimid;
		int prvimid = low + (high - low) / 3;
		int drugimid = high - (high - low) / 3;
		cout << "Prvi mid je :" << prvimid << " Drugi mid je :" << drugimid <<" Br koraka: "<<brkorakatern<<endl;
		if (niz[prvimid] == key) {
			brkorakatern++; return prvimid;
		}
		if (niz[drugimid] == key) {
			brkorakatern++; return drugimid;
		}
		if (key < niz[prvimid]) high = prvimid - 1;
		else if (key > niz[drugimid]) low = drugimid + 1;
		else {
			low = prvimid + 1;
			high = drugimid - 1;
		}
	}
	return -1;

}


int main() {
	char c;
	vector<int> niz;
	while (1) {
		cout << "IZABERITE JEDNU OD OPCIJA:" << endl;
		cout << "1)Unos rednog broja reda Lozanicevog trougla i generisanje sekvence" << endl;
		cout << "2)Pokretanje i ispis koraka pretrage" << endl;
		cout << "3)Ispis rezultata i poredjenje performansi" << endl;
		cout << "4)Zavrsi prvi deo domaceg i predji na drugi" << endl;
		cin >> c;
		if (c == '1') {
			niz.clear();
			int rednibrojreda;
			cout << "Unesite redni broj reda:" << endl;
			cin >> rednibrojreda;
			for (int i = 0; i < rednibrojreda + 1; i++) {
				if (i == 0 || i == rednibrojreda) {
					cout << 1; niz.push_back(1);
				}
				else {
					int element = (izracunaj_binomni(rednibrojreda, i) + izracunaj_binomni(rednibrojreda % 2, i % 2) * izracunaj_binomni(floor(rednibrojreda / 2), floor(i / 2)));
					cout << element/2;
					niz.push_back(element/2);
					
				}
				
				if (i != rednibrojreda) putchar(' ');
			}
		}
		if (c == '2') {
			int key;
			cout << "Koji kljuc zelite da pretrazite od datih?" << endl;
			if (!niz.empty())for (int i = 0; i < niz.size(); i++) cout << niz[i]<<' ';
			else cout << "Niste uneli ni jedan red Lozanicevog trougla!!";
			cout << endl;
			cin >> key;
			binarna_pretraga(niz, key);
			cout << endl;
			ternarna_pretraga(niz, key);
			cout<< endl;

		}
		if (c == '3') {
			cout << endl;
			cout << "Ukupan broj koraka bin. pretrage:" << brkorakabin << endl;
			cout << "Ukupan broj koraka tern. pretrage:" << brkorakatern << endl;
			
			if (brkorakabin > brkorakatern) cout << "Ternarna pretraga je brza za:" << (100-(brkorakatern / (double)brkorakabin) * 100) << " procenata" << endl;
			else if (brkorakabin == brkorakatern) cout << "Jednako su brze pretrage.";
			else { cout << "Binarna pretraga je brza za:" << (100 - (brkorakabin / (double)brkorakatern) * 100) << " procenata" << endl; }
		}



		if (c == '4') break;
		cout << endl;

		
	}

	// DRUGI DEO DOMACEG!
	Cvor* skupA=nullptr;
	Cvor* skupB=nullptr;
	char tmpchar;
	int tmp;
	while (1) {
		cout << "IZABERITE JEDNU OD OPCIJA:" << endl;
		cout << "1)Formiranje praznog skupa" << endl;
		cout << "2)Umetanje novog elementa u skup" << endl;
		cout << "3)Provera pripadnost elementa skupu" << endl;
		cout << "4)Formatiran ispis sadrzaja stabla koji predstavlja skup" << endl;
		cout << "5)Brisanje skupa iz memorije" << endl;
		cout << "6)Simetricna razlika A i B"<<endl;
		cout << "7)Kraj programa" << endl;
		cin >> c;
		if (c == '1') {
			if (skupA != nullptr) {

				InOrder_pretragaCL(skupA);
				skupA = nullptr;
			}
			if (skupB != nullptr){
				InOrder_pretragaCL(skupB);
				skupB = nullptr;
			}

			cout << "Formirani su prazni skupovi A i B !" << endl;
		}
		if (c == '2') {
			
			cout << "U koji skup zelite da ubacite element ? (A or B) "<<endl;
			cin >> tmpchar;
			cout << "Koju vrednost zelite da ubacite?" << endl;
			cin >> tmp;
			if (tmpchar == 'A') skupA->ubaci_vrednost(skupA, tmp);
			else if (tmpchar == 'B') skupB->ubaci_vrednost(skupB, tmp);
		}
		if (c == '3') {
			cout << "Za koji skup zelite da proverite element ? (A or B) " << endl;
			cin >> tmpchar; 
			cout << "Koju vrednost zelite da proverite?" << endl;
			cin >> tmp;
			if (tmpchar == 'A') {
				if (InOrder_pretragaPR(skupA, tmp)) cout << "Element postoji u skupu!" << endl;
				else cout << "Element ne postoji u skupu!" << endl;
			}
			else if (tmpchar == 'B') {
				if (InOrder_pretragaPR(skupB, tmp)) cout << "Element postoji u skupu!" << endl;
				else cout << "Element ne postoji u skupu!" << endl;
			}
		}
		if (c == '4') {
			cout << "Koji skup zelite da printujete (A or B) " << endl;
			cin >> tmpchar;
			if (tmpchar == 'A') {
				if (skupA == nullptr) cout << "A ne postoji" << endl;
				else {
					lepPrint(skupA,0);
					cout << endl;
				}
			}
			if (tmpchar == 'B') {
				if (skupB == nullptr) cout << "B ne postoji" << endl;
				else {
					lepPrint(skupB,0);
					cout << endl;
				}
			}

		}
		if (c == '5') {
			if (skupA != nullptr) {
				InOrder_pretragaCL(skupA);
				skupA = nullptr;
			}
			if (skupB != nullptr) {
				InOrder_pretragaCL(skupB);
				skupB = nullptr;
			}

		}
		if (c == '6') {
			Cvor* skupC = nullptr;
			vector<int>v1;
			vector<int>v2;
			InOrder_pretragaSR(skupA,v1);
			InOrder_pretragaSR(skupB,v2);
			vector<int>v3;
			set_symmetric_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(v3));
			for (int i : v3) skupC->ubaci_vrednost(skupC, i);

			cout << endl;
			lepPrint(skupC, 0);
			/*
				int g=0;
				for (int i:v1){
					g=0;
					for (int j:v2){
						if (i==j) g=1; 
					}
					if (!g) skupC->ubaci_vrednost(skupC,i);
				}
				for (int i:v2){
					g=0;
					for (int j:v1){
						if (i==j) g=1;
					}
					if (!g) skupC->ubaci_vrednost(skupC,i);
				}
			*/
		}


		if (c == '7') break;
	}



	return 0;
}