#include "EgaliseHistoLocal.hpp"

using namespace ns_wtni;

EgaliseHistoLocal::EgaliseHistoLocal( pluglink *p ) : plugin(p)
{
// Ajout des donnees en entree
	add_input( input, "Image en entree" );

// Ajout des donnees en sortie
	add_output( output, "Image de sortie" );
// Ajout des parametres
	windowsSize = 3;
	add_param( windowsSize, "Taille fenetre de calcul" );
}


bool EgaliseHistoLocal::is_windowsSize_set( std::string &msg )
{
    bool res = true;
    // Ajouter les tests a faire sur le parametre windowsSize
    if(windowsSize < 3){
        msg = "La taille de la fenetre doit etre superieure ou égale à 3";
        res = false;
    }
	// Renseigner la variable msg si necessaire
    return res;
}

bool EgaliseHistoLocal::verifyParameters( std::string &msg, bool isRunning )
{
	//Tableau contenant les differents messages
	std::vector<std::string> msgs;
	std::string _msg; // Message local
	bool res = true;
	_msg.clear();
	if ( is_param_input( &windowsSize )==isRunning && ! is_windowsSize_set( _msg ) )
	{
		 res = false;
		 msgs.push_back( _msg );
	}
	if ( msgs.size()==1 ) msg = msgs.front();
	else if ( msgs.size()>1 )
	{
		msg = "<ul>";
		for (unsigned int i=0; i<msgs.size(); ++i)
			msg += "<li>" + msgs[i] + "</li>";
		msg += "</ul>";
	}
	return res;
}

bool EgaliseHistoLocal::is_ready( std::string & msg )
{
	return verifyParameters(msg, false);
}

bool EgaliseHistoLocal::execute( std::string &msg)
{
	//Tester les parametres
	if ( !verifyParameters( msg, true ) ) 
		return false;

	// Tester les entrees - A COMPLETER si NECESSAIRE !
	if ( ! input )
	{
		 msg = "L'entree n°1 n'est pas initialisee.";
		return false;
	}

	// ALLOUER les sorties ! TODO
	// Ecrire le code du plugin : TODO !!
    GrayImage &out = *output;

    //histogramme cumulé croissant
    auto_ref<ns_wtni::e1::signal<long> > histo = new ns_wtni::e1::signal<long>(256);
    const GrayImage &proxy = *input;
    for (int line = 0; line < (int)proxy.height(); line++)
    {
        for (int colonne = 0; colonne < (int)input->width(); colonne++)
        {
            if(colonne < windowsSize -1 || colonne >= input->width() - windowsSize -1 || line < windowsSize -1 || line >= input->height() - windowsSize -1){
                out[line][colonne] = 0;
            }else{
            }
            int value = proxy[line][colonne];
            (*histo)[value] += 1;
        }
    }

    for(unsigned int i=1; i<histo->size() - windowsSize -1; i++)
    {
        for(unsigned int size = i; size < windowsSize; size++)
        {
            (*histo)[i] += (*histo)[i-1] + (*histo)[i];
        }
    }

    //parcours de notre image
    for (unsigned int colonne = 0; colonne < input->width(); colonne++) {
            for (unsigned int ligne = 0; ligne < input->height(); ligne++) {
                if(colonne < windowsSize -1 || colonne >= input->width() - windowsSize -1 || ligne < windowsSize -1 || ligne >= input->height() - windowsSize -1){
                    out[ligne][colonne] = 0;
                }else{
                    int value = proxy[ligne][colonne];
                    out[ligne][colonne] = (int) round(double(255) * (double)(*histo)[value] / double((*histo)[255]) ) ;
                }
            }
        }

    return true;
}

CREATE_PLUGIN( EgaliseHistoLocal );

