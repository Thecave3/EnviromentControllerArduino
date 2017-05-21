# EnviromentControllerArduino
Another enviroment controller code for Arduino UNO.

Controllore camera pulita

Version 0.7 RELEASE CANDIDATE

##What is?

Rilevatore di pressione interna ed ambientale, temperatura e umidità

Componenti adottate:
 * Temperatura e Umidità: KY 015
 * Pressione esterna: MPXA6115AU/T1
 * Pressione interna : Costruito autonomamente codice compreso

 Changelog:
 * 0.4 ALPHA :Start project
 * 0.5 BETA : Revisione del codice in modo che le stampe sul seriale siano prive di descrizione per essere catturate da un programma ausiliario(putty) e inserite dentro un file CSV
 * 0.6 FINAL BETA : Aggiunta del terzo sensore al codice
 * 0.7 RC:  Aggiunta scritte esplicative per creare direttamente tabella allo startup in modo che il logger data di putty possa essere riutilizzato fin da subito per fare tabella CSV.
 * 0.8 STABLE: Corretto bug variabile segnatempo


Copyright 2016 Andrea Lacava <thecave003@gmail.com>
Based on previous work by:
 TkkrLab: <https://tkkrlab.nl/wiki/Arduino_KY-015_Temperature_and_humidity_sensor_module>
