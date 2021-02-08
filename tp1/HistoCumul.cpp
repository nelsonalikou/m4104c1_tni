#include "HistoCumul.hpp"

using namespace ns_wtni;

HistoCumul::HistoCumul( pluglink *p ) : plugin(p)
{
// Ajout des donnees en entree
    add_input( input, "Image noir et blanc en entree" );

// Ajout des donnees en sortie
	add_output( histo, "Histogramme cummule" );
// Ajout des parametres
}

bool HistoCumul::execute( std::string &msg)
{

	// Tester les entrees - A COMPLETER si NECESSAIRE !
	if ( ! input )
	{
		 msg = "L'entree n°1 n'est pas initialisee.";
		return false;
	}

	// ALLOUER les sorties ! TODO
    histo = new ns_wtni::e1::signal<long>(256);
    const GrayImage &proxy = *input;
    for (int line = 0; line < (int)proxy.height(); line++)
    {
        for (int colonne = 0; colonne < (int)input->width(); colonne++)
        {
             int value = proxy[line][colonne];
             (*histo)[value] += 1;
        }
    }

    for(unsigned int i=1; i<histo->size(); i++)
    {
        (*histo)[i] = (*histo)[i-1] + (*histo)[i];
    }

	return true; 
}

CREATE_PLUGIN( HistoCumul );

