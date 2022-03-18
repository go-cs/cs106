#include "Plotter.h"
#include <iostream>
#include <strlib.h>
using namespace std;

void runPlotterScript(istream& input) {
    /* TODO: Delete this line and the one after it, then implement this function. */
    (void) input;
    string line;
    bool penValid = false;//笔抬起来就无效

    PenStyle style = {1, "black"};
    double x1 = 0, y1 = 0, x2, y2;
    //每次读一行，直至到达文件末尾
    while (getline(input,line)) {
        Vector<string> words = stringSplit(line, " ");//用空格拆分每次读入的行
        words[0] = toLowerCase(words[0]);//要转换成小写来作比较
        if (words[0] == "penup"){
            penValid = false;
        } else if (words[0] == "pendown"){
            penValid = true;
        } else if (words[0] == "moveabs"){
            x2 = stringToReal(words[1]);
            y2 = stringToReal(words[2]);
            if (penValid) drawLine(x1, y1, x2, y2, style);
            x1 = x2; y1 = y2;
        } else if (words[0] == "moverel") {
            x2 = x1 + stringToReal(words[1]);
            y2 = y1 + stringToReal(words[2]);
            if (penValid) drawLine(x1, y1, x2, y2, style);
            x1 = x2;y1=y2;
        } else if (words[0] == "pencolor") {
            style.color = words[1];
        } else if (words[0] == "penwidth") {
            style.width = stringToReal(words[1]);
        }
    }

}
