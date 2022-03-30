/**
Lecture de fichier dat (préliminaire)

build: make
(aucune dépendance autre que compilo récent)

A tester avec:
./lecture1 2022_03_04-17_14_27_069_caiman_0_data.dat

va générer:

 - reading 5 spikes
Spike bytes: 4a-0-0-0-
lecture de 4a000000
1: x,y=0,1280
Spike bytes: 8a-3e-fb-0-
lecture de 8a3efb00
2: x,y=1004,1311
Spike bytes: 4a-b-2b-1-
lecture de 4a0b2b01
3: x,y=1196,1285
Spike bytes: ca-36-5f-1-
lecture de ca365f01
4: x,y=380,1307
Spike bytes: ca-36-61-1-
lecture de ca366101
5: x,y=388,1307

=> ça me parait pas très cohérent...
*/

//#include <fstream>
#include <sstream>
#include <iomanip>

#include "spike.hpp"
/**

Endianness: little endian => most significant bits last

\verbatim
    Stockage du spike sous la forme d'un mot de 32 bits:

        Spike(0) => Flag de nouvelle Image, sépare les Spikes issues des différentes images. Si ce bit est à "1", cela indique le changement d'image au cours de l'acquisition.
        Spike(1) => Signe du Spike. indique si un éclaircissement ou un assombrissement du pixel à eu lieu
        Spike (5 downto 2) => indice du Filtre déclenchés

            "0000" => filtre 0°
            "0001" => filtre + 45°
            "0010" => filtre +90°
            "0011" => filtre -45°

        Spike (16 downto 6) => Position X du Spike dans l’image

        Spike(27 downto 17) => Position Y du Spike dans l’image
        Spike(31 downto 28) => Non utilisé pour le moment, ce champs est toujours lus en tant que "1111"
\endverbatim
*/

std::ofstream openOutputDataFile( std::string fname )
{
	std::ofstream fout( fname );
	if( !fout.is_open() )
	{
		std::cout << "Error: failed to open output file '" << fname << "'\n";
		std::exit(2);
	}
	return fout;
}

/// Lecture de fichier dat
/**
- arg1: nom fichier
- arg2 (optionnel): nombre de spikes à lire ou 'a' pour 'all': lecture de tout le fichier
- arg3 (optionnel): 0 ou 1. Si 1, alors les spikes sont sauvegardés dans des fichiers par frame dans un sous dossier "data" (0 par défaut)
*/
int main( int argc, char** argv )
{
	int fn_index_width = 5;
	if( argc < 2 )
	{
		std::cout << "Error: missing filename\n";
		return 1;
	}
	size_t nbSpikes{5};
	bool readAll{false};
	if( argc > 2 )
	{
		if( std::string{ argv[2]} == "a" ) // read all
			readAll = true;
		else
			nbSpikes = std::atoi( argv[2] );
	}

	if( readAll )
		std::cout << "- reading whole file\n";
	else
		std::cout << "- attempt reading " << nbSpikes << " spikes\n";

	bool saveSeparateFiles{false};
	if( argc > 3 )
	{
		if( std::atoi( argv[3] ) == 1 )
			saveSeparateFiles = true;
	}

	std::ifstream f( argv[1], std::ios::binary );
    if( !f.is_open() )
	{
		std::cout << "Error: failed to open input file " << argv[1] << '\n';
		return 1;
	}

	std::ofstream fout( "out.dat" );
	if( !fout.is_open() )
	{
		std::cout << "Error: failed to open output file out.dat\n";
		return 2;
	}

	std::ofstream fout2;
	if( saveSeparateFiles )
	{
		fout2.open( "data/out_0.dat" );
		if( !fout2.is_open() )
		{
			std::cout << "Error: failed to open output file data/out_0.dat\n";
			return 3;
		}
	}

	fout << "# frame;index;orientation;x;y\n";
	fout2 << "# frame;index;orientation;x;y\n";


	size_t c=0;
	char buf[4];
	do
	{
		c++;
		f.read( buf, 4 );
//		std::cout << "buf" <<
		Spike sp( buf );
		fout << sp;
		if( sp._frameHasChanged && saveSeparateFiles )
		{
            fout2.close();
            std::ostringstream ssfn;
            ssfn << "data/out_" << std::setw(5) << std::setfill('0') << sp._frame;
            fout2.open( ssfn.str() );
		}
		fout2 << sp;
	}
	while( (c != nbSpikes | readAll) && !f.eof() );

	fout << "# end, read " << c << " spikes in " << Spike::s_frame << " frames\n";

	std::cout << std::dec << "- read " << c << " spikes in " << Spike::s_frame << " frames\n";

}
