# GranularFlow
#### CZ - Bakalarska prace - Jan Kalinic - VUT 2023
plugin VST verze 3 se zameruje na granularni syntezu a experimentalni LFO.

Tento readme by měl uživatelům poskytnout více informací o tomto pluginu, který jsem vytvořil v rámci své bakalářské práce.

Protože byl plugin vytvořen pomocí samostatných modulů, každý modul bude podrobně popsán níže.


## Wrapper modul
Wrapper je úvodní obrazovka, kterou uvidíte, když je plugin přidán do vašeho DAW.
Skládá se ze 3 syntezátorů - aditivní, granulární a wavetable. Každý z nich má ovládací prvky, které můžete upravit pomocí LFO. Tato obrazovka také obsahuje 4 různé LFO - color, math, wavetable a bounce.
Chcete-li povolit zvuk ze syntezátoru, musíte kliknout na kabel, který vede do centrálního výstupního rozbočovače. 
Chcete-li aktivovat LFO, musíte jej přiřadit k parametru - což lze provést v požadovaném syntezátoru a poté jej zapnout kliknutím na přímku, která vede na sběrnici LFO.

## Modul granulárního syntetizátoru
Když se rozhodnete pracovat s tímto modulem, budete si muset vybrat, zda chcete syntetizovat z vyrovnávací paměti daw na kanálu, do kterého jste umístili tento plugin, nebo ze souboru.
Setkáte se s různými parametry pro granulární syntézu, včetně:
- BUFFER / FILE - tlačítka, která vám umožní vybrat preferovaný zdroj syntézy
- Length - nastavuje maximální velikost vnitřní vyrovnávací paměti
- Count - kolik kurzorů v tu chvíli syntetizuje
- Select - vybere aktuální kurzor -> zobrazí se jeho nastavení

Pokud jde o nastavení kurzoru, jsou zde:
- MODE - jak chcete, aby kurzor získával vzorky ze zdroje -> v případě MIRROR jsou to ve skutečnosti dva vzorky, které se kombinují a hrají současně
- CURSOR - umožňuje nastavit kurzor do pohybu
- MIDI - pokud má být nota spuštěna midi zprávou nebo se opakovat
- WINDOW - existují tři typy oken, které tvarují zrna tak, aby byla syntetizace lineárnější
- LENGHT - jak dlouhé by mělo být jedno zrno (až celá sekunda)
- PITCH - toto nastavení zvýší nebo sníží hlavní výšku zvuku v případě zrna
- GRAINS - počet zrn, která by měla hrát najednou
- OFFSET - mezi vytvářením zrn je nutný offset, takže zrna nevznikají najednou, ale s mírným časovým zpožděním
- VOLUME - řídí hlasitost nově vytvořených zrn
- PAN - to dělá zrna stereo, rotace odpovídá virtuálnímu umístění zdroje zrn

## Additive Synthesizer Module
Tento modul vytváří požadovaný počet oscilátorů pro dosažení aditivní syntézy.
Základní nastavení modulu jsou podobná jako u granulárního modulu:
- Count - počet oscilátorů
- Selected - zobrazí konfiguraci vybraných oscilátorů

- Nastavení jednoho oscilátoru:
- MIDI - když je zapnutý, zvuk se přehraje pouze po stisknutí kláves MIDI
- PHASE - nastavuje fázi harmonického oscilátoru
- FREQUENCY - nastavuje základní frekvenci pro oscilaci
- VOLUME - ovládá hlasitost oscilátoru
- PAN - umožňuje stereo panorámování oscilátoru

## Wavetable Module
Wavetable syntéza, kde můžete nakreslit 3 vlny. Mezi těmito vlnami se počítají tzv. interní nebo také mezi-vlny.
Pokud chcete syntetizovat nakreslené vlny, stiskněte tlačítko syntesize a zvuk se spustí, jakmile budou interpolovány všechny mezivlny.

- MIDI - lze buď přehrávat zvuk ve smyčce, nebo pouze při stisku klávesy MIDI
- FREQUENCY - nastavuje základní frekvenci - ta se mění s počtem vln, více vln vytváří vyšší frekvence
- WAVE COUNT - zvyšuje se o dvě a nastavuje, kolik mezivln je potřeba vypočítat pomocí lineární interpolace
- INTERPOLATION - ovlivňuje zvuk pouze tam, kde jsou vyžadovány mezivzorky, jsou interpolovány jednou z těchto metod, v současné době existují dvě metody, ale v budoucnu by jich mělo být více
- VOLUME - ovládá hlasitost
- PAN - nastavení posouvání pro modul wavetable

## Color LFO
Tento LFO pořídí snímek a na základě barvy pixelu určí výstupní hodnotu.
Nejlepší způsob, jak popsat toto LFO, je porovnat jej se sample and hold LFO, kde po určitou dobu LFO drží hodnotu na výstupu.
Parametry:
- DIRECTION - jakým směrem se má selektor pohybovat a vybrat další pixel pro analýzu barev
- SELECTED COLOR - hodnota na výstupu závisí na zvolené barvě R G nebo B
- RATE - jak rychle navzorkovat novou barvu
- DEPTH - jak moc změnit parametry na výstupu

## Bounce LFO
Vytvoří harmonický průběh pro vlnu LFO tím, že vezme souřadnice X nebo Y pohybující se kuličky.
Parametry:
- BALL SPEED - o kolik by se měl míč pohnout v každém intervalu
- DIRECTION - měla by být na výstupu hodnota pozice X nebo Y
- RATE - jak rychle nastavit výstupní hodnotu
- DEPTH - jak moc změnit parametry na výstupu

## Math LFO
Pracuje s předdefinovanými hodnotami funkce z bloku pro zadávání textu.
Prozatím je výstup této funkce v rozsahu 0,01 až 10 s krokem 0,01 pouze argumentem pro sinus... takže cokoliv tam napíšete, bude mít za následek různě tvarovanou sinusovou vlnu.
Parametry:
- Textový vstup - zde můžete napsat vlastní funkci, po stisknutí Enter se výše zobrazí tvar výstupní vlny
- RATE - jak rychle nastavit výstupní hodnotu
- DEPTH - jak moc změnit parametry na výstupu

## Wavetable LFO
Toto LFO používá stejný koncept jako wavetable syntéza. Pro výstup si můžete nakreslit vlastní tvary vln.
Parametry:
- WAVE COUNT - zvýší se o dvě a nastaví, kolik mezivln se vypočítá mezi nakreslenými vlnami
- RATE - jak rychle nastavit výstupní hodnotu
- DEPTH - jak moc změnit parametry na výstupu