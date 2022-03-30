/**
\file
\brief class Spike
*/

#include <iostream>
#include <fstream>
#include <vector>

class Spike
{
public:
	static size_t s_index; ///< spike index
	static size_t s_frame; ///< frame index
	bool   _frameHasChanged{false};
	size_t _frame; ///< frame index

private:
	size_t _index; ///< spike index

	size_t _posX, _posY;
	bool   _polarity;

public:
	Spike( char* buf )
	{
		std::cout << std::hex;

#if 1
		std::cout << "Spike bytes: ";
		for( int i=0; i<4; i++ )
			std::cout << (0xff&buf[i]) << '-'; // masquage pour l'affichage uniquement
		std::cout << '\n';
#endif
/*		for( int i=0; i<4; i++ )
			std::cout << std::dec << i << ":" << (3-i)*8 << ":" << std::hex <<(int32_t(buf[i]) << ((3-i)*8)) << '-';
		std::cout << '\n';
*/
		uint32_t value = 0;
		unsigned char buf2[4];
		for( int i=0; i<4; i++ )
		{
			buf2[i] = buf[i];
			value |= ( buf2[i] << (3-i)*8 );  // décalage vers la gauche de 24, 16, 8, 0 et OU logique pour insérer dans le mot 32 bits
//			value |= ( buf2[i] << i*8 );  // décalage vers la gauche de 24, 16, 8, 0 et OU logique pour insérer dans le mot 32 bits

		}
		std::cout << "  -value=" << value << '\n';

		std::vector<bool> vbool(32);
		uint8_t mask = 0x80;
        for( int i=0; i<vbool.size(); i++ )
        {
        	auto bit_idx = i / 8;
//        	std::cout << i << ": bit_idx=" << bit_idx << " mask=" << (int)mask << "\n";
        	vbool[i]= buf2[bit_idx] & mask;
        	mask = mask >> 1;
        	if( (i+1)%8 == 0 )
				mask = 0x80;
        }
#if 1
		std::cout << "  -bool: ";
        for( int i=0; i<vbool.size(); i++ )
        	std::cout << vbool[i];
        std::cout << '\n';
#endif
//		std::cout << "lecture de " << std::hex << value << '\n';
/// x: bit 16 à 6: 0000 0000 0000 0001 1111 1111 1100 0000 = 0x00.01.FF.c0
        _posX = value & 0x0001ffc0; // masquage
        _posX = _posX >> 6; // décalage

/// y: bit 27 à 17: 0000 1111 1111 1110 0000 0000 0000 0000 = 0x0F.FE.00.00
        _posY = value & 0x0FFE0000; // masquage
        _posY = _posY >> 17; // décalage
        _polarity = static_cast<bool>(buf2[3] & 0x02);

        if( buf2[0] & 0x80 )  // if first bit = 1
        {
			Spike::s_frame++;      // Moving to next frame
			Spike::s_index = 0;
			_frameHasChanged = true;
        }
		_frame = Spike::s_frame;

		_index = Spike::s_index;
		Spike::s_index++;
	}

	friend std::ostream& operator << ( std::ostream& f, Spike sp )
	{
		const char sep{';'};
		f << std::dec
			<< sp._frame << sep
			<< sp._index << sep
			<< sp._polarity << sep
			<< sp._posX << sep
			<< sp._posY
			<< '\n';
		return f;
	}
};

size_t Spike::s_index = 0;
size_t Spike::s_frame = 0;
