#include <iostream>
#include <string>
using namespace std;

const string basic  ="ABCDEFGHIJKLMNOPQRSTUVWXYZ_.";
const string code[]={"EKMFL.GDQVZNTOW_YHXUSPAIBRCJ",
                     "AJ_DKSIRUXBLHWTMCQG.ZNPYFVOE",
                     "BDFHJLCPRTXV.ZNYEIWGAKMU_SQO",
                     "ESOVP_ZJAYQUIRHX.LNFTGKDCMWB",
                     "VZBRGITY.UPSDNHLXAWMJQ_OFECK",
                     "J.PGVOUMFYQBENHZRDKASXLICTW_",
                     "NZJHGR.CXMYSW_BOUFAIVLPEKQDT",
                     "FKQHTLXOCB.JSPDZRAM_EWNIUYGV"};
const string rewA   ="ARBDCOEJFNGTHKIVLM_P.WQZSXUY";
const string moves[]  ={"R","F","W","K","A","AN","AN","AN"};
string key[3];
string push[3];

void CAPS(string &txt)
{
    const string low="abcdefghijklmnopqrstuvwxyz ";
    for(int i=0;i<txt.length();i++)
        if(low.find(txt[i],0)!=-1)
            txt[i]=basic[low.find(txt[i],0)];
}

void input(string &INtxt,int pos[],string &LK)
{
    cout<<"Witaj w AEnigmie"<<endl<<"Wpisz tekst wejsciowy"<<endl<<endl<<"||  ";
     string temp;
     cin>>temp;
     std::getline (std::cin,INtxt);
     temp+=INtxt;
     INtxt=temp;
     CAPS(INtxt);
    cout<<endl<<"Podaj pozycje startowe rotorow: (0-28)"<<endl;
    for(int i=0;i<4;i++)
        {
            cout<<i<<": ";
            cin>>pos[i];
        }
    cout<<endl<<endl<<"Podaj polaczenia Lacznicy kablowej: (0 - aby zakonczyc)"<<endl;
    string Lin;
    while(Lin!="0")
    {
        LK+=Lin;
        Lin="";
        cin>>Lin;
    }
    CAPS(LK);
    cout<<endl<<endl<<"Podaj kolejnosc walcow kodujacych (3 walce od 1 do 8) np. 318:"<<endl;
    string Pin;
    cin>>Pin;
    for(int i=0;i<3;i++)
    {
        key[i]=code[(Pin[i]-'0')-1];
        push[i]=moves[Pin[i]-'0'-1];
    }
}

void connector(string &txt, string LK)
{
    for(int i=0;i<txt.length();i++)
    {
        bool t2=0;
        for(int j=0;j<LK.length();j++)
        {
            if(txt[i]==LK[j] && t2==0)
            {
            if(j%2==1)
            {
                txt[i]=LK[j-1];
                t2=1;
            }
            else
                {
                txt[i]=LK[j+1];
                t2=1;
                }
            }
        }
    }
}

void rotation(int pos[])
{
    pos[0]++;
    for(int i=0;i<push[0].length();i++)
    if(pos[0]==key[0].find(push[0]))
    {
        pos[1]++;
        for(int i=0;i<push[1].length();i++)
        if(pos[1]==key[1].find(push[1]))
        {
            pos[2]++;
            for(int i=0;i<push[2].length();i++)
            if(pos[2]==key[2].find(push[2]))
            {
                pos[3]++;
            }
        }
    }

    for(int i=0;i<4;i++)
        if(pos[i]>basic.length()) pos[i]-=basic.length();

}

void rotor1(int &POS,int pos[],int num)
{
    POS-=pos[num];
    if(POS<0) POS+=basic.length();
    POS=basic.find(key[num][POS],0);
    POS+=pos[num];
    if(POS>=basic.length()) POS-=basic.length();
}

void rotor2(int &POS,int pos[],int num)
{
    POS-=pos[num];
    if(POS<0) POS+=basic.length();
    POS=key[num].find(basic[POS],0);
    POS+=pos[num];
    if(POS>=basic.length()) POS-=basic.length();
}

void rotorR(int &POS,int pos[])
{
    POS-=pos[3];
    if(POS<0) POS+=basic.length();
    int Rp=rewA.find(basic[POS],0);
    if(Rp%2==0) Rp++;
       else     Rp--;
    POS=basic.find(rewA[Rp]);
    POS+=pos[3];
    if(POS>=basic.length()) POS-=basic.length();
}

void decode(char &a,int pos[])
{
    int POS=basic.find(a,0);
    rotation(pos);
    rotor1(POS,pos,0);
    rotor1(POS,pos,1);
    rotor1(POS,pos,2);
    rotorR(POS,pos);
    rotor2(POS,pos,2);
    rotor2(POS,pos,1);
    rotor2(POS,pos,0);
    a=basic[POS];
}

void output(string &txt)
{
    cout<<endl<<"Tekst wynikowy to: "<<endl<<endl;
    for(int i=0;i<txt.length()+4;i++) cout<<"-";
    cout<<endl<<"| "<<txt<<" |"<<endl;
    for(int i=0;i<txt.length()+4;i++) cout<<"-"<<endl;
    cin>>txt;
}
int main()
{
int pos[4];
string LK;
string txt;

input(txt,pos,LK);
connector(txt,LK);
for(int i=0;i<txt.length();i++)
    decode(txt[i],pos);
connector(txt,LK);
output(txt);
}
