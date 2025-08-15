# Konfigurasi Virtual Machine 2

## IP Statis

1. Atur IP statis dengan menggunakan command sudo nano /etc/network/inferfaces
2. Buatlah konfigurasi file interfaces seperti yang tertera pada file inferfaces_vm2.txt
3. Terapkan konfigurasi dengan command sudo systemctl restart networking.service

## Apache

1. Install apache dengan command ```sudo apt install apache2```
2. Buatlah halaman html pada /var/www/html/index.html, halaman ini dibebaskan, namun aku menggunakan halaman sederhana seperti yang tertera di file index.html pada folder ini
3. Ubah port ke 8080 dengan mengedit /etc/apache2/ports.conf (ubah Listen 80 menjadi Listen 8080) dan juga pada file /etc/apache2/sites-available/000-default.conf (ubah <VirtualHost *:80> menjadi <VirtualHost *:8080>).
4. Lakukan restart terhadap apache dengan command ```sudo systemctl restart apache2```
