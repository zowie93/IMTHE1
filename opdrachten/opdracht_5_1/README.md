# Opdracht 5.1 - Uitleg

Elke IMTHE-Box bevat unieke componenten. Zoek naar de datasheets van deze componenten en maak een kort verslag per component over de protocollen die gebruikt worden en hoe je dit moet gebruiken vanuit de AVR code.

# Samenvatting

Als unieke componenten heb ik:

- Matrix van 8x8 (output)
- DHT11 sensor (input)



Deze componenten zal ik hieronder beschrijven. 

**Matrix van 8x8 (output)**

Dit is een uniek component wat in mijn box zit. De meeste informatie komt uit de [datasheet]. Het heet 8x8 matrix omdat het bestaat uit 64 leds namelijk 8 rijen pinnen en 8 kolommen pinnen. Om een ledje te laten branden heb je een combinatie nodig van 1 rij en 1 kolom. De matrix is in verschillende kleuren te verkrijgen bij de groothandel wij hebben echter de matrix met de rode kleur ledjes. Het component bevat zelf geen resistors dus bij het aansluiten moet je wel bij elke pin een resistor ertussen zetten. In de [datasheet] zie je ook het volledige internal circuit voor de matrix. 
[![Matrix 8x8 internal circuit](https://github.com/zowie93/IMTHE1/blob/master/opdrachten/opdracht_5_1/assets/img/matrix-pinlayout.png?raw=true)](https://github.com/zowie93/IMTHE1/blob/master/opdrachten/opdracht_5_1/assets/img/matrix-pinlayout.png?raw=true)



**DHT11 Sensor**

Als tweede uniek component heb ik een DHT11 Sensor gekregen dit is het broertje van de DHT22 sensor die iets duurder is en wat meer accurater. De DHT11 kan de temperatuur meten en de luchtvochtigheid in de omgeving waar de sensor zich bevindt. Hiermee hebben we ook gelijk onze input voor de eindopdracht. De temperatuur kan gemeten worden van 0 tot en met 50 graden celsuis en kan plus minus 2 graden afwijken van de realiteit. De luchtvochtigheid kan gemeten worden van 20% tot en met 80% met een afwijking van 5%. De sensor heeft een samplingrate van 1Hz dit betekend dat die de waarde maar per seconde kan uitrekenen. 

Ik heb de volgende [datasheet-dht11] gedownload en bestudeerd.

De pinnen op de DHT11 kunnen gevonden in de onderstaande tekening. Er is echter maar 1 pin waar de digitale data uitkomt. Dit verbaasde mij enorm maar toen ik verder ging lezen over deze sensor werd het mij al snel duidelijk. Dit komt door het Single Wire Two Way protocol die zorgt ervoor dat de data over 1 pin verstuurd kan worden. Je kan namelijk aangeven welke data je wilt hebben met de pull-up en pull-down. Je zorgt ook dat de DHT11 aangesloten wordt op de 5 volt pin. 

DHT11 Pin layout:
[![DHT11 Pin Layout](https://github.com/zowie93/IMTHE1/blob/master/opdrachten/opdracht_5_1/assets/img/dht11-pinout.png?raw=true)](https://github.com/zowie93/IMTHE1/blob/master/opdrachten/opdracht_5_1/assets/img/dht11-pinout.png?raw=true)

Je hebt een volgorde hoe je precies aan de verschillende data komt namelijk door de request, response en de data reading. 

Met request zorg je ervoor dat je de data opvraagt met een pull-down langer dan 18ms om te versturen vervolgt door een pull-up van 40us. Dan wordt pas de response gestuurd.

De response zorgt er dus voor dat het request data terugkrijgt. Deze bestaat uit een lage pin van 54us en hoge pin van 80us.

De reponse geeft een data terug in de vorm van 5 pakketen. van ieder 8 bit met een simpele berekening komt dit uit op een totaal van 40 bits. Elk pakket van 8 bit heeft een communicatie gevolgd in de volgende volgorde.

- Als eerste wordt de pin op low gezet voor 54us
- De pin wordt erna op high gezet voor 24us 
- Deze combinatie zorgt ervoor dat het binnen de reeks van 0 en 70us blijft zodat het een 1 wordt. 
- Aan het einde wordt de pin weer op low gezet voor 54us. 



Elk pakket heeft natuurlijk andere inhoud. 

1. Intergraal luchtvochtigheid.
2. Decimaal luchtvochtigheid.
3. Intergraal temperatuur.
4. Decimaal temperatuur.
5. Checksum van alle waarden van de 4 hierboven aangegeven.

[datasheet]: https://cdn-shop.adafruit.com/datasheets/BL-M12A881.PDF
[datasheet-dht11]: https://www.optimusdigital.ro/index.php?controller=attachment&amp;id_attachment=59