import glob
from unittest import result
from pylab import *
import matplotlib.pyplot as plt
from PIL import Image
import imageio
import os
#some imports aren't necessary, i used them just for several test i ve done 

files = sorted(glob.glob('roomtour/*')) #specify the path if the out_data file isn't in the same file 
images = []
for file in files:
    with open(file, 'r') as inf:
        lines = inf.readlines()
        resultx=[]
        resulty=[]
        polarite=[]
        for x in lines: #for each line, we get the 2nd columln for x, 3rd for y and 5th for the polarity 
            resultx.append(x.split()[2])
            resulty.append(x.split()[3])
            polarite.append(x.split()[5])

            #print(x)
        inf.close()
        coordx = []
        coordy = []
        polarite_val=[]
        for x in range(len(resultx)):  #conversion form strings to ints 
            coordx.append(int(resultx[x]))
            coordy.append(int(resulty[x]))  
            polarite_val.append(int(polarite[x])) 
        def newImg():
            img = Image.new('RGB', (2100, 1100))
            for x in range(len(resultx)):
                if polarite_val [x]==1:
                    img.putpixel((coordx[x],coordy[x]), (1,155,55))
                    print(coordx[x],coordy[x])
                else:
                    img.putpixel((coordx[x],coordy[x]), (250,0,0))
            img.save('sqr.png')

            return img
    wallpaper = newImg()
    #wallpaper.show() 
    images.append(wallpaper)  

imageio.mimsave(os.path.join('movieroomtour.gif'), images, duration = 0.04) # modify duration as needed

 
    #print(lines[1:2])