import processing.serial.*;

import java.util.ArrayList;

ArrayList X = new ArrayList();
ArrayList Y = new ArrayList();

static final char START = '<';
static final char DATA = '#';
static final char END = '>';

String gestureNames[] = { 
  "circleCCW", "v", "pigTail", "circleCW"
};

Serial port;
String result = "..."; 
boolean portOpened = false;
boolean echo = true;

String echoString = echo ? "..." : "";

int circleCCWPoints[] = {
  -1639, 4, -1786, 397, -1688, 807, -1475, 1167, -1147, 1429, -787, 1659, -410, 1839, -17, 2003, 408, 2068, 834, 2052, 1244, 1954, 1571, 1692, 1817, 1347, 1948, 938, 1997, 512, 2014, 86, 1981, -339, 1834, -732, 1686, -1125, 1440, -1470, 1129, -1764, 752, -1945, 343, -2027, -66, -1961, -476, -1846, -885, -1732, -1278, -1584, -1655, -1388, -1966, -1093, -2081, -683, -1917, -290, -1737, 37
};
int circleCWPoints[] = {
  -963, 4, -1096, -375, -1162, -772, -1063, -1152, -831, -1465, -499, -1697, -118, -1845, 263, -1994, 661, -1994, 992, -1796, 1224, -1465, 1390, -1102, 1506, -706, 1589, -309, 1606, 103, 1589, 516, 1573, 912, 1490, 1308, 1324, 1672, 1092, 1985, 727, 2101, 312, 2068, -51, 1886, -366, 1639, -648, 1341, -864, 1011, -980, 615, -1030, 218, -1328, -12, -1726, -128, -2108, -227, -2489, -342
};

void setup()
{
  try {
    port = new Serial(this, "COM8", 115200);
    portOpened = true;
  }
  catch (Exception e)
  {
  }

  size(1000, 1000);
  textSize(20);
}

void send(char command, int x, int y)
{
  print(command);
  print(x);
  print(' ');
  print(y);
  println();

  if (portOpened)
  {
    port.write(command);
    port.write(x >> 8);
    port.write(x & 0xFF );
    port.write(y >> 8);
    port.write(y & 0xFF );
  }

  switch(command)
  {
  case START:
    X.add(x);
    Y.add(y); 
    break;

  case DATA:
    X.add(x);
    Y.add(y);
    break;

  case END:
    X.clear();
    Y.clear();    

    break;
  }

  if (echo)
  {
    echoString = readString();
    println(echoString);
  }

}


void draw()
{
  background(portOpened ? 0 : 100);

  stroke(255);

  int y = 50;
  int dy = 50;

  text(result, 10, y += dy);
  text(echoString, 10, y += dy);
  text(X.size(), 10, y += dy);

  for (int i = 0; i < X.size () - 1; i++)
    line(((Integer)X.get(i)).intValue(), ((Integer)Y.get(i)).intValue(), ((Integer)X.get(i+1)).intValue(), ((Integer)Y.get(i+1)).intValue());
}

void mousePressed()
{
  send(START, mouseX, mouseY);
}

int _mx;
int _my;

void mouseDragged()
{ 
  if (dist(_mx, _my, mouseX, mouseY) < 50)
    return;

  _mx = mouseX;
  _my = mouseY; 

  send(DATA, mouseX, mouseY);
}

void mouseReleased()
{
  send(END, mouseX, mouseY);

  result = readResult();
//  println("circleCCW, v, pigTail, circleCW");
}

boolean cw = true;

void keyPressed()
{
  if (key == 'e')
  {
    send(END, 0, 0);

    println(readString());
    return;
  }

  int x = 0;
  int y = 0;
  int N = 64;
  int increment = 4;

  for (int i = 0; i < N; i+=increment)
  {
    x = cw ? circleCWPoints[i] : circleCCWPoints[i];
    y = cw ? circleCWPoints[i + 1] : circleCCWPoints[i + 1];

    if (i == 0)
      send(START, x, y);
    else if (i + increment < N) 
      send(DATA, x, y);
    else
      send(END, x, y);

    result = readString();
    println(result);
  }

  cw = !cw;
} 


String readResult()
{ 
  waitFor(2);

  int index = port.read();
  int score = port.read();

  return index + " " + score + "%";
}

String readString()
{  
  waitFor(1);

  String result = null;

  while (port.available () > 0 && result == null)
  {
    result = port.readStringUntil('\n');

    if (result != null)
      return result;
    else
      print("_");

    //    waitFor(1);
  }

  return "null";
  
}


void waitFor(int n)
{ 
  while (port.available () < n)
  {
    try { 
      Thread.sleep(1);
      print(".");
    } 
    catch (Exception e) {
      print("x");
    }
  }
}

