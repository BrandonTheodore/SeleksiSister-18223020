#include <iostream>
#include <vector>
#include <chrono>
#include <complex>
#include <cstdint>

// Mengaktifkan implementasi library stb_image_write
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// OpenMP untuk paralelisasi
#include <omp.h>

// --- Konfigurasi Gambar dan Himpunan Mandelbrot ---
const int MAX_ITERATIONS = 1000;
const int NUM_CHANNELS = 3; // RGB

// Struktur sederhana untuk warna RGB
struct Color {
    uint8_t r, g, b;
};

// Fungsi untuk menghitung iterasi Mandelbrot untuk satu titik
int getMandelbrotIterations(const std::complex<double>& c) {
    std::complex<double> z = 0;
    int n = 0;
    while (std::abs(z) <= 2.0 && n < MAX_ITERATIONS) {
        z = z * z + c;
        n++;
    }
    return n;
}

// Fungsi untuk memetakan jumlah iterasi ke warna yang menarik
Color mapIterationToColor(int n) {
    if (n == MAX_ITERATIONS) {
        return {0, 0, 0};
    }
    uint8_t r = (n % 256);
    uint8_t g = (n * 2 % 256);
    uint8_t b = (n * 5 % 256);
    return {r, g, b};
}


int main() {
    // Alokasi memori untuk data piksel gambar
    int height, width;
    std::cout << "Masukkan resolusi gambar (lebar dan tinggi): ";
    std::cin >> width >> height;
    std::vector<uint8_t> pixels(width * height * NUM_CHANNELS);

    // ====================================================================
    // 1. IMPLEMENTASI SERIAL
    // ====================================================================
    std::cout << "Memulai rendering SERIAL..." << std::endl;
    auto start_serial = std::chrono::high_resolution_clock::now();

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            double cx = -2.0 + (double)x / width * 3.0;
            double cy = -1.5 + (double)y / height * 3.0;
            std::complex<double> c(cx, cy);

            int iterations = getMandelbrotIterations(c);
            Color color = mapIterationToColor(iterations);

            int index = (y * width + x) * NUM_CHANNELS;
            pixels[index] = color.r;
            pixels[index + 1] = color.g;
            pixels[index + 2] = color.b;
        }
    }

    auto end_serial = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_serial = end_serial - start_serial;
    std::cout << "Rendering SERIAL selesai." << std::endl;

    // Simpan gambar hasil serial
    stbi_write_png("mandelbrot_serial.png", width, height, NUM_CHANNELS, pixels.data(), width * NUM_CHANNELS);
    std::cout << "Gambar 'mandelbrot_serial.png' telah disimpan." << std::endl << std::endl;


    // ====================================================================
    // 2. IMPLEMENTASI PARALEL (dengan OpenMP)
    // ====================================================================
    std::cout << "Memulai rendering PARALEL dengan OpenMP..." << std::endl;
    auto start_parallel = std::chrono::high_resolution_clock::now();

    // Loop luar (pada baris y) diparalelkan.
    // Setiap thread akan mengerjakan sebagian baris secara independen.
    #pragma omp parallel for schedule(dynamic)
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            double cx = -2.0 + (double)x / width * 3.0;
            double cy = -1.5 + (double)y / height * 3.0;
            std::complex<double> c(cx, cy);

            int iterations = getMandelbrotIterations(c);
            Color color = mapIterationToColor(iterations);

            int index = (y * width + x) * NUM_CHANNELS;
            pixels[index] = color.r;
            pixels[index + 1] = color.g;
            pixels[index + 2] = color.b;
        }
    }

    auto end_parallel = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_parallel = end_parallel - start_parallel;
    std::cout << "Rendering PARALEL selesai." << std::endl;

    // Simpan gambar hasil paralel
    stbi_write_png("mandelbrot_parallel.png", width, height, NUM_CHANNELS, pixels.data(), width * NUM_CHANNELS);
    std::cout << "Gambar 'mandelbrot_parallel.png' telah disimpan." << std::endl << std::endl;


    // ====================================================================
    // 3. BENCHMARKING DAN SPEEDUP
    // ====================================================================
    std::cout << "--- Hasil Benchmarking ---" << std::endl;
    std::cout << "Resolusi Gambar: " << width << "x" << height << std::endl;
    std::cout << "Jumlah Thread Maksimal: " << omp_get_max_threads() << std::endl;
    std::cout << "Waktu Eksekusi Serial: " << duration_serial.count() << " detik" << std::endl;
    std::cout << "Waktu Eksekusi Paralel: " << duration_parallel.count() << " detik" << std::endl;

    double speedup = duration_serial.count() / duration_parallel.count();
    std::cout << "Speedup: " << speedup << "x" << std::endl;

    return 0;
}