# DNS

## Persiapan

1. Buat Jaringan Internal: Buka File > Tools > Network Manager di VirtualBox, buat Internal Network baru, dan beri nama. Pada pengerjaan ini aku memberi nama jarkom.
2. Buat 4 VM Debian: Gunakan image Debian.
3. Hubungkan VM ke Jaringan: Untuk setiap VM, masuk ke Settings > Network, ubah Attached to: menjadi Internal Network, dan pilih jarkom.

## Konfigurasi Virtual Machine
> Konfigurasi setiap virtual machine dapat dilihat pada README.md di masing - masing folder VM yang sudah disediakan

## Simulasi

1. Sebelum memulai simulasi pastikan Apache sudah berjalan pada VM2 dan proxy.py sudah berjalan pada VM4
2. Jalankan program anda dengan run kode python pada VM 3 dengan command ```python3 web.py jarkom.local```
3. Apabila berhasil kita dapat melihat konten website yang terdapat pada VM 2

## Tambahan
Silakan liat link [YouTube](https://youtu.be/KjY25Hbx3Wo) berikut untuk simulasi


## Note
Temporary failure in name resolution terkadang bisa terjadi karena di sistem Linux (termasuk Debian), program seperti ping atau python tidak membaca file /etc/network/interfaces secara langsung untuk mencari DNS. Sebaliknya, mereka semua melihat ke satu file pusat untuk konfigurasi DNS, yaitu /etc/resolv.conf. Pastikan file resolv.conf hanya memiliki baris ini ```nameserver 192.168.100.10```
