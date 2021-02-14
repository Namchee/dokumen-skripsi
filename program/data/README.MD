## Data Pergerakan
### Input

Setiap data pergerakan yang berhasil diperoleh akan disimpan dalam berkas `input` yang terdapat dalam berkas `data`.

Setiap lokasi yang tercatat akan disimpan dalam satu baris yang memiliki format berikut:

[_frame-time_ id x z y v_x v_z v_y]

### Output

Setiap data akan menghasilkan identifikasi rombongan dengan nama berkas yang sesuai dengan nama berkas _input_ dalam format `.txt`. Sebagai contoh, hasil identifikasi dari berkas `seq_eth` akan menghasilkan output `seq_eth`.

Setiap rombongan yang berhasil teridentifikasi akan ditulis dalam format berikut:

[anggota_rombongan waktu_mulai waktu_selesai]

`anggota_rombongan` adalah kumpulan bilangan bulat yang dipisahkan menggunakan koma.