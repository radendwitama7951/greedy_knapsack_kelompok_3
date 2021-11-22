/* Program Permasalahan Knapsack
 * by Raden Dwitama Baliano
 * 19/9/2021
 *
 * */

/* PEMBAHASAN
 *
 * Faktorial Knapsack Problem
 * ciri-ciri
 * 1. Memiliki permasalahan berupa memilih objek-objek dengan batasan kapasitas
 * 2. Mencari kombinasi optimal dalam memilih objek-objek dengan batasan kapasitas
 * 3. Objek memiliki nilai alias profit
 * 4. Objek dan kapasitas dapat dinyatakan dalam satuan kontinyu (cth. Kg, Jam, Km, dsb.)
 *
 *
 * */

/* PERMASALAHAN
 *
 * Suatu kargo mempunyai kapasitas 100 TON. Ransel tersebut akan digunakan untuk memuat barang-barang
 * dengan berat masing-masing (W1, ..., W60) = (14, . . . , 4)
 * dan profitnya (P1, ...,P60) = (20500, . . ., 16000).
 * Tentukan kombinasi barang-barang yang dimuat 60 mempunyai profit yang max.
 *
 *
* */

/* PENYELESAIAN
 *
 * ... (Analisis kenapa permasalahan diatas merupakan permasalahan Knapsack)
 *
 * Data-data yang dimiliki dari permasalahan diatas yaitu
 *
 * Katakan : 
 * * jumlah data = n = 60
 * * kapasitas kargo = M = 100 TON
 * * Profit tiap-tiap barang = P
 * * Berat tiap-tiap barang = W
 * * perbandigan antara profit (P) dengan berat (W) = density = P/W
 * * Barang = {X | X barang-barang yang akan dimuat} = (X1,...,X6)
 * * solusi = x = {x | x faktor solusi optimal tiap-tiap barang} = (x1,...,x6)
 *
 * Diketahui :
 * * (P1,...,P6) = (25, 18, 22, 13, 8, 15)
 * * (W1,...,W2) = (10, 8, 25, 12, 16, 30)
 *
 * Tentukan x !
 *
 *
 * */

#define FILEPATH "data/data_barang_distribusi.csv"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Bagian ini merepresentasikan jumlah barang (n)
 * dan Kapasitas (M)
 *
 * */
int n = 60;
double M = 100;

/* barang_t akan menjadi template untuk tiap-tiap
 * instance barang kedepannya
 *
 * Tiap-tiap barang akan memiliki variabel
 * W, P, density, x, dan X
 *
 * */
struct barang_t {
	double W, P, density, x;
	int X;
};



/* Tiap-tiap barang nanti akan dimasukkan kedalam himpunan dengan nama himpunan "Barang" (array Barang)
 *
 * Prosedur insert barang bertugas untuk memasukkan barang-barang ke dalam himpunan
 * berdasarkan parameter yang telah ditentukan.
 *
 * */
void insert_barang (struct barang_t *Barang, double W, double P, int N) {
	Barang[N].W = W;
	Barang[N].P = P;
	Barang[N].density = P/W;
	Barang[N].X = N;
	Barang[N].x = 0;	// x di-set 0 untuk setiap solusi dari X karena solusi ditentukan oleh prosedur lain
}


/* Untuk mempermudah pemahaman, prosedur showall_barang dibuat untuk
 * menampilkan seluruh data yang dimasukkan
 *
 * */
void showall_barang (struct barang_t *Barang) {
	printf("%4s\t%10s\t%10s\t%10s\t%10s\n", "Barang", "W", "P", "density", "tsolution");
	for (int i = 1; i <= n; i++) {
	       printf("X[%d]\t%10.0lf \t%10.0lf\t%10.2lf\t%10.2lf\n", Barang[i].X, Barang[i].W, Barang[i].P, Barang[i].density, Barang[i].x);
	}
}

/* Dalam bahasa C, ada prosedur standar yang dapat mengurutkan set/ himpunan menggunakan algoritma quick sort (qsort)
 * Fungsi sort_by_density_desc diperlukan sebagai parameter dalam prosedur qsort
 *
 * sort_by_density_desc akan mengurutkan set Barang dalam urutan descending berdasarkan densitynya
 *
 * */
int sort_by_density_desc (const void *a, const void *b) {
	struct barang_t *objek_a = (struct barang_t*) a;
	struct barang_t *objek_b = (struct barang_t*) b;


	if (objek_a->density > objek_b->density )
		return -1;
	else if (objek_a->density < objek_b->density)
		return 1;
	else
		return 0;

}

/* Prosedur sort_by_identity_asc akan mengurutkan set Barang dalam urutan ascending berdasarkan nilai X pada properti
 *
 * */
int sort_by_identity_asc (const void *a, const void *b) {
	struct barang_t *objek_a = (struct barang_t*) a;
	struct barang_t *objek_b = (struct barang_t*) b;

	
	if (objek_a->X < objek_b->X )
		return -1;
	else if (objek_a->X > objek_b->X)
		return 1;
	else
		return 0;

}

///
/* Prosedur greedy_kanpsack merupakan prosedur utama yang akan mencari solusi bagi permasalahan.
 * Algoritma prosedur knapsack yaitu sebagai berikut:
 *
 * PROCEDUR GREEDY KNAPSACK (Barang[])
 * INTEGER Barang[X:n];
 * REAL Barang[W:n], Barang[x:n], cu, M;
 *
 * sort(Barang descending order by density)
 * cu := M
 * INTEGER i TO n DO
 * 	IF (Barang[W:i] < cu) THEN 
 * 		Barang[x:i] := 1
 * 		cu := cu - Barang[W:i]
 * 	ELSE BREAK ENDIF
 * 	REPEAT;
 * 	
 * 	IF i <= n THEN
 * 		Barang[x:i] := cu/ Barang[W:i];
 * 	ENDIF
 *
 * END GREEDY KNAPSACK
 *
 * */
void greedy_knapsack (struct barang_t *Barang) {
	double cu;
	int i;
	qsort(Barang, n+1, sizeof(struct barang_t), sort_by_density_desc);
	cu = M;

	for (i = 1; i <= n; i++) {
		if (Barang[i].W < cu) {
			Barang[i].x = 1;
			cu -= Barang[i].W;
		} else
			break;
	
	}

	if (i <= n) {
		Barang[i].x = cu/Barang[i].W;
	}



}

/* Prosedur untuk membaca File .csv
 *
 *
 * */
void get_data_barang_distribusi (struct barang_t *Barang) {
	FILE *fp = fopen(FILEPATH, "r");
	if (!fp) {
		printf("Gagal membuka file %s !\n\n", FILEPATH);
		exit(EXIT_FAILURE);
	} else {
	
		int row, counter;
		counter = 0;

		fscanf(fp, "%*[^\n]");
		while (1) {
				row = fscanf(fp, "%d, %lf, %lf", &Barang[counter].X, &Barang[counter].W, &Barang[counter].P);
				if (row == 3) {
					Barang[counter].density = Barang[counter].P/ Barang[counter].W;
					Barang[counter].x = 0;
					counter++;					
				} else if (row != EOF) {
					fprintf(stderr, "Format %s tidak valid !\n%s\n", FILEPATH, strerror(errno));
					exit(EXIT_FAILURE);
				} else {
					fprintf(stdout, "Data distribusi berhasil dibaca !\n");
					break;
				};
			}

	}

}



 /*======= main =========*/
int main (void) {

	// Array Barang (Barang[])
	// Perhatikan ukuran = n+1 = 7
	// dibuat n+1 karena array dimulai dari indeks 0, maka
	// agar tiap indeks ke i merepresentasikan X, indeks 0 diabaikan
	// diisi W = 1 dan P = 999 agar selalu berada pada posisi pertama
	// (supaya tidak terpengaruh oleh sorting by density)
	struct barang_t Barang[n+1];
	
	// format : insert (Array Barang, weight (W), profit (P), identitas (X))
//	insert_barang(Barang, 1, 100000, 0);
	/*
	insert_barang(Barang, 1, 999, 0);
	insert_barang(Barang, 10, 25, 1);
	insert_barang(Barang, 8, 18, 2);
	insert_barang(Barang, 25, 22, 3);
	insert_barang(Barang, 12, 13, 4);
	insert_barang(Barang, 16, 8, 5);
	insert_barang(Barang, 30, 15, 6);
	*/
	printf("Proccessing...\n");

	// Membaca file data/barang_distribusi.csv
	get_data_barang_distribusi(Barang);

	// format : show (Array Barang)
	showall_barang(Barang);

	// format : greedy knapsack (Array Barang)
	greedy_knapsack(Barang);

	printf("\n\n");

	// format : qsort (Array barang, panjang array (n+1), ukuran objek barang_t, fungsi komparasi (mempengaruhi urutan))
	//qsort(Barang, n+1, sizeof(struct barang_t), sort_by_identity_asc);

	// Semua Barang setelah dicari solusinya
	printf("Distribusi solusi:\n");
	showall_barang(Barang);
	printf("\n\n");

	// kode dibawah berfungsi untuk menampilkan hasil akhir
	printf("solusi (P/W): (X1, ..., X6) = (");

	// variabel total_berat dan total_profit berfungsi untuk
	// menampung nilai dari solusi profit / berat (P/W) yang didapatkan oleh program
	double profit, total_profit, berat;
       	total_profit = profit = berat = 0;

	// total berat = SUM(solusi barang ke-x dengan weight barang)
	// total profit = SUM(solusi barang ke-x dengan profit barang)
	for (int i = 1; i <= n; i++) {
		total_profit += Barang[i].P;
		berat += Barang[i].x * Barang[i].W;
		profit += Barang[i].x * Barang[i].P;
		printf("%.2lf%s ", Barang[i].x, i != n ?  ", ": "");
	}
	printf(")\nProfit : %.2lf/ %.2lf\nBerat : %.2lf\n\n", profit, total_profit, berat);

	/* PERHATIAN
	 * 
	 * Perhatikan solusi akhir (1.00, 1.00, 1.00, 1.00, 0, 0.33)
	 * solusi diatas bukan satu-satunya solusi optimal dari permasalahan ini
	 * perhatikan jika solusi akhir adalah (1.00, 1.00, 1.00, 1.00, 0.63, 0)
	 * juga solusi optimal yang valid
	 * 
	 *
	 * */

	/* ANALISIS KOMPLEKSITAS WAKTU DAN TEMPAT; SERTA PEMBUKTIAN LOGIKA
	 * ...
	 *
	 * */


	system("pause");

	return 0;


}
