# 🤖 Arduino Mega Mecanum Robot (OSOYOO FlexiRover) – Primjeri i Uputstva

Dobrodošli u repozitorij s primjerima kôda za edukacijskog robota s **Mecanum (omnidirekcijskim) kotačima**, pokretanog **Arduino Mega 2560** mikrokontrolerom i snažnim **520 motorima s enkoderima**.

Ovaj repozitorij pripremljen je kako bi učenicima i nastavnicima pružio jasan, strukturiran i jednostavan uvod u robotiku, rad s motorima, senzorima te bežičnim upravljanjem (Bluetooth i Wi-Fi).

🔗 **Službena dokumentacija proizvođača:**  
[OSOYOO FlexiRover Basic Robot Car for Mega2560 (Model 2024007400)](https://osoyoo.com/2024/08/26/osoyoo-flexirover-basic-robot-car-for-mega2560-running-520-motor-with-mecanum-wheel-model-2024007400/)

---

## 📑 Sadržaj
1. [O robotu i Mecanum kotačima](#-o-robotu-i-mecanum-kotačima)
2. [Priprema radnog okruženja (Arduino IDE)](#-priprema-radnog-okruženja-arduino-ide)
3. [Instalacija potrebnih biblioteka](#-instalacija-potrebnih-biblioteka)
4. [Pregled lekcija i primjera](#-pregled-lekcija-i-primjera)
   - [Lekcija 1: Osnovno kretanje (Test kotača)](#lekcija-1-osnovno-kretanje-test-kotača)
   - [Lekcija 2: Izbjegavanje prepreka](#lekcija-2-izbjegavanje-prepreka-obstacle-avoidance)
   - [Lekcija 3: Praćenje linije](#lekcija-3-praćenje-linije-line-tracking)
   - [Lekcija 4: Bluetooth upravljanje](#lekcija-4-bluetooth-upravljanje)
   - [Lekcija 5: Wi-Fi upravljanje aplikacijom](#lekcija-5-wi-fi-upravljanje-aplikacijom-udp)
   - [Lekcija 6: Praćenje objekta (Ultrazvuk)](#lekcija-6-praćenje-objekta-object-follow)
   - [Lekcija 7: Praćenje prepreke (IR senzori)](#lekcija-7-praćenje-prepreke-ir-follow-me)
5. [Kako učitati kôd na robota](#-kako-učitati-kôd-na-robota-upload-koraci)
6. [Česta pitanja i rješavanje problema (Troubleshooting)](#-česta-pitanja-i-rješavanje-problema-troubleshooting)
7. [Sigurnost na radionici](#-sigurnost-na-radionici)

---

## 🛞 O robotu i Mecanum kotačima

Za razliku od standardnih kotača, **Mecanum kotači** imaju valjke postavljene pod kutom od 45°. Kombiniranjem različitih smjerova i brzina vrtnje svakog pojedinog motora, robot se može kretati u bilo kojem smjeru bez zakretanja šasije:

- ⬆️ **Naprijed / Nazad** (svi kotači se vrte u istom smjeru)
- 🔄 **Rotacija u mjestu** (lijeva i desna strana vrte se u suprotnim smjerovima)
- ⬅️➡️ **Bočno kretanje (Strafe / klizanje lijevo i desno)** (dijagonalni parovi kotača vrte se suprotno)
- ↗️↘️ **Dijagonalno kretanje** (vrte se samo dva dijagonalna kotača)

> **Važno pri sastavljanju:** Pazite da su kotači pravilno montirani! Gledano odozgo prema robotu, valjci na kotačima moraju tvoriti oblik slova **"X"** (ili strelicu prema naprijed), a ne oblik slova "O". Ako su kotači zamijenjeni, robot neće moći ići bočno.

---

## 💻 Priprema radnog okruženja (Arduino IDE)

Kako biste programirali robota, potrebno je na računalo instalirati **Arduino IDE**:

1. Preuzmite i instalirajte [Arduino IDE](https://www.arduino.cc/en/software) (preporučena verzija: 2.x ili novija).
2. Spojite Arduino Mega na računalo pomoću **USB kabela (Type-B)**.
3. U Arduino IDE-u postavite odgovarajuću ploču i procesor:
   - **Tools (Alati)** ➔ **Board (Ploča)** ➔ **Arduino AVR Boards** ➔ **Arduino Mega or Mega 2560**
   - **Tools (Alati)** ➔ **Processor** ➔ **ATmega2560 (Mega 2560)**
   - **Tools (Alati)** ➔ **Port** ➔ Odaberite COM port na koji je robot spojen (npr. `COM3`, `COM4` na Windowsima ili `/dev/ttyUSB0` / `/dev/ttyACM0` na Linuxu/Macu).

---

## 📚 Instalacija potrebnih biblioteka

Za većinu primjera dovoljne su ugrađene biblioteke (kao što je `Servo`), no za **Lekciju 5 (Wi-Fi)** potrebna je dodatna biblioteka:

### Instalacija `WiFiEsp`:
1. U Arduino IDE-u otvorite: **Sketch** ➔ **Include Library** ➔ **Manage Libraries...** (ili prečac `Ctrl + Shift + I`).
2. U tražilicu upišite: `WiFiEsp`
3. Pronađite biblioteku autora **Bruno Portaluri** i kliknite **Install**.

---

## 📂 Pregled lekcija i primjera

| Mapa lekcije | Naziv lekcije | Korišteni senzori / moduli |
| :--- | :--- | :--- |
| `m2-lesson1` | **Osnovno kretanje** | 4x 520 motora, Model-Y driver |
| `m2-lesson2` | **Izbjegavanje prepreka** | Ultrazvučni senzor (HC-SR04) + SG90 servo |
| `m2-lesson3` | **Praćenje linije** | 5-kanalni infracrveni (IR) modul za liniju |
| `m2-lesson4` | **Bluetooth upravljanje** | Bluetooth modul (HC-02 / BLE) |
| `m2-lesson5` | **Wi-Fi upravljanje** | OSOYOO ESP8266 Wi-Fi shield |
| `m2-lesson6` | **Praćenje objekta** | Ultrazvučni senzor + Servo |
| `m2-lesson7-followme` | **Follow-me praćenje** | 2x IR senzori prepreka (lijevi i desni) |

---

### Lekcija 1: Osnovno kretanje (Test kotača)
📁 **Putanja:** `m2-lesson1/m2-lesson1.ino`  
- **Cilj:** Upoznavanje s mehanikom robota i provjera smjerova vrtnje motora.
- **Što robot radi:** Robot izvodi demonstracijski ciklus kretanja: naprijed, nazad, rotacija ulijevo/udesno, bočno pomicanje ulijevo/udesno te dijagonalno kretanje.
- 💡 *Savjet za učenike:* Prilikom prvog pokretanja podignite robota na stalak (ili kutiju) kako bi kotači bili u zraku i provjerite okreću li se u ispravnim smjerovima!

---

### Lekcija 2: Izbjegavanje prepreka (Obstacle Avoidance)
📁 **Putanja:** `m2-lesson2/m2-lesson2.ino`  
- **Cilj:** Autonomna vožnja pomoću senzora udaljenosti.
- **Što robot radi:** Robot se vozi prema naprijed. Kada ultrazvučni senzor prepozna prepreku bliže od zadane udaljenosti (npr. 25 cm), robot se zaustavlja, servo motor zakreće senzor ulijevo i udesno kako bi izmjerio prostor, te robot skreće u smjeru gdje ima više slobodnog prostora.

---

### Lekcija 3: Praćenje linije (Line Tracking)
📁 **Putanja:** `m2-lesson3/m2-lesson3/m2-lesson3.ino`  
- **Cilj:** Praćenje iscrtane crne linije na bijeloj (svijetloj) podlozi.
- **Što robot radi:** Modul s IR senzorima usmjeren prema podu očitava kontrast između crne trake i bijele podloge. Robot prilagođava snagu motora kako bi ostao centriran na traci.
- 💡 *Podešavanje:* Na IR modulu se nalaze mali potenciometri. Ako robot gubi liniju, pomoću malog odvijača podesite osjetljivost senzora tako da LED indikatori reagiraju točno na prijelazu s bijelog na crno.

---

### Lekcija 4: Bluetooth upravljanje
📁 **Putanja:** `m2-lesson4/m2-2560-lesson4.ino`  
- **Cilj:** Bežično upravljanje robotom u stvarnom vremenu putem Bluetooth veze.
- **Upute:**
  1. Provjerite je li Bluetooth modul ispravno spojen na serijske pinove (Serial1 – D18/D19).
  2. Uparite pametni telefon s Bluetooth modulom (najčešći PIN je `1234` ili `0000`).
  3. Pokrenite OSOYOO Bluetooth aplikaciju i upravljajte kretanjem pomoću virtualnog upravljača.

---

### Lekcija 5: Wi-Fi upravljanje aplikacijom (UDP)
📁 **Putanja:** `m2-lesson5/m2-lesson5/`  
Lekcija nudi dva načina povezivanja:

1. **`m2-lesson5a` (AP način – Access Point):**
   - Robot sam stvara vlastitu Wi-Fi mrežu (podrazumijevano ime: `osoyoo_robot`).
   - Mobitelom se spojite na tu mrežu (nije potreban vanjski internet ili router).
   - Idealno za radionice i učionice gdje nema dostupnog Wi-Fi interneta.
2. **`m2-lesson5b` (STA način – Station):**
   - Robot se spaja na vašu postojeću Wi-Fi mrežu (učionicu ili kućni router).
   - U kôdu je potrebno upisati ime i lozinku mreže:
     ```cpp
     char ssid[] = "Naziv_Vase_Mreze";
     char pass[] = "Lozinka_Mreze";
     ```
   - Mobitel mora biti spojen na istu mrežu.
- 📱 **Mobilna aplikacija:** Koristi se aplikacija **OSOYOO IoT UDP Robot** (dostupna na Google Playu ili kao direktan APK s Osoyoo stranice).

---

### Lekcija 6: Praćenje objekta (Object Follow)
📁 **Putanja:** `m2-lesson6/m2-lesson6.ino`  
- **Cilj:** Robot održava zadanu udaljenost od objekta ispred sebe.
- **Što robot radi:** Ako postavite ruku ili karton ispred senzora:
  - ako se udaljite – robot će krenuti naprijed prema vama,
  - ako se približite – robot će se povući unatrag.

---

### Lekcija 7: Praćenje prepreke (IR Follow Me)
📁 **Putanja:** `m2-lesson7-followme/followme/followme.ino`  
- **Cilj:** Praćenje kretanja pomoću dva infracrvena senzora prepreka (lijevi i desni).
- **Što robot radi:** Robot uspoređuje očitavanja s lijevog i desnog senzora. Ako se ruka pomakne ulijevo, robot skreće ulijevo; ako je ravno ispred oba senzora, ide ravno.

---

## 🚀 Kako učitati kôd na robota (Upload koraci)

1. **Postavite robota na stalak** kako kotači ne bi dodirivali podlogu.
2. Otvorite željenu `.ino` datoteku u Arduino IDE-u.
3. Provjerite u izborniku **Tools** da su odabrani **Arduino Mega or Mega 2560** i točan **COM port**.
4. Pritisnite gumb **Verify (Kvačica ✓)** kako biste provjerili prolazi li kôd kompajliranje bez grešaka.
5. Pritisnite gumb **Upload (Strelica ➔)** za prijenos na mikrokontroler.
6. Pričekajte poruku **"Done uploading"** u dnu ekrana.
7. Spojite baterije, uključite prekidač napajanja na driveru motora i testirajte!

---

## 🛠️ Česta pitanja i rješavanje problema (Troubleshooting)

### ❓ Arduino IDE javlja: *"The file needs to be inside a sketch folder..."*
- **Rješenje:** Arduino IDE zahtijeva da se `.ino` datoteka nalazi unutar mape s **potpuno istim imenom** (npr. datoteka `m2-lesson1.ino` mora biti unutar mape `m2-lesson1/`). Ako raspakirate datoteke, pripazite da ne mijenjate strukturu mapa.

### ❓ Greška pri uploadu: *"avrdude: stk500v2_ReceiveMessage(): timeout"*
- **Rješenje 1:** Provjerite jeste li odabrali točan COM port u izborniku **Tools ➔ Port**.
- **Rješenje 2:** Ako su Bluetooth ili Wi-Fi moduli spojeni na pinove `TX0`/`RX0` (glavni serijski port za programiranje), oni mogu ometati prijenos kôda. Provjerite jesu li spojeni na `Serial1` (`D18`/`D19`) ili privremeno odspojite modul dok traje upload.
- **Rješenje 3:** Provjerite USB kabel – koristite kvalitetan podatkovni kabel, a ne kabel samo za punjenje.

### ❓ Robot se kreće u suprotnom smjeru ili čudno rotira umjesto ravno
- **Rješenje 1 (Ožičenje motora):** Zamijenite mjesta žicama tog motora na izlazu iz motornog drivera (Model-Y) ili u kôdu prilagodite logička stanja `HIGH`/`LOW` za smjer.
- **Rješenje 2 (Raspored kotača):** Još jednom provjerite jesu li kotači montirani u "X" uzorak.

### ❓ Kotači jedva da se okreću, Arduino se resetira pri kretanju
- **Rješenje:** Baterije su prazne! Za pokretanje 4 snažna 520 motora potrebne su dobro napunjene litij-ionske baterije (18650). Kad napon padne, motori povuku veliku struju što dovodi do pada napona i resetiranja Arduina.

---

## ⚠️ Sigurnost na radionici

- 🔋 **Baterije:** Koristite isključivo preporučeni punjač za 18650 baterije. Nikada ne ostavljajte baterije na punjenju bez nadzora.
- ⚡ **Kratki spoj:** Pazite da metalni alati (odvijači) ne dođu u dodir s kontaktima na pločicama dok je napajanje uključeno.
- 🛑 **Isključivanje:** Nakon završetka rada uvijek isključite prekidač za napajanje motora kako se baterije ne bi ispraznile do kritične razine.

---

*Pripremljeno za potrebe natjecanja RobotIK 2026, nastave izvannastavnih aktivnosti i učeničkih radionica robotike.*  
*Autor primjera i repozitorija: [lovrosverko](https://github.com/lovrosverko)*
