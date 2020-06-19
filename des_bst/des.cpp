#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <time.h>
#pragma warning(disable : 4996)

using namespace std;

class DES {
private:
    int start_permutation_table[64] = { 57,49,41,33,25,17,9,1,59,51,43,35,27,19,11,3,61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7,56,48,40,32,24,16,8,0,58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,62,54,46,38,30,22,14,6 };
    int end_permutation_table[64] = { 39,7,47,15,55,23,63,31,38,6,46,14,54,22,62,30,37,5,45,13,53,21,61,29,36,4,44,12,52,20,60,28,35,3,43,11,51,19,59,27,34,2,42,10,50,18,58,26,33,1,41,9,49,17,57,25,32,0,40,8,48,16,56,24 };
    int expansion_permutation_table[48] = { 31,0,1,2,3,4,3,4,5,6,7,8,7,8,9,10,11,12,11,12,13,14,15,16,15,16,17,18,19,20,19,20,21,22,23,24,23,24,25,26,27,28,27,28,29,30,31,0 };
    int key_permutation_1_table[56] = { 56,48,40,32,24,16,8,0,57,49,41,33,25,17,9,1,58,50,42,34,26,18,10,2,59,51,43,35,62,54,46,38,30,22,14,6,61,53,45,37,29,21,13,5,60,52,44,36,28,20,12,4,27,19,11,3 };
    int key_permutation_2_table[48] = { 13,16,10,23,0,4,2,27,14,5,20,9,22,18,11,3,25,7,15,6,26,19,12,1,40,51,30,36,46,54,29,39,50,44,32,47,43,48,38,55,33,52,45,41,49,35,28,31 };
    int block_permutation_table[32] = { 15,6,19,20,28,11,27,16,0,14,22,25,4,17,30,9,1,7,23,13,31,26,2,8,18,12,29,5,21,10,3,24 };
    int s_box_1_table[4][16] = { 14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
                                0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
                                4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
                                15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13 };
    int s_box_2_table[4][16] = { 15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
                                3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
                                0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
                                13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9 };
    int s_box_3_table[4][16] = { 10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
                                13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
                                13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
                                1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12 };
    int s_box_4_table[4][16] = { 7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
                                13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
                                10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
                                3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14 };
    int s_box_5_table[4][16] = { 2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
                                14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
                                4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
                                11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3 };
    int s_box_6_table[4][16] = { 12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
                                10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
                                9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
                                4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13 };
    int s_box_7_table[4][16] = { 4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
                                13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
                                1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
                                6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12 };
    int s_box_8_table[4][16] = { 13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
                                1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
                                7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
                                2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11 };
    int key_shifts[16] = { 1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1 };

    int key_64bit[64] = { 0 };
    int key_56bit[56] = { 0 };
    int subkeys_48bit[17][48] = { 0 };
    int input_text_plain[64] = { 0 };
    int input_text_high[17][32] = { 0 };
    int input_text_low[17][32] = { 0 };
    int expansion_text[48] = { 0 };
    int xor_text[48] = { 0 };
    int sbox_value[32] = { 0 };
    int sbox[8] = { 0 };
    int encrypted_text[64] = { 0 };

public:
    void generate_key(uint32_t size);
    void generate_subkeys();
    void encrypt_input_text();
    void encrypt_bits(int dec_or_enc);
    void feistel_function(int round, int dec_or_enc);
    void create_sboxes();
    void write_to_file(int dec_or_enc);
    int get_sboxes_value();
    void decrypt();
};

void DES::generate_key(uint32_t size) {
    fstream file;
    string read_gen_number;
    int z = 0;
    uint32_t key_low = 0;
    uint32_t key_high = 0;
    uint32_t x[10] = { 0 };
    srand(time(NULL));

    file.open("plik.txt", ios::in);
    if (file.good() == true)
    {
        while (!file.eof())
        {
            if (getline(file, read_gen_number)) {
                x[z] = stoul(read_gen_number, nullptr, 0);
                z++;
            }
        }
        file.close();
    }
    int c = rand() % size;
    key_low = x[c];
    c = rand() % size;
    key_high = x[c];
    uint64_t mask = 0x80000000;
    for (int i = 0; i < 64; i++) {
        if (i < 32) {
            if ((key_high & mask) > 0) {
                key_64bit[i] = 1;
            }
            else {
                key_64bit[i] = 0;
            }
            mask = mask >> 1;
            if (i == 31) { mask = 0x80000000; }
        }
        else {
            if ((key_low & mask) > 0) {
                key_64bit[i] = 1;
            }
            else {
                key_64bit[i] = 0;
            }
            mask = mask >> 1;
        }
    }
    file.close();
}
void DES::generate_subkeys() {
    int key_56bit_low[17][28] = { 0 };
    int key_56bit_high[17][28] = { 0 };
    int temp_key_shift[17][2] = { 0 };
    int temp_key_56bit[17][56] = { 0 };

    for(int i = 0; i < 64; i++) {
        for (int j = 0; j < 56; j++) {
            if (key_permutation_1_table[j] == i) {
                key_56bit[j] = key_64bit[i];
                break;
            }
        }
    }
    
    for (int i = 0; i < 56; i++) {
        if (i < 28) {
            key_56bit_high[0][i] = key_56bit[i];
        }
        else {
            key_56bit_low[0][i-28] = key_56bit[i];
        }
    }
    for (int i = 1; i < 17; i++) {
        int z = 0;
        for (int j = 0; j < key_shifts[i - 1]; j++) {
            temp_key_shift[i - 1][j] = key_56bit_high[i - 1][j];
        }
        for (int j = 0; j < (28 - key_shifts[i - 1]); j++) {
            key_56bit_high[i][j] = key_56bit_high[i - 1][j + key_shifts[i - 1]];
        }
        for (int j = (28 - key_shifts[i - 1]); j < 28; j++) {
            key_56bit_high[i][j] = temp_key_shift[i - 1][z];
            z++;
        }

        for (int j = 0; j < key_shifts[i - 1]; j++) {
            temp_key_shift[i - 1][j] = key_56bit_low[i - 1][j];
        }
        for (int j = 0; j < (28 - key_shifts[i - 1]); j++) {
            key_56bit_low[i][j] = key_56bit_low[i - 1][j + key_shifts[i - 1]];
        }
        z = 0;
        for (int j = (28 - key_shifts[i - 1]); j < 28; j++) {
            key_56bit_low[i][j] = temp_key_shift[i - 1][z];
            z++;
        }
    }
    for (int i = 0; i < 17; i++) {
        for (int j = 0; j < 56; j++) {
            if (j < 28) {
                    temp_key_56bit[i][j] = key_56bit_high[i][j];
            }
            else {
                    temp_key_56bit[i][j] = key_56bit_low[i][j - 28];
            }
        }
    }
    for (int i = 1; i < 17; i++) {
        for (int j = 0; j < 56; j++) {
            for (int k = 0; k < 48; k++) {
                if (key_permutation_2_table[k] == j) {
                    subkeys_48bit[i][k] = temp_key_56bit[i][j];
                    break;
                }
            }
        }
    }
}

void DES::create_sboxes() {
    uint8_t auxiliary_mask = 0x20;
    for (int i = 0; i < 8; i++) {
        sbox[i] = 0;
    }
    for (int i = 0; i < 48; i++) {
        if (i < 6) {
            if (xor_text[i] > 0) {
                sbox[0] |= auxiliary_mask;
            }
            auxiliary_mask = auxiliary_mask >> 1;
            if (i == 5) { auxiliary_mask = 0x20; }
        }
        else if (i < 12) {
            if (xor_text[i] > 0) {
                sbox[1] |= auxiliary_mask;
            }
            auxiliary_mask = auxiliary_mask >> 1;
            if (i == 11) { auxiliary_mask = 0x20; }
        }
        else if (i < 18) {
            if (xor_text[i] > 0) {
                sbox[2] |= auxiliary_mask;
            }
            auxiliary_mask = auxiliary_mask >> 1;
            if (i == 17) { auxiliary_mask = 0x20; }
        }
        else if (i < 24) {
            if (xor_text[i] > 0) {
                sbox[3] |= auxiliary_mask;
            }
            auxiliary_mask = auxiliary_mask >> 1;
            if (i == 23) { auxiliary_mask = 0x20; }
        }
        else if (i < 30) {
            if (xor_text[i] > 0) {
                sbox[4] |= auxiliary_mask;
            }
            auxiliary_mask = auxiliary_mask >> 1;
            if (i == 29) { auxiliary_mask = 0x20; }
        }
        else if (i < 36) {
            if (xor_text[i] > 0) {
                sbox[5] |= auxiliary_mask;
            }
            auxiliary_mask = auxiliary_mask >> 1;
            if (i == 35) { auxiliary_mask = 0x20; }
        }
        else if (i < 42) {
            if (xor_text[i] > 0) {
                sbox[6] |= auxiliary_mask;
            }
            auxiliary_mask = auxiliary_mask >> 1;
            if (i == 41) { auxiliary_mask = 0x20; }
        }
        else {
            if (xor_text[i] > 0) {
                sbox[7] |= auxiliary_mask;
            }
            auxiliary_mask = auxiliary_mask >> 1;
        }
    }
}

void DES::write_to_file(int dec_or_enc) {
    uint8_t decrypted_char = 0;
    uint64_t auxiliary_mask = 0x80;
    if (dec_or_enc == 1) {
        FILE* encrypt_file = fopen("encrypted.txt", "ab+");
        for (int i = 0; i < 64; i++) {
            if (((i % 8) == 0) && (i != 0)) {
                auxiliary_mask = 0x80;
                //printf("encrypted_char: %d \n", decrypted_char);
                fprintf(encrypt_file, "%c", decrypted_char);
                decrypted_char = 0;
            }
            if (encrypted_text[i] > 0) {
                decrypted_char |= auxiliary_mask;
            }
            auxiliary_mask = auxiliary_mask >> 1;
            if (i == 63) {
                fprintf(encrypt_file, "%c", decrypted_char);
            }
        }
        fclose(encrypt_file);
        //cout << "encrypted text: " << encrypted_text << endl;
    }
    if (dec_or_enc == 0) {
        FILE* decrypt_file = fopen("decrypted.txt", "ab+");
        for (int i = 0; i < 64; i++) {
            if (((i % 8) == 0) && (i != 0)) {
                auxiliary_mask = 0x80;
                //printf("decrypted_char: %d \n", decrypted_char);
                fprintf(decrypt_file, "%c", decrypted_char);
                decrypted_char = 0;
            }
            if (encrypted_text[i] > 0) {
                decrypted_char |= auxiliary_mask;
            }
            auxiliary_mask = auxiliary_mask >> 1;
            if (i == 63) {
                fprintf(decrypt_file, "%c", decrypted_char);
            }
        }
        fclose(decrypt_file);
    }
}

int DES::get_sboxes_value() {
    uint32_t val = 0;
    int x = 0;
    int y = 0;
    uint8_t mask = 0;
    uint8_t auxiliary_mask = 0;
    uint32_t value_mask = 0x80000000;
    for (int i = 0; i < 8; i++) {
        x = 0;
        y = 0;
        mask = 0x20;
        auxiliary_mask = 0x02;
        if ((sbox[i] & mask) > 0) { x |= auxiliary_mask; }
        auxiliary_mask = auxiliary_mask >> 1;
        mask = 0x01;
        if ((sbox[i] & mask) > 0) { x |= auxiliary_mask; }
        mask = 0x10;
        auxiliary_mask = 0x08;
        for (int j = 0; j < 4; j++) {
            if ((sbox[i] & mask) > 0) {
                y |= auxiliary_mask;
            }
            mask = mask >> 1;
            auxiliary_mask = auxiliary_mask >> 1;
        }
        mask = 0x08;
        switch (i) {
        case 0:
            for (int j = 0; j < 4; j++) {
                if ((s_box_1_table[x][y] & mask) > 0) {
                    val |= value_mask;
                }
                value_mask = value_mask >> 1;
                mask = mask >> 1;
            }
            break;
        case 1:
            for (int j = 0; j < 4; j++) {
                if ((s_box_2_table[x][y] & mask) > 0) {
                    val |= value_mask;
                }
                value_mask = value_mask >> 1;
                mask = mask >> 1;
            }
            break;
        case 2:
            for (int j = 0; j < 4; j++) {
                if ((s_box_3_table[x][y] & mask) > 0) {
                    val |= value_mask;
                }
                value_mask = value_mask >> 1;
                mask = mask >> 1;
            }
            break;
        case 3:
            for (int j = 0; j < 4; j++) {
                if ((s_box_4_table[x][y] & mask) > 0) {
                    val |= value_mask;
                }
                value_mask = value_mask >> 1;
                mask = mask >> 1;
            }
            break;
        case 4:
            for (int j = 0; j < 4; j++) {
                if ((s_box_5_table[x][y] & mask) > 0) {
                    val |= value_mask;
                }
                value_mask = value_mask >> 1;
                mask = mask >> 1;
            }
            break;
        case 5:
            for (int j = 0; j < 4; j++) {
                if ((s_box_6_table[x][y] & mask) > 0) {
                    val |= value_mask;
                }
                value_mask = value_mask >> 1;
                mask = mask >> 1;
            }
            break;
        case 6:
            for (int j = 0; j < 4; j++) {
                if ((s_box_7_table[x][y] & mask) > 0) {
                    val |= value_mask;
                }
                value_mask = value_mask >> 1;
                mask = mask >> 1;
            }
            break;
        case 7:
            for (int j = 0; j < 4; j++) {
                if ((s_box_8_table[x][y] & mask) > 0) {
                    val |= value_mask;
                }
                value_mask = value_mask >> 1;
                mask = mask >> 1;
            }
            break;
        }
    }

    return val;
}

void DES::feistel_function(int round, int dec_or_enc) {
    int temp_sbox_value[32] = { 0 };
    uint32_t mask = 0x80000000;
    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 48; j++) {
            if (expansion_permutation_table[j] == i) {
                expansion_text[j] = input_text_low[round-1][i];
                break;
            }
        }
    }

    for (int i = 0; i < 48; i++) {
        if (dec_or_enc == 1) {
            xor_text[i] = expansion_text[i] ^ subkeys_48bit[round][i];
        }
        else {
            xor_text[i] = expansion_text[i] ^ subkeys_48bit[17-round][i];
        }
    }
    create_sboxes();
    uint32_t val = get_sboxes_value();
    for (int i = 0; i < 32; i++) {
        if ((val & mask) > 0) {
            temp_sbox_value[i] = 1;
        }
        else {
            temp_sbox_value[i] = 0;
        }
        mask = mask >> 1;
    }
    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 32; j++) {
            if (block_permutation_table[j] == i) {
                sbox_value[j] = temp_sbox_value[i];
                break;
            }
        }
    }
    for (int i = 0; i < 32; i++) {
        input_text_low[round][i] = input_text_high[round - 1][i] ^ sbox_value[i];
    }

}

void DES::encrypt_bits(int dec_or_enc) {
    int temp_input_text_plain[64] = { 0 };
    int temp_encrypted_text[64] = { 0 };
    for (int i = 0; i < 64; i++) {
        temp_input_text_plain[i] = input_text_plain[i];
    }
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 64; j++) {
            if (start_permutation_table[j] == i) {
                input_text_plain[j] = temp_input_text_plain[i];
                break;
            }
        }
    }

    for (int i = 0; i < 64; i++) {
        if (i < 32) {
            input_text_high[0][i] = input_text_plain[i];
        }
        else {
            input_text_low[0][i - 32] = input_text_plain[i];
        }
    }
    for (int i = 1; i < 17; i++) {
        feistel_function(i, dec_or_enc);
        for(int j = 0; j < 32; j++){
            input_text_high[i][j] = input_text_low[i - 1][j];
        }
    }

    for (int i = 0; i < 64; i++) {
        if (i < 32) {
            encrypted_text[i] = input_text_low[16][i];
        }
        else {
            encrypted_text[i] = input_text_high[16][i - 32];
        }
    }
    for (int i = 0; i < 64; i++) {
        temp_encrypted_text[i] = encrypted_text[i];
    }
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 64; j++) {
            if (end_permutation_table[j] == i) {
                encrypted_text[j] = temp_encrypted_text[i];
            }
        }
    }

    write_to_file(dec_or_enc);
}

void DES::encrypt_input_text() {
    FILE* plain_text = fopen("input.txt", "rb");
    char single_char;
    char input[8];
    uint32_t counter = 0;
    uint64_t mask = 0;
    uint64_t auxiliary_mask = 0;
    uint64_t input_text = 0;

    while (!feof(plain_text)) {
        single_char = fgetc(plain_text);
        input[counter] = single_char;
        counter++;
        if ((counter != 0) && (counter % 8 == 0)) {
            input_text = 0;
            mask = 0x8000000000000000;
            for (int i = 0; i < 8; i++) {
                auxiliary_mask = 0x80;
                for (int j = 0; j < 8; j++) {
                    if ((input[i] & auxiliary_mask) > 0) {
                        input_text |= mask;
                    }
                    mask = mask >> 1;
                    auxiliary_mask = auxiliary_mask >> 1;
                }
            }
            mask = 0x8000000000000000;
            for (int i = 0; i < 64; i++) {
                if ((input_text & mask) > 0) {
                    input_text_plain[i] = 1;
                }
                else {
                    input_text_plain[i] = 0;
                }
                mask = mask >> 1;
                //cout << input_text_plain[i];
            }
            encrypt_bits(1);

            for (int i = 0; i < 8; i++) {
                input[i] = 0;
                counter = 0;
            }
        }
    }
    if (((counter % 8) != 0) && (counter != 0)) {
        input_text = 0;
        mask = 0x8000000000000000;
        for (int i = 0; i < ((counter % 8) - 1); i++) {
            auxiliary_mask = 0x80;
            for (int j = 0; j < 8; j++) {
                if ((input[i] & auxiliary_mask) > 0) {
                    input_text |= mask;
                }
                mask = mask >> 1;
                auxiliary_mask = auxiliary_mask >> 1;
            }
        }
        mask = 0x8000000000000000;
        for (int i = 0; i < 64; i++) {
            if ((input_text & mask) > 0) {
                input_text_plain[i] = 1;
            }
            else {
                input_text_plain[i] = 0;
            }
            mask = mask >> 1;
        }
        encrypt_bits(1);
    }

    fclose(plain_text);
}

void DES::decrypt() {
    FILE* encrypted = fopen("encrypted.txt", "rb");
    char single_char;
    char input[8];
    uint32_t counter = 0;
    uint64_t mask = 0;
    uint64_t auxiliary_mask = 0;
    uint64_t input_text = 0;

    while (!feof(encrypted)) {
        single_char = fgetc(encrypted);
        input[counter] = single_char;
        counter++;
        if ((counter != 0) && (counter % 8 == 0)) {
            input_text = 0;
            mask = 0x8000000000000000;
            for (int i = 0; i < 8; i++) {
                auxiliary_mask = 0x80;
                for (int j = 0; j < 8; j++) {
                    if ((input[i] & auxiliary_mask) > 0) {
                        input_text |= mask;
                    }
                    mask = mask >> 1;
                    auxiliary_mask = auxiliary_mask >> 1;
                }
            }
            mask = 0x8000000000000000;
            for (int i = 0; i < 64; i++) {
                if ((input_text & mask) > 0) {
                    input_text_plain[i] = 1;
                }
                else {
                    input_text_plain[i] = 0;
                }
                mask = mask >> 1;
            }
            encrypt_bits(0);

            for (int i = 0; i < 8; i++) {
                input[i] = 0;
                counter = 0;
            }
        }
    }
    fclose(encrypted);
}



int main()
{
    const char example[16] = {'i', 'n', 's', 'e', 'r', 't', ' ', 't', 'e', 'x', 't', ' ', 'h', 'e', 'r', 'e' };
    FILE* file = fopen("input.txt", "ab+");
    for (int i = 0; i < 16; i++) {
        fprintf(file, "%c", example[i]);
    }
    fclose(file);

    char user_confirmation = '0';
    bool condition = true;
    cout << "Umiesc tekst do zaszyfrowania w pliku input.txt i wcisnij T, aby zaszyfrowac tekst wejsciowy lub N aby wyjsc z programu" << endl;
    cin >> user_confirmation;
    while(condition)  {
        if ((user_confirmation == 'T') || (user_confirmation == 't')) {
            file = fopen("encrypted.txt", "wb+");
            fclose(file);
            file = fopen("decrypted.txt", "wb+");
            fclose(file);
            DES des;
            des.generate_key(10);
            des.generate_subkeys();
            des.encrypt_input_text();
            des.decrypt();
            cout << "Jesli chcesz ponownie zaszyfrowac tekst, umiesc go w pliku input.txt oraz wcisnij T, aby zaszyfrowac tekst wejsciowy lub N aby wyjsc z programu" << endl;
            cin >> user_confirmation;
        }
        else if ((user_confirmation == 'N') || (user_confirmation == 'n')) {
            condition = false;
        }
        else {
            cout << "Wpisano niepoprawny znak, wybierz znak ponownie" << endl;
            cin >> user_confirmation;
        }
    }
    return 0;
}