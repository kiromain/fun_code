#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <bitset>
#include <cstddef>

using namespace std;

class BitStream {
    vector<char> data_;
    uint32_t bitsOccupied_ = 0;

    uint32_t calculateRequiredAdditionalBytes(uint32_t const bits){
        auto wholeBytes = bits / 8;
        if (bits % 8 != 0) wholeBytes++;
        return wholeBytes;
    }

    void ensureSufficientCapacity(uint32_t const bitLength) {
        auto const availableBits = data_.size() * 8 - bitsOccupied_;

        if (availableBits < bitLength) {
            auto const requiredAdditionalBits = bitLength - availableBits;
            auto const requiredAdditionalBytes =
                    calculateRequiredAdditionalBytes(requiredAdditionalBits);
            data_.insert(data_.end(), requiredAdditionalBytes, char(0));
        }
    }

public:

    uint32_t Add(uint32_t const bitLength, void* dataAddr) {
        ensureSufficientCapacity(bitLength);

        uint32_t byteIndex = bitsOccupied_ / 8;
        uint32_t bitIndex = bitsOccupied_ % 8;

        auto streamIterator = BitIterator(data_.data(), byteIndex, bitIndex);
        auto dataIterator = BitIterator(static_cast<char*>(dataAddr), 0, 0);

        for (uint32_t i = uint32_t(0); i < bitLength; i++) {
            streamIterator.assign_bit_from(dataIterator);
            ++streamIterator;
            ++dataIterator;
        }

        bitsOccupied_ += bitLength;

        return bitsOccupied_;
    }

class BitIterator {
        char* source_;
        unsigned int bit : 3;

    public:
        BitIterator(char* source, uint32_t byteOffset, uint32_t bitOffset)
                : source_(source + byteOffset), bit(bitOffset) { }

        auto operator++() -> BitIterator& {
            if (bit == 7) ++source_;
            ++bit;
            return *this;
        }

        void assign_bit_from(BitIterator const other){
            uint32_t const isOtherBitSet = (*(other.source_) & char(1 << other.bit)) == char(0);

            if (isOtherBitSet) {
                *source_ |= char(1 << bit);
            } else {
                *source_ &= ~char(1 << bit);
            }
        }
    };
};

int main()
{
     /*
     int Var0 = 1234;
     BitStream.Add(4, &Var0);
     BitStream->Add(2, &Var1);
     BitStream->Add(5, &Var2);
     BitStream->Add(1, &Var3);
     BitStream->Add(8, &Var4);
     BitStream->Add(16, &Var5);
     BitStream->Add(4, &Var6);
     */

}
