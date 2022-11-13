//
// Created by lianyu on 2022/11/12.
//

#ifndef MINIDB_LIBZPAQ_H
#define MINIDB_LIBZPAQ_H
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

namespace libzpaq {
  // 1, 2, 4, 8 byte unsigned integers
  typedef uint8_t U8;
  typedef uint16_t U16;
  typedef uint32_t U32;
  typedef uint64_t U64;

// Tables for parsing ZPAQL source code
  extern const char* compname[256];    // list of ZPAQL component types
  extern const int compsize[256];      // number of bytes to encode a component
  extern const char* opcodelist[272];  // list of ZPAQL instructions

// Callback for error handling
  extern void error(const char* msg);

// Virtual base classes for input and output
// get() and put() must be overridden to read or write 1 byte.
// read() and write() may be overridden to read or write n bytes more
// efficiently than calling get() or put() n times.
  class Reader {
  public:
    virtual int get() = 0;  // should return 0..255, or -1 at EOF
    virtual int read(char* buf, int n); // read to buf[n], return no. read
    virtual ~Reader() {}
  };

  class Writer {
  public:
    virtual void put(int c) = 0;  // should output low 8 bits of c
    virtual void write(const char* buf, int n);  // write buf[n]
    virtual ~Writer() {}
  };

  // Read 16 bit little-endian number
  int toU16(const char* p);

// An Array of T is cleared and aligned on a 64 byte address
//   with no constructors called. No copy or assignment.
// Array<T> a(n, ex=0);  - creates n<<ex elements of type T
// a[i] - index
// a(i) - index mod n, n must be a power of 2
// a.size() - gets n
  template <typename T>
  class Array {
    T *data;     // user location of [0] on a 64 byte boundary
    size_t n;    // user size
    int offset;  // distance back in bytes to start of actual allocation
    void operator=(const Array&);  // no assignment
    Array(const Array&);  // no copy
  public:
    Array(size_t sz=0, int ex=0): data(0), n(0), offset(0) {
      resize(sz, ex);} // [0..sz-1] = 0
    void resize(size_t sz, int ex=0); // change size, erase content to zeros
    ~Array() {resize(0);}  // free memory
    size_t size() const {return n;}  // get size
    int isize() const {return int(n);}  // get size as an int
    T& operator[](size_t i) {assert(n>0 && i<n); return data[i];}
    T& operator()(size_t i) {assert(n>0 && (n&(n-1))==0); return data[i&(n-1)];}
  };

// Change size to sz<<ex elements of 0
  template<typename T>
  void Array<T>::resize(size_t sz, int ex) {
    assert(size_t(-1)>0);  // unsigned type?
    while (ex>0) {
      if (sz>sz*2) error("Array too big");
      sz*=2, --ex;
    }
    if (n>0) {
      assert(offset>0 && offset<=64);
      assert((char*)data-offset);
      ::free((char*)data-offset);
    }
    n=0;
    offset=0;
    if (sz==0) return;
    n=sz;
    const size_t nb=128+n*sizeof(T);  // test for overflow
    if (nb<=128 || (nb-128)/sizeof(T)!=n) n=0, error("Array too big");
    data=(T*)::calloc(nb, 1);
    if (!data) n=0, error("Out of memory");
    offset=64-(((char*)data-(char*)0)&63);
    assert(offset>0 && offset<=64);
    data=(T*)((char*)data+offset);
  }

//////////////////////////// SHA1 ////////////////////////////

// For computing SHA-1 checksums
  class SHA1 {
  public:
    void put(int c) {  // hash 1 byte
      U32& r=w[U32(len)>>5&15];
      r=(r<<8)|(c&255);
      len+=8;
      if ((U32(len)&511)==0) process();
    }
    void write(const char* buf, int64_t n); // hash buf[0..n-1]
    double size() const {return len/8;}     // size in bytes
    uint64_t usize() const {return len/8;}  // size in bytes
    const char* result();  // get hash and reset
    SHA1() {init();}
  private:
    void init();      // reset, but don't clear hbuf
    U64 len;          // length in bits
    U32 h[5];         // hash state
    U32 w[16];        // input buffer
    char hbuf[20];    // result
    void process();   // hash 1 block
  };

//////////////////////////// SHA256 //////////////////////////

// For computing SHA-256 checksums
// http://en.wikipedia.org/wiki/SHA-2
  class SHA256 {
  public:
    void put(int c) {  // hash 1 byte
      unsigned& r=w[len0>>5&15];
      r=(r<<8)|(c&255);
      if (!(len0+=8)) ++len1;
      if ((len0&511)==0) process();
    }
    double size() const {return len0/8+len1*536870912.0;} // size in bytes
    uint64_t usize() const {return len0/8+(U64(len1)<<29);} //size in bytes
    const char* result();  // get hash and reset
    SHA256() {init();}
  private:
    void init();           // reset, but don't clear hbuf
    unsigned len0, len1;   // length in bits (low, high)
    unsigned s[8];         // hash state
    unsigned w[16];        // input buffer
    char hbuf[32];         // result
    void process();        // hash 1 block
  };

//////////////////////////// AES /////////////////////////////

// For encrypting with AES in CTR mode.
// The i'th 16 byte block is encrypted by XOR with AES(i)
// (i is big endian or MSB first, starting with 0).
  class AES_CTR {
    U32 Te0[256], Te1[256], Te2[256], Te3[256], Te4[256]; // encryption tables
    U32 ek[60];  // round key
    int Nr;  // number of rounds (10, 12, 14 for AES 128, 192, 256)
    U32 iv0, iv1;  // first 8 bytes in CTR mode
  public:
    AES_CTR(const char* key, int keylen, const char* iv=0);
    // Schedule: keylen is 16, 24, or 32, iv is 8 bytes or NULL
    void encrypt(U32 s0, U32 s1, U32 s2, U32 s3, unsigned char* ct);
    void encrypt(char* buf, int n, U64 offset);  // encrypt n bytes of buf
  };

//////////////////////////// ZPAQL ///////////////////////////
// Symbolic constants, instruction size, and names
  typedef enum {NONE,CONS,CM,ICM,MATCH,AVG,MIX2,MIX,ISSE,SSE} CompType;
  extern const int compsize[256];
  class Decoder;  // forward

// A ZPAQL machine COMP+HCOMP or PCOMP.
  class ZPAQL {
  public:
    ZPAQL();
    ~ZPAQL();
    void clear();           // Free memory, erase program, reset machine state
    void inith();           // Initialize as HCOMP to run
    void initp();           // Initialize as PCOMP to run
    double memory();        // Return memory requirement in bytes
    void run(U32 input);    // Execute with input
    int read(Reader* in2);  // Read header
    bool write(Writer* out2, bool pp); // If pp write PCOMP else HCOMP header
    int step(U32 input, int mode);  // Trace execution (defined externally)

    Writer* output;         // Destination for OUT instruction, or 0 to suppress
    SHA1* sha1;             // Points to checksum computer
    U32 H(int i) {return h(i);}  // get element of h

    void flush();           // write outbuf[0..bufptr-1] to output and sha1
    void outc(int ch) {     // output byte ch (0..255) or -1 at EOS
      if (ch<0 || (outbuf[bufptr]=ch, ++bufptr==outbuf.isize())) flush();
    }

    // ZPAQ1 block header
    Array<U8> header;   // hsize[2] hh hm ph pm n COMP (guard) HCOMP (guard)
    int cend;           // COMP in header[7...cend-1]
    int hbegin, hend;   // HCOMP/PCOMP in header[hbegin...hend-1]

  private:
    // Machine state for executing HCOMP
    Array<U8> m;        // memory array M for HCOMP
    Array<U32> h;       // hash array H for HCOMP
    Array<U32> r;       // 256 element register array
    Array<char> outbuf; // output buffer
    int bufptr;         // number of bytes in outbuf
    U32 a, b, c, d;     // machine registers
    int f;              // condition flag
    int pc;             // program counter
    int rcode_size;     // length of rcode
    U8* rcode;          // JIT code for run()

    // Support code
    int assemble();  // put JIT code in rcode
    void init(int hbits, int mbits);  // initialize H and M sizes
    int execute();  // interpret 1 instruction, return 0 after HALT, else 1
    void run0(U32 input);  // default run() if not JIT
    void div(U32 x) {if (x) a/=x; else a=0;}
    void mod(U32 x) {if (x) a%=x; else a=0;}
    void swap(U32& x) {a^=x; x^=a; a^=x;}
    void swap(U8& x)  {a^=x; x^=a; a^=x;}
    void err();  // exit with run time error
  };

///////////////////////// Component //////////////////////////

// A Component is a context model, indirect context model, match model,
// fixed weight mixer, adaptive 2 input mixer without or with current
// partial byte as context, adaptive m input mixer (without or with),
// or SSE (without or with).

  struct Component {
    size_t limit;   // max count for cm
    size_t cxt;     // saved context
    size_t a, b, c; // multi-purpose variables
    Array<U32> cm;  // cm[cxt] -> p in bits 31..10, n in 9..0; MATCH index
    Array<U8> ht;   // ICM/ISSE hash table[0..size1][0..15] and MATCH buf
    Array<U16> a16; // MIX weights
    void init();    // initialize to all 0
    Component() {init();}
  };

////////////////////////// StateTable ////////////////////////

// Next state table
  class StateTable {
  public:
    U8 ns[1024]; // state*4 -> next state if 0, if 1, n0, n1
    int next(int state, int y) {  // next state for bit y
      assert(state>=0 && state<256);
      assert(y>=0 && y<4);
      return ns[state*4+y];
    }
    int cminit(int state) {  // initial probability of 1 * 2^23
      assert(state>=0 && state<256);
      return ((ns[state*4+3]*2+1)<<22)/(ns[state*4+2]+ns[state*4+3]+1);
    }
    StateTable();
  };

///////////////////////// Predictor //////////////////////////

// A predictor guesses the next bit
  class Predictor {
  public:
    Predictor(ZPAQL&);
    ~Predictor();
    void init();          // build model
    int predict();        // probability that next bit is a 1 (0..4095)
    void update(int y);   // train on bit y (0..1)
    int stat(int);        // Defined externally
    bool isModeled() {    // n>0 components?
      assert(z.header.isize()>6);
      return z.header[6]!=0;
    }
  private:

    // Predictor state
    int c8;               // last 0...7 bits.
    int hmap4;            // c8 split into nibbles
    int p[256];           // predictions
    U32 h[256];           // unrolled copy of z.h
    ZPAQL& z;             // VM to compute context hashes, includes H, n
    Component comp[256];  // the model, includes P
    bool initTables;      // are tables initialized?

    // Modeling support functions
    int predict0();       // default
    void update0(int y);  // default
    int dt2k[256];        // division table for match: dt2k[i] = 2^12/i
    int dt[1024];         // division table for cm: dt[i] = 2^16/(i+1.5)
    U16 squasht[4096];    // squash() lookup table
    short stretcht[32768];// stretch() lookup table
    StateTable st;        // next, cminit functions
    U8* pcode;            // JIT code for predict() and update()
    int pcode_size;       // length of pcode

    // reduce prediction error in cr.cm
    void train(Component& cr, int y) {
      assert(y==0 || y==1);
      U32& pn=cr.cm(cr.cxt);
      U32 count=pn&0x3ff;
      int error=y*32767-(cr.cm(cr.cxt)>>17);
      pn+=(error*dt[count]&-1024)+(count<cr.limit);
    }

    // x -> floor(32768/(1+exp(-x/64)))
    int squash(int x) {
      assert(initTables);
      assert(x>=-2048 && x<=2047);
      return squasht[x+2048];
    }

    // x -> round(64*log((x+0.5)/(32767.5-x))), approx inverse of squash
    int stretch(int x) {
      assert(initTables);
      assert(x>=0 && x<=32767);
      return stretcht[x];
    }

    // bound x to a 12 bit signed int
    int clamp2k(int x) {
      if (x<-2048) return -2048;
      else if (x>2047) return 2047;
      else return x;
    }

    // bound x to a 20 bit signed int
    int clamp512k(int x) {
      if (x<-(1<<19)) return -(1<<19);
      else if (x>=(1<<19)) return (1<<19)-1;
      else return x;
    }

    // Get cxt in ht, creating a new row if needed
    size_t find(Array<U8>& ht, int sizebits, U32 cxt);

    // Put JIT code in pcode
    int assemble_p();
  };

  //////////////////////////// Decoder /////////////////////////
// Decoder decompresses using an arithmetic code
  class Decoder: public Reader {
  public:
    Reader* in;        // destination
    Decoder(ZPAQL& z);
    int decompress();  // return a byte or EOF
    int skip();        // skip to the end of the segment, return next byte
    void init();       // initialize at start of block
    int stat(int x) {return pr.stat(x);}
    int get() {        // return 1 byte of buffered input or EOF
      if (rpos==wpos) {
        rpos=0;
        wpos=in ? in->read(&buf[0], BUFSIZE) : 0;
        assert(wpos<=BUFSIZE);
      }
      return rpos<wpos ? U8(buf[rpos++]) : -1;
    }
    int buffered() {return wpos-rpos;}  // how far read ahead?
  private:
    U32 low, high;     // range
    U32 curr;          // last 4 bytes of archive or remaining bytes in subblock
    U32 rpos, wpos;    // read, write position in buf
    Predictor pr;      // to get p
    enum {BUFSIZE=1<<16};
    Array<char> buf;   // input buffer of size BUFSIZE bytes
    int decode(int p); // return decoded bit (0..1) with prob. p (0..65535)
  };

/////////////////////////// PostProcessor ////////////////////

  class PostProcessor {
    int state;   // input parse state: 0=INIT, 1=PASS, 2..4=loading, 5=POST
    int hsize;   // header size
    int ph, pm;  // sizes of H and M in z
  public:
    ZPAQL z;     // holds PCOMP
    PostProcessor(): state(0), hsize(0), ph(0), pm(0) {}
    void init(int h, int m);  // ph, pm sizes of H and M
    int write(int c);  // Input a byte, return state
    int getState() const {return state;}
    void setOutput(Writer* out) {z.output=out;}
    void setSHA1(SHA1* sha1ptr) {z.sha1=sha1ptr;}
  };

//////////////////////// Decompresser ////////////////////////

// For decompression and listing archive contents
  class Decompresser {
  public:
    Decompresser(): z(), dec(z), pp(), state(BLOCK), decode_state(FIRSTSEG) {}
    void setInput(Reader* in) {dec.in=in;}
    bool findBlock(double* memptr = 0);
    void hcomp(Writer* out2) {z.write(out2, false);}
    bool findFilename(Writer* = 0);
    void readComment(Writer* = 0);
    void setOutput(Writer* out) {pp.setOutput(out);}
    void setSHA1(SHA1* sha1ptr) {pp.setSHA1(sha1ptr);}
    bool decompress(int n = -1);  // n bytes, -1=all, return true until done
    bool pcomp(Writer* out2) {return pp.z.write(out2, true);}
    void readSegmentEnd(char* sha1string = 0);
    int stat(int x) {return dec.stat(x);}
    int buffered() {return dec.buffered();}
  private:
    ZPAQL z;
    Decoder dec;
    PostProcessor pp;
    enum {BLOCK, FILENAME, COMMENT, DATA, SEGEND} state;  // expected next
    enum {FIRSTSEG, SEG, SKIP} decode_state;  // which segment in block?
  };

  //////////////////////////// Encoder /////////////////////////

// Encoder compresses using an arithmetic code
  class Encoder {
  public:
    Encoder(ZPAQL& z, int size=0):
            out(0), low(1), high(0xFFFFFFFF), pr(z) {}
    void init();
    void compress(int c);  // c is 0..255 or EOF
    int stat(int x) {return pr.stat(x);}
    Writer* out;  // destination
  private:
    U32 low, high; // range
    Predictor pr;  // to get p
    Array<char> buf; // unmodeled input
    void encode(int y, int p); // encode bit y (0..1) with prob. p (0..65535)
  };

//////////////////////////// Compiler ////////////////////////

// Input ZPAQL source code with args and store the compiled code
// in hz and pz and write pcomp_cmd to out2.

  class Compiler {
  public:
    Compiler(const char* in, int* args, ZPAQL& hz, ZPAQL& pz, Writer* out2);
  private:
    const char* in;  // ZPAQL source code
    int* args;       // Array of up to 9 args, default NULL = all 0
    ZPAQL& hz;       // Output of COMP and HCOMP sections
    ZPAQL& pz;       // Output of PCOMP section
    Writer* out2;    // Output ... of "PCOMP ... ;"
    int line;        // Input line number for reporting errors
    int state;       // parse state: 0=space -1=word >0 (nest level)

    // Symbolic constants
    typedef enum {NONE,CONS,CM,ICM,MATCH,AVG,MIX2,MIX,ISSE,SSE,
      JT=39,JF=47,JMP=63,LJ=255,
      POST=256,PCOMP,END,IF,IFNOT,ELSE,ENDIF,DO,
      WHILE,UNTIL,FOREVER,IFL,IFNOTL,ELSEL,SEMICOLON} CompType;

    void syntaxError(const char* msg, const char* expected=0); // error()
    void next();                     // advance in to next token
    bool matchToken(const char* tok);// in==token?
    int rtoken(int low, int high);   // return token which must be in range
    int rtoken(const char* list[]);  // return token by position in list
    void rtoken(const char* s);      // return token which must be s
    int compile_comp(ZPAQL& z);      // compile either HCOMP or PCOMP

    // Stack of n elements
    class Stack {
      libzpaq::Array<U16> s;
      size_t top;
    public:
      Stack(int n): s(n), top(0) {}
      void push(const U16& x) {
        if (top>=s.size()) error("IF or DO nested too deep");
        s[top++]=x;
      }
      U16 pop() {
        if (top<=0) error("unmatched IF or DO");
        return s[--top];
      }
    };

    Stack if_stack, do_stack;
  };

//////////////////////// Compressor //////////////////////////

  class Compressor {
  public:
    Compressor(): enc(z), in(0), state(INIT), verify(false) {}
    void setOutput(Writer* out) {enc.out=out;}
    void writeTag();
    void startBlock(int level);  // level=1,2,3
    void startBlock(const char* hcomp);     // ZPAQL byte code
    void startBlock(const char* config,     // ZPAQL source code
                    int* args,              // NULL or int[9] arguments
                    Writer* pcomp_cmd = 0); // retrieve preprocessor command
    void setVerify(bool v) {verify = v;}    // check postprocessing?
    void hcomp(Writer* out2) {z.write(out2, false);}
    bool pcomp(Writer* out2) {return pz.write(out2, true);}
    void startSegment(const char* filename = 0, const char* comment = 0);
    void setInput(Reader* i) {in=i;}
    void postProcess(const char* pcomp = 0, int len = 0);  // byte code
    bool compress(int n = -1);  // n bytes, -1=all, return true until done
    void endSegment(const char* sha1string = 0);
    char* endSegmentChecksum(int64_t* size = 0, bool dosha1=true);
    int64_t getSize() {return sha1.usize();}
    const char* getChecksum() {return sha1.result();}
    void endBlock();
    int stat(int x) {return enc.stat(x);}
  private:
    ZPAQL z, pz;  // model and test postprocessor
    Encoder enc;  // arithmetic encoder containing predictor
    Reader* in;   // input source
    SHA1 sha1;    // to test pz output
    char sha1result[20];  // sha1 output
    enum {INIT, BLOCK1, SEG1, BLOCK2, SEG2} state;
    bool verify;  // if true then test by postprocessing
  };

/////////////////////////// StringBuffer /////////////////////

// For (de)compressing to/from a string. Writing appends bytes
// which can be later read.
  class StringBuffer: public libzpaq::Reader, public libzpaq::Writer {
    unsigned char* p;  // allocated memory, not NUL terminated, may be NULL
    size_t al;         // number of bytes allocated, 0 iff p is NULL
    size_t wpos;       // index of next byte to write, wpos <= al
    size_t rpos;       // index of next byte to read, rpos < wpos or return EOF.
    size_t limit;      // max size, default = -1
    const size_t init; // initial size on first use after reset

    // Increase capacity to a without changing size
    void reserve(size_t a) {
      assert(!al==!p);
      if (a<=al) return;
      unsigned char* q=0;
      if (a>0) q=(unsigned char*)(p ? realloc(p, a) : malloc(a));
      if (a>0 && !q) error("Out of memory");
      p=q;
      al=a;
    }

    // Enlarge al to make room to write at least n bytes.
    void lengthen(size_t n) {
      assert(wpos<=al);
      if (wpos+n>limit || wpos+n<wpos) error("StringBuffer overflow");
      if (wpos+n<=al) return;
      size_t a=al;
      while (wpos+n>=a) a=a*2+init;
      reserve(a);
    }

    // No assignment or copy
    void operator=(const StringBuffer&);
    StringBuffer(const StringBuffer&);

  public:

    // Direct access to data
    unsigned char* data() {assert(p || wpos==0); return p;}

    // Allocate no memory initially
    StringBuffer(size_t n=0):
            p(0), al(0), wpos(0), rpos(0), limit(size_t(-1)), init(n>128?n:128) {}

    // Set output limit
    void setLimit(size_t n) {limit=n;}

    // Free memory
    ~StringBuffer() {if (p) free(p);}

    // Return number of bytes written.
    size_t size() const {return wpos;}

    // Return number of bytes left to read
    size_t remaining() const {return wpos-rpos;}

    // Reset size to 0 and free memory.
    void reset() {
      if (p) free(p);
      p=0;
      al=rpos=wpos=0;
    }

    // Write a single byte.
    void put(int c) {  // write 1 byte
      lengthen(1);
      assert(p);
      assert(wpos<al);
      p[wpos++]=c;
      assert(wpos<=al);
    }

    // Write buf[0..n-1]. If buf is NULL then advance write pointer only.
    void write(const char* buf, int n) {
      if (n<1) return;
      lengthen(n);
      assert(p);
      assert(wpos+n<=al);
      if (buf) memcpy(p+wpos, buf, n);
      wpos+=n;
    }

    // Read a single byte. Return EOF (-1) at end.
    int get() {
      assert(rpos<=wpos);
      assert(rpos==wpos || p);
      return rpos<wpos ? p[rpos++] : -1;
    }

    // Read up to n bytes into buf[0..] or fewer if EOF is first.
    // Return the number of bytes actually read.
    // If buf is NULL then advance read pointer without reading.
    int read(char* buf, int n) {
      assert(rpos<=wpos);
      assert(wpos<=al);
      assert(!al==!p);
      if (rpos+n>wpos) n=wpos-rpos;
      if (n>0 && buf) memcpy(buf, p+rpos, n);
      rpos+=n;
      return n;
    }

    // Return the entire string as a read-only array.
    const char* c_str() const {return (const char*)p;}

    // Truncate the string to size i.
    void resize(size_t i) {
      wpos=i;
      if (rpos>wpos) rpos=wpos;
    }

    // Swap efficiently (init is not swapped)
    void swap(StringBuffer& s) {
      std::swap(p, s.p);
      std::swap(al, s.al);
      std::swap(wpos, s.wpos);
      std::swap(rpos, s.rpos);
      std::swap(limit, s.limit);
    }
  };


  /////////////////////////// compress() ///////////////////////

// Compress in to out in multiple blocks. Default method is "14,128,0"
// Default filename is "". Comment is appended to input size.
// dosha1 means save the SHA-1 checksum.
  void compress(Reader* in, Writer* out, const char* method,
                const char* filename=0, const char* comment=0, bool dosha1=true);

// Same as compress() but output is 1 block, ignoring block size parameter.
  void compressBlock(StringBuffer* in, Writer* out, const char* method,
                     const char* filename=0, const char* comment=0, bool dosha1=true);

  //////////////////////////// stretchKey //////////////////////
// Strengthen password pw[0..pwlen-1] and salt[0..saltlen-1]
// to produce key buf[0..buflen-1]. Uses O(n*r*p) time and 128*r*n bytes
// of memory. n must be a power of 2 and r <= 8.
  void scrypt(const char* pw, int pwlen,
              const char* salt, int saltlen,
              int n, int r, int p, char* buf, int buflen);

  // Generate a strong key out[0..31] key[0..31] and salt[0..31].
// Calls scrypt(key, 32, salt, 32, 16384, 8, 1, out, 32);
  void stretchKey(char* out, const char* key, const char* salt);

//////////////////////////// random //////////////////////////

// Fill buf[0..n-1] with n cryptographic random bytes. The first
// byte is never '7' or 'z'.
  void random(char* buf, int n);

/////////////////////////// decompress() /////////////////////

  void decompress(Reader* in, Writer* out);
};

#endif //MINIDB_LIBZPAQ_H
