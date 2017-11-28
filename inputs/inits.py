from os import system

# <myadr> <nextadr> <2B wskaźnik na tablicę stringów> <2B długość tablicy str>
# <2B wskaźnik na deskryptor urządzenia> <2B długość deskryptora urządzenia>
# <2B wskaźnik na deskryptor metod> <2B długość deskryptora metod>
 
langs=['pol', 'eng'] 	#Lista języków
texts=[					#Zbiór słów
    ['moc dawki', 'dose rate'], #0
    ['chwilowa moc dawki', '...'], #1
    ['ZR-3', 'ZR-3'], #2
    ['w fazie koncepcyjnej', 'in concept phase'], #3
    ['i kij', 'and stick'], #4
    ['komenda testowa', 'test command'], #5
    ['odpowiedz testowa', 'test answer'], #6
    [', nic nie robi', ', do nothing'], #7
    ['testowy parametr', 'test parametr'], #8
    ['Zapytanie o:', 'Question for:'], #9
    ['dawka', 'dose'], #10
    ['calkowita dawka zebrana przez urzadzenie', 'total dose...'], #11
    ['status urzadzenia', 'device state'], #12
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
	[2, 3, 4], #opis
		[	#funkcjonalności
			['dose', [0x40]],
			['dose-rate', [0x41, 0x42]]
		]
	]

# Deskryptor metod
gmeths=[

		[
			0x20, # nagłówek
			0x80, # parametry
			0xa0, # nagłówek powiązany
			[0], # tooltip
			[9, 0], #opis
			[
				#['int48','nSv',[10],[11]]
			]
		],

		[
			0xa0, # nagłówek
			0x6a, # parametry
			0x20, # nagłówek powiązany
			[0], # tooltip
			[1], #opis
			[
				['float24','Sv/h',[0],[1]]
			]
		],
			#==========================================================
		[
			0x22, # nagłówek
			0x80, # parametry
			0xa2, # nagłówek powiązany
			[10], # tooltip
			[9, 10], #opis
			[ # parametry
				#[
					#'char', # typ słowa
					#'j', # jednostka
					#[8], # tooltip
					#[8, 7]
				#] # opis
			]
		],
			
		[
			0xa2, # nagłówek
			0x6a, # parametry
			0x22, # nagłówek powiązany
			[10], # tooltip
			[11], #opis
			[
				['int48','nSv',[10],[11]]
			]
		],
			#=======================================================
		[
			0x30, # nagłówek
			0x80, # parametry
			0xb0, # nagłówek powiązany
			[12], # tooltip
			[9, 12], #opis
			[
				#['int48','nSv',[10],[11]]
			]
		],

		[
			0xb0, # nagłówek
			0x4a, # parametry
			0x30, # nagłówek powiązany
			[12], # tooltip
			[12], #opis
			[
				['string','',[12],[12]]
			]
		],
	]

name1='test1'
adrs1=[0x01, 0x02]

name2='test2'
adrs2=[0x02, 0x03]

name3='test3'
adrs3=[0x03, 0x14]

name4='test4'
adrs4=[0x14, 0xFE]

def genfun(name, adr, lng, txt, dev, met):
    nuls = [0x00, 0x00]
    filea = open('MendiumBusConnectorIn.cfg', 'at')
    filea.write('inputs/'+name+'.bin\n')
    filea.close()
    file = open(name+'.bin', 'wb')
    globaldata = bytearray()

    #================== Dodawanie wstępu ====================================
    globaldata+=(bytes(adr))
    globaldata+=(b'\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff')



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
    
    
    
    #================== Generowanie deskryptora metod =======================
    metd = bytearray()
    for metoda in met:
        metd += bytes([metoda[0], metoda[1], metoda[2]])
        for tt in metoda[3]:
            metd += bytes([tt])
        metd += b'\xFF'
        for op in metoda[4]:
            metd += bytes([op])
        metd += b'\xFF'
        for arg in metoda[5]:
            metd += bytes(arg[0], 'ascii')
            metd += b'\x00'
            metd += bytes(arg[1], 'ascii')
            metd += b'\x00'
            for att in arg[2]:
                metd += bytes([att])
            metd += b'\xFF'
            for aop in arg[3]:
                metd += bytes([aop])
            metd += b'\xFF'
        metd += b'\xFF'

    
    #dołączanie deskryptora metod
    globaldata[10] = (len(globaldata)>>8)&0xFF
    globaldata[11] = (len(globaldata)>>0)&0xFF
    globaldata[12] = (len(metd)>>8)&0xFF
    globaldata[13] = (len(metd)>>0)&0xFF
    globaldata+=(metd)
    
    
    file.write(globaldata)
    file.close()
    return

filem = open('MendiumBusConnectorIn.cfg', 'wt')
filem.close()

genfun(name1, adrs1, langs, texts, gdev, gmeths)
genfun(name2, adrs2, langs, texts, gdev, gmeths)
genfun(name3, adrs3, langs, texts, gdev, gmeths)
genfun(name4, adrs4, langs, texts, gdev, gmeths)

#system('pause')
