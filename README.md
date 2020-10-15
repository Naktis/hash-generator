
# *Hash* generatorius

  

C++ kalba sukurtas *hash* generatorius, bet kokio ilgio *string* eilutę paverčiantis 64 simbolių šešioliktainiu kodu.

  ## Pseudokodas
  

    Function getHashOfString 
      Pass In: string to be hashed as 'input'
      Initialize a hash structure made of 16 16b integers as 'hash'
      
      FOR every integer of 'hash' as h
	      h ← 4096 + ((index of h in 'hash')+1) * (raise 2 to the power of (('input' length) mod 10)) * 9719
      ENDFOR
      
      FOR every char of 'input' as c
	      (first int of 'hash') ← (first int of 'hash') * 7213 + 1327 * (raise (c mod 10) to the power of 3) + c
	      FOR every integer of 'hash' as h, starting from the second
		      h ← h * (previous h by index in 'hash') + c
	      ENDFOR
      ENDFOR
      
	  Initialize stringstream as hashStream
	  FOR every integer of 'hash' as h
		  Initialize char to represent the filling number for empty slots of the final hex number as 'fill'
		  fill ← '0' + (h mod 10)
		  Convert h to hexadecimal number
		  PRINT h to hashStream, fill whitespace with 'fill'
	  ENDFOR
	  Convert hashStream to string and SET it as hashString
  
      Pass Out: string representing the hash code as hashString
    Endfunction
      
Komentarai: 

 - Ne visi pseudokode minimi kintamųjų vardai sutampa su esančiais programoje dėl pseudokodo įskaitomumo gerinimo.
 - Pasirinkti daugikliai yra pirminiai skaičiai dėl kolizijų tikimybės mažinimo ir didesni nei 1000 dėl to, kad keistųsi visi *hash'o* struktūros kiekvieno *integer'io* vienetai, dešimtys, šimtai, tūkstančiai.
 - Pirmasis FOR ciklas sukuria pagrindą maišos kodui ir priklauso nuo *input* ilgio.
 - Antrasis dvigubas FOR ciklas keičia kiekvieną int iš *hash* pagal kiekvieną *input* simbolį.
 - Trečiasis FOR ciklas "sulipdo" *hash'o integerius* į vieną *string'ą* prieš tai juos konvertuodamas iš dešimtainės į šešioliktainę sistemą. Ten, kur skaičius yra per mažas, kad iš jo būtų sudaryti 4 hex simboliai, yra įrašoma skaičiaus liekana, gaunama padalijus visą integerį iš 10.

## Programos diegimas ir naudojimas:

  

1. Parsisiųsti programą iš versijų puslapio

2. Parsisiųsti ir įsidiegti C++ kompiliatorių (pvz. [GCC](https://gcc.gnu.org/))

3. Atsidaryti terminalą ir jame įvesti programos vietą diske

4. Sukompiliuoti programą, pvz

- Jei naudojate *GCC* su *GNU Make*, įrašyti komandą`make generator`

- Jei naudojate *GCC* be *GNU Make*, įrašyti:

`g++ -c generator.cpp hash_functions.cpp`

`g++ -o g generator.o hash_functions.o`

5. Paleisti programą ir perduoti norimas maišyti string eilutes arba failus, atskirtus tarpu:

 `./g string1 file1.txt` (unix)

 `g string1 file1.txt` (windows)

## Atlikti testai

1. Tos pačios įvesties ***hash'ų* vienodumas ir ilgis** su vieno simbolio failais (1_1_1.txt), skirtingais >1000 simbolių failais (1_1_2.txt), vienu simboliu besiskiriančiais >1000 simbolių failais (1_1_3.txt) ir tuščiu failu (1_4.txt)
	*Tester.cpp* faile esančios *test_1* funkcijos rezultatai:
	
![test_1](https://i.ibb.co/c6GxP6J/1.jpg)

	Išvados: *Hash* ilgis nepriklauso nuo *input* ilgio - kodas visada sudaromas iš 64 simbolių. Tai pačiai įvesčiai (*input*) išvestis (*output*) visuomet yra ta pati, funkcija deterministinė.

2. Kiekvienos eilutės iš Konstitucijos ***hash'avimo* trukmės matavimas**
*Tester.cpp* faile esančios *test_2* funkcijos rezultatai:

![test_2](https://i.ibb.co/mX6Yhx7/2.jpg)

Išvada: maišos funkcija veikia sparčiai.

3. 100 000 atsitiktinių simbolių eilučių porų ***hash'ų* kolizijų paieška**
 Testavimo failas buvo sugeneruotas naudojant *Tester.cpp* esančią *generateTest3File* funkciją.
 *Tester.cpp* faile esančios *test_3* funkcijos rezultatai:
 
 ![test_3](https://i.ibb.co/pwKN7dz/3.jpg)
 
 Išvada: maišos funkcija yra pakankamai atspari kolizijai, bet reikia daugiau testų, kad galėtume teigti, kad *hash'ų* sutapimai nėra įmanomi.

4. 100 000 simbolių eilučių porų, tarp kurių skiriasi tik vienas simbolis, ***hash'ų* panašumo vertinimas**
Testavimo failas buvo sugeneruotas naudojant *Tester.cpp* esančią *generateTest4File* funkciją.
*Tester.cpp* faile esančios *test_4* funkcijos rezultatai:

![test_4](https://i.ibb.co/0Dg0WR8/4.jpg)

Išvados: vidutiniškai beveik vienodų *string'ų* *hash'ai* pagal šešioliktainius simbolius sutapo 16.4%, o konvertavus *hash'us* į dvejetainius skaičius, vidutinis sutapimas išaugo iki 70.4%. Lyginant *hash'us* abiem skaičiavimo sistemom buvo rasta bent viena kolizija, nes didžiausias pasiektas sutapimas yra 100%. Taip pat bent vienos poros *hash'ai* skyrėsi visais simboliais, lyginant juos pagal šešioliktainę sistemą (0%).

## Testų išvados

 - Funkcijos stiprybės: sparta, vienodas rezultato dydis ir determinizmas.
 - Funkcijos trūkumai: nors ir maža, bet egzistuojanti kolizijos tikimybė ir pakankamai didelis panašių *string'ų hash'ų* vienodumas lyginant pagal dvejetainę sistemą.
 
Galimi patobulinimai: *bitwise* operatorių naudojimas ir nelinijinis *hash'o* kūrimas (keičiant *hash'o* gale esančius simbolius kinta ir pradiniai, nes dabar egzistuoja tik vienpusė priklausomybė (galą lemia pradžia)).
