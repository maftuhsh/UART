/*
   program device2
   percobaan komunikasi digital UART dan LED sebagai tanda keberhasilan
*/

#include <SoftwareSerial.h> // Library untuk komunikasi serial tambahan selain Serial utama

//========== Mendefinisikan pin dan konstanta untuk LED ===========
#define L1 4        // LED 1 dihubungkan ke pin digital 4
#define L2 5        // LED 2 dihubungkan ke pin digital 5
#define L3 6        // LED 3 dihubungkan ke pin digital 6
#define L4 7        // LED 4 dihubungkan ke pin digital 7
#define NUM_LEDS 4  // Jumlah total LED yang digunakan
#define MATI 0      // Nilai untuk mematikan LED (LOW)

//========== Inisialisasi komunikasi UART menggunakan SoftwareSerial ===========
SoftwareSerial SerialExternal(2/*rx*/, 3/*tx*/); 
// Membuat objek SerialExternal, menggunakan pin 2 sebagai RX dan pin 3 sebagai TX

//========== Variabel global ==========
int leds[NUM_LEDS] = {L1, L2, L3, L4}; // Array untuk menyimpan pin LED
int data = 0;        // Variabel untuk menyimpan data yang diterima dari device1
bool state = false;  // Penanda bahwa data sudah diterima dan siap diproses

//========== Fungsi setup (dijalankan sekali di awal) ==========
void setup() {
  SerialExternal.begin(9600); // Memulai komunikasi serial eksternal (UART) dengan baud rate 9600
  Serial.begin(9600);         // Memulai komunikasi serial ke komputer melalui USB

  // Mengatur semua pin LED sebagai output
  for (uint8_t indx = 0; indx < NUM_LEDS; indx++) {
    pinMode(leds[indx], OUTPUT); // Menetapkan pin LED sebagai OUTPUT
  }

  // Menampilkan pesan sambutan dan status di Serial Monitor
  Serial.println("Welcome to module 4");
  Serial.println("device2 is running");
}

//========== Fungsi loop (berulang terus menerus) ==========
void loop() {
  // Mengecek apakah ada data masuk dari device1 melalui UART
  if (SerialExternal.available()) {
    data = SerialExternal.read(); // Membaca satu byte data dari device1
    state = true;                 // Menandai bahwa data diterima dan siap diproses
  }

  // Menampilkan data yang diterima ke Serial Monitor
  Serial.println("data dari device1 = " + String(data));

  // Jika data valid (antara 1 sampai jumlah LED), maka nyalakan LED sesuai data
  if (data > 0 && data <= NUM_LEDS) {
    // Array representasi biner untuk logika penyalaan LED
    uint8_t bin[NUM_LEDS] = {0b0001, 0b0010, 0b0100, 0b1000};

    --data; // Mengurangi data sebesar 1 agar sesuai dengan indeks array (0–3)

    //====== Menyalakan LED sesuai data yang diterima ======
    for (uint8_t j = 0; j < NUM_LEDS; j++) {
      uint8_t val = (bin[j] >> data) & 1; // Mengambil bit hasil shift sebagai nilai nyala LED
      Serial.print("LED" + String(j + 1) + " = " + String(val) + " \t"); // Tampilkan status LED
      digitalWrite(leds[j], val); // Mengatur status LED (nyala/mati)
    }

    Serial.println(); // Pindah ke baris baru di Serial Monitor
    data++; // Mengembalikan nilai data ke semula (penting agar bisa dikirim balik dengan benar)
  }

  // Jika data tidak valid (misalnya 0 atau lebih dari 4), semua LED dimatikan
  else {
    for (int z = 0; z < NUM_LEDS; z++) {
      digitalWrite(leds[z], MATI); // Mematikan semua LED
    }
    Serial.println("all leds off"); // Tampilkan status ke Serial Monitor
  }

  // Jika sebelumnya data diterima, kirim ulang ke device1 sebagai balasan (acknowledgement)
  if (state) {
    state = false; // Reset status penerimaan
    SerialExternal.write(data); // Kirim data kembali ke device1
  }

  delay(250); // Delay selama 250 ms untuk mengontrol kecepatan loop dan komunikasi
}
