from os import system

# <myadr> <nextadr> <2B wskaźnik na tablicę stringów> <2B długość tablicy str>
# <2B wskaźnik na deskryptor urządzenia> <2B długość deskryptora urządzenia>
# <2B wskaźnik na deskryptor metod> <2B długość deskryptora metod>
 
langs=[u'pou', u'eng'] 	#Lista języków
texts=[					#Zbiór słów
    [u'moc dawki', u'dose rate'], #0
    [u'chwilowa moc dawki', u'...'], #1
    [u'jakość pomiaru', u'...'], #2
    [u'niepewność', u'...'], #3
    [u'zliczenia', u'...'], #4
    [u'pomiaru chwilowej mocy dawki', u'...'], #5
    [u'wykorzystane do oszacowania chwilowej mocy dawki', u'...'], #6
    [u'ustaw: ', u'set: '], #7
    [u'.', u'.'], #8
    [u'Zapytanie o:', u'Question for:'], #9
    [u'dawka', u'dose'], #10
    [u'całkowita dawka zebrana przez urządzenie', u'total dose...'], #11
    [u'status urządzenia', u'device state'], #12
    [u'nowa', u'new'], #13
    [u'alarm:', u'alarm:'], #14
    [u'stan alarmu zebranej dawki', u'...'], #15
    [u'nowa wartość progu alarmu', u'...'], #16
    [u'próg alarmu zebranej dawki', u'...'], #17
    [u'stan alarmu chwilowej mocy dawki', u'...'], #18
    [u'tryb pracy:',u'mode:'], #19
    [u'true=zatrzaskowy, false=ciągły', u'true=..., false='], #20
    [u'histereza:', u'histeresis:'], #21
    [u'nowa wartość histerezy alarmu', u'...'], #22
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
			#==================ZR3DoseRate========================================
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
			
			#==================ZR3CheckDoseRateAlarm========================================
		[
			0x29, # nagłówek
			0x80, # parametry
			0xa9, # nagłówek powiązany
			[14, 0], # tooltip
			[14, 0], #opis
			[
				#['int48','nSv',[10],[11]]
			]
		],

		[
			0xa9, # nagłówek
			0x6a, # parametry
			0x29, # nagłówek powiązany
			[14, 0], # tooltip
			[14, 0], #opis
			[
				['bool','',[14, 0],[18]]
			]
		],
			#==================ZR3SetDoseRateAlarmLevel========================================
		[
			0x2a, # nagłówek
			0x80, # parametry
			0xaa, # nagłówek powiązany
			[7, 14, 0], # tooltip
			[7, 14, 0], #opis
			[
				['float24','Sv',[14, 0],[16]]
			]
		],

		[
			0xaa, # nagłówek
			0x4a, # parametry
			0x2a, # nagłówek powiązany
			[7, 14, 0], # tooltip
			[7, 14, 0], #opis
			[
				#['bool','',[14, 0],[18]]
			]
		],
			#==================ZR3GetDoseRateAlarmLevel========================================
		[
			0x2b, # nagłówek
			0x80, # parametry
			0xab, # nagłówek powiązany
			[14, 0], # tooltip
			[14, 0], #opis
			[
				#['float24','Sv',[14, 0],[16]]
			]
		],

		[
			0xab, # nagłówek
			0x4a, # parametry
			0x2b, # nagłówek powiązany
			[14, 0], # tooltip
			[14, 0], #opis
			[
				['float24','Sv',[14, 0],[16]]
			]
		],
			#==================ZR3SetDoseRateAlarmMode========================================
		[
			0x2c, # nagłówek
			0x80, # parametry
			0xac, # nagłówek powiązany
			[7, 19, 14, 0], # tooltip
			[7, 19, 14, 0], #opis
			[
				['bool','',[19],[19, 20]]
			]
		],

		[
			0xac, # nagłówek
			0x4a, # parametry
			0x2c, # nagłówek powiązany
			[7, 19, 14, 0], # tooltip
			[7, 19, 14, 0], #opis
			[
				#['float24','Sv',[19],[19, 20]]
			]
		],
			#==================ZR3GetDoseRateAlarmMode========================================
		[
			0x2d, # nagłówek
			0x80, # parametry
			0xad, # nagłówek powiązany
			[19, 14, 0], # tooltip
			[19, 14, 0], #opis
			[
				#['bool','',[19],[19, 20]]
			]
		],

		[
			0xad, # nagłówek
			0x4a, # parametry
			0x2d, # nagłówek powiązany
			[19, 14, 0], # tooltip
			[19, 14, 0], #opis
			[
				['bool','',[19],[19, 20]]
			]
		],
			#==================ZR3SetDoseRateAlarmHysteresis========================================
		[
			0x2e, # nagłówek
			0x80, # parametry
			0xae, # nagłówek powiązany
			[7, 21, 14, 0], # tooltip
			[7, 21, 14, 0], #opis
			[
				['float24','Sv',[21, 14, 0],[16]]
			]
		],

		[
			0xae, # nagłówek
			0x4a, # parametry
			0x2e, # nagłówek powiązany
			[7, 21, 14, 0], # tooltip
			[7, 21, 14, 0], #opis
			[
				#['bool','',[14, 0],[18]]
			]
		],
			#==================ZR3GetDoseRateAlarmHysteresis========================================
		[
			0x2f, # nagłówek
			0x80, # parametry
			0xaf, # nagłówek powiązany
			[21, 14, 0], # tooltip
			[21, 14, 0], #opis
			[
				#['float24','Sv',[21, 14, 0],[16]]
			]
		],

		[
			0xaf, # nagłówek
			0x4a, # parametry
			0x2f, # nagłówek powiązany
			[21, 14, 0], # tooltip
			[21, 14, 0], #opis
			[
				['float24','Sv',[21, 14, 0],[21, 14, 0]]
			]
		],
			
			#==================ZR3DoseRateEstParams========================================
		[
			0x21, # nagłówek
			0x80, # parametry
			0xa1, # nagłówek powiązany
			[2], # tooltip
			[9, 2], #opis
			[
				#['int48','nSv',[10],[11]]
			]
		],

		[
			0xa1, # nagłówek
			0x6a, # parametry
			0x21, # nagłówek powiązany
			[2], # tooltip
			[2], #opis
			[
				['float24','%',[3],[4, 5]],
				['int32','imp',[4],[4, 6]]
			]
		],
			#=================ZR3Dose=========================================
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
			
			#=================ZR3SetDose=========================================
		[
			0x23, # nagłówek
			0x80, # parametry
			0xa3, # nagłówek powiązany
			[7, 10], # tooltip
			[7, 10], #opis
			[
				['int48','nSv',[10],[13]]
			]
		],
			
		[
			0xa3, # nagłówek
			0x4a, # parametry
			0x23, # nagłówek powiązany
			[7, 10], # tooltip
			[7, 10], #opis
			[
				#['int48','nSv',[10],[11]]
			]
		],
			#=================ZR3SetDoseAlarmLevel=========================================
		[
			0x25, # nagłówek
			0x80, # parametry
			0xa5, # nagłówek powiązany
			[7, 14, 10], # tooltip
			[7, 14, 10], #opis
			[
				['int48','nSv',[14, 10],[16]]
			]
		],
			
		[
			0xa5, # nagłówek
			0x4a, # parametry
			0x25, # nagłówek powiązany
			[7, 14, 10], # tooltip
			[7, 14, 10], #opis
			[
				#['int48','nSv',[10],[11]]
			]
		],
			#=================ZR3GetDoseAlarmLevel=========================================
		[
			0x26, # nagłówek
			0x80, # parametry
			0xa6, # nagłówek powiązany
			[14, 10], # tooltip
			[14, 10], #opis
			[
				#['int48','nSv',[14, 10],[16]]
			]
		],
			
		[
			0xa6, # nagłówek
			0x4a, # parametry
			0x26, # nagłówek powiązany
			[14, 10], # tooltip
			[14, 10], #opis
			[
				['int48','nSv',[14, 10],[17]]
			]
		],
			
			#=================ZR3CheckDoseAlarm=========================================
		[
			0x24, # nagłówek
			0x80, # parametry
			0xa4, # nagłówek powiązany
			[14, 10], # tooltip
			[14, 10], #opis
			[
				#['int48','nSv',[10],[13]]
			]
		],
			
		[
			0xa4, # nagłówek
			0x6a, # parametry
			0x24, # nagłówek powiązany
			[14, 10], # tooltip
			[14, 10], #opis
			[
				['bool','',[14, 10],[11]]
			]
		],
			#=================ZR3GetErrorList======================================
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
adrs2=[0x02, 0xFE]

#name3='test3'
#adrs3=[0x03, 0x14]

#name4='test4'
#adrs4=[0x14, 0xFE]

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
        sdata+=(bytes(string, 'utf-8'))
        ptrs.append(len(sdata)+1)
        sdata+=(bytes([0x00, 0xFF, 0xFF ]))
    sdata += b'\x00'

    for i in range(langsc):
        lstrs.append(bytearray())
    for langstrings in txt:
        for i in range(langsc):
            lstrs[i] += bytes(langstrings[i], 'utf-8')
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
    devd += bytes(dev[3], 'utf-8')
    devd += b'\x00'
    devd += bytes(dev[4], 'utf-8')
    devd += b'\x00'
    devd += bytes(dev[5], 'utf-8')
    devd += b'\x00'
    for i in dev[6]:
        devd += bytes([i])
    devd += b'\xFF'
    for i in dev[7]:
        devd += bytes([i])
    devd += b'\xFF'
    for fu in dev[8]:
        devd += bytes(fu[0], 'utf-8')
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
            metd += bytes(arg[0], 'utf-8')
            metd += b'\x00'
            metd += bytes(arg[1], 'utf-8')
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
#genfun(name3, adrs3, langs, texts, gdev, gmeths)
#genfun(name4, adrs4, langs, texts, gdev, gmeths)

#system('pause')
