#include <iostream>
#include <graphics.h>
#include <winbgim.h>
#include <stdio.h>
#include <math.h>
#include <fstream>
#include <vector>
#include <string.h>
#include <string>
#include <list>
using namespace std;

///Coordonatele diagramei
int Stanga=50;     // x
int Sus=20;        // y
int Dreapta=500;   // z
int Jos=70;        // w

int Left[100];
int Right[100];
int Down[100];
int Up[100];
int Count = 0;

int dif_down = 50;
int middle;
int pos;

vector<int> maxi;
int isif[100];
int nr_isif = -1;
int iswhile = 0;

char info_char[100];

struct node {
    string data;
    vector<node*> kids;
    node* father;
    int Jos, Dreapta, Sus, Stanga;
};
node* root;
node* tmp = new node;
///left, up, right, down
///Afisari-digrame
void Action(int x, int y, int z, int w)
{
    int difference = (z - x) / 2;
    setcolor(LIGHTGREEN);
    rectangle(x,y,z,w);
    setcolor(WHITE);
    int mid = textwidth(info_char) / 2;
    outtextxy((x+z)/2 - mid,(y+w)/2 ,info_char);
}

void printIF(int x, int y, int z, int w)
{
    int difference = (z - x) / 2;
    int mid = textwidth(info_char) / 2;
    setcolor(LIGHTBLUE);
    rectangle(x,y,z,w);
    line(x,y,(x+z)/2,w);
    line((x+z)/2,w,z,y);
    setcolor(WHITE);
    outtextxy((x+z)/2 - mid,(y+w)/2 ,info_char);
    outtextxy(x + 20, (y+w)/2, "FALSE");
    outtextxy(z - 55, (y+w)/2, "TRUE");
}

void printWHILE(int x, int y, int z, int w)
{
    int difference = (z - x) / 2;
    int mid = textwidth(info_char) / 2;
    setcolor(LIGHTMAGENTA);
    line(x,y,z,y);
    line(x,y,x,w);
    line(x+30,y+30,z,y+30);
    line(z,y,z,y+30);
    line(x+30,y+30,x+30,w);
    line(x,w,x+30,w);
    line(z,y,z,w);
    line(x,w,z,w);
    setcolor(WHITE);
}

void printDOWHILE(int x, int y, int z, int w)
{
    setcolor(YELLOW);
    line(x,y,x,w);
    line(x,y,x+30,y);
    line(x+30,y,x+30,w-30);
    line(x,w,z,w);
    line(x+30,w-30,z,w-30);
    line(z,w-30,z,w);
    line(x,y,z,y);
    line(z,y,z,w);
}

int Switch(string line)
{
    int a;
    if(line.find("daca") != std::string::npos) a = 2;
    else if(line.find("altfel") != std::string::npos) a = 3;
    else if(line.find("cat timp") != std::string::npos) a = 4;
    else if(line.find("repeta")!= std::string::npos) a = 5;
    else if(line.find("{") != std::string::npos) a = 0;
    else if(line.find("}") != std::string::npos) a = 0;
    else if(line.find("end if") != std::string::npos) a = 6;
    else if(line.find("end while") != std::string::npos) a = 7;
    else if(line.find("pana cand")!= std::string::npos) a = 8;
    else if(line.find("end code")!= std::string::npos) a = 9;
    else a = 1;
    return a;
}

void RemoveWordFromLine(std::string &line, const std::string &word)
{
  auto n = line.find(word);
  if (n != std::string::npos)
  {
    line.erase(n, word.length());
  }
}

string EditText(string text)
{
    if(text.find("daca") != std::string::npos)
    {
        RemoveWordFromLine(text, "daca");
        RemoveWordFromLine(text, "atunci");
    }

    if(text.find("cat timp") != std::string::npos)
    {
        RemoveWordFromLine(text, "cat timp");
        RemoveWordFromLine(text, "executa");
    }

    if(text.find("repeta") != std::string::npos)
    {
        RemoveWordFromLine(text, "repeta");
        RemoveWordFromLine(text, "pana cand");
    }
    if(text.find("pana cand") != std::string::npos)
    {
        RemoveWordFromLine(text, "pana cand");
    }
    return text;
}

char* StringToChar(string line)
{
    int n = line.length();
    char char_array[n + 1];

    strcpy(char_array, line.c_str());

    int i = 0;///delete all the tabs in front
    while(char_array[i] == ' ')
    {
        strcpy(char_array+i, char_array+i+1);
    }

    strcpy(info_char, char_array);
    return char_array;
}

void Utilis1(string line)
{
    cout << Left[Count] << " " << Right[Count] << " " << Up[Count] << " " << Down[Count] <<"*****" << line << endl;
    int x;
    cin >> x;
}

void Utilis2(node* nod)
{
    int pos = maxi.size();
    cout << nod->data << endl;
    for(int i = 0; i < maxi.size(); i++)
            {
                cout << "Maximul este: ";
                cout << maxi[i] << " " ;

            }
    cout << endl;
    int x; cin >> x;
}

void Display(string line, node* nod)
{
    int k = Switch(line);
    string info_str;
    info_str = EditText(nod->data);
    StringToChar(info_str);
    int width = textwidth(info_char);

    if(isif[nr_isif] == 1 && k != 3)
    {
        for(int i = 0; i < maxi.size(); i++)
            {
                maxi[i]++;
            }
    }

    switch (k)
    {
        case 1: ///action
            {
                Action(Left[Count],Up[Count],Right[Count],Down[Count]);

                nod->father->Stanga = Left[Count];
                nod->father->Dreapta = Right[Count];
                nod->father->Jos = Down[Count];
                nod->father->Sus = Up[Count];

                Count++;
                Left[Count] = Left[Count - 1]; Right[Count] = Right[Count - 1];
                Up[Count] = Up[Count - 1] + dif_down; Down[Count] = Down[Count - 1] + dif_down;
                break;
            }
        case 2: ///if
            {
                printIF(Left[Count],Up[Count],Right[Count],Down[Count]);

                nod->father->Stanga = Left[Count];
                nod->father->Dreapta = Right[Count];
                nod->father->Jos = Down[Count];
                nod->father->Sus = Up[Count];

                Count++;
                Up[Count] = Up[Count - 1] + dif_down;

                Left[Count] = Left[Count - 1]; Right[Count] = (Left[Count - 1] + Right[Count - 1]) / 2;
                Down[Count] = Down[Count - 1] + dif_down;

                nr_isif++;
                isif[nr_isif] = 1;

                maxi.push_back(0);
                break;
            }
        case 3: ///else
            {
                isif[nr_isif] = 0;

                int nr_else = nod->kids.size();
                dif_down = (50 * maxi.back())/nr_else;
                Left[Count] = (nod->father->Stanga + nod->father->Dreapta) / 2;
                Right[Count] = nod->father->Dreapta;
                Up[Count] = nod->father->Sus + 50;
                Down[Count] = nod->father->Jos + dif_down;

                break;
            }
        case 4: ///while
            {///left, up, right, down, x,y,z,w
                Left[Count] = Left[Count - 1] + 30;
                Up[Count] = Up[Count - 1] + 30 + dif_down;
                Down[Count] = Down[Count - 1] + 30 + dif_down;
                iswhile = 1;

                int mid = textwidth(info_char) / 2;
                outtextxy((Left[Count]+Right[Count])/2 - mid, Up[Count] - 17 ,info_char);

                break;
            }
        case 5: ///dowhile
            {
                Left[Count] = Left[Count - 1] + 30;
                Up[Count] = Up[Count - 1] + dif_down;
                Down[Count] = Down[Count - 1] + dif_down;
                iswhile = 1;

                int mid = textwidth(info_char) / 2;
                outtextxy((Left[Count]+Right[Count])/2 - mid, Up[Count] + 50 ,info_char);
                break;
            }
        case 6: ///end if
            {
                Left[Count] = nod->father->Stanga;
                Right[Count] = nod->father->Dreapta;

                dif_down = 50;
                Down[Count] = Up[Count] + dif_down;
                nr_isif--;

                maxi.pop_back();

                break;
            }
        case 7: ///end while
            {
                int x = nod->father->Stanga;
                int y = nod->father->Sus + dif_down;
                int z = nod->father->Dreapta;
                int w = Down[Count - 1];
                printWHILE(x,y,z,w);
                Left[Count] = nod->father->Stanga;
                break;
            }
        case 8:
            {
                int x = nod->father->Stanga;
                int y = nod->father->Sus + dif_down;
                int z = nod->father->Dreapta;
                int w = Down[Count - 1] + 30;
                printDOWHILE(x,y,z,w);
                int mid = textwidth(info_char) / 2;
                setcolor(WHITE);
                outtextxy((Left[Count]+Right[Count])/2 - mid, Up[Count] +2,info_char);
                Left[Count] = nod->father->Stanga;
                Down[Count] += 30;
                Up[Count] += 30;
                break;
            }
    }
}

///Construieste fct pentru arbore
void BuildTree(string line)
{
    if (root == NULL)
    {
        tmp->data = "{}";
        node* newNode = new node;
        newNode->data = line;
        newNode->father = tmp;
        tmp->kids.push_back(newNode);
        root = tmp;
    }
    else
    {
        if (line.find("{") != std::string::npos)
        {
            int pos = tmp->kids.size();
            tmp = tmp->kids.at(pos - 1);
        }
        else
        {
            if (line.find("}") != std::string::npos)
            {
                tmp = tmp->father;
            }
            else
            {
                    node* newNode = new node;
                    newNode->data = line;
                    newNode->father = tmp;
                    tmp->kids.push_back(newNode);
            }
        }
    }
}

void ShowPreorder(node* nod)
{
    int i;

    Display(nod->data, nod);

    if(nod == NULL)
    {
        return;
    }
    else
    {
        for(i = 0; i<nod->kids.size();i++)
        {
            ShowPreorder(nod->kids[i]);
        }
    }
}

void preordine(node* a, int nivel)
{
    int i;
    //for (i = 1; i <= 2*nivel; i++)
        // << "___";
    if (a == NULL) cout << ".\n";
    else
    {
        cout << a->data << "["<<a->kids.size()<<"]\n";
        for (i= 0; i<a->kids.size(); i++)
            preordine(a->kids[i], nivel + 1);
    }
}

int ANCHO = 720, ALTO = 720;
void print_text(int x, int y, char *n="    "){
  outtextxy(x,y,n);
  }

int print_button(int x, int y)
{
  rectangle(x,y,x+70,y+20);

  if(mousex()>x && mousex()<x+70 && mousey()>y && mousey()<y+20 && ismouseclick(WM_LBUTTONDOWN))
    {
	    clearmouseclick(WM_LBUTTONDOWN);
    	return 1;
	}
  else
    {
    	clearmouseclick(WM_LBUTTONDOWN);
  	    return 0;
    }
}


void mouse(int x, int y, int c1, int c2)
{
    if(mousex()>x && mousex()<x+70 && mousey()>y && mousey()<y+20 )
	{
    	setcolor(c1);
	}
	else
	{
		setcolor(c2);
	}
}

void CreateButon(int xtop, int ytop, int xbot, int ybot, char text[])
{
    setfillstyle(SOLID_FILL,RED);
    setcolor(WHITE);
    rectangle(xtop,ytop,xbot,ybot);
    floodfill(xtop+3,ytop+3,WHITE);
    ///settextjustify(CENTER_TEXT, CENTER_TEXT);
    setbkcolor(RED);
    outtextxy((xtop + xbot) / 2, (ytop + ybot) / 2, text);
}

void eraseButton(int xtop, int ytop, int xbot, int ybot)
{
    setcolor(WHITE);
    rectangle(xtop - 2, ytop - 2, xbot + 2, ybot + 2);
    setfillstyle(SOLID_FILL, BLACK);
    floodfill(xtop + 1, ytop + 1, BLACK);
    setcolor(BLACK);
    rectangle(xtop - 2, ytop - 2, xbot + 2, ybot + 2);
    setcolor(WHITE);
}

bool VerifyClick(int mx,int my,int xtop,int ytop, int xbot,int ybot)
{
    return (mx<=xbot && mx>=xtop && my>=ytop && my<=ybot);
}

void displayText(bool pagina)
{
    int nrlin = 0, y = 25, x = 1000;
    setbkcolor(BLACK);
    char s[250];
    ifstream indata;
    indata.open("pseudocod4.txt");
    ///settextstyle(8, 0, 2);
    ///settextjustify(LEFT_TEXT, CENTER_TEXT);
    if(pagina)
    {
        indata.getline(s, 260);
        while(!indata.eof())
        {
            nrlin++;
            if(nrlin > 43)
            {
                y += 18;
                outtextxy(x, y, s);
            }
            indata.getline(s, 260);
        }
    }
    else
    {
        indata.getline(s, 260);
        while(!indata.eof())
        {
            y += 18;
            outtextxy(x, y, s);
            indata.getline(s, 260);
        }
    }
    indata.close();
}

void Load()
{
    char s[250];
    ifstream indata; // indata is like cin
    int num; // variable for input value
    indata.open("pseudocod4.txt"); // opens the file
    if(!indata)
    { // file couldn't be opened
        cerr << "Error: file could not be opened" << endl;
        exit(1);
    }
    int x = 1000, y = 25, nrlin = 0;
    bool pag = false;
    setbkcolor(BLACK);
    while(!indata.eof())
    {
        nrlin++;
        indata.getline(s, 260);
        if(nrlin > 43)
        {
            CreateButon(900, 725, 950, 775, "V");
            pag = true;
        }
    }
    bool up = true, down = false;
    displayText(0);
    while(pag)
    {
        getmouseclick(WM_LBUTTONDOWN,x,y);
        if(VerifyClick(x,y,700,50,800,100))
        {
            pag = false;
            break;
        }
        if(VerifyClick(x, y, 900, 725, 950, 775) && up)
        {
            eraseButton(900, 725, 950, 775);
            CreateButon(900, 25, 950, 75, "^");
            up = false;
            down = true;
            setcolor(YELLOW);
            rectangle(999, 1, 1499, 799);
            setfillstyle(SOLID_FILL, BLACK);
            floodfill(1002, 2, YELLOW);
            setcolor(BLACK);
            rectangle(999, 1, 1499, 799);
            setcolor(WHITE);
            displayText(down);
        }
        else if(VerifyClick(x, y, 900, 25, 950, 75) && down)
        {
            eraseButton(900, 25, 950, 75);
            CreateButon(900, 725, 950, 775, "V");
            up = true;
            down = false;
            setcolor(YELLOW);
            rectangle(999, 1, 1499, 799);
            setfillstyle(SOLID_FILL, BLACK);
            floodfill(1002, 2, YELLOW);
            setcolor(BLACK);
            rectangle(999, 1, 1499, 799);
            setcolor(WHITE);
            displayText(down);
        }

    }
    indata.close();
}

void interfata(node *arb)
{
    int x;
    int y;
    int OK=1;
    CreateButon(700,50,800,100,"LOAD");
    CreateButon(700,250,800,300,"RUN");
    CreateButon(700,450,800,500,"EXIT");
    setbkcolor(BLACK);
    while(OK)
    {
        getmouseclick(WM_LBUTTONDOWN,x,y);
        if(VerifyClick(x,y,700,50,800,100))
        {
            Load();
        }
        if(VerifyClick(x,y,700,250,800,300))
        {
            ShowPreorder(arb);
        }
        if(VerifyClick(x,y,700,450,800,500))
        {
            exit(0);
        }
    }
}

int main()
{
    initwindow(1500,800,"Diagrama Nassi-Shneiderman");
    readimagefile("tesy1.jpg",600,0,897,800);
    ifstream file("pseudocod4.txt");

    ///Citire Pseudocod
    string line;
    while (getline(file, line))
    {
        BuildTree(line);
    }

    Left[Count] = 50;
    Right[Count] = 500;
    Up[Count] = 20;
    Down[Count] = 70;



    root->Jos = 70;
    root->Dreapta = 500;
    root->Stanga = 50;
    root->Sus = 20;

    preordine(root, 0);
    interfata(root);

    //ShowPreorder(root);

    /*while(true)
    {
	 print_text(600,40,"END");
	 ///mouse(200,42,2,15);
	 if (print_button(583,38))
	    {
	       return 0;
        }
	}*/


    getch();
    closegraph();
    return 0;
}
