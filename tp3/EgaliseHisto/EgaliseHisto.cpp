#include "EgaliseHisto.hpp"

using namespace ns_wtni;

EgaliseHisto::EgaliseHisto( pluglink *p ) : plugin(p)
{
// Ajout des donnees en entree
	add_input( input, "image d'entrée" );

// Ajout des donnees en sortie
	add_output( output, "image de sortie" );
// Ajout des parametres
}

bool EgaliseHisto::execute( std::string &msg)
{

	// Tester les entrees - A COMPLETER si NECESSAIRE !
	if ( ! input )
	{
		 msg = "L'entree n°1 n'est pas initialisee.";
		return false;
	}

	// ALLOUER les sorties ! TODO
	// Ecrire le code du plugin : TODO !!
    output = input;
    GrayImage &out = *output;

    //histogramme cumulé croissant
    auto_ref<ns_wtni::e1::signal<long> > histo = new ns_wtni::e1::signal<long>(256);
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

    //parcours de notre image
    for (unsigned int colonne = 0; colonne < input->width(); colonne++) {
        for (unsigned int ligne = 0; ligne < input->height(); ligne++) {
           int value = proxy[ligne][colonne];
           out[ligne][colonne] = (int) round(double(255) * (double)(*histo)[value] / double((*histo)[255]) ) ;
        }
    }
	return true; 
}

CREATE_PLUGIN( EgaliseHisto );

