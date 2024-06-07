#define BLYNK_TEMPLATE_ID "TMPL67sE7WVzA"          //membaca id tamplate pda blynk
#define BLYNK_TEMPLATE_NAME "TurbinAngin"    //membaca nama tamplate yang di gunakan di blynk
#define BLYNK_AUTH_TOKEN "S21udN7_ukC8V2EwR4WC2PdWR_c6XBsL"   //token pada blynk yng akan digunakan untuk alamat pengiriman data dari nodemcu ke hp

#define BLYNK_PRINT Serial    //fungsi yg bertugas untuk melakukan komunikasi antara hp blynk dan nodemcu, sepeti jembatan penghubung untuk mengirim data


#include <ESP8266WiFi.h>   //libraries untuk nodemcu membaca hotspot atau jaringan wifi

#include <BlynkSimpleEsp8266.h>   //libraies untuk membantu komunikasi antara blynk dan nodemcu

char ssid[] = "hikma";   //nama hostpot atau wifi
char pass[] = "123456789";  //sandi hotspot atau wifi

String dataBaru = "";    //set dataBaru dengan tipedata string, nilai awalnya tidak ada

WidgetLCD lcd(V1);   // fungsi untuk mendefinisikan id lcd pada blynk, maksudnya seperi pin yang di tuju node mcu pada blynk.

void setup()    //fungsi ini akan berjalan sekali untuk mengset sekaligus menjalankan setiap fungsi sekali salama alat dalam keadaan on.
{
  Serial.begin(9600);  //jalankan serial begin dengan baudrate 9600, sebagai jembatan untuk mengerim data dari arduino nodemcu

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);   //jalankan blynk dengan token, nama wifi, dan password wifi, nodemcu akan mengirim data melalui jaringan yg sudah di set dan tujiannya sesuai token pada blynk.
}

void loop()
{
  Blynk.run();

  String data = "";    //set variabel data dengan tipe data string
  while(Serial.available() > 0){   //perulangan while akan cek apakah ada data yang dikirim dari arduino atau tidak melalui Serial.available. jika ada jalankan perulangan

    data += char(Serial.read()); //jika ada data yang dikieim, ambil data tersebut lalu susun data tersebut dan simpan di variabel data.
  }

  if(data.length() > 0){  //cek kondisi jika da data, jalankan statment di dalamnya
    lcd.clear();    //hapus data lama pada lcd blynk, dana cetak data baru
    lcd.print(1, 0, data);      //data yang di cetak di lcd blynk, cetak pada baris pertama, kolom ke 2, data yang dicetak adalah data yang diterima dan di tampung didalam variabel string data.
  }
  delay(1000);  // menunggu 1 detik untuk memulai pengecekan ulang dari atas.
}