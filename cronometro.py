import time
import cronus.beat as beat
import select
import sys

centesimo=0
segundo=0
minuto=0
hora=0 


beat.set_rate(100)


while beat.true():
  char = select.select(sys.stdin, [], [], 0.1)[0]
  if char:
    print char
  print "%02d:%02d:%02d,%02d" % (hora,minuto,segundo,centesimo)
  centesimo=centesimo+1
  if centesimo>=100:
    segundo=segundo+1
    centesimo=0
  if segundo>=60:
    minuto=minuto+1
    segundo=0
  if minuto>=60:
    hora=hora+1
    minuto=0
  beat.sleep()

