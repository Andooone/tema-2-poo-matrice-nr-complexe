#include <fstream>
#include <istream>

using namespace std;
ifstream fin("test.in");
ofstream fout("test.out");
class complex
{

    float re,im;

public:

    complex();
    complex(float r,float i);
    complex(const complex &c);
    ~complex() {};
    friend istream& operator>>(istream&in,complex& c);
    friend ostream& operator<<(ostream&out,const complex &c);
    complex operator+(const complex &a);
    complex operator-(const complex &a);
    complex operator*(const complex &a);
    complex operator/(const complex &a) throw(bool);
    complex operator=(const complex &a);
    bool operator==(const complex&a);
    bool operator<(const complex&a);
    bool operator!=(const complex&a);
    float Getre();
    float Getim();
    void Set(float r,float i);
    friend class matrice;
    complex Getcomp();

};


complex::complex()
{
    re=0;
    im=0;
}

complex::complex(float r, float i)
{
    re=r;
    im=i;
}

float complex::Getre()
{
    return re;
}

float complex::Getim()
{
    return im;
}

void complex::Set(float r,float i)
{
    re=r;
    im=i;
}

complex::complex(const complex &c)
{
    re=c.re;
    im=c.im;
}

complex complex::Getcomp()
{ complex nr;
  nr.re=re;
  nr.im=im;
  return nr;
}

istream& operator>>(istream&in,complex&c)
{
    in>>c.re;
    in>>c.im;
    return in;
}

ostream& operator<<(ostream&out,const complex &c)
{
    out<<c.re<<" "<<c.im;
    return out;
}

complex complex::operator+(const complex &a)
{
    complex nr;
    nr.re=re+a.re;
    nr.im=im+a.im;
    return nr;
}

complex complex::operator-(const complex &a)
{
    complex nr;
    nr.re=re-a.re;
    nr.im=im-a.im;
    return nr;
}

complex complex::operator*(const complex &a)
{
    complex nr;
    nr.re=re*a.re-im*a.im;
    nr.im=re*a.im+im*a.re;
    return nr;
}

complex complex::operator/(const complex &a) throw (bool)
{ if(a.re==0&&a.im==0) throw 0;
    complex nr;


    nr.re=(re*a.re+im*a.im)/(a.re*a.re+a.im*a.im);
    nr.im=(a.re*im-re*a.im)/(a.re*a.re+a.im*a.im);
//(a+bi)/(c+di)=(a+bi)(c-di)/(cc+dd) = (ac+bd)/(cc+dd)+(cb-ad)i/(cc+dd)
    return nr;
}

complex complex::operator=( const complex &a)
{
    this->re=a.re;
    this->im=a.im;
    return *this;
}

bool complex::operator==(const complex&a)
{
    if(re==a.re&&im==a.im) return 1;
    return 0;
}

bool complex::operator<(const complex&a)
{
    if(re<a.re) return 1;
    else if(re==a.re&&im<a.im) return 1;
    return 0;
}

bool complex::operator!=(const complex&a)
{
    if(!(re==a.re&&im==a.im)) return 1;
    return 0;
}






class matrice
{
protected:
    complex **v;
    int lin,col;
public:
    matrice();
    matrice(int newlin, int newcol);
    matrice(const matrice& mat);
    virtual ~matrice();
    void Setelem(int i,int j,complex x);
    friend istream& operator>>(istream &in,matrice &a) {
        a.citeste(in);
        return in;
    }
    friend ostream& operator<<(ostream&out,const matrice&a){
       a.afis(out);
       return out;

    }
    virtual void citeste(istream &in) = 0;
    virtual void afis(ostream &out)const=0;
    int Getlin();
    int Getcol();
    complex** Getmat();
    virtual void Afisare()=0;
    void Set(int linn,int coll);
    virtual int Triunghiulara() {return 0;};
    virtual bool Diagonala(){return 0;};
    virtual int TRplusD() {return 0;};

};

matrice::matrice()
{
    v=NULL;
    lin=0;
    col=0;
}

    matrice::matrice( int newlin, int newcol)
{
    lin=newlin;
    col=newcol;
    complex p(0.0,0.0);
    v=new complex*[lin];
    for(int i=0; i<lin; i++)
        v[i]=new complex[col];
    for(int i=0; i<lin; i++)
        for(int j=0; j<col; j++)
            v[i][j]=p;
}

matrice::matrice(const matrice &mat)
{
    lin=mat.lin;
    col=mat.col;
    v= new complex*[lin];
    for(int i=0; i<lin; i++)
        v[i]=new complex[col];
    for(int i=0; i<lin; i++)
        for(int j=0; j<col; j++)
            v[i][j]=mat.v[i][j];
}

matrice::~matrice()
{
    for(int i=0;i<lin;i++)
     delete []v[i];
delete []v;
}

complex** matrice::Getmat()
{ return v;}

void matrice::Setelem(int i,int j,complex xx)
{
    v[i][j]=xx;
}

int matrice::Getlin()
{   return lin;    }

int matrice::Getcol()
{   return col;    }

void matrice::Set(int linn,int coll)
{ this->lin=linn;
  this->col=coll;
}

void matrice::Afisare()
{ for(int i=0;i<lin;i++)
   {for(int j=0;j<col;j++)
    fout<<v[i][j]<<" ";
    fout<<"\n";
   }
}
/*
istream& matrice::operator>>(istream &in,matrice &a)
{

}
*/
class matrice_oarecare: public matrice
{
public:
    matrice_oarecare() : matrice() {};
    matrice_oarecare(int newlin, int newcol) : matrice(newlin,newcol) {};
    matrice_oarecare(const matrice_oarecare &mat) : matrice(mat) {};
    virtual ~matrice_oarecare() {};
    bool operator==(const matrice_oarecare &) const;
    bool operator!=(const matrice_oarecare &a) const;
    void citeste(istream&in);
    void afis(ostream &out)const;
    matrice_oarecare operator=(const matrice_oarecare &a) ;
    matrice_oarecare operator+( matrice_oarecare &a);
    matrice_oarecare operator-( matrice_oarecare &a);
    matrice_oarecare operator*( matrice_oarecare &a);
    void Afisare();
    matrice_oarecare Transpusa();
};
void matrice_oarecare::citeste(istream &in)
{
  for(int i=0;i<this->lin;i++)
    delete[]this->v[i];
    delete []this->v;
    this->v==NULL;

    int x,y;
    in>>x;
    in>>y;
    this->lin=x;
    this->col=y;
    complex p;
     this->v=new complex*[this->lin];
    for(int i=0; i<this->lin; i++)
        this->v[i]=new complex[this->col];
    for(int i=0; i<this->lin; i++)
        for(int j=0; j<this->col; j++)
        {
            fin>>p;
            this->v[i][j]=p;
        }
}

void matrice_oarecare::afis(ostream& out) const

{
    out<<this->lin<<" "<<this->col<<"\n";
    for(int i=0; i<this->lin; i++)
    {
        for(int j=0; j<this->col; j++)
            out<<this->v[i][j]<<" ";
        out<<"\n";
    }
}


bool matrice_oarecare::operator==(const matrice_oarecare &a) const
{
    if(!(lin==a.lin&&col==a.col)) return 0;
    for(int i=0; i<lin; i++)
        for(int j=0; j<col; j++)
            if(v[i][j]!=a.v[i][j]) return 0;
    return 1;
}

bool matrice_oarecare::operator!=(const matrice_oarecare &a) const
{
    if(!(lin==a.lin&&col==a.col)) return 1;
    for(int i=0; i<lin; i++)
        for(int j=0; j<col; j++)
            if(v[i][j]!=a.v[i][j]) return 1;
    return 0;
}

matrice_oarecare matrice_oarecare::operator+( matrice_oarecare &a)
{
    if(lin==a.Getlin()&&col==a.Getcol())
    {
        matrice_oarecare x(lin,col);
        for(int i=0; i<lin; i++)
            for(int j=0; j<col; j++)
            {
            //    x.Setelem(i,j,v[i][j].Getre()+(a.v[i][j]).Getre(),v[i][j].Getim()+(a.v[i][j]).Getim());
            x.Setelem(i,j,v[i][j]+a.v[i][j]);
            }
        return x;
    }
}

matrice_oarecare matrice_oarecare::operator-( matrice_oarecare &a)
{
    if(lin==a.Getlin()&&col==a.Getcol())
    {
        matrice_oarecare x(lin,col);
        for(int i=0; i<lin; i++)
            for(int j=0; j<col; j++)
              //  x.Setelem(i,j,v[i][j].Getre()-a.v[i][j].Getre(),v[i][j].Getim()-a.v[i][j].Getim());
               x.Setelem(i,j,v[i][j]-a.v[i][j]);
        return x;
    }
}

matrice_oarecare matrice_oarecare::operator*( matrice_oarecare &a)
{
    if(col==a.lin)
    {
        matrice_oarecare x(lin,a.col);
        for(int i=0; i<x.Getlin(); i++)
            for(int j=0; j<x.Getcol(); j++)
                {for(int k=0; k<col; k++)
                    //x.Setelem(i,j,v[i][j].Getre()+(v[i][k]*a.v[k][j]).Getre(),v[i][j].Getim()+(v[i][k]*a.v[k][j]).Getim());
                  x.Setelem(i,j,x.v[i][j].Getcomp()+v[i][k]*a.v[k][j]);}
 //                cout<<x.v[i][j].Getre()<< " "  <<  x.v[i][j].Getim()<<" ";
        return x;
    }
}


matrice_oarecare matrice_oarecare::operator=(const matrice_oarecare &a)
{
    for(int i=0;i<lin;i++)
    delete[]v[i];
     delete[]v;
     v=NULL;

   this->lin=a.lin;
    this->col=a.col;

    v=new complex*[lin];
    for(int i=0; i<lin; i++)
        v[i]=new complex[col];

    for(int i=0; i<lin; i++)
        for(int j=0; j<col; j++)
        v[i][j]=a.v[i][j];

        return *this;
}

matrice_oarecare matrice_oarecare::Transpusa()
{ matrice_oarecare x(col,lin);
  for(int i=0;i<lin;i++)
    for(int j=0;j<col;j++)
    x.Setelem(j,i,v[i][j]);
  return x;
}

void matrice_oarecare::Afisare()
{  for(int i=0;i<lin;i++)
   {for(int j=0;j<col;j++)
    fout<<v[i][j]<<" ";
    fout<<"\n";
   }
}



class matrice_patratica:public matrice
{
  public:
  matrice_patratica(): matrice(){};
  matrice_patratica(int dim) :matrice(dim,dim){};
  matrice_patratica(const matrice_patratica &mat) :matrice(mat) {};
  ~matrice_patratica(){};
  void citeste(istream& in);
  void afis(ostream &out)const;
  matrice_patratica operator+(matrice_patratica &a);
  matrice_patratica operator*(matrice_patratica &a);
  matrice_patratica operator=(const matrice_patratica &a);
  matrice_patratica Submatrice(int linn,int coll);
  void Afisare();
  complex CalculDet();
  bool Diagonala();
  int Triunghiulara();
  int TRplusD(){if((*this).Diagonala()+(*this).Triunghiulara()==2) return 1;return 0;}
  matrice_patratica Transpusa();
  matrice_patratica Inversa();
};


void matrice_patratica::citeste(istream& in)
{
  for(int i=0;i<this->lin;i++)
    delete[]this->v[i];
    delete []this->v;
    this->v==NULL;

    int x;
    in>>x;
    this->lin=x;
    this->col=x;
    complex p;
     this->v=new complex*[this->lin];
    for(int i=0; i<this->lin; i++)
        this->v[i]=new complex[this->col];
    for(int i=0; i<this->lin; i++)
        for(int j=0; j<this->col; j++)
        {
            fin>>p;
            this->v[i][j]=p;
        }
}

void matrice_patratica::afis(ostream& out)const
{
    out<<this->lin<<"\n";
    for(int i=0; i<this->lin; i++)
    {
        for(int j=0; j<this->col; j++)
            out<<this->v[i][j]<<" ";
        out<<"\n";
    }

}


matrice_patratica matrice_patratica::operator+( matrice_patratica &a)
{
    if(lin==a.Getlin()&&col==a.Getcol())
    {
        matrice_patratica x(lin);
        for(int i=0; i<lin; i++)
            for(int j=0; j<col; j++)
            {
            x.Setelem(i,j,v[i][j]+a.v[i][j]);
            }
        return x;
    }
}

matrice_patratica matrice_patratica::operator*( matrice_patratica &a)
{
    if(col==a.lin)
    {
        matrice_patratica x(lin);
        for(int i=0; i<x.Getlin(); i++)
            for(int j=0; j<x.Getcol(); j++)
                {for(int k=0; k<col; k++)
                  x.Setelem(i,j,x.v[i][j].Getcomp()+v[i][k]*a.v[k][j]);
                }
        return x;
    }
}

void matrice_patratica::Afisare()
{  for(int i=0;i<lin;i++)
   {for(int j=0;j<lin;j++)
    fout<<v[i][j]<<" ";
    fout<<"\n";
   }
   fout<<"DET="<<(*this).CalculDet();
}

matrice_patratica matrice_patratica::Submatrice(int linn,int coll)
{
    matrice_patratica x(lin-1);
  for(int i=0;i<lin;i++)
     for(int j=0;j<col;j++)
        { complex p;
         // p.Set(v[i][j].Getre(),v[i][j].Getim());
         p=v[i][j];
            if(i<linn&&j<coll) x.Setelem(i,j,p);
    else if(i<linn&&j>coll) x.Setelem(i,j-1,p);
    else if(i>linn&&j<coll) x.Setelem(i-1,j,p);
    else if(i>linn&&j>coll) x.Setelem(i-1,j-1,p);
        int a=0;
        }
return x;
}

complex matrice_patratica::CalculDet()
{  if(lin==1) return v[0][0];
   complex s(0,0);
   for(int i=0;i<col;i++)
   { complex sign;
     if(i%2==0) sign.Set(1,0);
     else sign.Set(-1,0);
       s=s+sign*v[0][i]*(*this).Submatrice(0,i).CalculDet();

   }
   return s;
}

matrice_patratica matrice_patratica::operator=(const matrice_patratica &a)
{
    for(int i=0;i<lin;i++)
    delete[]v[i];
    delete[]v;
     v=NULL;

   this->lin=a.lin;
    this->col=a.col;

    v=new complex*[lin];
    for(int i=0; i<lin; i++)
        v[i]=new complex[col];

    for(int i=0; i<lin; i++)
        for(int j=0; j<col; j++)
        v[i][j]=a.v[i][j];

        return *this;
}

bool matrice_patratica::Diagonala()
{   complex p(0,0);
    for(int i=0;i<lin;i++)
     for(int j=0;j<col;j++)
      if(i!=j)
         if(v[i][j]!=p) return 0;
    return 1;
}

int matrice_patratica::Triunghiulara()
{ bool trsup=1,trinf=1;
   complex p(0,0);
    for(int i=0;i<lin;i++)
    for(int j=0;j<lin;j++)
        if(i<j)
          if(v[i][j]!=p) trsup=0;

   for(int i=0;i<lin;i++)
    for(int j=0;j<lin;j++)
        if(j>i)
          if(v[i][j]!=p) trinf=0;
 return (trsup||trinf);
}

matrice_patratica matrice_patratica::Transpusa()
{ matrice_patratica x(col);
  //cout<<x;
  for(int i=0;i<lin;i++)
    for(int j=0;j<col;j++)
    x.Setelem(j,i,v[i][j]);
  return x;
}

matrice_patratica matrice_patratica::Inversa()
{
    matrice_patratica x(lin);
//cout<<(*this).Transpusa();
  for(int i=0;i<lin;i++)
    for(int j=0;j<col;j++)
  { complex sign;
    if((i+j)%2==0) sign.Set(1,0);
    else sign.Set(-1,0);
      x.Setelem(i,j,sign*(*this).Transpusa().Submatrice(i,j).CalculDet());
      x.Setelem(i,j,x.v[i][j].Getcomp()/(*this).CalculDet());
  }
  return x;
}

int main()
{ matrice*p=new matrice_patratica ;

    matrice_patratica a(2);
    matrice_patratica b(5);

   // fin>>*(dynamic_cast<matrice_patratica*>(p));
     fin>>(*p);
   // fin>>b;
    //fout<<a;

    //fout<<b;
    //fout<<b;

//      a.Afisare();
/*try
{ complex p(0,0);
  if(a.CalculDet()==p) throw 12;
  cout<<a.Triunghiulara();

} catch(int x) {cout<<"Matricea A are determinantul 0";}
*/
fout<<(*p);

    return 0;
}
