Tower attack
============


Zadání semestralni prace z Progtestu
------------------------------------

Naprogramujte jednoduchou grafickou tower ATTACK hru (pozor nejedná se o tower defense). Kde hráč se snaží posílat vlny nepřátel do bludiště s cílem vyhnout se (příp. zničit) co největšímu počtu obraných věží nepřítele
a dobýt jeho bázi. Hra může fungovat na principu jednotlivých tahů nebo jako hra v reálném čase.

Implementujte následující funkcionality:

- 1.Implementujte interakci věže vs útočníci (př. zničení útočníka, proběhnutí, zničení věže, …)
    + a.implementujte alespoň 3 různé efekty pro věže (př. útok na nejbližší jednotku, na nejsilnější, zpomalení všech v okolí, …),
    + b.implementujte alespoň 3 různé efekty pro útočníky (př. neviditelnost, létání, vyšší odolnost, …),
    + c.jedna věž může mít více efektů, jeden útočník může mít více efektů.
 - 2.Implementujte počítadlo skóre a detekci vítězství.
 - 3.Implementujte jednoduchou AI řídící rozmisťování věží (náhodné tahy nestačí).
 - 4.Hra musí být konfigurovatelná ze souboru:
	+ a.definice útočníků (př. název, cena, životy, rychlost, útok, odolnost, efekty, …),
	+ b.definice věží (př. životy, dosah, útok, odolnost, efekty, …),
	+ c.jednotlivé mapy (př. zdi, místa na stavění věží, …).
 - 5.Hra umožňuje ukládat a načítat rozehrané hry.


Upřesnění zadání
----------------
Mapa bude tvořena pomocí ASCII znaků (zdi X, místa pro věže @, útočníci {S, W, T,...}, věže {T, I, F, C,...}, vchody =, východ >) v terminálu.
Hra bude tahová. Hráč bude vybírat vchody, možné útočníky a jim přiřazovat různé efekty. Jak útočníci, tak efekty stojí herní měnu, kterou hráč každé kolo získá.
Úkolem je dostat určitý počet útočníků do východu během určitého počtu kol. Hráč tohoto může docílit strategií v posílání různých útočníků z různých míst
(nebo tweaknutím config souborů).
Věže mají několik typů efektů při zásahu a základní vlastnostmi (poškození, rychlost útoku, dosah,...). Vše je konfigurovatelné ze souboru.
Útočníci mají několik typů s různými strategiemi průchodu a základními vlastnostmi (životy, rychlost,...) hráč si navíc může vybrat, jestli útočník bude mít vlastnost léčení, zrychlení nebo na čas bonusové brnění.
Věže jsou schopny útočníky zmrazit, zapálit nebo jim na nějakou dobu poškodit brnění.
Věže do mapy rozmisťuje jednoduchá umělá inteligence, která se rozhoduje na základě součtu vzdáleností od všech útočníků, která pozice by byla pro věž nejlepší. Jaký typ věže bude postaven je opět v konfiguračním souboru.
V konfiguračním souboru se, mimo jiné, dá nastavit: kolik kol hráč má k dispozici, jednou za kolik kol je hráč na tahu, jednou za kolik kol se postaví nová věž, kolik dostává hráč peněz, kolik životů má základna věží. Následně je konfigurační soubor pro pozitivní effekty, kde se dá nastavit jejich síla, cena a jak často se aktivují. Negativní efekty opět se silou a délkou trvání. Útočníci s jejich cenou, symbolem, co je reprezentuje ve hře, životy, poškozením , rychlostí, brněním a schopností lézt po zdech. U věží se dá nastavit, opět jejich symbol, poškození, rychlost útoku, dosah a efekty, co aplikuje na útočníka, když ho zasáhne.

Jak pro konfiguraci, tak ukládat/načítat je použit formát json s knihovnou nlohmann::json.


Polymorfismus
-------------
Polymorfní jsou efekty a to jak ty pozitivní, tak ty negativní.
U těch pozitivních se jedná jen o metodu apply, která se stará o aplikování efektu na útočníka.
U negativních efektů je opět polymorfní metoda apply, která funguje na stejné bázi, ale navíc je polymorfní i metoda save, která se stará o uložení efektu do souboru.