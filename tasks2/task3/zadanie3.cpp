#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <bitset>
#include <cstddef>

class BitStream {
     std::vector<std::byte> data_;
     std::uint32_t bitsOccupied_ = 0;

     static auto calculateRequiredAdditionalBytes(std::uint32_t const bits) -> std::uint32_t {
          auto wholeBytes = bits / 8;
          if (bits % 8 != 0) wholeBytes++;
          return wholeBytes;
     }

     auto ensureSufficientCapacity(std::uint32_t const bitLength) -> void {
          auto const availableBits = data_.size() * 8 - bitsOccupied_;

          if (availableBits < bitLength) {
               auto const requiredAdditionalBits = bitLength - availableBits;
               auto const requiredAdditionalBytes =
                         calculateRequiredAdditionalBytes(requiredAdditionalBits);
               data_.insert(data_.end(), requiredAdditionalBytes, std::byte(0));
          }
     }

public:

     auto Add(std::uint32_t const bitLength, void* dataAddr) -> std::uint32_t {
          ensureSufficientCapacity(bitLength);

          auto byteIndex = bitsOccupied_ / 8;
          auto bitIndex = bitsOccupied_ % 8;

          auto streamIterator = BitIterator(data_.data(), byteIndex, bitIndex);
          auto dataIterator = BitIterator(static_cast<std::byte*>(dataAddr), 0, 0);

          for (auto i = std::uint32_t(0); i < bitLength; i++) {
               streamIterator.assign_bit_from(dataIterator);
               ++streamIterator;
               ++dataIterator;
          }

          bitsOccupied_ += bitLength;

          return bitsOccupied_;
     }

class BitIterator {
          std::byte* source_;
          unsigned int bit : 3;

     public:
          BitIterator(std::byte* source, std::uint32_t byteOffset, std::uint32_t bitOffset)
                    : source_(source + byteOffset), bit(bitOffset) { }

          auto operator++() -> BitIterator& {
               if (bit == 7) ++source_;
               ++bit;
               return *this;
          }

          auto assign_bit_from(BitIterator const other) -> void {
               auto const isOtherBitSet = (*(other.source_) & std::byte(1 << other.bit)) == std::byte(0);

               if (isOtherBitSet) {
                    *source_ |= std::byte(1 << bit);
               } else {
                    *source_ &= ~std::byte(1 << bit);
               }
          }
     };
};

int main()
{
     BitStream a ='4';
     BitStream.Add(4,&a);
}
