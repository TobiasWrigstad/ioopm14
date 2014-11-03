Här är koden som skrevs på roliga timmen den 31 oktober.

Programmet innehåller en klasshierarki där klasserna `Dog` och
`Duck` båda ärver av klassen `Animal`. Klassen `Storyteller` har
en metod `tellStory` som tar två djur som argument och berättar en
saga om dem. Klassen `Driver` innehåller programmets main-metod.

Programmet kompileras och körs med:

```
javac Driver.java
java Driver
```

Om kompilatorn klagar på Å, Ä och Ö kan du prova 

```
javac -encoding utf8 Driver.java
```