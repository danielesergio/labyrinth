# SPECIFICHE PROGETTO
Il file [spedifiche.pdf](https://github.com/danielesergio/labyrinth/blob/master/specifiche.pdf) contiene le specifiche del progetto.

## BUILDING PROGETTO (LINUX)
Da terminale arrivare alla cartella progetto.
Eseguire i comandi:
- cd src
- mkdir CARTELLA
- cd CARTELLA
- cmake ..

Una volta terminato, digitare il comando:
- make

Il progetto è ora avviabile eseguendo il file Labyrinth

Per modificare il labirinto modificare il file CARTELLA/resources/scheme come indicato nella sezione seguente.

Note:
oltre alle librerie viste a lezione (opengl e glut) è necessario installare la libraria OpenAL per la gestione del suono

OpenGL: sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev
OpenAL: sudo apt-get install libopenal0a libopenal-dev
ALUT:   sudo apt-get install libalut0 libalut-dev

## FILE DI CONFIGURAZIONE 
Il file di configurazione e .\resources\scheme (resources deve essere allo stesso livello del file Labyrinth
ed è configurato come segue:
- prima riga dimensione labirinto
- seconda riga tempo a disposizione per complentare il labirinto
- terza riga schelta delle texture T o F
- le righe seguenti disegnano il labirinto:
  - `x` rappresenta uno muro;
  - `*` rappresenta un allarme;
  - lo spazio vuoto rappresenta un area esplorabile
  - `n`/`s`/`e`/`w` rappresenta il giocatore con l´orientamento
```
	N
      W   E	
	S

```

## COMANDI
- `w`: avanti
- `a`: rotazione antioraria
- `d`: rotazione oraria
- `s`: indietro
- `spazio`: disabilita un allarme (devo averlo davanti per poterlo disattivare)


## TERMINAZIONE PROGRAMMA 
codice di terminazione previsti:
- 0: ok;
- 1: giocatore non trovato
- 2: allarme non trovato
- 3: file di configurazione non trovato
- 4: errore nel file di configurazione
- 5: texture non trovata
- 6: troppi allarmi (al massimo 6)

## NOTE CODICE
Nel codice sono presenti generalizzazione pensate per una futura implementazione delle seguenti funzionalità:
- worldunit è stata pensata per creare un fattore moltiplicativo del mondo 
- aggiunta di una musica\rumore di sottofondo
- Seconda versione del suono nella quale il rumore non attraversa i muri
