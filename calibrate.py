#!/usr/bin/python
import serial
import time
import json
import pprint

ser = serial.Serial('/dev/ttyACM0', 9600)

def wakeup():
  while True:
    ser.write("ping")
    time.sleep(1)
    if ser.inWaiting() != 0:
      while ser.inWaiting():
        time.sleep(1)
        s = ser.readline()
        print s
      return
    print "still waiting... %s" % ser.inWaiting()

def values():
  try:
#    ser.write("values")
    s = ser.readline()
    return json.loads(s)
  except Exception as e:
    print e


def average(data):
  if not data:
    return
  values = []
  for k in data.keys():
    for val in data[k]:
      values.append(val)
  return values

while True:
  time.sleep(5)
  data = values()
  print average(data)

