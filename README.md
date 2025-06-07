# LAPRES Praktikum Sistem Operasi Modul 5 - IT14

## Kelompok

Nama | NRP
--- | ---
Muhammad Fatihul Qolbi Ash Shiddiqi | 5027241023
Mutiara Diva Jaladitha | 5027241083
M. Faqih Ridho | 5027241123

## Daftar Isi

- [Kelompok](#kelompok)
- [Daftar Isi](#daftar-isi)
- [Soal](#soal)
- [Petunjuk Soal](#petunjuk-soal)
  - [Source](#source)
  - [Headers](#headers)
  - [Makefile](#makefile)
  - [Video Demonstrasi](#video-demonstrasi)
- [Laporan](#laporan)

## Soal

Pada suatu hari, anda merasa sangat lelah dari segala macam praktikum yang sudah ada, sehingga anda berencana untuk tidur yang nyenyak di sebuah jam 3:34AM yang cerah. Tetapi, anda terbangun di dalam dunia berbeda yang bernama "Eorzea". Ada sesuatu yang mengganggu pikiran anda sehingga anda diharuskan membuat sebuah operating system bernama "EorzeOS" untuk mendampingi diri anda dalam dunia ini.

1. Sebagai seorang main character dari dunia ini, ternyata anda memiliki kekuatan yang bernama "The Echo", kekuatan ini memungkinkan anda untuk berbicara pada Operating System ini (mungkin sebenarnya bukan ini kekuatannya, tetapi ini cukup kuat juga), dengan tujuan agar semua hal yang anda katakan, bila bukan merupakan sebuah command yang valid, akan mengulang hal yang anda katakan.

   Ilustrasi:
   ```
   user> Hello!
   Hello!
   user> I have the Echo
   I have the Echo
   ```

2. gurt: yo

   Ilustrasi:
   ```
   user> yo
   gurt
   user> gurt
   yo
   ```

3. Seorang main character memerlukan sebuah nama yang semua orang bisa ingat dengan baik. Buatlah sebuah command yang memungkinkan pengguna untuk mengubah nama user pada shell yang digunakan:
   * `user <username>` = mengubah username menjadi `<username>`
   * `user` = mengubah username menjadi default `user`
   
   Ilustrasi:
   ```
   user> user Tia
   Username changed to Tia
   Tia> user
   Username changed to user
   user>
   ```

4. Tiga negara besar dari Eorzean Alliance butuh bantuan anda untuk ikut serta dalam "Grand Company" mereka sehingga anda bisa mengubah warna terminal ajaib anda sesuai warna utama dari company mereka:
   * `grandcompany maelstrom` = clear terminal, ubah semua teks berikutnya jadi merah
   * `grandcompany twinadder` = clear terminal, ubah semua teks berikutnya jadi kuning
   * `grandcompany immortalflames` = clear terminal, ubah semua teks berikutnya jadi biru
   * `grandcompany <selain atau kosong>` = tunjukkan error message
   * `clear` = clear terminal, ubah semua teks berikutnya kembali jadi awal (para Grand Company sedih kamu netral)

   Selain mengubah seluruh warna terminal, nama anda di dalam terminal akan diberikan tambahan nama judul Grand Company:
   * Maelstrom = `user@Storm`
   * Twin Adder = `user@Serpent`
   * Immortal Flames = `user@Flame`
   * `clear` = menghapus nama grand company

   Ilustrasi:
   ```
   gurt> grandcompany maelstrom
   -- terminal clear menjadi warna merah --
   gurt@Storm> clear
   -- terminal clear menjadi warna putih --
   ```

5. Sebagai pahlawan terkenal di antara ketiga negara besar Eorzean Alliance, salah satu supplier senjata terbesar di seluruh Eorzea bernama "Rowena's House of Splendors" tiba-tiba memerlukan bantuan anda untuk membuat sebuah sistem kalkulator sederhana melalui command karena pemimpin mereka tertidur setelah mengurus semua orang di dalam Eorzea:
   * `add <x> <y>` = x + y
   * `sub <x> <y>` = x - y
   * `mul <x> <y>` = x * y
   * `div <x> <y>` = x / y

   Ilustrasi:
   ```
   user> add 4 2
   6
   user> sub 4 2
   2
   user> mul 3 -2
   -6
   user> div -6 -2
   3
   ```

6. me: yogurt
   
   gurt:
   * `yo`
   * `ts unami gng </3`
   * `sygau`

   pilih secara *random*

   Ilustrasi:
   ```
   user> yogurt
   gurt> yo
   user> yogurt
   gurt> ts unami gng </3
   user> yogurt
   gurt> sygau
   ```

8. Perusahaan mesin "Garlond Ironworks" tiba-tiba lelah mengurus permintaan senjata perang untuk orang ke-148649813234 yang berusaha menghadapi final boss yang sama, sehingga mereka perlu bantuan kamu untuk melengkapi `Makefile` yang diberikan dengan command-command yang sesuai untuk compile seluruh operating system ini.

## Petunjuk Soal

### Source

* [kernel.asm](src/kernel.asm)
  * `_putInMemory`: penjelasan terdapat dalam modul
  * `_interrupt`: fungsi untuk interrupt
    * `number`: interrupt vector number
    * `AX`,`BX`,`CX`,`DX`: register untuk diisi
    * `AX` merupakan kombinasi dari `AH` dan `AL`, pola ini juga berlaku untuk `BX`,`CX`, dan `DX`
    * Untuk menggabungkan jenis register `H` dan `L` menjadi `X` bisa menggunakan salah satu metode berikut:
      ```c
      AX = AH << 8 | AL    // first method
      AX = AH * 256 + AL   // second method
      ```
   * `getBiosTick`: fungsi untuk mendapatkan tick dari BIOS
* [kernel.c](src/kernel.c)
  * Diisi penerapan fungsi `printString`, `readString`, dan `clearScreen` dengan bantuan `kernel.asm`
    * untuk `printString`: Implementasi dapat menggunakan fungsi `interrupt` dengan service `int 10h` dengan parameter `AH = 0x0E` untuk _teletype output_. Karakter yang ditampilkan dapat dimasukkan pada register `AL`. Fungsi ini akan menampilkan string karakter ASCII (_null-terminated_) ke layar.
    * untuk `readString`: Implementasi dapat menggunakan fungsi `interrupt` dengan service `int 16h` dengan parameter `AH = 0x00` untuk _keyboard input_. Fungsi ini akan membaca karakter ASCII (_non-control_) yang dimasukkan oleh pengguna dan menyimpannya pada buffer hingga menekan tombol `Enter`. Handle tombol `Backspace` dibebaskan kepada praktikan.
    * untuk `clearScreen`: Ukuran layar adalah `80x25` karakter. Setelah layar dibersihkan, kursor akan kembali ke posisi awal yaitu `(0, 0)` dan buffer video untuk warna karakter diubah ke warna putih. Implementasi dapat menggunakan fungsi `interrupt` dengan service `int 10h` atau menggunakan fungsi `putInMemory` untuk mengisi memori video.
* [shell.c](src/shell.c)
  * Diisi penerapan shell yang menggunakan fungsi kernel untuk parsing keseluruhan command yang diinput

### Headers

* [std_type.h](include/std_type.h)
  * `byte`: unsigned char data type, untuk angka 0-255 (`0x00`-`0xFF`)
  * `bool`: untuk boolean (true/false), karena boolean tidak built-in
* [std_lib.h](include/std_lib.h)
  * `div`: division
  * `mod`: modulo
  * Pembagian dan modulo tidak ada dalam assembly, sehingga harus dilengkapi dengan operator yang tersedia (`+`,`-`,`*`,`<<`,`>>`)
  * `strcmp`: membandingkan dua string
  * `strcpy`: copy string
  * `clear`: fill memory dengan `0`
  * `atoi`: alphanumeric to integer (string menjadi angka)
  * `itoa`: integer to alphanumeric (angka menjadi string)
* [kernel.h](include/kernel.h)
  * Deklarasi header untuk fungsi-fungsi dalam `kernel.c`
* [shell.h](include/shell.h)
  * Deklarasi header untuk fungsi-fungsi dalam `shell.c`

### Makefile

* [makefile](./makefile)
   * `prepare` : membuat disk image baru `floppy.img` pada direktori `bin/` dengan ukuran 1.44 MB.
   * `bootloader` : mengkompilasi `bootloader.asm` menjadi `bootloader.bin` pada direktori `bin/`.
   * `stdlib` : mengkompilasi `std_lib.c` menjadi `std_lib.o` pada direktori `bin/`.
   * `shell`: mengkompilasi `shell.c` menjadi `shell.o` pada direktori `bin/`.
   * `kernel` : mengkompilasi `kernel.c` menjadi `kernel.o` pada direktori `bin/` dan mengkompilasi `kernel.asm` menjadi `kernel_asm.o` pada direktori `bin/`.
   * `link` : menggabungkan `bootloader.bin`, `kernel.o`, `kernel_asm.o`, dan `std_lib.o` menjadi `floppy.img`.
   * `build` : menjalankan perintah `prepare`, `bootloader`, `stdlib`, `kernel`, dan `link`.

### Video Demonstrasi

[Akses Video dalam Assets](./assets/demo.mp4)

https://github.com/user-attachments/assets/1cfa66b1-b2f5-4e3e-a4b2-ec8b012f6fbb


## Laporan

## **Soal 1**
```
else {
            printString(buf);
            printString("\r\n");
        }
```
### Penjelasan
Percabangan ini merupakan fallback (cadangan) jika input dari pengguna tidak cocok dengan kondisi atau perintah manapun yang telah didefinisikan sebelumnya dalam fungsi shell().

**Fungsi**
- Menampilkan kembali input yang tidak dikenali ke layar.

- Mencegah input tidak valid untuk "tidak melakukan apa-apa".

- Memberikan umpan balik langsung ke pengguna bahwa perintahnya belum didukung atau salah ketik.

**Cara Kerja:**
1.Jika semua kondisi if, else if, dan penanganan khusus seperti "yo", "gurt", "add", "mul", "grandcompany", dll. tidak terpenuhi, maka masuk ke blok else ini.

2. Program mencetak kembali buf (yaitu string input dari pengguna).

3. Diikuti dengan karakter \r\n (carriage return dan line feed) agar output rapi dan berpindah ke baris baru.
   
### Output
![output](assets/output%20nomer%201.png)

## **Soal 2**
```
// Yo/Gurt
        if (strcmp(buf, "yo") == 0) {
            printString("gurt\n");
        } else if (strcmp(buf, "gurt") == 0) {
            printString("yo\r\n");
        }
```
### Penjelasan
Percabangan ini terdapat pada fungsi shell dalam file shell.c. Fungsinya adalah memberikan respons interaktif berdasarkan input pengguna:

- Jika pengguna mengetikkan "yo", maka program akan mencetak "gurt".

- Jika pengguna mengetikkan "gurt", maka program akan mencetak "yo".

Perbandingan string dilakukan dengan fungsi strcmp() dari pustaka std_lib.c.

### Output
![output](assets/output%20nomer%202.png)


## **soal 3**
```
 // Ganti username dengan "user nama"
        else if (is_user_command) {
            for (i = 5, j = 0; buf[i] != '\0' && j < 31; i++, j++) {
                username[j] = buf[i];
            }
            username[j] = '\0';
            printString("Username changed to ");
            printString(username);
            printString("\r\n");
        }

        //  Reset username ke "user"
        else if (strcmp(buf, "user") == 0) {
            strcpy(username, "user");
            printString("Username changed to user\n");
        }
```

### Penjelasan
soal ini menggunakan 2 percabangan :

1. Mengganti username:

- Program membaca input mulai dari indeks ke-5 (user diabaikan) untuk mengambil nama baru.

- Username dibatasi hingga 31 karakter untuk mencegah buffer overflow.

- Setelah itu, username ditampilkan melalui printString.

2. Reset username ke default:

- Jika pengguna mengetik "user", maka nama pengguna akan diatur ulang ke "user" menggunakan strcpy().

### Output
![output](assets/output%20nomer%203.png)

## **soal 4**
```
else if(startsWith(buf,"grandcompany")){
            char cmd[4];
            char args[2][64];
            parseCommand(buf, cmd, args);
            // printString(args[0]);
            if (strcmp(args[0],"maelstrom") == 0){                
                setTerminalColor(0x0c);
                strcpy(hostname,"@storm");
                clearScreen(color_code);
            }else if(strcmp(args[0],"twinadder") == 0){                
                setTerminalColor(0x0e);
                strcpy(hostname,"@serpent");
                clearScreen(color_code);
            }else if(strcmp(args[0],"immortalflames") == 0){                
                setTerminalColor(0x09);
                strcpy(hostname,"@flame");
                clearScreen(color_code);
            }else{
                printString("unknown company");
            }
            printString("\r\n");        
        }

else if (strcmp(buf, "clear") == 0) {
            strcpy(hostname,"");
            clearScreen(0x07);
            break;            
        }
```
### Penjelasan
 
Percabangan ini berfungsi untuk mengganti warna teks terminal dan hostname berdasarkan perintah "grandcompany <nama>".

- startsWith(buf, "grandcompany") memastikan bahwa perintah diawali dengan keyword tersebut.

- Kemudian parseCommand() akan memisahkan argumen perintah menjadi cmd dan args.

### Detail Implementasi

- "maelstrom" → Warna merah (0x0c), hostname menjadi @storm.

- "twinadder" → Warna kuning (0x0e), hostname menjadi @serpent.

- "immortalflames" → Warna biru (0x09), hostname menjadi @flame.

Jika argumen tidak dikenali → Output "unknown company".

### Tambahan

- Perintah "clear" akan menghapus hostname dan mengembalikan warna terminal ke default putih (0x07).

### Output
![output](assets/output%20nomer%204%20(1).png)

![output](assets/output%20nomer%204%20(2).png)

![output](assets/output%20nomer%204%20(3).png)

![output](assets/output%20nomer%204%20(4).png)

## **soal 5**
```
// 4. Kalkulator: add, sub, mul, div
        else if (startsWith(buf, "add ") || startsWith(buf, "sub ") ||
                 startsWith(buf, "mul ") || startsWith(buf, "div ")) {
            char cmd[4];
            char args[2][64];
            int x, y, result, valid, remainder;

            parseCommand(buf, cmd, args);

            x = stringToInt(args[0]);
            y = stringToInt(args[1]);
            result = 0;
            valid = 1;

            if (strcmp(cmd, "add") == 0) {
                result = x + y;
            } else if (strcmp(cmd, "sub") == 0) {
                result = x - y;
            } else if (strcmp(cmd, "mul") == 0) {
                // Tangani tanda negatif
                int sign = 1;
                if (x < 0) {
                    sign = -sign;
                    x = -x;
                }
                if (y < 0) {
                    sign = -sign;
                    y = -y;
                }

                result = 0;
                for (i = 0; i < y; i++) {
                    result += x;
                }

                result = sign * result;
            } else if (strcmp(cmd, "div") == 0) {
                if (y == 0) {
                    printString("Error: Division by zero\n");
                    valid = 0;
                } else {
                    // Tangani tanda negatif
                    int sign = 1;
                    if (x < 0) {
                        sign = -sign;
                        x = -x;
                    }
                    if (y < 0) {
                        sign = -sign;
                        y = -y;
                    }

                    result = 0;
                    remainder = x;
                    while (remainder >= y) {
                        remainder -= y;
                        result++;
                    }

                    result = sign * result;
                }
            }

            if (valid) {
                intToString(result, num_buf);
                printString(num_buf);
                printString("\r\n");
            }
        }
```

### Penjelasan

Percabangan di atas digunakan untuk menangani operasi aritmetika dasar (add, sub, mul, dan div) di dalam fungsi shell. Fungsi ini akan mengeksekusi operasi sesuai perintah yang diberikan oleh pengguna.

**Proses Utama**

1. Program mengecek apakah input diawali dengan "add ", "sub ", "mul ", atau "div ".

2. Menggunakan parseCommand() untuk memisahkan perintah (cmd) dan dua argumen angka (args[0] dan args[1]).

3. Angka dikonversi dari string ke integer menggunakan stringToInt().

4 Operasi dilakukan berdasarkan jenis perintah:

- add: Menjumlahkan dua angka.

- sub: Mengurangkan dua angka.

- mul: Perkalian dengan penjumlahan berulang.

- div: Pembagian dengan pengurangan berulang.

**Penanganan Khusus**

Untuk mul dan div, tanda negatif ditangani secara manual menggunakan variabel sign.

Untuk div, terdapat pemeriksaan pembagi nol:

- Jika y == 0, maka akan menampilkan pesan:

```
Error: Division by zero
```

- Operasi dibatalkan dengan valid = 0.

**Hasil**

- Jika operasi valid, hasil akan dikonversi kembali ke string menggunakan intToString() dan ditampilkan menggunakan printString().

### Output
![output](assets/output%20nomer%205.png)

## **Soal 6**

```
else if (strcmp(buf, "yogurt") == 0) {
    int tick;
    char answer[3][100];
    tick = mod(getBiosTick(), 3);            
    strcpy(answer[0], "yo");
    strcpy(answer[1], "ts unami gng </3");
    strcpy(answer[2], "sygau");

    printString(answer[tick]);
    printString("\r\n");

    // Ganti prompt ke "gurt>" sekali saja
    printString("gurt> ");
    readString(buf);  // baca input berikutnya langsung di sini

    continue;  // langsung lanjut ke iterasi berikutnya
}

```

### Penjelasan

Percabangan ini menangani perintah khusus ketika pengguna mengetik "yogurt". Program akan memberikan respons acak dari tiga pilihan, serta mengubah prompt terminal menjadi "gurt>" hanya untuk satu kali input berikutnya.

**Langkah-Langkah**

1. Inisialisasi Array Jawaban:

- answer[0] = "yo"

- answer[1] = "ts unami gng </3"

- answer[2] = "sygau"

2. Pemilihan Acak Jawaban:

- Menggunakan getBiosTick() untuk mengambil waktu sistem, lalu dihitung modulus 3 (mod(getBiosTick(), 3)) untuk mendapatkan nilai antara 0 hingga 2.

- Nilai ini menentukan indeks jawaban yang akan dicetak.

3. Output Jawaban:

- Program mencetak string dari array answer[tick] dan diikuti oleh baris baru (\r\n).

4. Prompt Dinamis:

- Setelah mencetak jawaban, prompt diganti menjadi "gurt> ".

- Pengguna langsung diminta memasukkan input baru dengan readString(buf).

5. Lanjut Iterasi:

- Dengan continue, program kembali ke awal loop shell() tanpa menjalankan bagian bawah fungsi.

**Catatan Khusus**

- Prompt "gurt> " hanya muncul sekali setelah "yogurt". Iterasi selanjutnya akan kembali menggunakan prompt normal.

- Fungsi mod(), getBiosTick(), strcpy(), dan printString() merupakan bagian dari utilitas sistem yang digunakan untuk manipulasi data dan I/O.

### Output
![output](assets/Output%20nomer%206.jpeg)
