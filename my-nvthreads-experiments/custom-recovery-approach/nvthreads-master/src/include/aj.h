#ifndef _AJ_H_
#define _AJ_H_

class FetchBaseAdd{
public:
  static volatile void* baseaddr;
  static int a ;

  static int get();
  static void set(int v);

  static void* getaddr();
  static void setaddr (void* v);

};
#endif