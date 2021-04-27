Uz normalne kontrole postoji još par "cheat" kontrola:
l - kupovanje života za 1000 bodova, bodovi mogu ići u negativno
r - resetira lopticu na splav, dodano uglavnom u slučaju bugova
u - instant level-up

Negdje mi se podkrala greška u micanju i kolizijama, pa se ponekad zna dogoditi da loptica "clippa" kroz granične zidove ili cigle.
Ako želite možete u kodu u main.cpp prilikom inicijalizacije promijeniti target framerate, 60 je default.
Sve teksture su u bmp formatu, a audio u wav formatu.

Kolizije su dosta ekstenzivno odrađene, iako ima ta neka greška. Ima puno prostora za optimiziranje, 
trenutačno ima mnogo redudantnih izračuna i dobavljanja podataka.

Hvala na razmatranju mog rada.