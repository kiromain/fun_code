#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

class bitstream
{
private:
     string *t;
     char *p;
     uint32_t bit_pos=0;
public:
     uint32_t Add(uint32_t bitlength, void* dataAddr)
     {
          ofstream ofs("serialize.txt");

          unsigned mask;
          mask = (1U<<bitlength) - 1;
          p = (char*)&dataAddr;

          uint32_t bits = mask & (static_cast<int>(*p)>>bit_pos);
          bit_pos+=bitlength;

          ofs.write(p, bitlength);

          return bit_pos;
     }
};
int main()
{
     string newy;
     newy = "12233423";
     uint32_t var = bitstream->Add(4,&newy);
     /*
     int a=10;
     char *p = (char*)&a;
     for(int i=0;i<sizeof(a);i++){
          cout<<hex<<static_cast<int>(*p++)<<" ";
     }*/
}
