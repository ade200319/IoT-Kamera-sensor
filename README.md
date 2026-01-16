# IoT Kamera med Rörelsesensor (Raspberry Pi + Python)

## Projektbeskrivning
Detta projekt är ett enkelt IoT-system där en Raspberry Pi med kamera och PIR-rörelsesensor tar en bild vid rörelse och skickar bilden till en Python-baserad webbserver via LAN. Webbservern tar emot bilden och sparar den i en lokal mapp.

## Funktion
När rörelse upptäcks av PIR-sensorn tänds en LED-lampa som indikator, kameran tar en bild och bilden skickas till webbservern där den sparas.

## Grundidé – endast två program
Program A (Raspberry Pi):  
Rörelse → ta bild → skicka till server  

Program B (Webbserver):  
Ta emot bild → spara i mapp  

## Flöde
PIR triggar → LED tänds → kameran tar bild → Raspberry Pi skickar bilden via LAN → servern sparar bilden

## Utrustning
- Raspberry Pi  
- Kamera (Pi Camera)  
- PIR rörelsesensor  
- LED-lampa + motstånd  
- LAN / nätverk  
- Dator eller server som kör Python  

## Implementation – 3 enkla steg
Steg 1: Webbserver  
Webbservern kör FastAPI och har en endpoint `/upload`. När Raspberry Pi skickar en bild sparas den i mappen `uploads/`.

Steg 2: Raspberry Pi – kamera  
Ett Python-program körs på Raspberry Pi som tar en bild med kameran och sparar den lokalt (t.ex. `photo.jpg`).

Steg 3: Raspberry Pi – PIR-sensor  
När PIR-sensorn känner av rörelse körs samma kod som i steg 2, men bilden skickas även till webbservern. Efter varje bild väntar systemet 10 sekunder för att undvika att ta för många bilder.

## Kommunikation
Raspberry Pi skickar bilden till en bestämd adress på servern. Servern lyssnar på den adressen och när den får en bild sparar den filen i en mapp. HTTP som är regler för hur datorer pratar med varandra och POST sättet att skicka något på.

## Cooldown-regel
Efter varje tagen och skickad bild väntar systemet 10 sekunder innan nästa bild kan tas.

## Resultat
Systemet tar automatiskt bilder vid rörelse och sparar dem på webbservern. Lösningen är enkel, stabil och lätt att bygga vidare på.

## Möjliga vidareutvecklingar
- Visa bilder i webbläsare  
- Spara tidpunkt och sensorinformation i databas  
- Stöd för flera kameror  
- Molnlagring  
- Notiser vid rörelse  

## Teknik
Python, FastAPI, Raspberry Pi, GPIO, HTTP
