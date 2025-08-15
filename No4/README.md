# Mandelbrot

## Deskripsi

> Himpunan Mandelbrot adalah himpunan dua dimensi yang terdiri dari titik - titik pada suatu bidang yang kompleks dan didefinisikan oleh persamaan iteratif z_n + 1 = z_n^2 + c dimana z dan c adalah bilangan kompleks.


## Implementasi Serial
- Nested Loop: Terdapat dua loop nested loop untuk mengunjungi setiap piksel pada gambar.

- Pemetaan Koordinat: Untuk setiap piksel (x, y), koordinatnya diubah menjadi sebuah titik c di bidang bilangan kompleks.

- Perhitungan Mandelbrot: Fungsi getMandelbrotIterations dipanggil untuk titik c. Fungsi ini menjalankan iterasi z_n+1=z_n^2+c hingga nilai ∣z∣ (magnitude z) melebihi 2, atau hingga mencapai jumlah iterasi maksimum. Jumlah iterasi yang diperlukan dikembalikan.

- Pewarnaan: Nilai iterasi ini kemudian dipetakan ke sebuah warna RGB. Titik yang tidak "lolos" (mencapai iterasi maksimum) dianggap bagian dari himpunan dan diwarnai hitam. Titik lainnya diwarnai berdasarkan seberapa cepat mereka "lolos".

- Penyimpanan Piksel: Warna RGB disimpan dalam sebuah std::vector bernama pixels.

## Implementasi Paralel dengan OpemMP
- Pragma OpenMP: Terdapat perintah #pragma omp parallel for yang berfungsi sebagai instruksi untuk membuat thread yang dibagi bagi pada for loop
- Cara Kerja: OpenMP secara otomatis membagi height (1080 baris) di antara thread CPU yang tersedia. Misalnya, jika kita memiliki 8 thread, setiap thread akan mengerjakan sekitar 135 baris piksel. Karena perhitungan warna untuk setiap piksel bersifat independen dan tidak bergantung pada piksel lain, ini adalah kasus yang ideal untuk paralelisasi.

## Benchmarking dan Speedup
- Pengukuran Waktu: Library <chrono> digunakan untuk mengukur waktu eksekusi dengan presisi tinggi. Waktu dicatat sebelum dan sesudah blok kode serial dan paralel.
- Speedup (Percepatan): Ini adalah metrik kunci untuk mengukur efektivitas paralelisasi. Rumusnya adalah:

Speedup= Waktu Eksekusi Paralel/Waktu Eksekusi Serial

Sebuah speedup sebesar 7.5x, memiliki arti versi paralel 7.5 kali lebih cepat daripada versi serial. Idealnya, pada CPU dengan N core, kita mengharapkan speedup mendekati N. Namun, dalam praktiknya, angka ini seringkali sedikit lebih rendah karena adanya overhead dari manajemen thread.

## Compile and Run
Untuk melakukan compile dan run sudah disediakan script untuk melakukan hal tersebut, pastikan script sudah diberi akses eksekusi untuk dapat dijalankan, apabila belum, silakan beri akses dengan command ``` chmod 777 script.sh ``` lalu jalankan script dengan ``` ./script.sh ```

## Tabel hasil benchmarking
Berikut merupakan tabel yang dibuat berdasarkan hasil yang dilakukan ketika kode terakhir kali dijalankan. Image dibuat dengan resolusi 1920 x 1080

|              | Serial              | Paralel      |
| ---          | ---                 |              |
| Waktu        | 7.31479             | 1.26029      |
| Percepatan   | 5.80408x                           |

Hasil dapat sedikit bervariasi, untuk mencobanya secara langsung silakan jalankan script yang sudah ada.

## Hasil Mandelbrot
Hasil gambar dapat dilihat pada file .png yang ada dalam folder ini
