
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
		  Initialize char to represent the filling number for empty slots of hex number as 'fill'
		  fill ← '0' + (h mod 10)
		  Convert h to hexadecimal number
		  PRINT h to hashStream, fill whitespace with 'fill'
	  ENDFOR
	  Convert hashStream to string and SET it as hashString
  
      Pass Out: string representing the hash code as hashString
    Endfunction
      

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

-  `./g string1 file1.txt` (unix)

-  `g string1 file1.txt` (windows)

## Atlikti testai

1. Lavinos (*avalanche*) efektas su žodžiu Lietuva

  

![Lietuva](https://i.ibb.co/JqzsqNC/Ekrano-nuotrauka-2020-10-09-094417.jpg)

2. Tos pačios įvesties ***hash'ų* vienodumas ir ilgis** su vieno simbolio failais, skirtingais >1000 simbolių failais, vienu simboliu besiskiriančiais >1000 simbolių failais ir tuščiu failu

  

![1_testas_1](https://i.ibb.co/K01VtyK/1.jpg)

![1_testas_2](https://i.ibb.co/PZqMWm1/2.jpg)

  

Išvados: *Hash* ilgis nepriklauso nuo *input* ilgio - kodas visada sudaromas iš 64 simbolių. Tai pačiai įvesčiai (*input*) išvestis (*output*) visuomet yra ta pati, funkcija deterministinė.
