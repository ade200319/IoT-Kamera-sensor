# Projekt: Raspberry Pi – Kamera, Rörelsesensor och Webbserver (C)

Detta projekt går ut på att bygga ett system där en **Raspberry Pi**:

* känner av rörelse med en sensor
* tar en bild med kamera
* sparar bilden lokalt
* gör bilden åtkomlig via en **webbserver skriven i C**

Allt körs på **samma Raspberry Pi**.

---

## Systemöversikt

Raspberry Pi fungerar både som:

* **inbyggt system** (sensor + kamera)
* **webbserver** (HTTP)

En dator eller mobil används endast för att **visa bilderna i webbläsare**.

---

## Flödesschema (övergripande)

```
[Start Raspberry Pi]
        |
        v
[Start webbserver (C)]
        |
        v
[Start sensorprogram (C)]
        |
        v
[Programmet väntar på rörelse]
        |
        v
[Rörelse upptäcks?] ---- Nej ----> (Vänta)
        |
       Ja
        |
        v
[Ta bild med kamera]
        |
        v
[Spara bild på filsystemet]
        |
        v
[Bilden kan visas via webbläsare]
```

---

## Programuppdelning

Projektet består av **två separata C-program**:

### 1. Sensor- och kameraprogram (`sensor.c`)

Ansvarar för:

* läsa GPIO (rörelsesensor)
* ta bild med kamera
* spara bilden som fil

### 2. Webbserver (`server.c`)

Ansvarar för:

* lyssna på nätverksport (HTTP)
* ta emot webbläsarförfrågningar
* skicka tillbaka den senast tagna bilden

Programmen delar **samma mapp och filsystem**.

---

## Flödesschema – sensorprogram

```
[Start sensorprogram]
        |
        v
[Initiera GPIO]
        |
        v
[Oändlig loop]
        |
        v
[Läs rörelsesensor]
        |
        v
[Rörelse?] ---- Nej ----> (Fortsätt loop)
        |
       Ja
        |
        v
[Ta bild med kamera]
        |
        v
[Spara bild som t.ex. senaste.jpg]
        |
        v
[Fördröj kort stund]
        |
        v
[Tillbaka till loop]
```

---

## Flödesschema – webbserver

```
[Start serverprogram]
        |
        v
[Skapa socket]
        |
        v
[Bind socket till port]
        |
        v
[Listen – vänta på klient]
        |
        v
[Accept – klient ansluter]
        |
        v
[Läs HTTP-request]
        |
        v
[GET-förfrågan?]
        |
       Ja
        |
        v
[Läs bildfil från disk]
        |
        v
[Skicka HTTP-svar + bild]
        |
        v
[Stäng anslutning]
        |
        v
[Tillbaka till accept]
```

---

## Kommunikationsflöde (nätverk)

```
Webbläsare        Raspberry Pi
    |                   |
    |  HTTP GET /bild   |
    |------------------>|
    |                   |
    |   Bild (JPEG)     |
    |<------------------|
```

---

## Viktiga tekniska begrepp

* **Socket** – ett handtag för nätverkskommunikation
* **TCP** – tillförlitlig kommunikation
* **HTTP** – protokoll som webbläsare använder
* **Port** – t.ex. 8080, serverns "dörr"
* **GPIO** – Raspberry Pis in- och utgångar

---

## Varför denna arkitektur valdes

* Allt körs på samma Linux-system
* Enkel att felsöka och demonstrera
* Kräver inga externa servrar
* Passar bra för C och lågnivåförståelse

---

## Sammanfattning

Projektet visar hur:

* hårdvara (sensor + kamera)
* operativsystem (Linux)
* nätverk (TCP/IP, HTTP)
* och C-programmering

kan kombineras i ett fungerande system på en Raspberry Pi.

- Spara tidpunkt och sensorinformation i databas  
- Stöd för flera kameror  
- Molnlagring  
- Notiser vid rörelse  

## Teknik
Python, FastAPI, Raspberry Pi, GPIO, HTTP
