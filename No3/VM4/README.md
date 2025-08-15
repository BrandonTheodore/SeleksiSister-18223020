# Konfigurasi Virtual Machine 4

## IP Statis

1. Atur IP statis dengan menggunakan command sudo nano /etc/network/inferfaces
2. Buatlah konfigurasi file interfaces seperti yang tertera pada file inferfaces_vm4.txt
3. Terapkan konfigurasi dengan command sudo systemctl restart networking.service

## Reverse Proxy

1. Install library requests pada python3 dengan command ```sudo apt install python3-requests```
2. Buatlah file proxy.py yang isinya sama dengan file proxy.py yang tertera pada folder ini
3. Jalankan reverse proxy dengan command ```sudo python3 proxy.py```
