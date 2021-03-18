DIGORI PARASCOVIA - TEMA 1 IOCLA - 323CC

In aceasta tema am avut de implementat functionalitatea printf-ului din C. 

Functia iocla_printf are la baza stringul format[] in care sunt citite argumentele de formatare 
si output[] care va pastra stringul final, pentru a fi afisat la ecran. Variabilele i si j vor 
fi contoarele/pozitiile curente din format[] si respectiv output[].
Cu un do while parcurg stringul format[] si verific printr-un switch fiecare caz de identificare 
a unui specificator de format 'c', 'd', 'u', 'x', 's'. 
Pentru cazul 'c' este simplu, doar pastrez valoarea argumentului intr-o variabila int input si 
dupa ii fac cast la char, introducand-o in output[] si incrementand valoarea lui j.
Pentru 'd' am tratat mai intaii cazul unui input negativ. Daca numarul este negativ in output[j] 
adaug mai intaii '-', il fac numar pozitiv si dupa cu ajutorul functiei toString() transform 
numarul in string. 
Functia toString() transforma un numar in orice baza (primita ca paramentru) si returneaza un 
string gata inversat. Aici folosesc un buffer static char pentru a ii pastra valoarea la 
fiecare executie a functiei. 
Pentru 'x' folosesc la fel functia toString() doar ca deja baza va fi 16.
Pentru 'u' delimitez cazurile cand inputul este negativ sau pozitiv. Daca este pozitiv el este 
tratat ca orice int pozitiv iar daca este negativ, am mers pe varianta mai muncitoreasca si naiva 
sa transform numarul negativ in baza 16 cu toString() apoi rezultatul din b16 il voi transforma 
in b10  cu functia hexToDec() si deja int-ul zecimal il transform in string-ul final.
Pentru 's' citesc argumentul cu un char* si aparent nu au fost probleme, doar l-am copiat in output. 
Am mai introdus un caz aparte '%' pentru a escapa acest caracter, deci daca dupa analiza din 
if (format[i] =='%') in switch mai gasesc un '%' inseamna ca acest caracter trebuie doar adaugat 
in output[].


