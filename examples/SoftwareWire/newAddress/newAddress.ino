// ПРИМЕР СМЕНЫ АДРЕСА МОДУЛЯ:                               // * Строки со звёздочкой являются необязательными.
// Требуется установить библиотеку <iarduino_I2C_Software.h> //   https://iarduino.ru/file/627.html
                                                             //
// Датчик освещенности, люксметр, FLASH-I2C:                 //   https://iarduino.ru/shop/Sensory-Datchiki/datchik-osveschennosti-lyuksmetr-i2c-trema-modul-v2-0.html
// Информация о подключении модулей к шине I2C:              //   https://wiki.iarduino.ru/page/i2c_connection/
// Информация о модуле и описание библиотеки:                //   https://wiki.iarduino.ru/page/DSL-trema-i2c/
                                                             //
// Данный скетч демонстрирует не только                      //
// возможность смены адреса на указанный в                   //
// переменной newAddress, но и обнаружение,                  //
// и вывод текущего адреса модуля на шине I2C.               //
                                                             //
// Библиотека <iarduino_I2C_DSL.h> предназначена             //
// для работы с датчиками освещённости I2C-flash             //
// и меняет только их адреса.                                //
// Но, в разделе Файл/Примеры/.../findSortDevices            //
// находятся примеры смены и сортировки адресов              //
// любых модулей iarduino серии Flash I2C.                   //
                                                             //
uint8_t newAddress = 0x09;                                   //   Назначаемый модулю адрес (0x07 < адрес < 0x7F).
                                                             //
#include <iarduino_I2C_Software.h>                           //   Подключаем библиотеку для работы с программной шиной I2C, до подключения библиотеки iarduino_I2C_DSL.
SoftTwoWire sWire(3,4);                                      //   Создаём объект программной шины I2C указав выводы которым будет назначена роль линий: SDA, SCL.
                                                             //
#include <iarduino_I2C_DSL.h>                                //   Подключаем библиотеку для работы с датчиком освещённости I2C-flash (Digital Sensor Light).
iarduino_I2C_DSL dsl;                                        //   Объявляем объект dsl для работы с функциями и методами библиотеки iarduino_I2C_DSL.
                                                             //   Если при объявлении объекта указать адрес, например, dsl(0xBB), то пример будет работать с тем модулем, адрес которого был указан.
void setup(){                                                //
    delay(500);                                              // * Ждём завершение переходных процессов связанных с подачей питания.
    Serial.begin(9600);                                      //
    while(!Serial){;}                                        // * Ждём завершения инициализации шины UART.
    if( dsl.begin(&sWire) ){                                 //   Инициируем работу с датчиком освещённости, указав ссылку на объект для работы с шиной I2C на которой находится датчик (Wire, Wire1, Wire2 ...).
        Serial.print("Найден датчик 0x");                    //
        Serial.println( dsl.getAddress(), HEX );             //   Выводим текущий адрес модуля.
        if( dsl.changeAddress(newAddress) ){                 //   Меняем адрес модуля на newAddress.
            Serial.print("Адрес изменён на 0x");             //
            Serial.println(dsl.getAddress(),HEX );           //   Выводим текущий адрес модуля.
        }else{                                               //
            Serial.println("Адрес не изменён!");             //
        }                                                    //
    }else{                                                   //
        Serial.println("Датчик не найден!");                 //
    }                                                        //
}                                                            //
                                                             //
void loop(){                                                 //
}                                                            //
