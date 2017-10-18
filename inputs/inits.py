from os import system

name1='test1'
adrs1=[0x01, 0x02]

name2='test2'
adrs2=[0x02, 0xFE]

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

system('pause')
