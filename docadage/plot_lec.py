from unittest import result
from pylab import *
import matplotlib.pyplot as plt
from PIL import Image



f=open("/Users/aelmoudn/Desktop/Anass_Cerbere/out_data/out_00005","r")
lines=f.readlines()
resultx=[]
resulty=[]
polarite=[]
i=0
for x in lines:
    resultx.append(x.split()[2])
    resulty.append(x.split()[3])
    polarite.append(x.split()[5])
    #print(x)
    i=i+1
    print(i)
f.close()

coordx = []
coordy = []
polarite_val=[]
for x in range(len(resultx)):
    coordx.append(int(resultx[x]))
    coordy.append(int(resulty[x]))
    polarite_val.append(int(polarite[x]))

#print(len(resultx))

def newImg():
    img = Image.new('RGB', (1900, 1080))
    for x in range(len(resultx)):
        if polarite_val [x]==1:
            img.putpixel((coordx[x],coordy[x]), (1,155,55))
            #print(coordx[x],coordy[x])
        else:
            img.putpixel((coordx[x],coordy[x]), (250,0,0))
    img.save('sqr.png')

    return img

wallpaper = newImg()  #activate the show to see the picture. 
#wallpaper.show()


#print(resultx)
#print(resulty)
#print(resultx[1]+resulty[1]) 
#print(coordx[1]+ coordy[1])
#plot(resultx, resulty)
#show() # affiche la figure a l'ecran



