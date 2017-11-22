from os import system

# <myadr> <nextadr> <2B wskaźnik na tablicę stringów> <2B długość tablicy str>
# <2B wskaźnik na deskryptor urządzenia> <2B długość deskryptora urządzenia>
 
langs=['pol', 'eng'] 	#Lista języków
texts=[					#Zbiór słów
    ['Polon-Alfa', 'Polon-Alfa'], #0
    ['prototyp', 'prototype of'], #1
    ['ZR-3', 'ZR-3'], #2
    ['w fazie koncepcyjnej', 'in concept phase'], #3
    ['moc dawki', 'dose rate'],
    ['koniec','end']
    ]

# Deskryptor urządzenia
gdev=[
	0, # wersja oprogramowania
	1, # wersja protokołu publicznego
	2, # wersja protokołu prywatnego
	'Polon-Alfa', # producent
	'H0666', #Numer serujny
	'ZR-3 mod', #Nazwa
	[1, 2], #tooltip
	[2, 3], #opis
		[	#funkcjonalności
			['dose', [0x40]],
			['dose-rate', [0x41, 0x42]]
		]
	]

name1='test1'
adrs1=[0x01, 0x02]

name2='test2'
adrs2=[0x02, 0x03]

name3='test3'
adrs3=[0x03, 0x14]

name4='test4'
adrs4=[0x14, 0xFE]

def genfun(name, adr, lng, txt, dev):
    nuls = [0x00, 0x00]
    filea = open('MendiumBusConnectorIn.cfg', 'at')
    filea.write('inputs/'+name+'.bin\n')
    filea.close()
    file = open(name+'.bin', 'wb')
    globaldata = bytearray()

    #================== Dodawanie wstępu ====================================
    globaldata+=(bytes(adr))
    globaldata+=(b'\xff\xff\xff\xff\xff\xff\xff\xff')



	#================== Generowanie tablicy stringów ========================
    langsc = len(lng)
    lstrs = []
    ptrs = []
    sdata = bytearray()
    for string in lng:
        sdata+=(bytes(string, 'ascii'))
        ptrs.append(len(sdata)+1)
        sdata+=(bytes([0x00, 0xFF, 0xFF ]))
    sdata += b'\x00'

    for i in range(langsc):
        lstrs.append(bytearray())
    for langstrings in txt:
        for i in range(langsc):
            lstrs[i] += bytes(langstrings[i], 'ascii')
            lstrs[i] += b'\x00'
    adrs = []
    for dat in lstrs:
        adrs.append(len(sdata))
        sdata += dat
    for i in range(len(ptrs)):
        valh = (adrs[i]>>8)&0xFF;
        vall = (adrs[i]>>0)&0xFF;
        sdata[ptrs[i]]=valh
        sdata[ptrs[i]+1]=vall

    #dołączanie tablicy stringów
    globaldata[2] = (len(globaldata)>>8)&0xFF
    globaldata[3] = (len(globaldata)>>0)&0xFF
    globaldata[4] = (len(sdata)>>8)&0xFF
    globaldata[5] = (len(sdata)>>0)&0xFF
    globaldata+=(sdata)
    
    
    
    #================== Generowanie deskryptora urządzenia ==================
    devd = bytearray()
    devd += bytes([dev[0], dev[1], dev[2]])
    devd += bytes(dev[3], 'ascii')
    devd += b'\x00'
    devd += bytes(dev[4], 'ascii')
    devd += b'\x00'
    devd += bytes(dev[5], 'ascii')
    devd += b'\x00'
    for i in dev[6]:
        devd += bytes([i])
    devd += b'\xFF'
    for i in dev[7]:
        devd += bytes([i])
    devd += b'\xFF'
    for fu in dev[8]:
        devd += bytes(fu[0], 'ascii')
        devd += b'\x00'
        for i in fu[1]:
            devd += bytes([i])
        devd += b'\x00'
    
    #dołączanie deskryptora urządzenia
    globaldata[6] = (len(globaldata)>>8)&0xFF
    globaldata[7] = (len(globaldata)>>0)&0xFF
    globaldata[8] = (len(devd)>>8)&0xFF
    globaldata[9] = (len(devd)>>0)&0xFF
    globaldata+=(devd)
    
    
    file.write(globaldata)
    file.close()
    return

filem = open('MendiumBusConnectorIn.cfg', 'wt')
filem.close()

genfun(name1, adrs1, langs, texts, gdev)
genfun(name2, adrs2, langs, texts, gdev)
genfun(name3, adrs3, langs, texts, gdev)
genfun(name4, adrs4, langs, texts, gdev)

#system('pause')
