// ПРИМЕР СМЕНЫ АДРЕСОВ НЕСКОЛЬКИХ МОДУЛЕЙ:                  // * Строки со звёздочкой являются необязательными.
// Требуется установить библиотеку <iarduino_I2C_Software.h> //
// Требуется установить библиотеку <iarduino_I2C_Address.h>  //
                                                             //
#include <iarduino_I2C_Software.h>                           //   Подключаем библиотеку для работы с программной шиной I2C, до подключения библиотеки iarduino_I2C_Address.
SoftTwoWire sWire(3,4);                                      //   Объявляем  объект программной шины I2C указав выводы которым будет назначена роль линий: SDA, SCL.
                                                             //
#include <iarduino_I2C_Address.h>                            //   Подключаем библиотеку для работы с адресами модулей линейки I2C-flash.
iarduino_I2C_Address j[]={0xA4,0xA5,0xA6,0xA7};              //   Определяем массив объектов, указав текущие адреса модулей I2C-flash на шине I2C.
                                                             //   Допускается объявить массив без указания адресов, например, iarduino_I2C_Address j[4]; Адреса модулей будут определены автоматически.
void setup(){                                                //
     delay(500);                                             // * Ждём завершение переходных процессов связанных с подачей питания.
     Serial.begin(9600);                                     //
     while(!Serial){;}                                       // * Ждём завершения инициализации шины UART.
//   Начинаем работу с модулями:                             //   Указанные действия можно выполнить в цикле.
     j[0].begin(&sWire); // &Wire, &Wire1, &Wire2 ...        //   Функция begin() принимает ссылку на объект для работы с шиной I2C и проверяет существование модуля на этой шине.
     j[1].begin(&sWire); // &Wire, &Wire1, &Wire2 ...        //   К функции begin() можно обратиться с проверкой: if( j[1].begin(&sWire) ){/*модуль обнаружен*/;}else{/*нет*/;}
     j[2].begin(&sWire); // &Wire, &Wire1, &Wire2 ...        //   После begin(), результат обнаружения модуля остаётся доступным для чтения: if( j[2] ){/*модуль был обнаружен*/;}else{/*нет*/;}
     j[3].begin(&sWire); // &Wire, &Wire1, &Wire2 ...        //   Если модули находятся на основной аппаратной шине I2C (под управлением объекта Wire), то ссылку на объект можно не указывать: j[3].begin();
//   Выводим старые адреса модулей на шине I2C:              //   Указанные действия можно выполнить в цикле.
     Serial.println( F("Найдены модули:") );                 //
     if( j[0] ){ Serial.print  ("0x");                       //   Если нет модуля с адресом 0xA4, то условие if(j[0]) не будет выполнено.
                 Serial.print  (j[0], HEX);                  //   Выводим адрес модуля в формате HEX.
                 Serial.print  (", ");                       //
                 Serial.println(j[0].getName());             //   Выводим название модуля.
     }                                                       //
     if( j[1] ){ Serial.print  ("0x");                       //   Выполняем аналогичные действия для модулей j[1], j[2], j[3]...
                 Serial.print  (j[1], HEX);                  //
                 Serial.print  (", ");                       //
                 Serial.println(j[1].getName());             //
     }                                                       //
     if( j[2] ){ Serial.print  ("0x");                       //
                 Serial.print  (j[2], HEX);                  //
                 Serial.print  (", ");                       //
                 Serial.println(j[2].getName());             //
     }                                                       //
     if( j[3] ){ Serial.print  ("0x");                       //
                 Serial.print  (j[3], HEX);                  //
                 Serial.print  (", ");                       //
                 Serial.println(j[3].getName());             //
     }                                                       //
//   Указываем новые адреса модулям:                         //   Указанные действия можно выполнить в цикле.
     Serial.println( F("Меняем адреса...") );                //
     j[0]=0x10;                                              //   Важно назначать адреса, которых ещё нет на шине I2C!!!
     j[1]=0x11;                                              //   Успех записи нового адреса можно проверить по результату присвоения: if( j[1]= 0x11 ){/*успешно*/;}else{/*провал*/;}
     j[2]=0x12;                                              //   Успех записи нового адреса можно проверить после присвоения:         if( j[2]==0x12 ){/*успешно*/;}else{/*провал*/;}
     j[3]=0x13;                                              //   Менять адреса позволяют только модули линейки Flash I2C.
//   Выводим адреса модулей на шине I2C:                     //   Указанные действия можно выполнить в цикле.
     Serial.println("Новые адреса модулей:");                //
     if( j[0] ){ Serial.println(j[0], HEX); }                //   Дополнительно можно вывести:
     if( j[1] ){ Serial.println(j[1], HEX); }                //   название модуля getName(), идентификатор getModel(), тип модуля getDevice(),
     if( j[2] ){ Serial.println(j[2], HEX); }                //   версию прошивки getVersion(), наличие подтяжки getPullI2C().
     if( j[3] ){ Serial.println(j[3], HEX); }                //
}                                                            //
                                                             //
void loop(){                                                 //
}                                                            //
                                                             //
//  ПРИМЕЧАНИЕ:                                              //   Пример библиотеки "sortingAll" показывает как автоматически отсортировать все адреса по порядку...
//  Если объявить массив объектов (j) без указания адресов,  //
//  например, iarduino_I2C_Address j[4];                     //
//  То адреса будут определены автоматически по возрастанию. //
//  Нулевой элемент массива объектов (j[0]) будет работать с //
//  модулем имеющем наименьший адрес.                        //
//  Если количество устройств на шине меньше чем количество  //
//  элементов массива объектов, то «лишние» элементы массива //
//  не пройдут проверку if(j[n]) и проигнорируют присвоение. //