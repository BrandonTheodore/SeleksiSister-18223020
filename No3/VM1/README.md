# Konfigurasi Virtual Machine 1

## IP statis

1. Atur IP statis dengan menggunakan command ```sudo nano /etc/network/inferfaces```
2. Buatlah konfigurasi file interfaces seperti yang tertera pada file inferfaces_vm1.txt
3. Terapkan konfigurasi dengan command ```sudo systemctl restart networking.service```

## BIND9

1. Install bind9 dengan ```sudo apt install bind9```
2. Edit named.conf.local dengan command ```nano /etc/bind/named.conf.local```
3. Buatlah konfigurasi file named.conf.local seperti yang tertera pada file named.conf.local pada folder ini
4. Buatlah (atau edit bila sudah ada) file db.jarkom.local dengan command ```sudo nano /etc/bind/db.jarkom.local```
5. Buatlah konfigurasi file db.jarkom.lokal seperti yang tertera pada file db.jarkom.local pada folder ini
6. Terapkan konfigurasi dengan command ```sudo systemctl restart bind9```
7. Lalu uji coba dengan command ```nslookup jarkom.local```
