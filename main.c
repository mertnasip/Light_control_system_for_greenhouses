#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>

#define LDR 7

int main(){

    //raspberry pi setup edilir
    if(wiringPiSetup() == -1){
        system("echo \"Subject: Sera Uyarısı\r\n\r\nSera sisteminizde hata tespit edilmiştir!!! Bu sorunu gidermek için müşteri hizmetleriyle iletişime geçebilirsiniz.\"|msmtp --debug --from=default -t mertnasipoglu@gmail.com");
        return 0;
    }
    while(1){

        //LDR çalıştırılır
        int count = 0;
        pinMode(LDR, OUTPUT);
        digitalWrite(LDR, LOW);
        delay(300);
        pinMode(LDR, INPUT);
        while(digitalRead(LDR) == 0){
            count = count + 1;
        }
        //ışık seviyesi istenilen değerin altına düşüşü izlenir. Uyarı maili göderilir.
        if(count < 2500){
            system("echo \"Subject: Sera Uyarısı\r\n\r\nSeranızda fazla ışık olduğutespit edilmiştir!!! Bu sorunu gidermek için ışıklarınızı kısabilirsiniz.\" |msmtp --debug --from=default -t mertnasipoglu@gmail.com");
            printf("\nEmail Gönderildi!\n");
            delay(5000);

        //ışık seviyesi istenilen değerin üstüne çıkışı izlenir. Uyarı maili göderilir.
        } else if(count > 13000){
            system("echo \"Subject: Sera Uyarısı\r\n\r\nSeranızda az ışık olduğutespit edilmiştir!!! Bu sorunu gidermek için ışıklarınızı açabilirsiniz.\" |msmtp --debug --from=default -t mertnasipoglu@gmail.com");
            printf("\nEmail Gönderildi!\n");
            delay(5000);

        } else {

            // cmd den LDR okuma değerleri kontrol için:
            printf("%d\n", count);
        }
    }

    return 0;
}
