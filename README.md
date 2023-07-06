PENTRU DOCUMENTAȚIA COMPLET: [Lattek Docs]([https://duckduckgo.com](https://docs.google.com/document/d/1-81m-K6sQDu1P-6rrh9l-CgVxX6aWneMaXuvqu2jdrg/edit?usp=sharing))



**Lattek Dust **

**Participanți:**

Lazăr Dragoș George

Teodor Moscaliuc

**Coordonatori:**

Buzoianu Ștefan

Balacea Georgeta

**InfoEducație 2023**

**Lattek Dust **


**Prezentare generală**

**Lattek Dust** reprezintă un sistem complex hardware-software ce permite monitorizarea calității aerului din habitate. Astfel, automatizând acțiuni precum ventilația unei încăperi și permitând chiar și persoanelor aflate la distanta să aibă grijă de sănătatea animalelor de companie dintr-un habitat dotat cu un sistem **Lattek Dust**.

Sistemul combină tehnologii variate disponibile pe piață 



* senzorii de calitate a aerului
* baze de date pentru statistici 
* motoare ce acționează sisteme mecanice 

pentru a oferi o soluție specializată, asemenea unui sistem **IoT** complex. Am decis clasificarea produsului nostru ca fiind unul utilitar deoarece îmbinăm creativitatea unui produs software obținut printr-un mix de tehnologii inovative cu resurse hardware accesibile pentru construirea unui black-box capabil să colecteze date prin senzorii săi interni.


<table>
  <tr>
   <td><strong>Probleme identificate și public țintă </strong>
   </td>
   <td><strong>Soluții</strong>
   </td>
  </tr>
  <tr>
   <td>Incăperile locuințelor pot deveni irespirabile în timpul <strong>plecărilor îndelungate</strong>. În același timp,  menținerea geamurilor deschise permanent în anumite perioade ale anului în care se manifesta intemperii - ploaie, temperaturi extreme, smog - determină scăderea confortului atunci când<strong> locatarii </strong>se întorc în propriul habitat.
   </td>
   <td rowspan="3" ><strong>Lattek Dust </strong>ajută la aerisirea încăperilor automat pe baza datelor colectate de senzori, însă permite și gestionarea acesteia manual cu ajutorul unui device mobil.
   </td>
  </tr>
  <tr>
   <td><strong>Posesorii de animale de companie</strong> nu pot controla mediul din locuință cât timp sunt plecați.
   </td>
  </tr>
  <tr>
   <td><strong>Persoanele imobilizate</strong> nu-și pot aerisi locuința singure pe timpul verii/iernii.
   </td>
  </tr>
  <tr>
   <td><strong>Persoanele ce doresc sa își îmbunătățească calitatea aerului din casa</strong> prin diferite metode nu au o evidență a stării acesteia precedente la care să se poată raporta pentru analiza progresului și a eficacității.
   </td>
   <td><strong>Lattek Dust </strong>păstrează toate datele colectate și realizează statistici pe anumite perioade de timp. Interfața conține și grafice pentru compararea ușoară a valorilor din diferite momente în timp pentru evaluarea lor.
   </td>
  </tr>
</table>


Pentru a eficientiza organizarea pe parcursul proiectului am decis să folosim soluția furnizată de **Github **pentru gestionarea sarcinilor de lucru numită generic **Kanban**. Astfel există o evidență clară a timpului consumat pentru fiecare task. De asemenea. cunoaștem stadiul de execuție pentru fiecare dintre acestea.

**Plan de dezvoltare **

**Sistem de versionare**

Ca sistem de versionare am ales **Git** prin **Github**, oferit de **Microsoft **și cel mai popular astfel de serviciu. Am lucrat într-un repository pe organizația **Lattek-Studio** unde am putut crea un **proiect Kanban** și un github actions runner pentru builduirea și deploymentul siteului și al aplicației.

Codul aplicației este disponibil **https://github.com/Lattek-Studio/projectBoromir**



**Implementarea aplicației**



1. **Backend / API**

**Tehnologii utilizate**



* **Ubuntu**
* **Docker**
* **Portainer**
* **Nginx**
* **Supabase Self Hosted**

	Aveam nevoie de un backend rapid și scalabil, dar nu aveam timpul necesar dezvoltării și întreținerii acestuia. Soluția agreata este un _backend-as-a-service(BaaS)_, care este o abordare de dezvoltare a aplicațiilor pre construită și găzduită în cloud. Acesta simplifică construirea unei aplicații și menținerea ei.

**Firebase**

**	**O primă opțiune luată în considerare a fost Firebase, un BaaS oferit de Google. Popularitatea lui ne-a atras deoarece acest framework ne punea la dispoziție un suport pe termen lung, dar costurile ridicate au reprezentat un foarte mare impediment. Limita de citire a planului gratuit de doar 10 GB era atinsă în cateva zeci de minute și ar fi trebuit să plătim destul de mult. Principala problemă a unui BaaS este că obliga utilizatorul sa ramana captiv în ecosistemul lor și pentru ca în final serviciile trebuie să plătite

.

	Dacă nu avem timp să ne construim propriul Backend și Firebase este mult prea scump ce altă soluție există?

**Supabase**

**	Supabase **este o alternativă a Firebase dezvoltată de comunitatea **open-source**. Pe lângă posibilitatea de a cumpăra un pachet găzduit la ei care e similar în preț cu Firebase,  mai există si cea de a-l hosta singuri.

De ce **Supabase**?



* E open source și poate fi hostat de noi
* Are dezvoltate o serie de funcționalități disponibile în mod gratuit
* Folosește o bază de date relațională POSTgreSQL potrivită pentru proiectul nostru.

<table>
  <tr>
   <td>
Site oficial
   </td>
   <td>https://supabase.com/
   </td>
  </tr>
  <tr>
   <td>Licență
   </td>
   <td>MIT, soft open-source
   </td>
  </tr>
  <tr>
   <td>Utilizatori activi
   </td>
   <td>+150.000
   </td>
  </tr>
</table>


**Cum am hostat?**

Folosind **Docker **cu docker-compose și un server de _Linux_ pe Oracle Cloud. Oracle Cloud este o platformă de cloud computing care oferă servicii de infrastructură și găzduire pentru aplicații și servicii. Am ales acest provider deoarece oferă un server VM ARM cu 24GB de RAM gratuit. Am urmărit tutorialul și am hostat o instanță de Supabase. Cu Nginx ca reverse proxy am securizat dashboardul web printr-o autentificare cu user și parolă și ne-am asigurat că nu deschidem porturi inutile pe server.

**Securitate**

**Nginx **este folosit ca reverse proxy pentru Supabase API, Supabase Dashboard, dar și site-ul web (**dust.lattek.org**). Am implementat conexiunea HTTPS folosind **CertBot **pentru a genera certificate SSL Let's Encrypt. Aceste certificate SSL permit comunicarea securizată prin intermediul protocolului HTTPS, asigurând confidențialitatea și integritatea datelor transmise între utilizator și server.

	Pentru o securitate sporită folosim **CloudFlare **drept  **DNS Provider**. Acesta ne oferă protecție împotriva diferitelor tipuri de atacuri DDoS și diferite servicii de accelerare ale traficului dar și caching. Din fericire planul gratuit oferă toate acestea.

**Supabase **pune la dispoziție o bază de date relațională **POSTgreSQL **care permite adăugarea unor politici de securitate pentru a evita accesul persoanelor neautorizate.	 Acestea se pot adăuga din dashboard-ul admin Supabase.

De asemenea librăria client Supabase.js oferă protecție împotriva SQL Injections deoarece abstractizează query-urile.



**2. Interfață (UI / UX / CUI)**

**Tehnologii utilizate**



* **SvelteKit**
* **Capacitor.js**
* **Supabase.js**

Solutia agreata pentru frontend este  un workflow de dezvoltare al aplicațiilor bazat pe tehnologii web. Principalul motiv este acela ca ne permite o arhitectura de tipul **write once run anywhere **(arhitectura specifica limbajului de programare JavaScript). În acest mod putem construi aplicații mobile native de iOS si Android, aplicații desktop pentru Windows, Linux sau MacOS, sau aplicația web din același cod sursă, reducând masiv timpul de dezvoltare și crescând audiența produsului..

**SvelteKit **este un framework javascript bazat pe Svelte, un framework specializat pe UI-Design într-un mod plăcut pentru dezvoltator. Ne permite o dezvoltare rapidă cu cod curat și viitoare modificări ușoare.


<table>
  <tr>
   <td>Site oficial
   </td>
   <td>https://kit.svelte.dev/
   </td>
  </tr>
  <tr>
   <td>Licență
   </td>
   <td>MIT, soft open source
   </td>
  </tr>
  <tr>
   <td>Descărcări
   </td>
   <td>+750.000/lună
   </td>
  </tr>
</table>


De ce am ales **SvelteKit**?



* E rapid! Folosind tehnologia **Vite **permite actualizarea real time a serverului în timpul dezvoltării
* E distractiv! Sintaxa minimala, zero boilerplate code și similaritate cu limbajul de bază permit un learning curve mic și o experiență plăcută.
* E flexibil! Poate construi orice fel de aplicație web și o poate rula oriunde există Javascript.

**Capacitor.js** este un compiler care ne permite să construim aplicații native de Android, IOS, dar și desktop (cu ajutorul lui Electron.js) folosind HTML, JavaScript și CSS.


<table>
  <tr>
   <td>Site oficial
   </td>
   <td>https://capacitorjs.com/
   </td>
  </tr>
  <tr>
   <td>Licență
   </td>
   <td>MIT, soft open source
   </td>
  </tr>
  <tr>
   <td>Descărcări
   </td>
   <td>1.600.000/lună
   </td>
  </tr>
</table>


**Supabase.js** este o interfață care ne permite interacțiunea cu backendul Supabase într-un mod intuitiv și sustenabil.


<table>
  <tr>
   <td>Site oficial
   </td>
   <td>https://supabase.com/
   </td>
  </tr>
  <tr>
   <td>Licență
   </td>
   <td>MIT, soft open source
   </td>
  </tr>
  <tr>
   <td>Descărcări
   </td>
   <td>+550.000/lună
   </td>
  </tr>
</table>


**Mod de dezvoltare**



1. Construim o aplicație web folosind **SvelteKit **și **Supabase.js** pentru a interacționa cu Backendul. 
2. Construim aplicația folosind adaptorul @svelte.js/adapter-static si obținem un site static. 
3. Cu ajutorul lui** Capacitor.js** traducem codul html, javascript si css în cod specific dispozitivului țintă (pentru Android codul de Javascript e tradus în Kotlin). 
4. Folosind Android Studio construim aplicația nativă.

**Interfață**

Am ales un model de design minimalist pentru a fi utilizat de oricine. Am ales o paletă de culori simplă formată din 2 culori de fundal (una mai închisă și una mai deschisă) pentru layoutul de bază și o singură culoare accent pentru a atrage atenția asupra elementelor cheie.

Am folosit regula **60-30-10 **pentru a crea un aranjament armonios. 



* 60% reprezintă culoarea dominantă, noi alegând culoarea închisă de fundal. 
* 30% reprezintă culoarea deschisă de fundal 
*  restul de 10% culoarea accent.

Am folosit site-uri precum **pinterest **și **dribble **pentru a vedea ce oferă aplicațiile similare și a decide unde putem îmbunătății designul.

**Workflow interfață**

Pentru a crea designul aplicației am decis să folosim **_Figma_**, o platformă web colaborativă specializată pe UI / UX. 

De ce **Figma**?



* E colaborativă! Ne-a permis să lucrăm simultan la același UI lucru care a redus timpul de dezvoltare.
* E puternică! Folosind dezvoltare pe bază de componente am putut modulariza designul, permițând modificări în masă mai rapide. Folosind variabilele de culoare am putut schimba culoarea întregului design cu un singur click.
* E prototipală! Folosind sistemul său de prototipuri și animații am putut vizualiza aplicația înainte de a o construi. Acest lucru ne-a permis să dezvoltăm aplicația rapid deoarece știam cum ne doream să arate.

<table>
  <tr>
   <td>
Link prototip
   </td>
   <td>https://www.figma.com/proto/2QMr3KGKGJquNjA7OljI2M/Buzo?type=design&node-id=1-388&scaling=min-zoom&page-id=0%3A1&starting-point-node-id=1%3A388
   </td>
  </tr>
</table>

	După finalizarea designului am început dezvoltarea propriu-zisă. Folosind **SvelteKit **am dezvoltat UI-ul, iar cu **Supabase.js** am adaugat interacțiunea cu backendul.



**Experiența Utilizatorului**

Experiența utilizatorului sau UX trebuie sa fie simplă astfel încât oricine să poată să  folosească aplicația, dar și să cuprindă toate funcțiile necesare unui utilizator avansat.

**Responsive design**

După cum am explicat în modul de dezvoltare, noi pornim de la un site web static și construim o aplicație care poate fi folosită pe orice platformă. Pentru a păstra conceptul de o singură bază de cod, website-ul nostru trebuie să fie responsive. Folosind puterea CSS și a media query-urilor am creat un site care se adaptează la orice dispozitiv

.

**Navigarea pe ecrane mici**

	Pentru dispozitivele mobile am optat pentru un navbar poziționat în partea de jos a ecranului. Acest lucru ne oferă posibilitatea folosirii dispozitivului cu o singură mână. Funcțiile folosite mai rar au rămas în partea de sus. De asemenea butoanele care permit deschiderea și închiderea perifericelor (geam și ventilator) sunt amplasate deasupra din aceleași motive.

**Navigarea pe ecrane mari**

	Pentru dispozitivele mai mari am decis înlocuirea navbarului în partea de jos cu un sidebar. Acest lucru ne permite afișarea mai multor informații, dar și accesarea butoanelor cu o singură mână pe dispozitivele de tip tabletă

**Navigarea desktop / laptop**

Pentru desktop și laptop am păstrat sidebarul deoarece este ușor de accesat cu un mouse.



**3.Stabilitatea aplicației**

	Aplicația este foarte eficientă din punct de vedere al resurselor. Din punct de vedere al stocării aceasta folosește 9.6MB: 



* 4.3MB aplicația sursă
* 4.6 MB date
* 0.7MB cache. 

Utilizarea maxim de memorie este de 73MB, lucru comparabil cu o aplicație de vreme.

Pentru a preveni posibile crash-uri la nivel de aplicație, folosim structuri de tip **try-catch**. Astfel, exista posibilitatea de afișare  în consola de debugging a stack-ului specific unei excepții fără a bloca funcționalitatea aplicației.



**Testarea produsului**

Testarea produsului a fost realizată de către membrii echipei de dezvoltare și putem defini acest mod de testare ca fiind **smoke test. **Smoke testing reprezinta o metodă de testare a software-ului care este utilizată pentru a determina dacă un nou build software este pregătit pentru următoarea fază de testare.

**Maturitatea aplicației**

În acest stadiu al dezvoltării aplicației, putem considera că produsul este în stadiul de **MVP - minimum viable product**. Considerăm că am trecut stadiul de PoC - Proof of Concept, deoarece componentele hardware colectează date în regim de producție, iar aplicația software are implementate toate functionalitatile pe care le-am definit în stadiul de proiectare. Menținem conceptul de MVP și versionăm aplicația ca fiind 1.0 deoarece exista cu siguranta opțiunea de a dezvolta multiple alte feature-uri. De asemenea, putem identifica și corecta în viitor posibile buguri de logica sau de funcționare.



**Partea de Hardware**

Pentru a colecta date din mediul exterior am folosit următoarele echipamente:



* Placa de dezvoltare NodeMCU cu microcontroller wireless ESP8266
* Modul de mediu SparkFun cu senzori BME280 si CCS811

Pentru ansamblul format din ventilator și fereastră am folosit:



* Servomotor HiTec HS-485HB
* DC motor AndyMark 6000 12V
* Placa de dezvoltare WeMos D1 R1
* Modul pentru motoare DC L298N

	

Palele ventilatorului, carcasa senzorilor cât și cea a ferestrei sunt construite după modele realizate în Fusion 360 iar acestea au fost printate 3D la o imprimantă Prusa i3Mk3s.



**Colectare date**

	Senzorii citesc datele și le actualizează într-un tabel **PostgreSQL **cu capacități real-time. De asemenea la câteva minute se crează o intrare nouă într-un tabel specializat pe istoricul de date.

	Geamul și ventilatorul “ascultă”  la datele din tabelul real-time și în funcție de acestea decid când trebuie sa se deschidă.

Tabelele PostgreSQL


<table>
  <tr>
   <td><strong>Denumire proprietate</strong>
   </td>
   <td><strong>Detalii proprietate, tip de date</strong>
   </td>
  </tr>
  <tr>
   <td><strong>id</strong>
   </td>
   <td>identificatorul specific senzorului (suport pentru mai multe dispozitive), int8
   </td>
  </tr>
  <tr>
   <td><strong>PRESSURE_pascals</strong>
   </td>
   <td>presiune, float8
   </td>
  </tr>
  <tr>
   <td><strong>average_TEMP_celsius</strong>
   </td>
   <td>temperatură medie, float4
<p>
Cum avea doi senzori de temperatură am decis că putem crește acuratețea printr-o mediere
   </td>
  </tr>
  <tr>
   <td><strong>HUMIDITY_percent</strong>
   </td>
   <td>procent umiditate, float4
   </td>
  </tr>
  <tr>
   <td><strong>CO2_ppm</strong>
   </td>
   <td>carbon dioxide level, int2
   </td>
  </tr>
  <tr>
   <td><strong>TVOC_ppb</strong>
   </td>
   <td>impurități, int2
   </td>
  </tr>
  <tr>
   <td><strong>window</strong>
   </td>
   <td>este geamul deschis, bool
   </td>
  </tr>
  <tr>
   <td><strong>fan</strong>
   </td>
   <td>este ventilatorul pornit, bool
   </td>
  </tr>
  <tr>
   <td><strong>AQI</strong>
   </td>
   <td>Air Quality Index - un indice de calitate al aerului, 0 = aer curat, 600 = aer poluat
   </td>
  </tr>
</table>


Structura datelor
