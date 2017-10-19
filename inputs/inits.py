from os import system

name1='test1'
adrs1=[0x01, 0x02]

name2='test2'
adrs2=[0x02, 0x03]

name3='test3'
adrs3=[0x03, 0x14]

name4='test4'
adrs4=[0x14, 0xFE]

def genfun(name, adr):
    nuls = [0x00, 0x00]
    filea = open('MendiumBusConnectorIn.cfg', 'at')
    filea.write('inputs/'+name+'.bin\n')
    filea.close()
    file = open(name+'.bin', 'wb')
    file.write(bytes(adr))
    file.close()
    return

filem = open('MendiumBusConnectorIn.cfg', 'wt')
filem.close()

genfun(name1, adrs1)
genfun(name2, adrs2)
genfun(name3, adrs3)
genfun(name4, adrs4)

system('pause')
