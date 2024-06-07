#include <LiquidCrystal_I2C.h>            //libraries untuk membaca lcd i2c

LiquidCrystal_I2C lcd(0x27, 16, 2);       //fungsi membaca kode versi lcd

const int anemometer = 2;                 //mendefinisikan variabel anemometer untuk pin 2 arduino

unsigned long duration;                   //set duratio dengan tipe data long

float kecepatanAngin;                     //set kecepatanAngin dengan tipe data float

unsigned long waktuSebelumnya = 0;              //set variabel waktuSebelumnya dengan nilai awal = 0

const unsigned long waktuTunggu = 10000;        //set variabel waktuTunggu dengan nilai awal = 10000 (10 detik)

String cekData = "KECEPATAN ANGIN : 0.00 M/S";    // set variabel string cetakData dengan kodisi awal "KECEPATAN ANGIN : 0.00 M/S"

void setup() {   //fungsi untuk menjalankan fungsi secara permanen dan akan terset kembali jika alat di matikan.

  Serial.begin(9600);               //untuk mengirim data ke nodeMcu

  lcd.init();                       //menjalankan fungsi lcd

  lcd.backlight();                  //mencetak data ke layar lcd

  pinMode(anemometer, INPUT);       //set variabel anemometer yg terhubung ke pin 2 arduino sebagai inputan

    lcd.setCursor(2,0);             //cetak data ke lcd pada baris pertama, kolom ke 2

    lcd.print("TURBIN ANGIN");      //data yang dicetak

    lcd.setCursor(5,1);             //cetak data ke lcd pada baris kedua, kolom ke lima

    lcd.print("HIKMAH");            //data yang dicetak
}

void loop() {     //fungsi yang berjalan terus menerus selama alat dalam keadaan on, fungsi akan berulang terus

  unsigned long waktuSaatIni = millis();   //set variabel waktuSaatIni dengan tipedata long, variabel ini akan mengimpan semua data waktu yang verjalan pada fungsi milis()

  // Melakukan pengukuran setiap 10 detik
  if (waktuSaatIni - waktuSebelumnya >= waktuTunggu) {       //cek kondisi, jika waktu saat ini - waktu sebelumnya >=waktuTunggu, kondisi memenuhi syarat, jalankan statment di dalamnya

    waktuSebelumnya = waktuSaatIni; // set waktu sebelumnya dengan waktu yang sekarang

    duration = pulseIn(anemometer, HIGH);    // Mengukur durasi pulsa pada pin anemometer (), fungsi pulseIn akan menangkap data putaran anemometer dan menerjemahkan menjadi priode waktu putaran

    if (duration == 0) {      //cek variabel durasi sama dengan 0 atau tidak, jika sama jalankan statment di dalamnya.

      kecepatanAngin = 0;   //set variabel kecepatanAningn = 0;
      
    } else { //jalankan fungsi ini jika kecepatanAngin tidak sama dengan 0

      // Menghitung kecepatan angin berdasarkan durasi pulsa
      kecepatanAngin = 1000000.0 / duration; //microdetik / durasi pulsa. 1000000 mewakili mikrodetik untuk 1 detiknya
    }

    String data = String("KECEPATAN ANGIN : ") + String(kecepatanAngin) + String(" M/S");     //set variabel data sebagai string dan diisi dengan data "kecepatan angin .... m/s", data ini akan dikirim ke nodeMcu , lalu data tersebut akan di kirim oleh nodeMcu menuju hp.

    if(data != cekData){    //cek kodisi variabel data, jika data tidak samadengan Variabel cekData, makan jalankan statment di dalamnya.

      Serial.println(data);     //statment yang dijalankan, yaitu mengirim data ke nodeMcu melalui serial.println(data)

    }

    lcd.clear();   //hapus data di lcd untuk mencetak data baru

    lcd.setCursor(0,0);   //cetak data dilcd pada baris pertama kolom pertama

    lcd.print("KECEPATAN ANGIN!"); //data ini yng di cetak

    lcd.setCursor(3,1);  //cetak data ke lcd pada kolom ke 3 baris ke dua

    lcd.print(kecepatanAngin);  //data ini yang di cetak

    lcd.print(" M/S");      //cetak data ini setelah cetak kecepatan angin
    
  }
}
