#include <stdio.h>

typedef unsigned long long ull;

#define MAX_LEN 2005 
#define NTT_N 4096   
#define MOD 998244353 
#define ROOT 3

ull tambah(ull a, ull b) {
    ull sisa;
tambah_loop:
    if (!b) goto tambah_end;
    sisa = (a & b) << 1;
    a = a ^ b;
    b = sisa;
    goto tambah_loop;
tambah_end:
    return a;
}

ull kurang(ull a, ull b) {
    return tambah(a, tambah(~b, 1));
}

ull kali_mod(ull a, ull b, ull m);

ull pangkat_mod(ull basis, ull eksponen, ull m) {
    ull hasil = 1;
basis_mod_loop_start:
    if (basis < m) goto basis_mod_loop_end;
    basis = kurang(basis, m);
    goto basis_mod_loop_start;
basis_mod_loop_end:;

pangkat_loop:
    if (!eksponen) goto pangkat_end;
    if (eksponen & 1) {
        hasil = kali_mod(hasil, basis, m);
    }
    eksponen = eksponen >> 1;
    basis = kali_mod(basis, basis, m);
    goto pangkat_loop;
pangkat_end:
    return hasil;
}

ull kali_mod(ull a, ull b, ull m) {
    ull hasil = 0;
mod_loop_start:
    if (a < m) goto mod_loop_end;
    a = kurang(a, m);
    goto mod_loop_start;
mod_loop_end:;

kali_loop:
    if (!b) goto kali_end;
    if (b & 1) {
        hasil = tambah(hasil, a);
        if (hasil >= m) {
            hasil = kurang(hasil, m);
        }
    }
    a = a << 1;
    if (a >= m) {
        a = kurang(a, m);
    }
    b = b >> 1;
    goto kali_loop;

kali_end:
    return hasil;
}

ull invers_mod(ull n, ull m) {
    return pangkat_mod(n, kurang(m, 2), m);
}

void ntt(ull a[], int n, int terbalik) {
    int i = 0, j = 0, k = 0;
    int len = 0, mid = 0;
    ull w, wn, t, u;

    i = 1;
bit_reversal_loop_i:
    if (i >= n) goto bit_reversal_end_i;
    j = 0;
    k = i;
    int bit = n >> 1;
bit_reversal_loop_bit:
    if (!bit) goto bit_reversal_end_bit;
    j = j | (k & 1 ? bit : 0);
    k = k >> 1;
    bit = bit >> 1;
    goto bit_reversal_loop_bit;
bit_reversal_end_bit:
    if (i < j) {
        t = a[i];
        a[i] = a[j];
        a[j] = t;
    }
    i = tambah(i, 1);
    goto bit_reversal_loop_i;
bit_reversal_end_i:


    len = 2;
main_ntt_loop_len:
    if (len > n) goto main_ntt_end_len;
    mid = len >> 1;
    ull root_inv = invers_mod(ROOT, MOD);
    wn = pangkat_mod(terbalik ? root_inv : ROOT, kurang(MOD, 1) / len, MOD);
    
    i = 0;
main_ntt_loop_i:
    if (i >= n) goto main_ntt_end_i;
    w = 1;
    j = 0;
main_ntt_loop_j:
    if (j >= mid) goto main_ntt_end_j;
    u = a[tambah(i, j)];
    t = kali_mod(w, a[tambah(tambah(i, j), mid)], MOD);
    a[tambah(i, j)] = tambah(u, t);
    if (a[tambah(i, j)] >= MOD) a[tambah(i, j)] = kurang(a[tambah(i, j)], MOD);
    
    a[tambah(tambah(i, j), mid)] = tambah(u, kurang(MOD, t));
    if (a[tambah(tambah(i, j), mid)] >= MOD) a[tambah(tambah(i, j), mid)] = kurang(a[tambah(tambah(i, j), mid)], MOD);

    w = kali_mod(w, wn, MOD);
    j = tambah(j, 1);
    goto main_ntt_loop_j;
main_ntt_end_j:
    i = tambah(i, len);
    goto main_ntt_loop_i;
main_ntt_end_i:
    len = len << 1;
    goto main_ntt_loop_len;
main_ntt_end_len:

    if (terbalik) {
        ull n_inv = invers_mod(n, MOD);
        i = 0;
scaling_loop:
        if (i >= n) goto scaling_end;
        a[i] = kali_mod(a[i], n_inv, MOD);
        i = tambah(i, 1);
        goto scaling_loop;
scaling_end:;
    }
}

typedef struct { ull quot; ull rem; } DivModResult;

DivModResult bagi_dengan_10(ull n) {
    DivModResult res;
    res.quot = 0;
    res.rem = n;
divide_loop:
    if (res.rem < 10) goto divide_end;
    res.rem = kurang(res.rem, 10);
    res.quot = tambah(res.quot, 1);
    goto divide_loop;
divide_end:
    return res;
}

int string_len(char s[]) {
    int len = 0;
len_loop:
    if (s[len] == '\0') goto len_end;
    len = tambah(len, 1);
    goto len_loop;
len_end:
    return len;
}

void balik_array(char s[], int len) {
    int i = 0;
    int j = kurang(len, 1);
    char temp;
reverse_loop:
    if (i >= j) goto reverse_end;
    temp = s[i];
    s[i] = s[j];
    s[j] = temp;
    i = tambah(i, 1);
    j = kurang(j, 1);
    goto reverse_loop;
reverse_end:;
}

// Main function
char s1[MAX_LEN], s2[MAX_LEN];
ull p1[NTT_N], p2[NTT_N];
ull hasil[NTT_N];

int main() {
    scanf("%s", s1);
    scanf("%s", s2);

    if ((s1[0] == '0' && s1[1] == '\0') || (s2[0] == '0' && s2[1] == '\0')) {
        printf("0\n");
        return 0;
    }

    int len1 = string_len(s1);
    int len2 = string_len(s2);
    
    balik_array(s1, len1);
    balik_array(s2, len2);
    
    int i = 0;
init_p1_loop:
    if(i >= NTT_N) goto init_p1_end;
    p1[i] = 0;
    i = tambah(i, 1);
    goto init_p1_loop;
init_p1_end:;

    i = 0;
init_p2_loop:
    if(i >= NTT_N) goto init_p2_end;
    p2[i] = 0;
    i = tambah(i, 1);
    goto init_p2_loop;
init_p2_end:;

    i = 0;
str_to_poly1_loop:
    if (i >= len1) goto str_to_poly1_end;
    p1[i] = kurang(s1[i], '0');
    i = tambah(i, 1);
    goto str_to_poly1_loop;
str_to_poly1_end:;
    
    i = 0;
str_to_poly2_loop:
    if (i >= len2) goto str_to_poly2_end;
    p2[i] = kurang(s2[i], '0');
    i = tambah(i, 1);
    goto str_to_poly2_loop;
str_to_poly2_end:;

    ntt(p1, NTT_N, 0);
    ntt(p2, NTT_N, 0);
    
    i = 0;
pointwise_mult_loop:
    if (i >= NTT_N) goto pointwise_mult_end;
    hasil[i] = kali_mod(p1[i], p2[i], MOD);
    i = tambah(i, 1);
    goto pointwise_mult_loop;
pointwise_mult_end:;
    
    ntt(hasil, NTT_N, 1);
    
    ull simpanan = 0;
    i = 0;
carry_loop:
    if (i >= NTT_N) goto carry_end;
    ull jumlah_sekarang = tambah(hasil[i], simpanan);
    DivModResult dm = bagi_dengan_10(jumlah_sekarang);
    hasil[i] = dm.rem;
    simpanan = dm.quot;
    i = tambah(i, 1);
    goto carry_loop;
carry_end:;
    
    int mulai_cetak = 0;
    i = kurang(NTT_N, 1);
print_loop:
    if (i < 0) goto print_end;
    if (hasil[i] != 0) {
        mulai_cetak = 1;
    }
    if (mulai_cetak) {
        printf("%llu", hasil[i]);
    }
    i = kurang(i, 1);
    goto print_loop;
print_end:
    // Menangani kasus jika hasil perkalian adalah 0, meskipun input bukan 0 (secara teori tidak mungkin untuk bilangan positif)
    if (!mulai_cetak) {
        printf("0");
    }
    printf("\n");

    return 0;
}