// developed by Muhammad Insan Kamil and Ari Nurcahya
// for Free
// Made in Indonesia

#include <iostream>
#include <math.h>
#include <iomanip>
#include <vector>

// selanjutnya mencari kuartil dan deviasi

using namespace std;

class Statistik{
	public:
		Statistik(){
			banyak = 0;
			cout << "Masukan data : " << endl;
			int i = 0;
			int temp;
			while(true){
				banyak++;
				cout << i+1 << " : ";
				cin >> temp;
				datax.push_back(temp);
				if(datax[i] < 0){
					datax.pop_back();
					i--;	
				} 
				if(i == 0) smallest = datax[i];
				if(datax[i] == 0) break;
				if(largest < datax[i]) largest = datax[i];
				if(smallest > datax[i]) smallest = datax[i];
				i++;
			}
			banyak--;
		}
		
		~Statistik(){
			cout << "\n\nDIMOHON PERIKSA TERLEBIH DAHULU JIKA ADA KESALAHAN DALAM PERHITUNGAN." << endl;
			cout << "TERUS LAPOR YAAA KALAU ADA YANG SALAH " << endl;
		}
		
		void tampilDatax();
		void mencariKRC();
		void mencariIntervalKelas();
		void mencariFrequensi();
		void mencariNilaiRerataKelas();
		void mencariFiKaliXi();
		void mencariMean();
		void mencariModus();
		void mencariMedian();
		void mencariQuartil();
	private:
		vector<int> datax; 
		vector<int> frequensiKelas;
		int banyak; // digunakan pada konstruktor
		int totalFrequensi; // digunakan pada mencariFrequensi()
		float K, R, C; // digunakan pada mencariKRC()
		float Q1, Q2, Q3;
		float Lk1, Lk2, Lk3;
		float largest, smallest; // digunakan pada mencariKRC() dan Konstruktor
		float totalFiXi; // digunakan pada mencariFiKaliXi()
		float modus; // digunakan pada mencariModus()
		float mean; // digunakan pada mencariMean()
		float median; // digunakan pada mencariMedian()
		vector<float> dataRataKelas; // digunakan pada mencariNilaiRerataKelas()
		vector<float> dataTepiAtas; // digunakan pada mencariIntervalKelas()
		vector<float> dataTepiBawah; // digunakan pada mencariIntervalKelas()
		vector<float> dataFiXi; // digunakan pada mencariFiKaliXi()
		vector<float> frequensiKumulatif; // digunakan pada mencariMedian()
		vector<float> frequensiRelatif;
};

void Statistik::tampilDatax(){
	for(int i = 0; i < banyak; i++){
		cout << datax[i] << " ";
	}
	cout << endl << banyak;
}

void Statistik::mencariKRC(){
	system("cls");
	K = 1 + (3.322 + log10(banyak));
	K = ceil(K);
	
	cout << "K = 1" << " + (3.322 + log" << banyak << ")" << endl;
	cout << "K = 1" << " + (3.322 + " << log10(banyak) << ")" << endl;
	cout << "K = " << K << endl;
		
	R = largest - smallest;
	cout << "R = " << largest << " - " << smallest << " = " << R << endl;
	
	C = R / K;
	C = ceil(C);
	cout << "C = " << R << "/" << K << endl;
	cout << "C = " << C << endl;
}

void Statistik::mencariIntervalKelas(){
	float dtb = smallest - 0.5;
	float dta = dtb + C;
	cout << "\nInterval Kelas" << setw(10);
	for(int i=0; i<K; i++){	
		dataTepiBawah.push_back(dtb);
		dataTepiAtas.push_back(dta);
		
		cout << dataTepiBawah[i] << " - " << dataTepiAtas[i] << setw(10);
		dtb = dta;
		dta += C;
	}
}

void Statistik::mencariFrequensi(){
	totalFrequensi = 0;
	
	for(int i=0; i<K; i++){
		int k = 0;
		for(int j=0; j<banyak; j++){
			if(datax[j] > dataTepiBawah[i] && datax[j] < dataTepiAtas[i]) k++;
		}
		frequensiKelas.push_back(k);
	}
	
	cout << "\nFrequensi Kelas (Fi) : " << setw(10);
	for(int i=0; i<K; i++) cout << frequensiKelas[i] << setw(10);
	
	cout << "\nTotal : ";
	for(int i=0; i<K; i++) totalFrequensi+=frequensiKelas[i];
	cout << totalFrequensi;
}

void Statistik::mencariNilaiRerataKelas(){
	cout << "\nRata-rata Kelas (Xi) : " << setw(10);
	for(int i=0; i<K; i++){
		dataRataKelas.push_back((dataTepiBawah[i] + dataTepiAtas[i]) / 2); 
		
		cout << dataRataKelas[i] << setw(10);
	}
	
	cout << endl;
}

void Statistik::mencariFiKaliXi(){
	float temp;
	totalFiXi = 0;
	cout << "Total Nilai Fi * Xi : " << setw(10);
	for(int i=0; i<K; i++){
		temp = dataRataKelas[i] * frequensiKelas[i];
		dataFiXi.push_back(temp);
		totalFiXi += dataFiXi[i];
		cout << dataFiXi[i] << setw(10);
	}
	cout << "\nTotal Fi * Xi : " << totalFiXi << endl;
}

void Statistik::mencariMean(){
	mean = totalFiXi / totalFrequensi;
	
	cout << "\nMean = " << totalFiXi << " / " << totalFrequensi << endl;
	cout << "Mean = " << setprecision(4) << mean << endl << endl;
}

void Statistik::mencariMedian(){
	int temp;
	int posisi;
	float setengah;
	float Lmd, F, Fmd;
	
	temp = 0;
	
	setengah = totalFrequensi / 2;
	
	frequensiKumulatif.push_back(0);

	for(int i=0; i<K; i++){
		temp += frequensiKelas[i];
		frequensiKumulatif.push_back(temp);
	}

	for(int i=0; i<K-1; i++){
		if( setengah > frequensiKumulatif[i] && setengah < frequensiKumulatif[i+1]) Lmd = dataTepiBawah[i]; 
	}
	
	for(int i=0; i<K; i++){
		if(Lmd == dataTepiBawah[i]){
			Fmd = frequensiKelas[i];
			posisi = i;	
		} 
	}
	
	if(posisi != 0){
		F = frequensiKelas[posisi-1];
		for(int i=posisi-2; i>=0; i--){
			F += frequensiKelas[i];
		}	
	} 
	else F = Fmd;
	
//	cout << "Total Kumulatif : " << temp << endl;

	median = Lmd + (((setengah - F) / Fmd ) * C);
	cout << "Median = " << Lmd << " + ((( " << setengah << " - " << F << ") / " << Fmd << " ) * " << C << ")" << endl;
	cout << "Median = " << Lmd << " + " << (((setengah - F) / Fmd ) * C) << endl;
	cout << "Median = " << setprecision(4) << median << endl;
}

void Statistik::mencariModus(){
	int posisi;
	int terbanyak;
	float a, b;
	terbanyak = frequensiKelas[0];
	posisi = 0;
	
	for(int i=0; i<K; i++){
		if(frequensiKelas[i] > terbanyak) {	
			terbanyak = frequensiKelas[i];
			posisi = i;
		}
	}
	if(frequensiKelas[posisi] != frequensiKelas[0]) a = frequensiKelas[posisi] - frequensiKelas[posisi-1];
	else a = frequensiKelas[posisi];
	if(frequensiKelas[posisi] != frequensiKelas[K-1]) b = frequensiKelas[posisi] - frequensiKelas[posisi+1];
	else b = frequensiKelas[posisi];
	
	modus = dataTepiBawah[posisi] + (a / (a + b) * C);
	
	cout << "\nModus = " << dataTepiBawah[posisi] << " + ( " << a << " / ( " << a << " + " << b << ") * " << C << ")" << endl;
	cout << "Modus = " << dataTepiBawah[posisi] << " + " << (a /(a + b) * C) << endl;
	cout << "Modus = " << setprecision(4) << modus << endl;
}

void Statistik::mencariQuartil(){
	
	float cariKelasQ1, cariKelasQ2, cariKelasQ3;
	int Fk1, Fk2, Fk3;
	int posisi1, posisi2, posisi3;
	int F1, F2, F3;
	
	cariKelasQ1 = totalFrequensi/4;
	cariKelasQ2 = totalFrequensi / 2;
	cariKelasQ3 = totalFrequensi * (3 / (float) 4);
	cout << endl << cariKelasQ1 << " " << cariKelasQ2 << " " << cariKelasQ3 << endl;
	
	for(int i=0; i<K-1; i++){
		if( cariKelasQ1 > frequensiKumulatif[i] && cariKelasQ1 < frequensiKumulatif[i+1]) Lk1 = dataTepiBawah[i]; 
		if( cariKelasQ2 > frequensiKumulatif[i] && cariKelasQ2 < frequensiKumulatif[i+1]) Lk2 = dataTepiBawah[i];
		if( cariKelasQ3 > frequensiKumulatif[i] && cariKelasQ3 < frequensiKumulatif[i+1]) Lk3 = dataTepiBawah[i];
	}
	
	for(int i=0; i<K; i++){
		if(Lk1 == dataTepiBawah[i]){
			Fk1 = frequensiKelas[i];
			posisi1 = i;	
		} 
	}
	
	for(int i=0; i<K; i++){
		if(Lk2 == dataTepiBawah[i]){
			Fk2 = frequensiKelas[i];
			posisi2 = i;	
		} 
	}
	
	for(int i=0; i<K; i++){
		if(Lk3 == dataTepiBawah[i]){
			Fk3 = frequensiKelas[i];
			posisi3 = i;	
		} 
	}
	
	if(posisi1 != 0){
		F1 = frequensiKelas[posisi1-1];
		for(int i = posisi1-2; i>=0; i--){
			F1 += frequensiKelas[i];
		}	
	} 
	else F1 = Fk1;

	if(posisi2 != 0){
		F2 = frequensiKelas[posisi2-1];
		for(int i = posisi2-2; i>=0; i--){
			F2 += frequensiKelas[i];
		}	
	} 
	else F2 = Fk2;
	
	if(posisi3 != 0){
		F3 = frequensiKelas[posisi3-1];
		for(int i = posisi3-2; i>=0; i--){
			F3 += frequensiKelas[i];
		}	
	} 
	else F3 = Fk3;	
	
	Q1 = Lk1 + (((cariKelasQ1 - F1) / Fk1) * C);
	Q2 = Lk2 + (((cariKelasQ2 - F2) / Fk2) * C);
	Q3 = Lk3 + (((cariKelasQ3 - F3) / Fk3) * C);
	
	cout << "Q1 = " << Lk1 << " + (( " << cariKelasQ1 << " - " << F1 << " / " << Fk1 << " ) *" << C << " )" << endl;
	cout << "Q1 = " << Lk1 << " + " << ((cariKelasQ1 - F1 / Fk1) * C) << endl;
	cout << "Q1 = " <<  Q1 << endl;
	
	cout << "\nQ2 = " << Lk2 << " + (( " << cariKelasQ2 << " - " << F2 << " / " << Fk2 << " ) *" << C << " )" << endl;
	cout << "Q2 = " << Lk2 << " + " << ((cariKelasQ2 - F2 / Fk2) * C) << endl;
	cout << "Q2 = " << Q2 << endl;
	
	cout << "\nQ3 = " << Lk3 << " + (( " << cariKelasQ3 << " - " << F3 << " / " << Fk3 << " ) *" << C << " )" << endl;
	cout << "Q3 = " << Lk3 << " + " << ((cariKelasQ3 - F3 / Fk3) * C) << endl;
	cout << "Q3 = " << Q3 << endl;
	
//	cout << endl << Lk1 << " " << Lk2 << " " << Lk3 << endl;
}

int main(){
//	cout << log10(30);
	Statistik A;
	A.mencariKRC();
	A.mencariIntervalKelas();
	A.mencariFrequensi();
	A.mencariNilaiRerataKelas();
	A.mencariFiKaliXi();
	A.mencariMean();
	A.mencariMedian();
	A.mencariModus();
	A.mencariQuartil();
	
	
	return 0;
}
