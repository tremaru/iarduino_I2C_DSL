// ПРИМЕР ЧТЕНИЯ ВСЕХ ЗНАЧЕНИЙ ДАТЧИКА:                      // * Строки со звёздочкой являются необязательными.
// Требуется установить библиотеку <iarduino_I2C_Software.h> //   https://iarduino.ru/file/627.html
                                                             //
// Датчик освещенности, люксметр, FLASH-I2C:                 //   https://iarduino.ru/shop/Sensory-Datchiki/datchik-osveschennosti-lyuksmetr-i2c-trema-modul-v2-0.html
// Информация о подключении модулей к шине I2C:              //   https://wiki.iarduino.ru/page/i2c_connection/
// Информация о модуле и описание библиотеки:                //   https://wiki.iarduino.ru/page/DSL-trema-i2c/
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
    dsl.begin(&sWire);                                       //   Инициируем работу с датчиком освещённости, указав ссылку на объект для работы с шиной I2C на которой находится датчик (по умолчанию &Wire).
}                                                            //
                                                             //
void loop(){                                                 //
    Serial.print("Освещённость = ");                         //
    Serial.print( dsl.getLux() );                            //   Выводим текущую освещённость, от 0 до 8191 лк.
    Serial.print(" лк.\t");                                  //
    Serial.print("Мерцание = ");                             //
    Serial.print( dsl.getPulsation() );                      //   Выводим коэффициент пульсаций света, от 0 до 100%.
    Serial.print("%\t");                                     //
    Serial.print("Близость = ");                             //
    Serial.print( dsl.getProximity() );                      //   Выводим близость препятствий, от 0 (нет  препятствий) до 1023 (датчик перекрыт).
    Serial.print(".\r\n");                                   //
    delay(500);                                              // * Задержка позволяет медленнее заполнять монитор последовательного порта.
}                                                            //