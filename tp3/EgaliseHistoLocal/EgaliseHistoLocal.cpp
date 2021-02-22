#include "EgaliseHistoLocal.hpp"
#include <iostream>

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
    unsigned int marge = windowsSize/2,
            w = input->width(),
            h = input->height();

    output = new GrayImage(w, h);

    //histogramme cumulé croissant

    auto_ref<ns_wtni::e1::signal<long> > histo = new ns_wtni::e1::signal<long>(256);

    // Ecrire le code du plugin : TODO !!
    for (unsigned int line = marge; line < input->height() - marge; line++)
    {
        for(unsigned int column = marge; column < input->width() - marge; column++)
        {
            //int hc[256];
            //memset(hc,0,256*sizeof(int));
            for(unsigned int s=0;s <histo->size();s++){
                (*histo)[s] = 0;
            }

            for (unsigned ll = line - marge; ll <= line + marge; ll++)
            {
                for(unsigned int cc = column - marge; cc <= column + marge; cc++)
                {
                    int pixel = (*input)[ll][cc];
                    (*histo)[pixel]++;
                }
            }

            for(int i=1;i<256;i++){
                (*histo)[i] += (*histo)[i-1];
            }

            //calcul de HC
            int pixel = (*input)[line][column];
            pixel = 255 * double((*histo)[pixel]) / double((*histo)[255]);
            (*output)[line][column] = pixel;
        }
    }
    return true;
}

CREATE_PLUGIN( EgaliseHistoLocal );

