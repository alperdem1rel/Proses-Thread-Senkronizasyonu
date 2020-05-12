/*
-> 152120151056 ALPER DEMİREL
-> 04/05/2020
-> 152115019 İŞLETİM SİSTEMLERİNE GİRİŞ LAB.
-> Uygulama 5 - Proses/Thread Senkronizasyonu: 5 farklı threadin alt işlemleri arasındaki ilişkiyi senkronizasyon yapılarını kullarak bir senaryo ve bu senaryodaki kurallar çerçevesinde uygulayan program.
-> Sağlık Çalışanlarını Giyinme Simülasyonu (Covid-19 precaution edition)
*/

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <time.h>
#include <pthread.h>

pthread_mutex_t printLine_sync; //thread senkronizasyonu sağlamak için kilitleme(lock) değişkeni tanımlama

sem_t sem1, sem2, sem3, sem4, sem5, sem6, sem7, sem8; //öğelerin(elements) senkronizasyonunu sağlamak için kullanılan semafor değişkenlerini tanımlama

int lineNumber = 0; //satır sayısı değişkeninin tanımlanması ve initiliaze edilmesi
int numberOfItems = 6; //kalan öğe sayısını bildirme değişkeninin tanımlanması ve initiliaze edilmesi 

void printLine(char *element); //printLine fonksiyonunun declare edilmesi
void *functionHead(); //Kafa öğelerini bulunduran fonksiyonun declare edilmesi(Thread 1)
void *functionBody(); //Gövde öğelerini bulunduran fonksiyonun declare edilmesi(Thread 2)
void *functionHand(); //El öğelerini bulunduran fonksiyonun declare edilmesi(Thread 3)
void *functionLeg(); //Bacak öğelerini bulunduran fonksiyonun declare edilmesi(Thread 4)
void *functionFoot(); //Ayak öğelerini bulunduran fonksiyonun declare edilmesi(Thread 1)

/*main fonksiyonu*/
void main()
{

    sem_init(&sem1, 0, 0); //sem1 değişkeninin initiliaze edilme işlemi(default attr.)
    sem_init(&sem2, 0, 0); //sem2 değişkeninin initiliaze edilme işlemi(default attr.)
    sem_init(&sem3, 0, 0); //sem3 değişkeninin initiliaze edilme işlemi(default attr.)
    sem_init(&sem4, 0, 0); //sem4 değişkeninin initiliaze edilme işlemi(default attr.)
    sem_init(&sem5, 0, 0); //sem5 değişkeninin initiliaze edilme işlemi(default attr.)
    sem_init(&sem6, 0, 0); //sem6 değişkeninin initiliaze edilme işlemi(default attr.)
    sem_init(&sem7, 0, 0); //sem7 değişkeninin initiliaze edilme işlemi(default attr.)
    sem_init(&sem8, 0, 0); //sem8 değişkeninin initiliaze edilme işlemi(default attr.)

    pthread_mutex_init(&printLine_sync, NULL); //mutex değişkeninin initiliaze edilme işlemi(default attr.)
    pthread_t thread_1, thread_2, thread_3, thread_4, thread_5; //programda kullanılacak 5 threadin tanımlanma işlemi
    
    /* 5 threadin yaratılma ve threadlerin parametrelerini ekleme fonksiyonu(metodu) */
    pthread_create(&thread_1, NULL, functionHead, NULL);
    pthread_create(&thread_2, NULL, functionBody, NULL);
    pthread_create(&thread_3, NULL, functionHand, NULL);
    pthread_create(&thread_4, NULL, functionLeg, NULL);
    pthread_create(&thread_5, NULL, functionFoot, NULL);

    pthread_join(thread_1, NULL); //thread_1'in sonlandırılma işlemi
    pthread_join(thread_2, NULL); //thread_2'in sonlandırılma işlemi
    pthread_join(thread_3, NULL); //thread_3'in sonlandırılma işlemi
    pthread_join(thread_4, NULL); //thread_4'in sonlandırılma işlemi
    pthread_join(thread_5, NULL); //thread_5'in sonlandırılma işlemi

    pthread_mutex_destroy(&printLine_sync); //mutex değişkeninin yok edilme işlemi

    sem_destroy(&sem1); //sem1 değişkeninin yok edilme işlemi
    sem_destroy(&sem2); //sem2 değişkeninin yok edilme işlemi
    sem_destroy(&sem3); //sem3 değişkeninin yok edilme işlemi
    sem_destroy(&sem4); //sem4 değişkeninin yok edilme işlemi
    sem_destroy(&sem5); //sem5 değişkeninin yok edilme işlemi
    sem_destroy(&sem6); //sem6 değişkeninin yok edilme işlemi
    sem_destroy(&sem7); //sem7 değişkeninin yok edilme işlemi
    sem_destroy(&sem8); //sem8 değişkeninin yok edilme işlemi

}

/*Uygulamada verilen öğeleri(elements) belirli kurallar çerçevesinde yazdırma işlemlerini gerçekleştiren fonksiyon)*/
void printLine(char *element)
{

    pthread_mutex_lock(&printLine_sync); //mutex değişkenin threadler arasındaki senkronizasyonu sağlaması için kilitleme(lock) işlemi

    if (lineNumber == 0) //Satır sayısı=0
    {
        printf("%2d.					--> Saglik calisanlarina sonsuz tesekkurler!..", lineNumber++);
        printf("\n");
    }

    if (lineNumber > 0 && lineNumber < 7) //0<Satır sayısı<7
    {
        printf("%2d. %s", lineNumber++, element);
        printf("\n");
    }

    else if (lineNumber > 6 && lineNumber < 13) //6<Satır sayısı<13
    {

        printf("%2d. %s	--> Kalan oge sayisi: %d", lineNumber++, element, numberOfItems--);
        printf("\n");
    }

    else if (lineNumber == 13) //Satır sayısı=13
    {
        printf("%2d. %s	--> Goreve hazirim!", lineNumber, element);
        printf("\n");
    }
    else
    {
        exit(-1); //Satır sayısı verilen kurallar dışında olduğunda programı bitirme işlemi
    }

    pthread_mutex_unlock(&printLine_sync); //mutex değişkenin threadler arasındaki senkronizasyonu sağladıktan sonra başka bir thread için kilit açma(unlock) işlemi
}

/*Kafa öğelerini içeren fonksiyon*/
void *functionHead()
{
    sem_wait(&sem5); //kaynakları(işlem yapan threadi) bekleme işlemi
    printLine(" (kafa ) YuzDezenfektani           ");
    sem_wait(&sem6); 
    printLine(" (kafa ) SaglikMaskesi             ");
    printLine(" (kafa ) Bone                      ");
    sem_post(&sem7); //kaynakları(işlem yapan threadin sonlanması ve sıradaki threade sıra gelmesi) salma(release) işlemi-sinyal(signal verme)
    sem_wait(&sem8);
    printLine(" (kafa ) KoruyucuPlastikYuzMaskesi");

    pthread_exit(0); //çağırılan threadin sonlandırma/temizlenme işlemi
}

/*Vücut öğelerini içeren fonksiyon*/
void *functionBody()
{

    printLine(" (govde) Atlet                    ");
    printLine(" (govde) Gomlek                   ");
    sem_post(&sem1);
    sem_wait(&sem7);
    printLine(" (govde) Tulum                    ");
    sem_post(&sem8);

    pthread_exit(0);
}

/*El öğelerini içeren fonksiyon*/
void *functionHand()
{

    sem_wait(&sem4);
    printLine(" (el   ) ElDezenfektani           ");
    printLine(" (el   ) Eldiven                  ");
    sem_post(&sem6);
    pthread_exit(0);
}

/*Bacak öğelerini içeren fonksiyon*/
void *functionLeg()
{

    sem_wait(&sem2);
    printLine(" (bacak) Pantolon                 ");
    printLine(" (bacak) Kemer                    ");
    sem_post(&sem3);

    pthread_exit(0); 
}

/*Ayak öğelerini içeren fonksiyon*/
void *functionFoot()
{

    sem_wait(&sem1);
    printLine(" (ayak ) Corap                    ");
    sem_post(&sem2);
    sem_wait(&sem3);
    printLine(" (ayak ) Ayakkabi                 ");
    sem_post(&sem4);
    sem_post(&sem5);
    pthread_exit(0);
}

