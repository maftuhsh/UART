# UART
Komunikasi UART Modul V Sistem Embeeded Dasar

Komunikasi Digital : Komunikasi digital adalah teknologi yang berbasis sinyal elektrik komputer, 
sinyalnya bersifat terputus-putus dan menggunakan sistem bilangan biner. Bilangan 
biner akan membentuk kode digital (1 dan 0 berdasarkan adanya arus listrik atau tidak, 
yang diatur oleh transistor).

UART atau Universal Asynchronous Receiver/Transmitter merupakan perangkat keras yang digunakan untuk komunikasi serial antara dua perangkat. SImpelnya adalah cara untuk mengirim dan menerima data antara dua alat elektronik, seperti mikrokontroler dan komputer, lewat kabel (usb to ttl)

Cara Kerja UART : UART1 (pengirim) akan mengirim data melalui pin TX (Transmit),
dan UART2 (penerima) akan menerima data itu melalui pin RX (Receive).

| Bagian          | Fungsi                                               |
| --------------- | ---------------------------------------------------- |
| **Start Bit**   | Menandakan awal pengiriman data (selalu logika 0)    |
| **Data Bits**   | Isi informasi yang dikirim (biasanya 7 atau 8 bit)   |
| **Parity Bit**  | Opsional. Untuk cek kesalahan (paritas genap/ganjil) |
| **Stop Bit(s)** | Menandakan akhir pengiriman (logika 1)               |

Simulasi Komunikasi UART dengan Tinkercad
link https://www.tinkercad.com/things/9lfTEWN86uj-uart-simulation?sharecode=CI31CeNw1NYqlYEFtjRwtcZY-Txehb8esrk1q3Q6_RE
