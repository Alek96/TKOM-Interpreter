# Techniki Kompilacji - Projekt - Interpreter prostego języka z wbudowanym typem wektorowym  

Projekt wykonany w ramach przedmiotu TKOM (Techniki Kompilacji), na kierunku Informatyka, specjalizacji Inżynieria Systemów Informacyjnych (ISI) na Wydziale Elektroniki i Technik Informacyjnych (EiTI) Politechniki Warszawskiej.  

### Opis projektu
Projekt ma na celu wykonanie interpretatora prostego języka. Język ma być wyposażony w zmienne z zasięgiem, 
dwie podstawowe konstrukcje sterujące (pętla oraz instrukcja warunkowa), możliwość definiowania funkcji oraz wbudowany typ wektorowy (2-, 3-wymiarowy). 
Dodatkowo język powinien obsługiwać wyrażenia matematyczne uwzględniając priorytet operatorów.  

### Kompilacja i uruchomienie  
Kompilacja następuje za pomoca narzędzie **CMake**.  
Program jest prostą aplikacja konsolową, uruchamianą wraz z parametrem reprezentującym ścieżkę do pliku ze skryptem do interpretacji.  
Wynik poszczególnych etapów analizy pliku oraz samego wyniku interpretacji końcowej i wykonania jest wyświetlany na standardowym wyjściu. W zależności od ogólnego wyniku analizy, na standardowe wyjście mogą być zgłaszane: błędy leksykalny, błędy składniowe, błędy semantyczne lub wynik wykonania skryptu (wraz z możliwymi błędami czasu wykonania). Jako że jest to aplikacja konsolowa, nie przewiduję zapisywania wyników do pliku (można to zrobić przekierowując wyjście bezpośrednio do pliku).  

### Wymagania
* Kompilator wspierający standard **C++14**  
* Narzędzie do budowania **CMake**  
* Narzędzie do testowania jednostkowego **Catch2**  


### TODO  
* Klasa Parser, w metodzie "parse" powinna zwracać obiekt do uruchomienia, a nie sama udostępniać metodę "run".  
* Dodawania własnej biblioteki, powinno być bardziej ukryte przed użytkownikiem. Lepiej by było, gdyby następowało to za pomocą podmiany Readera w Lexerze, niż podmiany lexera w parserze. Obecny sposób jest mało inruicyjny dla użytkownika.  
* Powinna zostać stworzona odzielna klasa "Context" przechowująca aktualne zmienna, które teraz są przechowywane w "BlockStatement". Dzięki temu będzie możliwę zamienienie obecnej metody "run" na constową. 
Do zmiennych w klasie "Context" odwoływało by się za pomocą dodatkowego obiektu proxy, co ułatwiło by zapisywanie i wczytywanie ponownie wartości zmiennych (co aktualnie jest robione w metodzie "run" w BlockStatement), oraz ułatwiło by odwoływanie się do nich w każdym miejscu, w którym to potrzebne. Klasy takie jak BaseMathExpr podczas tworzenia potrzebują odpowłanie do zmiennych, ale nie do ich wartrości, więc można by przekazywać tylko wskaźnik na ten proxy. Do proxy oddelegowano by wtedy jeszcze informacje o indexie.  
* Trzeba poprawić argument wywołania metody Parser::BlockStatementParse, jest nieintuicyjny - fakt podmiany aktualnego blocku. Możliwe że przez samo dodanie klasy "Context" zostanie to poprawione.  
* Instancje BlockStatement zawarte w klasacj IfStatement i WhileStatement powinny być tworzone automatycznie - tak jak zostało to zrobione w klasie FunctionDef. A w konstruktorze powinny pozostać tylko przekazywanie expression.  
* Okazuje się, że tworzenie hashMap w parserze trochę psuje wygląd kodu. Trzeba by je jakoś porawić (i dodać static) lub zmienić na coś innego.  
* W WhileStatement::run nie potrzebnie zostało dodane ograniczenie czasowe wykonania pętli, trzeba się go pozbyć.  
