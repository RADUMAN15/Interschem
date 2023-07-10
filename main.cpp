#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#include <graphics.h>
#include <winbgim.h>

#define FUNDAL LIGHTGRAY
///culori
#define COLOR_PIESA YELLOW
#define COLOR_BUTON LIGHTRED
#define COLOR_BUTON_SELECT RED
#define COLOR_TEXT BLACK
#define COLOR_CONTUR BLACK
///dimensiune fundal
#define WIDTH 1920
#define HEIGHT 1080
#define R 40 ///raza rest
#define R_IF_C 65 ///raza if/calcul

using namespace std;
///coordonate piese
struct lista
{
    lista *urm;
    int indice;
};
struct piesa
{
    bool parsat;
    int vizitat;
    lista *l_ext;
    lista *l_int;
    char txt[20];
    int ID;
    int x, y;
} p[1000];
///coordonate meniu
struct buton_meniu
{
    int x1, x2, y1, y2;
    char text[20];
} bm[13];
///variabile compilare
struct variabile
{
    char nume='0';
    int valoare=0;
}v[100];

bool op_imposibila = false;
int nr_piese;
char text_if_default[13]="a<=b && b<=c"; ///text if
char text_calcul_default[14]="a=a+b+c*d-a/b"; ///text calcul

void desen_fundal()
{
    setbkcolor(FUNDAL);
    cleardevice();
    setfillstyle(SOLID_FILL,WHITE);
    bar(0,HEIGHT/10,WIDTH/1.7,(HEIGHT/10)+10);
    bar(WIDTH/1.7,0,(WIDTH/1.7)+10,HEIGHT);
    bar((WIDTH/1.7)+10,HEIGHT/3.9,WIDTH,(HEIGHT/3.9)+10);
}
void desen_meniu()
{
    setfillstyle(SOLID_FILL,COLOR_BUTON);
    setcolor(COLOR_BUTON);
    int p=0, h=HEIGHT/50, l=((WIDTH/1.7)-h)/6;
    for(int i=1; i<=6; i++)
    {
        bm[i].x1=p+h;
        bm[i].x2=p+l;
        bm[i].y1=h;
        bm[i].y2=(HEIGHT/10)-h;
        bar(p+h,h,p+l,(HEIGHT/10)-h);
        p=p+l;
    }
    l=bm[1].x2-bm[1].x1, h=bm[1].y2-bm[1].y1;
    for(int i=7; i<=12; i++)
    {
        switch(i)
        {
        case 7:
        {
            bm[i].x1=(WIDTH/1.7)+40;
            bm[i].x2=(WIDTH/1.7)+30+l;
            bm[i].y1=HEIGHT/50;
            bm[i].y2=HEIGHT/50+h;
            bar(bm[i].x1,bm[i].y1,bm[i].x2,bm[i].y2);
        }
        break;
        case 8:
        {
            bm[i].x1=(WIDTH/1.7)+50+l;
            bm[i].x2=(WIDTH/1.7)+50+l+l;
            bm[i].y1=HEIGHT/50;
            bm[i].y2=HEIGHT/50+h;
            bar(bm[i].x1,bm[i].y1,bm[i].x2,bm[i].y2);
        }
        break;
        case 9:
        {
            bm[i].x1=(WIDTH/1.7)+40;
            bm[i].x2=(WIDTH/1.7)+30+l;
            bm[i].y1=HEIGHT/50+h+20;
            bm[i].y2=HEIGHT/50+h+20+h;
            bar(bm[i].x1,bm[i].y1,bm[i].x2,bm[i].y2);
        }
        break;
        case 10:
        {
            bm[i].x1=(WIDTH/1.7)+50+l;
            bm[i].x2=(WIDTH/1.7)+50+l+l;
            bm[i].y1=HEIGHT/50+h+20;
            bm[i].y2=HEIGHT/50+h+20+h;
            bar(bm[i].x1,bm[i].y1,bm[i].x2,bm[i].y2);
        }
        break;
        case 11:
        {
            bm[i].x1=(WIDTH/1.7)+40;
            bm[i].x2=(WIDTH/1.7)+30+l;
            bm[i].y1=HEIGHT/50+h+20+h+20;
            bm[i].y2=HEIGHT/50+h+20+h+20+h;
            bar(bm[i].x1,bm[i].y1,bm[i].x2,bm[i].y2);
        }
        break;
        case 12:
        {
            bm[i].x1=(WIDTH/1.7)+50+l;
            bm[i].x2=(WIDTH/1.7)+50+l+l;
            bm[i].y1=HEIGHT/50+h+20+h+20;
            bm[i].y2=HEIGHT/50+h+20+h+20+h;
            bar(bm[i].x1,bm[i].y1,bm[i].x2,bm[i].y2);
        }
        break;
        }
    }
    setcolor(COLOR_TEXT);
    for(int i=1; i<=12; i++)
    {
        switch(i)
        {
        case 1:
            strcpy(bm[i].text,"START");
            break;
        case 2:
            strcpy(bm[i].text,"STOP");
            break;
        case 3:
            strcpy(bm[i].text,"INTRARE");
            break;
        case 4:
            strcpy(bm[i].text,"IESIRE");
            break;
        case 5:
            strcpy(bm[i].text,"DECIZIE");
            break;
        case 6:
            strcpy(bm[i].text,"ATRIBUIRE");
            break;
        case 7:
            strcpy(bm[i].text,"LINIE");
            break;
        case 8:
            strcpy(bm[i].text,"STERGERE");
            break;
        case 9:
            strcpy(bm[i].text,"DECODARE");
            break;
        case 10:
            strcpy(bm[i].text,"COMPILARE");
            break;
        case 11:
            strcpy(bm[i].text,"SALVARE");
            break;
        case 12:
            strcpy(bm[i].text,"INCARCARE");
            break;
        }
        setbkcolor(COLOR_BUTON);
        if(i>7 || i==6) outtextxy((bm[i].x2-bm[i].x1)/3+bm[i].x1-10,(bm[i].y2-bm[i].y1)/3+bm[i].y1,bm[i].text);
        else outtextxy((bm[i].x2-bm[i].x1)/3+bm[i].x1,(bm[i].y2-bm[i].y1)/3+bm[i].y1,bm[i].text);
    }
}
///desene piese
void stop_button(int x, int y, int r, int culoare, int culoare_text, int contur)
{
    r = r*sqrt(2)/2;
    setfillstyle(SOLID_FILL,culoare); ///setez culoarea umplere patrat
    setcolor(contur);
    line(x-r,y-r,x+r,y-r);
    line(x-r,y-r,x-r,y+r);
    line(x-r,y+r,x+r,y+r);
    line(x+r,y+r,x+r,y-r);
    floodfill(x,y,contur); ///umplere forma patrat
    setbkcolor(culoare); ///culoarea background text
    setcolor(culoare_text); ///setez culoarea textului

    int t_h = textheight("STOP");
    int t_w = textwidth("STOP");
    outtextxy(x-t_w/2,y-t_h/2,"STOP");

}
void start_button(int x, int y, int r, int culoare, int culoare_text, int contur)
{
    setfillstyle(SOLID_FILL,culoare); ///setez culoarea umplere cerc
    setcolor(contur);
    circle(x,y,r*0.7);
    floodfill(x,y,contur);
    setbkcolor(culoare); ///culoarea background text
    setcolor(culoare_text); ///setez culoarea textului

    int t_h = textheight("START");
    int t_w = textwidth("START");
    outtextxy(x-t_w/2,y-t_h/2,"START");

}
void if_button(int x, int y, int r, char text[12], int culoare, int culoare_text, int contur)
{

    setfillstyle(SOLID_FILL,culoare); ///setez culoarea umplere cerc
    setcolor(contur);

    line(x-r,y,x+r,y);
    line(x-r,y,x,y-r);
    line(x+r,y,x,y-r);
    floodfill(x,y-1,contur);
    setbkcolor(culoare); ///culoarea background text
    setcolor(culoare_text); ///setez culoarea textului

    int t_h = textheight(text);
    int t_w = textwidth(text);
    outtextxy(x-t_w/2,y-t_h,text);
    outtextxy(x-14,y-40,"A | F");

}
void calculus_button(int x, int y, int r, char text[13], int culoare, int culoare_text, int contur)
{
    setfillstyle(SOLID_FILL,culoare); ///setez culoarea umplere dreptunghi
    setcolor(contur);
    line(x-r+5,y+r/4,x+r-5,y+r/4);
    line(x-r+5,y-r/4,x+r-5,y-r/4);
    line(x-r+5,y-r/4,x-r+5,y+r/4);
    line(x+r-5,y-r/4,x+r-5,y+r/4);
    floodfill(x,y,contur); ///umplere forma dreptunghi
    setbkcolor(culoare); ///culoarea background text
    setcolor(culoare_text); ///setez culoarea textului

    int t_h = textheight(text);
    int t_w = textwidth(text);
    outtextxy(x-t_w/2,y-t_h/2,text);
}

void output_button(int x, int y, int r,char var[2], int culoare, int culoare_text, int contur)
{
    setfillstyle(SOLID_FILL,culoare); ///setez culoarea umplere patrat
    setcolor(contur);
    line(x-r+1,y,x-r*sqrt(2)/2,y-r*sqrt(2)/2);
    line(x-r+1,y,x+r-1,y);
    line(x+r-1,y,x+r*sqrt(2)/2,y-r*sqrt(2)/2);
    line(x-r*sqrt(2)/2,y-r*sqrt(2)/2,x+r*sqrt(2)/2,y-r*sqrt(2)/2);
    floodfill(x,y-1,contur);
    setbkcolor(culoare); ///culoarea background text
    setcolor(culoare_text); ///setez culoarea textului
    int t_h = textheight(var);
    int t_w = textwidth(var);
    outtextxy(x-t_w/2,y-t_h,var);
}
void input_button(int x, int y, int r,char var[2], int culoare, int culoare_text, int contur)
{
    setfillstyle(SOLID_FILL,culoare); ///setez culoarea umplere patrat
    setcolor(contur);
    line(x-r+1,y,x-r*sqrt(2)/2,y+r*sqrt(2)/2);
    line(x-r+1,y,x+r-1,y);
    line(x+r-1,y,x+r*sqrt(2)/2,y+r*sqrt(2)/2);
    line(x-r*sqrt(2)/2,y+r*sqrt(2)/2,x+r*sqrt(2)/2,y+r*sqrt(2)/2);

    floodfill(x,y+1,contur);
    setbkcolor(culoare); ///culoarea background text
    setcolor(culoare_text); ///setez culoarea textului
    int t_h = textheight(var);
    int t_w = textwidth(var);
    outtextxy(x-t_w/2,y+t_h/4,var);
}

///desen linii
void linie (piesa &p1, piesa &p2, int culoare, int p1i, int p2i)
{
    if(culoare==COLOR_CONTUR)
    {
        lista *aux=p1.l_ext;
        bool ok=false;
        while(aux!=NULL)
        {
            if(aux->indice==p2i) ok=true;
            aux=aux->urm;
        }
        if(!ok)
        {
            lista *q=new lista;
            q->indice=p2i;
            q->urm=p1.l_ext;
            p1.l_ext=q;
        }

        aux=p2.l_int;
        ok=false;
        while(aux!=NULL)
        {
            if(aux->indice==p1i) ok=true;
            aux=aux->urm;
        }
        if(!ok)
        {
            lista *q2=new lista;
            q2->indice=p1i;
            q2->urm=p2.l_int;
            p2.l_int=q2;
        }
    }
    else
    {
        lista *q=p1.l_ext, *pred=p1.l_ext;
        while(q!=NULL)
        {
            if(q->indice==p2i)
            {
                if(q==p1.l_ext) p1.l_ext=p1.l_ext->urm;
                else pred->urm=q->urm;
                break;
            }
            pred=q;
            q=q->urm;
        }

        lista *q2=p2.l_int, *pred2=p2.l_int;
        while(q2!=NULL)
        {
            if(q2->indice==p1i)
            {
                if(q2==p2.l_int) p2.l_int=p2.l_int->urm;
                else pred2->urm=q2->urm;
                break;
            }
            pred2=q2;
            q2=q2->urm;
        }
    }
    if(p1.y<p2.y)
    {
        int x1=p1.x, y1, x2=p2.x, y2;
        switch(p1.ID)
        {
        ///start
        case 1:
            y1=p1.y+R*0.7;
            break;
        ///stop
        case 2:
            y1=p1.y+R*sqrt(2)/2;
            break;
        ///input
        case 3:
            y1=p1.y+R*sqrt(2)/2;
            break;
        ///output
        case 4:
            y1=p1.y;
            break;
        ///if
        case 5:
            y1=p1.y;
            break;
        ///calcul
        case 6:
            y1=p1.y+R_IF_C/4;
            break;
        }
        switch(p2.ID)
        {
        ///start
        case 1:
            y2=p2.y-R*0.7;
            break;
        ///stop
        case 2:
            y2=p2.y-R*sqrt(2)/2;
            break;
        ///input
        case 3:
            y2=p2.y;
            break;
        ///output
        case 4:
            y2=p2.y-R*sqrt(2)/2;
            break;
        ///if
        case 5:
            y2=p2.y-R_IF_C;
            break;
        ///calcul
        case 6:
            y2=p2.y-R_IF_C/4;
            break;
        }
        setcolor(culoare);
        line(x1,y1,x1,y1+(y2-y1)/2);
        line(x1,y1+(y2-y1)/2,x2,y1+(y2-y1)/2);
        line(x2,y1+(y2-y1)/2,x2,y2);
        line(x2,y2,x2+5,y2-5);
        line(x2,y2,x2-5,y2-5);
    }
    else
    {
        int x1=p1.x, y1, x2=p2.x, y2;
        switch(p1.ID)
        {
        ///start
        case 1:
            y1=p1.y+R*0.7;
            break;
        ///stop
        case 2:
            y1=p1.y+R*sqrt(2)/2;
            break;
        ///input
        case 3:
            y1=p1.y+R*sqrt(2)/2;
            break;
        ///output
        case 4:
            y1=p1.y;
            break;
        ///if
        case 5:
            y1=p1.y;
            break;
        ///calcul
        case 6:
            y1=p1.y+R_IF_C/4;
            break;
        }
        switch(p2.ID)
        {
        ///start
        case 1:
            y2=p2.y-R*0.7;
            break;
        ///stop
        case 2:
            y2=p2.y-R*sqrt(2)/2;
            break;
        ///input
        case 3:
            y2=p2.y;
            break;
        ///output
        case 4:
            y2=p2.y-R*sqrt(2)/2;
            break;
        ///if
        case 5:
            y2=p2.y-R_IF_C;
            break;
        ///calcul
        case 6:
            y2=p2.y-R_IF_C/4;
            break;
        }
        setcolor(culoare);
        if(x1<x2)
        {
            line(x1,y1,x1,y1+20);
            line(x1,y1+20,x1-70,y1+20);
            line(x1-70,y1+20,x1-70,y2-20);
            line(x1-70,y2-20,x2,y2-20);
            line(x2,y2-20,x2,y2);
        }
        else
        {
            line(x1,y1,x1,y1+20);
            line(x1,y1+20,x1+70,y1+20);
            line(x1+70,y1+20,x1+70,y2-20);
            line(x1+70,y2-20,x2,y2-20);
            line(x2,y2-20,x2,y2);
        }
        line(x2,y2,x2+5,y2-5);
        line(x2,y2,x2-5,y2-5);
    }
}

void stergere()
{
    setfillstyle(SOLID_FILL,FUNDAL);
    bar(0,(HEIGHT/10)+10,WIDTH/1.7,HEIGHT);
    bar((WIDTH/1.7)+10,(HEIGHT/3.9)+10,WIDTH,HEIGHT);
    nr_piese=0;
    for(int i=0; i<1000; i++)
    {
        p[i].ID=0;
        p[i].x=0;
        p[i].y=0;
        p[i].txt[0]=NULL;
        p[i].l_int=NULL;
        p[i].l_ext=NULL;
        p[i].parsat=false;
        p[i].vizitat=0;
    }
    for(int i=0; i<100; i++)
    {
        v[i].nume='0';
        v[i].valoare=0;
    }
}
int ordinea_efec_op(char op)
{
    if(op == '+'||op == '-')
        return 1;
    if(op == '*'||op == '/' || op == '%')
        return 2;
    return 0;
}
int fa_operatie(int a, int b, char op)
{
    if(b == 0 && (op == '/' || op == '%'))
    {
        op_imposibila = true;
        return -1;
    }
    switch(op)
    {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
        case '%':
            return a % b;
    }
}
int rez_expresie(char s[12], int start, int stop)   /// RETURNEAZA O SUMA/DIF/PROD/IMP/MODUL
{
    ///operatori + - / * %
    ///operanzi 0,1,..,100 sau a,b,...,z (iei ca atare ca daca gasesti o variabila ea are o valoare)
    /// si ( ) - optional

    stack <int> valori;
    stack <char> operatori;

    for(int i = start; i<stop; i++)
    {
        if(s[i] == ' ')
            continue;

        else if(s[i] == '(')
        {
            operatori.push(s[i]);
        }
        else if(s[i]>='0' && s[i]<='9')
        {
            int nr = 0;
            while(i<stop && s[i]>='0' && s[i]<='9')
            {
                nr = (nr*10) + (s[i]-'0');
                i++;
            }
            valori.push(nr);
            i--;
        }
        else if(s[i] >= 'a' && s[i] <= 'z')
        {
            for(int j = 0; j <= 99; j++)
                if(v[j].nume == s[i])
                {
                    valori.push(v[j].valoare);
                    break;
                }
        }
        else if(s[i] == ')')
        {
            while(!operatori.empty() && operatori.top() != '(')
            {
                char op = operatori.top();
                operatori.pop();

                int val2 = valori.top();
                valori.pop();

                if(op=='-' && (valori.empty() || operatori.top()=='('))
                {
                    valori.push(fa_operatie(0, val2, op));
                }
                else
                {
                    int val1 = valori.top();
                    valori.pop();
                    valori.push(fa_operatie(val1, val2, op));
                }

            }
            if(!operatori.empty())
               operatori.pop();
        }
        else
        {
            while(!operatori.empty() && ordinea_efec_op(operatori.top()) >= ordinea_efec_op(s[i]))
            {
                char op = operatori.top();
                operatori.pop();

                int val2 = valori.top();
                valori.pop();

                if(op=='-' && (valori.empty() || operatori.top()=='('))
                {
                    valori.push(fa_operatie(0, val2, op));
                }
                else
                {
                    int val1 = valori.top();
                    valori.pop();
                    valori.push(fa_operatie(val1, val2, op));
                }
            }
            operatori.push(s[i]);
        }
    }
    while(!operatori.empty())
    {
        char op = operatori.top();
        operatori.pop();

        int val2 = valori.top();
        valori.pop();

        if(op=='-' && (valori.empty() || operatori.top()=='('))
        {
            valori.push(fa_operatie(0, val2, op));
        }
        else
        {
            int val1 = valori.top();
            valori.pop();
            valori.push(fa_operatie(val1, val2, op));
        }
    }
    return valori.top();
}
bool valideaza(int var1, int var2, char op[])
{
    if(strcmp(op,"&&")==0) return var1&&var2;

    if(strcmp(op,"||")==0) return var1||var2;

    if(strcmp(op,">=")==0) return var1>=var2;

    if(strcmp(op,"<=")==0) return var1<=var2;

    if(strcmp(op,"==")==0) return var1==var2;

    if(strcmp(op,"!=")==0) return var1!=var2;

    if(strcmp(op,">")==0) return var1>var2;

    if(strcmp(op,"<")==0) return var1<var2;
}
bool calculeaza_expresie(int start, int stop, char s[14])   ///RETURNNEAZA REZ UNUI EXPRESII SIMPLE
{
        int i = start;
        int term1 = -1;
        int term2 = -1;
        char op[3]=""; ///aici pun operatorul

        while(i < stop && s[i]!='!' && s[i]!='<' && s[i]!='>' && s[i]!='=')
            i++;

        term1 = rez_expresie(s,start,i);
        if(i==stop)
        {
            if(term1!=0) return true;
            else return false;
        }
        op[0] = s[i];i++;
        if(s[i]=='!' || s[i]=='<' || s[i]=='>' || s[i]=='=')
        {
            op[1] = s[i];
            op[2] = NULL;
            i++;
        }
        else
            op[1] = NULL;

        term2 = rez_expresie(s,i,stop);

        //cout<<"VALOARE1: "<<term1<<endl;
        //cout<<"VALOARE2: "<<term2<<endl;
        //cout<<"OPERATOR: "<<op<<endl;
        return valideaza(term1,term2,op);
}
bool val_expresie(char s[14])
{
    /// exp == exp <=> EXP
    ///     <=
    ///     >=
    ///     !=
    ///      <
    ///      >
    /// EXP && EXP -> conventie && = 1
    ///     ||     -> conventie || = 0


    bool exista_si = false;
    bool exista_sau = false;
    int t1dr = -1;
    int t2st = -1;

    if(strstr(s,"&&")!=NULL)
    {
        exista_si = true;
        for(int i = 0 ; s[i]!=NULL; i++)
            if(s[i]=='&')
            {
                t1dr = i - 2;
                t2st = i + 3;
                break;
            }
    }
    else if (strstr(s,"||")!=NULL)
    {
        exista_sau = true;
        for(int i = 0 ; s[i]!=NULL; i++)
            if(s[i]=='|')
            {
                t1dr = i - 2;
                t2st = i + 3;
                break;
            }
    }
    if(!exista_si && !exista_sau) /// -> am un singur operator
    {
        return calculeaza_expresie(0,strlen(s),s);
    }
    else if(exista_si)  ///Calculez EXP1 si EXP2 si dupa fac && pe ele
    {
        return valideaza(calculeaza_expresie(0,t1dr+1,s),calculeaza_expresie(t2st,strlen(s),s),"&&");
    }
    else if(exista_sau)  ///Calculez EXP1 si EXP2 si dupa fac || pe ele
    {
        return valideaza(calculeaza_expresie(0,t1dr+1,s),calculeaza_expresie(t2st,strlen(s),s),"||");
    }
}
void compilare(piesa ps, int x, int &y)
{
    switch(ps.ID)
    {
        case 1:
        {
            start_button(ps.x,ps.y,R,FUNDAL,FUNDAL,FUNDAL);
            start_button(ps.x,ps.y,R,COLOR_BUTON_SELECT,COLOR_TEXT,COLOR_CONTUR);
            setcolor(COLOR_TEXT);
            setbkcolor(FUNDAL);
            outtextxy(x,y,"Start program!");
            y+=15;
            delay(20);
            compilare(p[ps.l_ext->indice],x,y);
            break;
        }
        case 2:
        {
            stop_button(ps.x,ps.y,R,FUNDAL,FUNDAL,FUNDAL);
            stop_button(ps.x,ps.y,R,COLOR_BUTON_SELECT,COLOR_TEXT,COLOR_CONTUR);
            setcolor(COLOR_TEXT);
            setbkcolor(FUNDAL);
            outtextxy(x,y,"Stop program!");
            delay(20);
            break;
        }
        case 3:
        {
            input_button(ps.x,ps.y,R,ps.txt,FUNDAL,FUNDAL,FUNDAL);
            input_button(ps.x,ps.y,R,ps.txt,COLOR_BUTON_SELECT,COLOR_TEXT,COLOR_CONTUR);
            setcolor(COLOR_TEXT);
            setbkcolor(FUNDAL);
            outtextxy(x,y,"Declarati o variabila:");
            y+=15;
            char text[12]="", txtaux[2]="";
            int k=0, xc=x;
            char carct='a';
            while(carct!='\r')
            {
                carct=getch();
                if(carct!='\r')
                {
                    txtaux[0]=carct;
                    txtaux[1]=NULL;
                    text[k++]=carct;
                    outtextxy(xc,y,txtaux);
                    xc+=10;
                }
            }
            carct=ps.txt[0];
            int val=rez_expresie(text,0,strlen(text));
            if(op_imposibila==true)
            {
                op_imposibila=false;
                outtextxy(x,y,"Eroare: Operatie imposibila!");
            }
            else
            {
                bool gasit=false;
                for(int i=0; i<100; i++)
                    if(v[i].nume==carct)
                    {
                        gasit=true;
                        v[i].valoare=val;
                        break;
                    }
                if(!gasit)
                {
                    for(int i=0; i<100; i++)
                        if(v[i].nume=='0')
                        {
                            v[i].nume=carct;
                            v[i].valoare=val;
                            break;
                        }
                }
                delay(20);
                y+=15;
                compilare(p[ps.l_ext->indice],x,y);
            }
            break;
        }
        case 4:
        {
            output_button(ps.x,ps.y,R,ps.txt,FUNDAL,FUNDAL,FUNDAL);
            output_button(ps.x,ps.y,R,ps.txt,COLOR_BUTON_SELECT,COLOR_TEXT,COLOR_CONTUR);
            setcolor(COLOR_TEXT);
            setbkcolor(FUNDAL);
            outtextxy(x,y,"Afisare: ");
            y+=15;
            char aux2[12]="";
            strcpy(aux2,ps.txt);
            int val=rez_expresie(aux2,0,strlen(aux2));
            if(op_imposibila==true)
            {
                op_imposibila=false;
                outtextxy(x,y,"Eroare: Operatie imposibila!");
            }
            else
            {
                char aux[5]="";
                int cl=val, nr=0;
                if(val==0)
                {
                    aux[0]='0';
                    aux[1]=NULL;
                }
                else
                {
                    if(val<0)
                    {
                        cl=-cl;
                        val=-val;
                        while(cl)
                        {
                            nr++;
                            cl/=10;
                        }
                        nr++;
                        aux[0]='-';
                        for(int i=nr-1; i>0; i--)
                        {
                            aux[i]=(val%10)+'0';
                            val/=10;
                        }
                        aux[nr]=NULL;
                    }
                    else
                    {
                        while(cl)
                        {
                            nr++;
                            cl/=10;
                        }
                        for(int i=nr-1; i>=0; i--)
                        {
                            aux[i]=(val%10)+'0';
                            val/=10;
                        }
                        aux[nr]=NULL;
                    }
                }
                outtextxy(x,y,aux);
                delay(20);
                y+=15;
                compilare(p[ps.l_ext->indice],x,y);
            }
            break;
        }
        case 5:
        {
            if_button(ps.x,ps.y,R_IF_C,ps.txt,FUNDAL,FUNDAL,FUNDAL);
            if_button(ps.x,ps.y,R_IF_C,ps.txt,COLOR_BUTON_SELECT,COLOR_TEXT,COLOR_CONTUR);
            setcolor(COLOR_TEXT);
            setbkcolor(FUNDAL);
            char aux[14]="";
            strcpy(aux, ps.txt);
            bool rez=val_expresie(aux);
            lista *q=ps.l_ext;
            lista *if1, *if2;
            if(p[q->indice].x<ps.x && p[q->urm->indice].x<ps.x)
            {
                if(p[q->indice].y<p[q->urm->indice].y)
                {
                    if1=q;
                    q=q->urm;
                    if2=q;
                }
                else
                {
                    if2=q;
                    q=q->urm;
                    if1=q;
                }
            }
            else if(p[q->indice].x<ps.x)
            {
                if1=q;
                q=q->urm;
                if2=q;
            }
            else
            {
                if2=q;
                q=q->urm;
                if1=q;
            }
            delay(20);
            if(rez==true)
            {
                //outtextxy(x,y,"Conditie adevarata!");
                //y+=15;
                compilare(p[if1->indice],x,y);
            }
            else
            {
                //outtextxy(x,y,"Conditie falsa!");
                //y+=15;
                compilare(p[if2->indice],x,y);
            }
            break;
        }
        case 6:
        {
            calculus_button(ps.x,ps.y,R_IF_C,ps.txt,FUNDAL,FUNDAL,FUNDAL);
            calculus_button(ps.x,ps.y,R_IF_C,ps.txt,COLOR_BUTON_SELECT,COLOR_TEXT,COLOR_CONTUR);
            setcolor(COLOR_TEXT);
            setbkcolor(FUNDAL);
            char aux[14]="";
            strcpy(aux, ps.txt+2);
            int val=rez_expresie(aux,0,strlen(aux));
            if(op_imposibila==true)
            {
                op_imposibila=false;
                outtextxy(x,y,"Eroare: Operatie imposibila!");
            }
            else
            {
                char carct=ps.txt[0];
                bool gasit=false;
                for(int i=0; i<100; i++)
                    if(v[i].nume==carct)
                    {
                        gasit=true;
                        v[i].valoare=val;
                        break;
                    }
                if(!gasit)
                {
                    for(int i=0; i<100; i++)
                        if(v[i].nume=='0')
                        {
                            v[i].nume=carct;
                            v[i].valoare=val;
                            break;
                        }
                }
                delay(20);
                compilare(p[ps.l_ext->indice],x,y);
            }
            break;
        }
    }
}
void decodare(piesa &ps, int x, int &y, int &final_if)
{
    setcolor(COLOR_TEXT);
    setbkcolor(FUNDAL);
    switch (ps.ID)
    {
        ///start
        case 1:
        {
            ps.parsat=true;
            outtextxy(x,y,"#include <iostream>");
            y+=15;
            outtextxy(x,y,"using namespace std;");
            y+=15;
            outtextxy(x,y,"int main()");
            y+=15;
            outtextxy(x,y,"{");
            if(ps.l_ext!=NULL && p[ps.l_ext->indice].ID!=2)
            {
                y+=15;
                decodare(p[ps.l_ext->indice],x+15,y,final_if);
            }
            y+=15;
            outtextxy(x+15,y,"return 0;");
            y+=15;
            outtextxy(x,y,"}");
            break;
        }
        ///stop
        case 2:
            break;
        ///input
        case 3:
        {
            bool este_finalif=false;
            int nr_prec=0;
            lista *prec=ps.l_int;
            while(prec)
            {
                if(p[prec->indice].y<ps.y) nr_prec++;
                prec=prec->urm;
            }
            if(nr_prec>1 && ps.vizitat<2*nr_prec-2) este_finalif=true;
            if(este_finalif)
            {
                ps.vizitat++;
                int iaux;
                for(int i=0; i<nr_piese; i++)
                    if(p[i].x==ps.x && p[i].y==ps.y)
                    {
                        iaux=i;
                        break;
                    }
                final_if=iaux;
                break;
            }
            else
            {
                ps.parsat=true;
                for(int i=0; i<100; i++)
                    if(v[i].nume=='0')
                    {
                        v[i].nume=ps.txt[0];
                        break;
                    }
                char aux[20]="";
                strcpy(aux,"int ");
                strcat(aux,ps.txt);
                strcat(aux,";");
                outtextxy(x,y,aux);
                y+=15;
                strcpy(aux,"cin>>");
                strcat(aux,ps.txt);
                strcat(aux,";");
                outtextxy(x,y,aux);
                lista *q=ps.l_ext;
                int nr=0;
                while(q)
                {
                    nr++;
                    q=q->urm;
                }
                if(nr==1)
                {
                    q=ps.l_ext;
                    if(p[q->indice].parsat==false)
                    {
                        if(p[q->indice].ID!=2) y+=15;
                        decodare(p[ps.l_ext->indice],x,y,final_if);
                    }
                }
                else if(nr==2)
                {
                    q=ps.l_ext;
                    if(p[q->indice].y<ps.y)
                        q=q->urm;
                    if(p[q->indice].parsat==false)
                    {
                        if(p[q->indice].ID!=2) y+=15;
                        decodare(p[ps.l_ext->indice],x,y,final_if);
                    }
                }
                break;
            }
            break;
        }
        ///output
        case 4:
        {
            bool este_finalif=false;
            int nr_prec=0;
            lista *prec=ps.l_int;
            while(prec)
            {
                if(p[prec->indice].y<ps.y) nr_prec++;
                prec=prec->urm;
            }
            if(nr_prec>1 && ps.vizitat<2*nr_prec-2) este_finalif=true;
            if(este_finalif)
            {
                ps.vizitat++;
                int iaux;
                for(int i=0; i<nr_piese; i++)
                    if(p[i].x==ps.x && p[i].y==ps.y)
                    {
                        iaux=i;
                        break;
                    }
                final_if=iaux;
                break;
            }
            else
            {
                ps.parsat=true;
                char aux[20]="";
                strcpy(aux,"cout<<");
                strcat(aux,ps.txt);
                strcat(aux,";");
                outtextxy(x,y,aux);
                lista *q=ps.l_ext;
                int nr=0;
                while(q)
                {
                    nr++;
                    q=q->urm;
                }
                if(nr==1)
                {
                    q=ps.l_ext;
                    if(p[q->indice].parsat==false)
                    {
                        if(p[q->indice].ID!=2) y+=15;
                        decodare(p[ps.l_ext->indice],x,y,final_if);
                    }
                }
                else if(nr==2)
                {
                    q=ps.l_ext;
                    if(p[q->indice].y<ps.y)
                        q=q->urm;
                    if(p[q->indice].parsat==false)
                    {
                        if(p[q->indice].ID!=2) y+=15;
                        decodare(p[ps.l_ext->indice],x,y,final_if);
                    }
                }
                break;
            }
            break;
        }
        ///if/while/for
        case 5:
        {
            bool este_finalif=false;
            int nr_prec=0;
            lista *prec=ps.l_int;
            while(prec)
            {
                if(p[prec->indice].y<ps.y) nr_prec++;
                prec=prec->urm;
            }
            if(nr_prec>1 && ps.vizitat<2*nr_prec-2) este_finalif=true;
            if(este_finalif)
            {
                ps.vizitat++;
                int iaux;
                for(int i=0; i<nr_piese; i++)
                    if(p[i].x==ps.x && p[i].y==ps.y)
                    {
                        iaux=i;
                        break;
                    }
                final_if=iaux;
                break;
            }
            else
            {
                bool are_bucla=false;
                lista *q=ps.l_int;
                while(q!=NULL)
                {
                    if(p[q->indice].y>ps.y) are_bucla=true;
                    q=q->urm;
                }
                if(are_bucla)
                {
                    bool are_for1=false;
                    bool are_for2=false;
                    bool are_for=false;
                    q=ps.l_int;
                    while(q)
                    {
                        if(p[q->indice].y<ps.y && p[q->indice].ID==6 && p[q->indice].txt[0]==ps.txt[0])
                        {
                            are_for1=true;
                            break;
                        }
                        q=q->urm;
                    }
                    q=ps.l_int;
                    while(q)
                    {
                        if(p[q->indice].y>ps.y && p[q->indice].ID==6 && p[q->indice].txt[0]==ps.txt[0])
                        {
                            are_for2=true;
                            break;
                        }
                        q=q->urm;
                    }
                    if(are_for1 && are_for2)
                        are_for=true;
                    if(!are_for)
                    {
                        ps.parsat=true;
                        char aux[20]="";
                        strcpy(aux,"while(");
                        strcat(aux,ps.txt);
                        strcat(aux,")");
                        outtextxy(x,y,aux);
                        y+=15;
                        outtextxy(x,y,"{");
                        q=ps.l_ext;
                        lista *if1, *if2;
                        if(p[q->indice].x<ps.x && p[q->urm->indice].x<ps.x)
                        {
                            if(p[q->indice].y<p[q->urm->indice].y)
                            {
                                if1=q;
                                q=q->urm;
                                if2=q;
                            }
                            else
                            {
                                if2=q;
                                q=q->urm;
                                if1=q;
                            }
                        }
                        else if(p[q->indice].x<ps.x)
                        {
                            if1=q;
                            q=q->urm;
                            if2=q;
                        }
                        else
                        {
                            if2=q;
                            q=q->urm;
                            if1=q;
                        }
                        y+=15;
                        decodare(p[if1->indice],x+15,y,final_if);
                        y+=15;
                        outtextxy(x,y,"}");
                        if(p[if2->indice].ID!=2)
                        {
                            y+=15;
                            decodare(p[if2->indice],x,y,final_if);
                        }
                    }
                    else
                    {
                        q=ps.l_int;
                        if(p[q->indice].y>ps.y)
                            q=q->urm;
                        p[q->indice].parsat=true;
                        ps.parsat=true;
                        char aux[30]="";
                        strcpy(aux,"for(int ");
                        strcat(aux,p[q->indice].txt);
                        strcat(aux,";");
                        strcat(aux,ps.txt);
                        strcat(aux,";");
                        q=ps.l_int;
                        if(p[q->indice].y<ps.y)
                            q=q->urm;
                        p[q->indice].parsat=true;
                        char aux2[20]="";
                        strcpy(aux2,p[q->indice].txt+2);
                        strcat(aux,aux2);
                        strcat(aux,")");
                        outtextxy(x,y,aux);
                        y+=15;
                        outtextxy(x,y,"{");
                        q=ps.l_ext;
                        lista *if1, *if2;
                        if(p[q->indice].x<ps.x && p[q->urm->indice].x<ps.x)
                        {
                            if(p[q->indice].y<p[q->urm->indice].y)
                            {
                                if1=q;
                                q=q->urm;
                                if2=q;
                            }
                            else
                            {
                                if2=q;
                                q=q->urm;
                                if1=q;
                            }
                        }
                        else if(p[q->indice].x<ps.x)
                        {
                            if1=q;
                            q=q->urm;
                            if2=q;
                        }
                        else
                        {
                            if2=q;
                            q=q->urm;
                            if1=q;
                        }
                        y+=15;
                        decodare(p[if1->indice],x+15,y,final_if);
                        y+=15;
                        outtextxy(x,y,"}");
                        if(p[if2->indice].ID!=2)
                        {
                            y+=15;
                            decodare(p[if2->indice],x,y,final_if);
                        }
                    }
                }
                else
                {
                    ps.parsat=true;
                    char aux[20]="";
                    strcpy(aux,"if(");
                    strcat(aux,ps.txt);
                    strcat(aux,")");
                    outtextxy(x,y,aux);
                    y+=15;
                    outtextxy(x,y,"{");
                    bool are_else=false;
                    q=ps.l_ext;
                    lista *if1, *if2;
                    if(p[q->indice].x<ps.x && p[q->urm->indice].x<ps.x)
                    {
                        if(p[q->indice].y<p[q->urm->indice].y)
                        {
                            if1=q;
                            q=q->urm;
                            if2=q;
                        }
                        else
                        {
                            if2=q;
                            q=q->urm;
                            if1=q;
                        }
                    }
                    else if(p[q->indice].x<ps.x)
                    {
                        if1=q;
                        q=q->urm;
                        if2=q;
                    }
                    else
                    {
                        if2=q;
                        q=q->urm;
                        if1=q;
                    }
                    if(p[if2->indice].ID!=2)
                    {
                        int nr=0;
                        lista *q2=p[if2->indice].l_int;
                        while(q2)
                        {
                            nr++;
                            q2=q2->urm;
                        }
                        if(nr==1) are_else=true;
                    }
                    y+=15;
                    decodare(p[if1->indice],x+15,y,final_if);
                    y+=15;
                    outtextxy(x,y,"}");
                    if(are_else)
                    {
                        y+=15;
                        outtextxy(x,y,"else");
                        y+=15;
                        outtextxy(x,y,"{");
                        y+=15;
                        decodare(p[if2->indice],x+15,y,final_if);
                        y+=15;
                        outtextxy(x,y,"}");
                    }
                    if(final_if>0)
                    {
                        y+=15;
                        if(!are_else) p[final_if].vizitat++;
                        decodare(p[final_if],x,y,final_if);
                    }
                }
                break;
            }
            break;
        }
        case 6:
        {
            bool este_finalif=false;
            int nr_prec=0;
            lista *prec=ps.l_int;
            while(prec)
            {
                if(p[prec->indice].y<ps.y) nr_prec++;
                prec=prec->urm;
            }
            if(nr_prec>1 && ps.vizitat<2*nr_prec-2) este_finalif=true;
            if(este_finalif)
            {
                ps.vizitat++;
                int iaux;
                for(int i=0; i<nr_piese; i++)
                    if(p[i].x==ps.x && p[i].y==ps.y)
                    {
                        iaux=i;
                        break;
                    }
                final_if=iaux;
                break;
            }
            else
            {
                lista *q=ps.l_ext;
                bool are_for=false;
                while(q!=NULL)
                {
                    if(p[q->indice].ID==5 && p[q->indice].y>ps.y)
                    {
                        int nr=0;
                        bool are_bucla=false;
                        bool are_fordupa=false;
                        lista *q2=p[q->indice].l_int;
                        while(q2!=NULL)
                        {
                            if(p[q2->indice].y>p[q->indice].y) are_bucla=true;
                            q2=q2->urm;
                        }
                        q2=p[q->indice].l_int;
                        while(q2!=NULL)
                        {
                            if(p[q2->indice].y>p[q->indice].y && p[q2->indice].txt[0]==p[q->indice].txt[0]) are_fordupa=true;
                            q2=q2->urm;
                        }
                        if(ps.txt[0]==p[q->indice].txt[0] && are_bucla && are_fordupa)
                        {
                            decodare(p[q->indice],x,y,final_if);
                            are_for=true;
                            break;
                        }
                    }
                    q=q->urm;
                }
                if(!are_for)
                {
                    ps.parsat=true;
                    char aux[20]="";
                    bool gasit=false;
                    for(int i=0; i<100; i++)
                        if(v[i].nume==ps.txt[0])
                        {
                            gasit=true;
                            break;
                        }
                    if(!gasit)
                    {
                        strcpy(aux,"int ");
                        strcat(aux,ps.txt);
                        for(int i=0; i<100; i++)
                        if(v[i].nume=='0')
                        {
                            v[i].nume=ps.txt[0];
                            break;
                        }
                    }
                    else strcpy(aux,ps.txt);
                    strcat(aux,";");
                    outtextxy(x,y,aux);
                    q=ps.l_ext;
                    int nr=0;
                    while(q)
                    {
                        nr++;
                        q=q->urm;
                    }
                    if(nr==1)
                    {
                        q=ps.l_ext;
                        if(p[q->indice].parsat==false)
                        {
                            if(p[q->indice].ID!=2) y+=15;
                            decodare(p[ps.l_ext->indice],x,y,final_if);
                        }
                    }
                    else if(nr==2)
                    {
                        q=ps.l_ext;
                        if(p[q->indice].y<ps.y)
                            q=q->urm;
                        if(p[q->indice].parsat==false)
                        {
                            if(p[q->indice].ID!=2) y+=15;
                            decodare(p[ps.l_ext->indice],x,y,final_if);
                        }
                    }
                    break;
                }
                break;
            }
            break;
        }
    }
}
void save()
{
    FILE *f;
    f=fopen("savefile.txt","w");
    for(int i=0; i<nr_piese; i++)
    {
        if(p[i].ID!=0)
        {
            char info1[100]="", info2[100]="";
            int cl, nr;
            ///i x y ID txt
            ///l_ext

            if(i==0) strcat(info1,"0 ");
            else
            {
                cl=i, nr=0;
                while(cl)
                {
                    nr++;
                    cl/=10;
                }
                char aux[nr+1]="";
                cl=i;
                for(int j=nr-1; j>=0; j--)
                {
                    aux[j]=(cl%10)+'0';
                    cl/=10;
                }
                aux[nr]=NULL;
                strcat(info1,aux);
                strcat(info1," ");
            }

            cl=p[i].x, nr=0;
            while(cl)
            {
                nr++;
                cl/=10;
            }
            char aux1[nr+1]="";
            cl=p[i].x;
            for(int j=nr-1; j>=0; j--)
            {
                aux1[j]=(cl%10)+'0';
                cl/=10;
            }
            aux1[nr]=NULL;
            strcat(info1,aux1);
            strcat(info1," ");

            cl=p[i].y, nr=0;
            while(cl)
            {
                nr++;
                cl/=10;
            }
            char aux2[nr+1]="";
            cl=p[i].y;
            for(int j=nr-1; j>=0; j--)
            {
                aux2[j]=(cl%10)+'0';
                cl/=10;
            }
            aux2[nr]=NULL;
            strcat(info1,aux2);
            strcat(info1," ");

            char aux3[2]="";
            aux3[0]=p[i].ID+'0';
            aux3[1]=NULL;
            strcat(info1,aux3);
            strcat(info1," ");

            if(p[i].txt[0]==NULL) strcat(info1,"NULL");
            else strcat(info1,p[i].txt);
            info1[strlen(info1)]=NULL;

            lista *q=p[i].l_ext;
            if(q==NULL) strcat(info2,"NULL");
            else
            {
                while(q!=NULL)
                {
                    cl=q->indice, nr=0;
                    while(cl)
                    {
                        nr++;
                        cl/=10;
                    }
                    char aux4[nr+1]="";
                    cl=q->indice;
                    for(int j=nr-1; j>=0; j--)
                    {
                        aux4[j]=(cl%10)+'0';
                        cl/=10;
                    }
                    aux4[nr]=NULL;
                    strcat(info2,aux4);
                    strcat(info2," ");
                    q=q->urm;
                }
                info2[strlen(info2)]=NULL;
            }

            char el='\n';
            fwrite(&info1,sizeof(char[100]),1,f);
            fwrite(&el,sizeof(char),1,f);
            fwrite(&info2,sizeof(char[100]),1,f);
            fwrite(&el,sizeof(char),1,f);
        }
    }
    fclose(f);
}
void load()
{
    stergere();
    FILE *f;
    f=fopen("savefile.txt","r");
    if(f!=NULL)
    {
        char info1[100]="", info2[100]="";
        int contor=0;
        while(!feof(f))
        {
            char a, aux[100]="";
            int k=0;
            do
            {
                fread(&a,sizeof(char),1,f);
                if(a!='\n') aux[k++]=a;
            }while(a!='\n');
            aux[99]=NULL;
            contor++;
            if(contor%2==1) strcpy(info1,aux);
            else
            {
                strcpy(info2,aux);
                int i=0, x=0, y=0, id=0;
                k=0;
                while(info1[k]!=' ')
                {
                    i=i*10+info1[k]-'0';
                    k++;
                }
                k++;
                while(info1[k]!=' ')
                {
                    x=x*10+info1[k]-'0';
                    k++;
                }
                k++;
                while(info1[k]!=' ')
                {
                    y=y*10+info1[k]-'0';
                    k++;
                }
                k++;
                while(info1[k]!=' ')
                {
                    id=id*10+info1[k]-'0';
                    k++;
                }
                k++;
                char txt2[100]="", txt[20]="";
                strcpy(txt2,info1+k);
                k=strlen(txt2)-1;
                while(txt2[k]==' ') k--;
                txt2[k+1]=NULL;
                strcpy(txt,txt2);

                strcpy(txt2,info2);
                k=strlen(txt2)-1;
                while(txt2[k]==' ') k--;
                txt2[k+1]=NULL;
                int fiu1=-1, fiu2=-1;
                if(txt2[0]!='N')
                {
                    if(strchr(txt2,' '))
                    {
                        fiu1=0;
                        fiu2=0;
                        k=0;
                        while(txt2[k]!=' ')
                        {
                            fiu1=fiu1*10+txt2[k]-'0';
                            k++;
                        }
                        k++;
                        while(txt2[k]!=NULL)
                        {
                            fiu2=fiu2*10+txt2[k]-'0';
                            k++;
                        }
                    }
                    else
                    {
                        fiu1=0;
                        k=0;
                        while(txt2[k]!=NULL)
                        {
                            fiu1=fiu1*10+txt2[k]-'0';
                            k++;
                        }
                    }
                }

                p[i].x=x;
                p[i].y=y;
                p[i].ID=id;
                if(txt[0]!='N') strcpy(p[i].txt,txt);
                if(i>=nr_piese) nr_piese=i+1;
                if(fiu1!=-1)
                {
                    lista *q=new lista;
                    q->indice=fiu1;
                    q->urm=NULL;
                    p[i].l_ext=q;
                    if(fiu2!=-1)
                    {
                        lista *r=new lista;
                        r->indice=fiu2;
                        r->urm=NULL;
                        p[i].l_ext->urm=r;
                    }
                }
            }
        }
        for(int i=0; i<nr_piese; i++)
            if(p[i].ID!=0)
            {
                switch(p[i].ID)
                {
                    case 1:
                    {
                        start_button(p[i].x,p[i].y,R,COLOR_PIESA,COLOR_TEXT,COLOR_CONTUR);
                        break;
                    }
                    case 2:
                    {
                        stop_button(p[i].x,p[i].y,R,COLOR_PIESA,COLOR_TEXT,COLOR_CONTUR);
                        break;
                    }
                    case 3:
                    {
                        char var[2];
                        strcpy(var,p[i].txt);
                        input_button(p[i].x,p[i].y,R,var,COLOR_PIESA,COLOR_TEXT,COLOR_CONTUR);
                        break;
                    }
                    case 4:
                    {
                        char var[2];
                        strcpy(var,p[i].txt);
                        output_button(p[i].x,p[i].y,R,var,COLOR_PIESA,COLOR_TEXT,COLOR_CONTUR);
                        break;
                    }
                    case 5:
                    {
                        char text[12];
                        strcpy(text,p[i].txt);
                        if_button(p[i].x,p[i].y,R_IF_C,text,COLOR_PIESA,COLOR_TEXT,COLOR_CONTUR);
                        break;
                    }
                    case 6:
                    {
                        char text[13];
                        strcpy(text,p[i].txt);
                        calculus_button(p[i].x,p[i].y,R_IF_C,text,COLOR_PIESA,COLOR_TEXT,COLOR_CONTUR);
                        break;
                    }
                }
                lista *q=p[i].l_ext;
                while(q!=NULL)
                {
                    linie(p[i],p[q->indice],COLOR_CONTUR,i,q->indice);
                    q=q->urm;
                }
            }
    }
    fclose(f);
}
int main()
{
    initwindow(WIDTH,HEIGHT,"InterSchem");
    desen_fundal();
    desen_meniu();
    int x, y, nrb=0;
    int x1=0, x2=0, y1=0, y2=0;
    int x1s=0, x2s=0, y1s=0, y2s=0;
    while(true)
    {
        ///selectare/deselectare buton meniu
        if(ismouseclick(WM_LBUTTONDBLCLK))
        {
            getmouseclick(WM_LBUTTONDBLCLK,x,y);
            ///cautare buton
            for(int i=1; i<=12; i++)
                if(x>bm[i].x1 && x<bm[i].x2 && y>bm[i].y1 && y<bm[i].y2)
                {
                    ///selectare
                    if(getpixel(bm[i].x1+1,bm[i].y1+1)==COLOR_BUTON)
                    {
                        nrb=i;
                        setfillstyle(SOLID_FILL,COLOR_BUTON_SELECT);
                        bar(bm[i].x1,bm[i].y1,bm[i].x2,bm[i].y2);
                        setbkcolor(COLOR_BUTON_SELECT);
                        setcolor(COLOR_TEXT);
                        if(i>7 || i==6) outtextxy((bm[i].x2-bm[i].x1)/3+bm[i].x1-10,(bm[i].y2-bm[i].y1)/3+bm[i].y1,bm[i].text);
                        else outtextxy((bm[i].x2-bm[i].x1)/3+bm[i].x1,(bm[i].y2-bm[i].y1)/3+bm[i].y1,bm[i].text);
                        ///deselectare rest
                        bool ok=false;
                        for(int j=i-1; j>0; j--)
                            if(getpixel(bm[j].x1+1,bm[j].y1+1)==COLOR_BUTON_SELECT)
                            {
                                setfillstyle(SOLID_FILL,COLOR_BUTON);
                                bar(bm[j].x1,bm[j].y1,bm[j].x2,bm[j].y2);
                                setbkcolor(COLOR_BUTON);
                                setcolor(COLOR_TEXT);
                                if(j>7 || j==6) outtextxy((bm[j].x2-bm[j].x1)/3+bm[j].x1-10,(bm[j].y2-bm[j].y1)/3+bm[j].y1,bm[j].text);
                                else outtextxy((bm[j].x2-bm[j].x1)/3+bm[j].x1,(bm[j].y2-bm[j].y1)/3+bm[j].y1,bm[j].text);
                                ok=true;
                                break;
                            }
                        for(int j=i+1; j<=12 && !ok; j++)
                            if(getpixel(bm[j].x1+1,bm[j].y1+1)==COLOR_BUTON_SELECT)
                            {
                                setfillstyle(SOLID_FILL,COLOR_BUTON);
                                bar(bm[j].x1,bm[j].y1,bm[j].x2,bm[j].y2);
                                setbkcolor(COLOR_BUTON);
                                setcolor(COLOR_TEXT);
                                if(j>7 || j==6) outtextxy((bm[j].x2-bm[j].x1)/3+bm[j].x1-10,(bm[j].y2-bm[j].y1)/3+bm[j].y1,bm[j].text);
                                else outtextxy((bm[j].x2-bm[j].x1)/3+bm[j].x1,(bm[j].y2-bm[j].y1)/3+bm[j].y1,bm[j].text);
                                break;
                            }
                        if(nrb==8)
                        {
                            stergere();
                            delay(100);
                            nrb=0;
                            setfillstyle(SOLID_FILL,COLOR_BUTON);
                            bar(bm[i].x1,bm[i].y1,bm[i].x2,bm[i].y2);
                            setbkcolor(COLOR_BUTON);
                            setcolor(COLOR_TEXT);
                            outtextxy((bm[i].x2-bm[i].x1)/3+bm[i].x1-10,(bm[i].y2-bm[i].y1)/3+bm[i].y1,bm[i].text);
                        }
                        if(nrb==9)
                        {
                            for(int i=0; i<nr_piese; i++)
                            {
                                switch(p[i].ID)
                                {
                                    case 1:
                                    {
                                        start_button(p[i].x,p[i].y,R,FUNDAL,FUNDAL,FUNDAL);
                                        start_button(p[i].x,p[i].y,R,COLOR_PIESA,COLOR_TEXT,COLOR_CONTUR);
                                        break;
                                    }
                                    case 2:
                                    {
                                        stop_button(p[i].x,p[i].y,R,FUNDAL,FUNDAL,FUNDAL);
                                        stop_button(p[i].x,p[i].y,R,COLOR_PIESA,COLOR_TEXT,COLOR_CONTUR);
                                        break;
                                    }
                                    case 3:
                                    {
                                        input_button(p[i].x,p[i].y,R,p[i].txt,FUNDAL,FUNDAL,FUNDAL);
                                        input_button(p[i].x,p[i].y,R,p[i].txt,COLOR_PIESA,COLOR_TEXT,COLOR_CONTUR);
                                        break;
                                    }
                                    case 4:
                                    {
                                        output_button(p[i].x,p[i].y,R,p[i].txt,FUNDAL,FUNDAL,FUNDAL);
                                        output_button(p[i].x,p[i].y,R,p[i].txt,COLOR_PIESA,COLOR_TEXT,COLOR_CONTUR);
                                        break;
                                    }
                                    case 5:
                                    {
                                        if_button(p[i].x,p[i].y,R_IF_C,p[i].txt,FUNDAL,FUNDAL,FUNDAL);
                                        if_button(p[i].x,p[i].y,R_IF_C,p[i].txt,COLOR_PIESA,COLOR_TEXT,COLOR_CONTUR);
                                        break;
                                    }
                                    case 6:
                                    {
                                        calculus_button(p[i].x,p[i].y,R_IF_C,p[i].txt,FUNDAL,FUNDAL,FUNDAL);
                                        calculus_button(p[i].x,p[i].y,R_IF_C,p[i].txt,COLOR_PIESA,COLOR_TEXT,COLOR_CONTUR);
                                        break;
                                    }
                                }
                            }
                            for(int i=0; i<100; i++)
                            {
                                v[i].nume='0';
                                v[i].valoare=0;
                            }
                            setfillstyle(SOLID_FILL,FUNDAL);
                            bar((WIDTH/1.7)+10,(HEIGHT/3.9)+10,WIDTH,HEIGHT);
                            int iaux;
                            for(int i=0; i<nr_piese; i++)
                                if(p[i].ID==1)
                                {
                                    iaux=i;
                                    break;
                                }
                            int xaux=(WIDTH/1.7)+20, yaux=(HEIGHT/3.9)+20, final_if=-1;
                            decodare(p[iaux],xaux,yaux,final_if);
                            delay(100);
                            nrb=0;
                            setfillstyle(SOLID_FILL,COLOR_BUTON);
                            bar(bm[i].x1,bm[i].y1,bm[i].x2,bm[i].y2);
                            setbkcolor(COLOR_BUTON);
                            setcolor(COLOR_TEXT);
                            outtextxy((bm[i].x2-bm[i].x1)/3+bm[i].x1-10,(bm[i].y2-bm[i].y1)/3+bm[i].y1,bm[i].text);
                        }
                        if(nrb==10)
                        {
                            for(int i=0; i<nr_piese; i++)
                            {
                                p[i].parsat=false;
                                switch(p[i].ID)
                                {
                                    case 1:
                                    {
                                        start_button(p[i].x,p[i].y,R,FUNDAL,FUNDAL,FUNDAL);
                                        start_button(p[i].x,p[i].y,R,COLOR_PIESA,COLOR_TEXT,COLOR_CONTUR);
                                        break;
                                    }
                                    case 2:
                                    {
                                        stop_button(p[i].x,p[i].y,R,FUNDAL,FUNDAL,FUNDAL);
                                        stop_button(p[i].x,p[i].y,R,COLOR_PIESA,COLOR_TEXT,COLOR_CONTUR);
                                        break;
                                    }
                                    case 3:
                                    {
                                        input_button(p[i].x,p[i].y,R,p[i].txt,FUNDAL,FUNDAL,FUNDAL);
                                        input_button(p[i].x,p[i].y,R,p[i].txt,COLOR_PIESA,COLOR_TEXT,COLOR_CONTUR);
                                        break;
                                    }
                                    case 4:
                                    {
                                        output_button(p[i].x,p[i].y,R,p[i].txt,FUNDAL,FUNDAL,FUNDAL);
                                        output_button(p[i].x,p[i].y,R,p[i].txt,COLOR_PIESA,COLOR_TEXT,COLOR_CONTUR);
                                        break;
                                    }
                                    case 5:
                                    {
                                        if_button(p[i].x,p[i].y,R_IF_C,p[i].txt,FUNDAL,FUNDAL,FUNDAL);
                                        if_button(p[i].x,p[i].y,R_IF_C,p[i].txt,COLOR_PIESA,COLOR_TEXT,COLOR_CONTUR);
                                        break;
                                    }
                                    case 6:
                                    {
                                        calculus_button(p[i].x,p[i].y,R_IF_C,p[i].txt,FUNDAL,FUNDAL,FUNDAL);
                                        calculus_button(p[i].x,p[i].y,R_IF_C,p[i].txt,COLOR_PIESA,COLOR_TEXT,COLOR_CONTUR);
                                        break;
                                    }
                                }
                            }
                            for(int i=0; i<100; i++)
                            {
                                v[i].nume='0';
                                v[i].valoare=0;
                            }
                            setfillstyle(SOLID_FILL,FUNDAL);
                            bar((WIDTH/1.7)+10,(HEIGHT/3.9)+10,WIDTH,HEIGHT);
                            int iaux;
                            for(int i=0; i<nr_piese; i++)
                                if(p[i].ID==1)
                                {
                                    iaux=i;
                                    break;
                                }
                            int xaux=(WIDTH/1.7)+20, yaux=(HEIGHT/3.9)+20;
                            compilare(p[iaux],xaux,yaux);
                            delay(100);
                            nrb=0;
                            setfillstyle(SOLID_FILL,COLOR_BUTON);
                            bar(bm[i].x1,bm[i].y1,bm[i].x2,bm[i].y2);
                            setbkcolor(COLOR_BUTON);
                            setcolor(COLOR_TEXT);
                            outtextxy((bm[i].x2-bm[i].x1)/3+bm[i].x1-10,(bm[i].y2-bm[i].y1)/3+bm[i].y1,bm[i].text);
                        }
                        if(nrb==11)
                        {
                            save();
                            delay(100);
                            nrb=0;
                            setfillstyle(SOLID_FILL,COLOR_BUTON);
                            bar(bm[i].x1,bm[i].y1,bm[i].x2,bm[i].y2);
                            setbkcolor(COLOR_BUTON);
                            setcolor(COLOR_TEXT);
                            outtextxy((bm[i].x2-bm[i].x1)/3+bm[i].x1-10,(bm[i].y2-bm[i].y1)/3+bm[i].y1,bm[i].text);
                        }
                        if(nrb==12)
                        {
                            load();
                            delay(100);
                            nrb=0;
                            setfillstyle(SOLID_FILL,COLOR_BUTON);
                            bar(bm[i].x1,bm[i].y1,bm[i].x2,bm[i].y2);
                            setbkcolor(COLOR_BUTON);
                            setcolor(COLOR_TEXT);
                            outtextxy((bm[i].x2-bm[i].x1)/3+bm[i].x1-10,(bm[i].y2-bm[i].y1)/3+bm[i].y1,bm[i].text);
                        }
                    }
                    ///deselectare
                    else if(getpixel(bm[i].x1+1,bm[i].y1+1)==COLOR_BUTON_SELECT)
                    {
                        nrb=0;
                        setfillstyle(SOLID_FILL,COLOR_BUTON);
                        bar(bm[i].x1,bm[i].y1,bm[i].x2,bm[i].y2);
                        setbkcolor(COLOR_BUTON);
                        setcolor(COLOR_TEXT);
                        if(i>7 || i==6) outtextxy((bm[i].x2-bm[i].x1)/3+bm[i].x1-10,(bm[i].y2-bm[i].y1)/3+bm[i].y1,bm[i].text);
                        else outtextxy((bm[i].x2-bm[i].x1)/3+bm[i].x1,(bm[i].y2-bm[i].y1)/3+bm[i].y1,bm[i].text);
                    }
                    break;
                }
        }
        ///stergere piesa sau linie
        if(ismouseclick(WM_RBUTTONDOWN))
        {
            if(nrb==7)
            {
                if(x1s==0 && y1s==0) getmouseclick(WM_RBUTTONDOWN,x1s,y1s);
                else
                {
                    getmouseclick(WM_RBUTTONDOWN,x2s,y2s);
                    if((x1s>0 && x1s<WIDTH/1.7 && y1s>(HEIGHT/10)+10 && y1s<HEIGHT) && (x2s>0 && x2s<WIDTH/1.7 && y2s>(HEIGHT/10)+10 && y2s<HEIGHT))
                    {
                        int aux1, aux2;
                        for(int i=0; i<nr_piese; i++)
                        {
                            if(p[i].ID!=0)
                            {
                                int r=R;
                                if(p[i].ID>4) r=R_IF_C;
                                if(x1s>=p[i].x-r && x1s<=p[i].x+r && y1s>=p[i].y-r && y1s<=p[i].y+r)
                                    aux1=i;
                                if(x2s>=p[i].x-r && x2s<=p[i].x+r && y2s>=p[i].y-r && y2s<=p[i].y+r)
                                    aux2=i;
                            }
                        }
                        if(aux1!=aux2) linie(p[aux1],p[aux2],FUNDAL,aux1,aux2);
                    }
                    x1s=0;
                    y1s=0;
                    x2s=0;
                    y2s=0;
                }
            }
            else
            {
                setfillstyle(SOLID_FILL,FUNDAL);
                setcolor(FUNDAL);
                getmouseclick(WM_RBUTTONDOWN,x,y);
                ///cautare coordonate piesa
                if(x>0 && x<WIDTH/1.7 && y>(HEIGHT/10)+10 && y<HEIGHT && getpixel(x,y)==COLOR_PIESA)
                {
                    int aux=0;
                    for(int i=0; i<nr_piese; i++)
                    {
                        if(p[i].ID!=0)
                        {
                            int r=R;
                            if(p[i].ID>4) r=R_IF_C;
                            if(x>=p[i].x-r && x<=p[i].x+r && y>=p[i].y-r && y<=p[i].y+r)
                            {
                                aux=p[i].ID;
                                x=p[i].x;
                                y=p[i].y;
                                p[i].ID=0;
                                p[i].x=0;
                                p[i].y=0;
                                p[i].txt[0]=NULL;
                                p[i].parsat=false;
                                p[i].vizitat=0;
                                break;
                            }
                        }
                    }
                    ///stergere
                    switch(aux)
                    {
                    case 0:
                        break;
                    case 1:
                        start_button(x,y,R,FUNDAL,FUNDAL,FUNDAL);
                        break;
                    case 2:
                        stop_button(x,y,R,FUNDAL,FUNDAL,FUNDAL);
                        break;
                    case 3:
                        input_button(x,y,R,"A",FUNDAL,FUNDAL,FUNDAL);
                        break;
                    case 4:
                        output_button(x,y,R,"A",FUNDAL,FUNDAL,FUNDAL);
                        break;
                    case 5:
                        if_button(x,y,R_IF_C,text_if_default,FUNDAL,FUNDAL,FUNDAL);
                        break;
                    case 6:
                        calculus_button(x,y,R_IF_C,text_calcul_default,FUNDAL,FUNDAL,FUNDAL);
                        break;
                    }
                }
            }
        }
        ///desen piesa sau linie
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            if(nrb==7)
            {
                if(x1==0 && y1==0) getmouseclick(WM_LBUTTONDOWN,x1,y1);
                else
                {
                    getmouseclick(WM_LBUTTONDOWN,x2,y2);
                    if((x1>0 && x1<WIDTH/1.7 && y1>(HEIGHT/10)+10 && y1<HEIGHT) && (x2>0 && x2<WIDTH/1.7 && y2>(HEIGHT/10)+10 && y2<HEIGHT))
                    {
                        int aux1, aux2;
                        for(int i=0; i<nr_piese; i++)
                        {
                            if(p[i].ID!=0)
                            {
                                int r=R;
                                if(p[i].ID>4) r=R_IF_C;
                                if(x1>=p[i].x-r && x1<=p[i].x+r && y1>=p[i].y-r && y1<=p[i].y+r)
                                    aux1=i;
                                if(x2>=p[i].x-r && x2<=p[i].x+r && y2>=p[i].y-r && y2<=p[i].y+r)
                                    aux2=i;
                            }
                        }
                        if(aux1!=aux2) linie(p[aux1],p[aux2],COLOR_CONTUR,aux1,aux2);
                    }
                    x1=0;
                    y1=0;
                    x2=0;
                    y2=0;
                }
            }
            else if(nrb<=6)
            {
                setfillstyle(SOLID_FILL,COLOR_PIESA);
                setcolor(COLOR_PIESA);
                getmouseclick(WM_LBUTTONDOWN,x,y);
                int r=R;
                if(nrb>4) r=R_IF_C;
                if(nrb!=0 && x>r && x<(WIDTH/1.7)-r && y>(HEIGHT/10)+10+r && y<HEIGHT-r)
                {
                    ///adaugare in vector
                    p[nr_piese].ID=nrb;
                    p[nr_piese].x=x;
                    p[nr_piese++].y=y;
                    ///desen
                    switch(nrb)
                    {
                    case 1:
                        start_button(x,y,R,COLOR_PIESA,COLOR_TEXT,COLOR_CONTUR);
                        break;
                    case 2:
                        stop_button(x,y,R,COLOR_PIESA,COLOR_TEXT,COLOR_CONTUR);
                        break;
                    case 3:
                        input_button(x,y,R,"A",COLOR_PIESA,COLOR_PIESA,COLOR_CONTUR);
                        break;
                    case 4:
                        output_button(x,y,R,"A",COLOR_PIESA,COLOR_PIESA,COLOR_CONTUR);
                        break;
                    case 5:
                        if_button(x,y,R_IF_C,text_if_default,COLOR_PIESA,COLOR_PIESA,COLOR_CONTUR);
                        break;
                    case 6:
                        calculus_button(x,y,R_IF_C,text_calcul_default,COLOR_PIESA,COLOR_PIESA,COLOR_CONTUR);
                        break;
                    }
                }
            }
        }
        ///scriere text in piesa
        if(ismouseclick(WM_MBUTTONDOWN))
        {
            getmouseclick(WM_MBUTTONDOWN,x,y);
            if(x>0 && x<WIDTH/1.7 && y>(HEIGHT/10)+10 && y<HEIGHT && getpixel(x,y)==COLOR_PIESA)
            {
                setfillstyle(SOLID_FILL,FUNDAL);
                bar((WIDTH/1.7)+10,(HEIGHT/3.9)+10,WIDTH,HEIGHT);
                char text[20]="", txtaux[2]="";
                int k=0, xc=(WIDTH/1.7)+20, yc=(HEIGHT/3.9)+20;
                char carct='a';
                while(carct!='\r')
                {
                    setcolor(COLOR_TEXT);
                    setbkcolor(FUNDAL);
                    carct=getch();
                    if(carct!='\r')
                    {
                        txtaux[0]=carct;
                        txtaux[1]=NULL;
                        text[k++]=carct;
                        outtextxy(xc,yc,txtaux);
                        xc+=10;
                    }
                }
                setfillstyle(SOLID_FILL,FUNDAL);
                bar((WIDTH/1.7)+10,(HEIGHT/3.9)+10,WIDTH,HEIGHT);
                int aux=0;
                for(int i=0; i<nr_piese; i++)
                {
                    if(p[i].ID!=0)
                    {
                        int r=R;
                        if(p[i].ID>4) r=R_IF_C;
                        if(x>=p[i].x-r && x<=p[i].x+r && y>=p[i].y-r && y<=p[i].y+r)
                        {
                            strcpy(p[i].txt,text);
                            aux=p[i].ID;
                            x=p[i].x;
                            y=p[i].y;
                            break;
                        }
                    }
                }
                ///scriere text
                switch(aux)
                {
                case 0:
                    break;
                case 1:
                    break;
                case 2:
                    break;
                case 3:{
                    input_button(x,y,R,"0000",COLOR_PIESA,COLOR_PIESA,COLOR_CONTUR);
                    input_button(x,y,R,text,COLOR_PIESA,COLOR_TEXT,COLOR_CONTUR);
                    break;}
                case 4:{
                    output_button(x,y,R,"0000",COLOR_PIESA,COLOR_PIESA,COLOR_CONTUR);
                    output_button(x,y,R,text,COLOR_PIESA,COLOR_TEXT,COLOR_CONTUR);
                    break;}
                case 5:{
                    if_button(x,y,R_IF_C,"a<=b && b<=c",COLOR_PIESA,COLOR_PIESA,COLOR_CONTUR);
                    if_button(x,y,R_IF_C,text,COLOR_PIESA,COLOR_TEXT,COLOR_CONTUR);
                    break;}
                case 6:{
                    calculus_button(x,y,R_IF_C,"2*a+b+c*d-a/b",COLOR_PIESA,COLOR_PIESA,COLOR_CONTUR);
                    calculus_button(x,y,R_IF_C,text,COLOR_PIESA,COLOR_TEXT,COLOR_CONTUR);
                    break;}
                }
            }
        }
    }
    getch();
    closegraph();
    return 0;
}

