// program device1
// percobaan komunikasi digital UART dan LED sebagai tanda keberhasilan

#include <SoftwareSerial.h> // Mengimpor pustaka SoftwareSerial untuk membuat port serial tambahan

// Membuat objek SerialExternal menggunakan pin 2 (RX) dan 3 (TX)
SoftwareSerial SerialExternal(2, 3); 

int data = 0;     // Variabel untuk menyimpan data dari Serial Monitor
bool state1 = 0;  // Penanda bahwa data dari komputer siap dikirim ke device2
bool state2 = 0;  // Penanda bahwa data dari device2 siap ditampilkan ke komputer

void setup() {
  SerialExternal.begin(9600); // Memulai komunikasi serial eksternal dengan baud rate 9600
  Serial.begin(9600);         // Memulai komunikasi serial dengan komputer (USB)
  Serial.println("Welcome to module 4"); // Menampilkan pesan sambutan di Serial Monitor
  Serial.println("device1 is running");  // Menampilkan status awal device
}

void loop() {
  // Mengecek apakah ada data masuk dari komputer via Serial Monitor
  if (Serial.available()) {
    data = Serial.read();  // Membaca satu karakter (byte) dari Serial Monitor
    data -= 48;            // Mengubah dari karakter ASCII ke angka (misal: '1' = 49 ASCII → 1)
    state1 = 1;            // Set flag untuk mengirim data ke device2
  }
   
  // Jika data dari komputer sudah siap dikirim
  if (state1) {
    SerialExternal.write(data); // Mengirim data ke device2 melalui port serial eksternal
    state1 = 0;                 // Reset flag setelah mengirim
  }

  int d_device2 = 0; // Variabel untuk menyimpan data dari device2

  // Mengecek apakah ada data masuk dari device2
  if (SerialExternal.available()) {
    d_device2 = SerialExternal.read(); // Membaca satu byte dari device2
    state2 = 1;                         // Set flag untuk menampilkan data
  }

  // Jika data dari device2 sudah siap ditampilkan
  if (state2) {
    Serial.println("data dari device2 = " + String(d_device2)); // Tampilkan data dari device2
    state2 = 0; // Reset flag setelah menampilkan
  }

  delay(250); // Memberi jeda 250 ms untuk memperlambat loop dan mencegah spam data
}
