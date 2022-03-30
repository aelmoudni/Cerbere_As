/**
\file
\brief lecture fichier dat et construction image via OpenCv

WIP !!!
*/

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/highgui.hpp"
//#include <iostream>
//#include <fstream>
#include "spike.hpp"

int main( int argc, char** argv )
{
#if 0
	auto im_h = 1000;  // arbitraire
	auto im_w = 1600;
	if( argc < 2 )
	{
		std::cout << "Error: missing filename\n";
		return 1;
	}

	std::ifstream f( argv[1], std::ios::binary );
    if( !f.is_open() )
	{
		std::cout << "Error: failed to open input file " << argv[1] << '\n';
		return 1;
	}

	cv::Mat img;
	img.create( im_h, im_w, CV_8UC3 );

	size_t c=0;
	char buf[4];
	do
	{
		c++;
		f.read( buf, 4 );
//		std::cout << "buf" <<
		Spike sp( buf );
	}
	while( !f.eof() );

	cv::imwrite( "out.png", img );
	std::cout << "- read " << c << " spikes in " << Spike::s_frame << " frames\n";
#endif
}

