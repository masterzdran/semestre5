#ifndef IOSTREAM_H
#define IOSTREAM_H

#include <string.h>

class ios;
class streambuf;
class istream;
class ostream;
class iostream;
class istream_withassign;
class ostream_withassign;
class iostream_withassign;

union ios_user_union {
    long lword;
    void *pword;
};

typedef long    streampos;
typedef long    streamoff;

#define EOF (-1)

//=============================================================================
//
//                                  IOS
//
class ios {

    //-------------------------------------------------------------------------
    //  Para que o utilizador possa adicionar mais flags e words
    static  long              nextbit;
    static  int               usercount;    // words usadas
    union   ios_user_union  * userwords;
            int               nwords;       // words alocadas 
            void              usersize(int);// realocar

    // estas declaracoes servem para prevenir a copia de ios
             ios(ios  &);                // declarado mas nao definido
    void     operator = (ios  &);        // declarado mas nao definido

protected:
    //-------------------------------------------------------------------------
    //  streambuf associado a este stream
    streambuf  * bp;

    //-------------------------------------------------------------------------
    //  stream de eco
    ostream  * x_tie;

    //-------------------------------------------------------------------------
    //  Estado do stream
    int     state;          // status bits

    //-------------------------------------------------------------------------
    //  Vari�veis de formata��o
    long    x_flags;        // flags
    int     x_precision;    // precis�o dos reais
    int     x_width;        // largura do campo de sa�da
    int     x_fill;         // caracer de preenchimento do campo

    //-------------------------------------------------------------------------
    //  Construtor privado - sem buffer
            ios() { userwords = 0; }

    void    init(streambuf  *);    // Inicializa��o

    static void  (* stdioflush)();

    void    setstate(int);         // Inicializar 'state'

public:
    
    //-------------------------------------------------------------------------
    // Estado do stream
    
    enum io_state   {
        goodbit     = 0x00,     // a proxima opera��o pode ter exito
        eofbit      = 0x01,     // no fim do stream
        failbit     = 0x02,     // a �ltima opera��o falhou
        badbit      = 0x04,     // erro na execu��o da opera��o, perda de integridade
        hardfail    = 0x80      // erro irrecuperavel
    };

    int      rdstate()  { return state; }
    int      eof()      { return state & eofbit; }
    int      fail()     { return state & (failbit | badbit | hardfail); }
    int      bad()      { return state & (badbit | hardfail); }
    int      good()     { return state == 0; }
    void     clear(int = 0);
             operator void  * ()  { return fail() ? 0 : this; }
    int      operator! ()         { return fail(); }
    
    //-------------------------------------------------------------------------
    // Modo de opera��o do ficheiro
    enum open_mode  {
        in          = 0x01,     // abrir para leitura
        out         = 0x02,     // abrir para escrita
        ate         = 0x04,     // posicionar-se no fim depois de aberto
        app         = 0x08,     // inser��o no fim
        trunc       = 0x10,     // eliminar o ficheiro se existir
        nocreate    = 0x20,     // n�o criar o ficheiro se falhar a abertura
        noreplace   = 0x40,     // falha a abertura se o ficheiro j� existir
        binary      = 0x80      // ficheiro em modo bin�rio
    };

    //-------------------------------------------------------------------------
    // Flags de formata��o
    enum {
        skipws      = 0x0001,   // salta brancos

        left        = 0x0002,   // ajuste � esquerda
        right       = 0x0004,   // ajuste � direita
        internal    = 0x0008,   // preenchimento de campo entre o sinal e o valor

        dec         = 0x0010,   // convers�o decimal
        oct         = 0x0020,   // convers�o octal
        hex         = 0x0040,   // convers�o hexadecimal
        showbase    = 0x0080,   // indica��o de base na sa�da
        showpoint   = 0x0100,   // ponto decimal nos reais
        uppercase   = 0x0200,   // hexadecimal em mai�sculas
        showpos     = 0x0400,   // sinal de '+' nos inteiros positivos

        scientific  = 0x0800,   // nota��o cient�fica nos reais : 1.2345E2
        fixed       = 0x1000,   // nota��o decimal nos reais : 123.45

        unitbuf     = 0x2000,   // actualiza o dispositivo de sa�da ap�s cada inser��o
        stdio       = 0x4000    // actualiza stdout ou stderr ap�s cada inser��o
    };

    // campos afins - segundo par�metro de setf()
    static  const long basefield;   // dec | oct | hex
    static  const long adjustfield; // left | right | internal
    static  const long floatfield;  // scientific | fixed

    // Fun��es gerais para manipula��o das flags de formata��o
    long     flags() { return x_flags; }
    long     flags(long);
    long     setf(long _setbits, long _field);
    long     setf(long);
    long     unsetf(long);

    // Manipula��o da vari�vel de formata��o 'width'
    int      width()       { return x_width; }
    int      width(int _w) { int _i = x_width; x_width = _w; return _i; }

    // Manipula��o da vari�vel de formata��o 'fill'
    char     fill()        { return x_fill; }
    char     fill(char _c) { char _x = x_fill; x_fill = _c; return _x; }

    // Manipula��o da vari�vel de formata��o 'precision'
    int      precision(int _p){ int _x = x_precision; x_precision = _p; return _x; }
    int      precision()      { return x_precision; }

    //-------------------------------------------------------------------------
    // Flags de direc��o
    enum seek_dir { beg = 0, cur = 1, end = 2 };

    //-------------------------------------------------------------------------
    //  Construtor p�blico
              ios(streambuf  * sb) { userwords = 0; init(sb); }

    //-------------------------------------------------------------------------
    //  Destrutor
    virtual  ~ios() { if (userwords) delete userwords; }

    //-------------------------------------------------------------------------
    //  Devolve o buffer associado a este stream
    streambuf  *  rdbuf() { return bp; }

    //-------------------------------------------------------------------------
    //  Para que o utilizador possa adicionar mais flags e words
    static long  bitalloc();    // reserva novo bit, retorna o valor
    static int   xalloc();      // reserva nova word, retorna o indice
    long       & iword(int);    // retorna uma word de utilizador
    void     * & pword(int);    // retorna o pointer para uma word de utilizador

    //-------------------------------------------------------------------------
    //  Manipula��o do stream de eco
    ostream  *  tie(ostream  *);
    ostream  *  tie()  { return x_tie; }

    static void  sync_with_stdio();

};

//=============================================================================
//
//                                  STREAMBUF
//
class streambuf {

    short   alloc_; // diferente de zero se o buffer poder ser eliminado
    short   unbuf_; // diferente de zero se nao tiver buffer
    char  * base_;  // inicio do buffer
    char  * ebuf_;  // fim do buffer + 1
    char  * pbase_; // inicio da area de put
    char  * pptr_;  // ponteiro de put
    char  * epptr_; // fim da area de put + 1
    char  * eback_; // base da seccao de putback na area de get
    char  * gptr_;  // ponteiro de get
    char  * egptr_; // fim da area de get + 1

    // estas declaracoes servem para prevenir a copia de streambuf
            streambuf (streambuf  &);    // declarado mas nao definido
    void    operator= (streambuf  &);    // declarado mas nao definido

protected:
    char  * base() { return base_;  }
    char  * ebuf() { return ebuf_;  }
    int     blen() { return (int)(ebuf_ - base_); }  // returna a dimensao do buffer
    char  * pbase(){ return pbase_; }
    char  * pptr() { return pptr_;  }
    char  * epptr(){ return epptr_; }
    char  * eback(){ return eback_; }
    char  * gptr() { return gptr_;  }
    char  * egptr(){ return egptr_; }

    void    setp(char  *, char  *);             // definir os ponteiros de area de put
    void    setg(char  *, char  *, char  *);    // definir os ponteiros da area de get
    void    pbump(int _n) { pptr_ += _n; }      // avancar o ponteiro de put
    void    gbump(int _n) { gptr_ += _n; }      // avancar o ponteiro de get
    void    setb(char  *, char  *, int = 0 );   // definir nova area de buffer

    void    unbuffered(int _unb) { unbuf_ = (_unb != 0); }   // set the buffering state
    int     unbuffered()         { return unbuf_; }          // non-zero if not buffered

    //  Alocar o buffer
    int   allocate() { return (base_ || unbuf_) ? 0 : doallocate(); }  

    //  Implementa��o virtual da fun��o de aloca��o do buffer
    virtual int  doallocate();

public:
             streambuf();              // Construtor sem buffer
             streambuf(char *, int);   // Construtor com buffer
    virtual ~streambuf();              // Destrutor

    // usar como buffer o array de caracteres fornecido pelo utilizador
    virtual streambuf  *  setbuf (  signed char  *, int);
            streambuf  *  setbuf (unsigned char  * _p, int _len)
                { return setbuf((signed char  *)_p, _len); }

    //=========================================================================
    // Extraccao de caracteres
    
    // Devolve o proximo caracter sem avancar o ponteiro
    
    int sgetc();
 
    // Avanca o ponteiro e devolve o proximo caracter
    
    int snextc();

    // Devolve o proximo caracter e avanca o ponteiro
    
    int sbumpc();

    // Avanca o ponteiro para o proximo caracter
    
    void stossc();
    // { if ( gptr_ >= egptr_ ) underflow(); else ++gptr_; }
        
    // Devolve os proximos n caracteres
    
    int sgetn(char  * _s, int _n);
    
    // Implementa��o de sgetn, por raz�es de eficiencia
    
    virtual int  do_sgetn(char  *, int);
    
    //  Preencher um buffer vazio a partir do disposistivo de entrada

    virtual int  underflow();

    //  Devolver um caracter para o buffer de get
    
    int   sputbackc(char _c);
    //    { return (gptr_ > eback_) ? (unsigned char)(*--gptr_ = _c) : pbackfail(_c); }

    //  A chamar quando 'sputbackc' falha
    
    virtual int  pbackfail(int);

    //  Devolve o n�mero de caracteres dispon�veis na area de get
    int in_avail();
    // { return (egptr_ > gptr_) ? (int)(egptr_ - gptr_) : 0; }

    //=========================================================================
    // Inser��o de caracteres

    //  Colocar um caracter na area de put
    int   sputc(int _c);
    //  { return (pptr_ >= epptr_) ? overflow((unsigned char)_c) : (unsigned char)(*pptr_++ = _c); }    

    //  Colocar 'n' caracteres na �rea de put
    
    int sputn(const char  * _s, int _n);
    
    //  Implementa��o de 'sputn', por raz�es de efici�ncia 
    
    virtual int  do_sputn(const char  * s, int n);

    //  Transfere os caracteres presentes na area de put para o dispositivo de sa�da
    virtual int  overflow(int = EOF);

    //  Devolve o n�mero de caracteres presentes na area de put
    int   out_waiting();
    //  { return pptr_ ? (int)(pptr_ - pbase_) : 0; }

    //=========================================================================
    // Posicionamento no stream
    virtual streampos  seekoff
        (streamoff, ios::seek_dir, int = (ios::in | ios::out));

    virtual streampos  seekpos
        (streampos, int = (ios::in | ios::out));
        
    //  Para syncronizar o dispositivo de entrada e/ou sa�da com o buffer
    virtual int  sync();

    //  Para debbuging
    void     debug();

};

//=============================================================================
//  
//                              ISTREAM
//
class istream : virtual public ios {

    // N�mero de caracteres extraidos na �ltima opera��o n�o formatada
    int         gcount_;
    
    // Implementa��o da extra��o de um caracter
    signed char do_get();

protected:
    void     eatwhite();  // Salta brancos
             istream()    { gcount_ = 0; }
public:
              istream(streambuf  * s) { ios::init(s); gcount_ = 0; }
    virtual  ~istream() {}

    int   ipfx(int = 0);                    // Fun��o prefixa para input
    int   ipfx0()     { return ipfx(0); }   // Para extrac��es formatadas
    int   ipfx1()     { return ipfx(1); }   // Para extrac��es n�o formatadas
    void  isfx()      { }                   // Fun��o sufixa para input

    istream  &  seekg(streampos);                // Definir posi��o corrente
    istream  &  seekg(streamoff, ios::seek_dir); // Definir posi��o corrente
    streampos   tellg();                         // Ler posic�o corrente

    int  sync()   { return bp->sync(); }

    //-------------------------------------------------------------------------
    // Opera��es n�o formatadas

    // Extrair caracteres do stream para um array
    istream  &  read(  signed char  *, int);
    istream  &  read(unsigned char  * _p, int _l)
                    { return read((signed char  *)_p, _l); }

    // n�o consome terminador
    istream  &  get(  signed char  *, int, char = '\n');
    istream  &  get(unsigned char  * _p, int _l, char _t = '\n')
                    { return get((signed char  *)_p, _l, _t); }

    // consome terminador
    istream  &  getline(  signed char  *, int, char = '\n');        
    istream  &  getline(unsigned char  *_p, int _l, char _t = '\n')
                    { return getline((signed char  *) _p, _l, _t); }

    // Extrair caracteres do stream para um streambuf
    istream  &  get(streambuf  &, char = '\n');

    // Extrair um character
    istream  &  get(unsigned char  & _c);
    istream  &  get(signed char  & _c);
    int         get();

    // Devolve o proximo caracter sem extrair
    int    peek()     { return ipfx1() ? bp->sgetc() : EOF; }

    // Devolve o numero de caracteres n�o formatados extraidos na �ltima opera��o
    int    gcount()   { return gcount_; }

    // Devolve um caracter para o stream
    istream  &  putback(char);

    // Extrai e descarta 'n' caracteres ou at� encontrar um terminador
    istream  &  ignore (int = 1, int = EOF);

    //-------------------------------------------------------------------------
    //  Operac��es de extra��o formatada
    
    istream  &  operator>> (  signed char  *);
    istream  &  operator>> (unsigned char  * _p) {
        return *this >> (signed char  *)_p;
    }
    istream  &  operator>> (char  * _p) {
        return *this >> (signed char  *)_p;
    }

    istream  &  operator>> (unsigned char  & _c) {
        if( ipfx0() )
            _c = bp->in_avail() ? bp->sbumpc() : do_get();
        return *this;
    }

    istream  &  operator>> (  signed char  & _c) {
        if( ipfx0() )
            _c = bp->in_avail() ? bp->sbumpc() : do_get();
        return *this;
    }

    istream  &  operator>> ( char  & _c) {
        if( ipfx0() )
            _c = bp->in_avail() ? bp->sbumpc() : do_get();
        return *this;
    }
    istream  &  operator>> (short  &);
    istream  &  operator>> (int  &);
    istream  &  operator>> (long  &);
    istream  &  operator>> (unsigned short  &);
    istream  &  operator>> (unsigned int  &);
    istream  &  operator>> (unsigned long  &);
    istream  &  operator>> (float  &);
    istream  &  operator>> (double  &);
    istream  &  operator>> (long double  &);

    // Extrair deste stream e inserir num streambuf
    istream  &  operator>> (streambuf  *);

    //-------------------------------------------------------------------------
    //   Execu��o de manipuladores
    istream  &  operator>> (istream  & ( *_f)(istream  &))
        { return (*_f)(*this); }

    istream  &  operator>> (ios  & ( *_f)(ios  &) ) { 
        (*_f)(*((ios*)this));
        return *this;   
    }
};

//=============================================================================
//  
//                              OSTREAM
//

class ostream : virtual public ios {

    void     outstr(const char  *, const char  *);

protected:
    int      do_opfx();   // Fun��o prefixa para output
    void     do_osfx();   // Fun��o sufixa para output
             ostream()    {}
public:
              ostream(streambuf  * s) { ios::init(s); }
    virtual  ~ostream()               { flush(); }

               int  opfx() { return do_opfx(); }
              void  osfx() { if (x_flags & (stdio | unitbuf)) do_osfx(); }
    ostream  &  flush();

    // set/read the put pointer's position
    ostream  &  seekp(streampos);                   // Definir posi��o corrente
    ostream  &  seekp(streamoff, ios::seek_dir);    // Definir posi��o corrente 
    streampos   tellp();                            // Ler posi��o corrente

    //-------------------------------------------------------------------------
    //  Opera��es de ecrita n�o formatadas

    ostream  &  put(char _c) {
        if ( bp->sputc(_c) == EOF )
            setstate(badbit);
        return *this;
    }

    ostream  &  write(const signed char  * _s, int _n);
    ostream  &  write(const unsigned char  * _s, int _n)
                    { return write((const signed char  *)_s, _n); }

    //-------------------------------------------------------------------------
    //  Opera��es de escrita formatada

    ostream  &  operator<< (signed char _c);
    ostream  &  operator<< (char _c)
                            { return *this << (signed char)_c; }
    ostream  &  operator<< (unsigned char _c)
                            { return *this << (signed char)_c; }

    ostream  &  operator<< (long);
    ostream  &  operator<< (unsigned long);

    ostream  &  operator<< (short _i)
                            { return *this << (long) _i; }
    ostream  &  operator<< (unsigned short _i)
                            { return *this << (unsigned long) _i; }

    ostream  &  operator<< (int _i)
                            { return *this << (long) _i; }
    ostream  &  operator<< (unsigned int _i)
                            { return *this << (unsigned long) _i; }

#ifdef	__GNUC__
    ostream  &  operator<< (long long);
    ostream  &  operator<< (unsigned long long);
#endif

    ostream  &  operator<< (long double);

    ostream  &  operator<< (float _f)
                            { return *this << (long double) _f; }

    ostream  &  operator<< (double _d)
                            { return *this << (long double) _d; }

    // Inserir string terminada por zero
    ostream  &  operator<< (const char  * _s);

    ostream  &  operator<< (const signed char  * _s)
                            { return *this << (const char *) _s; }

    ostream  &  operator<< (const unsigned char  * _s)
                            { return *this << (const char *) _s; }

    // Inserir a representa��o de um pointer
    ostream  &  operator<< (void *);

    // Inserir no stream a partir de um streambuf
    ostream  &  operator<< (streambuf *);

    //-------------------------------------------------------------------------
    //   Execu��o das fun��es manipuladoras
    //
    ostream  &  operator<< (ostream  & (*_f)(ostream &))
        { return (*_f)(* this ); }

    ostream  &  operator<< (ios  & ( *_f)(ios  &)) {
        (*_f) ( *((ios *) this));
        return *this;
    }
};

//=============================================================================
//  
//                              IOSTREAM
//

class iostream : public istream, public ostream {
public:
          iostream(streambuf  * s) : istream(s), ostream(s) { ios::init(s); }
virtual  ~iostream() {}

protected:
          iostream() : istream(), ostream() {}
};


//=============================================================================
//  
//                              ISTREAM_WITHASSIGN
//
class istream_withassign : public istream {
public:
          istream_withassign() : istream() { }
virtual  ~istream_withassign() {}

    // gets buffer from istream and does entire initialization
    istream_withassign  &  operator= (istream  &);

    // associates streambuf with stream and does entire initialization
    istream_withassign  &  operator= (streambuf  *);
};


//=============================================================================
//  
//                              OSTREAM_WITHASSIGN
//
class ostream_withassign : public ostream {
public:
          ostream_withassign() : ostream() {}
virtual  ~ostream_withassign() {}

    // gets buffer from istream and does entire initialization
    ostream_withassign  &  operator= (ostream  & os) {
        ios::init(os.rdbuf());
        return *this;
    }

    // associates streambuf with stream and does entire initialization
    ostream_withassign  &  operator= (streambuf* s) {
        ios::init(s);
        return *this;
    }
};

//=============================================================================
//  
//                              IOSTREAM_WITHASSIGN
//
class iostream_withassign : public iostream {
public:
          iostream_withassign() : iostream() {}
virtual  ~iostream_withassign() {}

    // gets buffer from stream and does entire initialization
    iostream_withassign  &  operator= (ios  & s) {
        ios::init(s.rdbuf());
        return *this;
    }

    // associates streambuf with stream and does entire initialization
    iostream_withassign  &  operator= (streambuf  * b) {
        ios::init(b);
        return *this;
    }
};

//-----------------------------------------------------------------------------
//  streams pre-definidos
//
extern istream_withassign  cin;
extern ostream_withassign  cout;
extern ostream_withassign  cerr;
extern ostream_withassign  clog;

//-----------------------------------------------------------------------------
//  Manipuladores sem argumentos, os outros estao declarados em <iomanip.h>
//
ostream  &  endl(ostream  &);
ostream  &  ends(ostream  &);
ostream  &  flush(ostream  & os);
ios      &  dec(ios  &);
ios      &  hex(ios  &);
ios      &  oct(ios  &);
istream  &  ws(istream  &);

#endif
