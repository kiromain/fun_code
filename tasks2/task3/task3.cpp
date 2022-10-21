#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

class bitstream
{
private:
     uint32_t bit_pos=0;
public:
     uint32_t Add(uint32_t bitlength, void* dataAddr)
     {
          ofstream ofs("serialize.txt");

          uint32_t p = *((uint32_t*)dataAddr);

          uint32_t *bits = new uint32_t[bitlength];
          uint32_t *freememory;

          for(int i=bit_pos;i<bit_pos+bitlength;i++){
               bits[i] = (p>>i) & 1;
          }

          for(int i=bit_pos+bitlength;i>bit_pos;i--){
               ofs<<bits[i];
          }
          bit_pos += bitlength;

          freememory = bits;
          delete []bits;

          return bit_pos;
     }
};


int main()
{
     uint32_t var = 23423423;

     bitstream->Add(4,&var);
     /*
     int a=10;
     char *p = (char*)&a;
     for(int i=0;i<sizeof(a);i++){
          cout<<hex<<static_cast<int>(*p++)<<" ";
     }*/

}
