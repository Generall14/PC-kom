from os import system

# <myadr> <nextadr> <2B wskaźnik na tablicę stringów> <2B długość tablicy str>
 
langs=['pol', 'eng']
texts=[
    ['dupa', 'ass'],
    ['dawka', 'dose'],
    ['moc dawki', 'dose rate'],
    ['koniec','end']
    ]

name1='test1'
adrs1=[0x01, 0x02]

name2='test2'
adrs2=[0x02, 0x03]

name3='test3'
adrs3=[0x03, 0x14]

name4='test4'
adrs4=[0x14, 0xFE]

def genfun(name, adr, lng, txt):
    nuls = [0x00, 0x00]
    filea = open('MendiumBusConnectorIn.cfg', 'at')
    filea.write('inputs/'+name+'.bin\n')
    filea.close()
    file = open(name+'.bin', 'wb')
    globaldata = bytearray()

    #generowanie wstępu:
    globaldata+=(bytes(adr))
    globaldata+=(b'\xff\xff\xff\xff')

    #generowanie tablicy stringów:
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
    
    file.write(globaldata)
    file.close()
    return

filem = open('MendiumBusConnectorIn.cfg', 'wt')
filem.close()

genfun(name1, adrs1, langs, texts)
genfun(name2, adrs2, langs, texts)
genfun(name3, adrs3, langs, texts)
genfun(name4, adrs4, langs, texts)

#system('pause')
